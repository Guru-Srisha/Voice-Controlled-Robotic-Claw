import RPi.GPIO as GPIO
import speech_recognition as sr
import serial
import time

BUTTON_PIN = 17 # Pin 11 for button
LED_PIN = 27 # Pin 13 for LED

GPIO.setmode(GPIO.BCM)
GPIO.setup(BUTTON_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(LED_PIN, GPIO.OUT)

ser = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(2)

recognizer = sr.Recognizer()

def listen_and_send_commands():
    with sr.Microphone(device_index=<mic_index>) as source: # Change your mic index here
        GPIO.output(LED_PIN, GPIO.HIGH)

        try:
            recognizer.adjust_for_ambient_noise(source, duration=0.5)
            audio = recognizer.listen(source, timeout=1, phrase_time_limit=1.5)
            command = recognizer.recognize_google(audio).lower()

            if "left" in command:
                ser.write('L'.encode('utf-8'))
            elif "right" in command:
                ser.write('R'.encode('utf-8'))
            elif "up" in command:
                ser.write('U'.encode('utf-8'))
            elif "down" in command:
                ser.write('D'.encode('utf-8'))
            elif "front" in command:
                ser.write('F'.encode('utf-8'))
            elif "back" in command:
                ser.write('B'.encode('utf-8'))
            elif "pick" in command or "grab" in command or "close" in command:
                ser.write('C'.encode('utf-8'))
            elif "open" in command or "drop" in command:
                ser.write('O'.encode('utf-8'))

        except sr.UnknownValueError:
            pass
        except sr.RequestError as e:
            pass
        except sr.WaitTimeoutError:
            pass
        finally:
            GPIO.output(LED_PIN, GPIO.LOW)

try:
    while True:
        button_state = GPIO.input(BUTTON_PIN)
        if button_state == GPIO.LOW:
            listen_and_send_commands()
        time.sleep(0.1)

except KeyboardInterrupt:
    pass
finally:
    ser.close()
    GPIO.cleanup()
