#include <lpc21xx.h>
#include <stdint.h>

#define bit(x) (1<<x)
//#define delay for(i=0;i<=60000;i++);
#define SwitchPinNumber 31
#define LEFT 29
#define RIGHT 30
#define FORWARD 31
#define BACKWARD 28

#define LcdDataBusPort       IO1PIN
#define LcdControlBusPort    IO1PIN

#define LcdDataBusDirnReg    IO1DIR
#define LcdCtrlBusDirnReg    IO1DIR

#define LCD_RS     16
#define LCD_RW     17
#define LCD_EN     18

#define LCD_D4     20
#define LCD_D5     21
#define LCD_D6     22
#define LCD_D7     23					 

/* Masks for configuring the DataBus and Control Bus direction */
#define LCD_ctrlBusMask  ((1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN))
#define LCD_dataBusMask  ((1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7))

unsigned int  forwardStatus;
unsigned int  backwardStatus;
unsigned int  leftStatus;
unsigned int  rightStatus;

char i,a[]={"HIasdasd!"},forward[]={"FORWARD!"},backward[]={"BACKWARD!"},right[]={"RIGHT!"},left[]={"LEFT!"};
unsigned char c;
void delay(int cnt)
{
    int i,j;
    for(i=0;i<cnt;i++)
	for(j=0;j<10;j++);
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
	
	if ( PWMIR & 0x0008 )
	{
		PWMIR = 0x0008;
	}	
	
	VICVectAddr = 0x00000000;
}

/* Function send the a nibble on the Data bus (LCD_D4 to LCD_D7) */
void sendNibble(char nibble)
{
    LcdDataBusPort&=~(LCD_dataBusMask);                   // Clear previous data
    LcdDataBusPort|= (((nibble >>0x00) & 0x01) << LCD_D4);
    LcdDataBusPort|= (((nibble >>0x01) & 0x01) << LCD_D5);
    LcdDataBusPort|= (((nibble >>0x02) & 0x01) << LCD_D6);
    LcdDataBusPort|= (((nibble >>0x03) & 0x01) << LCD_D7);
}


/* Function to send the command to LCD. 
   As it is 4bit mode, a byte of data is sent in two 4-bit nibbles */
void Lcd_CmdWrite(char cmd)
{
    sendNibble((cmd >> 0x04) & 0x0F);  //Send higher nibble
    LcdControlBusPort &= ~(1<<LCD_RS); // Send LOW pulse on RS pin for selecting Command register
    LcdControlBusPort &= ~(1<<LCD_RW); // Send LOW pulse on RW pin for Write operation
    LcdControlBusPort |= (1<<LCD_EN);  // Generate a High-to-low pulse on EN pin
    delay(1000);
    LcdControlBusPort &= ~(1<<LCD_EN);

    delay(1000);

    sendNibble(cmd & 0x0F);            //Send Lower nibble
    LcdControlBusPort &= ~(1<<LCD_RS); // Send LOW pulse on RS pin for selecting Command register
    LcdControlBusPort &= ~(1<<LCD_RW); // Send LOW pulse on RW pin for Write operation
    LcdControlBusPort |= (1<<LCD_EN);  // Generate a High-to-low pulse on EN pin
    delay(1000);
    LcdControlBusPort &= ~(1<<LCD_EN); 

    delay(1000);
}


void Lcd_DataWrite(char dat)
{
    sendNibble((dat >> 0x04) & 0x0F);  //Send higher nibble
    LcdControlBusPort |= (1<<LCD_RS);  // Send HIGH pulse on RS pin for selecting data register
    LcdControlBusPort &= ~(1<<LCD_RW); // Send LOW pulse on RW pin for Write operation
    LcdControlBusPort |= (1<<LCD_EN);  // Generate a High-to-low pulse on EN pin
    delay(1000);
    LcdControlBusPort &= ~(1<<LCD_EN);

    delay(1000);

    sendNibble(dat & 0x0F);            //Send higher nibble
    LcdControlBusPort |= (1<<LCD_RS);  // Send HIGH pulse on RS pin for selecting data register
    LcdControlBusPort &= ~(1<<LCD_RW); // Send LOW pulse on RW pin for Write operation
    LcdControlBusPort |= (1<<LCD_EN);  // Generate a High-to-low pulse on EN pin
    delay(1000);
    LcdControlBusPort &= ~(1<<LCD_EN); 

    delay(1000);
}

