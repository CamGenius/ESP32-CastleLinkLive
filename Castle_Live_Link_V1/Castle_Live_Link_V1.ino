#include <Arduino.h>
#include "heltec.h"
//#include <LoRa.h>

#define BAND    915E6

const uint8_t receiverInput = 12;
const uint8_t escPin = 13;

int timer;
bool ticked = false;

int currentState = 0;
int states[12];

int counter = 0;

void sendPacket(void * s){
      int* core2States = (int*)s;
      LoRa.beginPacket();
      LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
      for(int i = 1; i <= 11; i++)
      {
        LoRa.println(core2States[i]);
      }
      LoRa.endPacket();
      vTaskDelete(NULL);
}

void IRAM_ATTR escTick(){
  states[currentState] = micros() - timer;
  ticked = true;
  //Serial.println(states[currentState]);
  if(currentState == 11)
  {
    //Serial.println("11th Tick");
    counter++;
    if(counter == 4)
    {
      xTaskCreatePinnedToCore(sendPacket, "SendPacket", 1000, &states, 1, NULL, 1);
      counter = 0;
    }
  }
}

void IRAM_ATTR pwmChange(){
  if(digitalRead(receiverInput))
  {
    detachInterrupt(escPin);
    pinMode(escPin, OUTPUT);
    digitalWrite(escPin, LOW);
    if(!ticked)
    {
      currentState = 0;
    }
  }
  else
  {
    digitalWrite(escPin, HIGH);
    pinMode(escPin, INPUT);
    attachInterrupt(escPin, escTick, FALLING);
    timer = micros();
    currentState += 1;
    ticked = false;
  }
}

void setup() {
  Heltec.begin(false, true, true, true, BAND);
  pinMode(receiverInput, INPUT);
  pinMode(escPin, OUTPUT);
  digitalWrite(escPin, HIGH);
  attachInterrupt(receiverInput, pwmChange, CHANGE);
}

void loop() {
}
