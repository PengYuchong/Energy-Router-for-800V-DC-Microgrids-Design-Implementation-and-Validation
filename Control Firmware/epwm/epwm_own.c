/*
 * epwm_own.c
 *本函数定义八个PWM信号：PWM1-8。PWM1和PWM4同相位，2、3，5、8，6、7分别通相位。原边和副边有相位差。上下管互补导通。
 *  Created on: 2023年7月4日
 *  New revised on:2023年12月11日
 *      Author: PYC
 */

#include "epwm_own.h"

//#define FALLDELAY 25
//#define RISEDELAY 25//上升沿下降沿设置
#define FALLDELAY 8
#define RISEDELAY 8//上升沿下降沿设置

volatile Uint16 duty=0;

void EPWM1_Init(Uint16 tbprd)
{
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0; // Disable TBCLK within the ePWM
    CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;  //Enable ePWM1 CLK
    EDIS;

    InitEPwm1Gpio();

//    EALLOW;
//    PieVectTable.EPWM5_INT = &epwm3_isr;
//    EDIS;

    // Setup Sync
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
    // Allow each timer to be sync'ed
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE; // enable phase
    EPwm1Regs.TBPHS.bit.TBPHS = 0;
    EPwm1Regs.TBCTR = 0x0000;                  // Clear counter
    EPwm1Regs.TBPRD = tbprd;
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // Count up
    EPwm1Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;
    EPwm1Regs.TBCTL.bit.CLKDIV=TB_DIV1;

    // Setup shadow register load on ZERO
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    // Set Compare values
    EPwm1Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm1Regs.CMPB.bit.CMPB = 0;    // Set Compare B value



    // Set actions
    EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;            // Set PWM1A on Zero
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;          // Clear PWM1A on event A, up count


    // Dead-band Settings
    EPwm1Regs.DBCTL.bit.OUT_MODE =DB_FULL_ENABLE;// ;    // enable Dead-band module
    EPwm1Regs.DBCTL.bit.POLSEL =DB_ACTV_HIC;//DB_ACTV_HIC;        // Active Hi complementary
    EPwm1Regs.DBFED.bit.DBFED = 12;                          // FED =0.125 TBCLKs initially
    EPwm1Regs.DBRED.bit.DBRED = 12;                          // RED =0.125 TBCLKs initially

//    EPwm3Regs.ETSEL.bit.INTSEL = ET_CTRU_CMPA;     // Select INT on CMPA event
//    EPwm3Regs.ETSEL.bit.INTEN = 1;  // Enable INT
//    EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
    EPwm1Regs.TZSEL.all=0;
    EPwm1Regs.TZCTL.all=0;
    EPwm1Regs.TZEINT.all=0;
    EPwm1Regs.TZFLG.all=0;
    EPwm1Regs.TZCLR.all=0;
    EPwm1Regs.TZFRC.all=0;
    EPwm1Regs.ETSEL.all=0;            // // Disable Interrupt
    EPwm1Regs.ETCLR.all=0;
    EPwm1Regs.ETFRC.all=0;
    EPwm1Regs.PCCTL.all=0;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}

void EPwm1A_SetCompare(Uint16 val)


{
    EPwm1Regs.CMPA.bit.CMPA = val;  //设置占空比

}
void EPwm12_SetPhaseShift(Uint16 val)
{
    EPwm1Regs.TBPHS.bit.TBPHS = val;
    EPwm2Regs.TBPHS.bit.TBPHS = val;
}

