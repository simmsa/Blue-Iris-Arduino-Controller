#define LED_PIN 13
#define SWITCH_INPUT A0
#define SPEAKER_PIN 3

#define ON 1
#define OFF 0

bool switchPressed() {
    return digitalRead(SWITCH_INPUT) == 0;
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
