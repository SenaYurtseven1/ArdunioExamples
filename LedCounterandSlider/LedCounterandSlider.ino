//  TIME_LED_COUNTER used store waiting time between steps in operation1(Led counter operation)
int TIME_LED_COUNTER = 500;
//TIME_LED_SLIDER used store waiting time between steps in operation2(Led slider operation)
int TIME_LED_SLIDER = 250;
//It has been used to observe the LED turned on and off.
int DELAY_TIME=150;

//When ardunio pins are change, i can easily change the pins in here.  
int LED1=1;
int LED2=2;
int LED3=3;
int LED4=4;
int PUSHDOWN=5;

//The value variable contains the last variable of Pushdown Button.It is assigned to Low becouse i do not press in the first.
int value=LOW;
//The value variable contains the previous variable of Pushdown Button.
int previousValue;
//operationFlag variable is used for change the operations.If Led counter operation is continue then change the Led slider operation.Vice-versa.
int operationFlag=0;
//If press the button then number is increase. Firstly operation 1 is begin. So if num variable is 1 or odd number so operation 2 must begin.
//If press the button then number is increase. If num is odd number at the beggining so the number is increase and become even number so operation 1 is begin.
int num=0;

//At the beggining i assigned input and output pins.
void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(PUSHDOWN, INPUT);
}
//the loop is always run. At the beggining operation1 which is led counter is run. If button pressed then operation2 which is led slider is begin.
void loop()
{
     operation1();
     operation2();
}
//Operation1 is led counter. Led counter count 1 to 15. Each step in the loop is one of our counting steps in reality.It checks whether the button is pressed when each step will start.
//If the button is pressed-the operation flag is 1-, i came to the end of the first operation.Otherwise the operation1 is continue. 
//In operation 1 i have some rules for the check the led become HIGH or LOW:
//LED 1--> If the number of steps is odd then led will be high.
//LED 2--> If the number of steps is divided in two and the result is odd, it will high.
//LED 3--> If the LED2 is divided in two and the result is odd, it will high. 
//LED 4--> If the LED3 is divided in two and the result is odd,, it will high. 
// Every step check the led will be open or not. In here All leds can be open or closed at the same time. So that all of them can must assigned low at the same time-the last of the step-.
void operation1()
{
  for (int i=0;i<=15;i++)
  {  
    check();
    if(operationFlag==0)
    {
     int led1=i%2;
     int led2=(i/2);
     int led3=(led2/2); 
     int led4=(led3/2);
    
     if(led1%2==1)
        digitalWrite(LED1, HIGH);
     if(led2%2==1)
        digitalWrite(LED2, HIGH);
     if(led3%2==1)
        digitalWrite(LED3, HIGH);
     if(led4%2==1)
        digitalWrite(LED4, HIGH);
      
     delay(DELAY_TIME);
     digitalWrite(LED1, LOW); 
     digitalWrite(LED2, LOW); 
     digitalWrite(LED3, LOW);
     digitalWrite(LED4, LOW);
     delay(TIME_LED_COUNTER);
    }
    else 
      break;  
  }
}  
//Operation2 is led slider.Each step in the loop is one of our counting steps in reality.It checks whether the button is pressed when each step will start.
//If the button is pressed-the operation flag is 0-, i came to the end of the second operation.Otherwise the operation2 is continue.
//In here every step number is check and the leds become HIGH or LOW.
void operation2()  
{
  for(int i=0;i<6; i++)
  { 
    check();
    if(operationFlag==1)
    {
    
     if(i==0)
     {
      digitalWrite(LED1, HIGH);
      delay(DELAY_TIME);
      digitalWrite(LED1, LOW);
     }
     else if(i==1 || i==5)
     {
      digitalWrite(LED2, HIGH);
      delay(DELAY_TIME);
      digitalWrite(LED2, LOW);
     }
     else if(i==2 || i==4)
     {
      digitalWrite(LED3, HIGH);
      delay(DELAY_TIME);
      digitalWrite(LED3, LOW);
     }
     else if(i==3)
     {
      digitalWrite(LED4, HIGH);
      delay(DELAY_TIME);
      digitalWrite(LED4, LOW);
     }
     delay(TIME_LED_SLIDER);
    }
    else 
      break;  
  }    
}
//The function i control whether the button is pressed.
//To control this, i keep the previous value of the button. If the button is firstly Low and after that value is HIGH then button is pressed. But in here the button can be repedatly pressed.
//So that i have to check the button is realesed. If the button is pressed and relased then the button previous value become HIGH and current value become Low.
//In here if number is odd the operation 1 is over and operation 2 is begin. Otherwise operation 2 is over and operation 1 is begin.
void check()
{   
    previousValue=value;
    value=digitalRead(PUSHDOWN);
  
  if(value==LOW && previousValue==HIGH)
  { 
    if(num%2==0)
      operationFlag=1;
   else
      operationFlag=0;
    
    num++;
  }
}
