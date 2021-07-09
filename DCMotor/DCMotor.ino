//keep the current push button value 
int value=LOW;
//Keep the previous push button
int previousValue=LOW;
//check which way the motor is run if rotate mod 2 is 1 then rotate clockwise else roate anticlockwise
int rotate=0;
//keep the current second--in system 1000ms-->1second-- startMillis is keeping the program start millisecond
unsigned long startMillis;
//if the 3000ms--> 3second is over then time==true othersiwe time==false
bool time;
//analog value
int set=0;

void setup()
{
  //clockwise pin
   pinMode(5, OUTPUT);
   //anticlockwise pin
   pinMode(3, OUTPUT);
   //push button input pin
   pinMode(1, INPUT);
   //start millisecond is begin
   startMillis = millis();
}
void loop()
{
    //analog read -- get a value 0 to 255-- the value is 0 to 1023 but map is take a value from 0 to 255
    set=map(analogRead(A0),0,1023,0,255); 
    //check the 3 second is over
    Time();
    //push button pervious value is keep 
    previousValue=value;
    //push button read if is put value==HIGH otherwise value=LOW
    value=digitalRead(1);
    //check if button is push and again realese or time is over
    if((value==LOW && previousValue==HIGH)||time==true)
    { 
      //reset the start millisecond
      startMillis=millis();
      //rotate direction is change
      rotate++;
      //reset time value
      time=false;
    }
    //decide rotate direction 
    rotate_f(); 
}
//if rotate mod 2 is 0 then the motor is run in clockwise
//otherwise anticlockwise
void rotate_f()
{
  if(rotate%2==0)
  {
    //off anticlockwise pin
    analogWrite(5,0);
    //on anticlockwise pin
    analogWrite(3,set);
  }else
  {
    //off anticlockwise pin
    analogWrite(3,0);
    //on anticlockwise pin
    analogWrite(5,set);
  }
}
void Time(){
  //check time is 3000ms or bigger (3 second is done)
  if(millis() - startMillis >= 3000UL)
  {
    //time is over
    time=true;
  }
} 
