
void setup() { // código de inicialización (se ejecuta una vez al principio)
    pinMode(13, OUTPUT);
}

void loop() { // código del programa principal (se ejecuta repetidamente)
    digitalWrite(13, HIGH); // encender el LED (voltaje a HIGH)
    delay(1000); // esperar encendido durante 1 segundo (1000 mseg)
    digitalWrite(13, LOW); // apagar el LED (voltaje a LOW)
    delay(100); // esperar apagado durante 100 milisegundos
}
