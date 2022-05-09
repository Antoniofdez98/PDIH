#define BUTTON_PIN 7
#define LED_PIN0 13
#define LED_PIN1 12
#define LED_PIN2 11

void setup() { // código de inicialización (se ejecuta una vez al principio)
 pinMode(LED_PIN0, OUTPUT);
 pinMode(LED_PIN1, OUTPUT);
 pinMode(LED_PIN2, OUTPUT);
 pinMode(BUTTON_PIN, INPUT);
}
void loop() { // código del programa principal (se ejecuta repetidamente)

  if(digitalRead(BUTTON_PIN) == HIGH) {
    digitalWrite(LED_PIN0, LOW);
    digitalWrite(LED_PIN1, HIGH);
    digitalWrite(LED_PIN2, HIGH);
  }else{
    digitalWrite(LED_PIN0, HIGH);
    digitalWrite(LED_PIN1, LOW);
    digitalWrite(LED_PIN2, LOW);
    delay(3000);
  }

 
}
