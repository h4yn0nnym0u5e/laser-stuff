from tkinter import *
from tkinter import ttk
from oscutil import OSCutil
import re

class TreeFrame:
    def __init__(self, parent, label, loadTree, onClick, clickResult):            
        frame = ttk.Frame(parent, padding=5)
        frame.configure(borderwidth=2, relief="raised")
        frame.columnconfigure(0,weight=1)
        frame.rowconfigure(1,weight=1)
        ttk.Label(frame, text=label).grid(column=0, row=0, sticky="w")
        ttk.Button(frame, text="Load", command=loadTree).grid(column=1, row=0)
        
        scrollbar = ttk.Scrollbar(frame)
        listbox = ttk.Treeview(frame, yscrollcommand=scrollbar.set, show="tree",selectmode="browse")
        scrollbar.configure(command=listbox.yview)
        
        listbox.grid(row=1, column=0, columnspan=2, sticky="news")
        scrollbar.grid(row=1, column=2, sticky="nse")
        listbox.bind("<ButtonRelease-1>", lambda e:onClick(e, clickResult))

        self._root = frame
        self._listbox = listbox

    def root(self):
        return self._root  

    def listbox(self):
        return self._listbox   
        

class ILDAchooser:
    def __init__(self, port):
        root = Tk()
        root.title("ILDA Shape Loader")
        root.columnconfigure(0, weight=1)
        root.rowconfigure(0, weight=1)
        
        style=ttk.Style()
        style.theme_use("alt")
        style.configure("TButton", relief="raised")
        
        frm = ttk.Frame(root, padding=10, name="frm")
        frm.grid(sticky="news")
        frm.columnconfigure(0,weight=1)
        frm.columnconfigure(3,weight=1)
        frm.rowconfigure(1,weight=1)
        ttk.Label(frm, text="Hello World!").grid(column=0, row=0)
        ttk.Button(frm, text="Quit", command=root.destroy).grid(column=4, row=0, sticky="e")
        
        #entry_var = StringVar()
        #entry = ttk.Entry(frm, textvariable=entry_var).grid(column=2, row=1, rowspan=2, sticky="news")
        ttk.Button(frm, text=">>>", command=self._loadFile, width=4).grid(column=2, row=1)
        
        if 0:
            ffiles = ttk.Frame(frm, padding=5, name="files")
            files.configure(borderwidth=2, relief="raised")
            files.grid(column=0, row=1, columnspan=2, sticky="news")
            files.columnconfigure(0,weight=1)
            files.rowconfigure(1,weight=1)
            #undr.grid()
            ttk.Label(files, text="ILDA files on SD").grid(column=0, row=0, sticky="w")
            ttk.Button(files, text="Load", command=self._loadTree).grid(column=1, row=0)
            
            scrollbar = ttk.Scrollbar(files)
            listbox = ttk.Treeview(files, yscrollcommand=scrollbar.set, show="tree")
            scrollbar.configure(command=listbox.yview)
            
            listbox.grid(row=1, column=0, columnspan=2, sticky="news")
            scrollbar.grid(row=1, column=2, sticky="nse")
            listbox.bind("<ButtonRelease-1>", lambda e:self.onClick(e, self.clickedFile))

        # Frame for list of files on the Teensy SD card
        self.clickedFile = None
        filesObj = TreeFrame(frm, "ILDA files on SD", self._loadTree, self.onClick, self.clickedFile)
        files=filesObj.root()
        files.grid(column=0, row=1, columnspan=2, sticky="news")
        self.listbox = filesObj.listbox()
        self._filesObj = filesObj

        # Frame for list of shapes
        self.clickedShape = None
        shapesObj = TreeFrame(frm, "Shapes loaded", self._loadShapeList, self.onClick, self.clickedShape)
        shapes=shapesObj.root()
        shapes.grid(column=3, row=1, columnspan=2, sticky="news")
        self.shapesbox: ttk.Treeview = shapesObj.listbox()
        self._shapesObj = shapesObj

        self.root = root
        self.osc=OSCutil(port)


    def OSCinit(self):
        """
        Request Teensy to generate list of ILDA files 
        internally, and return count of files found
        """
        osc = self.osc
        msg = osc.packAuto('/teensy1/ilda/init','/')
        osc.send(msg)
        rv = osc.receive()
        rvd = OSCutil.unpackAuto(rv)
        self.fcount = rvd['content'][0]['params'][1]

    def OSCgetFiles(self):
        """
        Retrieve list of ILDA files (paths) from Teensy,
        one at a time, and create local list
        """
        osc = self.osc
        self.files = []
        for i in range(0,self.fcount):
            msg = osc.packAuto('/teensy1/ilda/entry',i)
            osc.send(msg)
            rv = osc.receive()
            rvd = OSCutil.unpackAuto(rv)
            fname = rvd['content'][0]['params'][1]
            self.files += [fname]
        
    def setupTree(self):
        """
        Create the tree view of the ILDA files on SD,
        based on the local list retrieved earlier.

        The Teensy may supply these in a weird order, but
        we attempt to make it a bit clearer by at least
        listing sub-folders first, then files.
        """
        depths = {}
        for text in self.files:
            tl = text.split("/")[1:]
            path = ""
            for folder in tl:
                newPath = path + "/" + folder
                if not self.listbox.exists(newPath):
                    if path not in depths:
                        depths[path] = 0
                    where = depths[path]
                    if folder == tl[-1]:  # file, not folder
                        where = "end" 
                    else:
                        depths[path] += 1
                    self.listbox.insert(path, where, iid=newPath, text=folder)
                path = newPath
            
    def _loadTree(self):
        """
        Load files tree from Teensy, using OSC
        """
        self.OSCinit()
        self.OSCgetFiles()
        self.setupTree()

    def _shapeText(self, slot, name):
        return f"Slot {slot}:  {name}"

    def _loadShapeList(self):
        """
        (Re-)load the list of loaded shapes from the Teensy
        """
        osc = self.osc
        msg = osc.packAuto('/teensy1/shapes/slots')
        osc.send(msg)
        rv = osc.receive()
        rvd = OSCutil.unpackAuto(rv)
        self.scount = rvd['content'][0]['params'][1]

        self.shapes = {}
        for i in range(self.scount):
            msg = osc.packAuto('/teensy1/shapes/entry',i)
            osc.send(msg)
            rv = osc.receive()
            rvd = OSCutil.unpackAuto(rv)
            print(rvd)
            self.shapes[i] = rvd['content'][0]['params'][1]

        self.shapesbox.delete(*self.shapesbox.get_children())
        for idx in self.shapes:
            self.shapesbox.insert("", "end", iid=f"shape{idx}", text=self._shapeText(idx, self.shapes[idx]))

    def nextAfter(self, iid, li: list):
        idx = li.index(iid)+1  # iid MUST be in list, by definition!
        if idx >= len(li): # off end... 
            idx = 0 # ...loop back
        return li[idx]

    def _loadFile(self):
        print(f"Load {self.clickedFile} to {self.clickedShape}")
        osc = self.osc
        msg = osc.packAuto('/teensy1/shapes/load',self.clickedShape, self.clickedFile, "ext")
        osc.send(msg)
        rv = osc.receive()
        rvd = OSCutil.unpackAuto(rv)
        if 0 == rvd['content'][0]['params'][1]:  # success
            clickedShapeID = f"shape{self.clickedShape}"
            self.shapesbox.item(clickedShapeID, text=self._shapeText(self.clickedShape, self.clickedFile))
            # auto-move to next entry: files...
            parent = "/".join(self.clickedFile.split("/")[:-1])
            siblings = list(self.listbox.get_children(parent))    
            self.clickedFile = self.nextAfter(self.clickedFile, siblings) # fake we clicked it
            self.listbox.selection_set(self.clickedFile)
            # ...and shapes
            shapes = list(self.shapesbox.get_children())
            nextShape = self.nextAfter(clickedShapeID, shapes)
            self.clickedShape = self.shapeIDtoIndex(nextShape)  # fake we clicked it
            self.shapesbox.selection_set(nextShape)

    def shapeIDtoIndex(self, id):
        result = None
        mtch = re.search("shape([0-9]+)",id)
        if mtch:  # click in shapes list
            result = int(mtch.group(1))

        return result            

    def onClick(self, event: Event, entry_var):
        """
        Deal with click in ILDA files tree
        """
        wdg = event.widget
        sel = wdg.selection()
        print("you've selected ", end='')
        evv=''
        for item in sel:
            wit=wdg.item(item,"text")
            print(wit, item, end=', ')
            evv += item + ' '
        print()
        shapeIndex = self.shapeIDtoIndex(evv)
        if shapeIndex is not None:
            self.clickedShape = shapeIndex
        else:            
            self.clickedFile = evv.strip()        

 
if __name__=="__main__":
    chooser=ILDAchooser('COM9')
    chooser.root.mainloop()