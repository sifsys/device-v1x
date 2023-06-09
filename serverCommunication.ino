

void readRequestData()
{
  httpRequestData = "pump_id= " + String(pumpID)
                    + "&status= " + String(digitalRead(pumpRelayPin))
                    + "&sensor= " + String(digitalRead(warningDevicePin))
                    + "&waterflow= " + String(currentFlowRate)
                    + "&volt= " + String(supplyVoltage)
                    + "&amp= " + String(AmpsRMS)
                    + "&unit= " + String(units)
                    + "&temp= " + String(getTempMeasurement(PinMainTemp))
                    + "&development= " + String(digitalRead(developmentPin))
                    + "&pf= " + String(pfVal * 100)
                    + "&load= " + String(powerOfPump)
                    + "&frequency= " + String(frequencyOfElectricity)
                    + "&extraSwitch= " + String(digitalRead(extraSwitchPin))
                    + "&needRestart= " + String(needRestart)
                    + "&step=" + condStep
                    + "&error= " + createError();
}
void communicationLoop()
{

  httpRequestData = "pump_id= " + String(pumpID);
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {

      readRequestData();
      Readings = httpPOSTRequest(serverName, httpRequestData);
      //Serial.println(Readings);
      JSONVar myObject = JSON.parse(Readings);

      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }

      //Serial.print("JSON object = ");
      Serial.println(myObject);

    if (myObject.hasOwnProperty("step")) 
    {
      
      condStep = (int) myObject["step"];
      //Serial.print("Current model is: ");
      //Serial.println(model);
    }
    
    if (myObject.hasOwnProperty("maxFlowRate")) 
    {
      
      maxFlowRate = (double) myObject["maxFlowRate"];
      //Serial.print("max wtter Flow Rate to be 100% is: ");
      //Serial.println(maxFlowRate);
    }
    
    if (myObject.hasOwnProperty("status")) 
    {
      
      powerPump = (int) myObject["status"];
      //Serial.print("Pump Status is: ");
      //Serial.println(powerPump);
    }
    
    if (myObject.hasOwnProperty("sensor")) 
    {
      sensorStatus = (int) myObject["sensor"];
//      Serial.print("Sensor Status is: ");
//      Serial.println(sensorStatus);
    }
   
    if (myObject.hasOwnProperty("rain")) 
    {
      maxRainPercentage = (int) myObject["rain"];
//      Serial.print("Max rain value is: ");
//      Serial.println(maxRainPercentage);
    }    
    if (myObject.hasOwnProperty("pf")) 
    {
      pfMinimum = (int) myObject["pf"];
//      Serial.print("pfMinimum value is: ");
//      Serial.println(pfMinimum);
    }
    if (myObject.hasOwnProperty("Vmax"))
    {
      max_volt = (int) myObject["Vmax"];
//      Serial.print("Maximum Voltage is: ");
//      Serial.println(max_volt);
    }
    if (myObject.hasOwnProperty("Vmin"))
    {
      min_volt = (int) myObject["Vmin"];
//      Serial.print("Minumum Voltage is: ");
//      Serial.println(min_volt);
    }
    if (myObject.hasOwnProperty("AMPmin"))
    {
      min_ampier = (int) myObject["AMPmin"];
//      Serial.print("Minumum Ampier is: ");
//      Serial.println(min_ampier);
    }
    if (myObject.hasOwnProperty("Vmax"))
    {
      max_ampier = (int) myObject["Vmax"];
//      Serial.print("Maximum Ampier is: ");
//      Serial.println(max_ampier);
    }
    if (myObject.hasOwnProperty("TempMax"))
    {
      maxTempToTurnOffPump = (int) myObject["TempMax"];
//      Serial.print("Maximum Temperature is: ");
//      Serial.println(maxTempToTurnOffPump);
    }
    if (myObject.hasOwnProperty("minFlow"))
    {
      minimumFlowRate = (int) myObject["minFlow"];
//      Serial.print("MInimum Water Flow rate is: ");
//      Serial.println(minimumFlowRate);
    }

    if (myObject.hasOwnProperty("extraSwitch"))
    {
      extraSwitch = (int) myObject["extraSwitch"];
//      Serial.print("MInimum Water Flow rate is: ");
//      Serial.println(minimumFlowRate);
    }
    if (myObject.hasOwnProperty("reboot"))
    {
      reboot = (int) myObject["reboot"];
//      Serial.print("Reboot clearance: ");
//      Serial.println(reboot);
    }

    if(needRestart == 1 && reboot == 1){
       esp_restart();
    }
    if(extraSwitch ==1 ){
       digitalWrite(extraSwitchPin, HIGH);
    }else{
      digitalWrite(extraSwitchPin, LOW);
    }


      if(sensorStatus == 1 ){
        
        digitalWrite(warningDevicePin, HIGH);
        digitalWrite(buzzerPin, HIGH);
//        delay(500);
//        digitalWrite(buzzerPin, LOW);
//        delay(500);
      }
      
      if(powerPump == 1 ){
        
        digitalWrite(warningDevicePin, LOW);
        digitalWrite(buzzerPin, LOW);
      }
      
      
      if (powerPump == 1)
      {
        if (isError == false)
        {
          if (pTInit == true)
          {
            pTInit = false;

            waterFlowWaitingState = true;
            pTforWF = millis();
          }
          digitalWrite(pumpRelayPin, HIGH);
          digitalWrite(warningDevicePin, LOW);
        }

        serverLag = false;
      }
      else if (powerPump == 0)
      {
        digitalWrite(pumpRelayPin, LOW);
        serverLag = false;
      }
      else
      {
        serverLag = true;
        Serial.println("ErrorChecked");
      }

    }
    else {

    }
    lastTime = millis();
  }
}
