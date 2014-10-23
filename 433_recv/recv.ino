#define analogPin A0 // RF data pin = Analog pin 0

byte dataBuffer[512];

int dataCounter = 0;
int maxSignalLength = 255;

const unsigned int upperThreshold = 100;
const unsigned int lowerThreshold = 80;

void setup() {
  Serial.begin(115200);

  // wait until a LOW signal is received
  while(analogRead(analogPin) < 1) { }

  // got HIGH; read the rest of the data into dataBuffer
  for (int i = 0; i < sizeof(dataBuffer); i = i+2) {

    // LOW signal
    dataCounter = 0;
    while (analogRead(analogPin) > upperThreshold && dataCounter < maxSignalLength)
      dataCounter++;

    dataBuffer[i] = dataCounter;

    // HIGH signal
    dataCounter = 0;
    while(analogRead(analogPin) < lowerThreshold && dataCounter < maxSignalLength)
      dataCounter++;

    dataBuffer[i+1] = dataCounter;
  }

  Serial.println(F("LOW,HIGH"));
  delay(20);
  for (int i = 0; i < sizeof(dataBuffer); i = i+2) {
    Serial.print(dataBuffer[i]);
    Serial.print(",");
    Serial.println(dataBuffer[i+1]);
    delay(20);
  }
}

void loop() { }