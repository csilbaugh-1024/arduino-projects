# RLC Circuit Group Experiment: Prediction and Validation

## Project Goal
The goal of this project is to use differential equations and electric circuit concepts to predict the behavior of an RLC circuit and compare the prediction to the observed behavior. Two group members, one specializing in differential equations (Cam) and the other specializing in circuit analysis (Gavin), will work together to find an equation that models the charge of the capacitor over time. After finding this theoretical equation, we will collect voltage data with an Arduino, which will be used in a Python program to build a graph displaying the capacitor's observed charge over time.

## RLC Circuit Background
A series RLC circuit combines a resistor, R, an inductor, L, and a capacitor, C. Based on the resistance (Ω), capacitance (C), and inductance (L) present, the circuit generally falls into one of four categories: undamped, underdamped, critically damped, and overdamped. Undamped circuits have positive L and C values, but no resistance. This causes infinite oscillation, meaning the circuit never reaches equilibrium. An underdamped circuit has positive values for L, R, and C, but the combination of these values still results in some oscillation, though the amplitude exponentially decays over time due to the resistor, and it eventually reaches equilibrium. A critically damped circuit contains positive values for L, R, and C, and there is no oscillation. Instead, critically damped behavior is characterized by exponential decay towards equilibrium driven by a single exponent. A critically damped circuit reaches equilibrium faster than any other kind of RLC circuit. Finally, an overdamped circuit has positive L, R, and C values and, similar to a critically damped circuit, there is no oscillation. Rather, there is exponential decay. Unlike critically damped circuits, however, exponential behavior is driven by two separate exponents rather than one. This causes an overdamped circuit to take more time to reach equilibrium than a critically damped one. Whether the circuit approaches equilibrium with exponential growth or decay is generally based on the charge on the capacitor, the current on the inductor, and the applied voltage.

## Circuit Description

### Physical Layout
This circuit was designed so that the capacitor can discharge in a closed RLC circuit. First, the switch is closed to charge the capacitor, and it is then opened for discharging. Consequently, the circuit is made up of two loops. The first and smaller loop was labelled loop A, and, going from the positive terminal of the power source to the negative, it includes a pushbutton to act as a switch, the inductor, a 100Ω resistor, and the negative terminal of the battery. The second loop, loop B, begins with the positive terminal of the power source, followed by the pushbutton, then the 10Ω resistor, then the 5000uF capacitor, the 100Ω resistor, then, finally, the negative terminal. Unfortunately, the inductor is not an ideal inductor as it has 27.6Ω of resistance.

![alt_text](Circuit.jpg)

*This diagram has the ground wire of the Arduino UNO microcontroller connected to the ground of the power supply. This was NOT how we measured the voltage over the capacitor. This picture just had this slight mistake. Since the ground is a reference for voltage differences, having it placed right after the capacitor is needed to measure the voltage drop/gain from the capacitor.*

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

### Discharging:
To study the capacitor's discharging behavior, it must begin with the maximum stored charge, or voltage across its terminals. Since a fully energized inductor will be ideally shorted in DC steady state except for some realistic resistance within the winding copper wire, placing the capacitor in parallel with the inductor guarantees that the capacitor will stop charging when the inductor reaches this moment. The circuit was therefore designed for both energy sources to be connected by a common node for both of them to reach their DC steady state. When these components are connected in parallel, we have found that they generally approach their DC steady state at around the same time of >5 $\tau$. However, what's great about the capacitor is that it stores charge for later use when disconnected, as the dielectric acts as an insulator, so it maintains a constant voltage. Once the inductor is shorted, a voltage divider equation can be used to find the voltage of the fully charged capacitor using the 100$\Omega$ resistor and the resistance of the winding copper wire. 

$$
V_{27.6}=3.3\cdot\frac{27.6}{100+27.6}=3.3\cdot\frac{27.6}{127.6}
$$

$$
V_{27.6}=3.3\times0.2165\approx0.7138\ \text{V}\approx0.714\ \text{V}
$$

If $C=5\ \text{mF}$, the corresponding charge is:

$$
Q=C\,V_{27.6}=5\times10^{-3}\cdot0.7138\approx3.57\times10^{-3}\ \text{C}=3.57\ \text{mC}
$$

