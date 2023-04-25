void turnOffPump()
{
  if (digitalRead(developmentPin) == LOW)
  {
    digitalWrite(pumpRelayPin, LOW);
  }
}

void warning()
{

    if(warningDevice == 1 && pumpRelayPin == LOW){
      digitalWrite(warningDevicePin, HIGH);
    }else {
      digitalWrite(warningDevicePin, LOW);
    }
  
}


//float getDistance()
//{
//  digitalWrite(hcsr04TrigPin, LOW);
//  delayMicroseconds(5);
//  digitalWrite(hcsr04TrigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(hcsr04TrigPin, LOW);
// 
//  pinMode(hcsr04EchoPin, INPUT);
//  float duration = pulseIn(hcsr04EchoPin, HIGH);
// 
//  // Convert the time into a distance
//  float cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
//  return(cm);
//}

//void laserDetection()
//{
//  if(analogRead(laserPin) > laserBrightness)
//  {
//    laserState=0;
//  }
//  else
//  {
//    laserState=1;
//  }
//}

int getRainPercentage()
{
  return(map(analogRead(rainSensorPin),0, 4095,100,-1));
  //return(analogRead(rainSensorPin));
}

int previousMillisB=0, differenceB=0;
void longTimeBuzzer()
{
  if(millis()-previousMillisB>5000)
  {
    previousMillis=millis();
    digitalWrite(buzzerPin,HIGH);
    delay(500);
    
    digitalWrite(buzzerPin,LOW);
  }
}

//void safetyLoop()
//{
//  if (laserState == 1)
//  {
//    error[6] = "laser";
//    turnOffPump();
//    digitalWrite(buzzerPin, HIGH);
//    turnRGB(170, 0, 0, true);
//    delay(500);
//    turnRGB(170, 0, 0, false);
//    digitalWrite(buzzerPin, LOW);
//    delay(500);
//  }
//  else
//  {
//    error[6] = "";
//  } 
//  if (getDistance() < maxDistanceToDetect)
//  {
//    error[2] = "ultra,";
//    turnOffPump();
//    digitalWrite(buzzerPin, HIGH);
//    turnRGB(170, 0, 0, true);
//    delay(500);
//    turnRGB(170, 0, 0, false);
//    digitalWrite(buzzerPin, LOW);
//    delay(500);
//  }
//  else
//  {
//    error[2] = "";
//  }

//}
