#include "config.h"						//configuration words
#include "gpio.h"                           //we use gpio functions
#include "delay.h"                          //we use software delays
#include "sPWM.h"							//we use software PWM

//hardware configuration
#define PWM2_PORT		GPIO
#define PWM2_DDR		TRISIO
#define PWM2			(1<<2)				//dual slope pwm

#define PWM_PORT		GPIO
#define PWM_DDR			TRISIO
#define PWM_P			(1<<0)				//pwm positive polarity
#define PWM_N			(1<<1)				//pwm negative polarity

#define QD_PORT			GPIO
#define QD_DDR			TRISIO
#define QD_A			(1<<4)				//quadruture ch a
#define QD_B			(1<<5)				//quadruture ch b
//end hardware configuration

//global defines

//global variables
sPWM8_TypeDef sPWM0;						//software pwm
char PWM2_DIR=1;							//dual slope pwm, 1=up, 0=down

int main(void) {
	
	mcu_init();							    //initialize the mcu
		
	//initialize the pins
	IO_SET(PWM_PORT, PWM_P); IO_OUT(PWM_DDR, PWM_P); 
	IO_CLR(PWM_PORT, PWM_N); IO_OUT(PWM_DDR, PWM_N); 
	IO_OUT(QD_DDR,  QD_A | QD_B);			//qda+b as output
	IO_OUT(PWM2_DDR, PWM2);				//dual slope pwm output
	
	//initialize the software pwm
	sPWM_init(sPWM0);
	sPWM_setoc0(sPWM0, 0xff/4);				//oc0 duty cycle to 25%
	sPWM_setoc1(sPWM0, 1);
	sPWM_setoc2(sPWM0, 0);					//oc2 match point at 0
	sPWM_setoc3(sPWM0, 0xff/2);				//oc3 match point 180 degrees off oc2 match point -> period if 0xff
	while (1) {
		sPWM_inc(sPWM0);					//increment spwm0 counter
		
		//for dual slope pwm
		if (sPWM_ovf(sPWM0)) {				//1 full period has finished
			sPWM0.OC1 +=1;					//increment duty cycle
			if (sPWM0.OC1 == 0) PWM2_DIR += 1;	//change directions
		}	
		if (PWM2_DIR & (1<<0)) {if (sPWM0.CNT > sPWM0.OC1) IO_SET(PWM2_PORT, PWM2); else IO_CLR(PWM2_PORT, PWM2);}	//up counting
		else {if (sPWM0.CNT < sPWM0.OC1) IO_SET(PWM2_PORT, PWM2); else IO_CLR(PWM2_PORT, PWM2);}					//downcounting
		
			
		//for complimentary pwm outputs
		//if (sPWM_ovf(sPWM0)) {IO_SET(PWM_PORT, PWM_P); IO_CLR(PWM_PORT, PWM_N);}
		//if (sPWM_match0(sPWM0)) {IO_CLR(PWM_PORT, PWM_P); IO_SET(PWM_PORT, PWM_N);}
		if (sPWM_ovf(sPWM0) || sPWM_match0(sPWM0)) IO_FLP(PWM_PORT, PWM_P | PWM_N);
		
		//for quadrature outputs
		if (sPWM_match2(sPWM0)) IO_FLP(QD_PORT, QD_A);
		if (sPWM_match3(sPWM0)) IO_FLP(QD_PORT, QD_B);
	}
}

