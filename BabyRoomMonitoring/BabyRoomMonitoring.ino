//References: https://www.youtube.com/watch?v=Ctbopg5hPyg
//https://www.youtube.com/watch?v=9d8P6_HrgUY
//For dht11 sensor i include a library which is "DHT.h"
#include "DHT.h"
//The pin which sensor is connetected
#define DHTPIN 2
//which type dht11
#define DHTTYPE DHT11
//dht object is created and it takes dhtpin and dhttype 
DHT HumidtyandTempr(DHTPIN, DHTTYPE);
//LDR pin
int LDR =0;
//keep the light number
int light;
//keep the humidity number
int hum;
//keep the temperature number
int temp;

//Decide the day--> if light>=400 --> day if light<400 --> night
String lightofday;
//Decide humidity--> 30<=humidity<=50-->optimal humidity<30-->low humidity>50-->high
String humidity;
//Decide temperature--> if(day) --> 20<=temperature<=24-->optimal temperature<20-->cold temperature>24-->hot
//if(night) --> 18<=temperature<=21-->optimal temperature<18-->cold temperature>21-->hot
String temperature;

//Date and time components give default values.
int day=30;
int month=5;
int year=2021;

int hour=23;
int minute=12;
int second=59;

//keep the begining time
unsigned long pre_time=0;
//check three second is passed
bool threesecond=false;

void setup()
{
  //open seri monitor
  Serial.begin(9600);
  //begin the dht11 function
  HumidtyandTempr.begin();
  //give a start time
  pre_time=millis();
}

void loop()
{ 
  //check the three second is over
  increasesecond();
  //if three second is over then display screen
  if(threesecond)
  {
    //Decide night or day
    DayorNight();
    //Decide humidity optimal,low or high
    DecideHumidity();
    //Decide temperature hot, low or high
    DecideTemp();
    //Display the date and clock on the screen
    Date();
    //Display every element on the screen
    Serial.print(" - Light: ");
    Serial.print(light);
    Serial.print(" - Temperature: ");
    Serial.print(temp);
    Serial.print(" - Humidity: ");
    Serial.print(hum);
    Serial.println("%");
    Serial.print(lightofday);
    Serial.print(" - ");
    Serial.print(temperature);
    Serial.print(" - ");
    Serial.println(humidity);
    Serial.println("---------------");
    //three second is over again begin the three second flag
    threesecond=false;
  } 
}
//Decide day or night
void DayorNight(){
  //Take the analog value of the light
  light =analogRead(LDR);
  if(light>=400)
    lightofday="Day";
  else
    lightofday="Night";
}

void DecideHumidity()
{
  //Decide humidity with below function(readHumidity())
   hum = HumidtyandTempr.readHumidity();
   if(hum<30)
     humidity="Low Humidity";
   else if(hum>50)
      humidity="High Humidity";
   else
      humidity="Optimal Humidity";
}

void DecideTemp()
{
  //Decide temperature with below function(readTemperature())
   temp = HumidtyandTempr.readTemperature();
   if(lightofday=="Night")
   {
      if(temp<18)
        temperature="Cold";
      else if(temp>21)
        temperature="Hot";
      else
        temperature="Optimal Temperature";
   }
   else if(lightofday=="Day")
   {
      if(temp<20)
        temperature="Cold";
      else if(temp>24)
        temperature="Hot";
      else
        temperature="Optimal Temperature";
   }
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
   if((millis()-pre_time)>=3000)
   {
     pre_time=millis();
     second=second+3; 
     threesecond=true;     
   }    
}
//if a number is only one digit so we have to add 0 at the beggining so this function print 0
void printnumber(int number) {
  if (number < 10) 
    Serial.print("0"); // print a 0 before if the number is < than 10
  Serial.print(number);
}
