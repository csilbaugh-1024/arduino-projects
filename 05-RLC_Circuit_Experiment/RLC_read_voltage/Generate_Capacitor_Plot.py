import matplotlib.pyplot as plt

time = []
voltage = []

with open("Collected_Capacitor_Voltage.txt", "r") as file:

    # Skip the header
    file.readline()

    while True:
        line = file.readline()

        if line == "":
            break

        values = line.strip().split(",")

        time.append(float(values[0]) / 1_000_000)   # seconds
        voltage.append(float(values[1]))

plt.plot(time, voltage)

plt.title("Voltage Across Capacitor")
plt.xlabel("Time (s)")
plt.ylabel("Voltage (V)")
plt.grid(True)

plt.show()