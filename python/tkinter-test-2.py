from tkinter import *
from tkinter import ttk
from oscutil import OSCutil

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
        frm.rowconfigure(1,weight=1)
        ttk.Label(frm, text="Hello World!").grid(column=0, row=0)
        ttk.Button(frm, text="Quit", command=root.destroy).grid(column=1, row=0)
        
        entry_var = StringVar()
        entry = ttk.Entry(frm, textvariable=entry_var).grid(column=2, row=0, rowspan=2, sticky="news")
        
        undr = ttk.Frame(frm, padding=10, name="undr")
        undr.configure(borderwidth=2, relief="raised")
        undr.grid(column=0, row=1, columnspan=2, sticky="news")
        undr.columnconfigure(0,weight=1)
        undr.rowconfigure(1,weight=1)
        #undr.grid()
        ttk.Label(undr, text="ILDA files on SD").grid(column=0, row=0, columnspan=2, sticky="w")
        
        scrollbar = ttk.Scrollbar(undr)
        listbox = ttk.Treeview(undr, yscrollcommand=scrollbar.set, show="tree")
        scrollbar.configure(command=listbox.yview)
        
        listbox.grid(row=1, column=0, sticky="news")
        scrollbar.grid(row=1, column=1, sticky="nse")

        self.root = root
        self.osc=OSCutil(port)
        self.listbox = listbox
        self.entry_var = entry_var

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
                    if folder == tl[-1]:
                        where = "end" 
                    else:
                        depths[path] += 1
                    self.listbox.insert(path, where, iid=newPath, text=folder)
                path = newPath
            
       
def onClick(event: Event, entry_var):
    wdg = event.widget
    sel = wdg.selection()
    print("you've selected ", end='')
    evv=''
    for item in sel:
        wit=wdg.item(item,"text")
        print(wit, item, end=', ')
        evv += item + ' '
    print()
    entry_var.set(evv)        

def onExit(event):
    pass

 
if __name__=="__main__":
    chooser=ILDAchooser('COM9')
    chooser.listbox.bind("<ButtonRelease-1>", lambda e:onClick(e, chooser.entry_var))
    chooser.OSCinit()
    chooser.OSCgetFiles()
    chooser.setupTree()
    chooser.root.mainloop()