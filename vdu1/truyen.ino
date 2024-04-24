#include <IRremote.h>
IRsend irsend(3);
const int trigPin = 5;
const int echoPin = 6;
long duration;
int distance;
void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance Measured=");
  Serial.print(distance);
  Serial.println("cm");
  if (distance < 10) {
    irsend.sendRC5(0x0, 8);
    delay(200);
  } else if (distance > 10) {
    irsend.sendRC5(0x1, 8);
    delay(200);
  }
}
