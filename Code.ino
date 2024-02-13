#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);
#define sensor 2

const unsigned char zmaj [] PROGMEM = {
  // MD.NUR ISLAM
};

int rpm = 0;
//int pid;
unsigned long millisBefore;
volatile int objects;

void setup()
{
  Serial.begin(9600);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64).

  attachInterrupt(digitalPinToInterrupt(2), count, FALLING);
  delay(1000);
  display.clearDisplay();
  display.drawBitmap(0, 0,zmaj, 128, 64, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(22,10);
  display.println("mircemk");// Print text
  display.setCursor(10,40);
  display.println("RPM METER");
  display.display();
  delay(2000);
  pinMode(2, INPUT);
 
}
void loop()

{
      print_to_OLED();
  if (millis() - millisBefore > 1000) {
    rpm = (objects / 3.0)*60;
    objects = 0;
    millisBefore = millis();
    }
    delay(100);
    
    display.fillRect(0, 4, 128, 12,BLACK);
    display.fillRect(0,4, map(rpm, 0, 1000, 0, 128), 8,WHITE);
    display.display();
     }
    void print_to_OLED() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(13,20);
    display.println("RPM:"); 
    display.setCursor(70,45); 
    display.println(rpm);  
    display.display();
    }
  void count() {
  objects++;
}

//RPM
