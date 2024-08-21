/*
 * Test of loading and getting info from ILDA files
 */
#include <Audio.h>


//------------------------------------------------------------------------------
// Custom struct to hold an element in our list of ILDA files
// Adjust contents to suit your purposes
struct ILDAslot {char* name; MemBuffer* data; float frequency; float rate;};

// Our list of files
ILDAslot slots[] = {
  {"/ilda/ilddolf.ild", .rate = 1.0f},
  {"/ilda/035.ild", .rate = 1.0f},
  {"/ilda/All Colors Sharp Dots.ild", .rate = 1.0f},
  };


void printSlot(ILDAslot& slot)
{
  Serial.printf("%s is at %08X, %d bytes long, repeats at %.3fHz, rate is set to %.3f\n",
                slot.name, slot.data->buffer, slot.data->bufSize, slot.frequency, slot.rate);
}

extern uint8_t external_psram_size;
  
void setup() 
{
  while(!Serial)
  {
    delay(100);
    digitalToggleFast(LED_BUILTIN);
  }
  
  while (!SD.begin(BUILTIN_SDCARD))
  {
    Serial.println("SD.begin() failed!");
    delay(500);
  } 

  Serial.printf("%dMB of EXTMEM fitted\n",external_psram_size);
  
  for (int i=0;i<3;i++) // look at files to find their repeat frequencies: not loaded into memory
  {
    elapsedMicros us;    
    float f = AudioPlayILDA::repeatFrequency(slots[i].name); 
    Serial.printf("Took %dus to find that %s repeats at %.3fHz\n",(int) us, slots[i].name, f);
  }

  Serial.println();

  for (int i=0;i<3;i++) // load files into memory "slots", and store their repeat frequencies
  {
    // load
    elapsedMicros us;    
    slots[i].data = AudioPlayILDA::loadFile(slots[i].name,MemBuffer::inExt);
    Serial.printf("Took %dus to load %s to %08X ... ",(int) us, slots[i].name, slots[i].data->buffer);

    // get frequency
    us = 0;
    float f = AudioPlayILDA::repeatFrequency(slots[i].data->buffer);
    slots[i].frequency = f;
    Serial.printf("%dus to find that it repeats at %.3fHz\n",(int) us, f);

    // print the information we have stored
    printSlot(slots[i]); 
  }

}


//------------------------------------------------------------------------------
volatile int16_t* data;
int count;
#define BUFLEN 50
char buf[BUFLEN+1];
int idx;

void loop() 
{
  while (Serial.available())
  {
    char ch = Serial.read();
    if (idx < BUFLEN)
      buf[idx++] = ch;

    if ('\n' == ch)
    {
      buf[idx-1]= 0; // terminate

      // interpret message here
      
      idx=0;
    }
  }
}
