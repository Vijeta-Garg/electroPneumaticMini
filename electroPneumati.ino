
const int inletPin = 8; //press 2 
const int pumpPin = 4; //press 1!!!


// const int pumpPin = 7;
// const int pump2Pin = 9;
// const int inletPin = 8;
// const int exhaustPin = 4;
void setup() {
  pinMode(pumpPin, OUTPUT);
  pinMode(pump2Pin, OUTPUT);
  pinMode(inletPin, OUTPUT);
  pinMode(exhaustPin, OUTPUT);

  digitalWrite(pumpPin, LOW);
  digitalWrite(pump2Pin, LOW);
  digitalWrite(inletPin, LOW);
  digitalWrite(exhaustPin, LOW);

  Serial.begin(9600);
  Serial.println("Debug Mode - 2 Pumps + 2 Valves");
  Serial.println("  p = toggle pump 1");
  Serial.println("  o = toggle pump 2");
  Serial.println("  1 = toggle inlet valve");
  Serial.println("  2 = toggle exhaust valve");
  Serial.println("  i = INFLATE");
  Serial.println("  d = DEFLATE");
  Serial.println("  h = HOLD");
  Serial.println("  x = ALL OFF");
  Serial.println("  ? = status");
}

bool pump1On = false;
bool pump2On = false;
bool inletOn = false;
bool exhaustOn = false;

void printStatus() {
  Serial.print("Pump 1: "); Serial.print(pump1On ? "ON" : "OFF");
  Serial.print(" | Pump 2: "); Serial.print(pump2On ? "ON": "OFF");
  Serial.print(" | Inlet valve: "); Serial.print(inletOn ? "OPEN" : "CLOSED");
  Serial.print(" | Exhaust valve: "); Serial.println(exhaustOn ? "OPEN" : "CLOSED");
}


void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();

    if (cmd == 'p') {
      pump1On = !pump1On;
      digitalWrite(pumpPin, pump1On ? HIGH : LOW);
      Serial.print("Pump 1: ");
      Serial.println(pump1On ? "ON" : "OFF");
    }

    if (cmd == 'o') {
      pump2On = !pump2On;
      digitalWrite(pump2Pin, pump2On ? HIGH : LOW);
      Serial.print("Pump 2: ");
      Serial.println(pump2On ? "ON" : "OFF");
    }

    if (cmd == '1') {
      inletOn = !inletOn;
      digitalWrite(inletPin, inletOn ? HIGH : LOW);
      Serial.print("Inlet valve: ");
      Serial.println(inletOn ? "OPEN" : "CLOSED");
    }

    if (cmd == '2') {
      exhaustOn = !exhaustOn;
      digitalWrite(exhaustPin, exhaustOn ? HIGH : LOW);
      Serial.print("Exhaust valve: ");
      Serial.println(exhaustOn ? "OPEN" : "CLOSED");
    }

    if (cmd == 'i') {
      pump1On = true;
      pump2On = true;
      inletOn = true;
      exhaustOn = false;
      digitalWrite(exhaustPin, LOW);
      digitalWrite(inletPin, HIGH);
      digitalWrite(pumpPin, HIGH);
      digitalWrite(pump2Pin, HIGH);
      Serial.println("INFLATING");
    }

    if (cmd == 'd') {
      pump1On = true;
      pump2On = true;
      inletOn = false;
      exhaustOn = true;
      digitalWrite(inletPin, LOW);
      digitalWrite(exhaustPin, HIGH);
      digitalWrite(pumpPin, HIGH);
      digitalWrite(pump2Pin, HIGH);
      Serial.println("DEFLATING");
    }

    if (cmd == 'h') {
      pump1On = false;
      pump2On = false;
      inletOn = false;
      exhaustOn = false;
      digitalWrite(pumpPin, LOW);
      digitalWrite(pump2Pin, LOW);
      digitalWrite(inletPin, LOW);
      digitalWrite(exhaustPin, LOW);
      Serial.println("HOLDING");
    }

    if (cmd == 'x') {
      pump1On = false;
      pump2On = false;
      inletOn = false;
      exhaustOn = false;
      digitalWrite(pumpPin, LOW);
      digitalWrite(pump2Pin, LOW);
      digitalWrite(inletPin, LOW);
      digitalWrite(exhaustPin, LOW);
      Serial.println("ALL OFF");
    }

    if (cmd == '?') { printStatus(); }
  }
}


//OLD CODE: 
// const int pumpPin = 7;
// const int bigValvePin = 8;
// const int smallValvePin = 4;

