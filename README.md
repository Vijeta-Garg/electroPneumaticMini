# ElectroWEAR


Inspiration: 
I've been working on an electropneumatically powered mechanotherapy wearable for breast cancer survivors, including in my last iteration (link to that abstract is here: https://www.overleaf.com/read/rxshvgcpytvv#2f1c8a) in which I created custom soft actuator structures for this application. However, the last electropneumatic system I made was powered by a 12 Volt battery + hard to integrate into a wearable. I wanted to make an electropneumatic system that can be easier to integrate into a mechanotherapy vest for breast cancer survivors.

What the project does:
The project uses 6 Volts (not 12Volts) and smaller components to make the electropneumatic as compact as possible so that it can  be integrated into a garment.

How it works:
A 6V battery powers the circuit while an Arduino Uno relays commands of which component should be on/off according to the code on the Arduino IDE. TIP120 and 1N4007 are there to primarily maintain electrical flow. This circuit powers 2 air pumps/compressors and 2 solenoid valves (although it can be adjusted to power just one of each as was done in this wearable). Furthermore, the circuit is electropneumatic, and it contains a "pneumatic" component in the way the air pumps and solenoid valves are conntected to each other through plastic piping and finally connected to the actuator. This part of the circuit maintains pneumatic flow and allows solenoid valves and air pumps to act as both inlets and outlets (if more than one is used). 
