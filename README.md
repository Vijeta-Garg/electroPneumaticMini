# ElectroWEAR


Inspiration: 
I've been working on an electropneumatically powered mechanotherapy wearable for breast cancer survivors, including in my last iteration (link to that abstract is here: https://www.overleaf.com/read/rxshvgcpytvv#2f1c8a in which I created custom soft actuator structures for this application). However, the last electropneumatic system I made was powered by a 12 Volt battery + hard to integrate into a wearable. I wanted to make an electropneumatic system that can be easier to integrate into a mechanotherapy vest for breast cancer survivors.

What the project does:
The project uses 6 Volts (unlike the earlier iterations which used 12Volts) and smaller components to make the electropneumatic as compact as possible so that it can  be integrated into a garment.

How it works:
A 6V battery powers the circuit while an Arduino Uno relays commands of which component should be on/off according to the code on the Arduino IDE. TIP120 and 1N4007 are there to primarily maintain electrical flow. This circuit powers 2 air pumps/compressors and 2 solenoid valves (although it can be adjusted to power just one of each as was done in this wearable). Furthermore, the circuit is electropneumatic, and it contains a "pneumatic" component in the way the air pumps and solenoid valves are conntected to each other through plastic piping and finally connected to the actuator. This part of the circuit maintains pneumatic flow and allows solenoid valves and air pumps to act as both inlets and outlets (if more than one is used). 


An example of the before and after:

**Before**
<img width="1832" height="1304" alt="image" src="https://github.com/user-attachments/assets/e8f6089b-c8e3-42c0-9605-1c16a74d7f5a" />

**Now: ElectroWEAR**
<img width="982" height="1316" alt="image" src="https://github.com/user-attachments/assets/508ca864-12ce-4caa-93dc-d4b3f13c385f" />

# Schematic 
This is the wiring diagram/schematic. This includes both the electrical parts of the circuit (contained in the "main circuit board") and the pneumatic parts of the circuit (which are integrated across the wearable rather than in the gray pocket on the bottom-left)!
<img width="1968" height="1366" alt="image" src="https://github.com/user-attachments/assets/90bc1018-b635-41c0-b0ff-a7858eef6635" />


# Layout 

# PCB (and maybe CAD) 


# How to build this? 

<img width="974" height="1380" alt="image" src="https://github.com/user-attachments/assets/fae11431-6cc1-4bef-807f-88670916a616" />


# BOM (properly formatted in the bom.csv file in the repo) 
Please note: I don't need reimbursement for any of these materials since I can use research grant money I've gotten for this project! 
<img width="2708" height="498" alt="image" src="https://github.com/user-attachments/assets/2550d27e-26f0-40a2-9f4b-4c4d42f4d633" />

