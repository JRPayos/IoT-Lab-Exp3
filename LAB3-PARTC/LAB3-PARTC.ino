// LASER to LDR read using the Experiment 1 code

const int LDR_PIN = 34;
const int LASER_PIN = 16;
const int THRESHOLD = 1600;  // 12-bit range is 0 to 4095 
  
void setup() { 
  Serial.begin(115200); 
  pinMode(LASER_PIN, OUTPUT);
  
  // Turn the laser ON automatically so it shines on the LDR
  digitalWrite(LASER_PIN, HIGH); 
  Serial.println("ESP32 ready"); 
} 
  
void loop() { 
  int raw = analogRead(LDR_PIN);          // 0 to 4095 
  float volts = raw * (3.3 / 4095.0); 
  Serial.printf("Raw: %d | Volts: %.2f V", raw, volts);

  // Print whether the beam is broken based on your THRESHOLD
  if (raw < THRESHOLD) {
    Serial.println(" -> BEAM BROKEN!");
  } else {
    Serial.println(" -> Beam Intact");
  }

  delay(500); 
} 
