#include "mbed.h"
#include "C12832.h"

//Hardware Initialisation
C12832 lcd(SPI_MOSI, SPI_SCK, SPI_MISO, p8, p11);   //LCD display
DigitalIn PB1(p5);         //Increament digit (push button)
DigitalIn PB2(p6);         //Decrement digit (push button)
DigitalIn PB3(p7);         //Accepts entered digit and move cursor (push button)
DigitalOut IND1(p8);         //LED Indicates that entered code is correct (Blue LED)
DigitalOut IND2(p9);         //LED Indicates that entered code is wrong (Red LED)
//Hardware for part 2
DigitalIn holster(p11);      //Indicates holster position (A switch)
DigitalOut pump(p10);       //Indicates pump on and flow rate (yellow LED)
AnalogIn pot(p15);          //Potentiometer increases flow rate (Potentiometer)

//Function parameters
void attendant();
void underscore();
void firstdigit();
void seconddigit();
void thirddigit();
void fourthdigit();
void fifthdigit();
void sixthdigit();
void seventhdigit();
void convert();
void delivery();
void by();
void flowrate();
void lcdprep();

//Global vairables Declaration and Initialisation
int container0=0, digitone=0, container1=0, digittwo=0, container2=0;
int digitthree=0, container3=0, digitfour=0, container4=0;
int digitfive=0, container5=0, digitsix=0, container6=0;
int digitseven=0, container7=0;
int num, check=3545202;
float cost, tickert;
bool flag1=0, flag2=0, flag3=0;     //allows some functions to run once
Timer t;
Ticker t1;
Timeout t2;

//Main function where the algo is buit
int main(){
    while(IND1==0 && holster==0){
        t1.attach(callback(&by), 500.0f);   //Remove once you can detach ticker interrupt
        while(IND1==0){
            lcdprep();
            lcd.printf("Switch on the Dispenser");
            if(holster==1){
                printf("Attentant lifted the nozzle from the holster\n");
                attendant();
                underscore();
                firstdigit();
                seconddigit();
                thirddigit();
                fourthdigit();
                fifthdigit();
                sixthdigit();
                seventhdigit();
                convert();
                wait(0.2);
            }else{
                IND2.write(false);
                wait(0.2);
            }
        }
        if(IND1==1){
            lcdprep();
            lcd.printf("Press the enter button to \ninitiate fuel delivery");
        }
        while(holster==1){
            if(PB3==1){
            lcdprep();
            lcd.printf("Fuel: %.2f ltrs\nCumulative cost: GBP %.2f",tickert,cost);
            printf("Delivery Initiated.\n");
            flowrate();     //add this funtion to when the enter button is pressed
            }
            if(cost<150 && holster==0){   //allows metering to work if code starts afresh
            IND1=0;
            printf("Pump has been turned off\n");
            printf("Total cost of fuel dispensed: GPB %.2f\n", cost);
            wait(1);
            tickert=0;
            cost=0;
            flag1=0;
            flag2=0;
            }else if(cost>150 && holster==1 && flag3==0){   //keeps cost on pc screen
            IND1=0;
            printf("Maximum volume of fuel has been dispensed\n");
            printf("Total cost of fuel dispensed: GPB %.2f\n", cost);
            flag3=1;        //makes cost display once
            }
        wait_ms(2);
        }
        if(cost>150 && holster==0){   //allows metering to work if code starts afresh
            IND1=0;
            printf("Pump has been turned off\n");
            wait(1);
            tickert=0;
            cost=0;
            flag1=0;
            flag2=0;
            flag3=0;
        }
        wait(1);
    }
}



//Function definitions
//Prepares LCD for display
void lcdprep(){
    lcd.cls();
    lcd.locate(0,0);
}
//Requests code from user
void attendant(){
    lcdprep();
    lcd.printf("Enter your pesonal code: \n");
}

