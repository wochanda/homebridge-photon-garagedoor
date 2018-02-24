int lastOpenSensor = 0;
int openSensor = 0;

int relayPin = D3;
int doorOpenSensorPin = D0;


void setup() {
    Particle.function("openClose", openClose);
    Particle.variable("openSensor", &openSensor, INT);
    pinMode(relayPin, OUTPUT);
    pinMode(doorOpenSensorPin, INPUT);

    publishDoorState();
}



void loop() {
    getDoorSensor();

    if (openSensor != lastOpenSensor) {
        publishDoorState();
        lastOpenSensor = openSensor;
    }

    delay(1000);
}

void publishDoorState() {
    if (openSensor == 1 ) {
        Particle.publish("doorState", "door-opened", 1);
    }
    else {
        Particle.publish("doorState", "door-closed", 1);
    }
}

int openClose(String value) {
    if (value == "open") {
        toggle();
        return 1;
    }
    else if (value == "close") {
        toggle();
        return 1;
    }

    return 0;
}

void toggle() {
    digitalWrite(relayPin, HIGH);
    delay(1000);
    digitalWrite(relayPin, LOW);
}

void getDoorSensor() {
   openSensor = digitalRead(doorOpenSensorPin);
}
