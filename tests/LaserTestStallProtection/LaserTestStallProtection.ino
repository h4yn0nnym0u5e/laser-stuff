/*
 * Test of AudioPlayILDA.
 * The target 035.ild file seems to have some slightly weird blanking,
 * resulting in ~136ms of blank time, and some lines crossing the
 * projection area which look incorrect, but it seems to work OK.
 */
#include <Audio.h>

// GUItool: begin automatically generated code
AudioPlayILDA            playILDA1;      //xy=578,205
AudioMixerSummer         summer1;        //xy=609,318
AudioEffectRotator       rotator1;       //xy=618,413
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

  protectStall1.setRGBsafevalue(-0.5f);
  queue1.begin();
  playILDA1.createBuffer(4096,AudioBuffer::inHeap);
  playILDA1.play(fileName);
  theTimer = 0;

  //prepareILDA(/*"/ilda/All Colors Sharp Dots.ild" */  "/ilda/ilddolf.ild" );
}


//------------------------------------------------------------------------------
volatile bool galvosRunning;
bool XgalvosAreRunning(audio_block_t** blocks, int threshold)
{
  bool result = false;
  
  int xmin=99999,xmax=-99999,ymin=99999,ymax=-99999;
  for (int i=0;i<AUDIO_BLOCK_SAMPLES && !result;i++)
  {
    if (nullptr != blocks[0])
    {
      if (blocks[0]->data[i] > xmax) xmax = blocks[0]->data[i];
      if (blocks[0]->data[i] < xmin) xmin = blocks[0]->data[i];
    }
    if (nullptr != blocks[1])
    {
      if (blocks[1]->data[i] > ymax) ymax = blocks[1]->data[i];
      if (blocks[1]->data[i] < ymin) ymin = blocks[1]->data[i];
    }

    if (xmax - xmin > threshold
     || ymax - ymin > threshold)
     result = true;
  }
  galvosRunning = result;
  return result;
}

bool galvosStateChanged(void)
{
  static bool last;
  bool result = false;

  if (last != galvosRunning)
  {
    last = galvosRunning;
    result = true;
  }

  return result;
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
      //digitalToggleFast(LED_BUILTIN);
      count = 9;
      Serial.printf("%d: validCount = {%d,%d}; %s; update count = %d; time since move %d\n",
                    millis(),
                    playILDA1.validCount[0],playILDA1.validCount[1],
                    protectStall1.isUpdating()?"OK":"***** No! *****",
                    protectStall1.getUpdateCount(),
                    millis() - protectStall1.lastMoved
//                    protectStall1.isRunning?"r":"s"
//                    protectStall1.sTime
                    );
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

  if (galvosStateChanged())
  {
    Serial.printf("Galvos are %s\n",galvosRunning?"running":"stalled");
  }
}
