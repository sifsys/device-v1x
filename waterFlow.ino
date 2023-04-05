int waterFlowErrorTimer = 0;
int waterFlowErrorPrev = 0;

void calculateWaterFlow()
{
  currentMillis = millis();
  if ((currentMillis - previousMillis) > interval)
  {
    pulse1Sec = pulseCount;
    pulseCount = 0;

    flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    previousMillis = millis();

    flowMilliLitres = (flowRate / 60) * 1000;

    totalMilliLitres += flowMilliLitres;

    currentFlowRate = floor(100 * (flowRate / maxFlowRate));

    printOnSerial();
  }
}


void waitForFlowTimer()
{
  //  if (previousStateForWF == false)
  //  {
  //    previousStateForWF = true;
  //    previousMillisForWF = millis();
  //  }
  //  differenceMillisForWF = millis() - previousMillisForWF;
  //  if (differenceMillisForWF > 20000)
  //  {
  //    Serial.println("PUMP Off");
  //    turnOffPump();
  //  }
  //  else
  //  {
  //    waterFlowErrorPrev = millis();
  //    Serial.println(differenceMillisForWF);
  //    waterFlowErrorTimer = 1;
  //  }


}

boolean pTstateForWE = false;
int pTstateForWEtime = 0;
void waterFlowErrorLoop()
{
  if (waterFlowWaitingState == true)
  {
    if (digitalRead(pumpRelayPin) == HIGH)
    {
      if (currentFlowRate < minimumFlowRate)
      {
        if ((millis() - pTforWF) > 20000)
        {
          turnOffPump();
          if ( pTstateForWE == false)
          {
            pTstateForWE = true;
            pTstateForWEtime = millis();
          }

        }
        else
        {
          Serial.println(millis() - pTforWF);
        }
      }
      else
      {
        error[4] = "";
        waterFlowWaitingState = false;
        pTstateForWE = false;
        pTInit = true;
      }
    }
    if (pTstateForWE == true)
    {

      if ((millis() - pTstateForWEtime) > 15000)
      {
        error[4] = "";
        waterFlowWaitingState = false;
        pTstateForWE = false;
        pTInit = true;
      }
      else
      {
        Serial.println((millis() - pTstateForWEtime));
        error[4] = "waterflow,";
      }
    }
  }



  //
  //  if (currentFlowRate < minimumFlowRate & digitalRead(pumpRelayPin) == HIGH)
  //  {
  //    if (waterFlowWaitingState == false)
  //    {
  //
  //      Serial.println("PUMP Off");
  //      error[4] = "waterflow,";
  //      turnOffPump();
  //      digitalWrite(buzzerPin, HIGH);
  //      turnRGB(170, 0, 0, true);
  //      delay(500);
  //      turnRGB(170, 0, 0, false);
  //      digitalWrite(buzzerPin, LOW);
  //      delay(500);
  //    }
  //    else
  //    {
  //      waitForFlowTimer();
  //    }
  //  }
  //  else if (currentFlowRate < minimumFlowRate & digitalRead(pumpRelayPin) == LOW)
  //  {
  //    if (waterFlowErrorTimer == 1)
  //    {
  //
  //      if ((millis() - waterFlowErrorPrev) > 15000)
  //      {
  //        error[4] = "";
  //        waterFlowErrorTimer=0;
  //      }
  //      else
  //      {
  //        error[4] = "waterflow,";
  //        digitalWrite(buzzerPin, HIGH);
  //        turnRGB(170, 0, 0, true);
  //        delay(500);
  //        turnRGB(170, 0, 0, false);
  //        digitalWrite(buzzerPin, LOW);
  //        delay(500);
  //      }
  //    }
  //  }
  //  else if (currentFlowRate > minimumFlowRate)
  //  {
  //    previousStateForWF = false;
  //    previousMillisForWF = 0;
  //    error[4] = "";
  //  }
}
