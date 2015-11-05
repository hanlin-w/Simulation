#include "Pre.h"
void initial(table *t, robot **ra)
{
	int i = 0;
	int j = 0;
	float left_upx;
	float left_upy;
	float xxx[] ={-0.4, -0.4, -0.4, -0.3, 0.3, 0.4, 0.4, 0.4, 0.4, 0.4};
    float yyy[]  = {-0.4, 0, 0.4, 0.4, -0.4, -0.4, 0, 0.4, 0.4, 0.4};
	robot *temp;

	c_v = 0;
	t->tt = 0;
	t->m_r = M_R;
	t->miu = MIU;
	t->x = t->m_r;
	t->y = 0;
	t->w = OMEGA;
	t->vx = -t->w * t->m_r * sin(t->tt * t->w);
	t->vy = t->w * t->m_r * cos(t->tt * t->w);
	t->ax = -t->w * t->w * t->m_r * cos(t->tt * t->w);
	t->ay = -t->w * t->w * t->m_r * sin(t->tt * t->w);
	t->r = RT;
	t->rb_num = NUM;
	t->line_num = NUM * (NUM - 1) / 2;
	for(i = 0; i != NUM * (NUM - 1) / 2; i++)
	{
		t->cl[i].is_show = 1;
	}
	t->alpha = 0.0;
	t->ax = -t->w * t->m_r *cos(t->tt * t->w);
	t->ay = -t->w * t->m_r * sin(t->tt * t->w);
	left_upx = t->x - (int)sqrt((float)NUM) * RR;
	left_upy = t->y + (int)sqrt((float)NUM) * RR;
		for(i = 0; i != 10; i++)
	{
		XX[i] = xxx[i];0.1 * i - 0.4;
		YY [i] = yyy[i];XX[i] * XX[i]  * 3; 
	}
	for(i = 0; i != NUM; i++)
	{
		(ra[i]) = (robot *)malloc(sizeof(robot));
		temp = ra[i];
		temp->r = RR;
		temp->alpha = 0;
		temp->ax = 0;
		temp->ay = 0;
		temp->fr.fx = 0;
		temp->fr.fy = 0;
		temp->ft.fx = 0;
		temp->ft.fy = 0;
		temp->is_on = 1;
		temp->x = 0;//M_R - 0.4;;//left_upx + i / (int)sqrt((float)NUM) * (temp->r * 2 ) * 2;
		temp->y = 0;0.48;//left_upy -  i % (int)sqrt((float)NUM) * (temp->r * 2) *2;
		temp->vx = 0;
		temp->vy = 0;
		temp->w = 0;
		temp->m = MASS;
		temp->is_show = 1;
		temp->angel = 0; //(float)i / NUM * 2 * Pi - Pi;
		for (j = 0; j != NUM; j++)
		{
			temp->buffer[j].num = i;
			temp->buffer[j].angel = 0;
			temp->buffer[j].flag = 0;
			temp->s.d_a[j].flag = 0;
			temp->s.d_a[j].angel = 0;
			temp->s.d_a[j].dis = 0;
		}
		temp->pub.num = i;
		temp->s.ax = 0;
		temp->s.ay = 0;
		temp->led= temp->is_on;
		temp->m_o = 0;
		temp->pub.ts = 2 * Pi / OMEGA * i / NUM;
		temp->time_ = 0;
		temp->c_flag = 0;
		temp->time = 0;
		temp->pr.rotate = 0;
		temp->is_cra = 0;
		temp->pr.x = 0;
		temp->pr.y = 0;
		temp->pr.omega = 0;
		temp->pr.v_angel = 0;
	}

}