// void setup() {
//   pinMode(pumpPin, OUTPUT);
//   pinMode(bigValvePin, OUTPUT);
//   pinMode(smallValvePin, OUTPUT);

//   digitalWrite(pumpPin, LOW);
//   digitalWrite(bigValvePin, LOW);
//   digitalWrite(smallValvePin, LOW);

//   Serial.begin(9600);
//   Serial.println("Inflate/Deflate Ready");
//   Serial.println("  i = INFLATE");
//   Serial.println("  d = DEFLATE (active vacuum)");
//   Serial.println("  x = STOP");
// }

// void loop() {
//   if (Serial.available()) {
//     char cmd = Serial.read();

//     if (cmd == 'i') {
//       digitalWrite(smallValvePin, LOW);  // block vacuum line
//       digitalWrite(bigValvePin, HIGH);   // P -> A
//       digitalWrite(pumpPin, HIGH);
//       Serial.println("INFLATING");
//     }

//     if (cmd == 'd') {
//       digitalWrite(bigValvePin, LOW);    // A -> R
//       digitalWrite(smallValvePin, HIGH); // open R -> pump suction
//       digitalWrite(pumpPin, HIGH);
//       Serial.println("DEFLATING");
//     }

//     if (cmd == 'x') {
//       digitalWrite(pumpPin, LOW);
//       digitalWrite(bigValvePin, LOW);
//       digitalWrite(smallValvePin, LOW);
//       Serial.println("ALL OFF");
//     }
//   }
// }


//GOOD CODE




// Combined: Pump + Inlet Valve + Exhaust Valve + MPXV5050GP Pressure Sensor
//
// Plumbing:
//   Pump pressure outlet -> Inlet valve -> T-junction -> Actuator
//                                          T-junction -> Pressure sensor
//                                          T-junction -> Exhaust valve -> Pump vacuum inlet
//
// Wiring:
//   Pump          -> TIP120 -> Arduino D7 (through 1kΩ resistor)
//   Inlet valve   -> TIP120 -> Arduino D8 (through 1kΩ resistor)
//   Exhaust valve -> TIP120 -> Arduino D4 (through 1kΩ resistor)
//   MPXV5050GP pin 2 -> Arduino 5V
//   MPXV5050GP pin 3 -> Arduino GND
//   MPXV5050GP pin 4 -> Arduino A0

// const int pumpPin = 7;
// const int pump2Pin = 9;

// const int inletPin = 8;
// const int exhaustPin = 4;
// const int sensorPin = A0;

// bool pumpOn = false;
// bool inletOn = false;
// bool exhaustOn = false;
// bool monitoring = false;

// float readPressureKpa() {
//   int raw = analogRead(sensorPin);
//   float voltage = raw * (5.0 / 1023.0);
//   float kpa = (voltage / 5.0 - 0.04) / 0.018;
//   if (kpa < 0) kpa = 0;
//   return kpa;
// }

// void printPressure() {
//   int raw = analogRead(sensorPin);
//   float voltage = raw * (5.0 / 1023.0);
//   float kpa = readPressureKpa();
//   float psi = kpa * 0.145038;

//   Serial.print("Raw: ");
//   Serial.print(raw);
//   Serial.print(" | ");
//   Serial.print(voltage, 2);
//   Serial.print("V | ");
//   Serial.print(kpa, 1);
//   Serial.print(" kPa | ");
//   Serial.print(psi, 2);
//   Serial.println(" PSI");
// }

// void printStatus() {
//   Serial.print("Pump: "); Serial.print(pumpOn ? "ON" : "OFF");
//   Serial.print(" | Inlet: "); Serial.print(inletOn ? "OPEN" : "CLOSED");
//   Serial.print(" | Exhaust: "); Serial.println(exhaustOn ? "OPEN" : "CLOSED");
//   printPressure();
// }

// void setup() {
//   pinMode(pumpPin, OUTPUT);
//   pinMode(inletPin, OUTPUT);
//   pinMode(exhaustPin, OUTPUT);

//   digitalWrite(pumpPin, LOW);
//   digitalWrite(inletPin, LOW);
//   digitalWrite(exhaustPin, LOW);

//   Serial.begin(9600);
//   Serial.println("Pump + Valves + MPXV5050GP Ready");
//   Serial.println("  i = INFLATE");
//   Serial.println("  d = DEFLATE (active vacuum)");
//   Serial.println("  h = HOLD");
//   Serial.println("  x = ALL OFF");
//   Serial.println("  p = toggle pump");
//   Serial.println("  1 = toggle inlet valve");
//   Serial.println("  2 = toggle exhaust valve");
//   Serial.println("  r = read pressure once");
//   Serial.println("  m = monitor pressure (any key to stop)");
//   Serial.println("  ? = status");
// }

