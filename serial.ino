void printOnSerial()
{
    Serial.print("Flow rate: ");
    Serial.print(flowRate, 2);
    Serial.print("L/min");
    Serial.print("\t");

    Serial.print("Output Liquid Quantity: ");
    Serial.print(totalMilliLitres);
    Serial.print("mL / ");
    Serial.print(totalMilliLitres / 1000);
    Serial.println("L");

    Serial.println("Output: " + String(floor(100 * flowRate / maxFlowRate)) + "%");
    Serial.println("Development: " + String(digitalRead(developmentPin)));
    Serial.println("Temp: " + String(getTempMeasurement(PinMainTemp)));
    Serial.println("Voltage: " + String(supplyVoltage));
    Serial.println("Ampier: " + String(AmpsRMS));
    Serial.println("PUMP: " + String(digitalRead(pumpRelayPin)));

    Serial.println("Bills: "+String(totalBill)+" BDT");
    Serial.println("Board Temperature: "+String(getTempMeasurement(boardTemperaturePin)));
    Serial.println("Main Temperature: "+String(getTempMeasurement(PinMainTemp)));

    Serial.println("Rain: "+String(getRainPercentage()));
          //Serial.println("LaserState: " + String(laserState));
    Serial.println("Error: "+error[0] + error[1] + error[2] + error[3] + error[4] + error[5] + error[6] );
    Serial.println("is error? = "+ String(isError));
    Serial.println("Development: "+ String(digitalRead(developmentPin)));
          // Serial.println("Distance: " + String(getDistance()));
    Serial.println("//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
//Serial.println('pfvalue is: ');
//Serial.println(pfVal);
}
