#include <DRV8835MotorShield.h>
#include <AccelStepper.h>

#define STEPPER_STEPS 1200
#define STEPPER_STEPS_PER_REVOLUTION 200

const int VR1A = 26;
const int VR1B = 27;
const int VR1C = 28;
const int VR1D = 29;

const int dcStepperToggle1Pin = 0;
const int dcStepperToggle2Pin = 1;


DRV8835MotorShield motors(2, 3, 4, 5);
AccelStepper stepperAcc(AccelStepper::FULL4WIRE, 2, 3, 4, 5);

float motorDamp = 0.3f;  // dampening motor volt
int deadZone = 25;       // between -deadZone and +deadZone -> no motor movement

void setup() {
  pinMode(dcStepperToggle1Pin, INPUT);
}

void loop() {
  bool toggle1 = digitalRead(dcStepperToggle1Pin);

  int poti1 = analogRead(VR1A);

  if (toggle1) {
    // 0= stepper, 1=dc motor

    int motor1 = map(poti1, 0, 1023, -255, 255);

    if (abs(motor1) > 25) {
      motors.setM1Speed(motor1 * motorDamp);
    } else {
      motors.setM1Speed(0);
    }
  } else {
    //motors.setM1Speed(0);

    if (stepperAcc.distanceToGo() == 0) {
      // Random change to speed, position and acceleration
      // Make sure we dont get 0 speed or accelerations
      delay(1000);
      stepperAcc.moveTo(rand() % 200);
      stepperAcc.setMaxSpeed((rand() % 200) + 1);
      stepperAcc.setAcceleration((rand() % 200) + 1);
    }
    stepperAcc.run();
  }

  delay(20);
}
