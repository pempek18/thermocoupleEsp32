#include "Dsp.h"

Dsp::Dsp()
{
  dsp = Adafruit_SH1106(5);
}

void Dsp::setup()
{
  dsp.begin(SH1106_SWITCHCAPVCC, 0x3C, false);
  dsp.clearDisplay();
  dsp.display();
  dsp.setTextSize(2);
  dsp.setTextColor(WHITE);
  dsp.setCursor(0, 0);
  // Display static text
  dsp.println("Temperatura");
  dsp.println("00.00°C");
  dsp.display();
  delay(1000);    
}

void Dsp::print(String text)
{
    dsp.clearDisplay();
    dsp.setCursor(0, 0);
    dsp.print(text);
    dsp.display();
}

void Dsp::clear()
{
    dsp.clearDisplay();
    dsp.display();
}