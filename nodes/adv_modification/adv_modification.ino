void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
//
//  sendCommand("AT");
//  sendCommand("AT+ROLE0");
//  sendCommand("AT+UUID0xFFE0");
//  sendCommand("AT+CHAR0xFFE1");
//  sendCommand("AT+NAMEDANIEL");
}

void writeSerialToBLE(int value) {
  Serial1.println(value);
}

void writeToBLE(char value) {
  Serial.print("Writing hex :");
  Serial.println(value, HEX);
  Serial1.write(value);
}

char j = 0;
void loop() {
  writeToBLE(j);
  j += 1;
  delay(1000);
}