// void loop() {
//   if (monitoring) {
//     printPressure();
//     delay(250);
//     if (Serial.available()) {
//       Serial.read();
//       monitoring = false;
//       Serial.println("-- Monitoring stopped --");
//     }
//     return;
//   }

//   if (Serial.available()) {
//     char cmd = Serial.read();

//     if (cmd == 'i') {
//       inletOn = true;
//       exhaustOn = false;
//       pumpOn = true;
//       digitalWrite(exhaustPin, LOW);
//       digitalWrite(inletPin, HIGH);
//       digitalWrite(pumpPin, HIGH);
//       Serial.println("INFLATING");
//     }

//     if (cmd == 'd') {
//       inletOn = false;
//       exhaustOn = true;
//       pumpOn = true;
//       digitalWrite(inletPin, LOW);
//       digitalWrite(exhaustPin, HIGH);
//       digitalWrite(pumpPin, HIGH);
//       Serial.println("DEFLATING");
//     }

//     if (cmd == 'h') {
//       inletOn = false;
//       exhaustOn = false;
//       pumpOn = false;
//       digitalWrite(inletPin, LOW);
//       digitalWrite(exhaustPin, LOW);
//       digitalWrite(pumpPin, LOW);
//       Serial.println("HOLDING");
//     }

//     if (cmd == 'x') {
//       pumpOn = false;
//       inletOn = false;
//       exhaustOn = false;
//       digitalWrite(pumpPin, LOW);
//       digitalWrite(inletPin, LOW);
//       digitalWrite(exhaustPin, LOW);
//       Serial.println("ALL OFF");
//     }

//     if (cmd == 'p') {
//       pumpOn = !pumpOn;
//       digitalWrite(pumpPin, pumpOn ? HIGH : LOW);
//       Serial.print("Pump: "); Serial.println(pumpOn ? "ON" : "OFF");
//     }

//     if (cmd == '1') {
//       inletOn = !inletOn;
//       digitalWrite(inletPin, inletOn ? HIGH : LOW);
//       Serial.print("Inlet: "); Serial.println(inletOn ? "OPEN" : "CLOSED");
//     }

//     if (cmd == '2') {
//       exhaustOn = !exhaustOn;
//       digitalWrite(exhaustPin, exhaustOn ? HIGH : LOW);
//       Serial.print("Exhaust: "); Serial.println(exhaustOn ? "OPEN" : "CLOSED");
//     }

//     if (cmd == 'r') { printPressure(); }
//     if (cmd == 'm') { monitoring = true; Serial.println("-- Monitoring (any key to stop) --"); }
//     if (cmd == '?') { printStatus(); }
//   }
// }

// MPXV5050GP Pressure Sensor Test
//
// Pinout (SOP-8, port nozzle facing you, dot top left):
//   Left side top to bottom:
//     Pin 1 - N/C
//     Pin 2 - Arduino 5V
//     Pin 3 - Arduino GND (soldered)
//     Pin 4 - Arduino A0
//   Right side - all N/C

// const int sensorPin = A0;

// float readPressureKpa() {
//   int raw = analogRead(sensorPin);
//   float voltage = raw * (5.0 / 1023.0);
//   float kpa = (voltage / 5.0 - 0.04) / 0.018;
//   if (kpa < 0) kpa = 0;
//   return kpa;
// }

// void setup() {
//   Serial.begin(9600);
//   Serial.println("MPXV5050GP Pressure Sensor Test");
//   Serial.println("  r = read once");
//   Serial.println("  m = monitor (any key to stop)");
// }

// bool monitoring = false;

// void loop() {
//   if (monitoring) {
//     int raw = analogRead(sensorPin);
//     float voltage = raw * (5.0 / 1023.0);
//     float kpa = readPressureKpa();
//     float psi = kpa * 0.145038;

//     Serial.print("Raw: ");
//     Serial.print(raw);
//     Serial.print(" | ");
//     Serial.print(voltage, 2);
//     Serial.print("V | ");
//     Serial.print(kpa, 1);
//     Serial.print(" kPa | ");
//     Serial.print(psi, 2);
//     Serial.println(" PSI");
//     delay(250);

//     if (Serial.available()) {
//       Serial.read();
//       monitoring = false;
//       Serial.println("-- Stopped --");
//     }
//     return;
//   }

