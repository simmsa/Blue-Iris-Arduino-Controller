#include <math.h>

#define LED_PIN 13
#define SWITCH_INPUT A0
#define SPEAKER_PIN 3

#define ON 1
#define OFF 0

// Blue Iris accepts a number called "Global input dio bits" to trigger a
// camera. This function converts the input number into a bitwise number,
// the format Blue Iris expects (a set of bytes with with a 1 in the nth
// position. Ex 6 = 0010000, 3 = 00000100, etc). The arduino's unsigned int type
// has 4 bytes (32 bits) so highest input this function can handle is 32 before
// it overflows
void startBlueIrisRecording(unsigned int global_input_dio_bits) {
    // This is a bitwise operation that converts the input number to a binary
    // number with the 1 at the input digit.
    // Ex: 6 -> 00100000
    unsigned int bitwise_dio = pow(global_input_dio_bits, 2);
    Serial.write(bitwise_dio);
}

void stopBlueIrisRecording() { Serial.write(0); }

bool switchPressed() { return digitalRead(SWITCH_INPUT) == 0; }

bool state = OFF;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(SPEAKER_PIN, OUTPUT);
    pinMode(SWITCH_INPUT, INPUT);

    // I don't know why or where this baud rate is defined by Blue Iris, but it
    // works...
    Serial.begin(9600);
    state = OFF;
}

void loop() {
    bool switchStatus = switchPressed();
    if(switchStatus && state == OFF) {
        Serial.print(1);
        digitalWrite(LED_PIN, HIGH);
        state = ON;
    } else if (!switchStatus && state == ON){
        digitalWrite(LED_PIN, LOW);
        Serial.print(0);
        state = OFF;
    }
    delay(500);
}
