#ifndef __HCRT_H
#define __HCRT_H

void    HCRT500_Init(void);
uint8_t Read_HCRT(void);        /* 原始读数，bit0=PB1 ... bit3=PB11，白=1（居中时=9） */
uint8_t Trace_ReadMask(void);   /* 循迹掩码，bit3=最左 ... bit0=最右，压黑线=1（居中时=6） */

#endif