//   if (Serial.available()) {
//     char cmd = Serial.read();
//     if (cmd == 'r') {
//       int raw = analogRead(sensorPin);
//       float voltage = raw * (5.0 / 1023.0);
//       float kpa = readPressureKpa();
//       float psi = kpa * 0.145038;
//       Serial.print("Raw: ");
//       Serial.print(raw);
//       Serial.print(" | ");
//       Serial.print(voltage, 2);
//       Serial.print("V | ");
//       Serial.print(kpa, 1);
//       Serial.print(" kPa | ");
//       Serial.print(psi, 2);
//       Serial.println(" PSI");
//     }
//     if (cmd == 'm') {
//       monitoring = true;
//       Serial.println("-- Monitoring (any key to stop) --");
//     }
//   }
// }

// Combined: Pump + Inlet Valve + Exhaust Valve + Pressure Sensor
//
// Plumbing:
//   Pump pressure outlet -> Inlet valve -> T-junction -> Actuator
//                                          T-junction -> Pressure sensor
//                                          T-junction -> Exhaust valve -> Pump vacuum inlet
//
// Wiring:
//   Pump          -> TIP120 -> Arduino D7 (through 1kΩ resistor)
//   Inlet valve   -> TIP120 -> Arduino D8 (through 1kΩ resistor)
//   Exhaust valve -> TIP120 -> Arduino D4 (through 1kΩ resistor)
//   Pressure sensor pin 1 -> Arduino 5V
//   Pressure sensor pin 2 -> Arduino A0
//   Pressure sensor pin 3 -> Arduino GND

// const int pumpPin = 7;
// const int inletPin = 8;
// const int exhaustPin = 4;
// const int sensorPin = A0;

// bool pumpOn = false;
// bool inletOn = false;
// bool exhaustOn = false;
// bool monitoring = false;

// float readPressurePSI() {
//   int raw = analogRead(sensorPin);
//   float voltage = raw * (5.0 / 1023.0);
//   float psi = (voltage - 0.5) * (15.0 / 4.0);
//   if (psi < 0) psi = 0;
//   return psi;
// }

// void printPressure() {
//   int raw = analogRead(sensorPin);
//   float voltage = raw * (5.0 / 1023.0);
//   float psi = readPressurePSI();
//   float kpa = psi * 6.89476;

//   Serial.print("Raw: ");
//   Serial.print(raw);
//   Serial.print(" | ");
//   Serial.print(voltage, 2);
//   Serial.print("V | ");
//   Serial.print(psi, 2);
//   Serial.print(" PSI | ");
//   Serial.print(kpa, 1);
//   Serial.println(" kPa");
// }

// void printStatus() {
//   Serial.print("Pump: "); Serial.print(pumpOn ? "ON" : "OFF");
//   Serial.print(" | Inlet: "); Serial.print(inletOn ? "OPEN" : "CLOSED");
//   Serial.print(" | Exhaust: "); Serial.println(exhaustOn ? "OPEN" : "CLOSED");
//   printPressure();
// }

// void setup() {
//   pinMode(pumpPin, OUTPUT);
//   pinMode(inletPin, OUTPUT);
//   pinMode(exhaustPin, OUTPUT);

//   digitalWrite(pumpPin, LOW);
//   digitalWrite(inletPin, LOW);
//   digitalWrite(exhaustPin, LOW);

//   Serial.begin(9600);
//   Serial.println("Pump + Valves + Pressure Sensor Ready");
//   Serial.println("  i = INFLATE");
//   Serial.println("  d = DEFLATE (active vacuum)");
//   Serial.println("  h = HOLD (close both valves)");
//   Serial.println("  x = ALL OFF");
//   Serial.println("  p = toggle pump");
//   Serial.println("  1 = toggle inlet valve");
//   Serial.println("  2 = toggle exhaust valve");
//   Serial.println("  r = read pressure once");
//   Serial.println("  m = monitor pressure (any key to stop)");
//   Serial.println("  ? = status");
// }

// void loop() {
//   if (monitoring) {
//     printPressure();
//     delay(250);
//     if (Serial.available()) {
//       Serial.read();
//       monitoring = false;
//       Serial.println("-- Monitoring stopped --");
//     }
//     return;
//   }

//   if (Serial.available()) {
//     char cmd = Serial.read();

//     if (cmd == 'i') {
//       inletOn = true;
//       exhaustOn = false;
//       pumpOn = true;
//       digitalWrite(exhaustPin, LOW);
//       digitalWrite(inletPin, HIGH);
//       digitalWrite(pumpPin, HIGH);
//       Serial.println("INFLATING");
//     }

