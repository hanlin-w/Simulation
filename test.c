#include "Pre.h"
#include <stdio.h>
table t;
robot *ra[NUM];
int flag = 0;
void mydisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport( 0, 0, WIDTH, HEIGHT ); 
	display(ra, &t);
	glViewport(WIDTH, 0, WIDTH, HEIGHT ); 
	_display(ra, &t);
	glutSwapBuffers();
}
void myMouse(int button,int state,int x,int y)
{
	int i = 0;
	int number;
		if(state==GLUT_DOWN)
    {
        if(button==GLUT_LEFT_BUTTON)
        {
			for (i=0; i<50; i++)
			{
				number = rand() % NUM; //
				ra[number]->is_on ^= 1;
			} 
        }
	}
}
void myIdle(void)
{
    mydisplay();
}
DWORD WINAPI ThreadFun(LPVOID pM)  
{  
    int i = 0;
	int st = 0;
	int number;
	int g = 0;
    srand((unsigned) time(NULL)); 
	initial(&t, ra);
	flag = 1;
	
	while(1)
	{
		for(i = 0; i != NUM; i++)
		{
			collision(ra[i], i, NUM, ra, &t);
		}
		update(ra, &t);
		for(i = 0; i < 100 - t.rb_num; i++)
		{
			int j = 0;
			for(j = 0; j < 700 + ROTATION * 40; j++);
		}
		for(i = 0; i < 450 / 2 - t.rb_num * (t.rb_num - 1) / 2; i++)
		{
			int j = 0;
			for(j = 0; j < 100 + CLINE * 20; j++);
		}
}

    return 0;  
}  
//DWORD WINAPI ThreadFun1(LPVOID pM)  
//{
//	int i = 0;
//	while(!flag)
//		;
//	while(1)
//	{
//	for(i = 0; i != NUM; i++)
//	{
//		ct(ra[i]);
//	}
//	}
//}

void main(int arg, char *argv[])
{
	HANDLE handle = CreateThread(NULL, 0, ThreadFun, NULL, 0, NULL); 
	//HANDLE handle2 = CreateThread(NULL, 0, ThreadFun1, NULL, 0, NULL); 
	int i = 0;
	glutInit(&arg, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(2 * HEIGHT, WIDTH);
	glutCreateWindow("Simulation1");
	glutDisplayFunc(&mydisplay);
    glutIdleFunc(&myIdle);    
	 //glutMouseFunc(&myMouse);
     glutMainLoop();
	system("pause");
}

