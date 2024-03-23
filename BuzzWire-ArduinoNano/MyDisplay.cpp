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

#include <Adafruit_GFX.h>    // Core graphics library
#include "MyDisplay.h"

MyDisplay::MyDisplay()
{
 tft = new ::Adafruit_ST7735(TFT_CS,TFT_DC,TFT_RST);
}

void MyDisplay::clearScreen()
{   
    tft->fillScreen(ST7735_BLACK);
}

void MyDisplay::tftSetup()
{  
 tft->initR(INITR_BLACKTAB);
 tft->setRotation(3);
 tft->fillScreen(ST7735_BLACK);
 tft->setTextWrap(true);
 tft->setTextColor(ST7735_CYAN, ST7735_BLACK);
}

void MyDisplay::ShowCredits()
{
    clearScreen();
    tft->setTextWrap(false);
    tft->setCursor(0,0);
    tft->setTextSize(2);
    tft->setTextColor(ST7735_GREEN);
    tft->print("TEL@TELsBENCH");
    tft->setCursor(0,16);
    tft->print("-------------");
    tft->setCursor(46,40);
    tft->print("By TEL");
    tft->setCursor(21,70);
    tft->print("March 2024");
   
}


void MyDisplay::ShowLikeAndSubscribe()
{
    clearScreen();
    tft->setTextWrap(false);
    tft->setCursor(0,0);
    tft->setTextSize(2);
    tft->setTextColor(ST7735_GREEN);
    tft->print("TEL@TELsBENCH");
    tft->setCursor(0,16);
    tft->print("-------------");
    tft->setCursor(46,40);
    tft->print("LIKE &");
    tft->setCursor(10,70);
    tft->print("SUBSCRIBE !");
   
}

void MyDisplay::showInstructions()
{
    clearScreen();
    tft->setTextWrap(true);
    tft->setTextSize(2);
    tft->setTextColor(ST7735_GREEN);
    tft->setCursor(20,0);
    tft->print("BUZZ GAME");
    tft->setCursor(20,16);
    tft->print("---------");
    tft->setCursor(0,27);
    tft->print("Get from one TAB to other with no wire Touch/Buzz.");
    tft->setTextWrap(false);
}

void MyDisplay::ShowStats(int pl1Won,int pl1Lost,int pl2Won, int pl2Lost)
{

    clearScreen();
    tft->setTextSize(2);
    tft->setTextColor(ST7735_GREEN);
    tft->setCursor(10,0);
    tft->print("GAME SCORES");
    tft->setCursor(5,16);
    tft->print("------------");
    
    //tft->setTextSize(1);
    //COLUMN HEADERS
    tft->setCursor(43,35);
    tft->setTextColor(ST7735_CYAN);
    tft->print("PL1  PL2");
    
    tft->setTextColor(ST7735_CYAN);
    tft->setCursor(10,60);
    tft->print("W");
    tft->setCursor(10,85);
    tft->print("L");
    tft->setTextColor(ST7735_GREEN);

    tft->setCursor(48,60);
    tft->print(pl1Won);
    tft->setCursor(48,85);
    if( pl1Lost >0)  tft->setTextColor(ST7735_RED);
    tft->print(pl1Lost);
    tft->setTextColor(ST7735_GREEN);

    tft->setCursor(103,60);
    tft->print(pl2Won);
    tft->setCursor(103,85);  
    if(pl2Lost>0) tft->setTextColor(ST7735_RED);
    tft->print(pl2Lost);
    tft->setTextColor(ST7735_GREEN);

}

