//COUNTER_VALUE is the variable that we specify the increase in the number specified in the code.
int COUNTER_VALUE  = 7;
//Keep the button is pressed or not/ at the beggining we do not pressed the button so default value is LOW.
int value=LOW;
//Keep the previous push button
int previousValue=LOW;
//Which number is show on the seven segment display we show in this variable
int num=0;
//Check the button pressed or not
bool flag=false;
//We determine the which pins are input and which pins are output.
void setup()
{

  //Let's make it more random
  randomSeed(42);   
  
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, INPUT);
}

void loop()
{
    //the previous value of push button
    previousValue=value;
    //keep the push button value if pressed value=HIGH , otherwise value=LOW. 
    value=digitalRead(9);
    //if the push button is now low and previously high so the button is pressed we say.
    if(value==LOW && previousValue==HIGH)
    { 
        //find the random number take a random number from 0 to 15. 
        num=random(0,16);
        LightTheNumbers(num);
    }
}
//LightTheNumbers take a parameter which is num and the function decide which led is open in the seven segment display.
void LightTheNumbers(int num)
{
  //Since we are working at the hexadecimal base, we receive the mode to start from zero if 16 large 
  num=num%16;
  //Decide which number is given and which led is open in the seven segment display.
  switch (num)
  {
    case 0:
      digitalWrite(1, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
    break;
    case 1:
      digitalWrite(3, HIGH);
      digitalWrite(5, HIGH);
      break;
    case 2:
      digitalWrite(1, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(2, HIGH);
      break;
    case 3:
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
    digitalWrite(8, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
      break;
    case 4:
      digitalWrite(7, HIGH);
      digitalWrite(5, HIGH);
    digitalWrite(8, HIGH);
      digitalWrite(3, HIGH);
      break;
    case 5:
      digitalWrite(2, HIGH);
      digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(6, HIGH);
      break;
    case 6:
      digitalWrite(2, HIGH);
      digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(1, HIGH);
      break;
    case 7:
      digitalWrite(3, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(5, HIGH);
      break;
    case 8:
      digitalWrite(1, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
      break;
     case 9:
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
      break;
     case 10:
    digitalWrite(1, HIGH);    
      digitalWrite(3, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
      break;
     case 11:
    digitalWrite(1, HIGH);    
      digitalWrite(3, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(2, HIGH);
      break;
     case 12:
    digitalWrite(1, HIGH);    
      digitalWrite(7, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(2, HIGH);
      break;
     case 13:
    digitalWrite(1, HIGH);    
      digitalWrite(5, HIGH);
      digitalWrite(2, HIGH);
        digitalWrite(8, HIGH);
      digitalWrite(3, HIGH);
      break;
    case 14:
    digitalWrite(1, HIGH);    
      digitalWrite(7, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(8, HIGH);
      break;
    case 15:
    digitalWrite(1, HIGH);    
      digitalWrite(7, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(8, HIGH);
      break;
  }
  delay(1000);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}
