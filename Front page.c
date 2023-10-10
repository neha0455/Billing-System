#include<graphics.h>
#include<conio.h>
#include<time.h>
int main(){
	//setting x,y coordinates to the center
	int x_coord=50;
	int y_coord=150;
	unsigned int x_hours=0;
	unsigned int x_minutes=0;
	unsigned int x_seconds=0;
	unsigned int x_milliseconds=0;
	unsigned int totaltime=0,count_down_time_in_secs=0,time_left=0;
	clock_t x_startTime,x_countTime;
	int gd=DETECT, gm;
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
	count_down_time_in_secs=30;  
	x_startTime=clock();  // start clock
    time_left=count_down_time_in_secs-x_seconds;
	
	//setting background color to red
	setbkcolor(RED);
	//setting text style
	settextstyle(8,0,4);
	//print text
	outtextxy(x_coord,y_coord,"SUPERMARKET BILLING SYSTEM");
	settextstyle(3,0,2);
	y_coord+=50;
	x_coord+=50;
	outtextxy(x_coord,y_coord,"by Dikshita and Neha");
	y_coord+=30;
	x_coord=0;
	while (time_left>0) 
	{
		x_countTime=clock();
		x_milliseconds=x_countTime-x_startTime;
		x_seconds=(x_milliseconds/(CLOCKS_PER_SEC))-(x_minutes*60);
		x_minutes=(x_milliseconds/(CLOCKS_PER_SEC))/60;
		x_hours=x_minutes/60;
		
		time_left=count_down_time_in_secs-x_seconds;
	}
	closegraph();
	return 0;
	}