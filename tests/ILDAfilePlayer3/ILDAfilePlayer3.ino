/*
 * Test of AudioPlayILDA.
 * The target 035.ild file seems to have some slightly weird blanking,
 * resulting in ~136ms of blank time, and some lines crossing the
 * projection area which look incorrect, but it seems to work OK.
 */
#include <Audio.h>

// GUItool: begin automatically generated code
AudioPlayILDA            playILDA1;      //xy=578,205
AudioRecordQueue         queue1;         //xy=744,100
AudioOutputTDM2          tdm2O;         //xy=832,264

AudioConnection          patchCord1(playILDA1, 0, tdm2O, 0);
AudioConnection          patchCord2(playILDA1, 0, queue1, 0);
AudioConnection          patchCord3(playILDA1, 1, tdm2O, 2);
AudioConnection          patchCord4(playILDA1, 2, tdm2O, 4);
AudioConnection          patchCord5(playILDA1, 3, tdm2O, 6);
AudioConnection          patchCord6(playILDA1, 4, tdm2O, 8);
AudioConnection          patchCord7(playILDA1, 5, tdm2O, 10);
AudioConnection          patchCord8(playILDA1, 6, tdm2O, 12);

AudioControlPCM3168      pcm3168;      //xy=860,419
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

  queue1.begin();
  playILDA1.createBuffer(4096,AudioBuffer::inHeap);
  playILDA1.play("/ilda/035.ild" /*"/ilda/ilddolf.ild"*/);

  //prepareILDA(/*"/ilda/All Colors Sharp Dots.ild" */  "/ilda/ilddolf.ild" );
}


//------------------------------------------------------------------------------
volatile int16_t* data;
int count;

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
}
