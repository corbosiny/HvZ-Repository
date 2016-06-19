#include <SPI.h>

#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

int motorAPins[2] = {9, 11};
int motorBPins[2] = {10, 12};
int numMotors = 2;
int motorSpeeds[2];

int turnAdjustSpeed = 75;

int trigPin = 7;

int switchPinA = 4;
int switchPinB = 5;

int addresses = 0xF0F0F0F0E1LL;

int joyStickReadings[3];
int numReadings = 3;


bool paused = false;
bool turningOff = true;

int motorXDirection = 0;
int motorYDirection = 0;
int motorClick = 0;

RF24 radio(9, 10);

void setup() 
{

  radio.begin();
  radio.setAutoAck(1);
  radio.setRetries(10, 15);
  radio.openReadingPipe(1, addresses);

  for(int x; x < numMotors; x++)
  {

    pinMode(motorAPins[x], OUTPUT);
    pinMode(motorBPins[x], OUTPUT);
    
    digitalWrite(motorAPins[x], LOW);
    digitalWrite(motorBPins[x], LOW);
    
  }

  pinMode(switchPinA, OUTPUT);
  pinMode(switchPinB, OUTPUT);

  digitalWrite(switchPinA, HIGH);
  digitalWrite(switchPinB, LOW);

}

void loop() 
{

  while(digitalRead(switchPinB == LOW))
  {

    turningOff = true;

    if(radio.available())
    {

      radio.read(&joyStickReadings, sizeof(joyStickReadings));

      if(joyStickReadings[0] == 2000 && joyStickReadings[2] == 2000)
      {

        paused = true;

         for(int x = 0; x < numMotors; x++)
          {

            digitalWrite(motorAPins[x], LOW);
            digitalWrite(motorBPins[x], LOW);
            
          }
          
        while(joyStickReadings[0] != 2001 && joyStickReadings[2] != 2001)
        {

          if(radio.available())
          {

            radio.read(&joyStickReadings, sizeof(joyStickReadings));
            
          }
          
        }
        
      }

      if(paused == true)
      {

        paused = false;

        for(int y = 0; y < numReadings; y++)
        {

          joyStickReadings[y] = 512;
          
        }
        
      }
      
      if(joyStickReadings[0] > 600) 
      {
      
        motorXDirection = 1;
        motorSpeeds[0] = joyStickReadings[0] / 2;
      
      }
      else if(joyStickReadings[0] < 450) 
      {
      
        motorXDirection = -1; 
        motorSpeeds[0] = joyStickReadings[0];
    
      }
      else motorXDirection = 0;

      if(joyStickReadings[1] > 600) 
      {
      
        motorYDirection = 1;
        motorSpeeds[1] = joyStickReadings[1] / 2;
    
      }
      else if(joyStickReadings[1] < 450) 
      {
      
        motorYDirection = -1;
        motorSpeeds[1] = joyStickReadings[1];
    
      }
      else motorYDirection = 0;
    
      if(joyStickReadings[2] < 450) motorClick = 1;
      else motorClick = 0;

      if(motorClick == 0) fire();

      for(int y = 0; y < numMotors; y++)
      {

          motorSpeeds[y] = map(motorSpeeds[y], 0, 512, 0, 256);
          motorSpeeds[y] += ((joyStickReadings[2]/1024) * turnAdjustSpeed) * (motorYDirection * (y % 2));
       
        if(motorXDirection == 1)
        {

          digitalWrite(motorBPins[y], LOW);
          analogWrite(motorAPins[y], motorSpeeds[y]);
      
        }
       else if(motorXDirection == -1)
        {

          digitalWrite(motorAPins[y], LOW);
          analogWrite(motorBPins[y], motorSpeeds[y]);
        
        }
      }
  
    }

  }

  if(digitalRead(switchPinB == HIGH) && turningOff)
  {

    turningOff = false;

    for(int z = 0; z < numMotors; z++)
    {

      digitalWrite(motorAPins[z], LOW);
      digitalWrite(motorBPins[z], LOW);
      
    }
    
  }
    
}



void fire()
{

  digitalWrite(trigPin, HIGH);
  delay(100);
  digitalWrite(trigPin, LOW);

}

