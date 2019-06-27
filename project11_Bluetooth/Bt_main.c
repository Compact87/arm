#include <lpc213x.h>
#include <stdint.h>

unsigned char c;
void uart_init(void){
	PINSEL0 |= 0x00008005;
  U0LCR=0x83;
	U0DLM=0x0;
	U0DLL=0x61;
	U0LCR=0x3;
	U0IER=0x01;
}
void uart_write(unsigned char c){
		U0IER = 0x00000000;
		U0THR=c;
		U0IER = 0x00000001;
}
void uart_write_msg(unsigned char *msg){
	while(*msg)
		uart_write(*msg++);


}
__irq void uart_ISR(void){
	int iir_value;
	
	iir_value=U0IIR;
	c=U0RBR;
	
	uart_write(c);
	if(c=='a')IOSET0=0x00000004;
	if(c=='b')IOCLR0=0x00000004;
	U0IIR=iir_value;
	
	VICVectAddr=0x00;
}
void delay_ms(uint16_t j)
{
    uint16_t x,i;
	for(i=0;i<j;i++)
	{
    for(x=0; x<6000; x++);    /* loop to generate 1 milisecond delay with Cclk = 60MHz */
	}
}

__irq void PWM_ISR (void)
{
	if ( PWMIR & 0x0001 )
	{
		PWMIR = 0x0001;
	}

	
	if ( PWMIR & 0x0004 )
	{
		PWMIR = 0x0004;
	}	
	
	VICVectAddr = 0x00000000;
}

int main(){
	uart_init();
	VICVectAddr0=(unsigned) uart_ISR;
	VICVectCntl0=0x26;
	VICIntEnable = 0x00000040;	/* Enable UART0 interrupt */
	VICIntSelect = 0x00000000;	/* UART0 configured as IRQ */
	/////////////////////////
	//int16_t value = 1000;
	PINSEL0 = PINSEL0 | 0x00008005; /* Configure P0.1 as PWM3 */
	VICVectAddr1 = (unsigned) PWM_ISR; /* PWM ISR Address */
	VICVectCntl1 = (0x00000020 | 8); /* Enable PWM IRQ slot */
	VICIntEnable = VICIntEnable | 0x00000100; /* Enable PWM interrupt */
	VICIntSelect = VICIntSelect | 0x00000000; /* PWM configured as IRQ */
	PWMTCR = 0x02; /* Reset and disable counter for PWM */
	PWMPR = 0x1D; /* Prescale Register value */
	PWMMR0 = 5000; /* Time period of PWM wave, 20msec */
	PWMMR2 = 650;	/* Ton of PWM wave 0.65 msec */
	PWMMCR = 0x00000043;	/* Reset and interrupt on MR0 match, interrupt on MR3 match */
	PWMLER = 0x05;	/* Latch enable for PWM3 and PWM0 */
	PWMPCR = 0x0400;	/* Enable PWM3 and PWM 0, single edge controlled PWM */
	PWMTCR = 0x09;	/* Enable PWM and counter */
	IODIR0|=0x00000004;

	while(1)
	{
		
		/*PWMMR2 = 650;
		PWMLER = 0x04;
		delay_ms(200);
		PWMMR2 = 1600;	
		PWMLER = 0x04;
		delay_ms(200);
		PWMMR2 = 2450;	
		PWMLER = 0x04;
		delay_ms(200);
	*/
		for(int16_t value = 650; value<2450; value++)
		{
			while(c=='a'){}
			PWMMR2 = value;
			PWMLER = 0x04;
			delay_ms(5);
			
			
		}
		for(int16_t value = 2450; value>650; value--)
		{
			while(c=='a'){}
			PWMMR2 = value;
			PWMLER = 0x04;
			delay_ms(5);
			
		
		}
	}

}
