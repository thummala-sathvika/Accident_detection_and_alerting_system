#include<reg51.h> //include header files
#include"GSM.h"
#include"LCD.h"

#define NUMBER1 ".........."   //Enter the mobile number
#define NUMBER2 ".........."
#define NUMBER3 ".........."

sbit vib = P3^2;    //initializing the single bits used in the circuit
sbit buzzer = P0^0;
sbit sw=P2^4;
sbit motor=P2^3;

void main()
{
	
	unsigned int r;
	sw=0; //switch in off state
	motor=0;  //motor in rest state
  init_serial();    //function to initialize the serial ports for transferring data using  timer 0 mode 1 timer 1 mode 2
  LCD_initialise(); //function to initialize LCD display
    comwrt(0x80);  //function to enable LCD for enabling and to write data on screen in first row
    display("INITIALISING...."); //calling display with parameter as string to display initialization on LCD
    for(r=0;r<60000;r++); //to get delay for 60000msec
    comwrt(0x80); //set LCD to write the data in first row
    display("GSM ACCIDENT DET");
    comwrt(0xC0);  //set LCD to write the data in second row
    display(" VIBRATION: NO  ");
    buzzer=1;  //buzzer in off state
    while(1) {
			if(sw==1) //when switch is on
				motor=1; //start motor to rotate
			else  //otherwise
				motor=0;//keep motor in normal state
			
      if(vib==1) { //if vibration is ditected then 
            buzzer=0; //buzzer is on
            comwrt(0x80); //set LCD to write data in first row
            display("VIBRATION DETECT"); //display "VIBRATION DETECT" in first row
            comwrt(0xC0); //set LCD to write data in first row
            display(" VIBRATION: YES ");
            for(r=0;r<30000;r++); //give delay 
            for(r=0;r<30000;r++);
            comwrt(0x80); //again to set LCD in writing state in first row
            display("SENDING MSG....."); //displaying the message
            sendSMS(NUMBER1,"...."); //function to send number and name/message as parameters 
            sendSMS(NUMBER2,"....");
            sendSMS(NUMBER3,"....");
            comwrt(0xC0); //again to set LCD in writing state and to write what GSM module did
            display("    MSG SENT    ");
            for(r=0;r<30000;r++);// for delay
            for(r=0;r<30000;r++);
            for(r=0;r<30000;r++);
            comwrt(0x80); //to set LCD in writing state and to write what GSM module did
            display("CALLING.........");
            call(NUMBER1); //function call and sending number as parameter to which number GSM have to dail
            call(NUMBER2);
            call(NUMBER3);
            comwrt(0x80);
            display("GSM ACCIDENT DET");
        
        }
        else //if vibration is not detected 
        {
            buzzer=1; //buzzer is in off state
            comwrt(0xC0); //to set LCD in writing state at second row
            display(" VIBRATION: NO  ");   //display the message
        }
            
    }
}
