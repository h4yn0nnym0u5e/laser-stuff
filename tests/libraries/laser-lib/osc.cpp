#include "osc.h"

SLIPEncodedClass HWSERIAL(OSCSERIALPORT);

OSCBundle* replyStack; // where reply is currently being built
//-----------------------------------------------------------------------------------------------------------------
// Append error code if message didn't reach a destination
void checkIfRouted(OSCBundle* reply, const char* dst)
{
  if (1 == reply->size())
  {
    OSCMessage* pMsg = reply->getOSCMessage(0);
    if (0 == pMsg->size()) // message wasn't routed...
      pMsg->add(dst).add((int) OSCUtils::NOT_FOUND);
  }
}


//-----------------------------------------------------------------------------------------------------------------
// route messages to deal with ILDA files on SD
void msgRouteILDA(OSCMessage& msg, int addressOffset)
{
  routeILDA(msg,addressOffset,*replyStack);
  checkIfRouted(replyStack,"subscribe");
}


//-----------------------------------------------------------------------------------------------------------------
// route messages to Shape functions
void msgRouteShape(OSCMessage& msg, int addressOffset)
{
  routeShape(msg,addressOffset,*replyStack);
  checkIfRouted(replyStack,"shape");
}


//-----------------------------------------------------------------------------------------------------------------
// Process a message. Because we can only extract messages from a bundle 
// by address, we have to accept a pointer rather than a reference
void processMessage(OSCMessage* msg,OSCBundle& reply)
{
  char prt[200];
  OSCBundle* replyPush = replyStack;
  replyStack = &reply;
  
  if (!msg->hasError())
  {
    msg->getAddress(prt);  
    //DEBUGSERIALPORT.println(prt);
    //DEBUGSERIALPORT.flush();

    // This is the key point at which the user can route incoming OSC messages
    // to whichever engines they choose to implement. The OSCAudio library
    // implements /audio and /dynamic, but /fs is implemented within this demo
    
    if (!msg->route("/teensy*/ilda",msgRouteILDA))      // see if this object can use the message
      if (!msg->route("/teensy*/shapes",msgRouteShape)) // or this one
         reply.getOSCMessage(0)->add((int) OSCUtils::NOT_FOUND);  // got no takers - say so
  }
  else
  {
    DEBUGSERIALPORT.println("error in msg");
    reply.getOSCMessage(0)->add((int) OSCUtils::NOT_FOUND);
  }
  
  replyStack = replyPush;
}


void processBundle(OSCBundle* bndl,OSCBundle& reply)
{
  int bndlSize = bndl->size();

  if (!bndl->hasError())  
  {
    for (int i=0;i<bndlSize;i++)
    {
      OSCMessage* msg = bndl->getOSCMessage(i); 
      //DEBUGSERIALPORT.printf("Message %d\n",i);
      processMessage(msg,reply);   
    }  
  }
  else
  {
    //DEBUGSERIALPORT.printf("error %d in bundle\n",(int) bndl->getError());
    
    for (int i=0;i<bndlSize;i++)
    {
      OSCMessage* msg = bndl->getOSCMessage(i); (void) msg;
      //DEBUGSERIALPORT.printf("error %d in message %d\n",(int) msg->getError(),i);
    }
  }  
}


void sendReply(OSCBundle& reply)
{
  int errCount = 0;
  // for debug
  // reply.send(DEBUGSERIALPORT);
  OSCMessage* pMsg;

  checkIfRouted(&reply,"teensy");
  
  DEBUGSERIALPORT.printf("Reply has %d messages, %d OSC errors\n",reply.size(),reply.hasError()); 
  for (int i=reply.size()-1;i>=0;i--)
  {
    pMsg = reply.getOSCMessage(i);
    int last = pMsg->size()-1;
    int errv;
    if (last > 0 && pMsg->isInt(last) && (errv = pMsg->getInt(last)) != 0)
    {
      errCount++;
      DEBUGSERIALPORT.printf("%d ",errv);
    }
  }
  if (errCount > 0)
    DEBUGSERIALPORT.printf(": %d error flags\n",errCount);

  // for real!
  HWSERIAL.beginPacket();
  reply.send(HWSERIAL); 
  HWSERIAL.endPacket();
}


//-----------------------------------------------------------------------------------------------------------------
// work with SLIP-protocol serial port:
void updateOSC()
{
  static enum {boot,reading,processing} state = boot;
  static OSCBundle* bndl;
  static OSCBundle reply;
  static OSCMessage msg;
  long long tt = 0; //0x4546474841424344; // for debug: ABCDEFGH
  static char firstCh = 0;
  int msgLen;

  switch (state)
  {
    case boot:
      DEBUGSERIALPORT.print("Waiting...");
      bndl = new OSCBundle; // because empty() doesn't work...
      //bndl->empty();
      reply.empty();
      msg.empty();
      firstCh = 0;
      state = reading;
      break;
    
    case reading:
      if (!HWSERIAL.endofPacket())
      {    
        msgLen = HWSERIAL.available(); // only ever returns 0 or 1, actually
        while (msgLen--)
        {
          char c = HWSERIAL.read();            
          // figure out if it's a message or a bundle
          if (0 == firstCh)
            firstCh = c;
          if ('#' == firstCh)
            bndl->fill((uint8_t) c); // simple messages should result in a 1-message "bundle", but don't
          else
            msg.fill((uint8_t) c); // so process them specifically
        }
      }
      else
      {
        state = processing;
      }
      break;

    case processing:  
      DEBUGSERIALPORT.println("processing!");
      reply.setTimetag((uint8_t*) &tt).add("/reply"); // create first message with reply address: used for all messages
      
      if ('#' == firstCh)
      {
        processBundle(bndl,reply);
        sendReply(reply);
      }
      else 
      {
        if ('/' == firstCh) 
        {
          processMessage(&msg,reply);   
          sendReply(reply);
        }
      }
      DEBUGSERIALPORT.println();
      delete bndl;
      state = boot;
      break;
  }
}


void initOSC(void)
{
  HWSERIAL.begin(115200);
  HWSERIAL.setTimeout(100);
}
