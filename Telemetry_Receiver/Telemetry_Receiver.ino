#include "heltec.h" 
#include "BluetoothSerial.h"

#define BAND    915E6

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

String packetString;
int packetData[11];

int beginIndex;
int endIndex;

double voltage;
double rippleVoltage;
double current;
double throttle;
double outputPower;
double RPM;
double becVoltage;
double becCurrent;
double temperature;

void setup() {
  Heltec.begin(false, true, true, true, BAND);//Display, LoRa, Serial, PABOOST, Band
  
  /*Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);

  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->drawString(0, 10, "Wait for incoming data...");
  Heltec.display->display();*/

  LoRa.onReceive(receivedData);

  LoRa.receive();

  //Serial.begin(115200);
  SerialBT.begin("CastleLinkLive");
}

void loop() {
  parseData();
  sendBluetooth();
  delay(1000);
}

void receivedData(int packetSize)
{
  //Serial.println("Start of Received Data");

  packetString = "";
  for(int i = 0; i < packetSize; i++)
  {
    packetString += (char)LoRa.read();
  }
  beginIndex = 0;
  endIndex = packetString.indexOf('\n');
  for(int j = 0; j < 11; j++)
  {
    packetData[j] = packetString.substring(beginIndex, endIndex).toInt();
    beginIndex = packetString.indexOf('\n', endIndex);
    endIndex = packetString.indexOf('\n', beginIndex+1);
  }
  
  /*Serial.print("Voltage: ");
  Serial.println(voltage);
  Serial.print("Ripple Voltage: ");
  Serial.println(rippleVoltage);
  Serial.print("Current: ");
  Serial.println(current);
  Serial.print("Throttle: ");
  Serial.println(throttle);
  Serial.print("Output Power: ");
  Serial.println(outputPower);
  Serial.print("RPM's: ");
  Serial.println(RPM);
  Serial.print("BEC Voltage: ");
  Serial.println(becVoltage);
  Serial.print("BEC Current: ");
  Serial.println(becCurrent);
  Serial.print("Temperature (F): ");
  Serial.println(temperature);
  Serial.println("End of Data");*/

}

void sendBluetooth()
{
  SerialBT.print("Voltage: ");
  SerialBT.println(voltage);
  SerialBT.print("Ripple Voltage: ");
  SerialBT.println(rippleVoltage);
  SerialBT.print("Current: ");
  SerialBT.println(current);
  SerialBT.print("Throttle: ");
  SerialBT.println(throttle);
  SerialBT.print("Output Power: ");
  SerialBT.println(outputPower);
  SerialBT.print("RPM's: ");
  SerialBT.println(RPM);
  SerialBT.print("BEC Voltage: ");
  SerialBT.println(becVoltage);
  SerialBT.print("BEC Current: ");
  SerialBT.println(becCurrent);
  SerialBT.print("Temperature (F): ");
  SerialBT.println(temperature);
}

void parseData()
{
  voltage = ((((double)map(packetData[1], packetData[10], packetData[0], 500, 1000)) / 1000) - 0.5) * 20;
  rippleVoltage = ((((double)map(packetData[2], packetData[10], packetData[0], 500, 1000)) / 1000) - 0.5) * 4;
  current = ((((double)map(packetData[3], packetData[10], packetData[0], 500, 1000)) / 1000) - 0.5) * 50;
  throttle = ((((double)map(packetData[4], packetData[10], packetData[0], 500, 1000)) / 1000) - 0.5);
  outputPower = ((((double)map(packetData[5], packetData[10], packetData[0], 500, 1000)) / 1000) - 0.5) * 0.2502;
  RPM = ((((double)map(packetData[6], packetData[10], packetData[0], 500, 1000)) / 1000) - 0.5) * 20416.7;
  becVoltage = ((((double)map(packetData[7], packetData[10], packetData[0], 500, 1000)) / 1000) - 0.5) * 4;
  becCurrent = ((((double)map(packetData[8], packetData[10], packetData[0], 500, 1000)) / 1000) - 0.5) * 4;
  temperature = ((((((double)map(packetData[9], packetData[10], packetData[0], 500, 1000)) / 1000) - 0.5) * 30) * 1.8) + 32;
}
