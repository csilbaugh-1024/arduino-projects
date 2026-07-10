# RLC Circuit Group Experiment: Prediction and Validation

## Project Goal
The goal of this project is to use differential equations and electric circuit concepts to predict the behavior of an RLC circuit and compare the prediction to the observed behavior. Two group members, one specializing in differential equations (Cam) and the other specializing in circuit analysis (Gavin), will work together to find an equation that models the charge of the capacitor over time. After finding this theoretical equation, we will collect voltage data with an Arduino, which will be used in a Python program to build a graph displaying the capacitor's observed charge over time.

## RLC Circuit Background
A series RLC circuit combines a resistor, R, an inductor, L, and a capacitor, C. Based on the resistance (Ω), capacitance (C), and inductance (L) present, the circuit generally falls into one of four categories: undamped, underdamped, critically damped, and overdamped. Undamped circuits have positive L and C values, but no resistance. This causes infinite oscillation, meaning the circuit never reaches equilibrium. An underdamped circuit has positive values for L, R, and C, but the combination of these values still results in some oscillation, though the amplitude exponentially decays over time due to the resistor, and it eventually reaches equilibrium. A critically damped circuit contains positive values for L, R, and C, and there is no oscillation. Instead, critically damped behavior is characterized by exponential decay towards equilibrium driven by a single exponent. A critically damped circuit reaches equilibrium faster than any other kind of RLC circuit. Finally, an overdamped circuit has positive L, R, and C values and, similar to a critically damped circuit, there is no oscillation. Rather, there is exponential decay. Unlike critically damped circuits, however, exponential behavior is driven by two separate exponents rather than one. This causes an overdamped circuit to take more time to reach equilibrium than a critically damped one. Whether the circuit approaches equilibrium with exponential growth or decay is generally based on the charge on the capacitor, the current on the inductor, and the applied voltage.

## Circuit Description

### Physical Layout
This circuit was designed so that the capacitor can discharge in a closed RLC circuit. First, the switch is closed to charge the capacitor, and it is then opened for discharging. Consequently, the circuit is made up of two loops. The first and smaller loop was labelled loop A, and, going from the positive terminal of the power source to the negative, it includes a pushbutton to act as a switch, the inductor, a 100Ω resistor, and the negative terminal of the battery. The second loop, loop B, begins with the positive terminal of the power source, followed by the pushbutton, then the 10Ω resistor, then the 5000uF capacitor, the 100Ω resistor, then, finally, the negative terminal. Unfortunately, the inductor is not an ideal inductor as it has 27.6Ω of resistance.

![alt_text](Circuit.jpg)

### Functionality and Initial Conditions
The main goal of the circuit design was to find an equation for the charging and discharging behavior of the capacitor. To solve for the capacitor's charging equation, two initial conditions are required: the capacitor's initial voltage (or its initial charge) and the initial current passing through the inductor. While it was easy to find that the initial charge on the capacitor at time t=0 is zero, determining the initial current on the inductor requires more math and analysis of the circuit configuration. Fortunately, it can be found using circuit rules and physics.

One of the interesting characteristics of an RLC circuit is the interaction between inductors and capacitors when switches are used. As current flows through an inductor, it gradually increases until the circuit reaches DC steady state. At this point, the inductor behaves like a short circuit, meaning the voltage across it is approximately zero while current continues to flow through its winding resistance. In contrast, a capacitor accumulates charge over time, causing the voltage across it to increase until it reaches its maximum value in DC steady state. At that point, the capacitor behaves like an open circuit and no steady-state current flows through it.

The main equations that describe this behavior are:

* Inductor voltage-current relationship:
  $v(t)=L\frac{di(t)}{dt}$

* Capacitor current-voltage relationship:
  $i(t)=C\frac{dv(t)}{dt}$

* DC Steady State Capacitor Charge:
  $Q=CV$

### [Note to gavin: this is desciribing discharging, right? Please include. Could you explain the physics behind the entire loop of both charging and discharging phases like you did with discharging? This is very close to a "How Does it Work section" so this could get that out of the way for us]
To study the capacitor's discharging behavior, it must begin with the maximum potential stored charge, or voltage across its terminals. Since a fully energized inductor will be shorted in DC steady state, placing the capacitor in parallel with the inductor guarantees that the capacitor will stop charging when the inductor reaches this moment. The circuit was therefore designed so that the switch connects the inductor to the power supply in parallel and allows it to reach DC steady state. Since charge tends to flow along the path of least resistance, a short circuit completely cuts off current flow through the capacitor. Since the time constant of the inductor is equal to $\tau_L=\frac{L}{R}$ in an RL circuit, and $\tau_C=RC$ in an RC circuit, our chosen circuit strategically places the two loops as an RC and RL circuit. With the chosen values, the Inductor looks to charge more quickly to its DC steady state of >5 $\tau than the capacitor. This means that the Capacitor does not fully reach its maximum charge by the time the inductor acts as a short circuit. However, what's great about the capacitor is that it stores charge for later use, so it maintains a constant voltage. So, when the switch is opened, the overdamped RLC circuit allows for the discharging behavior to be measured.

### [Discharging?]
The second initial condition is the inductor current immediately before switching. Because the inductor behaves as a short circuit in DC steady state, the steady-state current can be found using Ohm's Law. The current is determined by the supply voltage divided by the total series resistance, which consists of the 100 $\Omega$ resistor and the inductor's 27.6 $\Omega$ DC winding resistance:
$I_L(0^-)=\frac{3.3\,\mathrm{V}}{100\,\Omega+27.6\,\Omega}\approx25.9\,\mathrm{mA}$

