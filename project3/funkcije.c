
#include "functions.h"

unsigned long int tim=100,pom;
void msdelay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<6002;j++);
}
//DISPLEJ ZA SEKUNDE JEDAN
void zero_s1(){
	 IOCLR0 =0x0000007f;
   IOSET0 |= 0x0000003f;
	
//	msdelay(10);

}
void one_s1(){
	 IOCLR0 =  0x0000007f;
   IOSET0 |= 0x00000030;
//msdelay(10);

}
void two_s1(){
	 IOCLR0 =  0x0000007f;
   IOSET0 |= 0x0000005b;
	//msdelay(10);

}
void three_s1(){
	 IOCLR0 =  0x0000007f;
   IOSET0 |= 0x0000004f;
//msdelay(10);

}
void four_s1(){
	 IOCLR0 =  0x0000007f;
   IOSET0 |= 0x00000066;
	//msdelay(10);

}
void five_s1(){
	 IOCLR0 =  0x0000007f;
   IOSET0 |= 0x0000006d;
	//msdelay(10);

}
void six_s1(){
	 IOCLR0 =  0x0000007f;
   IOSET0 |= 0x0000007d;
	//msdelay(10);

}
void seven_s1(){
	 IOCLR0 =   0x0000007f;
   IOSET0 |= 0x00000007;
	//msdelay(10);

}
void eight_s1(){
	 IOCLR0 =  0x0000007f;
   IOSET0 |= 0x0000007f;
	//msdelay(10);

}
void nine_s1(){
	 IOCLR0 =  0x0000007f;
   IOSET0 |= 0x0000006f;
	//msdelay(10);

}
//DISPLEJ ZA SEKUNDE DVA
void zero_s2(){
	 IOCLR0 =  0x00007f00;
   IOSET0 |= 0x00003f00;
	

}
void one_s2(){
	 IOCLR0 =  0x00007f00;
   IOSET0 |= 0x00003000;
	

}
void two_s2(){
	 IOCLR0 =  0x00007f00;
   IOSET0 |= 0x00005b00;
	

}
void three_s2(){
	 IOCLR0 =  0x00007f00;
   IOSET0 |= 0x00004f00;
	

}
void four_s2(){
	 IOCLR0 =0x00007f00;
   IOSET0 |= 0x00006600;
	

}
void five_s2(){
	 IOCLR0 =  0x00007f00;
   IOSET0 |= 0x00006d00;
	

}
void six_s2(){
	 IOCLR0 = 0x00007f00;
   IOSET0 |= 0x00007d00;
	

}
void seven_s2(){
	 IOCLR0 =  0x00007f00;
   IOSET0 |= 0x00000700;
	

}
void eight_s2(){
	 IOCLR0 =  0x00007f00;
   IOSET0 |= 0x00007f00;
	

}
void nine_s2(){
	 IOCLR0 = 0x00007f00;
   IOSET0 |=0x00006f00;
	

}
//DISPLEJ ZA MINUTE JEDAN
void zero_m1(){
	 IOCLR0 =  0x007f0000;
   IOSET0 |= 0x003f0000;
	

}
void one_m1(){
	 IOCLR0 =  0x007f0000;
   IOSET0 |= 0x00300000;
	

}
void two_m1(){
	 IOCLR0 =  0x007f0000;
   IOSET0 |= 0x005b0000;
	

}
void three_m1(){
	 IOCLR0 =  0x007f0000;
   IOSET0 |= 0x004f0000;
	

}
void four_m1(){
	 IOCLR0 =  0x007f0000;
   IOSET0 |= 0x00660000;
	

}
void five_m1(){
	 IOCLR0 =  0x007f0000;
   IOSET0 |= 0x006d0000;
	

}
void six_m1(){
	 IOCLR0 =  0x007f0000;
   IOSET0 |= 0x007d0000;
	

}
void seven_m1(){
	 IOCLR0 =  0x007f0000;
   IOSET0 |= 0x00070000;
	

}
void eight_m1(){
	 IOCLR0 =  0x007f0000;
   IOSET0 |= 0x007f0000;
	

}
void nine_m1(){
	 IOCLR0 = 0x007f0000;
   IOSET0 |=0x006f0000;
	

}

