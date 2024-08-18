/*
 * Test of AudioPlayILDA with playback rate setting.
 * 
 * The target 035.ild file seems to have some slightly weird blanking,
 * resulting in ~136ms of blank time, and some lines crossing the
 * projection area which look incorrect, but it seems to work OK.
 */
#include <Audio.h>

// GUItool: begin automatically generated code
AudioSynthWaveform wav;
AudioPlayILDA            playILDA1;      //xy=578,205
AudioRecordQueue         queue1;         //xy=744,100
AudioOutputTDM           tdm2O;         //xy=832,264

//AudioConnection          patchCord1(wav, 0, tdm2O, 0);
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

struct thing {AudioSynthWaveform& wv; AudioPlayILDA& ply; AudioRecordQueue& q;};
struct XYthing {thing X,Y;};

XYthing myThing{{wav,playILDA1,queue1},{wav,playILDA1,queue1}};
//------------------------------------------------------------------------------
#define PCM3168_RST 17
//------------------------------------------------------------------------------
// 
uint8_t* memILDA;
size_t szILDA;
const char* fileName = "/ilda/ilddolf.ild"; // "/ilda/035.ild"; 
// "/ilda/All Colors Sharp Dots.ild" 

/*
 * Load ILDA file to EXTMEM for non-streaming playback
 * If successful,memILDA is not nullptr, and szILDA is set
 */
bool loadBuffer(const char* fn)
{
  File f;
  
  if (nullptr != memILDA)
  {
    extmem_free(memILDA);
    memILDA = nullptr;
  }

  f = SD.open(fn,FILE_READ);
  szILDA = f.size();
  if (szILDA > 0)
  {
    memILDA = (uint8_t*) extmem_malloc(szILDA);
    if (nullptr != memILDA)
    {
      if (szILDA != f.read(memILDA,szILDA))
      {
        extmem_free(memILDA);
        memILDA = nullptr;
      }
    }
  }
  f.close();
Serial.printf("Load '%s' to %08X, size %d\n", fn, (uint32_t) memILDA, (uint32_t) szILDA);

  return nullptr != memILDA;
}

//------------------------------------------------------------------------------
void playILDA(const char* fp)
{
  bool ok = playILDA1.play(fp);
  Serial.printf("%slaying %s\n",ok?"P":"Not p",fp);
}

//------------------------------------------------------------------------------
void playILDA()
{
  bool ok = (nullptr != memILDA)?playILDA1.play(memILDA,szILDA):false;
  Serial.printf("%slaying from RAM\n",ok?"P":"Not p");
}

//------------------------------------------------------------------------------
void setup() 
{
  AudioMemory(100); // plenty, for queues and TDM

pinMode(38,OUTPUT);
pinMode(41,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  pcm3168.reset(PCM3168_RST);
  
  while(!Serial)
  {
    delay(100);
    digitalToggleFast(LED_BUILTIN);
  }
    

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

  wav.begin(0.95f, 220.0f, WAVEFORM_SINE); // just to check system is working
  playILDA1.createBuffer(32768,AudioBuffer::inHeap); // plenty needed if high-speed playback required!
  playILDA("/ilda/035.ild" /*"/ilda/ilddolf.ild"*/);
  
  queue1.begin();
}


//------------------------------------------------------------------------------
volatile int16_t* data;
int count;
#define BUFLEN 50
char buf[BUFLEN+1];
int idx;

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
      count = 200;
      Serial.printf("CPU load %.2f%%\n",AudioProcessorUsageMax());
      AudioProcessorUsageMaxReset();
    }
  }

  while (Serial.available())
  {
    char ch = Serial.read();
    if (idx < BUFLEN)
      buf[idx++] = ch;

    if ('\n' == ch)
    {
      float speed;
      buf[idx-1]= 0; // terminate
      
      if (1 == sscanf(buf,"%f",&speed))
      {
        playILDA1.setPlaybackRate(speed);
        Serial.printf("Set playback rate to %.3f\n", speed);
      }
      else if (1 == idx) // blank entry
        playILDA("/ilda/035.ild");        
      else if (loadBuffer(buf)) // valid filename
      {
        Serial.println(buf);
        playILDA(); // play from RAM buffer
      }
      idx=0;
    }
  }
}
