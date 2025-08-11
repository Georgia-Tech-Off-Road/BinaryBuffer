#include <BinaryBuffer.h>

using cmbtl::BinaryBuffer;
// We create a struct to hold our RPM values
struct RPM {
  uint16_t front;
  uint16_t rear;

  // For arguments sake let us say that we know RPM will not exceed 2^12 - 1 = 4095 = max value held by uint16_t
  // We now define encode and decode functions for the struct

    // Default constructor
    RPM() : front(0), rear(0) {}

    RPM (uint16_t front, uint16_t rear) {
      this->front = front;
      this->rear = rear;
    }

    // Write values to buffer
    void encodeRPM(BinaryBuffer &buffer) {
      //Write only 12 bits for each axis
      buffer.writeValue(front, 12);
      buffer.writeValue(rear, 12);
    }

    // Update values from buffer
    void decodeRPM(BinaryBuffer const &buffer) {
      front = buffer.readValue<uint16_t>(12);
      rear = buffer.readValue<uint16_t>(12);
    }

    // Helper function to print RPM values
    void printRPM() {
      Serial.print("Front RPM: ");
      Serial.print(front);
      Serial.print("\nRear RPM: ");
      Serial.println(rear);
    }
};

void setup() {
  Serial.begin(9600);
}

void loop() {

  // We create a binary buffer that can hold 24 bits
  BinaryBuffer transmissionBuffer(24);

  // Set a new RPM for each time
  RPM carRPM(random(0, 4096), random(0, 4096));

  Serial.println("RPM Before Transmission:");
  carRPM.printRPM();
  carRPM.encodeRPM(transmissionBuffer);

  // Pretend that we sent this somehow

  RPM newCarRPM;

  newCarRPM.decodeRPM(transmissionBuffer);
  Serial.println("RPM After Transmission:");
  newCarRPM.printRPM();

}
