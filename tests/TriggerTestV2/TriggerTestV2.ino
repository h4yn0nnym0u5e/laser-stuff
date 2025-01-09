/*
 * Test of AudioPlayILDA with real-time triggering. 
 */

#include "design.h" // created using https://manicken.github.io/#

Projector proj;
AudioControlPCM3168      pcm3168;        //xy=766,479
// GUItool: end automatically generated code

//------------------------------------------------------------------------------
#define PCM3168_RST 17
//------------------------------------------------------------------------------

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
  pcm3168.volume(0.95f);
  pcm3168.inputLevel(0.5f);

  while (!SD.begin(BUILTIN_SDCARD))
  {
    Serial.println("SD.begin() failed!");
    delay(500);
  }  
  
  Serial.println("=======================");
  delay(1000);

  proj.ildachannel1.ilda.playILDA.createBuffer(32768,AudioBuffer::inHeap); // plenty needed if high-speed playback required!
  proj.ildachannel1.ilda.playILDA.setTriggerType(AudioPlayILDA::TriggerType::EDGE_POS);
  proj.ildachannel1.ilda.playILDA.setTriggerEvery(AudioPlayILDA::TriggerEvery::FRAME);
  proj.ildachannel1.ildaxyzmod.Mod.begin(0.001f,0.1f,WAVEFORM_SINE);
  proj.ildachannel1.ildaxyzmod.Mod.offset(0.75f); // size
  
  proj.ildachannel2.ilda.playILDA.createBuffer(32768,AudioBuffer::inHeap); // plenty needed if high-speed playback required!
  proj.ildachannel2.ilda.playILDA.setTriggerType(AudioPlayILDA::TriggerType::EDGE_POS);
  proj.ildachannel2.ilda.playILDA.setTriggerEvery(AudioPlayILDA::TriggerEvery::FRAME);
  proj.ildachannel2.ildaxyzmod.Mod.begin(0.001f,0.1f,WAVEFORM_SINE);
  proj.ildachannel2.ildaxyzmod.Mod.offset(0.5f); // size

  // set playback rate
  const float rate = 2.0f;
  proj.ildachannel1.ilda.playILDA.setPlaybackRate(rate);
  proj.ildachannel2.ilda.playILDA.setPlaybackRate(rate);
  
  proj.queue.begin();

  // trigger testing
  
  // Trigger needs to be 0.0 - 1.0 for our usage. The rising edge
  // triggers a frame, and also enables the galvo drive. This is 
  // not ideal, we'd really like to cross-fade to the next playback
  // object's position while still blanked...
  proj.trig1.offset(0.5f);
  proj.trig2.offset(0.5f);

  proj.trig1.pulseWidth(0.49f);
  proj.trig2.pulseWidth(0.49f);

  AudioNoInterrupts();
  const float frameRate = 25.0f;
  proj.trig1.begin(0.5f, frameRate, WAVEFORM_PULSE);
  proj.trig2.begin(0.5f, frameRate, WAVEFORM_PULSE);
  proj.trig2.phase(180.0f);
  AudioInterrupts();

  // position of first ILDA channel:
  proj.X_mrMix.gain(2, -0.15f);
  proj.Y_mrMix.gain(2, 0.45f);

  // position of second ILDA channel:
  proj.X_mrMix.gain(3, -0.25f);
  proj.Y_mrMix.gain(3, -0.35f);

  // Now play the files!
  proj.ildachannel1.ilda.playILDA.play("/ilda/Enterprise2.ild"); // max 1210 points / frame; 83 frames
  proj.ildachannel2.ilda.playILDA.play("/ilda/ilddolf.ild");  // max 1593 points / frame; 65 frames
}


//------------------------------------------------------------------------------
volatile int16_t* data;
int count;
#define BUFLEN 50
char buf[BUFLEN+1];
int idx;

void loop() 
{
  if (proj.queue.available())
  {
    data = proj.queue.readBuffer();
    proj.queue.freeBuffer();
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

/*
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
*/  
}
