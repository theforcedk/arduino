#define transmitPin 4 // RF transmit pin = Digital pin 4

const int signalSize = 13;

/*
  2   5   LH  2
  2   2   LL  1
  5   5   HH  4
  2   5   LH  2
  2   2   LL  1
  5   5   HH  4
  2   5   LH  2
  2   5   LH  2
  2   5   LH  2
  2   2   LL  1
  5   2   HL  3
  5   5   HH  4
  2   42  VLH 5
*/
int ding[] = {2, 1, 4, 2, 1, 4, 2, 2, 2, 1, 3, 4, 5};

// Play with this value
int timeDelay = 135;

void setup() {
   Serial.begin(9600);
   pinMode(transmitPin, OUTPUT);
   delay(3000);

  // wait 3 seconds, then transmit the payload
  int highLength = 0;
  int lowLength = 0;

  for(int x = 0; x < 19; x++) {
    for(int i = 0; i < signalSize; i++) { 
      switch(ding[i]) {
        case 1: // LL
          highLength = 2;
          lowLength = 2;
        break;

        case 2: // LH
          highLength = 2;
          lowLength = 5;
        break;

        case 3: // HL
          highLength = 5;
          lowLength = 2;
        break;

        case 4: // HH
          highLength = 5;
          lowLength = 5;
        break;

        case 5: // VLH
          highLength = 2;
          lowLength = 42;
        break;
      }

      // transmit HIGH signal
      digitalWrite(transmitPin, HIGH);
      delayMicroseconds(highLength*timeDelay);

      digitalWrite(transmitPin,LOW);
      delayMicroseconds(lowLength*timeDelay);
    }
  }
}

void loop() { }