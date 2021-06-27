code unsigned char SMS1[2] = "AT" ;
code unsigned char SMS2[9] = "AT+CMGF=1" ;
code unsigned char SMS3[8]= "AT+CMGS=" ; 
code unsigned char SMS4[3]= "ATD" ; 
code unsigned char SMS5[3]= "ATH" ; 
void sendSMS(unsigned char *num , unsigned char *msg);
void delay1(unsigned int tim);
void sendserial(unsigned char mydata1);
void call(unsigned char *num1);
unsigned char i;

void sendserial(unsigned char mydata1)
{
    TI=0; //transmitter is zero initially
    SBUF= mydata1; //mydata is transferred to SBUF
    while(TI==0); // when transmission is done T1 changes to 1
}

void init_serial()
{
    SCON=0x50; 
    TMOD=0x21; //timer 0 mode 1 timer 1 mode 2
    TH1=0xFD;
    TL1=0xFD;
    TR1=1;
}


void sendSMS(unsigned char *num , unsigned char *msg)
{   
    for (i=0;i<2;i++)
    sendserial(SMS1[i]); //to print each character in sms1
    sendserial(0X0D); //to print the next sentence in next line
    delay1(60);  //delay for 3sec
 
    for (i=0;i<9;i++)
    sendserial(SMS2[i]); //to print each character in sms2
    sendserial(0X0D);   //to print the next sentence in next line       
    delay1(60);        //delay for 3sec
    
    for (i=0;i<8;i++)
    sendserial(SMS3[i]);  //to print each character in sms3
    sendserial(0x22);   //to print the next sentence in same line 
    
    for(;*num!=0;num++)
    sendserial(*num);   //to print phone number
    sendserial(0X0D);   //to print the next sentence in next line  
    delay1(60);           //delay for 3sec
    
    for(;*msg!=0;msg++)
    sendserial(*msg);      //to print the message
    sendserial(0X0D);    //to print the next sentence in next line  
    delay1(80);          //delay for 4sec
 
}
 
void call(unsigned char *num1)
{
    for (i=0;i<2;i++)  
    sendserial(SMS1[i]);   //to print each character in sms1
    sendserial(0X0D);      //to print the next sentence in next line  
    delay1(60);     //delay of 3 sec
 
    for (i=0;i<9;i++)
    sendserial(SMS2[i]); //to print each character in sms2
    sendserial(0X0D);    //to print the next sentence in next line                  
    delay1(60);           //delay 3 sec
 
    for (i=0;i<3;i++)
    sendserial(SMS4[i]); //to print each character in sms4
    
    for(;*num1!=0;num1++)
    sendserial(*num1);    //send number to serial monitor
    sendserial(0X0D);     //to print the next sentence in next line   
    delay1(80);   //delay of 4sec
    delay1(600);  
 
    for (i=0;i<3;i++)
    sendserial(SMS5[i]);  //to print each character in sms4
    delay1(80);  //delay of 4sec
} 
 
void delay1(unsigned int tim)
{
    unsigned int h;
    for(h=0;h<=tim;h++) {
        TMOD=0X21;  
        TH0=0x4B;     //move 4B hexa into TH0
        TL0=0xFD;     //move FD hexa into TL0
        TR0=1;       //timer is started
        while(TF0==0); //it runs till Tf0 is 1
        TF0=0;  
    }
}
