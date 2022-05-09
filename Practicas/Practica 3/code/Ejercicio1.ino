#define LED_PIN0 13
#define LED_PIN1 12
#define LED_PIN2 11

void setup()
{
  pinMode(LED_PIN0, OUTPUT);
    pinMode(LED_PIN1, OUTPUT);
    pinMode(LED_PIN2, OUTPUT);
}

void loop()
{
    digitalWrite(LED_PIN0, HIGH);
    delay(1500);
  digitalWrite(LED_PIN0, LOW);
    digitalWrite(LED_PIN1, HIGH);
    delay(1500);
  digitalWrite(LED_PIN1, LOW);
    digitalWrite(LED_PIN2, HIGH);
    delay(1500);
    digitalWrite(LED_PIN2, LOW);
}
