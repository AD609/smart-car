# 蓝牙循迹避障智能小车（STM32F103C8T6）

基于 STM32F103C8T6 + STM32 标准外设库（SPL）的智能小车，实现超声波测距、红外循迹、舵机转向与 OLED 显示。

## 功能特性

- **HC-SR04 超声波测距**：TIM4 更新中断计数法（0.1ms 心跳），距离 = 计数 × 1.7cm，OLED 实时显示
- **TCRT5000 红外循迹**：传感器采样 + Follow_car 转向控制
- **舵机 PWM 控制**：TIM2 50Hz 输出，0.5~2.5ms 脉宽映射 0~180°
- **TB6612 电机驱动**：TIM3 PWM 调速 + 方向引脚控制
- **OLED 显示**：0.96 寸 I2C 屏（SSD1306），PA11/PA12

## 硬件清单

| 器件 | 型号 | 说明 |
|------|------|------|
| 主控板 | STM32F103C8T6 最小系统板 | 主频 72MHz |
| 扩展板 | 智能小车扩展板 | 集成各模块接口与电源 |
| 超声波 | HC-SR04 | 测距 2cm ~ 400cm |
| 循迹 | TCRT5000 四路模块 | 红外反射式 |
| 舵机 | SG90 等 | 50Hz 控制信号 |
| 电机驱动 | TB6612 | 双 H 桥 |
| 显示 | 0.96 寸 OLED（I2C） | SSD1306 |
| 烧录 | ST-Link V2 | SWD 接口 |

## 引脚分配

| 模块 | 引脚 |
|------|------|
| HC-SR04 | Trig = PA4，Echo = PA5 |
| OLED | SCL = PA11，SDA = PA12 |
| 舵机 | PA0（TIM2_CH1） |
| 左电机 | PWMA = PA7，IN = PB5 / PB6 |
| 右电机 | PWMB = PA6，IN = PB7 / PB8 |
| 四路循迹 | PB0 / PB1 / PB10 / PB11 |
| 蓝牙（预留） | USART1：PA9 / PA10 |
| 供电 | 电池 7~12V → 开关 → 5V/5A 稳压 |

## 目录结构

```
Hardware/    各模块驱动：HCSOR04 / TCRT5000 / Follow / Motor / PWM / Servo / OLED / Key / LED
Library/     STM32 标准外设库 3.5
Start/       启动文件与系统文件（system_stm32f10x.c）
System/      Delay 延时、sys
User/        main.c 主程序、stm32f10x_it.c 中断文件
```

## 编译与烧录

1. 用 Keil MDK5 打开 `project.uvprojx`
2. F7 编译，LOAD 烧录（ST-Link）
3. OLED 不亮时先确认接线是 **PA11 / PA12**（不是 PB8/PB9）

## 功能说明

### 超声波测距（HCSOR04.c）

```
触发 45µs → TIM4 以 0.1ms 心跳数 Echo 高电平 → 距离 = Time × 1.7cm
超 4m 无回波 → 返回 0（"无障碍"语义）
```

精度说明：0.1ms 心跳的量化误差 ±1.7cm，对避障足够；曾试验 10µs 心跳（±0.17cm）在面包板可用、整车失效，驱动参数需随硬件环境实测。

### 循迹（TCRT5000.c + Follow.c）

`Read_HCRT()` 采样循迹值 → `Follow_car()` 按值转向：0 停车 / 10 直行 / 8 左偏右修 / 2 右偏左修

### 避障（开发中，逻辑保留在 main.c 注释）

超声波 ≤15cm 停车 → 舵机转向测左/右 → 向空侧转向（待启用）

## 已知问题 / 待办

- [ ] 蓝牙 JDY-31 模块接入（USART1 引脚已预留）
- [ ] 避障逻辑启用（当前 main.c 中为注释状态）
- [ ] 循迹阈值需现场标定
- [ ] Control.c 控制层整理

## 版本历史

| 提交 | 内容 |
|------|------|
| `fa56eb1`（tag: car-hcsr04-v1） | 超声波测距驱动 + OLED 适配 |
| `14fcff9` | TCRT5000 循迹 + Follow_car 控制 |
| `f41d9f3` | 仓库忽略规则整理 |

## 学习笔记

STM32 学习记录见 GitHub 主页：https://github.com/AD609