The second initial condition is the inductor current immediately before switching. Because the inductor behaves as a short circuit ideally in DC steady state, the steady-state current can be found using Ohm's Law. The current is determined by the supply voltage divided by the total series resistance, which consists of the 100 $\Omega$ resistor and the inductor's 27.6 $\Omega$ DC winding resistance:
$I_L(0^-)=\frac{3.3\,\mathrm{V}}{100\,\Omega+27.6\,\Omega}\approx25.9\,\mathrm{mA}$

When the switch changes position, the power supply is disconnected and the discharging behavior begins as the RLC circuit is overdamped. Because the current through an inductor and the voltage across a capacitor cannot change instantaneously, the initial conditions immediately after switching are
$I_L(0^+)=I_L(0^-)$
and
$V_C(0^+)=V_C(0^-)$.
These conditions provide the known initial values needed to solve the differential equation describing the capacitor's discharging behavior.

### Charging:
From the instant that the switch was closed, the capacitor and the inductor began to charge. For the second-order differential equation of a charging capacitor within an overdamped circuit, the initial charge of the capacitor and current through the inductor are still needed. As mentioned before that $I_L(0^+)=I_L(0^-)$
and
$V_C(0^+)=V_C(0^-)$, the initial current of the inductor right before and right after the switch is closed must be equal to 0 mA. Also, as we learned earlier, capacitors have a dielectric that acts as an insulator, allowing them to hold charge. This supports the idea that the voltage right before is equal to the voltage right after the switch is closed. Assuming the capacitor is fully discharged to nearly 0 V, there will be an initial charge on the capacitor of nearly 0 C as well. 

## Circuit Diagram
*Designed within KiCad*

<img width="659" height="356" alt="Screenshot 2026-07-08 235401" src="https://github.com/user-attachments/assets/6d6affd7-02c5-4f6e-ae36-3e8197a5cdea" />

## Hardware and Safety
There were numerous hardware and safety concerns that appeared during this project, and the largest, most prominent problem was that of negative voltage. Undamped and underdamped RLC configurations can cause voltage to oscillate and dip below zero. Negative voltage must be avoided or, alternatively, approached with the proper protective measures such as diodes and voltage dividers because it can damage the polarized electrolytic capacitors in the circuit as well as the analog input pins of the microcontroller. So, while we planned this project, we chose a combination of R, L, and C that would ensure no oscillatory behavior, preventing the circuit from being undamped or underdamped.

Also, we chose to connect the circuit to the arduino with a 10k $\Omega$ resistor to safeguard against possible current spikes if anything unexpected were to happen, which could damage the analog in pin. 

Another concern that had to be considered was the sampling rate of the microcontroller. At its quickest, the arduino's analog in pins can only sample data at a rate of around one sample per hundred microseconds. So, this circuit was engineered so that its capacitor did not charge or discharge too quickly to be measured accurately.

## Predicting Behavior with Differential Equations
The behavior of a series RLC circuit can be explained mathematically using a second order linear nonhomogeneous ordinary differential equation. The standard RLC equation is:

$LQ''+RQ'+\frac{1}{C}Q=E(t)$

where L represents inductance in henries, R represents resistance in ohms, C represents capacitance in farads, Q represents charge in coulombs, and E(t) represents applied voltage in volts as a function of time. Furthermore, the form of the general solution indicates whether the circuit is undamped, underdamped, critically damped, or overdamped. The possible homogeneous general solutions (general solutions without the particular solution from E(t) included) are listed below.

 + Undamped: $Q_h(t)=c_1\cos(\theta t)+c_2\sin(\theta t)$
 + Underdamped: $Q_h(t)=c_1e^{at}\cos(\theta t)+c_2e^{at}\sin(\theta t)$
 + Critically Damped: $Q_h(t)=c_1e^{at}+c_2te^{at}$
 + Overdamped: $Q_h(t)=c_1e^{at}+c_2e^{bt}$

Where a and b are negative.

Because this is a second order differential equation, the general solution will contain two unknown constants. To find these constants and identify a particular solution, there must be known initial conditions for charge, Q(t), and current, Q'(t).

