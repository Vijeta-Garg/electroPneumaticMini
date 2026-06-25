
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
