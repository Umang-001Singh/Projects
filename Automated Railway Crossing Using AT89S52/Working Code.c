#include<stdio.h>
#include<REGX51.H>



#define display_port P1
sbit rs=P3^2;
sbit rw=P3^3;
sbit e=P3^4;

int pre_reed_switch1;
int pre_infrared1;
int pre_reed_switch2;
int pre_infrared2;
int pre_obstacle1;
int pre_obstacle2;
int pre_reed_switch3;
int pre_infrared3;
int pre_reed_switch4;
int pre_infrared4;

sbit ledgreen=P0^4;
sbit ledred=P0^5;
sbit obstacle1=P0^6; //Obstacle sensor 1
sbit obstacle2=P0^7; //Obstacle sensor 2
sbit reed_switch2 = P2^6; // connect Reed switch to P1.0 
sbit reed_switch1 = P2^7; //connect Reed switch to P1.1 APPROACHING SENSOR
sbit infrared2 = P2^4; //connect infrared switch to P2.2
sbit infrared1 = P2^5; //connect infrared switch to P2.3 APPROACHING SENSOR
sbit motorA = P0^0; // enable pin for H-bridge
sbit motorB = P0^1; //dcmotor direction
// sbit led = P3^0;
sbit reed_switch3 = P2^3; //APPROACHING SENSOR
sbit reed_switch4 = P2^0;
sbit infrared3 = P2^2; //APPROACHING SENSOR
sbit infrared4 = P2^1;

// SENSOR SET 1 and SENSOR SET 2 are for track 1 
// SENSOR SET 3 and SENSOR SET 4 are for track 2

void msdelay(unsigned int x) {
    unsigned int i, j;
    for(i = 0; i < x; i++) {
        for(j = 0; j < 1275; j++);
    }
}

void lcd_cmd(unsigned char command){
	display_port = command;
	rs=0;
	rw=0;
	e =1;
	msdelay(1);
	e=0;
}

void lcd_data(unsigned char disp_data){
	display_port = disp_data;
	rs=1;
	rw=0;
	e=1;
	msdelay(1);
	e=0;
}

void lcd_init(){
	lcd_cmd(0x38);
	msdelay(10);
	lcd_cmd(0x0F);
	msdelay(10);
	lcd_cmd(0x01);
	msdelay(10);
	lcd_cmd(0x081);
	msdelay(10);
}


