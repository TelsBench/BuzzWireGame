#include <arduino.h>
#include "MyDisplay.h"
#include <anyrtttl.h>

MyDisplay myScreen;

//RTTTL Tunes
const char * SoundAttention = "attention:d=8,o=6,b=240:8e,32p,8e";
const char * SoundTick      = "tick:d=8,o=6,b=240:8e";
const char * SoundLose     = "lose:d=4,o=4,b=160:d4#";
const char * SoundWin       = "win:d=16,0=6:b=120;e,f,b,g,g7";

//Global game vars
int TURN=1,PL1WON=0,PL1LOST=0,PL2WON=0,PL2LOST=0,NUMPLAYERS=1;
uint16_t TARGET=0;
bool GAMEWON=true,GAMELOST=false;
String CurrPlyrName ="";
String PL1NAME="Player1";
String PL2NAME="Player2";


//Values expected at input PORTD Left/Right TABS or Buzzwire
//when masked with 0x0007
const uint16_t LEFT =  6;
const uint16_t BUZZ  = 5;
const uint16_t RIGHT = 3;

//TAB AND BUZZ Pin allocations
#define LEFT_PIN  0         //PORT-D D0
#define BUZZ_PIN  1         //PORT-D D1
#define RIGHT_PIN 2         //PORT-D D2
#define NUMPLAYERS_SW 7     //PORT-D D7
#define COUNTDOWN_ON_PIN 14 //D14 (A0)

//Toughness and Skill
bool COUNTDOWN_ON   = false;
long SkillLevel = 1;  // 1 - 4

//Speaker Out Pin
#define SPEAKER 6  //PORT-D D6

//Prototype Signatures
void PlayWin();
void PlayLose();
void PlayAttention( bool once = false);
void InstructionsAndStart();
void playerResult(bool hasWon);
byte GetBuzzOrTap(bool tapOnly);
String GetTargetString(int target);
unsigned int GetTimoutInSeconds();

void setup() {


  //Number of players  LOW = 1 Player HIGH = 2 Players
  pinMode(NUMPLAYERS_SW,INPUT_PULLUP);
  NUMPLAYERS = digitalRead(NUMPLAYERS_SW) == LOW ? 1 : 2;

  //Countdown on pin ( off by default )
  pinMode(COUNTDOWN_ON_PIN,INPUT_PULLUP);
  COUNTDOWN_ON=digitalRead(COUNTDOWN_ON_PIN);

  pinMode(SPEAKER, OUTPUT);

  //CONTROLLER INPORT PORT IS PORT 'D'
  pinMode(LEFT_PIN,INPUT_PULLUP);
  pinMode(BUZZ_PIN,INPUT_PULLUP);
  pinMode(RIGHT_PIN,INPUT_PULLUP);

  myScreen.tftSetup();
  myScreen.clearScreen();
  InstructionsAndStart();

}

uint16_t inByte=0;
unsigned int timeoutSeconds;
unsigned long startMillis;
bool timeForClockUpdate;
bool timedOut;
void loop() 
{ 
  startMillis = millis();
  timeoutSeconds = GetTimoutInSeconds();
  timedOut = false;
  
  do
  {
    inByte=PIND & 0x0007;

    if(COUNTDOWN_ON && (millis() - startMillis)/920 >=1 && !timedOut ) 
    {    
      if(timeoutSeconds>=0) myScreen.WriteCountdownValue (String(timeoutSeconds));
      if(timeoutSeconds>0) timeoutSeconds--;
      PlayAttention(true);
      startMillis=millis();
      timedOut = timeoutSeconds==0 ?true : false;
    }

  } while(inByte!=TARGET &&  inByte!=BUZZ && !timedOut );

   if( timedOut )
   {
    //timed out
     playerResult(false);
   }
    else
   { 
      if(inByte==TARGET)
      playerResult(true);
    else
      playerResult(false);
   }

}

//PlayTimeout
unsigned int GetTimoutInSeconds()
{

    switch (SkillLevel)
    {
    case 1 :
      return 60;

    case 2 :
      return 40;

    case 3 :
    return 20;

    case 4 :
    return 10;

    default:
      return 5;
    }

}

//GameWorks
void playerResult(bool hasWon )
{
  String tabDollar=GetTargetString(TARGET);

  if(!hasWon) //If LOST, Make player continue to TARGET TAB
  {
    myScreen.ShowLostContinueToTAB(tabDollar,TURN);
    PlayLose();
    while ((PIND & 0x0007)!= TARGET){};
  }

  String targetDollar =GetTargetString(TARGET);
  if(hasWon)
  { 
    myScreen.ShowWon(TURN);
    PlayWin();
    delay(3000);
  }

  // ( PLAYER 1 )
  if(TURN==1 && hasWon)  {PL1WON=PL1WON+1;}// CurrPlyrName = PL1NAME;}
  if(TURN==1 && !hasWon) {PL1LOST=PL1LOST+1;}//CurrPlyrName = PL1NAME;}

  // ( PLAYER 2)
  if(TURN==2 && hasWon)  {PL2WON=PL2WON+1; }//CurrPlyrName = PL2NAME;}
  if(TURN==2 && !hasWon) {PL2LOST=PL2LOST+1;} //CurrPlyrName=PL2NAME;} 

  myScreen.ShowStats(PL1WON,PL1LOST,PL2WON,PL2LOST);
  delay(3000);

  //SWAP TARGETS and SHow Next Target
  if(TARGET==LEFT) TARGET=RIGHT; else TARGET=LEFT;
   
  //SWAP TURNS IF REQUIRED
  if(TURN==1 && NUMPLAYERS==2) TURN=2; else TURN=1;

  myScreen.ShowAdvanceToTAB(GetTargetString(TARGET),TURN);
  PlayAttention();
}

//Sounds
void PlayAttention(bool once){
  if(once)
   anyrtttl::blocking::play(SPEAKER, SoundTick);
  else
    anyrtttl::blocking::play(SPEAKER, SoundAttention);
};

void PlayLose(){
  anyrtttl::blocking::play(SPEAKER, SoundLose);
};
void PlayWin(){

  anyrtttl::blocking::play(SPEAKER, SoundWin);
}

void InstructionsAndStart()
{
   myScreen.ShowCredits();
   delay(3000);
   myScreen.ShowLikeAndSubscribe();
  delay(4000);
  myScreen.ShowStartGotoNearestTAB();

  TARGET=GetBuzzOrTap(true);
  String tabName = TARGET==LEFT ? "RIGHT" : "LEFT";
  TARGET=(TARGET==LEFT ? RIGHT : LEFT);
  myScreen.ShowAdvanceToTAB(tabName,1);
  PlayAttention(); 
  delay(3000);
}

byte GetBuzzOrTap(bool tapOnly)
{
  bool found;
  byte T=0;
  byte S=0;
  while(!found)
  { 
    // GET T FROM PORT X??
    T= PIND & 0x0007;
    if(T==LEFT)  S=LEFT;
    if(T==RIGHT) S=RIGHT;
    if(T==BUZZ)  S=BUZZ;
    if(tapOnly && S==BUZZ) S=0; // REM prevents BUZZ When Taponly
    found = (S==BUZZ || S==LEFT || S==RIGHT);
  }
  return S;
}

String GetTargetString(int target)
{
    return  target==LEFT ? "LEFT" : "RIGHT";
}
