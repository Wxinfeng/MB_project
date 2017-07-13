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
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO,INPUT);

}

float measure_distance()
{
	/*struct timeval t1,t2;
	digitalWrite(TRIG, LOW);
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(1e2);
	gettimeofday(&t1,NULL);
	digitalWrite(TRIG, LOW);

	while(!digitalRead(ECHO));
	while(digitalRead(ECHO));
	gettimeofday(&t2,NULL);


	return 340*(((t2.tv_usec + t2.tv_sec*1e6)  - (t1.tv_sec + t1.tv_usec*1e6))/1e6)*100/2;
*/

struct timeval tv1;
	struct timeval tv2;
	long start, stop;
	float dis;

	digitalWrite(TRIG, LOW);
	delayMicroseconds(2);

	digitalWrite(TRIG, HIGH);
	delayMicroseconds(10);	  
	digitalWrite(TRIG, LOW);
										
	while(!(digitalRead(ECHO) == 1));
	//get the time of now
	gettimeofday(&tv1, NULL);		   

	while(!(digitalRead(ECHO) == 0));
	//get the time of now
	gettimeofday(&tv2, NULL);		   

	//the time(us)
	start = tv1.tv_sec * 1000000 + tv1.tv_usec;   
	stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;

	//the distance
	dis = (float)(stop - start) / 1000000 * 34000 / 2;  

	return dis;

}



BOOL has_obstacle()
{
	if(measure_distance() < 15)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

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
	delayMicroseconds(1e5);
	stop();	
	//delayMicroseconds(5e4);

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
	delayMicroseconds(1e5);
	stop();
//	delayMicroseconds(1e4);
}

void turn_right()
{
	puts("turn right");
	int data[] = {1,0,0,1};
	data_write(data);
	delayMicroseconds(1e5);
	stop();
//	delayMicroseconds(1e4);		

}
int main(int argc, char  * argv[])
{

	//int data[] = {1,0,1,0};
	//data_write(data);
	
	setup();	
	while(1)
	{
		printf("%d  %d %2.4f\n",digitalRead(LEFT_DETECT_SIGNAL), digitalRead(RIGHT_DETECT_SIGNAL) , measure_distance());
		while(!has_obstacle())
		{
		printf("%d  %d %2.4f\n",digitalRead(LEFT_DETECT_SIGNAL), digitalRead(RIGHT_DETECT_SIGNAL) , measure_distance());
			go_ahead();
		}

		
	//	while(!has_obstacle())
		{
			turn_left();
		}
	
	}

	puts("test\n");
	return 0;
}
	





