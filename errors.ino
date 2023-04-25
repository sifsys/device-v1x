String createError()
{
  if (max_volt < supplyVoltage)
  {
    error[0] = "hvolt,";
    turnRGB(170, 0, 0, true);
    longTimeBuzzer();
    turnOffPump();
  }
  else if (supplyVoltage < min_volt & supplyVoltage != 0)
  {
    error[0] = "lvolt,";
    turnRGB(170, 0, 0, true);
    longTimeBuzzer();
    turnOffPump();
  }
  else
  {
    error[0] = "";
  }
  if (max_ampier < AmpsRMS)
  {
    error[1] = "hAmps,";
    turnOffPump();
    longTimeBuzzer();
    turnRGB(170, 0, 0, true);
  }
  else if (float(min_ampier) > AmpsRMS & AmpsRMS != 0)
  {
    error[1] = "lAmps,";
    turnOffPump();
    longTimeBuzzer();
    turnRGB(170, 0, 0, true);
  }
  else
  {
    error[1] = "";
  }


  if (maxTempToTurnOffPump < getTempMeasurement(PinMainTemp))
  {
    error[3] = "Temp,";
    turnOffPump();
    turnRGB(170, 0, 0, true);
  }
  else
  {
    error[3] = "";
  }

  
  if (getRainPercentage() > maxRainPercentage)
  {
    error[5] = "rain,";
    turnOffPump();
    turnRGB(170, 0, 0, true);
    delay(500);
    turnRGB(170, 0, 0, false);
    delay(500);
  }
  else
  {
    error[5]="";
  }


  for (int i = 0; i < 10; i++)
  {
    if (error[i] != "")
    {
      i = i + (11 - i);
      if (digitalRead(developmentPin) == LOW)
      {
        isError = true;
      }
      else
      {
        isError = false;
      }
    }
    else
    {
      isError = false;
    }
  }

  return (error[0] + error[1] + error[2] + error[3] + error[4] + error[5] + error[6] );
}
