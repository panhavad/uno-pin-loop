// Arduino Sketch to Control Output via Serial Commands with Pin12 and Pin13 Interaction

// Define the output pins
const int pin12 = 12;
const int pin13 = 13;
bool autoMode = false;    // Flag to track auto mode

void setup() {
  pinMode(pin12, OUTPUT); // Set pin12 as output
  pinMode(pin13, INPUT);  // Set pin13 as input
  Serial.begin(9600);     // Initialize serial communication
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    // Exit auto mode if manual command is received
    if (autoMode && (command == "on" || command == "off")) {
      autoMode = false;
      Serial.println("Exiting AUTO mode, switching to MANUAL mode");
    }

    processCommand(command);
  }
}

void processCommand(String command) {
  if (command == "on") {
    ON();
  } 
  else if (command == "off") {
    OFF();
  } 
  else if (command.startsWith("auto")) {
    int loops, ontime, offtime;
    sscanf(command.c_str(), "auto %d %d %d", &loops, &ontime, &offtime);

    autoMode = true;
    Serial.println("Entering AUTO mode");

    for (int i = 0; i < loops && autoMode; i++) {
      Serial.print("Loop ");
      Serial.print(i + 1);
      Serial.print("/");
      Serial.println(loops);

      OFF();
      Serial.print("Wait ");
      Serial.println(offtime);
      delayWithCountdown(offtime);


      if (!autoMode) break;

      ON();
      Serial.print("Wait ");
      Serial.println(ontime);
      delayWithCountdown(ontime);

    }

    if (autoMode) {
      Serial.println("AUTO mode completed");
      autoMode = false;
    }
  } 
  else {
    Serial.println("Invalid command");
  }
}

void ON() {
  digitalWrite(pin12, LOW);
  Serial.println("ON"); // Should read HIGH
}

void OFF() {
  digitalWrite(pin12, HIGH);
  Serial.println("OFF"); // Should read LOW
}

void delayWithCountdown(int seconds) {
  for (int i = seconds; i > 0; i--) {
    Serial.print("Countdown: ");
    Serial.println(i);
    delayWithCheck(1000);
    if (!autoMode) break;
  }
}

void delayWithCheck(unsigned long delayTime) {
  unsigned long startTime = millis();
  while (millis() - startTime < delayTime) {
    if (Serial.available()) {
      String command = Serial.readStringUntil('\n');
      command.trim();

      if (command == "on" || command == "off") {
        autoMode = false;
        Serial.println("Exiting AUTO mode, switching to MANUAL mode");
        processCommand(command);
        break;
      }
    }
  }
}
