'''
TinLab - Machine Learning eindopdracht

Zoy Oudeness, Robert-Jan Schutte en Rowan van der Zanden
'''
import logging
from net import Net
import numpy as np
import torch
import platform
from pytocl.driver import Driver
from pytocl.car import State, Command

logging.basicConfig(level=logging.INFO)

# Load the model
MODEL_PATH = 'model/model24.pth'
params = 22
model = Net(params)

# Set device to GPU if available on the system, else CPU
os_name = platform.system()
if os_name == "Windows" or os_name == "Linux":
    model.load_state_dict(torch.load(MODEL_PATH, map_location=torch.device("cuda:0" if torch.cuda.is_available() else "cpu")))
elif os_name == "Darwin":
    model.load_state_dict(torch.load(MODEL_PATH, map_location=torch.device('mps')))
model.eval()

'''
This overrides the standard drive method of the Driver class.
It uses the model to make a prediction based on the input data.
The prediction is then used to set the steering, accelerator, brake and gear.
'''
class MyDriver(Driver):
    def drive(self, carstate: State) -> Command:
        global model
        command = Command()

        # Prepare the input data
        track_data = np.ndarray((params,), dtype=np.float32)
        track_data[0] = carstate.angle
        track_data[1] = carstate.speed_x
        track_data[2:21] = carstate.distances_from_edge
        track_data[21] = carstate.distance_from_center

        # Convert to PyTorch tensor and make a prediction
        test_tensor = torch.tensor(track_data, dtype=torch.float32).unsqueeze(0)
        with torch.no_grad():
            prediction = model(test_tensor).numpy().flatten()
        
        # Set the commands based on the prediction
        # Steering and braking are multiplied by 1.5 and 2.5 to increase driving behavior
        command.steering = prediction[0]*1.5
        command.accelerator = prediction[1]
        command.brake = prediction[2]*2.5
        
        # Gear changing
        if carstate.rpm > 8000:
            command.gear = carstate.gear + 1
        elif carstate.rpm < 2500 and carstate.gear > 1:
            command.gear = carstate.gear - 1
        if not command.gear:
            command.gear = carstate.gear or 1

        # Prevent the car from driving too slow
        if carstate.speed_x < 10:
            command.accelerator = 0.9
            command.brake = 0

        # Prevent the car from reversing too much
        if carstate.gear < 0:
            command.gear = 1

        # Unstuck the car when stuck in the barriers
        if carstate.angle > 30 and carstate.distance_from_center < -.9:
            command.steering = -1
            command.accelerator = 1
            command.brake = 0
            command.gear = -1
        if carstate.angle < -30 and carstate.distance_from_center > .9:
            command.steering = 1
            command.accelerator = 1
            command.brake = 0
            command.gear = -1
                
        logging.info(prediction)
        return command

