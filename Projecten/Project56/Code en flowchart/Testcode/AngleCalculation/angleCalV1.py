import math
# lat = y
# long = x

currentAngle = 120
def getAngle(long1, lat1, long2, lat2):
    if lat2-lat1==0:
        if long1>=long2:
            return -90
        else:
            return 90
    elif lat2-lat1>=0:
        if long2-long1>=0:
            return round(math.degrees(math.atan((long2-long1)/(lat2-lat1))))
        else:
            return round(-math.degrees(math.atan((abs(long2-long1))/(lat2-lat1))))
    else:
        if long2-long1>=0:
            return round(180-math.degrees(math.atan((long2-long1)/(abs(lat2-lat1)))))
        else:
            return round((180-math.degrees(math.atan((long2-long1)/(lat2-lat1))))*-1)
def sendToCar(angle):
    if angle-currentAngle > 0:
        return 1
    elif angle-currentAngle <0:
        return -1
    else:
        return 0


# print(getAngle(4.679730788228449, 51.885386406957075, 19.022418466905325, -58.71745847123175))
# print(getAngle(4.679730788228449, 51.885386406957075, 21.144424696987727, 52.8534947032697))
# print(getAngle(4.679730788228449, 51.885386406957075, 4.679730788228449, 52.885386406957075))
# print(getAngle(4.679730788228449, 51.885386406957075, 5.679730788228449, 51.885386406957075))

tempAngle = getAngle(4.4777417, 51.924419, 4.4777416, 51.924418)
while currentAngle!=tempAngle:
    currentAngle+=sendToCar(tempAngle)
    print('current angle: ', currentAngle)