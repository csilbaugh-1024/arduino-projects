import matplotlib.pyplot as plt

# 5 mF capacitor
capacitance = 5e-3

time_data = []
charge_data = []

with open("Collected_Capacitor_Voltage.txt", "r") as file:

    # Skip header
    file.readline()

    while True:
        line = file.readline()

        if line == "":
            break

        line = line.strip()

        if line:
            values = line.split(",")

            time = float(values[0]) / 1_000_000
            voltage = float(values[1])

            # Q = CV
            charge = capacitance * voltage

            time_data.append(time)
            charge_data.append(charge)

plt.plot(time_data, charge_data)

plt.title("Charge Stored on 5 mF Capacitor vs Time")
plt.xlabel("Time (seconds)")
plt.ylabel("Charge (Coulombs)")
plt.grid(True)

plt.show()