void MyDisplay::ShowLostContinueToTAB(String tabPosition, int plyrNum)
{
  clearScreen();
  tft->setTextSize(2);
  tft->setTextColor(ST7735_GREEN);
  tft->setCursor(10,0);
  tft->print("Plyr " + String(plyrNum) + " LOST!");
  tft->setCursor(0,16);
  tft->print("-------------");
  tft->setCursor(0,33);
  tft->print("Tap " + tabPosition  + " TAB");
  //Draw Circles
  int16_t tabRadius =10; //int16_t screenHeight=128;
  
  //Do Left Tab
  if(tabPosition=="LEFT")
  {
    tft->fillCircle(20,110,tabRadius,ST7735_RED);
    tft->fillCircle(140,110,tabRadius,ST7735_WHITE);

    //Draw Pointer LEFT
    tft->drawLine(33,110,43,100,ST7735_YELLOW);
    tft->drawLine(33,110,43,120,ST7735_YELLOW);
    tft->drawLine(33,110,53,110,ST7735_YELLOW);
  }

  //Do Right Tab
  if(tabPosition=="RIGHT")
  {
    tft->fillCircle(140,110,tabRadius,ST7735_RED);
    tft->fillCircle(20,110,tabRadius,ST7735_WHITE);

    //Draw pointer RIGHT
    tft->drawLine(127,110,117,100,ST7735_YELLOW);
    tft->drawLine(127,110,117,120,ST7735_YELLOW);
    tft->drawLine(127,110,107,110,ST7735_YELLOW);
  }

  //Draw VirticalBuzzStruts
  tft->fillRoundRect(19, 90,2, 25, 0, ST7735_BLUE);
  tft->fillRoundRect(140, 90,2, 25, 0, ST7735_BLUE);
  tft->fillRoundRect(19, 80,2, 25, 0, ST7735_CYAN);
  tft->fillRoundRect(140, 80,2, 25, 0, ST7735_CYAN);

  //Draw BuzzWire
  tft->drawLine(20,80,30,70,ST7735_CYAN);
  tft->drawLine(30,70,40,80,ST7735_CYAN);
  tft->drawLine(40,80,50,70,ST7735_CYAN);
  tft->drawLine(50,70,60,80,ST7735_CYAN);
  tft->drawLine(60,80,70,70,ST7735_CYAN);
  tft->drawLine(70,70,80,80,ST7735_CYAN);
  tft->drawLine(80,80,90,70,ST7735_CYAN);
  tft->drawLine(90,70,100,80,ST7735_CYAN);
  tft->drawLine(100,80,110,70,ST7735_CYAN);
  tft->drawLine(110,70,120,80,ST7735_CYAN);
  tft->drawLine(120,80,130,70,ST7735_CYAN);
  tft->drawLine(130,70,140,80,ST7735_CYAN);

  //Reset Default Text Color
  tft->setTextColor(ST7735_GREEN);
}

void MyDisplay::ShowWon(int plyrNum)
{
  clearScreen();
  tft->setTextSize(2);
  tft->setTextColor(ST7735_GREEN);
  tft->setCursor(10,0);
  tft->print("Plyr " + String(plyrNum) + " WON!");
  tft->setCursor(0,16);
  tft->print("-------------");
 
  //Plots Galaxy Colored Stars
  int ySpace=88;
  uint16_t colors[6] ={0xFFFF,0xF800,0x001F,0xF81F,0xFFE0,0xFC00};

   for( int i=1 ; i<100;i++)
   {
      srand(millis());
      int x= random(160);
      int y= random(ySpace);
      int randColor = random(6);
      int col = colors[randColor];
      tft->drawPixel(x,y+40,col);
   }

}

void MyDisplay::ShowStartGotoNearestTAB()
{
  clearScreen();
  tft->setTextSize(2);
  tft->setTextColor(ST7735_GREEN);
  tft->setCursor(0,0);
  tft->print("To Start Game");
  tft->setCursor(2,16);
  tft->print("-------------");
  tft->setCursor(10,33);
  tft->print("Tap any TAB");

  //Draw Circles
  int16_t tabRadius =10; //int16_t screenHeight=128;
  
  //DRAW TABS
  tft->fillCircle(20,110,tabRadius,ST7735_RED);
  tft->fillCircle(140,110,tabRadius,ST7735_RED);

  //Draw Pointer LEFT
  tft->drawLine(33,110,43,100,ST7735_YELLOW);
  tft->drawLine(33,110,43,120,ST7735_YELLOW);
  tft->drawLine(33,110,53,110,ST7735_YELLOW);

  //Draw pointer RIGHT
  tft->drawLine(127,110,117,100,ST7735_YELLOW);
  tft->drawLine(127,110,117,120,ST7735_YELLOW);
  tft->drawLine(127,110,107,110,ST7735_YELLOW);

  //Draw VirticalBuzzStruts
  tft->fillRoundRect(19, 90,2, 25, 0, ST7735_BLUE);
  tft->fillRoundRect(140, 90,2, 25, 0, ST7735_BLUE);
  tft->fillRoundRect(19, 80,2, 25, 0, ST7735_CYAN);
  tft->fillRoundRect(140, 80,2, 25, 0, ST7735_CYAN);

  //Draw BuzzWire
  tft->drawLine(20,80,30,70,ST7735_CYAN);
  tft->drawLine(30,70,40,80,ST7735_CYAN);
  tft->drawLine(40,80,50,70,ST7735_CYAN);
  tft->drawLine(50,70,60,80,ST7735_CYAN);
  tft->drawLine(60,80,70,70,ST7735_CYAN);
  tft->drawLine(70,70,80,80,ST7735_CYAN);
  tft->drawLine(80,80,90,70,ST7735_CYAN);
  tft->drawLine(90,70,100,80,ST7735_CYAN);
  tft->drawLine(100,80,110,70,ST7735_CYAN);
  tft->drawLine(110,70,120,80,ST7735_CYAN);
  tft->drawLine(120,80,130,70,ST7735_CYAN);
  tft->drawLine(130,70,140,80,ST7735_CYAN);

  //Reset Default Text Color
  tft->setTextColor(ST7735_GREEN);

}

