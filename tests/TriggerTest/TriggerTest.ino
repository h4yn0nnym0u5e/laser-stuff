/*
 * Test of AudioPlayILDA with real-time triggering. 
 */
#include <Audio.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       wavTrig;      //xy=151,233
AudioSynthWaveformDc     dcTrig;            //xy=157,277
AudioMixer4              mixTrig;         //xy=318,264
AudioSynthWaveform       wav;            //xy=482,143
AudioPlayILDA            playILDA1;      //xy=484,265
AudioRecordQueue         queue1;         //xy=650,160
AudioOutputTDM           tdm2O;          //xy=738,324

AudioConnection          patchCord1(wavTrig, 0, mixTrig, 0);
AudioConnection          patchCord2(dcTrig, 0, mixTrig, 1);
AudioConnection          patchCord3(mixTrig, playILDA1);
AudioConnection          patchCord4(mixTrig, 0, tdm2O, 14);
AudioConnection          patchCord5(playILDA1, 0, tdm2O, 0);
AudioConnection          patchCord6(playILDA1, 0, queue1, 0);
AudioConnection          patchCord7(playILDA1, 1, tdm2O, 2);
AudioConnection          patchCord8(playILDA1, 2, tdm2O, 4);
AudioConnection          patchCord9(playILDA1, 3, tdm2O, 6);
AudioConnection          patchCord10(playILDA1, 4, tdm2O, 8);
AudioConnection          patchCord11(playILDA1, 5, tdm2O, 10);
AudioConnection          patchCord12(playILDA1, 6, tdm2O, 12);

AudioControlPCM3168      pcm3168;        //xy=766,479
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

  // trigger testing
  /*
  wavTrig.begin(0.5f,30.0f,WAVEFORM_PULSE);
  wavTrig.pulseWidth(0.1f);
  playILDA("/ilda/035.ild");
  playILDA1.setTriggerType(AudioPlayILDA::TriggerType::EDGE_POS);
  playILDA1.setTriggerEvery(AudioPlayILDA::TriggerEvery::FRAME);
  /*/
  wavTrig.begin(0.5f,50.0f,WAVEFORM_PULSE);
  wavTrig.pulseWidth(0.1f);
  playILDA("/ilda/triangle.ild");
  //playILDA1.setPlaybackRate(0.1f);
  playILDA1.setTriggerType(AudioPlayILDA::TriggerType::EDGE_POS);
  playILDA1.setTriggerEvery(AudioPlayILDA::TriggerEvery::FILE);
  //*/
  
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
      Serial.printf("CPU load %.2f%%"
                    //"; last Y %d"
                    "\n"
                    , AudioProcessorUsageMax() 
                    //, playILDA1.lastY
                    );
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
