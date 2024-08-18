import os
import re
import struct

fp = "D:/Installers/Laser" # /shownet"
fp = "E:/Jonathan/Teensy/laser-stuff"

print("file,fmt,recs,total")
# print(file,ilda,fmt,name,company,recs,num,total,proj)
for root,dirs,files in os.walk(fp):
    for file in files:
        if re.search("[.]ild$",file):
            f = open(os.path.join(root,file),"rb")
            hdr = f.read(32)
            ilda,fmt,name,company,recs,num,total,proj = struct.unpack(">4sxxxB8s8sHHHBx",hdr)
            print(file,fmt,recs,total)
            # print(file,ilda,fmt,name,company,recs,num,total,proj)
            f.close()
