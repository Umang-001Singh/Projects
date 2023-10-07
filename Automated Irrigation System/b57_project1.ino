#include<LiquidCrystal.h>
int sensorValue = 0;
int buttonPin1 = A3;
int buttonPin2 = A4;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup()
{
 lcd.begin(16, 2); 
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);

}

void loop()
{
  int buttonValue1 = digitalRead(buttonPin1);
  int buttonValue2 = digitalRead(buttonPin2);
  int sensorValue0 = analogRead(A0);
  int sensorValue1 = analogRead(A1);
  int sensorValue2 = analogRead(A2);
  
  if(buttonValue1==HIGH)
  {
  if(sensorValue0<400&&sensorValue1<400&&sensorValue2<400)
  {
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
    lcd.setCursor(0,0);          
  lcd.print("WATER LEVEL LOW"); 
  lcd.setCursor(0,1);           
  lcd.print("PUMP ON  (RICE)  ");  
    
   
  }
  // pause the program for <sensorValue> millseconds
  delay(sensorValue); // Wait for sensorValue millisecond(s)
  // turn the LED off
  if(sensorValue0>400&&sensorValue1>400&&sensorValue2>400)
  {
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);
    lcd.setCursor(0,0);          
  lcd.print("WATER LEVEL OK "); 
  lcd.setCursor(0,1);           
  lcd.print("PUMP OFF (RICE)  ");
  }
    
    
  }
  if(buttonValue2==HIGH)
  {
  if(sensorValue0<200&&sensorValue1<200&&sensorValue2<200)
  {
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
    lcd.setCursor(0,0);          
  lcd.print("WATER LEVEL LOW"); 
  lcd.setCursor(0,1);           
  lcd.print("PUMP ON  (WHEAT)");  
    
   
  }
  // pause the program for <sensorValue> millseconds
  delay(sensorValue); // Wait for sensorValue millisecond(s)
  // turn the LED off
  if(sensorValue0>200&&sensorValue1>200&&sensorValue2>200)
  {
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);
    lcd.setCursor(0,0);          
  lcd.print("WATER LEVEL OK "); 
  lcd.setCursor(0,1);           
  lcd.print("PUMP OFF (WHEAT)");
  }
    
    
  }
  delay(sensorValue);
  }