#include "Adafruit_LEDBackpack.h"
#include <Wire.h>

int fourdigitTime;
Adafruit_7segment matrix = Adafruit_7segment();
char buf[5];
int TZCalc = 800;
boolean TZMinus = true;

void setup()  
{
  matrix.begin(0x70); 
  fourdigitTime = 0; 
  Serial.begin(9600);
}

void loop()                     // run over and over again
{
  matrix.drawColon(false);
  matrix.writeDisplay();
  system("/home/root/time.sh > /home/root/time.txt");
  FILE *fp;
  fp = fopen("/home/root/time.txt", "r");
  fgets(buf, 5, fp);
  fclose(fp);
  system("rm /home/root/time.txt");
  delay(1000);
  int fourdigitTime = atoi(buf);

  if (TZMinus = true)
  {

    if ((fourdigitTime - TZCalc) < 0)
    {
      fourdigitTime = (fourdigitTime - TZCalc + 2400);
    } 
    if ((fourdigitTime - TZCalc) > 0)
    {
      fourdigitTime = (fourdigitTime - TZCalc);
    }
  }
  if (TZMinus = false)
  {

    if ((fourdigitTime + TZCalc) >= 2400 )
    {
      fourdigitTime = (fourdigitTime + TZCalc - 2400);
    } 
    if ((fourdigitTime + TZCalc) < 2400)
    {
      fourdigitTime = (fourdigitTime + TZCalc);
    }
  }

  Serial.println(fourdigitTime);
  matrix.print(fourdigitTime);

  matrix.drawColon(true);
  matrix.writeDisplay();
  delay(1000);
  matrix.setBrightness(10);

}



