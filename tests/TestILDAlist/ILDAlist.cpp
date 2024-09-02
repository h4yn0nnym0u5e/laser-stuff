#include "ILDAlist.h"

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