### Charging Phase
During the charging phase, when the switch is closed, the circuit is not a true series RLC circuit. So, the standard RLC equation alone is not sufficient to find an expression for the charge on the capacitor. Instead, the charge on the capacitor must be found with a system of first-order linear ordinary differential equations because its derivative is dependent on the current through the inductor parallel to it. This system is constructed with circuit loop analysis. Following the physical layout of the circuit, the smaller loop is called Loop A and includes the power source, the pushbutton, the inductor, and the $100\,\Omega$ resistor. Also, the inductor has $27.6\,\Omega$ of resistance which must be included in the equation. Loop A's equation looks like this:

$3.3 - L\frac{di_L(t)}{dt} - R_L i_L(t) - 100\left(i_L(t) + \frac{dQ(t)}{dt}\right) = 0$

This equation can then be solved for $\frac{di_L(t)}{dt}$, the derivative of the current through the inductor as a function of time.

$\frac{di_L(t)}{dt} = -12760 i_L(t) - 10000\frac{dQ(t)}{dt} + 330$

Next, Loop B consists of the power source, the pushbutton, the $10\,\Omega$ resistor, the $5000\,\mu\text{F}$ capacitor, and the $100\,\Omega$ resistor. This is the equation for Loop B:

$3.3 - 10\frac{dQ(t)}{dt} - 200Q(t) - 100\left(i_L(t) + \frac{dQ(t)}{dt}\right) = 0$

This equation is then solved for the current through the capacitor, which is equivalent to the derivative of the charge on the capacitor, $\frac{dQ(t)}{dt}$.

$\frac{dQ(t)}{dt} = -\frac{100}{110}i_L(t) - \frac{200}{110}Q(t) + 0.03$

This equation can then be plugged into the equation for $\frac{di_L(t)}{dt}$ to make it an equation in terms of only $i_L(t)$ and $Q(t)$. With $\frac{dQ(t)}{dt}$ plugged in, the equation looks like this:

$\frac{di_L(t)}{dt} = -3669 i_L(t) + 18182Q(t) +30$

These two first order linear ordinary differential equations each have the same two dependent variables, so they form a system. Though the exact tactics for solving this system for Q(t) are beyond the scope of this report, its general form is:

$Q(t) = 19.4c_1\mathrm{e}^{-6.5t} + c_2\mathrm{e}^{-3664.5t} + 0.00355$

This equation represents an overdamped circuit. However, out of the two initial conditions, only one represents charge, but this equation has two unknown constants. Fortunately, the equation for current on the inductor has the same unknown constants, so they can be found using a system of the two equations. The general solution for current on the inductor as a function of time is:

$i_L(t) = 100c_1\mathrm{e}^{-6.5t} + 4040c_2\mathrm{e}^{-3664.5t} + 0.0264$

With the initial conditions, $Q(0)=0$ and $i_L(0)=0$ applied and the resulting system solved for $c_1$ and $c_2$, the equation for charge on the capacitor during charging looks like this:

$Q(t) = -0.00355\mathrm{e}^{-6.5t} + 0.00355$

Surprisingly, the general form for this equation matches that of an overdamped circuit, but the particular form now matches none of the four possible cases. This is initially surprising, but it makes sense after considering the exponential terms in the general form. One term has e raised to the power of -6.5 multiplied by t, while the other exponential term uses -3664.5 instead. So, the second term exponentially decays insanely faster than the first one, and this happens so quickly that its influence is negligible in the solved form of the equation. And, $c_2$ becomes negligible, incredibly close to zero. So, the equation behaves as an RC circuit despite the inductor's being parallel to the capacitor. From a circuits perspective, the inductor has a negligible effect on the form of the capacitor's charging equation. Though unexpected, this equation makes perfect sense.

### Discharging phase
Unlike the charging phase where the capacitor charges in parallel to the inductor, the discharging phase features a full series RLC circuit because the switch is open. It can be modeled with the standard RLC equation:

$0.01Q''+37.6Q'+200Q=0$

The general form of the equation solved for Q(t) is:

$Q(t) = c_1\mathrm{e}^{-5.5t} + c_2\mathrm{e}^{-3754.5t}$

The two curves for charging and discharging form a continuous curve, and the discharging process begins at the known time t=3 when the switch is opened. So, since charge and current cannot instantaneously change, we can use $Q(3)$ and $Q'(3)$ as initial conditions for discharging. Those conditions are:

$Q(3)=0.00355$, $Q'(3)=0$

The solved form of the capacitor's discharging is:

