#include <Audio.h>

//============================================================
// GUItool: begin automatically generated code
AudioSynthWaveform       wav1;      //xy=221,278
AudioEffectWaveshaper    shapeX;     //xy=380,262
AudioEffectWaveshaper    shapeY;     //xy=389,301
AudioSynthWaveform       rotatorSin; //xy=399,348
AudioSynthWaveform       rotatorCos; //xy=411,387
AudioEffectMultiply      XxSin;      //xy=576,268
AudioEffectMultiply      XxCos; //xy=584,305
AudioEffectMultiply      YxSin; //xy=591,343
AudioEffectMultiply      YxCos; //xy=597,382
AudioMixer4              mixerX;         //xy=751,288
AudioMixer4              mixerY; //xy=757,364
AudioFilterStateVariable filterX;        //xy=884,296
AudioFilterStateVariable filterY; //xy=888,370
AudioOutputI2S           i2s1;           //xy=1027,332

AudioConnection          patchCord1(wav1, shapeX);
AudioConnection          patchCord2(wav1, shapeY);
AudioConnection          patchCord3(shapeX, 0, XxSin, 0);
AudioConnection          patchCord4(shapeX, 0, XxCos, 0);
AudioConnection          patchCord5(shapeY, 0, YxSin, 0);
AudioConnection          patchCord6(shapeY, 0, YxCos, 0);
AudioConnection          patchCord7(rotatorSin, 0, XxSin, 1);
AudioConnection          patchCord8(rotatorSin, 0, YxSin, 1);
AudioConnection          patchCord9(rotatorCos, 0, XxCos, 1);
AudioConnection          patchCord10(rotatorCos, 0, YxCos, 1);
AudioConnection          patchCord11(XxSin, 0, mixerX, 0);
AudioConnection          patchCord12(XxCos, 0, mixerY, 1);
AudioConnection          patchCord13(YxSin, 0, mixerY, 0);
AudioConnection          patchCord14(YxCos, 0, mixerX, 1);
AudioConnection          patchCord15(mixerX, 0, filterX, 0);
AudioConnection          patchCord16(mixerY, 0, filterY, 0);
AudioConnection          patchCord17(filterX, 0, i2s1, 0);
AudioConnection          patchCord18(filterY, 0, i2s1, 1);

AudioControlSGTL5000     sgtl5000;     //xy=1025,384
// GUItool: end automatically generated code
//============================================================

// Definition of points for a pentagram. 6 points define 5 segments,
// and get us back to the starting point. AudioEffectWaveshaper needs
// an array of 2^n + 1 points, so we need 9 array elements, and arrange
// that we only use 6 of them by setting the scanning waveform's
// amplitude and offset appropriately:
float pointsX[9] = {0.f, 0.587785252292473f, -0.951056516295154f, 0.951056516295153f, -0.587785252292473f, 0.f /* 4 zeroes implied */},
      pointsY[9] = {1.f, -0.809016994374947f, 0.309016994374947f, 0.309016994374947f, -0.809016994374947f, 1.f /* 4 zeroes implied */};

//============================================================
void setRotators(float freq, bool clockwise)
{
  // no interrupts is vital as once started, the waveforms accumulate
  // phase even when off, and don't reset it on begin()
  AudioNoInterrupts();
  rotatorSin.begin(1.0f, freq, WAVEFORM_SINE);
  rotatorCos.begin(1.0f, freq, WAVEFORM_SINE);
  rotatorCos.phase(90.0f);
  if (clockwise)
  {
    mixerX.gain(1, 1.0f);
    mixerY.gain(1,-1.0f);
  }
  else
  {
    mixerX.gain(1,-1.0f);
    mixerY.gain(1, 1.0f);
  }
  
  AudioInterrupts();
}


//============================================================
void setup() 
{
  AudioMemory(20);

  sgtl5000.setAddress(HIGH); // because I hacked my audio adaptor...
  sgtl5000.enable();
  sgtl5000.volume(0.7f);

  shapeX.shape(pointsX,9);
  shapeY.shape(pointsY,9);

  // 9 points gives 8 segments: we want to use 5 of them...
  wav1.begin(5.0f / 8, 100.0f, WAVEFORM_SAWTOOTH);
  wav1.offset(-3.0f/8); // ... starting with segment 0

  setRotators(0.2f,true);

  // see what happens if we filter out high frequencies
  filterX.frequency(1000.0f);
  filterY.frequency(1000.0f);
}

//============================================================
uint32_t lastReverse;
void loop() 
{
  static bool cw;
  if (millis() - lastReverse >= 2000)
  {
    lastReverse = millis();
    cw = !cw;

    setRotators(0.2f,cw);
  }
}
