#include "TM4C123GH6PM.h"
#include <math.h>
#define SYSCTL_RCGCGPIO_R *((volatile unsigned long *)0x400FE608)
#define CPAC_R *((volatile unsigned long *)0xE000ED88)

// Peripheral clock enabling for timer and GPIO
#define SYS_CLOCK_FREQUENCY 16000000

void SystemInit()
{
    CPAC_R |= (0xF << 20);
}

/* Generates 50HZ and variable duty cycle on PF2 pin of TM4C123 Tiva C Launchpad */
/* PWM1 module and PWM generator 3 of PWM1 module is used. Hence PWM channel*/

void init_pwm1()
{
	/* Clock setting for PWM and GPIO PORT */
		SYSCTL->RCGCPWM |= 2;       /* Enable clock to PWM1 module */
		SYSCTL->RCGCGPIO |= 0x20;  	/* Enable system clock to PORTF */
		SYSCTL->RCC |= (1<<20);    	/* Enable System Clock Divisor function  */
		SYSCTL->RCC |= 0x000E0000; 	/* Use pre-divider valur of 64 and after that feed clock to PWM1 module*/

		 /* Setting of PF2 pin for M1PWM6 channel output pin */
		GPIOF->AFSEL |= (1<<2);  		/* PF2 sets a alternate function */
		GPIOF->PCTL &= ~0x00000F00; /*set PF2 as output pin */
		GPIOF->PCTL |= 0x00000500; 	/* make PF2 PWM output pin */
		GPIOF->DEN |= (1<<2);      	/* set PF2 as a digital pin */
				
		PWM1->_3_CTL &= ~(1<<0);   	/* Disable Generator 3 counter */
		PWM1->_3_CTL &= ~(1<<1);   	/* select down count mode of counter 3*/
		PWM1->_3_GENA = 0x0000008C; /* Set PWM output when counter reloaded and clear when matches PWMCMPA */
		PWM1->_3_LOAD = 5000;     	/* set load value for 50 Mhz 16MHz/64 = 250kHz and (250KHz/5000) */
		PWM1->_3_CMPA = 4999;     	/* set duty cyle to to minumum value*/
		PWM1->_3_CTL = 1;           /* Enable Generator 3 counter */
		PWM1->ENABLE |= 0x40;      	/* Enable PWM1 channel 6 output */
}

void init_pwm2()
{
	/* Clock setting for PWM and GPIO PORT */
		SYSCTL->RCGCPWM |= 1;       /* Enable clock to PWM0 module */
		SYSCTL->RCGCGPIO |= 0x04;  	/* Enable system clock to PORTC */
		SYSCTL->RCC |= (1<<20);    	/* Enable System Clock Divisor function  */
	  SYSCTL->RCC |= 0x000E0000; 	/* Use pre-divider valur of 64 and after that feed clock to PWM1 module*/

		 /* Setting of PF2 pin for M1PWM6 channel output pin */
		GPIOC->AFSEL |= (1<<4);  		/* PC4 sets a alternate function */
		GPIOC->PCTL &= ~0x000F0000; /*set PC4 as output pin */
		GPIOC->PCTL |= 0x00040000; 	/* make PC4 PWM output pin */
		GPIOC->DEN |= (1<<4);      	/* set PC4 as a digital pin */
				
		PWM0->_3_CTL &= ~(1<<0);   	/* Disable Generator 3 counter */
		PWM0->_3_CTL |= (1<<1);   	/* select down count mode of counter 3*/
		PWM0->_3_GENA = 0x0000008C;	/* Set PWM output when counter reloaded and clear when matches PWMCMPA */
		PWM0->_3_LOAD = 500;     	/* set load value for 500Hz 16MHz/64 = 250kHz and (250KHz/500) */
		PWM0->_3_CMPA = 499;     	/* set duty cyle to to minumum value*/
		PWM0->_3_CTL = 1;           /* Enable Generator 3 counter */
		PWM0->ENABLE |= 0x40;      	/* Enable PWM1 channel 6 output */
}

void SetSpeedB( float speed )
{
	PWM1->_3_CMPA = (1-speed)*500;
}

void SetSpeedA( float speed )
{
	PWM0->_3_CMPA = (1-speed)*500;
}

void delay(int time_ms)
{
    int i, j;
    for(i = 0 ; i < time_ms; i++)
        for(j = 0; j < 3180; j++)
            {}  /* excute NOP for 1ms */
}

// Application main function
int main(void)
{
	
		int f = 50;
		double speed;
		float i;
		init_pwm1();
		delay(10);
		init_pwm2();

    while (1)
    {
				for (i=0;i,<=0.02;i+=0.001)
				{
					speed=(1+sin(2*3.141*50*i))*0.9/2;
					SetSpeedB(speed);
					delay(1);
				}
				SetSpeedB(33.33);
				SetSpeedA(33.33);
			
    }
}


(1+sin(2*pi*f*t))*0.9/2
