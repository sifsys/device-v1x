#include <Arduino.h>
#include <analogWrite.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <assert.h>

//const char* ssid = "High Tech Park Authority";
//const char* password = "12345678";
//const char* ssid = "MyLightHost";
//const char* password = "fig8me912";
const char* ssid = "SiF";
const char* password = "sif.systems";

String serverName = "http://sifsys.com/api/device/pump/response";
//String serverName = "http://sif.systems/p.php";

String Readings;
float ReadingsArr[5];

int model;
int condStep;

const int pumpID = 1;

//////////Error fixing////////
const int maxReboots = 5;
int rebootCounter = 0;
int needRestart = 0;
int reboot = 0;
//////////////////////////////

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 15


//int maxDistanceToDetect=150;
//int hcsr04TrigPin = 12;    // Trigger
//int hcsr04EchoPin = 13;    // Echo

int extraSwitchPin = 21;
int extraSwitch = 0;
int developmentPin = 26;
int warningDevicePin = 23;
//JSONVar powerPump;
// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

#define pumpRelayPin 12
int powerPump;
String error[10] = {"", "", "", "", "", "", "", "", "", ""};
boolean isError = false;
#include <PZEM004Tv30.h>

#define PZEM_RX_PIN 16
#define PZEM_TX_PIN 17
#define PZEM_SERIAL Serial2
//#define CONSOLE_SERIAL Serial
PZEM004Tv30 pzem(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN);

// Create an instance

double AmpsRMS = 0;
//double unitPrice = 5.00;
//double totalBill = 0.00;
float max_volt = 250, min_volt = 150;
float max_ampier = 31, min_ampier = 0.20;

float powerOfPump, frequencyOfElectricity;
float supplyVoltage;


int fanPin = 32, boardTemperaturePin = 0;

float maxBoardTemp = 36.0;
int warningDevice;

float maxTempToTurnOffPump = 80.0;
int PinMainTemp = 1;

const int temp = 15;


//#define ADC_VREF_mV    3300.0 // in millivolt
//#define ADC_RESOLUTION 4096.0

#define LED_BUILTIN 2
#define waterFlowPin  27

long currentMillis = 0;
long previousMillis = 0;
int interval = 1500;
boolean ledState = LOW;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
float maxFlowRate = 4.44, minimumFlowRate = 0.0, currentFlowRate = 0;
float units;


String varNames[50];
String varValues[50];

//int getObjectValSerial(String objName)
//{
//  int finalText = 50;
//  for (int y = 0; y < 50; y++)
//  {
//    if (varNames[y] == objName)
//    {
//
//      finalText = y;
//    }
//  }
//  return (finalText);
//}

int rainSensorPin = 34;
int maxRainPercentage = 50;
int sensorStatus; // whether the server asking for start the sensor switch. details at serverCommunication page.


int redP = 5, greenP = 18, blueP = 19;
//int redC = 0, greenC = 0, blueC = 0;



// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;


String httpRequestData = "";
String httpPOSTRequest(String serverName, String httpRequestData)
{
  WiFiClient client;
  HTTPClient http;
  http.begin(client, serverName);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST(httpRequestData);

  String payload = "{}";

  if (httpResponseCode == 200)
  {
    //Serial.print("HTTP Response code: ");
    //Serial.println(httpResponseCode);
    payload = http.getString();
    //digitalWrite(indicatorLED, HIGH);
    if (isError==false)
    {
      if(digitalRead(developmentPin)==LOW)
      {
        
        turnRGB(0, 255, 0, true);
      }
      else
      {
        turnRGB(0, 0, 200, true);
      }
    }
  }
  else
  {
    //digitalWrite(indicatorLED, LOW);

    turnRGB(0, 255, 0, false);
    Serial.print("http code is: ");
    Serial.println(httpResponseCode);
  }
  return payload;
}
int buzzerPin = 25;
boolean serverLag=false;

int pTforWF=0;
boolean pTInit=true;

//int laserPin=35;
//int laserBrightness=3900, laserState=0;

boolean waterFlowWaitingState=false;

boolean previousStateForWF=false;
int previousMillisForWF = 0, differenceMillisForWF=0;

int pfMinimum=95, pfPin=4, pfPrevious=0;
float pfVal=1;

//int powerRelayForSensors=23;
//boolean sensorsState=false;
//
//int powerSensorPreviousState=0, powerSensorPrevious=0;
