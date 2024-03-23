/*
MIT License

Copyright (c) [2023] [TEL at @TELsBench channel on youtube]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef MyDisplay_h
#define MyDisplay_h

#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>             //Serial Peripheral Interface


class MyDisplay{

//AZ Delivery SPI - TFT-T7735 using  *AZ-DELIVERY ESP32-WROOM DEV KIT*
//===========================================
  private:
                                    //TOP TO BOTTOM
                                    //===============
                                    // ORANGE - LED 3.3V
                                    // YELLOW - SCK  GPIO_18
                                    // GREEN  - SDA  GPIO_23
    #define TFT_DC    GPIOR03       // BLUE   - AO   GPIO_2
    #define TFT_RST   GPIOR04       // purple  - RST GPIO_4
    #define TFT_CS    GPIOR05      // GRAY   - CS   GPIO_5
                                    // WHITE  - GND GND
                                    // BLACK  - VCC 3.3V
 
  Adafruit_ST7735 * tft;

  public:
    MyDisplay( );
    void clearScreen();
    void tftSetup();
    void showInstructions();
    void ShowCredits();
    void ShowStats(int pl1Won,int pl1Lost,int pl2Won, int pl2Lost);
    void ShowStartGotoNearestTAB();
    void ShowLostContinueToTAB(String tabPosition,int plyrNum);
    void ShowWon(int plyrNum);
    void ShowAdvanceToTAB(String tabPosition,int playerNum);
    void PrepCountDownScreen(int playerNum);
    void WriteCountdownValue(String outstandingSeconds);
    void MyDisplay::ShowLikeAndSubscribe();

 

};

#endif
