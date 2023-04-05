

void measureVoltageAndAmpier()
{
  // Read the data from the sensor
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();
  float energy = pzem.energy();
  float frequency = pzem.frequency();
  float pf = pzem.pf();
  supplyVoltage = floor(voltage);
  AmpsRMS = current;
  totalBill = energy * unitPrice;
  units = energy;
  pfVal = pf;
  powerOfPump = power;
  frequencyOfElectricity = frequency;
  //supplyVoltage,AmpsRMS
}

void controlPF()
{
  if (digitalRead(pumpRelayPin))
  {

    if ((pfVal * 100) < pfMinimum)
    {
      if ((millis() - pfPrevious) > (1000 * 600))
      {
        digitalWrite(pfPin, LOW);
      }
      else
      {
        digitalWrite(pfPin, HIGH);
      }
    }
    else
    {
      digitalWrite(pfPin, LOW);
    }
  }
  else
  {
    digitalWrite(pfPin, LOW);
  }

}
