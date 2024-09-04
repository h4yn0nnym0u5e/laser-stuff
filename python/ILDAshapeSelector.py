from oscutil import OSCutil

osc=OSCutil('COM9')
if 0:
    print(osc.packAuto('/teensy1/ilda/list','/'))
    msg = osc.packAuto('/teensy1/shape/load',7,'/ilda/triangle-3pt.ild',
                       True,'heap',b'0x00ab0x03',99.7)
    print(msg)
    unpk = osc.unpackAuto(msg)
    print(unpk)
    params = osc.unpackParams(unpk['tags'],unpk['rawParams'])
    print(params)
    msg = osc.packAuto('/teensy1/shape/load',7,'/ilda/triangle-3pt.ild','heap')
    osc.send(msg)
    print(osc.packAuto('/teensy1/shape/play',0,30.0))
    rv = osc.receive()
    print(rv)
    print(OSCutil.unpackAuto(rv))
    print(osc.receive())

msg = osc.packAuto('/teensy1/ilda/init','/')
osc.send(msg)
rv = osc.receive()
rvd = OSCutil.unpackAuto(rv)
fcount = rvd['content'][0]['params'][1]
for i in range(0,fcount):
    msg = osc.packAuto('/teensy1/ilda/entry',i)
    osc.send(msg)
    rv = osc.receive()
    rvd = OSCutil.unpackAuto(rv)
    fname = rvd['content'][0]['params'][1]
    print(fname)
    
