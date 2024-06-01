import serial
import threading
from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import json

app = Flask(__name__)
socketio = SocketIO(app)

@app.route('/')
def index():
    return render_template('index.html')

def read_serial():
    ser = serial.Serial('/dev/tty.usbserial-10', 9600)  # Adjust to your serial port
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            try:
                data = json.loads(line)
                co2_value = data.get('CO2', None)
                if co2_value is not None:
                    print(f"Emitting values: {data}")  # Debug print
                    socketio.emit('update', {'values': data}, to=None)
                else:
                    print(f"CO2 key not found in the data: {line}")  # Debug print
            except json.JSONDecodeError:
                print(f"JSONDecodeError: Could not parse {line}")  # Debug print
            except ValueError:
                print(f"ValueError: Could not convert CO2 value from {line}")  # Debug print

if __name__ == '__main__':
    threading.Thread(target=read_serial).start()
    socketio.run(app)
