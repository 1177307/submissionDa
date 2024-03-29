#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

uint8_t ui8PinData=2;
/*
 * 2 = red
 * 4 = blue
 * 8 = green
 * */

int main(void)
{
    int clock_spd = 0;
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	clock_spd = SysCtlClockGet(); //40Mhz
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	while(1)
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, ui8PinData);
		SysCtlDelay(10000000);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);
		SysCtlDelay(10000000);
		//if(ui8PinData==8) {ui8PinData=2;} else {ui8PinData=ui8PinData*2;}
		if(ui8PinData==2) {ui8PinData=8;} //R -> G
		else if(ui8PinData==8) {ui8PinData=4;} //G -> B
		else if(ui8PinData==4) {ui8PinData=10;}//B -> RG
		else if(ui8PinData==10) {ui8PinData=6;}//RG-> RB
		else if(ui8PinData==6) {ui8PinData=12;}//RB-> GB
		else if(ui8PinData==12) {ui8PinData=16;}//GB-> RGB
		else if(ui8PinData==16) {ui8PinData=2;}//RGB-> R
	}
}


