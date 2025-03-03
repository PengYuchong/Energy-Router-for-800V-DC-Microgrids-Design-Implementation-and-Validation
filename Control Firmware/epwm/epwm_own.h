/*
 * epwm_own.h
 *
 *  Created on: 2023Äê7ÔÂ4ÈÕ
 *      Author: PYC
 *
 */

#ifndef EPWM_OWN_H_
#define EPWM_OWN_H_

#include "F28x_Project.h"

#define FIRST_CYCLE_FLAG 0
#define SECOND_CYCLE_FLAG 1

#define Ts 1000

//#define FIRST_DUTY 500
//#define SECOND_DUTY 1500

//extern volatile Uint16 duty;

void EPWM1_Init(Uint16 tbprd);
void EPwm1A_SetCompare(Uint16 val);
void EPWM2_Init(Uint16 tbprd);
void EPwm2A_SetCompare(Uint16 val);
//void EPwm12_SetDuty(Uint16 val);
void EPwm12_SetPhaseShift(Uint16 val);

void EPWM3_Init(Uint16 tbprd);
void EPwm3A_SetCompare(Uint16 val);
void EPWM4_Init(Uint16 tbprd);
void EPwm4A_SetCompare(Uint16 val);
void EPwm34_SetPhaseShift(Uint16 val);

void EPWM5_Init(Uint16 tbprd);
void EPwm5A_SetCompare(Uint16 val);
void EPWM6_Init(Uint16 tbprd);
void EPwm6A_SetCompare(Uint16 val);
void EPwm56_SetPhaseShift(Uint16 val);

void EPWM7_Init(Uint16 tbprd);
void EPwm7A_SetCompare(Uint16 val);
void EPWM8_Init(Uint16 tbprd);
void EPwm8A_SetCompare(Uint16 val);
void EPwm78_SetPhaseShift(Uint16 val);

#endif /* APP_EPWM_EPWM_OWN_H_ */
