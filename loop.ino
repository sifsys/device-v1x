
void loop() {

  if (WiFi.status() != WL_CONNECTED) {

    turnRGB(110, 170, 0, true); //yellow
    delay(500);
    Serial.print("..");
    turnRGB(255, 0, 0, false);
    delay(500);
  }
  else
  {


    communicationLoop();

    //laserDetection();
    sensors.requestTemperatures();
   // safetyLoop();
    waterFlowErrorLoop();
    controlPF();
    calculateWaterFlow();
    temperatureLoop();
    measureVoltageAndAmpier();
//        if (sensorsState == true)
//        {
//          if ((millis() - powerSensorPrevious) > 15000)
//          {
//    
//            digitalWrite(pumpRelayPin, HIGH);
//          }
//          else
//          {
//            sensorsLoop();
//          }
//        }
  }
}

//void sensorsLoop()
//{
//
//}
