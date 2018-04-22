#include "config.h"						//configuration words
#include "gpio.h"                           //we use gpio functions
#include "delay.h"                          //we use software delays

//hardware configuration
#define RAMP_PORT		GPIO
#define RAMP_DDR		TRISIO
#define RAMP			(1<<0)				//ramp output / input: needs a ST pin
//#define RAMP_DISC		(1<<2)
#define RAMP_DLY		10
//end hardware configuration

//global defines

int main(void) {
	char ramp_dir=+1;
		
	mcu_init();							    //initialize the mcu
	IO_SET(RAMP_PORT, RAMP); IO_OUT(RAMP_DDR, RAMP);	//start charging up the capacitor
	//IO_CLR(RAMP_PORT, RAMP_DISC); IO_IN(RAMP_DDR, RAMP_DISC);
	
	while (1) {
		if (IO_GET(RAMP_PORT, RAMP)) IO_CLR(RAMP_PORT, RAMP);	//discharge the capacitor
		else IO_SET(RAMP_PORT, RAMP);							//charge the capacitor
		delay_ms(RAMP_DLY);					//waste sometime
	}
}
