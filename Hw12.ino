const int button1 = 5;
const int button2 = 2;
const int potPin = A0;

int sequence[] = {2, -1, 1};
int inputIndex = 0;
bool waitingForInput = true;

void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  Serial.println("Enter the code. Waiting for input...");
}

void loop() {
  if (waitingForInput) {
    if (sequence[inputIndex] == -1) {
      int potValue = analogRead(potPin);
      if (potValue < 50) {
        Serial.println("Potentiometer step entered.");
        inputIndex++;
        delay(500);
      }
    } else {
      if (digitalRead(sequence[inputIndex]) == HIGH) { // Inverted logic
        Serial.print("Button ");
        Serial.print(sequence[inputIndex]);
        Serial.println(" step entered.");
        inputIndex++;
        delay(500);
      }
    }

    if (inputIndex >= sizeof(sequence) / sizeof(sequence[0])) {
      waitingForInput = false;
    }
  } else {
    if (validateCode()) {
      Serial.println("Code is correct!");
    } else {
      Serial.println("Code is wrong!");
    }
    resetMachine();
  }
}

bool validateCode() {
  return inputIndex == sizeof(sequence) / sizeof(sequence[0]);
}

void resetMachine() {
  inputIndex = 0;
  waitingForInput = true;
  delay(1000);
  Serial.println("Try again. Waiting for input...");
}

