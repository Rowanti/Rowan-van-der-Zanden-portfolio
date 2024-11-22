import sys, random, math, time, socketio, json
from controller import Supervisor, Robot
from collections import deque


# y x from server
destination = [0.4,0.5]

try:
    sio = socketio.Client()
    sio.connect('http://localhost:8000')
    connected = True
except:
    print("Failed to connect")
    connected = False
    
@sio.on('nextposrowan')
def on_message(data):
    # coord = data['x']['y']
    # print(f'Client received message: {data}')
    destination[0] = float(data['y'])
    destination[1] = float(data['x'])


@sio.on('noodstop')
def on_message(data):
    translation = box1.getField('translation').getSFVec3f()
    destination[0] = translation[0]
    destination[1] = translation[1]


  
supervisor = Supervisor()

mt = 10

box1 = supervisor.getSelf()
timestep = int(supervisor.getBasicTimeStep()*4)

ds1 = supervisor.getDevice("Sensor1")
ds2 = supervisor.getDevice("Sensor2")
ds3 = supervisor.getDevice("Sensor3")
ds4 = supervisor.getDevice("Sensor4")
leds = [supervisor.getDevice("Led1"),supervisor.getDevice("Led2"),supervisor.getDevice("Led3"),supervisor.getDevice("Led4")]

ds1.enable(10)
ds2.enable(10)
ds3.enable(10)
ds4.enable(10)

def bfs(matrix, start, goal):
    num_rows = len(matrix)
    num_cols = len(matrix[0])

    visited = set()
    queue = deque([(start, [])])

    while queue:
        current, path = queue.popleft()
        if current == goal:
            return path + [current]
        if current in visited:
            continue

        visited.add(current)
        row, col = current
        neighbors = get_valid_neighbors(matrix, row, col)
        for neighbor in neighbors:
            queue.append((neighbor, path + [current]))

    return None


def get_valid_neighbors(matrix, row, col):
    num_rows = len(matrix)
    num_cols = len(matrix[0])
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]  # Possible neighbor directions

    neighbors = []
    for dx, dy in directions:
        new_row, new_col = row + dx, col + dy
        if 0 <= new_row < num_rows and 0 <= new_col < num_cols and matrix[new_row][new_col] != 0:
            neighbors.append((new_row, new_col))

    return neighbors

# matrix = [
    # [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    # [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    # [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    # [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    # [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    # [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    # [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    # [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    # [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    # [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
# ]
matrix = [
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 0, 0, 0, 1, 1, 0, 0, 0, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 0, 0, 0, 1, 1, 1, 1, 0, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 0, 0, 0, 1, 1, 0, 0, 0, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 0, 0, 0, 1, 1, 0, 0, 0, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
]

def getDirection(old, new):
    if (new[0]-old[0]>0):
        ledControl(0)
    elif (new[0]-old[0]<0):
        ledControl(2)
    elif (new[1]-old[1]>0):
        ledControl(1)
    elif (new[1]-old[1]<0):
        ledControl(3)
  
def readSensors():
    return (ds1.getValue(),ds2.getValue(),ds3.getValue(),ds4.getValue())

def appendMatrix(translation, sensors):
    if sensors[0] < 1000:
        if(translation[0]*mt+1<=len(matrix[0])-1):
            matrix[int(translation[0]*mt+1)][int(translation[1]*mt)] = 0
    else:
        if(translation[0]*mt+1<=len(matrix[0])-1):
            matrix[int(translation[0]*mt+1)][int(translation[1]*mt)] = 1
    if sensors[1] < 1000:
        if(translation[1]*mt+1<=len(matrix[0])-1):
            matrix[int(translation[0]*mt)][int(translation[1]*mt+1)] = 0
    else:
        if(translation[1]*mt+1<=len(matrix[0])-1):
            matrix[int(translation[0]*mt)][int(translation[1]*mt+1)] = 1
    if sensors[2] < 1000:
        if(translation[0]*mt-1>=0):
            matrix[int(translation[0]*mt-1)][int(translation[1]*mt)] = 0
    else:
        if(translation[0]*mt-1>=0):
            matrix[int(translation[0]*mt-1)][int(translation[1]*mt)] = 1
    if sensors[3] < 1000:
        if(translation[1]*mt-1>=0):
            matrix[int(translation[0]*mt)][int(translation[1]*mt-1)] = 0    
    else:
        if(translation[1]*mt-1>=0):
            matrix[int(translation[0]*mt)][int(translation[1]*mt-1)] = 1

def ledControl(num):
    for i in range(len(leds)):
        leds[i].set(1) if num == i else leds[i].set(0)
def ledRead():
    for i in range(len(leds)):
        if (leds[i].get() == 1):
            return i
    return 4
while supervisor.step(timestep) != -1:
    sensorValues = readSensors()
    translation = box1.getField('translation').getSFVec3f()
    object = {'x': translation[1], 'y': translation[0], 'direction': ledRead()}
    # Send new position of the box to the nodejs server every movement with websockets
    if connected:
        sio.emit('rowan_position', json.dumps(object))
    appendMatrix(translation,sensorValues)
    path = bfs(matrix, (int(translation[0]*mt),int(translation[1]*mt)),(int(destination[0]*mt),int(destination[1]*mt)))
    if path:
        try:
            new_position = [path[1][0]/mt,path[1][1]/mt,0]
            getDirection(translation,new_position)
        except:
            ledControl(-1)
            # print("rowan is at destination")
        box1.getField('translation').setSFVec3f(new_position)
        translation = box1.getField('translation').getSFVec3f()
    # if(round(translation[0]*mt)/mt == destination[0] and round(translation[1]*mt)/mt == destination[1]):
        # ledControl(-1)
        # print("you made it")
    pass