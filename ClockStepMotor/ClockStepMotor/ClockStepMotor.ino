#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

#define SENSOR_THRESHOLD 20

const int stepSequence[8][4] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

const int stepsPerRevolution = 4096; 
int currentStep = 0;                
float currentAngle = 0;             
float targetAngle = 0;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  Serial.println("Stepper Motor Angle Control Ready");
}

void loop() {
  // if (Serial.available() > 0) {
  //   String input = Serial.readStringUntil('\n');
  //   float targetAngle = input.toFloat();

  //   moveToAngleForward(targetAngle);

  //   Serial.print("Moved to angle: ");
  //   Serial.println(currentAngle);
  // }
  uint8_t sensor_value = analogRead(A0);

  if(sensor_value < SENSOR_THRESHOLD)
  {
    moveToAngleForward(targetAngle++);
    if(targetAngle >= 360)
    {
      targetAngle = 0;
    }
  }
}

void setStep(int stepIndex) {
  digitalWrite(IN1, stepSequence[stepIndex][0]);
  digitalWrite(IN2, stepSequence[stepIndex][1]);
  digitalWrite(IN3, stepSequence[stepIndex][2]);
  digitalWrite(IN4, stepSequence[stepIndex][3]);
}


void moveStepsForward(int steps) {
  for (int i = 0; i < steps; i++) {
    currentStep = (currentStep + 1) % 8; 
    setStep(currentStep); 
    delay(2); 
  }
}

void moveToAngleForward(float targetAngle) {
  float targetSteps = (targetAngle / 360.0) * stepsPerRevolution; 
  float currentSteps = (currentAngle / 360.0) * stepsPerRevolution; 

  int stepsToMove = (int)(targetSteps - currentSteps + stepsPerRevolution) % stepsPerRevolution;

  moveStepsForward(stepsToMove);

  currentAngle = targetAngle;
}