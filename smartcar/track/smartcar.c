#include <wiringPi.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include "smartcar.h"


void setup()
{
	if(wiringPiSetup() == -1)
	{
		puts("an error ocurred when setup");
		exit(-1);
	}
	pinMode(ENABLE_A,OUTPUT);
	pinMode(ENABLE_B,OUTPUT);
	pinMode(LEFT_SIGNAL_1,OUTPUT);
	pinMode(LEFT_SIGNAL_2,OUTPUT);
	pinMode(RIGHT_SIGNAL_1,OUTPUT);
	pinMode(RIGHT_SIGNAL_2,OUTPUT);

	pinMode(LEFT_DETECT_SIGNAL, INPUT);
	pinMode(RIGHT_DETECT_SIGNAL, INPUT);


}
void data_write(int data[4])
{
	digitalWrite(ENABLE_A,1);
	digitalWrite(ENABLE_B,1);
	digitalWrite(LEFT_SIGNAL_1,data[0]);
	digitalWrite(LEFT_SIGNAL_2,data[1]);
	digitalWrite(RIGHT_SIGNAL_1,data[2]);
	digitalWrite(RIGHT_SIGNAL_2,data[3]);
}
void go_ahead( )
{
	puts("go ahead");
	int data[] = {1,0,1,0};
	data_write(data);	
	//delayMicroSeconds(1e5);
	delayMicroseconds(3e4);
	stop();	
	delayMicroseconds(5e4);

}

void stop()
{
	int data[] = {0,0,0,0};
	data_write(data);

}


void turn_left()
{
	puts("turn left");
	int data[] = {0,1,1,0};
	data_write(data);
	delayMicroseconds(1e4);
	stop();
	delayMicroseconds(1e4);
}

void turn_right()
{
	puts("turn right");
	int data[] = {1,0,0,1};
	data_write(data);
	delayMicroseconds(1e4);
	stop();
	delayMicroseconds(1e4);		

}
int main(int argc, char  * argv[])
{

	//int data[] = {1,0,1,0};
	//data_write(data);
	
	setup();	
	while(1)
	{
		printf("%d  %d\n",digitalRead(LEFT_DETECT_SIGNAL), digitalRead(RIGHT_DETECT_SIGNAL));
		while(digitalRead(LEFT_DETECT_SIGNAL) && digitalRead(RIGHT_DETECT_SIGNAL))
		{
			go_ahead();
		}

		
		while(!digitalRead(LEFT_DETECT_SIGNAL))
		{
			turn_left();
		}
		while(!digitalRead(RIGHT_DETECT_SIGNAL))
		{
			turn_right();
		}

	
	
	
	
	}

	puts("test\n");
	return 0;
}
	





