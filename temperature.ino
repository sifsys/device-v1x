


float getTempMeasurement(int PIN_DS18B20)
{
  float tempC=sensors.getTempCByIndex(PIN_DS18B20);
  return (tempC);
}
void temperatureLoop()
{
  if (getTempMeasurement(boardTemperaturePin) > maxBoardTemp)
  {
    digitalWrite(fanPin, HIGH);
  }
  else if(getTempMeasurement(boardTemperaturePin)<maxBoardTemp-2)
  {
    digitalWrite(fanPin, LOW);
  }
}