void EPWM2_Init(Uint16 tbprd)
{
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0; // Disable TBCLK within the ePWM
    CpuSysRegs.PCLKCR2.bit.EPWM2 = 1;  //Enable ePWM1 CLK
    EDIS;

    InitEPwm2Gpio();

//    EALLOW;
//    PieVectTable.EPWM5_INT = &epwm3_isr;
//    EDIS;

    // Setup Sync
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    // Allow each timer to be sync'ed
    EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE; // enable phase
    EPwm2Regs.TBPHS.bit.TBPHS = 0;
    EPwm2Regs.TBCTR = 0x0000;                  // Clear counter
    EPwm2Regs.TBPRD = tbprd;
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // Count up
    EPwm2Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;
    EPwm2Regs.TBCTL.bit.CLKDIV=TB_DIV1;

    // Setup shadow register load on ZERO
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    // Set Compare values
    EPwm2Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm2Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Set actions
    EPwm2Regs.AQCTLA.bit.ZRO = AQ_CLEAR;            // Set PWM1A on Zero
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;          // Clear PWM1A on event A, up count

    // Dead-band Settings
    EPwm2Regs.DBCTL.bit.OUT_MODE =DB_FULL_ENABLE;// ;    // enable Dead-band module
    EPwm2Regs.DBCTL.bit.POLSEL =DB_ACTV_HIC;//DB_ACTV_HIC;        // Active Hi complementary
    EPwm2Regs.DBFED.bit.DBFED = 12;                          // FED =0.125 TBCLKs initially
    EPwm2Regs.DBRED.bit.DBRED = 12;                          // RED =0.125 TBCLKs initially

//    EPwm3Regs.ETSEL.bit.INTSEL = ET_CTRU_CMPA;     // Select INT on CMPA event
//    EPwm3Regs.ETSEL.bit.INTEN = 1;  // Enable INT
//    EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
    EPwm2Regs.TZSEL.all=0;
    EPwm2Regs.TZCTL.all=0;
    EPwm2Regs.TZEINT.all=0;
    EPwm2Regs.TZFLG.all=0;
    EPwm2Regs.TZCLR.all=0;
    EPwm2Regs.TZFRC.all=0;
    EPwm2Regs.ETSEL.all=0;            // // Disable Interrupt
    EPwm2Regs.ETCLR.all=0;
    EPwm2Regs.ETFRC.all=0;
    EPwm2Regs.PCCTL.all=0;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}

void EPwm2A_SetCompare(Uint16 val)
{
    EPwm2Regs.CMPA.bit.CMPA = val;  //设置占空比
}

void EPWM3_Init(Uint16 tbprd)
{
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0; // Disable TBCLK within the ePWM
    CpuSysRegs.PCLKCR2.bit.EPWM3 = 1;  //Enable ePWM1 CLK
    EDIS;

    InitEPwm3Gpio();

//    EALLOW;
//    PieVectTable.EPWM5_INT = &epwm3_isr;
//    EDIS;

    // Setup Sync
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    // Allow each timer to be sync'ed
    EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE; // enable phase
    EPwm3Regs.TBPHS.bit.TBPHS = 0;
    EPwm3Regs.TBCTR = 0x0000;                  // Clear counter
    EPwm3Regs.TBPRD = tbprd;
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // Count up
    EPwm3Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;
    EPwm3Regs.TBCTL.bit.CLKDIV=TB_DIV1;

    // Setup shadow register load on ZERO
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    // Set Compare values
    EPwm3Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm3Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Set actions
    EPwm3Regs.AQCTLA.bit.ZRO = AQ_SET;            // Set PWM1A on Zero
    EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;          // Clear PWM1A on event A, up count

    // Dead-band Settings
    EPwm3Regs.DBCTL.bit.OUT_MODE =DB_FULL_ENABLE;// ;    // enable Dead-band module
    EPwm3Regs.DBCTL.bit.POLSEL =DB_ACTV_HIC;//DB_ACTV_HIC;        // Active Hi complementary
    EPwm3Regs.DBFED.bit.DBFED = 12;                          // FED =0.125 TBCLKs initially
    EPwm3Regs.DBRED.bit.DBRED = 12;                          // RED =0.125 TBCLKs initially

//    EPwm3Regs.ETSEL.bit.INTSEL = ET_CTRU_CMPA;     // Select INT on CMPA event
//    EPwm3Regs.ETSEL.bit.INTEN = 1;  // Enable INT
//    EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
    EPwm3Regs.TZSEL.all=0;
    EPwm3Regs.TZCTL.all=0;
    EPwm3Regs.TZEINT.all=0;
    EPwm3Regs.TZFLG.all=0;
    EPwm3Regs.TZCLR.all=0;
    EPwm3Regs.TZFRC.all=0;
    EPwm3Regs.ETSEL.all=0;            // // Disable Interrupt
    EPwm3Regs.ETCLR.all=0;
    EPwm3Regs.ETFRC.all=0;
    EPwm3Regs.PCCTL.all=0;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

//    IER |= M_INT3;
//
//    // Enable EPWM INTn in the PIE: Group 3 interrupt 1-3
//    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
//
//    // Enable global Interrupts and higher priority real-time debug events:
//    EINT;   // Enable Global interrupt INTM
//    ERTM;   // Enable Global realtime interrupt DBGM
}

