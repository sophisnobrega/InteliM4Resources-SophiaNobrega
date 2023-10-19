void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);

}

void loop() {
  //s
  delay(1000);
  digitalWrite(13, HIGH);
  delay(300);
  digitalWrite(13, LOW);

  delay(400);
  digitalWrite(13, HIGH);
  delay(300);
  digitalWrite(13, LOW);

  delay(400);
  digitalWrite(13, HIGH);
  delay(300);
  digitalWrite(13, LOW);

  //o
  delay(400);
  digitalWrite(13, HIGH);
  delay(800);
  digitalWrite(13, LOW);

  delay(400);
  digitalWrite(13, HIGH);
  delay(800);
  digitalWrite(13, LOW);

  delay(400);
  digitalWrite(13, HIGH);
  delay(800);
  digitalWrite(13, LOW);

  //s
  delay(400);
  digitalWrite(13, HIGH);
  delay(300);
  digitalWrite(13, LOW);

  delay(400);
  digitalWrite(13, HIGH);
  delay(300);
  digitalWrite(13, LOW);

  delay(400);
  digitalWrite(13, HIGH);
  delay(300);
  digitalWrite(13, LOW);

}
