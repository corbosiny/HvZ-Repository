#include <Servo.h>

Servo myServos[5];
int numServos = 5;
int starterPin = 6;

int sensorPins[5] = {A0, A1, A2, A3, A4};
int numSensors = 5;
int sensorReadings[5];
int distance;

int firePosition = 180;
int resetPosition = 0;

int switchPinA = 2;
int switchPinB = 3;

char userInput;

void setup() 
{

  Serial.begin(9600);
  
  for(int x = 0; x < numServos; x++)
  {

    myServos[x].attach(starterPin + x);
    
  }

  pinMode(switchPinA, OUTPUT);
  pinMode(switchPinB, OUTPUT);

  digitalWrite(switchPinA, HIGH);
  digitalWrite(switchPinB, LOW);

}

void loop()
{

  while(digitalRead(switchPinB) == LOW)
  {
    
      for(int z = 0; z < numSensors; z++)
      {

        sensorReadings[z] = takeAverageSensorReading(z, 3, 10);
        distance = readingToDistance(sensorReadings[z]);

        if(distance < 25 && distance != 0)
        {

          fire(z);
      
        }
    
      }

  }

  if(Serial.available())
  {

    userInput = Serial.read();

    if(userInput == 'r')
    {

      for(int r = 0; r < numServos; r++)
      {

          reset(r);
        
      }
            
    }

    else if(userInput - 48 < 10 && userInput - 48 >= 0)
    {

         reset(userInput - 48);
      
    }
    
  }

}

int takeAverageSensorReading(int numSensor, int samples, int delayTime)
{

  int totalReading = 0;

  for(int i = 0; i < samples; i++)
  {

    totalReading += analogRead(sensorPins[numSensor]);
    delay(delayTime);
    
  }

  return totalReading / 3;

}

int readingToDistance(int reading)
{

  int distanceConversion = (6787 / (reading - 3)) - 4;

  return distanceConversion;

}

void fire(int motor)
{

  myServos[motor].write(firePosition);

}

void reset(int motor)
{

  myServos[motor].write(resetPosition);

}
