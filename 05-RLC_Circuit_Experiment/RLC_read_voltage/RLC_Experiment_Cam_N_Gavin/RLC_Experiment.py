import serial
import time

# Replace COM3 with your Arduino's COM port
PORT = "COM6"
BAUD = 115200

ser = serial.Serial(PORT, BAUD)
time.sleep(2)  # Wait for Arduino to reset

with open("Collected_Capacitor_Voltage.txt", "w") as file:
    print("Collecting data... Press Ctrl+C to stop.")

    try:
        while True:
            line = ser.readline().decode("utf-8").strip()

            if line:
                print(line)
                file.write(line + "\n")

    except KeyboardInterrupt:
        print("Finished collecting data.")

ser.close()