''' '
TinLab - Machine Learning eindopdracht

Zoy Oudeness, Robert-Jan Schutte en Rowan van der Zanden
'''

from pytocl.driver import Driver
from pytocl.car import State, Command
from pynput import keyboard
import csv
import os
import pygame

# Initialize Pygame
pygame.init()
pygame.joystick.init()

# Initialize joystick
joystick = None
if pygame.joystick.get_count() > 0:
    joystick = pygame.joystick.Joystick(0)
    joystick.init()

# Variables to store keyboard input state
keyboard_state = {
    'accelerator': 0,
    'brake': 0,
    'left': 0,
    'right': 0
}

def on_press(key):
    try:
        if key == keyboard.Key.up:
            keyboard_state['accelerator'] = 1
        elif key == keyboard.Key.down:
            keyboard_state['brake'] = 1
        elif key == keyboard.Key.left:
            keyboard_state['right'] = 1
        elif key == keyboard.Key.right:
            keyboard_state['left'] = 1
    except AttributeError:
        pass

def on_release(key):
    try:
        if key == keyboard.Key.up:
            keyboard_state['accelerator'] = 0
        elif key == keyboard.Key.down:
            keyboard_state['brake'] = 0
        elif key == keyboard.Key.left:
            keyboard_state['right'] = 0
        elif key == keyboard.Key.right:
            keyboard_state['left'] = 0
    except AttributeError:
        pass

listener = keyboard.Listener(on_press=on_press, on_release=on_release)
listener.start()

# Ensure the log directory exists
os.makedirs('./logs', exist_ok=True)

# Open the log file in append mode
log_file = open('./logs/driving_data_eTrack2.csv', mode='a', newline='')
log_writer = csv.writer(log_file, dialect='excel')

# Create the header dynamically
header = [
    'Angle', 'Distance_raced','DistanceFromStart' , 'CurrentLapTime'
] + [f'Opponent_{i}' for i in range(36)] + [
    'RPM', 'SpeedX', 'SpeedY', 'SpeedZ'
] + [f'Track_{i}' for i in range(19)] + [
    'TrackPosition'
] + [f'WheelSpinVelocity_{i}' for i in range(4)] + [
    'Z', 'Acceleration', 'Braking', 'Steering'
]

log_writer.writerow(header)

class MyDriver(Driver):
    # Override the `drive` method to create your own driver
    def drive(self, carstate: State) -> Command:
        command = Command()
        
        # Update joystick state
        pygame.event.pump()
        if joystick:
            joystick_accelerator = joystick.get_axis(5)  # Assuming the right trigger
            joystick_brake = joystick.get_axis(4)  # Assuming the left trigger
            joystick_steering = joystick.get_axis(0)*-1  # Assuming the left stick horizontal
            if joystick_steering < 0.2 and joystick_steering > -0.2:
                joystick_steering = 0
            elif joystick_steering > 0.2:
                joystick_steering = (joystick_steering - 0.2) / 1.3
            else:
                joystick_steering = (joystick_steering + 0.2) / 1.3
            # Normalize joystick inputs to [0, 1]
            command.accelerator = max(0, (joystick_accelerator + 1) / 2)
            command.brake = max(0, (joystick_brake + 1) / 2)
            command.steering = joystick_steering
        else:
            command.accelerator = keyboard_state['accelerator']
            command.brake = keyboard_state['brake']
            command.steering = keyboard_state['right'] - keyboard_state['left']
        
        if carstate.rpm > 8000:
            command.gear = carstate.gear + 1
        elif carstate.rpm < 2500 and carstate.gear > 1:
            command.gear = carstate.gear - 1
        if not command.gear:
            command.gear = carstate.gear or 1

        # Log the car state and command
        log_writer.writerow([
            carstate.angle,
            carstate.distance_raced,
            carstate.distance_from_start,
            carstate.current_lap_time,
            *carstate.opponents,
            carstate.rpm,
            carstate.speed_x,
            carstate.speed_y,
            carstate.speed_z,
            *carstate.distances_from_edge,
            carstate.distance_from_center,
            *carstate.wheel_velocities,
            carstate.z,
            command.accelerator,
            command.brake,
            command.steering
        ])

        return command
