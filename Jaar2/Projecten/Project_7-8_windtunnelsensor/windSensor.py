import machine
import time
import math

analogPinForRV = machine.ADC(26)   # change to the pins you are using
analogPinForTMP = machine.ADC(27)

zeroWindAdjustment = 0.2   # negative numbers yield smaller wind speeds and vice versa.

TMP_Therm_ADunits = 0
RV_Wind_ADunits = 0
RV_Wind_Volts = 0
lastMillis = 0
TempCtimes100 = 0
zeroWind_ADunits = 0
zeroWind_volts = 0
WindSpeed_MPH = 0

def setup():
    global lastMillis
    
    uart = machine.UART(0, 57600)
    time.sleep(1)   # wait for serial to be ready
    uart.write("start\n")
    
    # uncomment the three lines below to reset the analog pins A2 & A3
    # This is code from the Modern Device temp sensor (not required)
    #pin = machine.Pin(18, machine.Pin.IN)   # GND pin      
    #pin = machine.Pin(19, machine.Pin.IN)   # VCC pin
    #pin.value(0)   # turn off pullups
    
    lastMillis = time.ticks_ms()
def loop():
    while True:
        if time.ticks_ms() - lastMillis > 200:   # read every 200 ms - printing slows this down further
            TMP_Therm_ADunits = analogPinForTMP.read_u16()
            RV_Wind_ADunits = analogPinForRV.read_u16()
            RV_Wind_Volts = RV_Wind_ADunits * 0.0048828125

            # These are all derived from regressions from raw data as such they depend on a lot of experimental factors
            # such as accuracy of temp sensors, and voltage at the actual wind sensor, (wire losses) which were unaccounted for.
            TempCtimes100 = (0.005 *(TMP_Therm_ADunits * TMP_Therm_ADunits)) - (16.862 * TMP_Therm_ADunits) + 9075.4
            zeroWind_ADunits = -0.0006*(TMP_Therm_ADunits * TMP_Therm_ADunits) + 1.0727 * TMP_Therm_ADunits + 47.172
            zeroWind_volts = (zeroWind_ADunits * 0.0048828125) - zeroWindAdjustment

            # This from a regression from data in the form of
            # Vraw = V0 + b * WindSpeed ^ c
            # V0 is zero wind at a particular temperature
            # The constants b and c were determined by some Excel wrangling with the solver.
            # WindSpeed_MPH = math.pow(((RV_Wind_Volts - zeroWind_volts) /.2300) , 2.7265)
            Speed = ((RV_Wind_Volts - zeroWind_volts) /.2300)
            WindSpeed_MPH = Speed**1.7265
            print("TMP volts:", TMP_Therm_ADunits * 0.0048828125, end=" ")
            print("RV volts:", RV_Wind_Volts, end=" ")
            print("TempC*100:", TempCtimes100, end=" ")
            print("ZeroWind volts:", zeroWind_volts, end=" ")
            print("WindSpeed KM/H:", WindSpeed_MPH * 1.609344)
            lastMillis = time.ticks_ms()
setup()
loop()
