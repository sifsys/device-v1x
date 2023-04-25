
void turnRGB(int r, int g, int b, boolean state)
{
  if (state)
  {

    analogWrite(redP, r);
    analogWrite(greenP, g);
    analogWrite(blueP, b);
  }
  else
  {
    analogWrite(redP, 0);
    analogWrite(greenP, 0);
    analogWrite(blueP, 0);
    delay(500);
    analogWrite(redP, r);
    analogWrite(greenP, g);
    analogWrite(blueP, b);
    delay(500);
  }
}
