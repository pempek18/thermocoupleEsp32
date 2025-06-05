#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define OLED_SDA 21
#define OLED_SCL 22

class Dsp {
    public:
        Dsp();
        void setup();
        void clear();
        void print(String text);
    private:
        int x;
        Adafruit_SH1106 dsp;
};