/*
 * Test of AudioPlayILDA and stall protection.
 * The target 035.ild file seems to have some slightly weird blanking,
 * resulting in ~136ms of blank time, and some lines crossing the
 * projection area which look incorrect, but it seems to work OK.
 */
#include <Audio.h>
//#include <TeensyDebug.h>

//==========================================================================================

//*
// With protection:
// GUItool: begin automatically generated code
AudioSynthWaveform       wav1;      //xy=552,117
AudioPlayILDA            playILDA1;      //xy=578,205
AudioMixerSummer         summer1;        //xy=609,318
AudioRecordQueue         queue1;         //xy=744,100
AudioEffectRotator       rotator1;       //xy=757,161
AudioEffectProtectStall  protectStall1;  //xy=920,209
AudioOutputTDM2          tdm2O;         //xy=1127,232

AudioConnection          patchCord1(wav1, 0, rotator1, 2);
AudioConnection          patchCord2(playILDA1, 0, queue1, 0);
AudioConnection          patchCord3(playILDA1, 0, rotator1, 0);
AudioConnection          patchCord4(playILDA1, 1, rotator1, 1);
AudioConnection          patchCord5(playILDA1, 2, protectStall1, 2);
AudioConnection          patchCord6(playILDA1, 3, protectStall1, 3);
AudioConnection          patchCord7(playILDA1, 4, protectStall1, 4);
AudioConnection          patchCord8(playILDA1, 5, protectStall1, 5);
AudioConnection          patchCord9(playILDA1, 6, protectStall1, 6);
AudioConnection          patchCord10(rotator1, 0, protectStall1, 0);
AudioConnection          patchCord11(rotator1, 1, protectStall1, 1);
AudioConnection          patchCord12(protectStall1, 0, tdm2O, 0);
AudioConnection          patchCord13(protectStall1, 1, tdm2O, 2);
AudioConnection          patchCord14(protectStall1, 2, tdm2O, 4);
AudioConnection          patchCord15(protectStall1, 3, tdm2O, 6);
AudioConnection          patchCord16(protectStall1, 4, tdm2O, 8);
AudioConnection          patchCord17(protectStall1, 5, tdm2O, 10);
AudioConnection          patchCord18(protectStall1, 6, tdm2O, 12);

AudioControlPCM3168      pcm3168;      //xy=1128,446
// GUItool: end automatically generated code


//------------------------------------------------------------------------------
#define PCM3168_RST 17
void resetPCM3168(void)
{
  pinMode(PCM3168_RST,OUTPUT);
  digitalWriteFast(PCM3168_RST,0);
  delay(1);
  digitalWriteFast(PCM3168_RST,1);
  delay(100);  
}

//------------------------------------------------------------------------------
// 
uint8_t* memILDA;
size_t szILDA;
const char* fileName = "/ilda/035.ild"; // "/ilda/ilddolf.ild"; // 

/*
 * Load ILDA file to EXTMEM for non-streaming playback
 * If successful,memILDA is not nullptr, and szILDA is set
 */
void loadBuffer(const char* fn)
{
  File f;

  f = SD.open(fn);
  szILDA = f.size();
  memILDA = (uint8_t*) extmem_malloc(szILDA);
  if (nullptr != memILDA)
  {
    if (szILDA != f.read(memILDA,szILDA))
    {
      extmem_free(memILDA);
      memILDA = nullptr;
    }
  }
  f.close();
}

//------------------------------------------------------------------------------
elapsedMillis theTimer;
AudioWAVdata::ILDAformat2 palette[256];
//------------------------------------------------------------------------------
void setup() 
{
  AudioMemory(100); // plenty, for queues and TDM

  pinMode(LED_BUILTIN,OUTPUT);
  resetPCM3168();
  
  while(!Serial)
    ;

  if (CrashReport)
    Serial.print(CrashReport);    

  pcm3168.enable();
  pcm3168.volume(0.5f);
  pcm3168.inputLevel(0.5f);

  while (!SD.begin(BUILTIN_SDCARD))
  {
    Serial.println("SD.begin() failed!");
    delay(500);
  }  
  
  Serial.println("=======================");
  wav1.begin(1.0f,0.25f,WAVEFORM_SAWTOOTH); // disable to stop rotation, so protection is visible
  delay(1);

  // protectStall1.setRGBsafeValue(-0.5f); // enable to see when protection kicks in on a 'scope
  queue1.begin();
  playILDA1.copyPalette(palette,nullptr,256); // copy default palette into our buffer
  playILDA1.setPaletteMemory(palette,256);    // make the library use it

  /*
  playILDA1.createBuffer(4096,AudioBuffer::inExt);
  playILDA1.play(fileName);
  /*/
  loadBuffer(fileName);
  if (nullptr != memILDA)
    playILDA1.play(memILDA,szILDA);
  else
  {
    while (1)
    {
      Serial.printf("Failed to buffer %s; needed %ul bytes\n",fileName,szILDA);
      delay(500);
    }
  }
  //*/

  theTimer = 0;
}


//------------------------------------------------------------------------------
volatile int16_t* data;
int count;
bool protectActive;
bool dir;
elapsedMillis pTimer;

void loop() 
{
  //============================================================
  if (queue1.available() )
  {
    // discard queued data, just using it for update() counting
    data = queue1.readBuffer();
    queue1.freeBuffer();
    count--;
    if (count < 0)
    {
      digitalToggleFast(LED_BUILTIN);
      count = 30;
    }
  }

  // test of stop() - protection will kick in if
  // output is not being rotated
  if (playILDA1.isPlaying() && theTimer > 7000)
  {
    Serial.println("stop"); Serial.flush(); delay(10);
    playILDA1.stop();
  }

  // test of re-starting playback
  if (theTimer > 8000)
  {
    theTimer = 0;
    Serial.println("play"); Serial.flush(); delay(10);
    /*
    playILDA1.play(fileName);
    /*/
    playILDA1.play(memILDA,szILDA);
    //*/
  }

  // message on Serial if protection changes state
  if (protectActive != protectStall1.isProtecting())
  {
    protectActive = protectStall1.isProtecting();

    Serial.printf("t=%d: Protection system %s\n", millis(), protectActive?"ON":"off");
  }
  
  // mess with the palette
  // we happen to know the dolphin uses colours 40 and 56
  if (pTimer > 1)
  {
    pTimer = 0;

    if (dir)
    {
      palette[40].G++;
      palette[56].G++;
      if (0 == palette[56].G)
      {
        palette[56].G--;
        dir = !dir;
      }
    }
    else
    {
      palette[40].G--;
      if (0 == palette[56].G)
      {
        palette[56].G++;
        dir = !dir;
      }
      else
        palette[56].G--;   
    }
  }
}
