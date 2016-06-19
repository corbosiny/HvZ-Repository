#include <SPI.h>

#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

int addresses = 0xF0F0F0F0E1LL;

int pauseButtonTrig = 4;
int pauseButton = 5;

int numReadings = 3;

bool paused = false;

int joyStickReadings[3];

RF24 radio(9, 10);

void setup() 
{

  radio.begin();
  radio.setAutoAck(1);
  radio.setRetries(15, 20);
  radio.openWritingPipe(addresses);

  pinMode(pauseButtonTrig, OUTPUT);
  pinMode(pauseButton, OUTPUT);

  digitalWrite(pauseButtonTrig, HIGH);
  digitalWrite(pauseButton, LOW);

}

void loop() 
{

  if(digitalRead(pauseButton == HIGH) && !paused)
  {

    paused = true;

    for(int x = 0; x < numReadings; x++)
    {

      joyStickReadings[x] = 2000;
      
    }

    radio.write(&joyStickReadings, sizeof(joyStickReadings));
    
    while(digitalRead(pauseButton) == HIGH)
    {

      
    }
  
  }
  else if(digitalRead(pauseButton == HIGH) && paused)
  {

    paused = false;
  
    for(int y = 0; y < numReadings; y++)
    {

      joyStickReadings[y] = 2001;
      
    }

    radio.write(&joyStickReadings, sizeof(joyStickReadings));

    while(digitalRead(pauseButton) == HIGH)
    {

      
    }
    
  }

}
