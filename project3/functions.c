#include <LPC213X.H>
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
	 pom=IO0PIN &  0xffffff80;
   IO0PIN =pom | 0x0000003f;
	msdelay(100);

}
void one_s1(){
	 pom=IO0PIN &  0xffffff80;
   IO0PIN =pom | 0x00000030;
msdelay(100);

}
void two_s1(){
	 pom=IO0PIN &  0xffffff80;
   IO0PIN =pom | 0x0000005b;
	msdelay(100);

}
void three_s1(){
	 pom=IO0PIN &  0xffffff80;
   IO0PIN =pom | 0x0000004f;


}
void four_s1(){
	 pom=IO0PIN &  0xffffff80;
   IO0PIN =pom | 0x00000066;
	msdelay(100);

}
void five_s1(){
	 pom=IO0PIN &  0xffffff80;
   IO0PIN =pom | 0x0000006d;
	

}
void six_s1(){
	 pom=IO0PIN &  0xffffff80;
   IO0PIN =pom | 0x0000007d;
	msdelay(100);

}
void seven_s1(){
	 pom=IO0PIN &  0xffffff80;
   IO0PIN =pom | 0x00000007;
	msdelay(100);

}
void eight_s1(){
	 pom=IO0PIN &  0xffffff80;
   IO0PIN =pom | 0x0000007f;
	msdelay(100);

}
void nine_s1(){
	 pom=IO0PIN &  0xffffff80;
   IO0PIN =pom | 0x0000006f;
	msdelay(100);

}
//DISPLEJ ZA SEKUNDE DVA
void zero_s2(){
	 pom=IO0PIN &  0xffff80ff;
   IO0PIN =pom | 0x00003f80;
	

}
void one_s2(){
	 pom=IO0PIN &  0xffff80ff;
   IO0PIN =pom | 0x00003000;
	

}
void two_s2(){
	 pom=IO0PIN &  0xffff80ff;
   IO0PIN =pom | 0x00005b00;
	

}
void three_s2(){
	 pom=IO0PIN &  0xffff80ff;
   IO0PIN =pom | 0x00004f00;
	

}
void four_s2(){
	 pom=IO0PIN &  0xffff80ff;
   IO0PIN =pom | 0x00006600;
	

}
void five_s2(){
	 pom=IO0PIN &  0xffff80ff;
   IO0PIN =pom | 0x00006d00;
	

}
void six_s2(){
	 pom=IO0PIN &  0xffff80ff;
   IO0PIN =pom | 0x00007d00;
	

}
void seven_s2(){
	 pom=IO0PIN &  0xffff80ff;
   IO0PIN =pom | 0x00000700;
	

}
void eight_s2(){
	 pom=IO0PIN &  0xffff80ff;
   IO0PIN =pom | 0x00007f00;
	

}
void nine_s2(){
	 pom=IO0PIN & 0xffff80ff;
   IO0PIN =pom |0x00006f00;
	

}


