#include <DRV8835MotorShield.h>

const int VR1A = 26;  
const int VR1B = 27;  
const int VR1C = 28;  
const int VR1D = 29;  


DRV8835MotorShield motors(2,3,4,5);

float motorDamp = 0.3f; // dampening motor volt
int deadZone = 25; // between -deadZone and +deadZone -> no motor movement

void setup() {
}

void loop() {
  int poti1 = analogRead(VR1A);
  int motor1 = map(poti1, 0, 1023, -255,255);

  if(abs(motor1) > 25){
    motors.setM1Speed(motor1 * motorDamp);
  } else {
    motors.setM1Speed(0);
  }

  delay(2);
}
