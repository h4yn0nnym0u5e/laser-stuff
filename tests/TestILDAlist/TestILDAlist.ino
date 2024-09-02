#include "ILDAlist.h"

//============================================================================
ILDAlist& listFiles(FS& fs, const char* root="/")
{
  ILDAlist& fileList = *(new ILDAlist(fs,root));
  
  Serial.println("=====================");
  for (int i=0;i<fileList.fileCount();i++)
    Serial.printf("%s: %s\n", fileList.getName(i), fileList.getPath(i));

  return fileList;
}

//============================================================================
void testOpen(ILDAlist& fileList, int idx)
{
  const char* fto = fileList.getPath(idx);
  File f = SD.open(fto);
  if (f)
  {
    Serial.printf("Opened %s OK\n",fto);
    f.close();
  }
  else
    Serial.printf("Couldn't open %s\n",fto);  
}

//============================================================================
void setup() 
{
  while (!Serial)
    ;

  while (!SD.begin(BUILTIN_SDCARD))
  {
    Serial.println("No SD card!");
    delay(500);    
  }
  Serial.println("SD card found");

  ILDAlist& fileList = listFiles(SD);
  testOpen(fileList,3);
}

void loop() 
{

}