void EPwm3A_SetCompare(Uint16 val)
{

    EPwm3Regs.CMPA.bit.CMPA = val;  //设置占空比
}


void EPwm34_SetPhaseShift(Uint16 val)
{
    EPwm3Regs.TBPHS.bit.TBPHS = val;
    EPwm4Regs.TBPHS.bit.TBPHS = val;
}

void EPWM4_Init(Uint16 tbprd)
{
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0; // Disable TBCLK within the ePWM
    CpuSysRegs.PCLKCR2.bit.EPWM4 = 1;  //Enable ePWM1 CLK
    EDIS;

    InitEPwm4Gpio();

//    EALLOW;
//    PieVectTable.EPWM5_INT = &epwm4_isr;
//    EDIS;

    // Setup Sync
    EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    // Allow each timer to be sync'ed
    EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE; // enable phase
    EPwm4Regs.TBPHS.bit.TBPHS = 0;
    EPwm4Regs.TBCTR = 0x0000;                  // Clear counter
    EPwm4Regs.TBPRD = tbprd;
    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // Count up
    EPwm4Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;
    EPwm4Regs.TBCTL.bit.CLKDIV=TB_DIV1;

    // Setup shadow register load on ZERO
    EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    // Set Compare values
    EPwm4Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm4Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Set actions
    EPwm4Regs.AQCTLA.bit.ZRO = AQ_CLEAR;            // Set PWM1A on Zero
    EPwm4Regs.AQCTLA.bit.CAU = AQ_SET;          // Clear PWM1A on event A, up count

    // Dead-band Settings
    EPwm4Regs.DBCTL.bit.OUT_MODE =DB_FULL_ENABLE;// ;    // enable Dead-band module
    EPwm4Regs.DBCTL.bit.POLSEL =DB_ACTV_HIC;//DB_ACTV_HIC;        // Active Hi complementary
    EPwm4Regs.DBFED.bit.DBFED = FALLDELAY;                          // FED =0.125 TBCLKs initially
    EPwm4Regs.DBRED.bit.DBRED = RISEDELAY;                          // RED =0.125 TBCLKs initially

//    EPwm4Regs.ETSEL.bit.INTSEL = ET_CTRU_CMPA;     // Select INT on CMPA event
//    EPwm4Regs.ETSEL.bit.INTEN = 1;  // Enable INT
//    EPwm4Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
    EPwm4Regs.TZSEL.all=0;
    EPwm4Regs.TZCTL.all=0;
    EPwm4Regs.TZEINT.all=0;
    EPwm4Regs.TZFLG.all=0;
    EPwm4Regs.TZCLR.all=0;
    EPwm4Regs.TZFRC.all=0;
    EPwm4Regs.ETSEL.all=0;            // // Disable Interrupt
    EPwm4Regs.ETCLR.all=0;
    EPwm4Regs.ETFRC.all=0;
    EPwm4Regs.PCCTL.all=0;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

//    IER |= M_INT3;
//
//    // Enable EPWM INTn in the PIE: Group 3 interrupt 1-3
//    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
//
//    // Enable global Interrupts and higher priority real-time debug events:
//    EINT;   // Enable Global interrupt INTM
//    ERTM;   // Enable Global realtime interrupt DBGM
}

void EPwm4A_SetCompare(Uint16 val)
{
    EPwm4Regs.CMPA.bit.CMPA = val;  //设置占空比
}


