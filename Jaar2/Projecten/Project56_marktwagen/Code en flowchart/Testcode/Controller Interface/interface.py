from tkinter import *
from tkinter import ttk
import tkinter
from turtle import bgcolor, right
from bluetooth import *
import sys
from time import *

#bluetooth addr of esp
addr = "30:C6:F7:29:F7:82"

if len(sys.argv) < 2:
    print("no device specified.  Searching all nearby bluetooth devices for")
    print("the SampleServer service")
else:
    addr = sys.argv[1]
    print("Searching for SampleServer on %s" % addr)

buf_size = 1024
service_matches = find_service( address = addr )

if len(service_matches) == 0:
    print("couldn't find the SampleServer service =(")
    sys.exit(0)

first_match = service_matches[0]
port = first_match["port"]
name = first_match["name"]
host = first_match["host"]


print("connecting to \"%s\" on %s" % (name, host))

sock=BluetoothSocket( RFCOMM )
sock.connect((host, port))

#connected to esp
print("connecteted")


root = Tk()

maincolor1 = "#0194da"
maincolor2 = "#FFFFFF"
blank = "#000000"
currentbeacon = ""

root.geometry('800x480')
root.resizable(width=0, height=0)
root.configure(bg=maincolor1)




def popup(confirm):
    confirmpopup.place(x=0, y=0)
    popuplabel = Label(confirmpopup, fg=maincolor2, bg=maincolor1, text="Stuur hoverB naar " + confirm , font=("Arial", 20))
    popuplabel.place(x=280, y=10)
    currentbeacon = confirm
    jabutton = Button(confirmpopup, text="JA",  height=4, width=10, fg=maincolor2 ,bg="green",font=("Arial", 40), command=lambda: japopup(confirm)).place(x=40, y=100)
    neebutton = Button(confirmpopup, text="NEE", height=4, width=10, fg=maincolor2, bg="red", font=("Arial", 40), command=neepopup).place(x=420, y=100)

def japopup(confirmedbeacon):
    print("ja" + confirmedbeacon)
    confirmpopup.place(x=9999, y=99999)
    sock.send(confirmedbeacon)

def neepopup():
    confirmpopup.place(x=9999, y=99999)

def stop():
    while True:
        sock.send("1")
        sleep(5)

def follow():
    sock.send("follow")
    #start sending location every few ms    

def follow():
    sock.send("follow")
    #start sending location every few ms
    for i in range(20):
        sock.send(b"52.239857283578, 4.34242323422 \n")
        sleep(1)
xbutton = Button(root, text='STOP', width=10, 
             height=2, command=stop, borderwidth=0, fg="black", bg="red", font=("Arial", 40))
  
xbutton.place(x=30, y=50)

followbutton = Button(root, text='follow', width=10, height=2, command=follow, borderwidth=0, fg=maincolor1, bg=maincolor2, font=("Arial", 40))

followbutton.place(x=30, y=230)

scrollframe = Canvas(root, height=800, width=400, bg=maincolor1, highlightthickness=0)


scrollframe.place(x=400, y=40)

def down():
    scrollframe.place(x=400, y=-500)
def up():
    scrollframe.place(x=400, y=50)

beacon1 = Button(scrollframe, command=lambda: popup("1"), text='#1', width=5, height=2, borderwidth=0, fg=maincolor1, bg=maincolor2, font=("Arial", 40)).place(x=30, y=30)
beacon2 = Button(scrollframe, command=lambda: popup("beacon2"),text='#2', width=5, height=2, borderwidth=0, fg=maincolor1, bg=maincolor2, font=("Arial", 40)).place(x=220, y=30)
beacon3 = Button(scrollframe, command=lambda: popup("beacon3"),text='#3', width=5, height=2, borderwidth=0, fg=maincolor1, bg=maincolor2, font=("Arial", 40)).place(x=30, y=200)

beacon4 = Button(scrollframe, command=lambda: popup("beacon4"),text='#4', width=5, height=2, borderwidth=0, fg=maincolor1, bg=maincolor2, font=("Arial", 40)).place(x=220, y=200)

downbuton = Button(scrollframe, text='scrolldown', width=21, height=1, command=down,borderwidth=0, fg=maincolor1, bg=maincolor2, font=("Arial", 20)).place(x=30, y=380)
downbuton = Button(scrollframe, text='scrollup', width=21, height=1, command=up,borderwidth=0, fg=maincolor1, bg=maincolor2, font=("Arial", 20)).place(x=30, y=550)


beacon5 = Button(scrollframe, command=lambda: popup("5"),text="#5", width=5, height=2, borderwidth=0, fg=maincolor1, bg=maincolor2, font=("Arial", 40)).place(x=30, y=630)
beacon6 = Button(scrollframe, command=lambda: popup("6"),text="#6", width=5, height=2, borderwidth=0, fg=maincolor1, bg=maincolor2, font=("Arial", 40)).place(x=220, y=630)


beacons = Label(root, text="Beacons:",bg=maincolor1, fg=maincolor2, font=("Arial", 25))
beacons.place(x=400, y=3)


confirmpopup = Canvas(root, bg=maincolor1, height=480, width=800, highlightthickness=0)




root.mainloop()

