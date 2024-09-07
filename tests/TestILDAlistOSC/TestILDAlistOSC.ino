#include "ILDAlist.h"
#include "osc.h"

#include <Audio.h>

// GUItool: begin automatically generated code
AudioPlayILDA            playILDA1;      //xy=158,155
AudioPlayILDA            playILDA2;      //xy=165,345
AudioSynthWaveform       wav1;           //xy=170,235
AudioSynthWaveform       wav2;           //xy=175,270
AudioRecordQueue         queue1;         //xy=325,67
AudioEffectRotator       rotator1;       //xy=404,137
AudioEffectRotator       rotator2;       //xy=404,202
AudioMixer4              mixerX;         //xy=576,134
AudioMixer4              mixerY;         //xy=577,218
AudioMixer4              mixerR;         //xy=582,295
AudioMixer4              mixerG;         //xy=585,358
AudioMixer4              mixerB;         //xy=586,422
AudioOutputTDM           tdm1;           //xy=808,157

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
AudioConnection          patchCord18(mixerX, 0, tdm1, 10);
AudioConnection          patchCord19(mixerY, 0, tdm1, 8);

AudioControlPCM3168      pcm3168;      //xy=823,303
// GUItool: end automatically generated code


Shapes<NUM_SHAPES> shapes;
//============================================================================
ILDAlist& listFiles(FS& fs, const char* root="/")
{
  ILDAlist& fileList = *(new ILDAlist(fs,root));
  
  DEBUGSERIALPORT.println("=====================");
  for (int i=0;i<fileList.fileCount();i++)
    DEBUGSERIALPORT.printf("%s: %s\n", fileList.getName(i), fileList.getPath(i));

  return fileList;
}

//============================================================================
void setup() 
{
  pcm3168.reset(17);
  AudioMemory(50);
  
  DEBUGSERIALPORT.begin(115200);
  DEBUGSERIALPORT.println("Waiting for USB serial...");
  
  while (!Serial)
    ;

  while (!SD.begin(BUILTIN_SDCARD))
  {
    DEBUGSERIALPORT.println("No SD card!");
    delay(500);    
  }  DEBUGSERIALPORT.println("SD card found");

  pcm3168.enable();
  pcm3168.volume(0.5f);
  pcm3168.inputLevel(0.5f);
  
  initOSC();

  DEBUGSERIALPORT.println("Ready");  
}


#define BUFLEN 50
char buf[BUFLEN+1];
int idx;

void loop() 
{
  updateOSC();  

  while (DEBUGSERIALPORT.available())
  {
    char ch = DEBUGSERIALPORT.read();
    DEBUGSERIALPORT.print(ch);
    
    if (idx < BUFLEN)
      buf[idx++] = ch;

    if ('\n' == ch || '\r' == ch)
    {
      float speed,ampl;
      int n, nr;
      
      buf[idx-1]= 0; // terminate      
/*      
 * Use debug terminal to send commands:
 * li     - list ILDA files on SD
 * int:n  - n=0 to use FLOOR interpolation, 1 to use INTERPOLATE
 * ld:n:f - load file f to shape n
 * pl:n:f - play shape n at frequency f
 * stop   - stop playing
 */     
      if (0 == strncmp(buf,"li",2))
      {
        listFiles(SD);
      }
      else if (2 == sscanf(buf, "int:%d:%d", &nr, &n)) // set interpolation
      {
        AudioPlayILDA& pi = nr?playILDA2:playILDA1;
        pi.setInterpolationMethod(n?AudioPlayILDA::INTERPOLATE:AudioPlayILDA::FLOOR);
        DEBUGSERIALPORT.printf("playILDA%d set to %s\n", nr+1, n?"INTERPOLATE":"FLOOR");
      }
      else if (2 == sscanf(buf, "lv:%d:%f", &nr, &ampl)) // set level
      {
        mixerX.gain(nr,ampl);
        mixerY.gain(nr,ampl);
        DEBUGSERIALPORT.printf("Channel %d set to %.2f\n", nr, ampl);
      }
      else if (1 == sscanf(buf, "ld:%d:%n", &n, &nr)) // load ILDA file to shape
      {
        if (n>=0 && n<shapes.count())
        {
          shapes[n].loadHeap(buf+nr);
          DEBUGSERIALPORT.printf("%s %s\n",shapes[n].isReady()?"Loaded":"Failed to load",buf+nr);
        }
      }
      else if (3 == sscanf(buf, "pl:%d:%d:%f", &n, &nr, &speed)) // play shape at frequency
      {
        if (n>=0 && n<shapes.count() && shapes[n].isReady())
        {
          AudioPlayILDA& pi = nr?playILDA2:playILDA1;
          
          DEBUGSERIALPORT.printf("%s %s at %.2fHz\n",
              shapes[n].play(pi,speed)?"Playing":"Failed to play",
              shapes[n].getFilename(),
              speed
              );
        }
      }
      else if (0 == strncmp(buf, "stop", 4)) // stop playing
      {
        playILDA1.stop();
        playILDA2.stop();
        DEBUGSERIALPORT.println("Stopped");
      }
      else if (2 == sscanf(buf, "rt:%d:%f", &n, &speed)) // rotate shape at amplitude / frequency
      {
        AudioSynthWaveform& wv = n?wav2:wav1;
        AudioEffectRotator& rt = n?rotator2:rotator1;

        wv.begin(1.0f,fabs(speed),WAVEFORM_SAWTOOTH);
        rt.reverse(speed < 0.0f);
        DEBUGSERIALPORT.println("rotate");
      }
      idx=0;
      buf[0]=0;
      DEBUGSERIALPORT.println();
    }
  }
}
