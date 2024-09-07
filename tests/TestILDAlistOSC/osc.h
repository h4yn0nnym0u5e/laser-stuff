#if !defined(_OSC_H_)
#define _OSC_H_

#include "config.h"

#include <OSCBundle.h>
#include <OSCUtils.h>

#include "util_macros.h"
#define SERIAL_CLASS_Serial  SLIPEncodedUSBSerial
#define SERIAL_CLASS_Serial1 SLIPEncodedSerial
#define SERIAL_CLASS_Serial2 SLIPEncodedSerial
#define SERIAL_CLASS_Serial3 SLIPEncodedSerial
#define SERIAL_CLASS_Serial4 SLIPEncodedSerial
#define SERIAL_CLASS_Serial5 SLIPEncodedSerial
#define SERIAL_CLASS_Serial6 SLIPEncodedSerial
#define SERIAL_CLASS_Serial7 SLIPEncodedSerial
#define SERIAL_CLASS_Serial8 SLIPEncodedSerial

#define SLIPEncodedClass PASTE_AB(SERIAL_CLASS_, OSCSERIALPORT)

#include <SLIPEncodedSerial.h>
#include <SLIPEncodedUSBSerial.h>


extern void initOSC(void);
extern void updateOSC(void);

extern void routeILDA(OSCMessage& msg,int addressOffset,OSCBundle& replyStack);
extern void routeShape(OSCMessage& msg,int addressOffset,OSCBundle& replyStack);

#endif // !defined(_OSC_H_)
