# ElectroWEAR


Inspiration: 
I've been working on an electropneumatically powered mechanotherapy wearable for breast cancer survivors, including in my last iteration (link to that abstract is here: https://www.overleaf.com/read/rxshvgcpytvv#2f1c8a in which I created custom soft actuator structures for this application). However, the last electropneumatic system I made was powered by a 12 Volt battery + hard to integrate into a wearable. I wanted to make an electropneumatic system that can be easier to integrate into a mechanotherapy vest for breast cancer survivors.

What the project does:
The project uses 6 Volts (unlike the earlier iterations which used 12Volts) and smaller components to make the electropneumatic as compact as possible so that it can  be integrated into a garment.

How it works:
A 6V battery powers the circuit while an Arduino Uno relays commands of which component should be on/off according to the code on the Arduino IDE. TIP120 and 1N4007 are there to primarily regulate electrical flow. This circuit powers 2 air pumps/compressors and 2 solenoid valves (although it can be adjusted to power just one of each as was done in this wearable). Furthermore, the circuit is electropneumatic, and it contains a "pneumatic" component in the way the air pumps and solenoid valves are conntected to each other through plastic piping and finally connected to the actuator. This part of the circuit maintains pneumatic flow and allows solenoid valves and air pumps to act as both inlets and outlets (if more than one is used). 


An example of the before and after:

**Before**
<img width="1832" height="1304" alt="image" src="https://github.com/user-attachments/assets/e8f6089b-c8e3-42c0-9605-1c16a74d7f5a" />

**Now: ElectroWEAR**
<img width="982" height="1316" alt="image" src="https://github.com/user-attachments/assets/508ca864-12ce-4caa-93dc-d4b3f13c385f" />

# Schematic 
This is the wiring diagram/schematic. This includes both the electrical parts of the circuit (contained in the "main circuit board") and the pneumatic parts of the circuit (which are integrated across the wearable rather than in the gray pocket on the bottom-left)!
<img width="1776" height="1166" alt="image" src="https://github.com/user-attachments/assets/20c83b9a-02ff-4674-aa87-99106a88089b" />


# Layout 
This is how the circuit is mapped out onto the wearable. Currently the main "control board" is only breadboarded and not PCBed but the files are ready and I just need to order the PCB and substitute it in (that is why that box says breadboard/perfboard/PCB) 
Also note: if one was to wear ElectroWEAR the battery component would theoretically live in their pant pocket or a string bag. 
<img width="1444" height="1458" alt="image" src="https://github.com/user-attachments/assets/24f5f97b-4b9d-451f-9d9e-56101a5b2028" />


# PCB and CAD 
Here is a 3D version of my PCB! Note: The PCB isn't printed yet but it would essentially just replace the breadboard in the breadboard pocket as it has all the same parts. 
<img width="2144" height="1220" alt="image" src="https://github.com/user-attachments/assets/e483beb1-a2c3-4759-b6f4-262c7c3bb517" />

I also CADDed some connectors for the pneumatic circuit to connect the smaller pipes to the bigger ones (both are necessarybecause some the valve and air pump work better with some but the actuator works better with the smaller pipe) 
https://www.tinkercad.com/things/jGbuTJKzcDS/edit?returnTo=%2Fdashboard&sharecode=0BTtQNpM6YuViGaWplz6nGzc2ZjLgraPeQsmGDZI_-0

# How to build this? 
1. Wire up the main electrical component (refer to the schematic in pcb folder). Every solenoid valve or air pump added require the same subset of wiring: TIP120 connected to 1N4007 diode and also connected to the component and GND and Power rails.
2. Connect this circuit to the 6V battery holder. Put the 1.5V batteries inside this battery holder. Remember NOT to plug the 6V directly into the arduino! Plug into power rail to share with components! Either connect by soldering or alligator clips! 
3. Import firmware to arduino IDE and run the circuit
4. Build out the pneumatic section of the circuit by using the schematic as reference. The joint parts are all pneumatic connectors *which look like pipes. Test the circuit out with the pneumatic connections as well. Get pneumatic connectors (plastic tubes) to connect the pipes 
5. Cut out 4 different pockets (preferably of strong material like denim) on a shirt and place the circuit as detailed in the layout diagram. If you have a soft textile actuator (or any output you want the electropneumatic to puff up) place that in the top-left pocket) 
6. Sew the pockets closed and the build is done!
7. Print out the flex PCB design detailed in this repo. Then, unsew the controller pocket and connect that to the arduino + into the pocket instead of the earlier perfboarded/breadboarded version!

   
<img width="974" height="1380" alt="image" src="https://github.com/user-attachments/assets/fae11431-6cc1-4bef-807f-88670916a616" />


# BOM (properly formatted in the bom.csv file in the repo) 
Please note: I don't need reimbursement for any of these materials since I can use research grant money I've gotten for this project! 
<img width="2142" height="926" alt="image" src="https://github.com/user-attachments/assets/43aad4a5-d419-478b-93d5-e321bdc6a401" />

