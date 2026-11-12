# 蓝牙循迹避障智能小车

基于 STM32F103C8T6 + STM32 标准外设库（SPL）的智能小车，实现蓝牙遥控、红外循迹、超声波测距、舵机转向与 OLED 显示。

## 模块一览

| 模块 | 说明 | 主要知识点 |
|------|------|------------|
| [Serial](./Hardware/Serial.c) | 蓝牙串口遥控，单字符指令 | USART、NVIC 中断收数据 |
| [TCRT5000](./Hardware/TCRT5000.c) | 四路红外循迹采样 | GPIO 上拉输入、位组合 |
| [Follow](./Hardware/Follow.c) | 按循迹值转向控制 | 差速转向、状态判断 |
| [Motor](./Hardware/Motor.c) | TB6612 双电机驱动 | GPIO 方向控制、差速、限幅 |
| [PWM](./Hardware/PWM.c) | TIM3 调速 + TIM2 舵机 | 定时器 PWM、ARR/PSC 计算 |
| [HCSOR04](./Hardware/HCSOR04.c) | HC-SR04 超声波测距 | 输入捕获替代方案、更新中断计数 |
| [Servo](./Hardware/Servo.c) | 舵机角度控制 | 50Hz PWM、脉宽映射 |
| [OLED](./Hardware/OLED.c) | 0.96 寸 SSD1306 显示 | 软件 I2C、字库取模 |
| [Control](./Hardware/Control.c) | 避障决策（备用的控制层） | 多次测距、选空侧绕行 |

## 功能特性

- **蓝牙遥控**：USART1，9600 8N1，中断接收单字符指令，`main.c` 已启用
- **红外循迹**：TCRT5000 四路，采样值 0~15，`Follow_car()` 按位组合转向
- **超声波测距**：TIM4 更新中断以 0.1ms 为心跳数 Echo 高电平，距离 = 计数 × 1.7cm，超过 4m 返回 0
- **舵机扫描**：TIM2 输出 50Hz，0.5~2.5ms 脉宽映射 0~180°
- **电机驱动**：TIM3 输出 10kHz PWM 调速（ARR=100），方向引脚控制正反转
- **OLED 显示**：PA11/PA12 软件 I2C

## 硬件清单

| 器件 | 型号 | 说明 |
|------|------|------|
| 主控板 | STM32F103C8T6 最小系统板 | 72MHz，64KB Flash / 20KB RAM |
| 超声波 | HC-SR04 | 测距 2cm ~ 400cm |
| 循迹 | TCRT5000 四路模块 | 红外反射式，黑线输出 0 |
| 舵机 | SG90 等 | 50Hz 控制信号 |
| 电机驱动 | TB6612 | 双 H 桥 |
| 显示 | 0.96 寸 OLED（I2C） | SSD1306 |
| 蓝牙 | JDY-31 等串口透传模块 | 接 USART1 |
| 烧录 | ST-Link V2 | SWD 接口 |

## 引脚分配

| 模块 | 引脚 |
|------|------|
| HC-SR04 | Trig = PA4，Echo = PA5 |
| OLED | SCL = PA11，SDA = PA12 |
| 舵机 | PA0（TIM2_CH1） |
| 左电机 | PWM = PA7（TIM3_CH2），IN1 / IN2 = PB5 / PB6 |
| 右电机 | PWM = PA6（TIM3_CH1），IN1 / IN2 = PB7 / PB8 |
| 四路循迹 | PB1 / PB0 / PB10 / PB11 |
| 蓝牙 | USART1：PA9（TX）/ PA10（RX） |

> 注意 `PWM.c` 的命名与实际通道相反：`PWM_Compare1_L()` 驱动的是 TIM3_CH1 → PA6 → **右轮**，`PWM_Compare2_R()` 才是左轮。Motor 层已经包好，调用 `Motor_L_Speed()` / `Motor_R_Speed()` 不用管这个。

## 蓝牙指令

发送单个字符即可控制，`main.c` 中按 `switch(RxData)` 分派：

| 字符 | 动作 | 实现 |
|------|------|------|
| `f` | 前进 | `Motor_Speed(50)` |
| `d` | 后退 | `Motor_Speed(-50)` |
| `l` | 左转 | `Motor_Differential(30, 50)` |
| `r` | 右转 | `Motor_Differential(50, 30)` |
| `s` | 停车 | `Motor_Differential(0, 0)` |

## 循迹值对照

`Read_HCRT()` 把 PB1/PB0/PB10/PB11 四位拼成 `value`（白=1，黑=0），`Follow_car()` 的判断：

| value | 含义 | 动作 |
|-------|------|------|
| 9 | 居中压线 | 直行 `Motor_Speed(50)` |
| 14 / 13 / 12 | 偏出一侧 | `Motor_Differential(0, 50)` 左转修正 |
| 11 / 7 / 3 | 偏出另一侧 | `Motor_Differential(50, 0)` 右转修正 |
| 8 | 最外侧 | 原地旋转 `(-50, 50)` 600ms 后重采样 |
| 1 | 最外侧 | 原地旋转 `(50, -50)` 600ms 后重采样 |
| 0 / 15 | 全黑 / 全白 | `Motor_Stop(0)` 停车 |

## 工程结构

```
Hardware/    模块驱动：Motor / PWM / Servo / HCSOR04 / TCRT5000 / Follow / Serial / OLED / Control
Library/     STM32 标准外设库 3.5
Start/       启动文件 startup_stm32f10x_md.s、system_stm32f10x.c、CMSIS
System/      Delay（SysTick 延时）、sys.h
User/        main.c、stm32f10x_it.c、stm32f10x_conf.h
```

## 编译与烧录

1. Keil MDK5 打开 `project.uvprojx`
2. F7 编译，确认 `0 Error(s)` 且重新生成了 `.axf`
3. LOAD（ST-Link）烧录

> 烧录后没反应，先看编译窗口有没有 `Target not created` —— 链接失败时烧进去的还是上一次的固件。
> 电机不动但 OLED 正常，优先查 TB6612 的 VM 是否单独供电（ST-Link 的 3.3V 带不动电机）。

## 当前进度

- [x] 电机驱动与 PWM 调速
- [x] 蓝牙串口遥控（USART1 中断收字符）
- [x] 超声波测距驱动
- [x] 舵机 PWM 角度控制
- [x] 红外循迹采样与转向逻辑
- [ ] `main.c` 接入循迹 —— `Follow_car()` 目前没有被调用，`HCRT500_Init()` 也还是注释状态
- [ ] 避障启用 —— `Control.c` 已写好，但 `Get_Data()` 三次测距共约 1s，过程完全不控车，上车前需改为非阻塞
- [ ] 循迹阈值现场标定
- [ ] OLED 显示测距 / 状态（目前只调用了 `OLED_Init()`）

## 开发环境

- 芯片：STM32F103C8（Cortex-M3，72MHz）
- IDE：Keil uVision 5（MDK5）
- 标准库：STM32F10x Standard Peripheral Library 3.5
- 烧录器：ST-Link V2

## 说明

本仓库用于记录智能小车从点灯到整车的搭建过程，按模块逐步推进。

其他 STM32 学习案例见：[STM32 学习记录](https://github.com/AD609/STM32-)
