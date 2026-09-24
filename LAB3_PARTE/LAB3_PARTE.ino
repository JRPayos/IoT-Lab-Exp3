#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h> 

// Initialize I2C LCD (Typical address 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Keypad Configuration
const byte ROWS = 4, COLS = 4; 
char keys[ROWS][COLS] = { 
  {'1','2','3','A'}, 
  {'4','5','6','B'}, 
  {'7','8','9','C'}, 
  {'*','0','#','D'} 
}; 
byte rowPins[ROWS] = { 13, 12, 14, 27 }; 
byte colPins[COLS] = { 26, 25, 33, 32 };

Keypad pad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); 

// Passcode Variables
const char* CODE  = "2468"; 
const int   CLEN  = 4; 
char entry[CLEN + 1] = ""; 
int  entryLen = 0; 


void promptEntry() { 
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("ENTER CODE:"); 
  lcd.setCursor(0, 1); 
  for (int i = 0; i < entryLen; i++) {
    lcd.print('*'); 
  }
}

void checkCode() {
  lcd.clear();
  lcd.setCursor(0, 0);
  
  if (strcmp(entry, CODE) == 0) {
    lcd.print("ACCESS GRANTED");
  } else {
    lcd.print("ACCESS DENIED");
  }
  
  delay(2000);
  entryLen = 0; 
  entry[0] = 0; 
  promptEntry();
}

// Processes individual key presses
void handleKey(char k) { 
  //clear
  if (k == '*') {                 
    entryLen = 0; 
    entry[0] = 0; 
    promptEntry(); 
    return; 
  }
  //submit
  if (k == '#') {                
    checkCode(); 
    return; 
  }
  
  // Accept digits only if we haven't reached the 4-digit limit
  if (entryLen < CLEN && k >= '0' && k <= '9') { 
    entry[entryLen++] = k; 
    entry[entryLen]   = 0; 
    promptEntry(); 
  }
}

void setup() {
  Serial.begin(115200); 
  
  // Initialize LCD with backlight
  lcd.init();
  lcd.backlight();
  
  promptEntry();
  Serial.println("ESP32 Keypad Ready"); 
} 

void loop() { 
  char k = pad.getKey(); 
  if (k) {
    Serial.println(k); // Keep for serial debugging
    handleKey(k);      // Pass the key to the menu logic
  } 
}
