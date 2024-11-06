#include <DHT.h>
#include <Servo.h>
#include <ArduinoJson.h>

#define ledR 13
#define ledY 12
#define ledG 11
#define dhtpin 2
#define dhttype DHT22
#define trigger 7
#define echo 8
#define servopin 9
#define ldrpin A0

int dist = 0;
int ldrvalor = 0;

DHT dht(dhtpin, dhttype);
Servo myservo;

void setup() {
  myservo.attach(servopin);
  dht.begin();

  pinMode(ledR, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(servopin, OUTPUT);
  pinMode(ldrpin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  dist = pulseIn(echo, HIGH);

  int temp = dht.readTemperature();
  int umi = dht.readHumidity();

  ldrvalor = analogRead(ldrpin);

  Serial.println("------------------------------------------------------------------------------------------");
  Serial.print("Distância: ");
  Serial.print(dist);
  Serial.print(" cm  |  ");
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print(" °C  |  ");
  Serial.print("Umidade: ");
  Serial.print(umi);
  Serial.print(" %  |  ");
  Serial.print("Luminosidade: ");
  Serial.print(ldrvalor);
  Serial.println(" (LDR)");

  Serial.println("------------------------------------------------------------------------------------------");

  if (ldrvalor < 300) {
    digitalWrite(ledR, LOW);
    digitalWrite(ledY, LOW);
    digitalWrite(ledG, HIGH);

  } else if (ldrvalor < 700) {
    digitalWrite(ledR, LOW);
    digitalWrite(ledY, HIGH);
    digitalWrite(ledG, LOW);

  } else {
    digitalWrite(ledR, HIGH);
    digitalWrite(ledY, LOW);
    digitalWrite(ledG, LOW);
  }

  if (temp > 50) {
    myservo.write(100);
  } else if (temp > 35) {
    myservo.write(90);
  } else {
    myservo.write(0);
  }

  delay(500);
}
