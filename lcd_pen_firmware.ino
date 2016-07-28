
#include <MsTimer2.h>
#include <LowPower.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define SSD1306_LCDHEIGHT 16
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#if (SSD1306_LCDHEIGHT != 16)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

//atmega2560
//It can't be any pin, look for interrupt pins on your board
//#define SWITCH_PIN 19 
//#define LCD_POWER_PIN 22 

//atmega328
#define SWITCH_PIN 2
#define LCD_POWER_PIN 9
#define SDA_PIN 27
#define SCL_PIN 28
#define ON 1
#define OFF 0
int counter = 0;
int counterCopy = 0;
int counterPrev = 0;

bool powerDown = false;
const char powerDownTimeout = 3;
char powerDownTime = 0;
unsigned long lastMillis = 0;
bool LCDEnabled = false;

void EnableLCD(bool enable)
{
  
  if(LCDEnabled==false && enable)
  {
    digitalWrite(LCD_POWER_PIN, ON);
    delay(300);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.display();
    LCDEnabled = enable;
  }
  else if(LCDEnabled == true && !enable)
  {
    LCDEnabled = enable;
    digitalWrite(LCD_POWER_PIN, OFF);
  }
}

void setup()   {     
    pinMode(LCD_POWER_PIN, OUTPUT);
    digitalWrite(LCD_POWER_PIN, OFF);
    pinMode(13, OUTPUT);
    digitalWrite(13, ON);

  MsTimer2::set(1000, onTimer2);
  MsTimer2::start();
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), onSwitch, FALLING);
  lastMillis = millis();

   
   EnableLCD(true);
   PrintValue(counter);   
}


void onSwitch()
{
  powerDownTime = 0;
  if(millis() - lastMillis > 100)
  {
    lastMillis = millis();
    counter++;
  }
}

void onTimer2()
{
  if(powerDownTime > powerDownTimeout)
  {
    powerDownTime = 0;
    powerDown = true;
  }
  else
  {
    powerDownTime++;
  }
}

void SetPowerDown()
{
    powerDown = false;
    digitalWrite(13, OFF);
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    digitalWrite(13, ON);
}

void PrintValue(int value)
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println(value);
    display.display();
}

void loop() {

   noInterrupts();
   counterCopy = counter;
   if(powerDown)
   {
    EnableLCD(false);
    SetPowerDown();
   }
   interrupts();

  if(counterPrev!=counterCopy)
  {
    EnableLCD(true);
    counterPrev = counterCopy;
    if(LCDEnabled)
    {
      PrintValue(counterCopy);
      counterPrev = counterCopy;
    }
    
  }
}