void checkSensors() {
	int y,z;
	
	//Function to open gates
	if((reed_switch4 == 1) && (infrared4 == 1)){
	
	// If train is coming on other track, gate would not open even if train on this track triggers receding set of sensors
	if(y==1){
		unsigned char b[23]="STOP TRAIN APPROACHING";
	int m=0;
	lcd_init();
	while(b[m]!='\0')
	{
		lcd_data(b[m]);
		if(m==14){
			lcd_cmd(0x0C1);
		}
		m++;
		msdelay(5);
	}
}

	//Gate will open if train is not coming on other track
	else{
	unsigned char c[13]="GATE OPENING";
	int n=0;
	lcd_init();
	while(c[n]!='\0'){
		lcd_data(c[n]);
		n++;
		msdelay(5);
	}
	
else
	{
	ledgreen=0;
	ledred=1;
	motorA=0;
	motorB=1;	// set P1^0 high to rotate DC motor in opposite direction i.e to open the gate
	msdelay(250);
	msdelay(250);
	motorA=0;
	motorB=0;
	ledgreen=0;
	ledred=1;
}
}
z=0;
}


//Second function to open the gates
else if ((reed_switch2 == 1) && (infrared2 == 1))
{	

	//If train is coming on other track, gate would not open even if train on this track triggers receding set of sensors
	if(z==1){
		unsigned char b[23]="STOP TRAIN APPROACHING";
	int m=0;
	lcd_init();
	while(b[m]!='\0')
	{
		lcd_data(b[m]);
		if(m==14){
			lcd_cmd(0x0C1);
		}
		m++;
		msdelay(5);
	}
}
	
	//If train is not approaching on other track, gates will open
	else{
	unsigned char c[13]="GATE OPENING";
	int n=0;
	lcd_init();
	while(c[n]!='\0'){
		lcd_data(c[n]);
		n++;
		msdelay(5);
	}
	
	
else{
	ledgreen=0;
	ledred=1;
	motorA=0;
	motorB=1;	// set P1^0 high to rotate DC motor in opposite direction i.e to open the gates
	msdelay(250);
	msdelay(250);
	motorA=0;
	motorB=0;
	ledgreen=0;
	ledred=1;
	}
}
y=0;
}


//If trains trigger the approaching sensor sets on both the tracks at the same time
else if (((reed_switch1 == 1) && (infrared1 == 1))&&((reed_switch3 == 1)&&(infrared3 == 1))){
	unsigned char b[23]="STOP TRAIN APPROACHING";
	int m=0;
	lcd_init();
	while(b[m]!='\0')
	{
		lcd_data(b[m]);
		if(m==14){
			lcd_cmd(0x0C1);
		}
		m++;
		msdelay(5);
	}
	
	
	//Obstacle detection
	if((obstacle1==1)||(obstacle2==1)){
		motorA=0;
		motorB=0;
		ledred=1;
		ledgreen=0;
	}

	else
	{
	ledred=0;
	ledgreen=1;
	motorA=1;
	motorB = 0;	// set P1^0 high to rotate DC motor in one direction
	msdelay(250);
	msdelay(250);
	motorA=0;
	motorB=0;
	ledgreen=1;
	ledred=0;
}
y=1;
z=1;
}
	

//If train is coming on track 1	
else if((reed_switch1 == 1) && (infrared1 == 1)) 
{	
	
	unsigned char b[23]="STOP TRAIN APPROACHING";
	int m=0;
	lcd_init();
	while(b[m]!='\0')
	{
		lcd_data(b[m]);
		if(m==14){
			lcd_cmd(0x0C1);
		}
		m++;
		msdelay(5);
	}
	

	//z==0 shows that gate not already closed	
	if(z==0){
	
	//Obstacle detection
	if((obstacle1==1)||(obstacle2==1)){
		motorA=0;
		motorB=0;
		ledred=1;
		ledgreen=0;
	}

else
{
	ledred=0;
	ledgreen=1;
	motorA=1;
	motorB = 0;	// set P1^0 high to rotate DC motor in one direction CLOCKWISE DIRECTION
	msdelay(250);
	msdelay(250);
	motorA=0;
	motorB=0;
	ledgreen=1;
	ledred=0;
}
}
y=1;
}


//If train is coming track 2
else if((reed_switch3 == 1)&&(infrared3 == 1)){
unsigned char b[23]="STOP TRAIN APPROACHING";
	int m=0;
	lcd_init();
	while(b[m]!='\0')
	{
		lcd_data(b[m]);
		if(m==14){
			lcd_cmd(0x0C1);
		}
		m++;
		msdelay(5);
	}
	
	//y==0 shows that gate is not already closed
	if(y==0){

	//Obstacle detection
	if((obstacle1==1)||(obstacle2==1)){
		motorA=0;
		motorB=0;
		ledred=1;
		ledgreen=0;
	}

else
{
	ledred=0;
	ledgreen=1;
	motorA=1;
	motorB = 0;	// set P1^0 high to rotate DC motor in one direction
	msdelay(250);
	msdelay(250);
	motorA=0;
	motorB=0;
	ledgreen=1;
	ledred=0;
	}	
}
z=1;
}



//When no train is coming
else 
{
	if(y==0 && z ==0){
	unsigned char a[14]="CROSSING OPEN";
	int l=0;
	lcd_init();
	while(a[l] != '\0')
	{
		lcd_data(a[l]);
		l++;
		msdelay(5);
	}
ledred=1;
ledgreen=0;
motorA=0; // set P1^0 low to stop DC motor
motorB=0; //
}
}
}

void main() 
{
while(1){
//Below lines ensure that checkSensors() is only accesed if signal coming from any of the sensor sets changes		 
if(((reed_switch1!=pre_reed_switch1)&&(infrared1!=pre_infrared1))||((reed_switch2!=pre_reed_switch2)&&(infrared2!=pre_infrared2))||((reed_switch3!=pre_reed_switch3)&&(infrared3!=pre_infrared3))||((reed_switch4!=pre_reed_switch4)&&(infrared4!=pre_infrared4))||(obstacle1!=pre_obstacle1)||(obstacle2!=pre_obstacle2))
{
	if(reed_switch1==1){
		pre_reed_switch1=1;
	}
	else{
		pre_reed_switch1=0;
	}
	if(reed_switch2==1)
	{
		pre_reed_switch2=1;
	}
	else{
		pre_reed_switch2=0;
	}
	if(reed_switch3==1){
		pre_reed_switch3=1;
	}
	else{
		pre_reed_switch3=0;
	}
	if(reed_switch4==1){
		pre_reed_switch4=1;
	}
	else{
		pre_reed_switch4=0;
	}
	
	if(infrared1==1){
		pre_infrared1=1;
	}
	else{
		pre_infrared1=0;
	}
	if(infrared2==1){
		pre_infrared2=1;
	}
	else{
		pre_infrared2=0;
	}
	if(infrared3==1){
		pre_infrared3=1;
	}
	else{
		pre_infrared3=0;
	}
	if(infrared4==1){
		pre_infrared4=1;
	}
	else{
		pre_infrared4=0;
	}
	
	if(obstacle1==1){
		pre_obstacle1=1;
	}
	else{
		pre_obstacle1=0;
	}
	if(obstacle2==1){
		pre_obstacle2=1;
	}
	else{
		pre_obstacle2=0;
	}
	
checkSensors();

}
}
}