# ArduinoNano-CO2-Visualization
ArduinoNano real-time CO2 monitoring from MH-Z19B to Browser



# Arduino Nano CO2 Visualization

ArduinoNano real-time CO2 monitoring from MH-Z19B to Browser


## Description
This project demonstrates a real-time CO2 monitoring system using ..
- an Arduino Nano
- a Python Flask web server

The Arduino Nano reads CO2 levels from a MH-Z19B sensor and sends the data to a connected computer via a serial port.
A Python Flask application reads this data, processes it, and serves it to a web page using Flask-SocketIO and Chart.js for real-time visualization.
Users can view live updates of CO2 levels directly in their web browser.

## Tooling

Hardware:
- Notebook
- USB-connector to your Arduino Nano
- Arduino Nano
- 4 Jumper cables (Female to female)
- MH-Z19B CO2-sensor

Software Tools:
- Tools
  - Arduino IDE
  - Visual Studio Code

- Languages / Scripts
  - Python3
  - HTML
  - JavaScript

## Hardware setup

On the Arduino Nano the PINs are used to be connected to the CO2-sensor as follows:

| Arduino Nano | MH-Z19B |
|---|---|
| D3 | Tx |
| D2  | Rx |
| GND  | GND |
| 5V  | VIN |

Be aware that TX and Rx are swapped
(Python-Code vs. Hardware-Connectors)



## Installation

After connecting the hardware,
push the `co2Sense.ino` onto your Arduino Nano
using the Arduino IDE.

### Arduino IDE
You will have to install the following libraries via `Library Editor`:
- **MH-Z19** by Jonathan Dempsey
- **ArduinoJson** by Benoit Blanchon

You can check the Arduino Nano working properly by opening the `serial monitor`.
Sample output:

```
{'millis': 1564189, 'ABCEnabled': True, 'Range': 5000, 'BackgroundCO2': 557, 'Temperature': 17, 'CO2': 550}
{'millis': 1566189, 'ABCEnabled': True, 'Range': 5000, 'BackgroundCO2': 553, 'Temperature': 17, 'CO2': 553}
{'millis': 1570189, 'ABCEnabled': True, 'Range': 5000, 'BackgroundCO2': 551, 'Temperature': 17, 'CO2': 557}
```

Close the Arduino IDE `serial monitor` to release the serial port.



### Check the serial port

`You may have to install packages via python pip!`

Check the used serial port:
```
ls /dev/tty.*
```

Choose the right port as input for your python script.
Start with `checkPort.py` to find your desired 'not in use' serial port.


### Adjust main.py

Use the gained knowledge to fill in the serial port in `main.py`

```
    ser = serial.Serial('/dev/tty.usbserial-10', 9600)  # Adjust to your serial port
```

Now the `main.py` is supposed to consume the data from the serial port.


## View in browser

The data are now displayed on the given website.



## Sample output

![sampleScreen.png](pictures%2FsampleScreen.png)