//displays "_" on the lcd
void underscore(){
    while(container0==0 && holster==1){
        if(PB3==1){                     //Placing _ on the lcd
            lcdprep();
            lcd.printf("_");
            container0=1;
            printf("Code authentication started\n");
        }else{
            container0=0;
        }
        wait(0.2);
    }
}    
//Entering the first digit
void firstdigit(){
    
    while(container1==0 && holster==1){
        if(PB1==1 && digitone<10){      //Increasing the digit
            digitone++;
            lcd.locate(0,0);
            lcd.printf("%d", digitone);
        }else if(PB2==1 && digitone>=1){    //Decreasing the digit
            digitone--;
            lcd.locate(0,0);
            lcd.printf("%d", digitone);
        }else if(PB3==1){                   //Accepting the digit
            lcd.locate(6,0);
            lcd.printf("_");
            container1=1;               
        }else{
            container1=0;           
        }
        wait(0.2);
    }
}
//Entering the second digit
void seconddigit(){
    while(container2==0 && holster==1){
        if(PB1==1 && digittwo<10){      //Increasing the digit
            digittwo++;
            lcd.locate(6,0);
            lcd.printf("%d", digittwo);
        }else if(PB2==1 && digittwo>=1){    //Decreasing the digit
            digittwo--;
            lcd.locate(6,0);
            lcd.printf("%d", digittwo);
        }else if(PB3==1){                   //Accepting the digit
            lcd.locate(12,0);
            lcd.printf("_");
            container2=1;
        }else{
            container2=0;
        }
        wait(0.2);
    }
}
//Entering the third digit
void thirddigit(){
    while(container3==0 && holster==1){
        if(PB1==1 && digitthree<10){      //Increasing the digit
            digitthree++;
            lcd.locate(12,0);
            lcd.printf("%d", digitthree);
        }else if(PB2==1 && digitthree>=1){    //Decreasing the digit
            digitthree--;
            lcd.locate(12,0);
            lcd.printf("%d", digitthree);
        }else if(PB3==1){                   //Accepting the digit
            lcd.locate(18,0);
            lcd.printf("_");
            container3=1;
        }else{
            container3=0;
        }
        wait(0.2);
    }
}
//Entering the fourth digit
void fourthdigit(){
    while(container4==0 && holster==1){
        if(PB1==1 && digitfour<10){      //Increasing the digit
            digitfour++;
            lcd.locate(18,0);
            lcd.printf("%d", digitfour);
        }else if(PB2==1 && digitfour>=1){    //Decreasing the digit
            digitfour--;
            lcd.locate(18,0);
            lcd.printf("%d", digitfour);
        }else if(PB3==1){                   //Accepting the digit
            lcd.locate(24,0);
            lcd.printf("_");
            container4=1;
        }else{
            container4=0;
        }
        wait(0.2);
    }
}
//Entering the fifth digit
void fifthdigit(){
    while(container5==0 && holster==1){
        if(PB1==1 && digitfive<10){      //Increasing the digit
            digitfive++;
            lcd.locate(24,0);
            lcd.printf("%d", digitfive);
        }else if(PB2==1 && digitfive>=1){    //Decreasing the digit
            digitfive--;
            lcd.locate(24,0);
            lcd.printf("%d", digitfive);
        }else if(PB3==1){                   //Accepting the digit
            lcd.locate(30,0);
            lcd.printf("_");
            container5=1;
        }else{
            container5=0;
        }
        wait(0.2);
    }
}
//Entering the sixth digit
void sixthdigit(){
    while(container6==0 && holster==1){
        if(PB1==1 && digitsix<10){      //Increasing the digit
            digitsix++;
            lcd.locate(30,0);
            lcd.printf("%d", digitsix);
        }else if(PB2==1 && digitsix>=1){    //Decreasing the digit
            digitsix--;
            lcd.locate(30,0);
            lcd.printf("%d", digitsix);
        }else if(PB3==1){                   //Accepting the digit
            lcd.locate(36,0);
            lcd.printf("_");
            container6=1;
        }else{
            container6=0;
        }
        wait(0.2);
    }
}
//Entering the seventh digit
void seventhdigit(){
    while(container7==0 && holster==1){
        if(PB1==1 && digitseven<10){      //Increasing the digit
            digitseven++;
            lcd.locate(36,0);
            lcd.printf("%d", digitseven);
        }else if(PB2==1 && digitseven>=1){    //Decreasing the digit
            digitseven--;
            lcd.locate(36,0);
            lcd.printf("%d", digitseven);
        }else if(PB3==1){                   //Accepting the digit
            lcd.locate(42,0);
            
            container7=1;
        }else{
            container7=0;
        }
        wait(0.2);
    }
}
//Converting the digits to an integer
void convert(){
    num=digitone*10;
    num=num+digittwo;
    num=num*10;
    num=num+digitthree;
    num=num*10;
    num=num+digitfour;
    num=num*10;
    num=num+digitfive;
    num=num*10;
    num=num+digitsix;
    num=num*10;
    num=num+digitseven;
    if(num==check){             //Auth code but enable program to start afresh
       IND1.write(1);
       IND2.write(0);
       container0=0; digitone=0; container1=0; digittwo=0; container2=0;
       digitthree=0; container3=0; digitfour=0; container4=0;
       digitfive=0; container5=0; digitsix=0; container6=0;
       digitseven=0; container7=0;
       printf("Attendant's code is correct.\n");
       wait(1);
    }else if(container0!=0){    //Enables restart of auth when code is wrong    
       IND2.write(1);
       container0=0; digitone=0; container1=0; digittwo=0; container2=0;
       digitthree=0; container3=0; digitfour=0; container4=0;
       digitfive=0; container5=0; digitsix=0; container6=0;
       digitseven=0; container7=0;
       printf("Attendant's code is wrong.\n");
    }else{
       IND2.write(1);
       printf("Attendant returned nozzle to the holster\n");
    }
}
//blink yellow led, calculates cost, tells casher when pump is running and when paused
void by(){
    if(cost<150.1 && holster==1){
        pump = !pump;
        tickert=tickert+0.1;
        cost= tickert*1.5;
    }else{
        pump.write(0);
    }
    if(pot>0 && holster==1 && cost<150.1 && flag1==0){
        printf("Fuel is deivering\n");
        flag1=1;
    }else if(pot==0 && holster==1 && cost<150.1 && flag2==0){
        printf("Fuel delivery is paused\n");
        flag2=1;
    }
}
//led blinking to indicate flow rate
void flowrate(){
    while (IND1==1 && holster==1 && cost<150.1) {
        if(pot*5>0 && pot*5<1 || pot*5==1){
            t1.attach(callback(&by), 1.0f);
            lcdprep();
            lcd.printf("Fuel: %.2f ltrs\nCumulative cost: GBP %.2f",tickert,cost);
            wait(1.0);
        }else if(pot*5>1 && pot*5<2 || pot*5==2){
            t1.attach(callback(&by), 0.8f);
            lcdprep();
            lcd.printf("Fuel: %.2f ltrs\nCumulative cost: GBP %.2f",tickert,cost);
            wait(0.8);
        }else if(pot*5>2 && pot*5<3 || pot*5==3){
            t1.attach(callback(&by), 0.6f);
            lcdprep();
            lcd.printf("Fuel: %.2f ltrs\nCumulative cost: GBP %.2f",tickert,cost);
            wait(0.6);
        }else if(pot*5>3 && pot*5<4 || pot*5==4){
            t1.attach(callback(&by), 0.4f);
            lcdprep();
            lcd.printf("Fuel: %.2f ltrs\nCumulative cost: GBP %.2f",tickert,cost);
            wait(0.4);
        }else if(pot*5>4 && pot*5<5){
            t1.attach(callback(&by), 0.2f);
            lcdprep();
            lcd.printf("Fuel: %.2f ltrs\nCumulative cost: GBP %.2f",tickert,cost);
            wait(0.2);
        }else if(pot*5>4 && pot*5<5 || pot*5==5){
            t1.attach(callback(&by), 0.1f);
            lcdprep();
            lcd.printf("Fuel: %.2f ltrs\nCumulative cost: GBP %.2f",tickert,cost);
            wait(0.1);
        }else{
            t1.attach(callback(&by), 500.0f);    //the time lower than wait time, so it can attach
            pump.write(0);  
            wait_us(0.2);           //wait time is far lower than attach time. (use detach function in this block)
        }
        //wait_ms(osWaitForever);
    }
}



