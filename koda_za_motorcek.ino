const int dirPin = 2;
const int stepPin = 3;
const int enablePin = 4;

// Mikrokoraki: 1/4-step
const int stepsPerFullStep = 200;
const int microstepFactor = 4;
const int stepsPerRevolution = stepsPerFullStep * microstepFactor;  // 800

const float desiredRotations = 2.685;  // število obratov (lahko decimalno)
const int delayMicros = 2500;         // čas med koraki

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Aktiviraj motor (LOW = vklopljen pri A4988)
  digitalWrite(enablePin, LOW);

  Serial.begin(9600);
  Serial.print("Pripravljen. Pritisni ENTER za ");
  Serial.print(desiredRotations, 2);
  Serial.println(" obratov v obe smeri.");
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();

    if (c == '\n' || c == '\r') {
      int totalSteps = round(desiredRotations * stepsPerRevolution);

      Serial.print("Vrtenje v desno za ");
      Serial.print(totalSteps);
      Serial.println(" mikrokorakov...");
      digitalWrite(dirPin, HIGH);  // smer: desno
      performSteps(totalSteps);

      delay(500);  // pavza

      Serial.println("Vrtenje v levo za enako razdaljo...");
      digitalWrite(dirPin, LOW);   // smer: levo
      performSteps(totalSteps);

      delay(500);  // pavza

      Serial.print("Vrtenje v desno za ");
      Serial.print(totalSteps);
      Serial.println(" mikrokorakov...");
      digitalWrite(dirPin, HIGH);  // smer: desno
      performSteps(totalSteps);

      delay(500);  // pavza

      Serial.println("Vrtenje v levo za enako razdaljo...");
      digitalWrite(dirPin, LOW);   // smer: levo
      performSteps(totalSteps);

      Serial.println("Končano. Pritisni ENTER za ponovitev.");
    }

    while (Serial.available()) {
      Serial.read(); // počisti buffer
    }
  }
}

// Funkcija za izvajanje korakov
void performSteps(int stepCount) {
  for (int i = 0; i < stepCount; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayMicros);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayMicros);
  }
}















