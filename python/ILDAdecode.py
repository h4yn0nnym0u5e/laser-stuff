import struct
import os

fmtll = [8,6,3,0,10,8]

fn = "ilddolf.ild"
fp = "../ilda"
ffp = os.path.join(fp,fn)
print(ffp)

f = open(ffp,"rb")
while True:
    try:
        hdr = f.read(32)
        vals = struct.unpack(">4sbbbb8s8shhhbb",hdr)
        vald = {"ILDA": vals[0], "format": vals[4],
                "name": vals[5], "company": vals[6],
                "records": vals[7], "number": vals[8],
                "total": vals[9], "projector": vals[10]}
        print(vald)
        seekTo = f.tell()
        seekTo += fmtll[vals[4]] * vals[7]
        f.seek(seekTo)
    except:    
        break
f.close()
    
