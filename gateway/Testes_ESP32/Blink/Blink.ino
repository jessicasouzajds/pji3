#define touchPin T0

int led = 2;
int valor_touch = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Teste - Sensores touch capacitivos!");
  pinMode(led, OUTPUT);  
  digitalWrite(led, LOW);
}

void loop() {
  valor_touch = touchRead(touchPin);
  Serial.print("valor do sensor: ");
  Serial.println(valor_touch);
  if(valor_touch < 70) digitalWrite(led, HIGH); 
  else digitalWrite(led, LOW);
  delay(1000); 
}
