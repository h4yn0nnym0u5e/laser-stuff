#include "ILDAlist.h"
#include "osc.h"

#include <Audio.h>

// GUItool: begin automatically generated code
AudioPlayILDA            playILDA1;      //xy=346,451
AudioPlayILDA            playILDA2;      //xy=353,641
AudioSynthWaveform       wav1;      //xy=358,531
AudioSynthWaveform       wav2; //xy=363,566
AudioRecordQueue         queue1;         //xy=513,363
AudioEffectRotator       rotator1;       //xy=592,433
AudioEffectRotator       rotator2;       //xy=592,498
AudioMixer4              mixerX;         //xy=764,430
AudioMixer4              mixerY; //xy=765,514
AudioMixer4              mixerR; //xy=770,591
AudioMixer4              mixerG; //xy=773,654
AudioMixer4              mixerB; //xy=774,718
AudioOutputI2S           i2sOut;           //xy=1059,439

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
AudioConnection          patchCord18(mixerX, 0, i2sOut, 0);
AudioConnection          patchCord19(mixerY, 0, i2sOut, 1);

AudioControlSGTL5000     sgtl5000;     //xy=1075,484
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
  AudioMemory(50);
  
  DEBUGSERIALPORT.begin(115200);
  DEBUGSERIALPORT.println("Waiting for USB serial...");
  
  while (!Serial)
    ;

  while (!SD.begin(BUILTIN_SDCARD))
  {
    DEBUGSERIALPORT.println("No SD card!");
    delay(500);    
  }
  DEBUGSERIALPORT.println("SD card found");

  sgtl5000.setAddress(HIGH);
  sgtl5000.enable();
  sgtl5000.volume(0.05f);
  
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

    if ('\n' == ch)
    {
      float speed;
      int n, nr;
      
      buf[idx-1]= 0; // terminate
      //DEBUGSERIALPORT.printf("'%s': ",buf);
      
      if (0 == strncmp(buf,"li",2))
      {
        listFiles(SD);
      }
      else if (1 == sscanf(buf, "ld:%d:%n", &n, &nr)) // load ILDA to shape
      {
        if (n>=0 && n<8)
        {
          shapes[n].loadHeap(buf+nr);
          DEBUGSERIALPORT.printf("%s %s\n",shapes[n].isReady()?"Loaded":"Failed to load",buf+nr);
        }
      }
      else if (2 == sscanf(buf, "pl:%d:%f", &n, &speed)) // play shape at frequency
      {
        if (n>=0 && n<8 && shapes[n].isReady())
          DEBUGSERIALPORT.printf("%s %s at %.2fHz\n",
              shapes[n].play(playILDA1,speed)?"Playing":"Failed to play",
              shapes[n].getFilename(),
              speed
              );
      }
      else if (0 == strncmp(buf, "stop", 4)) // stop playing
      {
        playILDA1.stop();
        DEBUGSERIALPORT.println("Stopped");
      }
      idx=0;
      buf[0]=0;
      DEBUGSERIALPORT.println();
    }
  }
}

/*
 * Functions to apply ILDA methods sent by OSC
 */
void routeILDA(OSCMessage& msg,int addressOffset,OSCBundle& reply) 
{
  static ILDAlist* pList = nullptr;
  OSCMessage& repl = OSCUtils::staticPrepareReplyResult(msg,reply);

  // load list of files
  if (OSCUtils::isStaticTarget(msg,addressOffset,"/init","s"))
  {
    char root[50];
    msg.getString(0,root,50);
    
    if (nullptr != pList)
      delete pList;

    pList = new ILDAlist(SD,root);
    repl.add(pList->fileCount()).add(0);
  }
  else if (nullptr != pList)
  {
    // get an entry from the list
    if (OSCUtils::isStaticTarget(msg,addressOffset,"/entry","i"))
    {
      int fnum = msg.getInt(0);
      if (fnum <= pList->fileCount())      
        repl.add(pList->getPath(fnum)).add(0);
      else
        repl.add((int) OSCUtils::NOT_FOUND);
    }
    
  }
  else    
    repl.add((int) OSCUtils::NOT_CONNECTED);
}

/*
 * Function to apply Shape methods sent by OSC
 */
void routeShape(OSCMessage& msg,int addressOffset,OSCBundle& reply) 
{
  OSCMessage& repl = OSCUtils::staticPrepareReplyResult(msg,reply);

  // load ILDA file to RAM, with data in given shapes[] element
  if (OSCUtils::isStaticTarget(msg,addressOffset,"/load","iss"))
  {
    int slot;
    char where[5];
    char fn[50];

    slot = msg.getInt(0);
    msg.getString(1,fn,50);
    msg.getString(2,where,50);
    DEBUGSERIALPORT.printf("Load shape %s to slot %d, using %s\n", fn, slot, where);
    if (slot < shapes.count())
    {
      Shape& shape = shapes[slot];  
      bool ok = false;
      
      if (0 == strncmp(where, "heap", 4))
        ok = shape.loadHeap(fn);
      else if (0 == strncmp(where, "ext", 3))
        ok = shape.loadExt(fn);

      repl.add(ok?(int) OSCUtils::OK:(int) OSCUtils::NOT_FOUND);
    }
  }
  else if (OSCUtils::isStaticTarget(msg,addressOffset,"/entry","i"))
  {
    int slot;
    
    slot = msg.getInt(0);
    if (slot < shapes.count())
    {
      Shape& shape = shapes[slot];

      if (shape.isReady())
        repl.add(shape.getFilename()).add((int) OSCUtils::OK);
      else        
        repl.add("<empty>").add((int) OSCUtils::OK);
    }
    else
      repl.add((int) OSCUtils::NOT_FOUND);
    
  }
  else if (OSCUtils::isStaticTarget(msg,addressOffset,"/slots",NULL))
  {
    repl.add(shapes.count()).add((int) OSCUtils::OK);
  } 
}