int main (void)
{
	//DC MOTOR//
		IO1PIN=0x00000000;
		IO1DIR=0x0;
		IO1DIR|=0x0f000000; //Declaring as a output
		int j=4;//direction control
		
		
	
	PINSEL0 = PINSEL0 | 0x00000008; /* Configure P0.1 as PWM3 */

	
	LcdDataBusDirnReg |= LCD_dataBusMask;  // Configure all the LCD pins as output
    LcdCtrlBusDirnReg |= LCD_ctrlBusMask;															 

Lcd_CmdWrite(0x02);                   // Initialize Lcd in 4-bit mode
    Lcd_CmdWrite(0x28);                   // enable 5x7 mode for chars 
    Lcd_CmdWrite(0x0E);                   // Display OFF, Cursor ON
    Lcd_CmdWrite(0x01);                   // Clear Display
    Lcd_CmdWrite(0x80);                   // Move the cursor to beginning of first line	 
		
		 Lcd_CmdWrite(0xc0);

    for(i=0;a[i]!=0;i++)
    {
        Lcd_DataWrite(a[i]);
    }
			VICVectAddr0 = (unsigned) PWM_ISR; /* PWM ISR Address */
	VICVectCntl0 = (0x00000020 | 8); /* Enable PWM IRQ slot */
	VICIntEnable = VICIntEnable | 0x00000100; /* Enable PWM interrupt */
	VICIntSelect = VICIntSelect | 0x00000000; /* PWM configured as IRQ */
	PWMTCR = 0x02; /* Reset and disable counter for PWM */
	PWMPR = 0x1D; /* Prescale Register value */
	PWMMR0 = 20000; /* Time period of PWM wave, 20msec */
	PWMMR3 = 650;	/* Ton of PWM wave 0.65 msec */
	PWMMCR = 0x00000203;	/* Reset and interrupt on MR0 match, interrupt on MR3 match */
	PWMLER = 0x09;	/* Latch enable for PWM3 and PWM0 */
	PWMPCR = 0x0800;	/* Enable PWM3 and PWM 0, single edge controlled PWM */
	PWMTCR = 0x09;	/* Enable PWM and counter */
		//int16_t value = 1000;
		PWMMR3 = value;
			PWMLER = 0x08;
			delay_ms(5);
	while(1)
	{
		
		/*for(int16_t value = 650; value<2450; value++)
		{
			rightStatus = (IOPIN1>>RIGHT) & 0x01 ;
			if(leftStatus==1)break;
			PWMMR3 = value;
			PWMLER = 0x08;
			delay_ms(5);
		}
		for(int16_t value = 2450; value>650; value--)
		{
			leftStatus = (IOPIN1>>LEFT) & 0x01 ;
			PWMMR3 = value;
			PWMLER = 0x08;
			delay_ms(5);
		}
		*/
						leftStatus=(IOPIN1>>LEFT) & 0x01 ;
						rightStatus=(IOPIN1>>RIGHT) & 0x01 ;
			if((leftStatus!=1) && value>600 ){
				value=value-30;
				PWMMR3=value;
				PWMLER=0x08;
				delay_ms(5);
				
			}
			if((rightStatus!=1) && value<1250){
				value=value+30;
				PWMMR3=value;
				PWMLER=0x08;
				delay_ms(5);
				
			}
		
		
					  forwardStatus = (IOPIN1>>FORWARD) & 0x01 ;
						backwardStatus = (IOPIN1>>BACKWARD) & 0x01 ;
				
 /*Forward*/
if(forwardStatus!=1){	 
	if(j!=1){
		Lcd_CmdWrite(0x80);
	for(i=0;a[i]!=0;i++)
    {
				
        Lcd_DataWrite(forward[i]);
    }
	}

	IO1SET=bit(24); //IN1 = 1
	IO1CLR=bit(25); //IN2 = 0
	IO1SET=bit(26); //IN1 = 1
	IO1CLR=bit(27); //IN2 = 0
	j=1;
}
delay_ms(60);
 /*Off*/
IO1CLR=bit(24)|bit(25); //IN1 = IN2 = 0
IO1CLR=bit(26)|bit(27); //IN1 = IN2 = 0
// delay;delay;
 /*Reverse*/
if(backwardStatus!=1){	 
	if(j!=0){
		Lcd_CmdWrite(0x80);
	for(i=0;a[i]!=0;i++)
    {
				
        Lcd_DataWrite(backward[i]);
    }
	}
	
	IO1SET=bit(25); //IN2 = 1
	IO1CLR=bit(24); //IN0 = 1
	IO1SET=bit(27); //IN1 = 1
	IO1CLR=bit(26); //IN2 = 0
	j=0;
}
 //IO0SET=bit(1); //IN2 = 1
 //IO0CLR=bit(0); //IN0 = 1
// delay;delay;
 /*Off*/
// IO0CLR=bit(0)|bit(1); //IN1 = IN2 = 0
 //delay;delay;
	}
}