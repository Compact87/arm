

#include <LPC213X.H>
#include "functions.h"



	void (*pokS1[10])(void)={zero_s1,one_s1,two_s1,three_s1,four_s1,five_s1,six_s1,seven_s1,eight_s1,nine_s1};
	void (*pokS2[10])(void)={zero_s2,one_s2,two_s2,three_s2,four_s2,five_s2,six_s2,seven_s2,eight_s2,nine_s2};
	void (*pokM1[10])(void)={zero_m1,one_m1,two_m1,three_m1,four_m1,five_m1,six_m1,seven_m1,eight_m1,nine_m1};
	//Counters
	int sek1=0,sek2=0,min1=0,min2=0,sat1=0,sat2=0,i=0,j=0;
	void timer_init(void);
 __irq void timer_IRQ(void);
	
    


int main()
{
   IODIR0 = 0xFFFFFFFF;
   timer_init();

 
	
		
    while(1){
			if(sek1==10){sek1=0;sek2++;}
			if(sek2==6){sek2=0;min1++;}
			if(min1==10){min1=0;}
			
			
		
		}
    /*{
				for(int i=0;i<10;i++,sek1++)
					(*pokS1[i])();
			
				if(sek1-1==9){
					sek1=0;
					sek2++;
					(*pokS2[sek2])();
					
				 	
					
					if(sek2-1==5){
	
						sek2=0;
						(*pokS2[sek2])();
						min1++;
						(*pokM1[min1])();
					}
				}
					
					
					
				
				}*/
			
    }
void timer_init(){
  PINSEL1 = PINSEL1 | 0x300000000;// p0.30 Capture pin
  VICVectAddr0=(unsigned)timer_IRQ;
	VICVectCntl0=0x00000024;	// timer0 irq za slot 0 i irq enable za slot 0
	VICIntEnable=0x00000010;	// enable timer0 irq
	VICIntSelect = 0x00000000; // svi interapti su irq (0 => t0 ce biti irq),(1 => t0 ce biti fiq)
	T0TCR = 0x02; //reset TC i PR
	T0CTCR = 0x00; //inkrementuje pc svakom uzlaznom ivicom PCLK-a
	T0PR = 0x1D; // PR rezolucija
	T0MR0 = 100000; //1usec*1000*100 
	T0MCR = 0x0003; //kada se poklope tc i mr0 pokrece interapt i resetuje tajmer 
	T0TCR = 0x01; // pokreni tajmer
}
__irq void timer_IRQ(void){
	
  (*pokS1[sek1++])();
	(*pokS2[sek2])();
	(*pokM1[min1])();
	T0IR = ( T0IR | (0x01) ); //reset interapt registra
	VICVectAddr = 0x00;
}	



