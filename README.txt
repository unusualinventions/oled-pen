1. Install arduino Pro mini on a bread board, configure it to work with internal oscillator
http://www.instructables.com/id/Atmega-Standalone-Running-without-crystal-oscillat/

Or see short instruction at file "how to configure arduino 328 on 8 MHz internal clock.txt"

2. Install OLED display on a bread board, install libraries to work with display
http://www.instructables.com/id/Monochrome-096-i2c-OLED-display-with-arduino-SSD13/step3/Libraries/

3. Configure arduino libraries for OLED display
Uncomment line at C:\Program Files (x86)\Arduino\libraries\Adafruit_SSD1306\Adafruit_SSD1306.h
line  #define SSD1306_96_16

4. Install additional arduino libraries
MsTimer2
LowPower
5. Burn firmware to arduino
