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

int dcSpeed = 512;

void setup() {
  pinMode(dcStepperToggle1Pin, INPUT);
}

void loop() {
  bool toggle1 = digitalRead(dcStepperToggle1Pin);

  int poti1 = analogRead(VR1A);

  if (toggle1) {
    // 0= stepper, 1=dc motor

    int motor1 = map(poti1, 0, 1023, -dcSpeed, dcSpeed);

    if (abs(motor1) > 25) {
      motors.setM1Speed(motor1 * motorDamp);
    } else {
      motors.setM1Speed(0);
    }
  } else {
    //motors.setM1Speed(0);

      stepperAcc.setMaxSpeed(1200);
      stepperAcc.setSpeed(1200);	
      stepperAcc.runSpeed();
  }

  delay(20);
}
