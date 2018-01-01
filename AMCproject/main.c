#include <lpc17xx.h>   
void forward();
void backward();
void left();
void right();
void stop();
void delay_ms();
void repeatAction(unsigned int,unsigned int[] );
#define LEFT_RIGHT_DELAY	1  //Delay is low for simulation purposes
#define STOP_DELAY	1    		 //Delay is low for simulation purposes
/* START OF MAIN FUNCTION */
int main() 
{
    SystemInit();                    //Clock and PLL configuration 
    LPC_PINCON->PINSEL2 = 0x000000;  //Configure the PORT1 Pins as GPIO;
		LPC_PINCON->PINSEL3 = 0x000000;  //Configure the PORT1 Pins as GPIO;
    LPC_GPIO1->FIODIR = 0xffffffff;  //Configure the PORT1 pins as OUTPUT;
		LPC_PINCON->PINSEL0 = 0x000000;  //Configure the PORT0 Pins as GPIO;
		LPC_PINCON->PINSEL1 = 0x000000;  //Configure the PORT0 Pins as GPIO;
		LPC_GPIO0->FIODIR = 0x00000000;  //Configure the PORT0 pins as INPUT;
//==========================================================================================================================================
	//FOR REPEAT ACTION
		LPC_PINCON->PINSEL4 = 0x000000;  //Configure the PORT2 Pins as GPIO;
		LPC_GPIO2->FIODIR0 = 0x00;  		 //Configure the PORT2 pins as INPUT;
		LPC_GPIO2->FIOPIN0 = 0x00;
		unsigned int rAction,switchStatus1,switchStatus2,switchStatus3,switchStatus4;
		unsigned int i = 0;
		unsigned int caseStateVar;
		unsigned int action[100] = {0};  //array to store movement
		while(1)
		{
			unsigned int curStateVar = 0;
			switchStatus1 = (LPC_GPIO0->FIOPIN1) & 0xF0;
			if(switchStatus1 == 0)
			{
				forward();
				stop();
				caseStateVar = 1;
				curStateVar = 1;
			}
			switchStatus2 = (LPC_GPIO0->FIOPIN0) & 0x01;
			if(switchStatus2 == 0)
			{
				backward();
				stop();
				caseStateVar = 2;
				curStateVar = 1;
			}			
			switchStatus3 = (LPC_GPIO0->FIOPIN2) & 0x01;
			if(switchStatus3 == 0)
			{
				left();
				stop();
				caseStateVar = 3;
				curStateVar = 1;
			}
			switchStatus4 = (LPC_GPIO0->FIOPIN3) & 0x01;
			if(switchStatus4 == 0)
			{
				right();
				stop();
				caseStateVar = 4;
				curStateVar = 1;
			}
			rAction = (LPC_GPIO2->FIOPIN0) & 0x01;
			if(rAction == 0)
			{
				repeatAction(i,action);
			}
			if (curStateVar != 0)
			{
				 action[i] = caseStateVar;
			   i++;
			   i=i%100;
			}
		}		
}
void repeatAction(unsigned int i,unsigned int action[100])
{
	i = 0;
	while(action[i] != 0 & i < 100)
	{	
		switch(action[i])
		{
			case 1:
				forward();
				break;
			case 2:
				backward();
				break;
			case 3:
				left();
				break;
			case 4:
				right();
				break;
			case 5:
			default:
				stop();
				break;
		}
		i++;
	}	
}
void delay_ms(unsigned int ms)
{
   unsigned int i,j;
   for(i=0; i<ms; i++)
   for(j=0; j<2; j++);   //Delay is low for simulation purposes
}
void forward()
{
  LPC_GPIO1->FIOSET = 0x1C400;			  
	delay_ms(LEFT_RIGHT_DELAY);
}
void backward()
{
	LPC_GPIO1->FIOSET = 0x2C200;       
	delay_ms(LEFT_RIGHT_DELAY);
}
void stop()
{
	LPC_GPIO1->FIOCLR = 0xFFFFFFFF;
  delay_ms(STOP_DELAY);			
}
void right()
{
	LPC_GPIO1->FIOSET = 0x4400;
  delay_ms(LEFT_RIGHT_DELAY);			
}
void left()
{
	LPC_GPIO1->FIOSET = 0x18000;
  delay_ms(LEFT_RIGHT_DELAY);			
}
		