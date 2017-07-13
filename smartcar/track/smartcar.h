#include <wiringPi.h>
#include <sys/time.h>



#define ENABLE_A 0
#define ENABLE_B 1

#define LEFT_SIGNAL_1 21
#define LEFT_SIGNAL_2 22
#define RIGHT_SIGNAL_1 24
#define RIGHT_SIGNAL_2 23


#define LEFT_DETECT_SIGNAL 27
#define RIGHT_DETECT_SIGNAL 28

void setup();

void data_write(int data[4]);


void go_ahead();
void turn_left();
void stop();
void turn_right();
