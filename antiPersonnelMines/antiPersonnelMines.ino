#include <Servo.h>

Servo myServos[8];
int numServos = 8;

int startPin = 6;

int buttonPins[8] = {};
int numButtons = 8;

int firePosition = 180;
int resetPosition = 0;

int switchPinA = 2;
int switchPinB = 3;

int userInput;

void setup() 
{

  Serial.begin(9600);

  for(int x = 0; x < numServos; x++)
  {

    myServos[x].attach(startPin + x);
    
  }
  
  for(int y = 0; y < numButtons; y++)
  {

    pinMode(buttonPins[y], INPUT);
    
  }

  pinMode(switchPinA, OUTPUT);
  pinMode(switchPinB, OUTPUT);

  digitalWrite(switchPinA, HIGH);
  digitalWrite(switchPinB, LOW);

}

void loop() 
{

  for(int x = 0; x < numButtons; x++)
  {

    if(digitalRead(buttonPins[x]) == HIGH)
    {

      fire(x);
      delay(5);
      
    }
    
  }

  if(Serial.available())
  {

    userInput = Serial.read();

    if(userInput == 'r')
    {

      for(int z = 0; z < numServos; z++)
      {

        reset(z);
        
      }

    }
    else if(userInput - 48 >= 0 || userInput < 10)
    {

      reset(userInput - 48);

    }

  }
  
}

void fire(int motor)
{

  myServos[motor].write(firePosition);

}

void reset(int motor)
{

  myServos[motor].write(resetPosition);

}