//     if (cmd == 'd') {
//       inletOn = false;
//       exhaustOn = true;
//       pumpOn = true;
//       digitalWrite(inletPin, LOW);
//       digitalWrite(exhaustPin, HIGH);
//       digitalWrite(pumpPin, HIGH);
//       Serial.println("DEFLATING");
//     }

//     if (cmd == 'h') {
//       inletOn = false;
//       exhaustOn = false;
//       pumpOn = false;
//       digitalWrite(inletPin, LOW);
//       digitalWrite(exhaustPin, LOW);
//       digitalWrite(pumpPin, LOW);
//       Serial.println("HOLDING");
//     }

//     if (cmd == 'x') {
//       pumpOn = false;
//       inletOn = false;
//       exhaustOn = false;
//       digitalWrite(pumpPin, LOW);
//       digitalWrite(inletPin, LOW);
//       digitalWrite(exhaustPin, LOW);
//       Serial.println("ALL OFF");
//     }

//     if (cmd == 'p') {
//       pumpOn = !pumpOn;
//       digitalWrite(pumpPin, pumpOn ? HIGH : LOW);
//       Serial.print("Pump: "); Serial.println(pumpOn ? "ON" : "OFF");
//     }

//     if (cmd == '1') {
//       inletOn = !inletOn;
//       digitalWrite(inletPin, inletOn ? HIGH : LOW);
//       Serial.print("Inlet: "); Serial.println(inletOn ? "OPEN" : "CLOSED");
//     }

//     if (cmd == '2') {
//       exhaustOn = !exhaustOn;
//       digitalWrite(exhaustPin, exhaustOn ? HIGH : LOW);
//       Serial.print("Exhaust: "); Serial.println(exhaustOn ? "OPEN" : "CLOSED");
//     }

//     if (cmd == 'r') { printPressure(); }
//     if (cmd == 'm') { monitoring = true; Serial.println("-- Monitoring (any key to stop) --"); }
//     if (cmd == '?') { printStatus(); }
//   }
// }


// Pressure Sensor Test Only
// Honeywell ASDX015PAAA5
//
// Wiring:
//   Pin 1 -> Arduino 5V
//   Pin 3 -> Arduino GND
//   Pin 6 -> Arduino A0
//   All other pins -> leave unconnected
//   Air tube on port nozzle

// const int sensorPin = A0;

// float readPressurePSI() {
//   int raw = analogRead(sensorPin);
//   float voltage = raw * (5.0 / 1023.0);
//   float psi = (voltage - 0.5) * (15.0 / 4.0);
//   if (psi < 0) psi = 0;
//   return psi;
// }

// void setup() {
//   Serial.begin(9600);
//   Serial.println("Pressure Sensor Test");
//   Serial.println("  r = read once");
//   Serial.println("  m = monitor continuously (any key to stop)");
// }

// bool monitoring = false;

// void loop() {
//   if (monitoring) {
//     int raw = analogRead(sensorPin);
//     float voltage = raw * (5.0 / 1023.0);
//     float psi = readPressurePSI();
//     float kpa = psi * 6.89476;

//     Serial.print("Raw: ");
//     Serial.print(raw);
//     Serial.print(" | ");
//     Serial.print(voltage, 2);
//     Serial.print("V | ");
//     Serial.print(psi, 2);
//     Serial.print(" PSI | ");
//     Serial.print(kpa, 1);
//     Serial.println(" kPa");
//     delay(250);

//     if (Serial.available()) {
//       Serial.read();
//       monitoring = false;
//       Serial.println("-- Stopped --");
//     }
//     return;
//   }

//   if (Serial.available()) {
//     char cmd = Serial.read();
//     if (cmd == 'r') {
//       int raw = analogRead(sensorPin);
//       float voltage = raw * (5.0 / 1023.0);
//       float psi = readPressurePSI();
//       float kpa = psi * 6.89476;
//       Serial.print("Raw: ");
//       Serial.print(raw);
//       Serial.print(" | ");
//       Serial.print(voltage, 2);
//       Serial.print("V | ");
//       Serial.print(psi, 2);
//       Serial.print(" PSI | ");
//       Serial.print(kpa, 1);
//       Serial.println(" kPa");
//     }
//     if (cmd == 'm') {
//       monitoring = true;
//       Serial.println("-- Monitoring (any key to stop) --");
//     }
//   }
// }



// //GOODCODE YUM
// // Pump + Inlet Valve + Exhaust/Vacuum Valve

// // Plumbing:
// //   Pump pressure outlet -> Inlet valve -> T-junction -> Actuator
// //                                          T-junction -> Exhaust valve -> Pump vacuum inlet

