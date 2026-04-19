#include <SPI.h> // Includes the library to use fast Serial communication pins (D11, D13)

// --- 1. GLOBAL SETTINGS ---
const int latchPin = 10;           // Pin 10 tells the MBI5026 to "show" the data we sent
const int layerPins[4] = {A0, A1, A2, A3}; // These control the transistors for each floor
int danceSpeed = 80;               // A base time in milliseconds for animations

void setup() {
  // Loop through our 4 layer pins to set them as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(layerPins[i], OUTPUT);
    digitalWrite(layerPins[i], LOW); // Ensure all floors start turned OFF
  }
  
  pinMode(latchPin, OUTPUT);       // Set the Latch pin as an output
  
  SPI.begin();                     // Wake up the SPI hardware inside the Nano
  // Set SPI speed to 1MHz, most significant bit first, and mode 0 (standard for MBI chips)
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  
  Serial.begin(9600);              // Start communication with your computer for debugging
}

void loop() {
  // --- STEP 1: Layer by layer with 2s delay ---
  for (int z = 0; z < 4; z++) {
    drawFullLayer(z, 2000);        // Turn on all 16 LEDs on floor 'z' for 2000ms
  }

  // --- STEP 2: The Snake (1 to 64) ---
  for (int z = 0; z < 4; z++) {     // For each floor...
    for (int bitPos = 0; bitPos < 16; bitPos++) { // For each of the 16 LEDs on that floor...
      allLayersOff();              // Safety: Turn off layers before shifting data
      sendToMBI(1 << bitPos);      // Shift a '1' to the specific column position
      digitalWrite(layerPins[z], HIGH); // Turn on the floor to see that one LED
      delay(50);                   // Wait a short time so it looks like it's moving
    }
  }

  // --- STEP 3: Layer by layer fast (The Scan) ---
  for (int z = 0; z < 4; z++) {
    drawFullLayer(z, 100);         // Rapidly cycle floors with only 100ms delay
  }

  // --- STEP 4-6: The Moves ---
  bounceLayer(2);                  // Run the bounce animation 2 times
  spinningPillar(3);               // Run the rotation animation 3 times
  randomSparkle(40);               // Flash 40 random LEDs

  // --- STEP 7: Expanding Box (Half Speed) ---
  int slowSpeed = danceSpeed * 2;  // Double the delay time to make it look slower
  expandingBoxSlow(5, slowSpeed);  // Pulse the box 5 times at the new slow speed

  delay(1000);                     // Wait 1 second before starting the whole show again
}

// --- DANCE MOVE FUNCTIONS ---

void bounceLayer(int repeats) {
  for (int r = 0; r < repeats; r++) {
    for (int z = 0; z < 4; z++) drawFullLayer(z, danceSpeed); // Go up
    for (int z = 2; z >= 1; z--) drawFullLayer(z, danceSpeed); // Go down
  }
}

void spinningPillar(int rotations) {
  // Hexadecimal codes for the 4 corners of the 4x4 grid
  uint16_t corners[4] = {0x0033, 0x00CC, 0xCC00, 0x3300}; 
  for (int rot = 0; rot < rotations; rot++) {
    for (int c = 0; c < 4; c++) {
      allLayersOff();
      sendToMBI(corners[c]);       // Load the corner pattern
      for(int i=0; i<4; i++) digitalWrite(layerPins[i], HIGH); // Light all 4 floors
      delay(danceSpeed * 1.5);     // Wait 1.5x dance speed for visibility
    }
  }
}

void randomSparkle(int count) {
  for (int i = 0; i < count; i++) {
    int z = random(0, 4);          // Pick a random floor
    int bit = random(0, 16);       // Pick a random column
    allLayersOff();
    sendToMBI(1 << bit);           // Light only that column
    digitalWrite(layerPins[z], HIGH); 
    delay(30);                     // Very short flash
    digitalWrite(layerPins[z], LOW);
  }
}

void expandingBoxSlow(int pulses, int customSpeed) {
  uint16_t center = 0x0660;        // Binary for the 4 middle LEDs
  uint16_t outer = 0xF99F;         // Binary for the LEDs on the outer edges
  for (int p = 0; p < pulses; p++) {
    allLayersOff();
    sendToMBI(center);             // Show the middle square
    digitalWrite(layerPins[1], HIGH); digitalWrite(layerPins[2], HIGH); // On middle floors
    delay(customSpeed);
    
    allLayersOff();
    sendToMBI(outer);              // Show the big outer frame
    for(int i=0; i<4; i++) digitalWrite(layerPins[i], HIGH); // On all floors
    delay(customSpeed);
  }
}

// --- HELPERS (The "Tools" used by the moves) ---

void drawFullLayer(int z, int duration) {
  allLayersOff();                  // Turn off power to all floors
  sendToMBI(0xFFFF);               // Tell MBI5026 to open all 16 sinks (Binary all 1s)
  digitalWrite(layerPins[z], HIGH); // Apply power to floor 'z'
  delay(duration);                 // Keep it on for the requested time
  digitalWrite(layerPins[z], LOW);  // Turn power off
}

void sendToMBI(uint16_t data) {
  digitalWrite(latchPin, LOW);     // Prepare the chip to receive data
  SPI.transfer16(data);            // Blast the 16 bits out of D11 and D13
  digitalWrite(latchPin, HIGH);    // Lock the data into the output pins
}

void allLayersOff() {
  // Simple loop to make sure every transistor is closed
  for (int i = 0; i < 4; i++) digitalWrite(layerPins[i], LOW);
}