void EPWM5_Init(Uint16 tbprd)
{
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0; // Disable TBCLK within the ePWM
    CpuSysRegs.PCLKCR2.bit.EPWM5 = 1;  //Enable ePWM1 CLK
    EDIS;

    InitEPwm5Gpio();

//    EALLOW;
//    PieVectTable.EPWM5_INT = &epwm5_isr;
//    EDIS;

    // Setup Sync
    EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    // Allow each timer to be sync'ed
    EPwm5Regs.TBCTL.bit.PHSEN = TB_ENABLE; // enable phase
    EPwm5Regs.TBPHS.bit.TBPHS = 0;
    EPwm5Regs.TBCTR = 0x0000;                  // Clear counter
    EPwm5Regs.TBPRD = tbprd;
    EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // Count up
    EPwm5Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;
    EPwm5Regs.TBCTL.bit.CLKDIV=TB_DIV1;

    // Setup shadow register load on ZERO
    EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    // Set Compare values
    EPwm5Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm5Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Set actions
    EPwm5Regs.AQCTLA.bit.ZRO = AQ_SET;            // Set PWM1A on Zero
    EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR;          // Clear PWM1A on event A, up count

    // Dead-band Settings
    EPwm5Regs.DBCTL.bit.OUT_MODE =DB_FULL_ENABLE;// ;    // enable Dead-band module
    EPwm5Regs.DBCTL.bit.POLSEL =DB_ACTV_HIC;//DB_ACTV_HIC;        // Active Hi complementary
    EPwm5Regs.DBFED.bit.DBFED = 12;                          // FED =0.125 TBCLKs initially
    EPwm5Regs.DBRED.bit.DBRED = 12;                          // RED =0.125 TBCLKs initially

//    EPwm5Regs.ETSEL.bit.INTSEL = ET_CTRU_CMPA;     // Select INT on CMPA event
//    EPwm5Regs.ETSEL.bit.INTEN = 1;  // Enable INT
//    EPwm5Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
    EPwm5Regs.TZSEL.all=0;
    EPwm5Regs.TZCTL.all=0;
    EPwm5Regs.TZEINT.all=0;
    EPwm5Regs.TZFLG.all=0;
    EPwm5Regs.TZCLR.all=0;
    EPwm5Regs.TZFRC.all=0;
    EPwm5Regs.ETSEL.all=0;            // // Disable Interrupt
    EPwm5Regs.ETFLG.all=0;
    EPwm5Regs.ETCLR.all=0;
    EPwm5Regs.ETFRC.all=0;
    EPwm5Regs.PCCTL.all=0;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

//    IER |= M_INT3;
//
//    // Enable EPWM INTn in the PIE: Group 3 interrupt 1-3
//    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
//
//    // Enable global Interrupts and higher priority real-time debug events:
//    EINT;   // Enable Global interrupt INTM
//    ERTM;   // Enable Global realtime interrupt DBGM
}

void EPwm5A_SetCompare(Uint16 val)
{
    EPwm5Regs.CMPA.bit.CMPA = val;  //设置占空比
}

void EPWM6_Init(Uint16 tbprd)
{
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0; // Disable TBCLK within the ePWM
    CpuSysRegs.PCLKCR2.bit.EPWM6 = 1;  //Enable ePWM1 CLK
    EDIS;

    InitEPwm6Gpio();

//    EALLOW;
//    PieVectTable.EPWM5_INT = &epwm5_isr;
//    EDIS;

    // Setup Sync
    EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    // Allow each timer to be sync'ed
    EPwm6Regs.TBCTL.bit.PHSEN = TB_ENABLE; // enable phase
    EPwm6Regs.TBPHS.bit.TBPHS = 0;
    EPwm6Regs.TBCTR = 0x0000;                  // Clear counter
    EPwm6Regs.TBPRD = tbprd;
    EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // Count up
    EPwm6Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;
    EPwm6Regs.TBCTL.bit.CLKDIV=TB_DIV1;

    // Setup shadow register load on ZERO
    EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    // Set Compare values
    EPwm6Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm6Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Set actions
    EPwm6Regs.AQCTLA.bit.ZRO = AQ_CLEAR;            // Set PWM1A on Zero
    EPwm6Regs.AQCTLA.bit.CAU = AQ_SET;          // Clear PWM1A on event A, up count

    // Dead-band Settings
    EPwm6Regs.DBCTL.bit.OUT_MODE =DB_FULL_ENABLE;// ;    // enable Dead-band module
    EPwm6Regs.DBCTL.bit.POLSEL =DB_ACTV_HIC;//DB_ACTV_HIC;        // Active Hi complementary
    EPwm6Regs.DBFED.bit.DBFED = 12;                          // FED =0.125 TBCLKs initially
    EPwm6Regs.DBRED.bit.DBRED = 12;                          // RED =0.125 TBCLKs initially

//    EPwm5Regs.ETSEL.bit.INTSEL = ET_CTRU_CMPA;     // Select INT on CMPA event
//    EPwm5Regs.ETSEL.bit.INTEN = 1;  // Enable INT
//    EPwm5Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
    EPwm6Regs.TZSEL.all=0;
    EPwm6Regs.TZCTL.all=0;
    EPwm6Regs.TZEINT.all=0;
    EPwm6Regs.TZFLG.all=0;
    EPwm6Regs.TZCLR.all=0;
    EPwm6Regs.TZFRC.all=0;
    EPwm6Regs.ETSEL.all=0;            // // Disable Interrupt
    EPwm6Regs.ETFLG.all=0;
    EPwm6Regs.ETCLR.all=0;
    EPwm6Regs.ETFRC.all=0;
    EPwm6Regs.PCCTL.all=0;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

//    IER |= M_INT3;
//
//    // Enable EPWM INTn in the PIE: Group 3 interrupt 1-3
//    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
//
//    // Enable global Interrupts and higher priority real-time debug events:
//    EINT;   // Enable Global interrupt INTM
//    ERTM;   // Enable Global realtime interrupt DBGM
}

