const unsigned long INTERVAL = 30000; // 30 seconds
const int NOISE_THRESHOLD = 20; // Adjust based on your noise level (in mV)

unsigned long previousTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT); // No pull-up resistor!
  Serial.println("Time (ms)\tVoltage (mV)");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - previousTime >= INTERVAL) {
    previousTime = currentTime;

    // Average 10 readings to reduce noise
    float sum = 0;
    for (int i = 0; i < 10; i++) {
      sum += analogRead(A0);
      delay(1);
    }
    float avgRaw = sum / 10.0;

    // Convert to millivolts (5V reference)
    float millivolts = avgRaw * (5000.0 / 1023.0);

    // Apply noise threshold (report 0mV if below threshold)
    if (millivolts < NOISE_THRESHOLD) millivolts = 0;

    // Print data
    Serial.print(currentTime);
    Serial.print("\t, \t");
    Serial.println(millivolts, 1); // 1 decimal place
  }
}