#include "ILDAlist.h"

//============================================================================
void ILDAlist::getFiles(const char* prefix, File dir)
{
  while(true) 
  {
    File entry = dir.openNextFile();
    
    if (!entry)
      break;
    if (entry.isDirectory())
    {
      char dn[strlen(prefix) + strlen(entry.name()) + 2];

      sprintf(dn, "%s/%s", prefix, entry.name());
      getFiles(dn, entry);
    }
    else 
    {
      const char* fn = entry.name();
      //Serial.println(fn);
      if (nullptr != strstr(fn, ".ild"))
        addEntry(prefix,fn);   
     }
     entry.close();
   }  
}


ILDAlist::ILDAlist(FS& fs, const char* root)
{
  const char* prefix = root;
  if (0 == strcmp(prefix,"/"))
    prefix = "";
  getFiles(prefix, fs.open(root));
}


void ILDAlist::addEntry(const char* d, const char* s)
{
  char* pn = (char*) malloc(strlen(d)+strlen(s)+2);
  
  if (nullptr != pn)
  {
    sprintf(pn, "%s/%s", d, s);
    vectorEntry_t e{pn,pn+strlen(d)+1};  
    files.push_back(e);
  }
}

//============================================================================
bool Shape::load(const char* fp, where_e w, FS& fs)
{
  bool result = false;  

  do
  {
    // discard any memory that's in use
    if (nullptr != fileName)
      switch (where)
      {
        case STREAM:
          free(fileName);
          break;
          
        case HEAP:
          free(memILDA);
          break;
          
        case EXT:
          extmem_free(memILDA);
          break;
      }

    // open the file
    pfs = &fs; // store the filesystem, in case we're streaming
    File f = pfs->open(fp,FILE_READ);
    if (!f)
      break;

    if (f.isDirectory())
    {
      f.close();
      break;      
    }
      
    // allocate the new buffer
    where = w;
    fileName = nullptr;
    szILDA = f.size();
    switch (where)
    {
      case STREAM:
        memILDA = nullptr;
        fileName = (char*) malloc(strlen(fp)+1);
        break;
        
      case HEAP:
        memILDA = (uint8_t*) malloc(szILDA + strlen(fp)+1);
        if (nullptr != memILDA)
          fileName = (char*) memILDA+szILDA;
        break;
        
      case EXT:
        memILDA = (uint8_t*) extmem_malloc(szILDA + strlen(fp)+1);
        if (nullptr != memILDA)
          fileName = (char*) memILDA+szILDA;
        break;
    }

    if (nullptr == fileName) // buffer allocation failed
    {
      f.close();      
      break;
    }

    strcpy(fileName,fp); // keep a copy for UI purposes

    // get repeat frequency and
    // load file, unless we plan to stream it
    switch (where)
    {
      case STREAM:
        loopFreq=AudioPlayILDA::repeatFrequency(fileName,*pfs);
        result = true;
        break;

      case HEAP:
      case EXT:
        if (szILDA == f.read(memILDA,szILDA)) // load OK?
        {
          loopFreq=AudioPlayILDA::repeatFrequency(memILDA);
          result = true;             
        }
        break;      
    }
    f.close();
  } while (0);

  //Serial.printf("%s %s\n", result?"Loaded":"Failed to load", fp);
  return result;
}


bool Shape::play(AudioPlayILDA& pi, float frequency)
{
  bool ok = false;
  pi.setPlaybackRate(frequency/loopFreq); 

  switch (where)
  {
    case EXT:
    case HEAP:
      ok = (nullptr != memILDA)?pi.play(memILDA,szILDA):false;
      break;

    case STREAM:
      ok = pi.play(fileName, *pfs);
      break;
  }

  if (ok)
    ppi = &pi;

  return ok;
}
