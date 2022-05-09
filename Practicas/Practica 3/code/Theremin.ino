
int sensorValue;
int sensorLow  = 1023;
int sensorHigh = 0;
const int ledPin = 13;
int lightPin = 0;
int latchPin = 11;
int clockPin = 9;
int dataPin = 12;
int leds = 0;

voit setup(){

    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(ledPin, OUTPUT);

    digitalWrite(ledPin, HIGH);

    while(millis() < 5000){
        sensorValue = analogRead(A0);
        if(sensorValue > sensorHigh){
            sensorHigh = sensorValue;
        }
        if(sensorValue < sensorLow){
            sensorLow = sensorValue;
        }
    }

    digitalWrite(ledPin, LOW);

}

void updateShiftRegister(){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, leds);
    digitalWrite(latchPin, HIGH);
}

void loop(){
    int reading = analogRead(lightPin);
    int numLEDSLit = reading / 57;
    if(numLEDSLit > 8) numLEDSLit = 8;
    leds = 0;
    for(int i = 0; i < numLEDSLit; i++){
        leds = leds + (1 << i);
    }
    updateShiftRegister();

    sensorValue = analogRead(A0);

    int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 4000);

    tone(8, pitch, 20);

    delay(10);
}
