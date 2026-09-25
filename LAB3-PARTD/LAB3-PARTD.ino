const int REED_PIN = 18; 
const int BUTTON_PIN = 19;
  
void setup() { 
  Serial.begin(115200); 
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.println("ESP32 Switches Test Ready"); 
} 
  
void loop() { 
  int switchState = digitalRead(REED_PIN);
  int buttonState = digitalRead(BUTTON_PIN);

  //Reed Switch
  if (switchState == LOW) {
    Serial.print("REED: DETECTED");
  } else {
    Serial.print("REED: NOT DETECTED");
  }

  Serial.print("  |  ");

  //Button Status
  if (buttonState == LOW) {
    Serial.println("BUTTON: PRESSED");
  } else {
    Serial.println("BUTTON: RELEASED");
  }

  delay(200); 
}
