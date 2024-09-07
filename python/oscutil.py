import serial # need to "pip install pyserial" for this to work
import sliplib # need to "pip install sliplib" for this to work
import struct

class OSCutil:
    def __init__(self, port=None):
        self.ser = None
        if port is not None:
            try:
                # Set up communication channel
                self.ser = serial.Serial(port,115200,timeout=1)
                self.SLIPser = sliplib.SlipStream(self.ser,chunk_size=1)
            except:
                pass                

    def isConnected(self):
        return self.ser is not None

    def __del__(self):
        if self.ser is not None:
            self.ser.close()

    def send(self, msg):
        if self.ser is None:
            print(msg)
        else:
            self.SLIPser.send_msg(msg)

    def receive(self):
        if self.ser is None:
            msg = "/disconnected"
        else:            
            msg = self.SLIPser.recv_msg()
        return msg
    
        
        
        
    # Pad a string or bytes object out to a multiple of 4 octets
    @staticmethod
    def pad(s):
        if isinstance(s,str): # needs a \0 terminator
            r = bytes(s.encode('ascii'))+b'\x00'+b'\x00'*((-1-len(s))%4)
        else: # doesn't need a terminator
            r = s + b'\x00'*((-len(s))%4)
        #r = bytes(b'\x00'+b'\x00'*((-1-len(s))%4))
        #print(r)
        return r


    # Pack an address, parameter types and parameters into an OSC message
    @staticmethod
    def pack(addr,pt,*argv):
        addr = OSCutil.pad(addr)
        ptp = OSCutil.pad(','+pt)
        fmt = '>' + str(len(addr))+'s' + str(len(ptp))+'s'
        rv = bytes(struct.pack(fmt,addr,ptp))
        for i in range(len(argv)):
            rv += bytes(struct.pack('>'+pt[i],argv[i]))
        #print(rv)
        return rv

     

    # Pack an address and parameters into an OSC message
    # The types of the parameters are determined automatically
    @staticmethod
    def packAuto(addr,*argv):
        pt = ''
        rv = b''
        for v in argv:
            if isinstance(v,bool):
                t = 'T' if v else 'F'
            elif isinstance(v,int):
                t = 'i'
            elif isinstance(v,float):
                t = 'f'
            elif isinstance(v,float):
                t = 'f'
            elif isinstance(v,str):
                t = 's'
                v = OSCutil.pad(v)
            else:
                t = 'b'
                v = struct.pack('>i',len(v)) + OSCutil.pad(v)
            pt += t
            if t not in 'TF': # not a bool: pack the data
                l=''
                if t in 'sb': # string or blob
                    l = str(len(v))
                if 'b' == t:
                    t = 's'
                rv += bytes(struct.pack('>'+l+t,v))
            
        addr = OSCutil.pad(addr)
        ptp = OSCutil.pad(','+pt)
        fmt = '>' + str(len(addr))+'s' + str(len(ptp))+'s'
        rv = bytes(struct.pack(fmt,addr,ptp)) + rv
        #print(rv)
        return rv

    # Unpack an OSC message
    @staticmethod
    def unpackAuto(msg):
        if b'' == msg:
            return {}
        elif b'#bundle\x00' != msg[0:8]:
            msgl = msg.split(b',') # split address from parameters
            addrl = list(map(lambda b : b.decode('ascii'),msgl[0].split(b',')[0].strip(b'\x00').split(b'/')))[1:]
            tags, off = OSCutil.unpackParam('s', b',' + msgl[1])
            result = {'addr': addrl, 'tags': tags[1:], 'rawParams': msgl[1][off-1:]}
            result['params'] = OSCutil.unpackParams(tags[1:], result['rawParams'])
            return result
        else:  # it's a bundle
            timetag, size = struct.unpack_from('>qi',msg[8:])
            result = {'timetag': timetag}
            msg = msg[20:]
            result ['content'] = []
            while msg != b'':
                result['content'] += [OSCutil.unpackAuto(msg[:size])]
                msg = msg[size:]
            return result                


    # Unpack a message parameter
    @staticmethod
    def unpackParam(tag, b):
        if 'b' == tag:
            l = struct.unpack_from('>i',b)[0]
            v = b[4:4+l]
            l = 4 + l + ((-l)%4)
            print(l)
        if 'i' == tag:
            v = struct.unpack_from('>i',b)[0]
            l = 4
        elif 'f' == tag:
            v = struct.unpack_from('>f',b)[0]
            l = 4
        elif 'T' == tag or 'F' == tag:
            v = True if 'T' == tag else False
            l = 0
        elif 's' == tag:
            v = b.split(b'\x00')[0].decode('ascii')
            l = len(v) +1 + ((-1-len(v))%4)

        return (v,l)            
    
    # Unpack a message parameter
    @staticmethod
    def unpackParams(expect, b):
        result = []
        while '' != expect:
            v,l = OSCutil.unpackParam(expect[0], b)
            result += [v]
            b = b[l:]
            expect = expect[1:]

        return result
            


    # Make an OSC bundle for execution at time ttag, from the
    # elements in ell. If any elements are themselves bundles, it
    # is assumed that their timetags are >= ttag
    # The default timetag is 1, which means "immediately"
    @staticmethod
    def makeBundle(ell,ttag=1):
        rv = OSCutil.pad(b'#bundle') + struct.pack(">Q",ttag)
        for el in ell:
            rv += struct.pack(">L%ds" % len(el),len(el),el)
        #print(rv)
        return rv
