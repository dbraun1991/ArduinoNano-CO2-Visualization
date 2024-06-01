import serial

try:
    ser = serial.Serial('/dev/tty.usbserial-10', 9600)  # Adjust to your serial port
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
except serial.SerialException as e:
    print(f"Error: {e}")

