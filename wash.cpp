// This #include statement was automatically added by the Particle IDE.
#include "SparkFunLSM9DS1/SparkFunLSM9DS1.h"
#include "math.h"

#define LOOP_INTERVAL           3000
#define EMAIL_INTERVAL          15000

#define TUCSON_MAGNETIC_PULL    9.59

#define AWAITING_START_STATE 1
#define WASHING_STATE        2
#define AWAITING_DOOR_STATE  3

#define DEBUG_STATE 1


LSM9DS1 accel;
int state;

/* Setup once device has powered on */
void setup()
{
    Serial.begin(115200);

    accel.settings.device.commInterface = IMU_MODE_I2C;
    accel.settings.device.agAddress     = 0x6B;
    accel.settings.device.mAddress      = 0x1E;

    state = AWAITING_START_STATE;

    while (1) {}
}

/* Main Loop */
void loop()
{
    if (state == AWAITING_START_STATE)
    {
        if (hasStarted() == 1)
        {
            state = WASHING_STATE;
        }
    }
    else if (state == WASHING_STATE)
    {
        if (hasEnded() == 1)
        {
            state = AWAITING_DOOR_STATE;
        }

    }
    else if (state == AWAITING_DOOR_STATE)
    {   
        if (hasDoorOpened() == 1)
        {
            // DO STUFF TO DELAY
            state = AWAITING_START_STATE;
        }
        else
        {
            // NOTE: WE CAN'T DELAY HERE, HAVE TO USE A TIME CHECK, JUST HERE FOR PLACEHOLDER!
            delay(EMAIL_INTERVAL);
            sendEvent();
        }
    }

    if (DEBUG_STATE == 1)
    {
        debugOutput();
    }

    delay(LOOP_INTERVAL);
}

/* State Condition Checker Functions that act as Booleans */
int hasStarted()
{
    return 0;
}

int hasEnded()
{
    return 0; 
}

int hasDoorOpened()
{
    return 0;
}

/* Debug Serial Printing */
void debugOutput()
{
    accel.readAccel();

    char debugBuffer[512];
    bzero(debugBuffer, 512);

    sprintf(debugBuffer, "Time: %lu\nAx: %d | Ay: %d | Az: %d\n", Time.now(),  accel.ax, accel.ay, accel.az);

    Serial.print("--------------------\n");
    Serial.print(debugBuffer);
    Serial.print("--------------------\n");
}

/* Publish Event to E-Mail Customer */
void sendEvent()
{
    /* Publish Code To Use Later */
    // char bufferX[100];
    // char bufferY[100];
    // char bufferZ[100];
    // char bufferS[100];
    // snprintf(bufferX, sizeof(char) * 32, "%d", imu.ax);
    // snprintf(bufferY, sizeof(char) * 32, "%d", imu.ay);
    // snprintf(bufferZ, sizeof(char) * 32, "%d", imu.az);
    // snprintf(bufferS, sizeof(char) * 32, "%d", (imu.ax + imu.ay + imu.az));
    // snprintf(&buffer[32], sizeof(char) * 32, "%d", imu.ay);
    // snprintf(&buffer[65], sizeof(char) * 32, "%d", imu.az);
    // Spark.publish("Ax", bufferX, 60, PRIVATE);
    // Spark.publish("Ay", bufferY, 60, PRIVATE);
    // Spark.publish("Az", bufferZ, 60, PRIVATE);
    // Spark.publish("SumA", bufferS, 60, PRIVATE);
}