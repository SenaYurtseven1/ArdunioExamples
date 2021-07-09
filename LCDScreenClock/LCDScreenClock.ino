//First i try in tinkercad. Other References:https://forum.arduino.cc/t/stop-motor-after-3-seconds/249156
//https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/substring/
//https://www.robotistan.com/16x2-lcd-ekran-yesil-uzerine-siyah?language=tr&h=5cb76a49&&gclid=Cj0KCQjw4v2EBhCtARIsACan3nyc7PEnV6gupygoPBMEhRe6vTbA5eKBQ49UTFz_INH-x8R1o6uT6MkaAr5xEALw_wcB
// include the library code for the LCD screen:
#include <LiquidCrystal.h> 
//keep the button current value. If button is pressed value become HIGH otherwise LOW.
int value=LOW;
//keep the button previous. If button was pressed previousvalue become HIGH otherwise LOW.
int previousValue=LOW;
//Push button pin number
int PUSHDOWN=1;

//the clock screen show in 2000 seconds.
int TIME_SCREEN_CLOCK = 2000;
//the info screen show in 1000 seconds. 
int TIME_SCREEN_INFO = 1000;
//Begin in this date
String TIME_STRING = "2021.12.31 - 23:59:58";

//odd numbers:turkish, even numbers:english
int language_flag=0;

//split the date and keep all values in a variable.
int year=0;
int month=0;
int day=0;
int hour=0;
int minute=0;
int second=0;
int eng_hour=0;

//begin with this time for info and clock screen 
//pre_time is used for calculate every second
unsigned long pre_time=0;
//preTimeScreen is used for calculate info and clock screen
unsigned long preTimeScreen=0;
//which screen is showing right now: screen_flag=1->info screen screen_flag=0->clock screen
int screen_flag=0;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{ 
  //push button is known by the system
  pinMode(PUSHDOWN, INPUT);
  // set up the LCD's number of columns and rows we have 2 row and 16 columns.
  lcd.begin(16, 2);

  //At the begin time is keep the values.
  pre_time=millis();
  preTimeScreen=millis();

//Take every value in string date with substring.
  year=TIME_STRING.substring(0,4).toInt();          
  month=TIME_STRING.substring(5,7).toInt();
  day=TIME_STRING.substring(8,10).toInt();
  hour=TIME_STRING.substring(13,15).toInt();
  minute=TIME_STRING.substring(16,18).toInt();
  second=TIME_STRING.substring(19,21).toInt();

  //take the english time hour we take turkish system time hour.
  if(hour>12)
  {
    eng_hour=hour-12;
  } 
  else
  {  
    if(hour == 0)
        eng_hour=12;
    else
      eng_hour=hour;  
  }
  //Clear the screen
  lcd.clear();
}

void loop() 
{
    //increase the second for every 1000 ms.      
    increase_second();
    //info and clock screen are change.
    changeScreen();
    //keep the button previous value
    previousValue=value;
    //read the button is pressed or not.
    value=digitalRead(PUSHDOWN);
    //check if button is pressed and after that release.
    if(value==LOW && previousValue==HIGH)
    { 
      //increase language flag and change the language.
      language_flag++;
      //clear the screen.
      lcd.clear();
    }
    //if screen_flag 1 then info screen show else calendar.    
    if(screen_flag==1)
      info();
    else
      calendar();
  //check minute second or year is over if over then update the calendar.
      if(second==60)
      {
        second=0;
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
      }else if(day==31 &&(month==4 || month==6 || month==9 || month==11))
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
      //decide new hour eng_hour   
      if(hour>12)
      {
        eng_hour=hour-12;
      } 
      else
      {  
        if(hour == 0)
          eng_hour=12;
        else
          eng_hour=hour;  
      }    
}
//Increase the second for every 1000 ms.
  void increase_second()
  {
   
    if((millis()-pre_time)>=1000)
    {
      pre_time=millis();
      second++;      
    }    
  }
