/*
 * This file contains the methods used to process OSC messages
 * destined for various laser synth sub-systems.
 * 
 * So far it deals with ILDA file lists on SD, and Shapes
 */
#include "osc.h"
#include "ILDAlist.h"

extern Shapes<NUM_SHAPES> shapes;

/*
 * Functions to apply ILDA methods sent by OSC
 */
void routeILDA(OSCMessage& msg,int addressOffset,OSCBundle& reply) 
{
  static ILDAlist* pList = nullptr;
  OSCMessage& repl = OSCUtils::staticPrepareReplyResult(msg,reply);

  // load list of files
  if (OSCUtils::isStaticTarget(msg,addressOffset,"/init","s"))
  {
    char root[50];
    msg.getString(0,root,50);
    
    if (nullptr != pList)
      delete pList;

    pList = new ILDAlist(SD,root);
    repl.add(pList->fileCount()).add(0);
  }
  else if (nullptr != pList)
  {
    // get an entry from the list
    if (OSCUtils::isStaticTarget(msg,addressOffset,"/entry","i"))
    {
      int fnum = msg.getInt(0);
      if (fnum <= pList->fileCount())      
        repl.add(pList->getPath(fnum)).add(0);
      else
        repl.add((int) OSCUtils::NOT_FOUND);
    }
    
  }
  else    
    repl.add((int) OSCUtils::NOT_CONNECTED);
}

/*
 * Function to apply Shape methods sent by OSC
 */
void routeShape(OSCMessage& msg,int addressOffset,OSCBundle& reply) 
{
  OSCMessage& repl = OSCUtils::staticPrepareReplyResult(msg,reply);

  // load ILDA file to RAM, with data in given shapes[] element
  if (OSCUtils::isStaticTarget(msg,addressOffset,"/load","iss"))
  {
    int slot;
    char where[5];
    char fn[50];

    slot = msg.getInt(0);
    msg.getString(1,fn,50);
    msg.getString(2,where,50);
    DEBUGSERIALPORT.printf("Load shape %s to slot %d, using %s\r\n", fn, slot, where);
    if (slot < shapes.count())
    {
      Shape& shape = shapes[slot];  
      bool ok = false;
      
      if (0 == strncmp(where, "heap", 4))
        ok = shape.loadHeap(fn);
      else if (0 == strncmp(where, "ext", 3))
        ok = shape.loadExt(fn);

      repl.add(ok?(int) OSCUtils::OK:(int) OSCUtils::NOT_FOUND);
    }
  }
  else if (OSCUtils::isStaticTarget(msg,addressOffset,"/entry","i"))
  {
    int slot;
    
    slot = msg.getInt(0);
    if (slot < shapes.count())
    {
      Shape& shape = shapes[slot];

      if (shape.isReady())
        repl.add(shape.getFilename()).add((int) OSCUtils::OK);
      else        
        repl.add("<empty>").add((int) OSCUtils::OK);
    }
    else
      repl.add((int) OSCUtils::NOT_FOUND);
    
  }
  else if (OSCUtils::isStaticTarget(msg,addressOffset,"/slots",NULL))
  {
    repl.add(shapes.count()).add((int) OSCUtils::OK);
  } 
}
