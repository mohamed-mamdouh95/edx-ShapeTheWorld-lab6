
#define SYSCTL_RCGC2 				(*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTF_AMSEL 			(*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL 			(*((volatile unsigned long *)0x4002552C))
#define GPIO_PORTF_DIR				(*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL			(*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_DEN 				(*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_PUR				(*((volatile unsigned long *)0x40025510))	
#define GPIO_PORTF_DATA				(*((volatile unsigned long *)0x400253FC))


void port_init(void){
	volatile unsigned long delay;
	SYSCTL_RCGC2 |= 0x00000020;
	delay = SYSCTL_RCGC2;
	GPIO_PORTF_AMSEL = 0x00;
	GPIO_PORTF_PCTL = 0x00000000;
	GPIO_PORTF_DIR |= 0x04; 			//make pf2 as output
	GPIO_PORTF_DIR &= (~0x10); 	 //make pf4 as input
	GPIO_PORTF_PUR = 0x10;
	GPIO_PORTF_AFSEL = 0x00;
	GPIO_PORTF_DEN = 0x14;
	
}

void Delay100ms(unsigned long time){
  unsigned long i;
  while(time > 0){
    i = 1333333;  // this number means 100ms
    while(i > 0){
      i = i - 1;
    }
    time = time - 1; // decrements every 100 ms
  }
}

unsigned long switch_input ;

int main(void)
{
	port_init();
	while(1){
	  switch_input = GPIO_PORTF_DATA & 0x10;
		if(!switch_input)
		{
				Delay100ms(1);
				GPIO_PORTF_DATA ^= 0x04;
		}
		else{
				GPIO_PORTF_DATA = 0x04;
		}
	}
}