#define LCDDATA P1
#define DELAY for(i=0;i<1200;i++) //delay of 1200 m sec
 
sbit RS = P2^0; //all single bits are initialized
sbit RW = P2^1;
sbit EN = P2^2; 
 
void comwrt(unsigned char); 
void datawrt(unsigned char);
void  LCD_initialise();
void display(unsigned char *str);

void display(unsigned char *str)
{
    int i;
    for(;*str!=0;str++) {
    datawrt(*str);//send data as parameter 
    DELAY; //delay for 1200msec
    }
		
void comwrt(unsigned char dat)
{
    unsigned int i;
    LCDDATA=dat; 
    RS = 0; //to set up the display
    RW = 0; //writes to the LCD
    EN = 1; //enable the pin
    DELAY;
    EN = 0;
}

void datawrt(unsigned char dat)
{
    unsigned int i;
    LCDDATA=dat;
    RS = 1; //actual data is sent
    RW = 0; //writes to the LCD
    EN = 1;//enabling the LCD
    DELAY; //delay for 1200msec
    EN = 0;
}

void LCD_initialise()
{ 
    unsigned int i,j;
    int com[5]={0x38,0x0C,0x01,0x06,0x80}; //every com for displaying in different places
    for(j=0;j<=4;j++) {
    comwrt(com[j]); //to initialize every place
    DELAY; //delay for 1200msec
    }
} 


}
