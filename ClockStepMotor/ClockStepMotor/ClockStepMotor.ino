#define REED_SW_SENSOR 7
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define RELAY 12
#define REED_SW 2

#define SOLUTION_MINUTE 30
#define CONFIRMATION_TIME 5000
#define DEBUG_SENS_DISP_TIME 1500
#define DEBUG_ANGLE_DISP_TIME 25
#define DEBUG_SOL_DISP_TIME 500

typedef enum {
  PUZZLE_WAIT_FOR_SENS,
  PUZZLE_SENS_DETECTED,
  PUZZLE_DOOR_OPEN
} puzzle_state_t;

typedef enum
{
  LAST_REED_SW_WAS_HIGH,
  LAST_REED_SW_WAS_LOW
}reed_sw_state_t;

const int stepSequence[8][4] = {
  { 1, 0, 0, 0 },
  { 1, 1, 0, 0 },
  { 0, 1, 0, 0 },
  { 0, 1, 1, 0 },
  { 0, 0, 1, 0 },
  { 0, 0, 1, 1 },
  { 0, 0, 0, 1 },
  { 1, 0, 0, 1 }
};

const int stepsPerRevolution = 4076;
int currentStep = 0;
float currentAngle = 0;
float targetAngle = 0;
unsigned long tick = 0;
unsigned long debug_tick_sens = 0;
unsigned long debug_tick_angle = 0;
unsigned long debug_tick_solution = 0;

puzzle_state_t puzzle_state = PUZZLE_WAIT_FOR_SENS;
reed_sw_state_t reed_sw_state = LAST_REED_SW_WAS_HIGH;

uint8_t solution_flag = 0;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(REED_SW, INPUT_PULLUP);
  pinMode(REED_SW_SENSOR, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Clock puzzle init");
  digitalWrite(RELAY, HIGH);
}

void loop() {
  uint8_t sensor_value = digitalRead(REED_SW_SENSOR);
  uint8_t reed_value = digitalRead(REED_SW);

  switch (puzzle_state) {
    case PUZZLE_WAIT_FOR_SENS:
      if (sensor_value == LOW) {
        puzzle_state = PUZZLE_SENS_DETECTED;
      }

      if (millis() - debug_tick_sens >= DEBUG_SENS_DISP_TIME) {
        Serial.print("Sensor value: ");
        Serial.println(sensor_value);
        debug_tick_sens = millis();
      }

      if(reed_value == HIGH) //no hand clock detected
      {
        digitalWrite(LED_BUILTIN, LOW);
        reed_sw_state == LAST_REED_SW_WAS_HIGH;
        if(solution_flag)
        {
          solution_flag = 0;
          Serial.println("Hand was removed from good position");
        }
        
      }
      else if((reed_value == LOW && reed_sw_state == LAST_REED_SW_WAS_HIGH) && solution_flag == 0) //hand clock detected
      {
        Serial.println("Clock hand good position start counting");
        digitalWrite(LED_BUILTIN, HIGH);
        debug_tick_solution = millis();
        solution_flag = 1;
      }

      if((millis() - debug_tick_solution > CONFIRMATION_TIME) && solution_flag)
      {
        solution_flag = 0;
        puzzle_state = PUZZLE_DOOR_OPEN;
      }
      break;

    case PUZZLE_SENS_DETECTED:
      moveToAngleForward(targetAngle++);
      if (targetAngle >= 360)
        targetAngle = 0;

      puzzle_state = PUZZLE_WAIT_FOR_SENS;
      tick = millis();
      break;

    case PUZZLE_DOOR_OPEN:
      digitalWrite(RELAY, LOW);
      delay(1000);
      digitalWrite(RELAY, HIGH);

      targetAngle = targetAngle - 50;
      moveToAngleForward(targetAngle);

      puzzle_state = PUZZLE_WAIT_FOR_SENS;
      break;
  }
}

void setStep(int stepIndex) {
  digitalWrite(IN1, stepSequence[stepIndex][0]);
  digitalWrite(IN2, stepSequence[stepIndex][1]);
  digitalWrite(IN3, stepSequence[stepIndex][2]);
  digitalWrite(IN4, stepSequence[stepIndex][3]);
}

void moveStepsReverse(int steps) {
  for (int i = 0; i < steps; i++) {
    currentStep = (currentStep - 1 + 8) % 8;  // Decrement to move backward
    setStep(currentStep);
    delay(4);
  }
}

void moveToAngleForward(float targetAngle) {
  float targetSteps = (targetAngle / 360.0) * stepsPerRevolution;
  float currentSteps = (currentAngle / 360.0) * stepsPerRevolution;

  int stepsToMove = (int)(targetSteps - currentSteps + stepsPerRevolution) % stepsPerRevolution;

  //moveStepsForward(stepsToMove);
  moveStepsReverse(stepsToMove);
  currentAngle = targetAngle;
}