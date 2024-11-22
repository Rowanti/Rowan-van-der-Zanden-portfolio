from machine import Pin
import utime, network, urequests, json
import _thread

led_onboard = Pin("LED", Pin.OUT)
button = Pin(0, Pin.IN, Pin.PULL_UP)
leds = (Pin(6, Pin.OUT),Pin(7, Pin.OUT),Pin(14, Pin.OUT),Pin(8, Pin.OUT))

ssid = 'Tesla IoT'
password = 'fsL6HgjN'
PostIp = 'http://145.137.110.40:8080/noodstop'
Ip = 'http://145.137.110.40:8080/seedata'
HTTP_HEADERS = {'Content-Type': 'application/json'}

def connect():
    # Connect to WLAN
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(ssid, password)
    while not wlan.isconnected():
        print('Waiting for connection...')
        utime.sleep(1)
    ip = wlan.ifconfig()[0]
    print(f'Connected on {ip}')
    return ip

def ledControl(led):
    
    for i in range (len(leds)):
        leds[i].high() if i == led else leds[i].low()

def recieveData():
    direction = urequests.get(url=Ip)
    data = json.loads(direction.text)
    rowan_data = data['rowan']
    direction_value = rowan_data['direction']
    direction.close()
    return direction_value

def sendData(waarde):
    dht_readings = {'noodstop':waarde}
    request = urequests.post(url = PostIp ,json = dht_readings, headers = HTTP_HEADERS)
    request.close()
    

connect()
oldbutton = 0
while True:
    button_value = button.value()
    print('button ', end= "")
    print(button_value)
    if button_value!=oldbutton:
        sendData(button_value)
        oldbutton = button_value       
    
    direction_value = recieveData()
    ledControl(direction_value)
    print('direction ', end = "")
    print(direction_value)

    utime.sleep(0.005)