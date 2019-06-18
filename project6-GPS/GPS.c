#include<lpc213x.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 50

__irq void uartISR(void);
void izlaz(void);
void uart_init(void);
void uart_write(char value);
void uart_write_msg(char msg[]);
char uart_read(void);
char msg[] = "\nHello world\r\n";
char echo_test[] = "test\r\n";
char c,buffer[MAX+1]="",test='\0',prev;
char c,buffer1[MAX+1]="";
char type[MAX+1]="";
char	time[MAX+1]="";
char	latitude[MAX+1]="";
 char	longitude[MAX+1]="";
 char	satelites[MAX+1]="";
char temp[MAX+1]=" ";



int i=0,m=0,n=0,br_char=0,output=0,state=0,poz=0,ti=0;

void delay_ms(uint16_t j)
{
    uint16_t x,i;
	for(i=0;i<j;i++)
	{
    for(x=0; x<6000; x++);    /* loop to generate 1 milisecond delay with Cclk = 60MHz */
	}
}

int main()	
{		
		
	
  
  uart_init();
  VICVectAddr0 = (unsigned) uartISR;	/* UART0 ISR Address */
	VICVectCntl0 = 0x00000026;	/* Enable UART0 IRQ slot */
	VICIntEnable = 0x00000040;	/* Enable UART0 interrupt */
	VICIntSelect = 0x00000000;	/* UART0 configured as IRQ */
	
    while(1)
    {  
		   delay_ms(1000);
			 izlaz();
    }        
}
void izlaz(){
	
			
		
			U0IER = 0x00000000;
			buffer1[m]='\0';
			time[ti]='\0';
			if(buffer1[0]==',')
			uart_write_msg(buffer1);
			for(n=1,ti=0;n<7;n++){
				time[ti++]=buffer1[n];
				if(ti==2 || ti==5)time[ti++]=':';
			}
			time[ti]='\0';
			uart_write_msg("UTC:\r\n");
			uart_write_msg(time);
			uart_write_msg("\r\n");
			
			
		
			
			strcpy(buffer1,"");
			strcpy(buffer,"");
			strcpy(time,"");
			 i=0;m=0;state=0;ti=0;poz=0;
		  U0IER = 0x00000001;
}


__irq void uartISR(void){
		
	 int iir_value;
		iir_value=U0IIR;
		c=U0RBR;
		buffer[i++]=c;
	  
		if(state==1)
			buffer1[m++]=c;
		if(buffer[i-1]=='A' && buffer[i-2]=='G'&& buffer[i-3]=='G')
			state=1;
		if(c=='$'&& state==1)
			state=0;
			

	
		U0IIR=iir_value;
		VICVectAddr = 0x00;
}
void uart_init(){
  PINSEL0= 0x00000005;	 //Configure P0.0/P0.1 as RX0 and TX0
  U0LCR =0x83;   	// 8bit data, 1Stop bit, No parity
  U0DLM=0x0;
	U0DLL=0x61;
	U0LCR = 0x03; 
	U0IER = 0x00000001;
}
void uart_write(char value){
	
	while(!(U0LSR & 0x20)); 
	U0THR=value;
	

}
void uart_write_msg(char msg[]){
	
	
 while(*msg)
	 uart_write(*msg++);
   
	
  

}
char uart_read(void){
	while(!(U0LSR & 0x01));
	
	return (U0RBR);
	

}


