#include <Servo.h>

//Pin defines
#define REED_SW_DETECT_HAND_PIN 6
#define REED_SW_DETECT_MOVE_PIN 7
#define RELAY 8
#define SERVO 9

#define SERWO_STOP_VALUE 93
#define SERWO_GO_VALUE 91
#define SERWO_START_STOP_DELAY 20

#define DEBUG_SENS_DISP_TIME 1500
#define CONFIRMATION_TIME 5000

//Functions
void ServoProcess(void);

//Typedefs
typedef enum
{
  SERWO_STOP,
  SERWO_GO
} serwo_state_t;

typedef enum {
  PUZZLE_WAIT_FOR_SENS,
  PUZZLE_DOOR_OPEN
} puzzle_state_t;

typedef enum
{
  LAST_REED_SW_WAS_HIGH,
  LAST_REED_SW_WAS_LOW
}reed_sw_state_t;

//Variables
//Servo
Servo myservo;
serwo_state_t serwo_state = SERWO_STOP;
//Puzzle
puzzle_state_t puzzle_state = PUZZLE_WAIT_FOR_SENS;
reed_sw_state_t reed_sw_state = LAST_REED_SW_WAS_HIGH;
uint8_t move = 0;
uint8_t solution_flag = 0;

//Timers
unsigned long debug_tick_sens = 0;
unsigned long debug_tick_solution = 0;
unsigned long tick = 0;

void setup() {
  pinMode(REED_SW_DETECT_HAND_PIN, INPUT_PULLUP);
  pinMode(REED_SW_DETECT_MOVE_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);
  myservo.attach(SERVO);
  Serial.begin(9600);
}

void loop() {
  ServoProcess();
  uint8_t sensor_value = digitalRead(REED_SW_DETECT_MOVE_PIN);
  uint8_t reed_value = digitalRead(REED_SW_DETECT_HAND_PIN);

  switch (puzzle_state) {
    case PUZZLE_WAIT_FOR_SENS:
      if (sensor_value == LOW) {
        move = 1;
      }
      else
      {
        move = 0;
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

    case PUZZLE_DOOR_OPEN:
      digitalWrite(RELAY, LOW);
      delay(1000);
      digitalWrite(RELAY, HIGH);
      myservo.write(SERWO_GO_VALUE);
      delay(4500);
      puzzle_state = PUZZLE_WAIT_FOR_SENS;
      break;
  }
}

void ServoProcess(void)
{
  static unsigned long tick_servo = millis();
  if(move)
  {
    switch (serwo_state) {
    case SERWO_STOP:
    if(millis() - tick_servo > SERWO_START_STOP_DELAY)
    {
      myservo.write(SERWO_STOP_VALUE);
      tick_servo = millis();
      serwo_state = SERWO_GO;
    }

    break;

    case SERWO_GO:
      if(millis() - tick_servo > SERWO_START_STOP_DELAY)
      {
        myservo.write(SERWO_GO_VALUE);
        tick_servo = millis();
        serwo_state = SERWO_STOP;
      }
    break;
    }
  }
  else
  {
    myservo.write(SERWO_STOP_VALUE);
  }
}