// // Wiring:
// //   Pump          -> TIP120 -> Arduino D7 (through 1kΩ resistor)
// //   Inlet valve   -> TIP120 -> Arduino D8 (through 1kΩ resistor)
// //   Exhaust valve -> TIP120 -> Arduino D6 (through 1kΩ resistor)

// const int pumpPin = 7;
// const int inletPin = 8;
// const int exhaustPin = 4;

// void setup() {
//   pinMode(pumpPin, OUTPUT);
//   pinMode(inletPin, OUTPUT);
//   pinMode(exhaustPin, OUTPUT);

//   digitalWrite(pumpPin, LOW);
//   digitalWrite(inletPin, LOW);
//   digitalWrite(exhaustPin, LOW);

//   Serial.begin(9600);
//   Serial.println("Inflate/Deflate Ready");
//   Serial.println("  i = INFLATE");
//   Serial.println("  d = DEFLATE (active vacuum)");
//   Serial.println("  h = HOLD (close both valves)");
//   Serial.println("  x = ALL OFF");
//   Serial.println("  p = toggle pump only");
//   Serial.println("  1 = toggle inlet valve only");
//   Serial.println("  2 = toggle exhaust valve only");
//   Serial.println("  ? = status");
// }

// bool pumpOn = false;
// bool inletOn = false;
// bool exhaustOn = false;

// void printStatus() {
//   Serial.print("Pump: "); Serial.print(pumpOn ? "ON" : "OFF");
//   Serial.print(" | Inlet: "); Serial.print(inletOn ? "OPEN" : "CLOSED");
//   Serial.print(" | Exhaust: "); Serial.println(exhaustOn ? "OPEN" : "CLOSED");
// }

// void loop() {
//   if (Serial.available()) {
//     char cmd = Serial.read();

//     if (cmd == 'i') {
//       inletOn = true;
//       exhaustOn = false;
//       pumpOn = true;
//       digitalWrite(exhaustPin, LOW);
//       digitalWrite(inletPin, HIGH);
//       digitalWrite(pumpPin, HIGH);
//       Serial.println("INFLATING");
//     }

//     if (cmd == 'd') {
//       inletOn = false;
//       exhaustOn = true;
//       pumpOn = true;
//       digitalWrite(inletPin, LOW);
//       digitalWrite(exhaustPin, HIGH);
//       digitalWrite(pumpPin, HIGH);
//       Serial.println("DEFLATING (active vacuum)");
//     }

//     if (cmd == 'h') {
//       inletOn = false;
//       exhaustOn = false;
//       pumpOn = false;
//       digitalWrite(inletPin, LOW);
//       digitalWrite(exhaustPin, LOW);
//       digitalWrite(pumpPin, LOW);
//       Serial.println("HOLDING - valves closed");
//     }

//     if (cmd == 'x') {
//       pumpOn = false;
//       inletOn = false;
//       exhaustOn = false;
//       digitalWrite(pumpPin, LOW);
//       digitalWrite(inletPin, LOW);
//       digitalWrite(exhaustPin, LOW);
//       Serial.println("ALL OFF");
//     }

//     if (cmd == 'p') {
//       pumpOn = !pumpOn;
//       digitalWrite(pumpPin, pumpOn ? HIGH : LOW);
//       Serial.print("Pump: "); Serial.println(pumpOn ? "ON" : "OFF");
//     }

//     if (cmd == '1') {
//       inletOn = !inletOn;
//       digitalWrite(inletPin, inletOn ? HIGH : LOW);
//       Serial.print("Inlet: "); Serial.println(inletOn ? "OPEN" : "CLOSED");
//     }

//     if (cmd == '2') {
//       exhaustOn = !exhaustOn;
//       digitalWrite(exhaustPin, exhaustOn ? HIGH : LOW);
//       Serial.print("Exhaust: "); Serial.println(exhaustOn ? "OPEN" : "CLOSED");
//     }

//     if (cmd == '?') {
//       printStatus();
//     }
//   }
//}
//GOOOD CODEEEEE 


// old w only one
// const int pumpPin = 7;
// const int valvePin = 8;

// void setup() {
//   pinMode(pumpPin, OUTPUT);
//   pinMode(valvePin, OUTPUT);

//   digitalWrite(pumpPin, HIGH); // pump always on
//   digitalWrite(valvePin, LOW);

//   Serial.begin(9600);
//   Serial.println("Active Inflate/Deflate Ready");
//   Serial.println("  i = INFLATE (P -> A, pressure into actuator)");
//   Serial.println("  d = DEFLATE (A -> R, vacuum pulls air out)");
// }