//check the screen is on 2000ms for the clock and check the screen is on 1000ms for the info screen.
//If 2000ms or 1000ms is over then change the screen.
  void changeScreen()
  { 
    //Find the difference between begining time and current time and check it is bigger than 2000ms.
    //If it is bigger and clock screen is on so change the screen
    if(((millis()-preTimeScreen)>=TIME_SCREEN_CLOCK) && screen_flag==0)
    {
      preTimeScreen=millis();
      screen_flag = 1;  
      lcd.clear();
    }
    //Find the difference between begining time and current time and check it is bigger than 1000ms.
    //If it is bigger and info screen is on so change the screen
    if(((millis()-preTimeScreen)>=TIME_SCREEN_INFO) && screen_flag==1)
    {
      preTimeScreen=millis();
      screen_flag = 0; 
      lcd.clear();
    }
  }
//language_flag%2==0 --> ENG
//language_flag%2==1 --> TR
//Print every clock variable in the screen with setcursor function.
//for example setCursor(0,0)--> Get the index of [0,0].(0 row 0 column)
  void calendar()
  {   
    if(language_flag%2 == 0)
    {
      lcd.setCursor(0,0);
      if(eng_hour<10)
      lcd.print("0");
      lcd.print(eng_hour);
      lcd.print(":");
      
      lcd.setCursor(3, 0);
      if(minute<10)
      lcd.print("0");
      lcd.print(minute); 
      lcd.print(":");
      
      lcd.setCursor(6, 0);
      if(second<10)
      lcd.print("0");
      lcd.print(second); 
      
      lcd.setCursor(9, 0);
      if(hour<12)
      {
        lcd.print("AM");
      }else
      {
      lcd.print("PM");
      }
      
      lcd.setCursor(13, 0);
      lcd.print("ENG");
      
      lcd.setCursor(0, 1);
      if(day<10)
      lcd.print("0");
      lcd.print(day);
      lcd.print(".");
      
      lcd.setCursor(3, 1);
      if(month<10)
      lcd.print("0");
      lcd.print(month); 
      lcd.print(".");
      
      lcd.setCursor(6, 1);
      lcd.print(year);
      
      lcd.setCursor(13, 1);
      lcd.print(findDayOfWeek());
          
    }else
    {
      lcd.setCursor(0, 0);
      if(hour<10)
      lcd.print("0");
      lcd.print(hour);
      lcd.print(":");
      
      lcd.setCursor(3, 0);
      if(minute<10)
      lcd.print("0");
      lcd.print(minute); 
      lcd.print(":");
      
      lcd.setCursor(6, 0);
      if(second<10)
      lcd.print("0");
      lcd.print(second); 
      
      lcd.setCursor(13, 0);
      lcd.print("TUR");
      
      lcd.setCursor(0, 1);
      if(day<10)
      lcd.print("0");
      lcd.print(day);
      lcd.print(".");
      
      lcd.setCursor(3, 1);
      if(month<10)
      lcd.print("0");
      lcd.print(month); 
      lcd.print(".");
      
      lcd.setCursor(6, 1);
      lcd.print(year); 
      
      lcd.setCursor(13, 1);
      lcd.print(findDayOfWeek());    
    }  
  }
//print the screen info string.
  void info()
  {
    if(language_flag%2 == 0)
    {
     lcd.setCursor(0, 0);
     lcd.print("HH:MM:SS 12H LNG");
     lcd.setCursor(0, 1);
     lcd.print("DD.MM.YYYY   DOW");
    }else
    {
     lcd.setCursor(0, 0);
     lcd.print("SA:DA:SN 24H DIL");
     lcd.setCursor(0, 1);
     lcd.print("GG.AA.YYYY   GUN");
    } 
  }
  //Find the day of week use a formula.
  String findDayOfWeek()
  {
    int a=year-(14-month)/12;
    int b=a+a/4-a/100+a/400;
    int c=month+12*((14-month)/12)-2;
    int d=(day+b+(31*c)/12)%7;
    
    if(language_flag%2==0)
    {
      switch (d)
      {
          case 0:
      return"SUN";
        case 1:
      return"MON";
        case 2:
      return"TUE";
        case 3:
      return"WED";
          case 4:
      return"THU";
          case 5:
      return"FRI";
          case 6:
      return"SAT";
      }    
    }else if(language_flag%2==1)
    {
      switch (d)
      {
          case 0:
      return"PAZ";
        case 1:
      return"PZT";
        case 2:
      return"SAL";
        case 3:
      return"ÇAR";
          case 4:
      return"PER";
          case 5:
      return"CUM";
          case 6:
      return"CMT";
      }    
    }     
  }
