#include <Stepper.h>
#include <IRremote.h>

const int stepsPerRevolution = 2024; // Số bước mỗi vòng quay
const int rolePerMinute = map(45, 0, 360, 0, 2048);
Stepper myStepper(stepsPerRevolution, 3, 6, 5, 7); //lắp liên tiếp in1-4: 3, 5, 6, 7
IRrecv irrecv(11); 
decode_results results;

void setup() {
  myStepper.setSpeed(rolePerMinute);
  irrecv.enableIRIn(); // Bắt đầu nhận tín hiệu hồng ngoại
  Serial.begin(9600);
}

void rotateClockwise() {
  myStepper.setSpeed(15);
  myStepper.step(rolePerMinute);
}

void rotateCounterclockwise() {
  myStepper.setSpeed(15);
  myStepper.step(-rolePerMinute);
}

void loop() {
  if (irrecv.decode(&results))  // nếu nhận được tín hiệu
  {
    uint32_t IRcode = results.value;
//    Serial.println(IRcode, HEX);//in ra giá trị nhận được
    String keyBuf = translateIR(IRcode);
    if (keyBuf == "counter clockwise") {
      rotateCounterclockwise();
    } else if(keyBuf == "clockwise") {
      rotateClockwise();
    }
    irrecv.resume(); // nhận giá trị tiếp theo
  }

  delay(100);

}
String translateIR(uint32_t code) {
  String keyBuff = "";
  switch (code) {
    case 0xB7C75DCE:
      keyBuff = "counter clockwise";
      break;
    case 0xB8C75F63:
      keyBuff = "clockwise";
      break;
    default:
      return keyBuff;
  }
  return keyBuff;
}