void EPwm6A_SetCompare(Uint16 val)
{
    EPwm6Regs.CMPA.bit.CMPA = val;  //设置占空比
}

void EPwm56_SetPhaseShift(Uint16 val)
{
    EPwm5Regs.TBPHS.bit.TBPHS = val;
    EPwm6Regs.TBPHS.bit.TBPHS = val;
}

void EPWM7_Init(Uint16 tbprd)
{
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0; // Disable TBCLK within the ePWM
    CpuSysRegs.PCLKCR2.bit.EPWM7 = 1;  //Enable ePWM1 CLK
    EDIS;

    InitEPwm7Gpio();

//    EALLOW;
//    PieVectTable.EPWM5_INT = &epwm7_isr;
//    EDIS;

    // Setup Sync
    EPwm7Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
    // Allow each timer to be sync'ed
    EPwm7Regs.TBCTL.bit.PHSEN = TB_ENABLE; // enable phase
    EPwm7Regs.TBPHS.bit.TBPHS = 0;
    EPwm7Regs.TBCTR = 0x0000;                  // Clear counter
    EPwm7Regs.TBPRD = tbprd;
    EPwm7Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // Count up
    EPwm7Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;
    EPwm7Regs.TBCTL.bit.CLKDIV=TB_DIV1;

    // Setup shadow register load on ZERO
    EPwm7Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm7Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm7Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm7Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    // Set Compare values
    EPwm7Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm7Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Set actions
    EPwm7Regs.AQCTLA.bit.ZRO = AQ_SET;            // Set PWM1A on Zero
    EPwm7Regs.AQCTLA.bit.CAU = AQ_CLEAR;          // Clear PWM1A on event A, up count

    // Dead-band Settings
    EPwm7Regs.DBCTL.bit.OUT_MODE =DB_FULL_ENABLE;// ;    // enable Dead-band module
    EPwm7Regs.DBCTL.bit.POLSEL =DB_ACTV_HIC;//DB_ACTV_HIC;        // Active Hi complementary
    EPwm7Regs.DBFED.bit.DBFED = FALLDELAY;                          // FED =0.125 TBCLKs initially
    EPwm7Regs.DBRED.bit.DBRED = RISEDELAY;                          // RED =0.125 TBCLKs initially

//    EPwm7Regs.ETSEL.bit.INTSEL = ET_CTRU_CMPA;     // Select INT on CMPA event
//    EPwm7Regs.ETSEL.bit.INTEN = 1;  // Enable INT
//    EPwm7Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
    EPwm7Regs.TZSEL.all=0;
    EPwm7Regs.TZCTL.all=0;
    EPwm7Regs.TZEINT.all=0;
    EPwm7Regs.TZFLG.all=0;
    EPwm7Regs.TZCLR.all=0;
    EPwm7Regs.TZFRC.all=0;
    EPwm7Regs.ETSEL.all=0;            // // Disable Interrupt
    EPwm7Regs.ETFLG.all=0;
    EPwm7Regs.ETCLR.all=0;
    EPwm7Regs.ETFRC.all=0;
    EPwm7Regs.PCCTL.all=0;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

//    IER |= M_INT3;
//
//    // Enable EPWM INTn in the PIE: Group 3 interrupt 1-3
//    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
//
//    // Enable global Interrupts and higher priority real-time debug events:
//    EINT;   // Enable Global interrupt INTM
//    ERTM;   // Enable Global realtime interrupt DBGM
}

