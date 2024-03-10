#ifndef sensors_ir_h
#define sensors_ir_h

#define SENSOR_THRESHOLD 220

void SENSORS_Process(void);

typedef enum
{
    SENSORS_READY,
    SENSORS_DETECTED,
}sensors_state_t;
#endif