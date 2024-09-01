/*
 * Test of AudioPlayILDA with playback rate setting and different 
 * indexing schemes.
 * 
 * We have one ILDA file, which consists of 3 points using the palette
 * to colour them red, green and blue, lying at the corners of an
 * equilateral triangle.
 * 
 * We load this into memory, and play it back using two AudioPlayILDA objects
 * with different settings:
 * * the first is a position modulator, using FLOOR indexing and a loop 
 *   frequency of 30Hz: this steps to the triangle's points, remaining at 
 *   each for 11.1ms
 * * the second is a shape drawer, using INTERPOLATION indexing to draw
 *   smooth lines between the triangle's points, changing colour as it
 *   goes. With a loop frequency of 90Hz, we get one shape drawn
 *   at each corner of the positioning triangle
 */
#include <Audio.h>

// GUItool: begin automatically generated code
AudioPlayILDA            playILDA1;      //xy=366,208
AudioPlayILDA            playILDA2;      //xy=373,398
AudioSynthWaveform       wav1;      //xy=378,288
AudioSynthWaveform       wav2; //xy=383,323
AudioRecordQueue         queue1;         //xy=533,120
AudioEffectRotator       rotator1;       //xy=612,190
AudioEffectRotator       rotator2;       //xy=612,255
AudioMixer4              mixerX;         //xy=784,187
AudioMixer4              mixerY; //xy=785,271
AudioMixer4              mixerR; //xy=790,348
AudioMixer4              mixerG; //xy=793,411
AudioMixer4              mixerB; //xy=794,475
AudioOutputTDM           tdm2O;          //xy=1190,301

AudioConnection          patchCord1(playILDA1, 0, queue1, 0);
AudioConnection          patchCord2(playILDA1, 0, rotator1, 0);
AudioConnection          patchCord3(playILDA1, 1, rotator1, 1);
AudioConnection          patchCord4(playILDA1, 3, mixerR, 0);
AudioConnection          patchCord5(playILDA1, 4, mixerG, 0);
AudioConnection          patchCord6(playILDA1, 5, mixerB, 0);
AudioConnection          patchCord7(playILDA2, 0, rotator2, 0);
AudioConnection          patchCord8(playILDA2, 1, rotator2, 1);
AudioConnection          patchCord9(playILDA2, 3, mixerR, 1);
AudioConnection          patchCord10(playILDA2, 4, mixerG, 1);
AudioConnection          patchCord11(playILDA2, 5, mixerB, 1);
AudioConnection          patchCord12(wav1, 0, rotator1, 2);
AudioConnection          patchCord13(wav2, 0, rotator2, 2);
AudioConnection          patchCord14(rotator1, 0, mixerX, 0);
AudioConnection          patchCord15(rotator1, 1, mixerY, 0);
AudioConnection          patchCord16(rotator2, 0, mixerX, 1);
AudioConnection          patchCord17(rotator2, 1, mixerY, 1);
AudioConnection          patchCord18(mixerX, 0, tdm2O, 10);
AudioConnection          patchCord19(mixerY, 0, tdm2O, 8);
AudioConnection          patchCord20(mixerR, 0, tdm2O, 6);
AudioConnection          patchCord21(mixerG, 0, tdm2O, 4);
AudioConnection          patchCord22(mixerB, 0, tdm2O, 2);

AudioControlPCM3168      pcm3168;        //xy=1218,456
// GUItool: end automatically generated code



//------------------------------------------------------------------------------
#define PCM3168_RST 17
//------------------------------------------------------------------------------
// 
struct Shape 
{
  uint8_t* memILDA;
  size_t szILDA;
  const char* fileName;
  float loopFreq; 
};

Shape shapes[2];

/*
 * Load ILDA file to EXTMEM for non-streaming playback
 * If successful,memILDA is not nullptr, and szILDA is set
 * 
 * We calculate the 'natural' loop frequency and store it,
 * so that it's easy later to set a rate that will loop
 * at a chosen frequency.
 * 
 * The natural frequency is as given by the library, assuming
 * one sample emitted for every point in the file. This allows 
 * the whole thing to be run at a different sample rate from
 * the default 44.1kHz, and you'll still be driving the
 * galvos at the same rate.
 */
bool loadBuffer(Shape& shp, const char* fn)
{
  File f;
  
  if (nullptr != shp.memILDA)
  {
    extmem_free(shp.memILDA);
    shp.memILDA = nullptr;
  }

  f = SD.open(fn,FILE_READ);
  shp.szILDA = f.size();
  if (shp.szILDA > 0)
  {
    shp.memILDA = (uint8_t*) extmem_malloc(shp.szILDA);
    if (nullptr != shp.memILDA)
    {
      shp.fileName = fn; // fn mustn't be on stack or otherwise volatile!
      if (shp.szILDA != f.read(shp.memILDA,shp.szILDA))
      {
        extmem_free(shp.memILDA);
        shp.memILDA = nullptr;
      }
      else
        shp.loopFreq = AudioPlayILDA::repeatFrequency(shp.memILDA);
    }
  }
  f.close();
  
  Serial.printf("Load '%s' to %08X, size %d, loop freq %.2f\n", fn, (uint32_t) shp.memILDA, (uint32_t) shp.szILDA, shp.loopFreq);

  return nullptr != shp.memILDA;
}


//------------------------------------------------------------------------------
/*
 * Play a pre-loaded shape at a given loop frequency
 */
void playILDA(AudioPlayILDA& pi, Shape& shp, float frequency)
{
  pi.setPlaybackRate(frequency/shp.loopFreq); 
  bool ok = (nullptr != shp.memILDA)?pi.play(shp.memILDA,shp.szILDA):false;
  Serial.printf("%slaying %s from RAM\n",ok?"P":"Not p",shp.fileName);
}

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
  delay(100);

  wav1.begin(1.0f, 0.10f, WAVEFORM_SAWTOOTH); // rotation rate 1
  wav2.begin(1.0f, 0.37f, WAVEFORM_SAWTOOTH); // rotation rate 2
  rotator2.reverse(true);

  loadBuffer(shapes[0], "/ilda/triangle.ild"); // 137 points wait, 10 points transition while blank
  loadBuffer(shapes[1], "/ilda/triangle-3pt.ild"); // three points of different colours
  
  playILDA1.createBuffer(32768,AudioBuffer::inHeap); // plenty needed if high-speed playback required!
  playILDA2.createBuffer(32768,AudioBuffer::inHeap); // plenty needed if high-speed playback required!

  // Default interpolation is FLOOR, by special request of Roj
  // playILDA1.setInterpolationMethod(AudioPlayILDA::FLOOR);
  // playILDA1.setInterpolationMethod(AudioPlayILDA::ROUND);
  
  // For drawing a shape given only its corners, we MUST interpolate
  playILDA2.setInterpolationMethod(AudioPlayILDA::INTERPOLATE); // interpolate position and colour when drawing

  // we're only using the 3-point file here, as a demo
  playILDA(playILDA1, shapes[1],  30.0f); // step to each point and wait
  playILDA(playILDA2, shapes[1],  90.0f); // draw a shape

  // point stepper
  mixerX.gain(0,0.8f);
  mixerY.gain(0,0.8f);
  mixerR.gain(0,0.0f); // doesn't contribute to the colour
  mixerG.gain(0,0.0f);
  mixerB.gain(0,0.0f);

  // drawn shape
  mixerX.gain(1,0.2f);
  mixerY.gain(1,0.2f);

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
  // queue is just used to know when audio update has occurred
  // we don't care about its content
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

// Serial commands not used for this, but leave code in
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
