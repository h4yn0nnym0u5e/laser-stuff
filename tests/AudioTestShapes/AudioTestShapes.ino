#include <Audio.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       wav1;      //xy=339,253
AudioEffectWaveshaper    shapeX;     //xy=529,213
AudioEffectWaveshaper    shapeY; //xy=536,292
AudioOutputI2S           i2s1;           //xy=692,252

AudioConnection          patchCord1(wav1, shapeX);
AudioConnection          patchCord2(wav1, shapeY);
AudioConnection          patchCord3(shapeX, 0, i2s1, 0);
AudioConnection          patchCord4(shapeY, 0, i2s1, 1);

AudioControlSGTL5000     sgtl5000;     //xy=698,301
// GUItool: end automatically generated code


float pointsX[9] = {0.f, 0.587785252292473f, -0.951056516295154f, 0.951056516295153f, -0.587785252292473f, 0.f /* 4 zeroes implied */},
      pointsY[9] = {1.f, -0.809016994374947f, 0.309016994374947f, 0.309016994374947f, -0.809016994374947f, 1.f /* 4 zeroes implied */};


void setup() 
{
  AudioMemory(20);

  sgtl5000.setAddress(HIGH);
  sgtl5000.enable();
  sgtl5000.volume(0.7f);

  shapeX.shape(pointsX,9);
  shapeY.shape(pointsY,9);

  // 9 points gives 8 segments: we want to use 5 of them...
  wav1.begin(5.0f / 8, 100.0f, WAVEFORM_SAWTOOTH);
  wav1.offset(-3.0f/8); // ... starting with segment 0
}

void loop() 
{

}