void EPwm7A_SetCompare(Uint16 val)
{
    EPwm7Regs.CMPA.bit.CMPA = val;  //设置占空比
}

void EPWM8_Init(Uint16 tbprd)
{
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0; // Disable TBCLK within the ePWM
    CpuSysRegs.PCLKCR2.bit.EPWM8 = 1;  //Enable ePWM1 CLK
    EDIS;

    InitEPwm8Gpio();

//    EALLOW;
//    PieVectTable.EPWM5_INT = &epwm7_isr;
//    EDIS;

    // Setup Sync
    EPwm8Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
    // Allow each timer to be sync'ed
    EPwm8Regs.TBCTL.bit.PHSEN = TB_ENABLE; // enable phase
    EPwm8Regs.TBPHS.bit.TBPHS = 0;
    EPwm8Regs.TBCTR = 0x0000;                  // Clear counter
    EPwm8Regs.TBPRD = tbprd;
    EPwm8Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // Count up
    EPwm8Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;
    EPwm8Regs.TBCTL.bit.CLKDIV=TB_DIV1;

    // Setup shadow register load on ZERO
    EPwm8Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm8Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm8Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm8Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    // Set Compare values
    EPwm8Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm8Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Set actions
    EPwm8Regs.AQCTLA.bit.ZRO = AQ_CLEAR;            // Set PWM1A on Zero
    EPwm8Regs.AQCTLA.bit.CAU = AQ_SET;          // Clear PWM1A on event A, up count

    // Dead-band Settings
    EPwm8Regs.DBCTL.bit.OUT_MODE =DB_FULL_ENABLE;// ;    // enable Dead-band module
    EPwm8Regs.DBCTL.bit.POLSEL =DB_ACTV_HIC;//DB_ACTV_HIC;        // Active Hi complementary
    EPwm8Regs.DBFED.bit.DBFED = FALLDELAY;                          // FED =0.125 TBCLKs initially
    EPwm8Regs.DBRED.bit.DBRED = RISEDELAY;                          // RED =0.125 TBCLKs initially

//    EPwm8Regs.ETSEL.bit.INTSEL = ET_CTRU_CMPA;     // Select INT on CMPA event
//    EPwm8Regs.ETSEL.bit.INTEN = 1;  // Enable INT
//    EPwm8Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
    EPwm8Regs.TZSEL.all=0;
    EPwm8Regs.TZCTL.all=0;
    EPwm8Regs.TZEINT.all=0;
    EPwm8Regs.TZFLG.all=0;
    EPwm8Regs.TZCLR.all=0;
    EPwm8Regs.TZFRC.all=0;
    EPwm8Regs.ETSEL.all=0;            // // Disable Interrupt
    EPwm8Regs.ETFLG.all=0;
    EPwm8Regs.ETCLR.all=0;
    EPwm8Regs.ETFRC.all=0;
    EPwm8Regs.PCCTL.all=0;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

//    IER |= M_INT3;
//
//    // Enable EPWM INTn in the PIE: Group 3 interrupt 1-3
//    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
//
//    // Enable global Interrupts and higher priority real-time debug events:
//    EINT;   // Enable Global interrupt INTM
//    ERTM;   // Enable Global realtime interrupt DBGM
}

void EPwm8A_SetCompare(Uint16 val)
{
    EPwm8Regs.CMPA.bit.CMPA = val;  //设置占空比
}

void EPwm78_SetPhaseShift(Uint16 val)
{
    EPwm7Regs.TBPHS.bit.TBPHS = val;
    //EPwm8Regs.TBPHS.bit.TBPHS = val-100;
    EPwm8Regs.TBPHS.bit.TBPHS = val;
}
