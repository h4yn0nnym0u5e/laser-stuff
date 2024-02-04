#include "SD.h"
#include "ilda.h"
#include <Audio.h>
//#include "TeensyDebug.h"

// GUItool: begin automatically generated code
AudioSynthWaveformDc     dc;            //xy=491,204
AudioRecordQueue         queueSync;         //xy=646,210
AudioPlayQueue           queueX;         //xy=646,392
AudioPlayQueue           queueY; //xy=650,443
AudioOutputTDM           tdmO;           //xy=841,347

AudioConnection          patchCord1(dc, queueSync);
AudioConnection          patchCord2(queueX, 0, tdmO, 12);
AudioConnection          patchCord3(queueY, 0, tdmO, 14);

AudioControlCS42448      cs42448_1;      //xy=832,497
// GUItool: end automatically generated code


File ildaFile;
int frameLength;
int queuedSamples;

void setup() 
{
  AudioMemory(100); // plenty, for queues and TDM

  pinMode(LED_BUILTIN,OUTPUT);
  
//halt_cpu();
  while(!Serial)
    ;

  cs42448_1.enable();
  cs42448_1.volume(0.5f);
  cs42448_1.inputLevel(0.5f);

  while (!SD.begin(BUILTIN_SDCARD))
  {
    Serial.println("SD.begin() failed!");
    delay(500);
  }  

  File root = SD.open("/ilda/");
  
  printDirectory(root, 0);
  Serial.println("=======================");
  delay(1000);

  prepareILDA(/*"/ilda/All Colors Sharp Dots.ild" */  "/ilda/ilddolf.ild" );
  dc.amplitude(0.1); // non-zero value
  queueSync.begin(); // start sync queue
}

void printILDA(File& f)
{
  ILDAheader hdr;
  f.read(&hdr,sizeof hdr);
  Serial.printf("; Format %d: %d;%d;%d ",hdr.getFormat(),hdr.getRecords(),hdr.getNumber(),hdr.getTotal());
}

/*
 * Scan for info.
 * Max records might be 1594 in a Format 0 file (ilddolf.ild), so
 * that frame is 8*1594=12572 bytes long. If we plot 2 samples / record
 * so 22kp/s galvos, it'll take 72.3ms, or 13.8fps. One would assume
 * that we want a constant frame rate...
 * 
 * 1594 samples is 12.45 audio blocks
 */
int scanILDA(File& f)
{
  ILDAheader hdr;

  f.seek(0);  
  f.read(&hdr,sizeof hdr);

  int total = hdr.getTotal();
  int maxRecords = hdr.getRecords();
  size_t maxPos = 0;
  uint32_t s = micros();
  for (int i=1; i<total; i++)
  {
    size_t newPos = f.position() + ILDA::sizes[hdr.getFormat()] * hdr.getRecords();
    f.seek(newPos);
    f.read(&hdr,sizeof hdr);
    
    if (hdr.getRecords() > maxRecords)
    {
      maxRecords = hdr.getRecords();
      maxPos = newPos;
    }
  }
  Serial.printf("max %d at position %X; took %dus", maxRecords, maxPos, micros() - s);

  return maxRecords;
}

void prepareILDA(const char* fp)
{
  ildaFile = SD.open(fp);

  frameLength = scanILDA(ildaFile); // maximum record count in a frame
  ildaFile.seek(0);
}

/*
 * Send a frame
 */
void sendILDA(File& f)
{
  ILDAheader hdr;

  
  if (sizeof hdr != f.read(&hdr,sizeof hdr)
    || 0 == hdr.getRecords())
  {
    f.seek(0);
    f.read(&hdr,sizeof hdr);
    //Serial.println("loop\n");
    digitalToggleFast(LED_BUILTIN);
  }

  int recs = hdr.getRecords();
  //Serial.println(recs);
  for (int i=0;i<recs /* frameLength */;i++)
  {
    ILDAformat0 rec; // make an assumption!
    if (i<recs)
      f.read(&rec, sizeof rec);
    else
      rec.status = ILDA_BLANK;

    if (ILDA_BLANK != rec.status)      
    {
      queueX.play((int16_t) htons(rec.X));
      queueX.play((int16_t) htons(rec.X));
      queueY.play((int16_t) htons(rec.Y));
      queueY.play((int16_t) htons(rec.Y));
    }
    else
    {
      /*
      queueX.play(0);
      queueY.play(0);      
      */
    }
  }
  queuedSamples += recs*2;
}

void printDirectory(File dir, int numSpaces) {
   while(true) {
     File entry = dir.openNextFile();
     if (! entry) {
       //Serial.println("** no more files **");
       break;
     }
     printSpaces(numSpaces);
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numSpaces+2);
     } else {
       // files have sizes, directories do not
       int n = log10f(entry.size());
       if (n < 0) n = 10;
       if (n > 10) n = 10;
       printSpaces(50 - numSpaces - strlen(entry.name()) - n);
       Serial.print("  ");
       Serial.print(entry.size(), DEC);

       printILDA(entry);
       scanILDA(entry);
       /*
       DateTimeFields datetime;
       if (entry.getModifyTime(datetime)) {
         printSpaces(4);
         printTime(datetime);
       }
       */
       Serial.println();
     }
     entry.close();
   }
}

void printSpaces(int num) {
  for (int i=0; i < num; i++) {
    Serial.print(" ");
  }
}


void loop() 
{
  if (queuedSamples < 2048) // frameLength*2)
    sendILDA(ildaFile);

  if (queueSync.available())
  {
    queuedSamples -= AUDIO_BLOCK_SAMPLES;
    queueSync.readBuffer();
    queueSync.freeBuffer();
  }
}