When the switch changes position, the power supply is disconnected and the inductor begins transferring its stored potential energy to the capacitor. Because the current through an inductor and the voltage across a capacitor cannot change instantaneously, the initial conditions immediately after switching are
$I_L(0^+)=I_L(0^-)$
and
$V_C(0^+)=V_C(0^-)$

### Note to gavin: I changed "charging behavior" to "discharging behavior". If that's correct, just delete this and disregard please
These conditions provide the known initial values needed to solve the differential equation describing the capacitor's discharging behavior.

## Circuit Diagram
*Designed within KiCad*

<img width="659" height="356" alt="Screenshot 2026-07-08 235401" src="https://github.com/user-attachments/assets/6d6affd7-02c5-4f6e-ae36-3e8197a5cdea" />

## Hardware and Safety
There were numerous hardware and safety concerns that appeared during this project, and the largest, most prominent problem was that of negative voltage. Undamped and underdamped RLC configurations can cause voltage to oscillate and dip below zero. Negative voltage must be avoided or, alternatively, approached with the proper protective measures such as diodes and voltage dividers because it can damage the polarized electrolytic capacitors in the circuit as well as the analog input pins of the microcontroller. So, while we planned this project, we chose a combination of R, L, and C that would ensure no oscillatory behavior, preventing the circuit from being undamped or underdamped.

Also, we chose to connect the circuit to the arduino with a 10k $\Omega$ resistor to safeguard against possible current spikes if anything unexpected were to happen, which could damage the analog in pin. 

Another concern that had to be considered was the sampling rate of the microcontroller. At its quickest, the arduino's analog in pins can only sample data at a rate of around one sample per hundred microseconds. So, this circuit was engineered so that its capacitor did not charge or discharge too quickly to be measured accurately.

## Testing Procedure and Results
During testing, the circuit was connected to the power source and the pushbutton was held down for three seconds before being released. Voltage and charge data was collected during the whole process, and the graphs are included below.

<img width="384" height="288" alt="ChargeOverCapacitor" src="https://github.com/user-attachments/assets/7203237c-90e5-450a-a9bd-162c13381faf" />
<img width="384" height="288" alt="Voltage_Across_Capacitor" src="https://github.com/user-attachments/assets/4634bdd8-0d01-4ea3-8873-8d499dc5136f" />

The graphs illustrate that the capacitor reached its peak charge of roughly 0.004 coulombs and peak voltage of roughly 0.8 volts after around 2.5 seconds of charging. Then, it took nearly one second to fully discharge after the switch was opened. Both curves, that of the charging phase and the discharging phase, appear to be exponential.

## Predicting Behavior with Differential Equations
The behavior of a series RLC circuit can be explained mathematically using a second order linear nonhomogeneous ordinary differential equation. The standard RLC equation is:

$LQ''+RQ'+\frac{1}{C}Q=E(t)$

where L represents inductance in henries, R represents resistance in ohms, C represents capacitance in farads, Q represents charge in coulombs, and E(t) represents applied voltage in volts as a function of time. Furthermore, the form of the general solution indicates whether the circuit is undaped, underdamped, critically damped, or overdamped. The possible homogeneous general solutions (general solutions without the particular solution from E(t) included) are listed below.

 + Undamped: $Q_h(t)=c_1\cos(\theta t)+c_2\sin(\theta t)$
 + Underdamped: $Q_h(t)=c_1e^{at}\cos(\theta t)+c_2e^{at}\sin(\theta t)$
 + Critically Damped: $Q_h(t)=c_1e^{at}+c_2te^{at}$
 + Overdamped: $Q_h(t)=c_1e^{at}+c_2e^{bt}$

Where a and b are negative.

Because this is a second order differential equation, the general solution will contain two unknown constants. To find these constants and identify a particular solution, there must be known initial conditions for charge, Q(t), and current, Q'(t).

### Charging Phase
During the charging phase, when the switch is closed, the circuit is not a true series RLC circuit. So, the standard RLC equation alone is not sufficient to find an expression for the charge on the capacitor. Instead, the charge on the capacitor must be found with a system of first-order linear ordinary differential equations because it is dependent on the current through the inductor parallel to it. This system is constructed with circuit loop analysis. Following the physical layout of the circuit, the smaller loop is called Loop A and includes the power source, the pushbutton, the inductor, and the $100,\Omega$ resistor. Also, the inductor has $27.6,\Omega$ of resistance which must be included in the equation. Loop A's equation looks like this:

$3.3 - L\frac{di_L(t)}{dt} - R_L i_L(t) - 100\left(i_L(t) + \frac{dQ(t)}{dt}\right) = 0$

This equation can then be solved for $\frac{di_L(t)}{dt}$, the derivative of the current through the inductor as a function of time.

$\frac{di_L(t)}{dt} = -12760 i_L(t) - 10000\frac{dQ(t)}{dt} + 330$

Next, Loop B consists of the power source, the pushbutton, the $10,\Omega$ resistor, the $5000,\mu\text{F}$ capacitor, and the $100,\Omega$ resistor. This is the equation for Loop B:

$3.3 - 10\frac{dQ(t)}{dt} - 200Q(t) - 100\left(i_L(t) + \frac{dQ(t)}{dt}\right) = 0$

This equation is then solved for the current through the capacitor, which is equivalent to the derivative of the charge on the capacitor, $\frac{dQ(t)}{dt}$.

$\frac{dQ(t)}{dt} = -\frac{100}{110}i_L(t) - \frac{200}{110}Q(t) + 0.03$

This equation can then be plugged into the equation for $\frac{di_L(t)}{dt}$ to make it an equation in terms of only $i_L(t)$ and $Q(t)$.

## Conclusions

## What Did I learn? (Cam)
