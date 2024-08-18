from tkinter import *
from tkinter import ttk
import serial
import copy

#####################################################
class DummySer():
    def readline(self):
        return b''
    def write(self, s):
        print(f"Serial: {s}")
    def close(self):
        print("Serial closed")
        
#####################################################
try:
    ser = serial.Serial('COM32',115200,timeout=0.01)
except:
    ser = DummySer()
    print("Using dummy serial port!")
done = False

#####################################################
mw = Tk()
mw.title('ILDA controls')
mw.minsize(width=200,height=0)
w = ttk.Frame(mw,padding = '5 5 5 5',borderwidth=2)
w.grid(column=0,row=0)
#w['padding'] = '5 5 5 5'
w['borderwidth'] = 2
w['relief'] = 'sunken'

#####################################################
colours = {}
currentColour = 0
currentShift = 8
theLabel = None
picoLabel = None
scales = []

#####################################################
theMessage = ''
def serPoll():
    global theMessage,picoLabel,scales
    theMessage += str(ser.readline(),'ascii')
    if '\n' in theMessage:
        theMessage = theMessage.strip()
        picoLabel['text'] = theMessage

        if 'g' == theMessage[0]:
            nn = list(map(int,theMessage[1:].split(',')))
            for sc in range(len(scales)):
                scales[sc].update_lbl(nn[sc+1]) # skip the channel
        theMessage = ''
        
        
        
#####################################################
def xprint(s):
    print(s)

def setColour(n,rgb,val):
    global scales,colours,ser,currentShift
    emit='colour'
    if n not in colours:
        colours[n] = [0]*len(scales)
    if 'XYg' == rgb:
        colours[n][0] = val
    elif 'Xo' == rgb:
        colours[n][1] = val
    elif 'Yo' == rgb:
        colours[n][2] = val
    elif 'RGBg' == rgb:
        colours[n][3] = val
    elif 'RGBo' == rgb:
        colours[n][4] = val
        #currentShift = val
        #emit = 'shift'
    else:
        emit = False

    if 'colour' == emit:
        print(f"Set {n} to {colours[n]}")
        ser.write(f"s {n},{','.join(map(str,colours[n]))}\n".encode())
    elif 'shift' == emit:
        print(f"Set shift to {currentShift}")
        ser.write(f"> {currentShift}\n".encode())
    else:
        pass
    

def scaleChange(name,val):
    #xprint(f"{name}: {val}")
    setColour(currentColour,name,val)
    

def buttonPress(name,val):
    global currentColour,theLabel,done
    xprint(f"{name}: {val}")

    if 'OK' == name:
        print(colours)

    if 'Cancel' == name:
        done = True

    if '>' == val:
        currentColour += 1
    
    if '<' == val and currentColour > 0:
        currentColour -= 1

    if val in '<>':
        print(f"Setting LED {currentColour}")
        theLabel['text'] = f"LED {currentColour}"
        ser.write(f"g {currentColour}\n".encode())
        
    

class CScale():
    def __init__(self,w,x,y,nm,f=255,t=0):
        self.name = nm
        self.val = IntVar()
        self.txt = ttk.Label(w,text=nm).grid(column=x,row=y)
        self.lbl = ttk.Label(w,textvariable=self.val).grid(column=x,row=y+1)
        self.scl = ttk.Scale(w,orient='vertical',length=200,from_=f,to=t,variable=self.val,command=self.update_lbl)
        self.scl.grid(column=x,row=y+2)

    def update_lbl(self,val):
        self.val.set(int(float(val)))
        scaleChange(self.name,self.val.get())
        
class CButton():
    def __init__(self,w,x,y,nm,send):
        self.name = nm
        self.send = send
        self.scl = ttk.Button(w,text=self.name,command=self.update_lbl)
        self.scl.grid(column=x,row=y)

    def update_lbl(self):
        buttonPress(self.name,self.send)
        
#####################################################
rscl=CScale(w,0,0,"XYg")
xscl=CScale(w,1,0,"Xo")
yscl=CScale(w,2,0,"Yo")
bscl=CScale(w,3,0,"RGBg")
sscl=CScale(w,4,0,"RGBo")

scales = [rscl,xscl,yscl,bscl,sscl]

bf = ttk.Frame(mw,padding = '5 5 5 5',borderwidth=2)
bf['relief'] = 'sunken'

theLabel = ttk.Label(bf,text='buttons!')
theLabel.grid(column=0,row=0)

#bt = ttk.Button(bf,text='OK').grid()
okBut  = CButton(bf,0,1,'OK','k')
canBut = CButton(bf,0,2,'Cancel','X')
gtBut  = CButton(bf,0,3,'>>>','>')
ltBut  = CButton(bf,0,4,'<<<','<')

picoLabel = ttk.Label(bf,text='***')
picoLabel.grid(column=0,row=5)

buttonPress('','<') # set text


bf.grid(column=1,row=0,sticky='n')
    

while not done:
    try:
        serPoll()
        mw.update_idletasks()
        mw.update()
    except Exception as e:
        print(e)
        done = True
        
ser.close()
try:
    mw.destroy()
except Exception as e:
    print(e)
    
print("Done!")