// void loop() {
//   if (Serial.available()) {
//     char cmd = Serial.read();

//     if (cmd == 'i') {
//       digitalWrite(valvePin, HIGH);
//       Serial.println("INFLATING");
//     }

//     if (cmd == 'd') {
//       digitalWrite(valvePin, LOW);
//       Serial.println("DEFLATING (active vacuum)");
//     }
//   }
// }

// old w only one


// pump conseved code statt!!! 
// const int pumpPin = 7;
// const int valvePin = 8;

// void setup() {
//   pinMode(pumpPin, OUTPUT);
//   pinMode(valvePin, OUTPUT);

//   digitalWrite(pumpPin, LOW);
//   digitalWrite(valvePin, LOW);

//   Serial.begin(9600);
//   Serial.println("Pump + 5/2 Valve Control Ready");
//   Serial.println("Commands:");
//   Serial.println("  i = INFLATE (pump on, valve open)");
//   Serial.println("  d = DEFLATE (pump off, valve exhaust)");
//   Serial.println("  x = everything OFF");
// }

// void loop() {
//   if (Serial.available()) {
//     char cmd = Serial.read();

//     if (cmd == 'i') {
//       digitalWrite(valvePin, HIGH);
//       digitalWrite(pumpPin, HIGH);
//       Serial.println("INFLATING - pump on, P -> A");
//     }

//     if (cmd == 'd') {
//       digitalWrite(pumpPin, LOW);
//       digitalWrite(valvePin, LOW);
//       Serial.println("DEFLATING - pump off, A -> R exhaust");
//     }

//     if (cmd == 'x') {
//       digitalWrite(pumpPin, LOW);
//       digitalWrite(valvePin, LOW);
//       Serial.println("OFF");
//     }
//   }
// }

//good code end

// const int valvePin = 8;
// const int pumpPin = 7;

// void setup() {
//   pinMode(pumpPin, OUTPUT);
//   pinMode(valvePin, OUTPUT);

//   digitalWrite(pumpPin, LOW);
//   digitalWrite(valvePin, LOW);

//   Serial.begin(9600);
//   Serial.println("Pump + Valve Control Ready");
//   Serial.println("Send 'p' to toggle pump");
//   Serial.println("Send 'v' to toggle valve");
//   Serial.println("Send 'b' to toggle both ON");
//   Serial.println("Send 'x' to turn everything OFF");
// }

// bool pumpOn = false;
// bool valveOn = false;

// void loop() {
//   if (Serial.available()) {
//     char cmd = Serial.read();

//     if (cmd == 'p') {
//       pumpOn = !pumpOn;
//       digitalWrite(pumpPin, pumpOn ? HIGH : LOW);
//       Serial.print("Pump: ");
//       Serial.println(pumpOn ? "ON" : "OFF");
//     }

//     if (cmd == 'v') {
//       valveOn = !valveOn;
//       digitalWrite(valvePin, valveOn ? HIGH : LOW);
//       Serial.print("Valve: ");
//       Serial.println(valveOn ? "ON" : "OFF");
//     }

//     if (cmd == 'b') {
//       pumpOn = true;
//       valveOn = true;
//       digitalWrite(pumpPin, HIGH);
//       digitalWrite(valvePin, HIGH);
//       Serial.println("Both ON - air should be flowing to actuator");
//     }

//     if (cmd == 'x') {
//       pumpOn = false;
//       valveOn = false;
//       digitalWrite(pumpPin, LOW);
//       digitalWrite(valvePin, LOW);
//       Serial.println("Everything OFF");
//     }
//   }
// }

// const int SOLENOID_1 = 6;
// const int SOLENOID_2 = 7;

// void setup() {
//   // Set pins as outputs
//   pinMode(SOLENOID_1, OUTPUT);
//   // pinMode(SOLENOID_2, OUTPUT);
 
//   // Start with both OFF
//   digitalWrite(SOLENOID_1, LOW);
//   digitalWrite(SOLENOID_2, LOW);
 
//   // Start serial monitor for feedback
//   Serial.begin(9600);
//   Serial.println("=== SOLENOID VALVE TEST ===");
//   Serial.println("Solenoid 1: Pin 7");
//   Serial.println("Solenoid 2: Pin 6");
//   Serial.println();
//   Serial.println("Starting alternating test...\n");
 
//   delay(2000);  // Wait 2 seconds before starting
// }

// void loop() {
//   // Turn ON Solenoid 1
//   Serial.println(">>> Solenoid 1 ON (Pin 7)");
//   digitalWrite(SOLENOID_1, HIGH);
//   delay(1000);  // Stay on for 2 seconds
 