$Q(t) = 0.00355\mathrm{e}^{-5.5t}$

In this equation, time t represents the time elapsed since discharging began, not the time elapsed since charging began. Again, the influence of the inductor is negligible on the form of this equation, so it resembles that of an RC circuit. Interestingly, though, the number in the exponent has changed from -6.5 to -5.5. This is likely due to the inductor's influence and the fact that the current now flows in a single loop rather than two loops in the charging phase.

## Testing Procedure and Results
During testing, the circuit was connected to the power source and the pushbutton was held down for three seconds before being released. Voltage and charge data was collected during the whole process, and the graphs are included below.

<img width="384" height="288" alt="ChargeOverCapacitor" src="https://github.com/user-attachments/assets/7203237c-90e5-450a-a9bd-162c13381faf" />
<img width="384" height="288" alt="Voltage_Across_Capacitor" src="https://github.com/user-attachments/assets/4634bdd8-0d01-4ea3-8873-8d499dc5136f" />

The graphs illustrate that the capacitor reached its peak charge of roughly 0.004 coulombs and peak voltage of roughly 0.8 volts after around 1 second of charging. Then, it took nearly one second to fully discharge after the switch was opened. Both curves, that of the charging phase and the discharging phase, appear to be exponential.

## Conclusions
After testing and data collection finished, the experimental graphs for charging and discharging agreed quite well with the predictive equations. However, the match was not perfect. Although both the expected and observed curves behaved exponentially, the former predicted a maximum charge of 3.55 mC, while the latter reached roughly 4.0 mC at its maximum. These discrepancies could have been caused by the resistors' tolerance, the 10k resistor connected to the Arduino UNO that increases the read voltage, stray capacitance within the breadboard, breadboard and component quality, or even leakage or resistance within the capacitors. This experiment was not conducted in an ideal lab environment, so it is reasonable to expect error. Overall, however, this was a very successful experiment because we successfully predicted the capacitor's behavior quite accurately.

## What Did I learn? (Cam)
The process of selecting and ordering components for the circuit, designing it, and physically assembling it immensely expanded my understanding of how inductors and capacitors behave and interact with each other in an RLC circuit. Also, it gave me valuable experience with real-world physical circuitry and the design process, things that are essential to electrical engineering. Furthermore, because differential equations and circuits like the one in this project are so closely intertwined, my prior knowledge in differential equations helped me navigate these new circuit topics more effectively, and these circuit concepts allowed me to use initial conditions for the prediction equations that could not have been found with differential equations alone. It was also very satisfying to solve a real-world problem with the techniques I had acquired in differential equations, and this was a clear demonstration that these skills would be essential for my engineering skillset. Further, it was useful to navigate this project while considering the constraints: oscillation coming from an underdamped circuit had to be avoided because negative voltage could damage the arduino analog input pin and the polarized electrolytic capacitors, and the circuit had to be built with large enough time constants for the arduino to measure its behavior accurately. In fact, designing the experimental procedure involved intricately balancing many constraints and factors such as the supplied voltage, the layout of the circuit to allow for effective charging and discharging, and the timing of the pushbutton. This process of reaching a desired goal while navigating constraints mirrors the process that a professional engineer would navigate. I also learned how to properly sample voltage data with a microcontroller and compare my theoretical equations predicting the charging and discharging of the capacitor with the experimental graph of the charge of the capacitor over time. In doing this, I learned about possible sources of error such as component quality or stray capacitance that could explain why my mathematical predictions did not exactly match the observed behavior of the circuit. This idea specifically was a useful reminder that, while mathematical predictions such as these are very useful, they are only approximations of real-world behavior that do not account for sources of error and imperfections such as these. In fact, it is quite common that predicted behavior does not fully match experimental behavior. Overall, this project was very helpful for teaching me about circuit concepts such as how inductors and capacitors behave in a DC RLC circuit, it was a useful review of the concepts I had learned in differential equations, and it allowed me to bridge the gap between the theoretical differential equations I learned in class and the behavior of circuits in the real world as I followed the engineering design process. Indeed, this project demonstrated that neither circuits nor differential equations could fully achieve the project goal alone, and these two topics had to be instead combined to reach the end goal of predicting and observing the charging and discharging behavior of a capacitor in an RLC circuit.
