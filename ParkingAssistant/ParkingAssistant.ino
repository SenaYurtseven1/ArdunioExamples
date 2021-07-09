//references:https://www.youtube.com/watch?v=jgPZsxYvSIk&ab_channel=Robotistan,http://www.arduino.cc/en/Tutorial/Tone
// include the library code:
#include <LiquidCrystal.h> 

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Some notes for the game 
#define NOTE_C4  262
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262
//buzzer trigger and echo pin defined
#define buzz 8
#define triggerPin 7
#define echoPin 6

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
//keep the distance measure
int cm = 0;

//Date and time components give default values.
int day=30;
int month=5;
int year=2021;

int hour=23;
int minute=12;
int second=59;

//keep the begining time for the lcd and serial monitor
unsigned long pre_time=0;
unsigned long pre_time_one=0;

//check two second is passed
bool twosecond=true;
//check 100 ms is passed
bool onesecond=true;


void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  //Serial monitor is begin
  Serial.begin(9600);
  //timing is begin for the two secon or 100 ms is over or not
  pre_time=millis();
  pre_time_one=millis();
  //Trigger,echo and buzz pin are defined in the code
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzz, OUTPUT);
  //lcd display is clear
  lcd.clear();
}

void loop()
{
  // cm the ping time in cm
  cm = readUltrasonicDistance();
  //the time is passed for the two second and 100ms
  increasesecond();  
  //If the car is crashed then play the game over melody
  if(cm==5)
  {
     gameOver();
     printLCD();
  }
  //Print the serial monitor every two second.
  if(twosecond)
  {
      Date();
      Serial.print(" -Distance: ");
      Serial.print(cm);
      Serial.println(" cm.");
      printDistanceTypeinSerial();
      twosecond=false;
  }
  //update the information every 100 ms.
  if(onesecond)
    printLCD();
}
//read the distance
long readUltrasonicDistance()
{
  long duration, distance;
  //Clear the trigger
  digitalWrite(triggerPin,LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  //distance is keep the values in cm
  distance = duration / 58.2;
  //if the values are between 400cm and 0 then it will return as a distance 
  if(distance >= 400 || distance <= 0)
      return 0;
  return distance;
}
//Create a gameover melody
void gameOver() 
{
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void printDistance() {
  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  // print the distance on the lcd 
  lcd.print(cm);
  lcd.print(" cm");
}

void printLCD()
{
  melodydistance(cm*10);
  lcd.clear();
  printDistance();
  printDistanceType();
  //delay(1000);
  onesecond=false;  
}

void printDistanceType()
{
  
  lcd.setCursor(0, 1);
  if(cm>100)
    lcd.print("Too Far");
  else if(cm>=51&&cm<=100)
     lcd.print("Far");
  else if(cm>=21&&cm<=50)
     lcd.print("Close");
  else if(cm>=5&&cm<=20)
    lcd.print("Too Close");
  else
     lcd.print("Crashed");  
}
void printDistanceTypeinSerial()
{
  lcd.setCursor(0, 1);
  if(cm>100)
    Serial.println("Too Far");
  else if(cm>=51&&cm<=100)
     Serial.println("Far");
  else if(cm>=21&&cm<=50)
     Serial.println("Close");
  else if(cm>=5&&cm<=20)
    Serial.println("Too Close"); 
  else
     Serial.println("Crashed");
}

void Date()
{
  //if second is bigger than 60 so 0 will come
  if(second==60)
  {
      second=0;
      minute++;
  }
  //if bigger than 60 so take the second
  if(second>60)
  {
      second=second-60;
      minute++;
  }     
  if(minute==60)
  {
      minute=0;
      hour++;
  }    
  if(hour==24)
  {
      hour=0;
      day++;
  } 
  if(day==32 &&(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12))
  {
      day=1;
      month++;
  }
  else if(day==31 &&(month==4 || month==6 || month==9 || month==11))
  {
      day=1;
      month++;
  }
  else if(day==29 &&(month==2))
  {
      day=1;
      month++;
  }
  else if(day==28 &&(month==2) && (year%4==0))
  {
      day=1;
      month++;
  }      
  if(month==13)
  {
      month=1;
      year++;
  }  
  Serial.print("Date: ");
  printnumber(day);
  Serial.print(".");
  printnumber(month);
  Serial.print(".");
  Serial.print(year);
  Serial.print(" - ");
  Serial.print("Hour: ");
  printnumber(hour);
  Serial.print(":");
  printnumber(minute);
  Serial.print(":");
  printnumber(second);
}
//Decide three second is over or not
void increasesecond()
{
    if((millis()-pre_time_one)>=100)
   {
     pre_time_one=millis();
     onesecond=true;     
   }    
   if((millis()-pre_time)>=2000)
   {
     pre_time=millis();
     second=second+2; 
     twosecond=true;     
   }   
}
//if a number is only one digit so we have to add 0 at the beggining so this function print 0
void printnumber(int number) {
  if (number < 10) 
    Serial.print("0"); // print a 0 before if the number is < than 10
  Serial.print(number);
}

int melodydistance(int dly)
{
  if(cm>100)
    tone(8, 262);//DO
  else if(cm>=51&&cm<=100)
     tone(8, 330);//Mi
  else if(cm>=21&&cm<=50)
    tone(8, 349);//Fa
  else if(cm>=5&&cm<=20)
    tone(8, 440);//la
  else
     tone(8, 523);//ince si
  
  delay(dly);
  noTone(8);
  delay(dly);

}
