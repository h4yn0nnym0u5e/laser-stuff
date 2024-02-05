/*
 * Test of AudioPlayILDA and stall protection.
 * The target 035.ild file seems to have some slightly weird blanking,
 * resulting in ~136ms of blank time, and some lines crossing the
 * projection area which look incorrect, but it seems to work OK.
 */
#include <Audio.h>

// GUItool: begin automatically generated code
AudioPlayILDA            playILDA1;      //xy=578,205
AudioRecordQueue         queue1;         //xy=744,100
AudioEffectProtectStall  protectStall1;  //xy=920,209
AudioOutputTDM2          tdm2O;         //xy=1127,232

AudioConnection          patchCord1(playILDA1, 0, queue1, 0);
AudioConnection          patchCord2(playILDA1, 0, protectStall1, 0);
AudioConnection          patchCord3(playILDA1, 1, protectStall1, 1);
AudioConnection          patchCord4(playILDA1, 2, protectStall1, 2);
AudioConnection          patchCord5(playILDA1, 3, protectStall1, 3);
AudioConnection          patchCord6(playILDA1, 4, protectStall1, 4);
AudioConnection          patchCord7(playILDA1, 5, protectStall1, 5);
AudioConnection          patchCord8(playILDA1, 6, protectStall1, 6);
AudioConnection          patchCord9(protectStall1, 0, tdm2O, 0);
AudioConnection          patchCord10(protectStall1, 1, tdm2O, 2);
AudioConnection          patchCord11(protectStall1, 2, tdm2O, 4);
AudioConnection          patchCord12(protectStall1, 3, tdm2O, 6);
AudioConnection          patchCord13(protectStall1, 4, tdm2O, 8);
AudioConnection          patchCord14(protectStall1, 5, tdm2O, 10);
AudioConnection          patchCord15(protectStall1, 6, tdm2O, 12);

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

const char* fileName = "/ilda/035.ild";
elapsedMillis theTimer;
//------------------------------------------------------------------------------
void setup() 
{
  AudioMemory(100); // plenty, for queues and TDM

  pinMode(LED_BUILTIN,OUTPUT);
  resetPCM3168();
  
  while(!Serial)
    ;

  pcm3168.enable();
  pcm3168.volume(0.5f);
  pcm3168.inputLevel(0.5f);

  while (!SD.begin(BUILTIN_SDCARD))
  {
    Serial.println("SD.begin() failed!");
    delay(500);
  }  
  
  Serial.println("=======================");
  delay(1000);

  // protectStall1.setRGBsafeValue(-0.5f); // enable to see when protection kicks in
  queue1.begin();
  playILDA1.createBuffer(4096,AudioBuffer::inHeap);
  playILDA1.play(fileName);
  theTimer = 0;
}


//------------------------------------------------------------------------------
volatile int16_t* data;
int count;
bool protectActive;

void loop() 
{
  if (queue1.available())
  {
    data = queue1.readBuffer();
    queue1.freeBuffer();
    count--;
    if (count < 0)
    {
      digitalToggleFast(LED_BUILTIN);
      count = 100;
    }
  }

  if (playILDA1.isPlaying() && theTimer > 7000)
  {
    Serial.println("stop");
    playILDA1.stop();
  }

  if (theTimer > 8000)
  {
    theTimer = 0;
    Serial.println("play");
    playILDA1.play(fileName);
  }

  if (protectActive != protectStall1.isProtecting())
  {
    protectActive = protectStall1.isProtecting();

    Serial.printf("t=%d: Protection system %s\n", millis(), protectActive?"ON":"off");
  }
}
