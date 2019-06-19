#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
void iot(String stringdata);
int moisture = A2;
int temp = A0;
int water = A9;
int rain = A11;

int mpin1 = 52;
int mpin2 = 50;
int mpin3 = 46;
int mpin4 = 44;
char s;
//iotcloud616.

 

///................///////............
void setup()
{
  //pinMode(water,INPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  pinMode(moisture, INPUT);
  pinMode(temp, INPUT);
  
  pinMode(mpin1,OUTPUT);
  pinMode(mpin2,OUTPUT);
  pinMode(mpin3,OUTPUT);
  pinMode(mpin4,OUTPUT);  



  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("SMART");
  lcd.setCursor(4,1);
  lcd.print("AGRICULTURE");
  delay(2000);
  lcd.clear();
}
///////////////......................///////////////////////
void loop()
{
  while ( Serial.available() > 0)
  {
    char s = (char) Serial.read();
   // Serial.print(state);
    
    lcd.print(s);
    if (s == 'A')
    {
      lcd.setCursor(0, 0);
      lcd.print("CITRUS CONKER");
      delay(1000);
      iot("*CITRUS CONKER#");
      delay(1000);
      lcd.clear();
      s = ' ';
    }
    else if (s == 'B')
    {
      lcd.setCursor(0, 0);
      lcd.print("CITRUS WHITEFLY");
      delay(1000);
      iot("*CITRUS WHITEFLY#");
       delay(1000);
      lcd.clear();
       s = ' ';
    }
    else if (s == 'C')
    { 
      lcd.setCursor(0, 0);
      lcd.print("CITRUS GREENING");
      delay(1000);
      
      iot("*CITRUS GREENING#");
      delay(1000);
      lcd.clear();
       s = ' ';
    }
    else if (s == 'D')
    {
      lcd.setCursor(0, 0);
      lcd.print("CITRUS SOOTYMOLD");
      delay(1000);
      iot("*CITRUS SOOTYMOLD#");
      delay(1000);
      lcd.clear();
       s = ' ';
    }
  }

  
 
  int moisturelevel = analogRead(moisture);
  delay(100);
  //Serial.println(moisturelevel);
  lcd.setCursor(0,0);
  lcd.print("MOIS LEVEL; ");
  lcd.print(moisturelevel);
  delay(1000);
 
  lcd.clear();
   if (moisturelevel>800)
  {
     digitalWrite(mpin1,HIGH);
    digitalWrite(mpin2,LOW);
    lcd.setCursor(0, 0);
    lcd.print("MOISTURE LEVEL");
    lcd.setCursor(0, 1);
    lcd.print("LOW");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PUMP MOTOR ON");
    iot("*MOISTURE LEVEL LOW#");
    
    lcd.clear();
  }
  if(moisturelevel<600)
  {
    lcd.setCursor(0, 0);
    lcd.print("MOISTURE LEVEL");
    lcd.setCursor(0, 1);
    lcd.print("NORMAL");
 
    digitalWrite(mpin1,LOW);
    digitalWrite(mpin2,LOW);
    iot("*MOISTURE LEVEL NORMAL#");
   
    lcd.clear();
    
  }
  int waterlevel = analogRead(water);
  //Serial.print(waterlevel);
  lcd.setCursor(0,0);
  lcd.print("water level; ");
  lcd.print(waterlevel);
  delay(1000);
  lcd.clear();
 
  
  if(waterlevel<416)
  {
    digitalWrite(mpin3, HIGH);
    digitalWrite(mpin4, LOW);
    lcd.setCursor(0,0);
    lcd.print("TANK EMPTY");
    delay(1000);
    lcd.clear();
    
    lcd.setCursor(0,0);
    lcd.print("PUMP MOTOR ON");
    iot("*TANK EMPTY#");
    lcd.clear();
  }
 if(waterlevel>600 && waterlevel<710)
  {
    digitalWrite(mpin3, LOW);
    digitalWrite(mpin4, LOW);
    lcd.setCursor(0,0);
    lcd.print("TANK LEVEL");
    lcd.setCursor(4,1);
    lcd.print("NORMAL");
    
    iot("*TANK LEVEL NORMAL#");
    lcd.clear();
  }
  
   if(waterlevel>720 && waterlevel<900)
  {
   digitalWrite(mpin3, LOW);
    digitalWrite(mpin4, LOW);
    lcd.setCursor(0,0);
    lcd.print("TANK LEVEL");
    lcd.setCursor(4,1);
    lcd.print("FULL");
    
    iot("*TANK LEVEL FULL#");
    lcd.clear();
   
  }
 int tempvalue = analogRead(temp);
  //Serial.println(tempvalue);
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("TEMPLEVEL:");
  lcd.setCursor(11, 0);
  lcd.print(tempvalue/2);
  delay(1000);
  lcd.clear();

  if ((tempvalue/2)>45)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TEMPERATURE");
    lcd.setCursor(0, 1);
    lcd.print("LEVEL HIGH");
    delay(1000);
    iot("*TEMPERATURE LEVEL HIGH#");
    
    lcd.clear();
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TEMPERATURE");
    lcd.setCursor(0, 1);
    lcd.print("LEVEL NORMAL");
    delay(1000);
    iot("*TEMPERATURE LEVEL NORMAL#");
    
    lcd.clear();
  }
  int rainlevel=analogRead(rain);
  //Serial.println(rainlevel);


 
 
  lcd.setCursor(0,0);
  lcd.print("RAINLEVEL:");
  lcd.setCursor(11,0);
  lcd.print(rainlevel);
  
  lcd.clear();
  if (rainlevel<330)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("RAIN LEVEL");
    lcd.setCursor(0,1);
    lcd.print("HIGH");
    
    iot("*RAIN LEVEL HIGH#");
   
    lcd.clear();
  }
  if(rainlevel>600)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("NO RAIN");
    delay(1000);
    iot("*NO RAIN#");
    delay(1000);
    lcd.clear();
  }
  if((rainlevel>350)&&(rainlevel<600))
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("RAIN LEVEL");
    lcd.setCursor(0,1);
    lcd.print("NORMAL");
    
    iot("*RAIN LEVEL NORMAL#");
    
    lcd.clear();
  }
}



void iot(String stringdata)
{
  for (int i = 0; i < stringdata.length(); i++)
  {
    Serial1.write(stringdata[i]);
  }
  delay(4000);
}