//   // Turn OFF Solenoid 1
//   Serial.println("    Solenoid 1 OFF");
//   digitalWrite(SOLENOID_1, LOW);
//   delay(4000);  // Wait 1 second
 
//   // Turn ON Solenoid 2
//   Serial.println(">>> Solenoid 2 ON (Pin 6)");
//   digitalWrite(SOLENOID_2, HIGH);
//   delay(2000);  // Stay on for 2 seconds
 
//   // Turn OFF Solenoid 2
//   Serial.println("    Solenoid 2 OFF");
//   digitalWrite(SOLENOID_2, LOW);
//   delay(1000);  // Wait 1 second
 
//   Serial.println("---");
//}

// // Pin definitions
// const int PUMP_PIN = 6;
// const int VALVE_PIN = 7;

// void setup() {
//   pinMode(PUMP_PIN, OUTPUT);
//   pinMode(VALVE_PIN, OUTPUT);
 
//   // Start with everything off
//   digitalWrite(PUMP_PIN, LOW);
//   digitalWrite(VALVE_PIN, LOW);
 
//   Serial.begin(9600);
//   Serial.println("=== Pneumatic Control System ===");
//   Serial.println("Ready to start inflate/deflate cycles");
//   delay(2000);
// }

// void loop() {
//   // INFLATE: Pump ON + Valve OPEN
//   Serial.println("\n>>> INFLATING <<<");
//   digitalWrite(PUMP_PIN, HIGH);   // Turn pump ON
//   digitalWrite(VALVE_PIN, HIGH);  // Open valve
//   delay(30000);                    // Inflate for 5 seconds
 
//   // HOLD: Pump OFF + Valve CLOSED
//   Serial.println(">>> HOLDING PRESSURE <<<");
//   digitalWrite(PUMP_PIN, LOW);    // Turn pump OFF
//   digitalWrite(VALVE_PIN, LOW);   // Close valve to trap air
//   delay(10000);                    // Hold for 2 seconds
 
  // // DEFLATE: Pump OFF + Valve OPEN
  // Serial.println(">>> DEFLATING <<<");
  // digitalWrite(PUMP_PIN, LOW);    // Keep pump OFF
  // digitalWrite(VALVE_PIN, HIGH);  // Open valve to release air
  // delay(1000);                    // Allow 4 seconds to deflate
 
  // // REST: Everything OFF
  // Serial.println(">>> REST <<<");
  // digitalWrite(PUMP_PIN, LOW);
  // digitalWrite(VALVE_PIN, LOW);
  // delay(1000);                    // Wait 2 seconds before next cycle
 
  // Serial.println("\n--- Cycle complete, repeating ---\n");
// // Pin definitions
// const int PUMP_PIN = 6;
// const int VALVE_PIN = 7;

// void setup() {
//   pinMode(PUMP_PIN, OUTPUT);
//   pinMode(VALVE_PIN, OUTPUT);
 
//   // Start with everything off
//   digitalWrite(PUMP_PIN, LOW);
//   digitalWrite(VALVE_PIN, LOW);
 
//   Serial.begin(9600);
//   Serial.println("=== Pneumatic System Test ===");
//   Serial.println("Starting in 3 seconds...");
//   delay(3000);
// }

// void loop() {
//   // Test 1: Pump only
//   Serial.println("\n--- Test 1: PUMP ONLY (5 sec) ---");
//   digitalWrite(PUMP_PIN, HIGH);
//   digitalWrite(VALVE_PIN, LOW);
//   delay(5000);
//   digitalWrite(PUMP_PIN, LOW);
//   Serial.println("Pump OFF");
//   delay(2000);
 
//   // Test 2: Valve only
//   Serial.println("\n--- Test 2: VALVE ONLY (3 sec) ---");
//   digitalWrite(PUMP_PIN, LOW);
//   digitalWrite(VALVE_PIN, HIGH);
//   delay(3000);
//   digitalWrite(VALVE_PIN, LOW);
//   Serial.println("Valve OFF");
//   delay(2000);
 
//   // Test 3: Both together (inflate)
//   Serial.println("\n--- Test 3: PUMP + VALVE (5 sec) ---");
//   digitalWrite(PUMP_PIN, HIGH);
//   digitalWrite(VALVE_PIN, HIGH);
//   delay(5000);
//   digitalWrite(PUMP_PIN, LOW);
//   digitalWrite(VALVE_PIN, LOW);
//   Serial.println("Both OFF");
 
//   Serial.println("\n=== Test cycle complete. Waiting 5 sec... ===\n");
//   delay(5000);
// }