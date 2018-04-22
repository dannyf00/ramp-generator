#ifndef _SPWM_H
#define _SPWM_H

#include <stdint.h>

//software PWM implementation
//minimalist framework

//hardware configuration
//end hardware configuration

//global defines
//software pwm, 8-bit, upcounter. bottom at 0, top at 0xff
typedef struct {
	uint8_t CNT;							//counter
	uint8_t OC0;							//duty cycle / output compare
	uint8_t OC1;							//duty cycle / output compare
	uint8_t OC2;							//duty cycle / output compare
	uint8_t OC3;							//duty cycle / output compare
	//additional features can be implemented as well
} sPWM8_TypeDef;
	
//software pwm, 16-bit, upcounter. bottom at 0, top at 0xffff
typedef struct {
	uint16_t CNT;							//counter
	uint16_t OC0;							//duty cycle / output compare
	uint16_t OC1;							//duty cycle / output compare
	uint16_t OC2;							//duty cycle / output compare
	uint16_t OC3;							//duty cycle / output compare
	//additional features can be implemented as well
} sPWM16_TypeDef;
	
//global variables

//macros to operate on a software pwm module
#define sPWM_setcnt(pwm, cnt) 	pwm.CNT = (cnt)			//set counter
#define sPWM_getcnt(pwm) 		(pwm.CNT)				//reset counter
#define sPWM_setoc0(pwm, oc)	pwm.OC0  = (oc)			//set pwm oc match point
#define sPWM_setoc1(pwm, oc)	pwm.OC1  = (oc)			//set pwm oc match point
#define sPWM_setoc2(pwm, oc)	pwm.OC2  = (oc)			//set pwm oc match point
#define sPWM_setoc3(pwm, oc)	pwm.OC3  = (oc)			//set pwm oc match point
#define sPWM_getoc0(pwm)		(pwm.OC0)				//get pwm oc match point
#define sPWM_getoc1(pwm)		(pwm.OC1)				//get pwm oc match point
#define sPWM_getoc2(pwm)		(pwm.OC2)				//get pwm oc match point
#define sPWM_getoc3(pwm)		(pwm.OC3)				//get pwm oc match point
#define sPWM_match0(pwm)		(pwm.CNT==pwm.OC0)	//test for CNT = OC0
#define sPWM_match1(pwm)		(pwm.CNT==pwm.OC1)	//test for CNT = OC1
#define sPWM_match2(pwm)		(pwm.CNT==pwm.OC2)	//test for CNT = OC2
#define sPWM_match3(pwm)		(pwm.CNT==pwm.OC3)	//test for CNT = OC3
#define sPWM_init(pwm)			pwm.CNT = pwm.OC0 = pwm.OC1 = pwm.OC2 = pwm.OC3 = 0	//reset the pwm
#define sPWM_inc(pwm)			pwm.CNT+= 1				//increment the pwm counter
#define sPWM_ovf(pwm)			(pwm.CNT==0)			//test for overflow: CNT -> 0

#endif
