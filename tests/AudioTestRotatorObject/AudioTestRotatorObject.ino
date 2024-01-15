#include <Audio.h>
#include "effect_rotator.h"
#define AudioFilterLadder AudioEffectRotator

//============================================================
// GUItool: begin automatically generated code
AudioSynthWaveform       wav1;      //xy=221,278
AudioSynthWaveform       wavRm; //xy=278,391
AudioSynthWaveform       wavR; //xy=281,339
AudioEffectWaveshaper    shapeX;     //xy=397,246
AudioEffectWaveshaper    shapeY; //xy=403,293
  AudioMixerSummer         rotMixer;         //xy=445,365: was a Mixer4
  AudioFilterLadder        rotator;        //xy=602,304: re-mapped via #define
AudioFilterStateVariable filterX;        //xy=783,278
AudioFilterStateVariable filterY; //xy=787,352
AudioOutputI2S           i2s1;           //xy=926,314

AudioConnection          patchCord1(wav1, shapeX);
AudioConnection          patchCord2(wav1, shapeY);
AudioConnection          patchCord3(wavRm, 0, rotMixer, 1);
AudioConnection          patchCord4(wavR, 0, rotMixer, 0);
AudioConnection          patchCord5(shapeX, 0, rotator, 0);
AudioConnection          patchCord6(shapeY, 0, rotator, 1);
AudioConnection          patchCord7(rotMixer, 0, rotator, 2);
AudioConnection          patchCord8(rotator, 0, filterX, 0);
  AudioConnection          patchCord9(rotator, 1, filterY, 0); // connection changed after export
AudioConnection          patchCord10(filterX, 0, i2s1, 0);
AudioConnection          patchCord11(filterY, 0, i2s1, 1);

AudioControlSGTL5000     sgtl5000;     //xy=924,366
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
void setRotator(float freq, bool clockwise)
{
  // no interrupts is vital as once started, the waveforms accumulate
  // phase even when off, and don't reset it on begin()
  AudioNoInterrupts();
  wavR.begin(1.0f, freq, WAVEFORM_SAWTOOTH);
  rotator.reverse(!clockwise);
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

  setRotator(0.2f,true);
  wavRm.begin(0.1f,1.2f,WAVEFORM_SINE);

  // see what happens if we filter out high frequencies
  filterX.frequency(1000.0f);
  filterY.frequency(1000.0f);
}

//============================================================
uint32_t lastReverse;
void loop() 
{
  static bool cw;
  if (millis() - lastReverse >= 5555)
  {
    lastReverse = millis();
    cw = !cw;

    rotator.reverse(cw);
    Serial.printf("Rotator CPU usage: %.2f%%\n",rotator.processorUsageMax());
    rotator.processorUsageMaxReset();
  }
}
