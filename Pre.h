# include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <math.h>
#include <glut.h>
#define MAG_F 100000000000 ///the force press the robot when attached N
#define DELTA_T 0.001///the simulation time interval s
#define NUM 1///the # of the robot we run the simulation
#define RR 0.01/// the radius of robot unit :m 
#define RT 1/// the radius of the table unit : m
#define E 10000 /// the parameter of the force between the robot when collision happens
#define MASS 0.05/// the mass of the robot kg
#define Pi 3.1415926535898/// 
#define MIU 0.000000000003///responding to the struct table.miu
#define OMEGA 2///the angel velocity rad
#define M_R 0.05///the radius of the motion m
#define HEIGHT 700///the out put window height size in pixels
#define WIDTH 700///the out put window width size in pixels
#define _x(x, y, theta) cos((theta)) * (x) + sin((theta)) * (y)
#define _y(x, y, theta) -sin((theta)) * (x) + cos((theta)) * (y)
#define ROTATION 0/// control the rotation method 
#define CLINE 1/// Draw the communication line between robots
#define MAX_RANGE 0.1///the communication limit distance.
#define C_V 50
 char c_v; ///the velocity of communication
long long Time; /// t= Time * Delta_T
float XX[10];
float YY[10];

typedef struct connect_line
{
	int from, to;///the visualized connection 
	float xf, yf;
	float xt, yt;
	float length;
	char is_show;
}connect_line;
///*******************************REMEBER : the robot can only "see" the content of the sensor************************************///
typedef struct dis
{
	int to; ///the dis sensor on the robot, relative distance and angel between 2 robots.
	float dis;
	float angel;
	char flag;
}dis; 
typedef struct sensor
{
	double ax, ay; ///the content of the sensor, ax and ay is the value of the accelerometer
	dis d_a[NUM];
}sensor;
///*******************************REMEBER : the robot can only "see" the content of the sensor************************************///
typedef struct message
{
	int num;///the #of the msg(who send the msg)
	float ts;
	float angel;
	char flag;/// the content of the talking
}msg;
typedef struct table 
{
	double x, y, vx, vy, w, miu, r;///position velocity ; miu is the paramter of friction: f = MIU * N;
	double ax, ay, alpha;///acceleration
	double m_r; ///the radius of the motion
	float tt;/// simulation time % the T(1/f)
	int rb_num, line_num;///the number of the robot which is on the table'
	connect_line cl[NUM * (NUM - 1) / 2];///the array of the lines between the robots
}table;
typedef struct pos_rf
{
	float x;///the x and y in robot computation world(same frame without rotation from the tabel frame, but the origin is the robot initial position (0,0))
	float y;
	float rotate;///the rotation of robot relative to the table.
	float omega;
	float rotate_initial; /// the initial rotation angel of the robot relative to the table
	float v_angel;
}pos_rf; 

typedef struct force
{
	double fx, fy;
}force;
typedef struct robot
{
	double m; ///mass
	double r; ///the radius of the robot
	double angel; ///This is angel is relative to the table AKA the world coordinate, and robot don't know it
	force ft;///the force between robot and the table
	force fr;///the force between robots
	msg buffer[NUM]; ///the buffer which store the msg from other robots
	msg pub;///the buffer for send msg
	sensor s;///the acclereter
	double x, y, vx, vy, w, ax, ay, alpha; ///velocity acceleration and the position of the robot
	char is_on;/// whether the robot is attached or detached 
	char is_show;///whether the robot is on the table or not
	char led;///the corlor of the robot
	float m_o; ///the angel of motition iin the robot coordinate
	float time;
	float time_; /// the starting time of robot detach
	char c_flag;/// whether be hitted or not when detached. 1 is hitted, 0 is safe
	float is_cra;
	pos_rf pr;
}robot;

extern void initial(table *, robot **);
extern void collision(robot *, int, int, robot **, table *);
extern void update(robot **, table *);
extern void display(robot **, table*);
extern void On_Recieve_Command(char *, robot **);
extern void ct(robot*, table*);
extern void _display(robot **, table*);
//extern void display_s(robot **, table*)