void MyDisplay::ShowAdvanceToTAB(String tabPosition, int playerNum)
{
   String playerName=playerNum==1 ? "Plyr1" : "Plyr2";

  clearScreen();
  tft->setTextSize(2);
  tft->setTextColor(ST7735_GREEN);
  tft->setCursor(0,0);
  tft->print( String( playerName + " Started"));
  tft->setCursor(0,16);
  tft->print("-------------");
  tft->setCursor(0,33);
  tft->print("Tap " + tabPosition  + " TAB");
  //Draw Circles
  int16_t tabRadius =10; //int16_t screenHeight=128;
  
  //Do Left Tab
  if(tabPosition=="LEFT")
  {
    tft->fillCircle(20,110,tabRadius,ST7735_RED);
    tft->fillCircle(140,110,tabRadius,ST7735_WHITE);

    //Draw Pointer LEFT
    tft->drawLine(33,110,43,100,ST7735_YELLOW);
    tft->drawLine(33,110,43,120,ST7735_YELLOW);
    tft->drawLine(33,110,53,110,ST7735_YELLOW);
  }

  //Do Right Tab
  if(tabPosition=="RIGHT")
  {
    tft->fillCircle(140,110,tabRadius,ST7735_RED);
    tft->fillCircle(20,110,tabRadius,ST7735_WHITE);

    //Draw pointer RIGHT
    tft->drawLine(127,110,117,100,ST7735_YELLOW);
    tft->drawLine(127,110,117,120,ST7735_YELLOW);
    tft->drawLine(127,110,107,110,ST7735_YELLOW);
  }

  //Draw VirticalBuzzStruts
  tft->fillRoundRect(19, 90,2, 25, 0, ST7735_BLUE);
  tft->fillRoundRect(140, 90,2, 25, 0, ST7735_BLUE);
  tft->fillRoundRect(19, 80,2, 25, 0, ST7735_CYAN);
  tft->fillRoundRect(140, 80,2, 25, 0, ST7735_CYAN);

  //Draw BuzzWire
  tft->drawLine(20,80,30,70,ST7735_CYAN);
  tft->drawLine(30,70,40,80,ST7735_CYAN);
  tft->drawLine(40,80,50,70,ST7735_CYAN);
  tft->drawLine(50,70,60,80,ST7735_CYAN);
  tft->drawLine(60,80,70,70,ST7735_CYAN);
  tft->drawLine(70,70,80,80,ST7735_CYAN);
  tft->drawLine(80,80,90,70,ST7735_CYAN);
  tft->drawLine(90,70,100,80,ST7735_CYAN);
  tft->drawLine(100,80,110,70,ST7735_CYAN);
  tft->drawLine(110,70,120,80,ST7735_CYAN);
  tft->drawLine(120,80,130,70,ST7735_CYAN);
  tft->drawLine(130,70,140,80,ST7735_CYAN);

  //Reset Default Text Color
  tft->setTextColor(ST7735_GREEN);


}


void MyDisplay::PrepCountDownScreen(int playerNum )
{

  clearScreen();
  tft->setTextSize(2);
  tft->setTextColor(ST7735_GREEN);
  tft->setCursor(10,0);
  tft->print("COUNTDOWN");
  tft->setCursor(0,16);
  tft->print("-------------");

}
void MyDisplay::WriteCountdownValue(String outstandingSeconds)
{ 
     int xbase=60,ybase=100;
     int xtop=35,ytop=60;
   
     tft->fillRect(xbase,ybase,xtop,ytop, ST7735_BLACK);
     tft->setTextSize(3);
     tft->setTextColor(ST7735_ORANGE);
     tft->setCursor(xbase,ybase);
     tft->print(outstandingSeconds);
     tft->setTextSize(2);
}