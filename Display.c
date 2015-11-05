#include "Pre.h"
void draw_robot(float x, float y, float r, float f, char c, char is_show, float angel)
{
	int i = 0;
	if(is_show)
	{
		if(c)
			glColor3f(0.141, 0.663, 0.882);
		else
			glColor3f(0.73, 0.157, 0.207);
		glBegin(GL_POLYGON);
		 for(i=0; i<10; ++i)
			 glVertex2f(x + r * (cos(Pi / 10 * i + angel)), y + r * sin(Pi / 10 * i + angel));
		 glEnd();
		 glColor3f(0.95, 0.9, 0.5);
		 glBegin(GL_POLYGON);
		 for(i = 0; i < 10; i++)
			 glVertex2f(x + r * (cos(Pi / 10 * i + Pi + angel)), y + r * sin(Pi / 10 * i + angel + Pi));
		 glEnd();
	}
}
void draw_table(float x, float y, float r, table *t)
{
	int i = 0;
	int j = 0;
	glColor3f(0.3019, 0.271, 0.31);
	glBegin(GL_POLYGON);
	for(i=0; i<50; ++i)
		glVertex2f(x + r * cos(2 * Pi / 50*i), y + r * sin(2 * Pi / 50 * i));
	glEnd();
	if(CLINE)
	{
		for (i = 0; i != NUM * (NUM - 1) / 2; i++)
		{
			if(t->cl[i].is_show)
			{
				if(t->cl[i].length < MAX_RANGE)
				{
					glColor3f(0, t->cl[i].length / (RT + RR), t->cl[i].length / (RT + RR));
					glBegin(GL_LINE_STRIP);
					glVertex2f(t->cl[i].xf / (RT + t->m_r), t->cl[i].yf / (RT + t->m_r));
					glVertex2f(t->cl[i].xt / (RT + t->m_r), t->cl[i].yt/ (RT + t->m_r));
					glEnd();
				}
			}
		}
	}
}
void _draw_table(float x, float y, float r, table *t)
{
	int i = 0;
	int j = 0;
	glColor3f(0.3019, 0.271, 0.31);
	glBegin(GL_POLYGON);
	for(i=0; i<50; ++i)
		glVertex2f(x + r * cos(2 * Pi / 50*i), y + r * sin(2 * Pi / 50 * i));
	glEnd();
	if(CLINE)
	{
		for (i = 0; i != NUM * (NUM - 1) / 2; i++)
		{
			if(t->cl[i].is_show)
			{
				if(t->cl[i].length < MAX_RANGE)
				{
					glColor3f(0, t->cl[i].length / (RT + RR), t->cl[i].length / (RT + RR));
					glBegin(GL_LINE_STRIP);
					glVertex2f((t->cl[i].xf - t->x)/ (RT + t->m_r), (t->cl[i].yf - t->y) / (RT + t->m_r));
					glVertex2f((t->cl[i].xt - t->x) / (RT + t->m_r), (t->cl[i].yt - t->y)/ (RT + t->m_r));
					glEnd();
				}
			}
		}
	}
}
void display(robot **ra, table *t)
{
	
	int i = 0;
	draw_table(t->x / (RT + t->m_r) , t->y / (RT + t->m_r), (RT / (RT + t->m_r)), t);
	for(i = 0; i != NUM; i++)
	{
		draw_robot((ra[i]->x ) / (RT + t->m_r), (ra[i]->y) / (RT + t->m_r), ra[i]->r / (RT + t->m_r), i, ra[i]->is_on, ra[i]->is_show, ra[i]->angel);
	}
	glFlush();
}
void _display(robot** ra, table *t)
{
	int i = 0;
	float offsetx[10] = {-0.37, -0.37, -0.37, -0.321, 0.279, 0.43, 0.43, 0.43, 0.43, 0.43};
	float offsety[10] =  {-0.4, 0, 0.37, 0.37, -0.43, -0.43, 0, 0.4, 0.4, 0.4};
	_draw_table(0, 0, RT / (RT + t->m_r), t);
	
	for(i = 0; i != NUM; i++)
	{
		draw_robot((ra[i]->x - t->x) / (RT + t->m_r), (ra[i]->y - t->y) / (RT + t->m_r), ra[i]->r / (RT + t->m_r), i, ra[i]->is_on, ra[i]->is_show, ra[i]->angel);
	}
	///******************************************

	               glBegin(GL_LINE_STRIP);
				   for(i = 0; i != 9; i++)
				   {
					glVertex2f((XX[i])/ (RT + t->m_r), (YY[i]) / (RT + t->m_r));
					//glVertex2f((0) / (RT + t->m_r), (0)/ (RT + t->m_r));
				   }
					glEnd();
					//glBegin(GL_LINE_STRIP);
					//glVertex2f((0.4 - 0.707 * 0.03)/ (RT + t->m_r), (0.4 + 0.707 * 0.03) / (RT + t->m_r));
					//glVertex2f((- 0.707 * 0.03) / (RT + t->m_r), (0.707 * 0.03)/ (RT + t->m_r));
					//glEnd();
					glBegin(GL_LINE_STRIP);
					for(i = 0; i != 9; i++)
					//{
					//glVertex2f((XX[i] + sin(atan2(YY[i+1] - YY[i], XX[i+1] - XX[i])) * 0.03 )/ (RT + t->m_r), (YY[i] - cos(atan2(YY[i+1] - YY[i], XX[i+1] - XX[i])) * 0.03 ) / (RT + t->m_r));
					//}
					//glVertex2f((+ 0.707 * 0.03) / (RT + t->m_r), (-0.707 * 0.03)/ (RT + t->m_r));
					glVertex2f(offsetx[i] / (RT + t->m_r), offsety[i]/ (RT + t->m_r));
					glEnd();
	///************************************************
	glFlush();
}