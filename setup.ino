

// Mention pin Number insted of 0 where you want to get output (HIGH/LOW)
//

void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}

void setup() {

  pinMode (pumpRelayPin, OUTPUT);
  Serial.begin(115200);

  pinMode(pfPin, OUTPUT);
//  pinMode(powerRelayForSensors,OUTPUT);

  pinMode(redP, OUTPUT);
  pinMode(greenP, OUTPUT);
  pinMode(blueP, OUTPUT);
  pinMode(warningDevicePin, OUTPUT);
  pinMode(extraSwitchPin, OUTPUT);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    turnRGB(110, 170, 0, true); //yellow
    delay(500);
    Serial.print("..");
    turnRGB(255, 0, 0, true);
    delay(500);
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");

  pinMode(fanPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(waterFlowPin, INPUT_PULLUP);

  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;
  //pinMode(laserPin, INPUT);
  //pinMode(25, INPUT);



  Serial.println("Started 1");
  attachInterrupt(digitalPinToInterrupt(waterFlowPin), pulseCounter, FALLING);
  Serial.println("Started 2");

  pinMode(developmentPin, INPUT_PULLUP);


  //pinMode(hcsr04TrigPin, OUTPUT);
 // pinMode(hcsr04EchoPin, INPUT);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

}
