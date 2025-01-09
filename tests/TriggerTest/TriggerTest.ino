/*
 * Test of AudioPlayILDA with real-time triggering. 
 */
#include <Audio.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       wavTrig;        //xy=259,249
AudioSynthWaveformDc     dcTrig;         //xy=265,293
AudioMixer4              mixTrig;        //xy=426,280
AudioSynthWaveform       wav;            //xy=590,159
AudioPlayILDA            playILDA1;      //xy=592,281
AudioRecordQueue         queue1;         //xy=758,176
AudioOutputTDM           tdm2O;          //xy=846,340

AudioConnection          patchCord1(wavTrig, 0, mixTrig, 0);
AudioConnection          patchCord2(dcTrig, 0, mixTrig, 1);
AudioConnection          patchCord3(mixTrig, playILDA1);
AudioConnection          patchCord4(mixTrig, 0, tdm2O, 14);
AudioConnection          patchCord5(playILDA1, 0, queue1, 0);
AudioConnection          patchCord6(playILDA1, 0, tdm2O, 10);
AudioConnection          patchCord7(playILDA1, 1, tdm2O, 8);
AudioConnection          patchCord8(playILDA1, 3, tdm2O, 6);
AudioConnection          patchCord9(playILDA1, 4, tdm2O, 4);
AudioConnection          patchCord10(playILDA1, 5, tdm2O, 2);

AudioControlPCM3168      pcm3168;        //xy=874,495
// GUItool: end automatically generated code

//------------------------------------------------------------------------------
#define PCM3168_RST 17
//------------------------------------------------------------------------------
// 

//------------------------------------------------------------------------------
void setup() 
{
  AudioMemory(100); // plenty, for queues and TDM

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
  //*
  wavTrig.begin(0.5f,30.0f,WAVEFORM_PULSE);
  wavTrig.pulseWidth(0.1f);
  playILDA1.play("/ilda/035.ild");
  playILDA1.setTriggerType(AudioPlayILDA::TriggerType::EDGE_POS);
  playILDA1.setTriggerEvery(AudioPlayILDA::TriggerEvery::FRAME);
  /*/
  wavTrig.begin(0.5f,50.0f,WAVEFORM_PULSE);
  wavTrig.pulseWidth(0.1f);
  playILDA1.play("/ilda/triangle.ild");
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
        wavTrig.frequency(speed);
        Serial.printf("Set trigger frequency to %.3f\n", speed);
      }
      
      idx=0;
    }
  }
}
