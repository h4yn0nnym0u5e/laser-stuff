#include "Audio.h"
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

class Shape 
{
    uint8_t* memILDA;
    size_t szILDA;
    FS* pfs;
    char* fileName;
    float loopFreq;
    enum where_e {STREAM, HEAP, EXT} where;
    bool load(const char* fp, where_e w, FS& fs);
    AudioPlayILDA* ppi;
    
  public:
    Shape() : memILDA(nullptr), szILDA(0), pfs(nullptr), fileName(nullptr) {}
    bool loadHeap(const char* fp, FS& fs = SD) { return load(fp, HEAP, fs); }
    bool loadExt(const char* fp, FS& fs = SD)  { return load(fp, EXT, fs); }
    bool prepStream (const char* fp, FS& fs = SD)  { return load(fp, STREAM, fs); }
    bool play(AudioPlayILDA& pi, float frequency);
    void stop(void) { if (nullptr != ppi) { ppi->stop(); ppi = nullptr; }}
    bool isReady(void) { return nullptr != fileName; }
    char* getFilename(void) { return fileName; }
};
