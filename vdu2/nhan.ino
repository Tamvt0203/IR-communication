#include <IRremote.h>

IRrecv irrecv(11); 
decode_results results;


int ena = 9;
int in1 = 8;
int in2 = 7;
int speed = 150;
String keyBuf = "off";
void setup() {
  irrecv.enableIRIn(); // Bắt đầu nhận tín hiệu hồng ngoại
  Serial.begin(9600);

  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results))  // nếu nhận được tín hiệu
  {
    uint32_t IRcode = results.value;
    Serial.println(IRcode, HEX);
    keyBuf = translateIR(IRcode);
    Serial.println(keyBuf);
    irrecv.resume(); // nhận giá trị tiếp theo
  }
  if (keyBuf == "max") {
    setSpeed(2);
    directionControl();
    delay(1000);
    continuousRotation();
  } else if (keyBuf == "medium") {
    setSpeed(1);
    directionControl();
    delay(1000);
    continuousRotation();
  } else if (keyBuf == "off") {
    setSpeed(0);
    directionControl();
    delay(1000);
    continuousRotation();
  }
}
String translateIR(uint32_t code) {
  String keyBuff = "";
  switch (code) {
    case 0xB7C75DCE:
      keyBuff = "max";
      break;
    case 0xB8C75F63:
      keyBuff = "medium";
      break;
    case 0x558B9626:
      keyBuff = "off";
      break;
    default:
      return keyBuff;
  }
  return keyBuff;
}
void directionControl() {
  analogWrite(ena, speed);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(10);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(10);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(10);
}

void continuousRotation() {
  analogWrite(ena, speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void setSpeed(int mode) {
  if (mode == 0) {
    speed = 0;
  }
  else if (mode == 1) {
    speed = 150;
  }
  else if (mode == 2) {
    speed = 255;
  }
  else {
    speed = 0;
  }
}
