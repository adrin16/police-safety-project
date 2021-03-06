#include<Servo.h>                          //library for servo
#include<LiquidCrystal.h>                  //library for LCD display
#define pir 4
#define whiteled 3
#define greenled 2
#define trig 5
#define echo 6
#define servo_pin 9
#define buzzer 20
#define alcohol 5
Servo myservo;                             //creating servo object              
long duration=0;
float dist=0;
float distance=0;
float max_smoke = 0;
float smoke=0;
int i;
int temp=0;
unsigned long starttime,endtime;
LiquidCrystal lcd(22,23,24,25,26,27,28,29,30,31);            //creating liquidcrystal object

void setup()
{
  pinMode(pir,INPUT);
  pinMode(whiteled,OUTPUT);
  pinMode(greenled,OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  myservo.attach(servo_pin);                              //this says where signal pin is actually connected
  pinMode(buzzer,OUTPUT);
  pinMode(alcohol,INPUT);
  for(i=44;i<=53;i++)
  pinMode(i,OUTPUT);
  myservo.write(0);                                       //set servo to 0 position
  lcd.begin(16, 2);                                       //initialises interface to lcd screen
}

void loop() 
{
  if(digitalRead(pir) == 1)                               //checks for presence of person
  {
    lcd.clear();                                          //clears lcd screen
    lcd.setCursor(3,0);                                   //sets position in lcd screen to print
    lcd.print("WELCOME");                                 //prints in lcd screen
    check_dist();
   }
   else
   {
    digitalWrite(whiteled,LOW);
    myservo.write(0);                                     //if no person is present servo will be at initial position
   }
   
 }

void check_dist()
{
  while(digitalRead(pir)==1)
  {
    digitalWrite(whiteled,HIGH);                          //glow white led when person is present
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    duration = pulseIn(echo,HIGH);                        //calculates duration for switching echo pin from low to high
    dist = (duration/58.138)*0.39;                        //calc distance in inches
    distance = dist*2.54;                                 //distance in cm
    if(distance<=5)                                       //checks for distance less than 5
    {
      digitalWrite(greenled,HIGH);                        //when the distance is less tahn 5 glow green led
      delay(500);
      detection();
    }
    else 
    digitalWrite(greenled,LOW); 
  }
}
void detection()
{
  while(distance<=5)
  {
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Be Ready");
    digitalWrite(whiteled,HIGH);
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    duration = pulseIn(echo,HIGH);
    dist = (duration/58.138)*0.39;
    distance = dist*2.54;
    myservo.write(90); 
    tone(4,1000,500);
    starttime = millis();
    endtime = starttime;
    while((endtime-starttime)<5000)
    {
      smoke = analogRead(alcohol);
      if(smoke>temp)
      temp=smoke;
      endtime=millis();
     }
     max_smoke=temp;
     myservo.write(0);
     lcd.clear();
     lcd.setCursor(1,0);
     lcd.print("Sensor val=");
     lcd.setCursor(12,0);
     lcd.print(max_smoke);
     lcd.setCursor(1,1);
     lcd.print("Level =");
     if(max_smoke<30)
     {
      lcd.setCursor(9,1);
      lcd.print("1");
      digitalWrite(2,HIGH);
       for(i=44;i<=53;i++)
         digitalWrite(i,LOW);
         
     }
      if(max_smoke>=30 && max_smoke<40)
     {
      lcd.setCursor(9,1);
      lcd.print("2");
       for(i=44;i<=45;i++)
         digitalWrite(i,HIGH);
       for(i=46;i<=53;i++)
         digitalWrite(i,LOW);
     }
      if(max_smoke>=40 && max_smoke<50)
     {
      lcd.setCursor(9,1);
      lcd.print("3");
        for(i=44;i<=46;i++)
         digitalWrite(i,HIGH);
       for(i=47;i<=53;i++)
         digitalWrite(i,LOW);
     }
      if(max_smoke>=50 && max_smoke<60)
     {
      lcd.setCursor(9,1);
      lcd.print("4");
       for(i=44;i<=47;i++)
         digitalWrite(i,HIGH);
       for(i=48;i<=53;i++)
         digitalWrite(i,LOW);
     }
      if(max_smoke>=60 && max_smoke<70)
     {
      lcd.setCursor(9,1);
      lcd.print("5");
       for(i=44;i<=48;i++)
         digitalWrite(i,HIGH);
       for(i=49;i<=53;i++)
         digitalWrite(i,LOW);
     }
      if(max_smoke>=70 && max_smoke<80)
     {
      lcd.setCursor(9,1);
      lcd.print("6");
       for(i=44;i<=49;i++)
         digitalWrite(i,HIGH);
       for(i=50;i<=53;i++)
         digitalWrite(i,LOW);
     }
      if(max_smoke>=80 && max_smoke<90)
     {
      lcd.setCursor(9,1);
      lcd.print("7");
       for(i=44;i<50;i++)
         digitalWrite(i,HIGH);
       for(i=51;i<=53;i++)
         digitalWrite(i,LOW);
     }
      if(max_smoke>=90 && max_smoke<100)
     {
      lcd.setCursor(9,1);
      lcd.print("8");
       for(i=44;i<51;i++)
         digitalWrite(i,HIGH);
       for(i=52;i<=53;i++)
         digitalWrite(i,LOW);
     }
      if(max_smoke>=100 && max_smoke<110)
     {
      lcd.setCursor(9,1);
      lcd.print("9");
       for(i=44;i<=52;i++)
         digitalWrite(i,HIGH);
         digitalWrite(53,LOW);
     }
      if(max_smoke>=110)
     {
      lcd.setCursor(9,1);
      lcd.print("10");
       for(i=44;i<=53;i++)
         digitalWrite(i,HIGH);
     }
    delay(5000);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Thank you");
    delay(5000);
  }
}
