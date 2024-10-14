import serial.tools.list_ports
import speech_recognition as sr

r = sr.Recognizer()

ports = serial.tools.list_ports.comports()
serialInst = serial.Serial()
portlist = []
for onePort in ports:
    portlist.append(str(onePort))

# CHANGE COM PORT HERE
val = 6
for x in range(0, len(portlist)):
    if portlist[x].startswith("COM" + str(val)):
        portvar = "COM" + str(val)

serialInst.baudrate = 9600
serialInst.port = portvar
serialInst.open()

def record_text():
    while True:
        try:
            with sr.Microphone() as Source2:
                r.adjust_for_ambient_noise(Source2, duration=0.02)
                audio2 = r.listen(Source2)
                myText = r.recognize_google(audio2)
                return myText.lower()
        except sr.RequestError as e:
            print("Could not request results: {0}".format(e))
        except sr.UnknownValueError:
            print("Didn't get you.")

while True:
    print("Tell me your command.")
    command = record_text()
    
    if "forward" in command:
        print("Moving forward")
        dir = 'F'
        serialInst.write(dir.encode('utf-8'))
    elif "backward" in command:
        print("Moving backward")
        dir = 'B'
        serialInst.write(dir.encode('utf-8'))
    elif "up" in command:
        print("Moving up")
        dir = 'U'
        serialInst.write(dir.encode('utf-8'))
    elif "down" in command:
        print("Moving down")
        dir = 'D'
        serialInst.write(dir.encode('utf-8'))
    elif "left" in command:
        print("Moving left")
        dir = 'L'
        serialInst.write(dir.encode('utf-8'))
    elif "right" in command:
        print("Moving right")
        dir = 'R'
        serialInst.write(dir.encode('utf-8'))
