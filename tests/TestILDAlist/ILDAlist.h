#include "Arduino.h"
#include "SD.h"
#include <vector>

class ILDAlist
{
    struct vectorEntry_t
    {
      const char* path;
      const char* name;
    };
    std::vector<vectorEntry_t> files;
    void getFiles(const char* prefix, File dir);
  public:
    ILDAlist(FS& fs = SD, const char* root="/");
    ~ILDAlist() {for (auto e : files) free((char*) e.path); }
    void addEntry(const char* d, const char* s);
    int fileCount(void) { return files.size(); }
    const char* getPath(int idx) { return files.at(idx).path; }
    const char* getName(int idx) { return files.at(idx).name; }
};
