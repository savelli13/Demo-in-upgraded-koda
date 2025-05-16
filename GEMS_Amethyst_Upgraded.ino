#define BTN 9
#define LED_R 7
#define LED_G 10
#define LED_B 4
#define LX_A 1
#define LX_B 3
#define LX_OUT 0

const int THRESHOLD_DARK = 75; 
const int COLOR_DELAY = 250;    

bool colorCycleActive = false;
unsigned long lastColorChange = 0;
int currentColor = 0;
bool lastButtonState = false;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(BTN, INPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LX_A, INPUT);
  pinMode(LX_B, INPUT);
  pinMode(LX_OUT, INPUT);

  Serial.begin(115200);
  Serial.println("Amethyst Demo!");
}

void loop() {
  delay(10);

  int lightLevel = lx(1);

  bool reading = !digitalRead(BTN);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != colorCycleActive) {
      colorCycleActive = reading;
    }
  }
  lastButtonState = reading;

  if (lightLevel < THRESHOLD_DARK) {
    playSOS();
    return;
  }

  if (colorCycleActive) {
    if (millis() - lastColorChange >= COLOR_DELAY) {
      currentColor = (currentColor + 1) % 3;
      switch (currentColor) {
        case 0: rgb(0, 0, 255); break; 
        case 1: rgb(0, 255, 0); break; 
        case 2: rgb(255, 0, 0); break; 
      }
      lastColorChange = millis();
    }
  } else {
    rgb(0, 0, 0); 
  }
}

void playSOS() {
  const int dot = 200;
  const int dash = dot * 3;
  const int gap = dot;
  const int wordGap = dot * 7;

  int morse[] = {dot, dot, dot, dash, dash, dash, dot, dot, dot};

  for (int i = 0; i < 9 ; i++) {
    rgb(255, 0, 0);  
    delay(morse[i]);
    rgb(0, 0, 0);    
    delay(gap);
  }
  delay(wordGap);  
}

// RGB LED kontrola
void rgb(int R, int G, int B) {
  analogWrite(LED_R, R);
  analogWrite(LED_G, G);
  analogWrite(LED_B, B);
}

int lx(int mode) {
  switch (mode) {
    case 1:
      pinMode(LX_A, INPUT);
      pinMode(LX_B, OUTPUT);
      digitalWrite(LX_B, LOW);
      break;
    case 2:
      pinMode(LX_A, OUTPUT);
      digitalWrite(LX_A, LOW);
      pinMode(LX_B, INPUT);
      break;
    default:
      pinMode(LX_A, INPUT);
      pinMode(LX_B, INPUT);
  }
  return analogRead(LX_OUT);
}
