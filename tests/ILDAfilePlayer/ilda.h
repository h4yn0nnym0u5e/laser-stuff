#if !defined(_ILDA_H_)
#define _ILDA_H_

#if !defined(htons)
#define htons(x) (((((x) >> 8) & 0xFF) | ((x) << 8)) & 0xFFFF)
#endif // !defined(htons)

#define ILDA_BLANK 0x40

struct __attribute__ ((packed))
ILDAheader_s
{
  union
  {
    uint32_t ilda_u32;
    uint8_t ilda_char[4];
  };
  uint8_t reserved1[3];
  uint8_t format;
  char name[8];
  char company[8];
  uint16_t records;
  uint16_t number;
  uint16_t total;
  uint8_t projector;
  uint8_t reserved2;
};

struct __attribute__ ((packed))
ILDAformat0
{
  int16_t X,Y,Z;
  uint8_t status;
  uint8_t index;
};


struct __attribute__ ((packed))
ILDAformat1
{
  int16_t X,Y;
  uint8_t status;
  uint8_t index;
};


struct __attribute__ ((packed))
ILDAformat2
{
  uint8_t R,G,B;
};


struct __attribute__ ((packed))
ILDAformat4
{
  int16_t X,Y,Z;
  uint8_t status;
  uint8_t B,G,R;
};


struct __attribute__ ((packed))
ILDAformat5
{
  int16_t X,Y;
  uint8_t status;
  uint8_t B,G,R;
};

class ILDAheader
{
    ILDAheader_s hdr;
  public:
    ILDAheader() : hdr{0} {}
    uint16_t getFormat(void) { return hdr.format; }
    uint16_t getRecords(void) { return htons(hdr.records); }
    uint16_t getNumber(void) { return htons(hdr.number); }
    uint16_t getTotal(void) { return htons(hdr.total); }
};


class ILDA
{
  public:
    static const ILDAformat2 palette256[256];
    static const int sizes[6];
};



#endif // defined(_ILDA_H_)
