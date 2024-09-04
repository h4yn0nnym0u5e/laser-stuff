#if !defined(_OSC_H_)
#define _OSC_H_

#include <OSCBundle.h>
#include <SLIPEncodedSerial.h>
#include <OSCUtils.h>

extern void initOSC(void);
extern void updateOSC(void);

extern void routeILDA(OSCMessage& msg,int addressOffset,OSCBundle& replyStack);
extern void routeShape(OSCMessage& msg,int addressOffset,OSCBundle& replyStack);

#define HWSERIALPORT Serial1
#define NOT_ROUTED notRouted

#endif // !defined(_OSC_H_)
