#include "Pre.h"
void collision(robot *r, int number, int len, robot **ra, table *t)///len = NUM, number is the serial of the r
{
	int i = 0;
	float rx, ry, rr;
	float ff;
	if(r->is_show)
	{
		for(i = number + 1; i != len; i++)
		{
			if(ra[i]->is_show)
			{
				rx = ra[i]->x - r->x;
				ry = ra[i]->y - r->y;
				rr =sqrt(rx * rx + ry * ry);
				if(CLINE)
				{
					t->cl[ i - number -1 + number * (len - 1 + len - number) / 2 ].from = number;
					t->cl[ i - number -1 + number * (len - 1 + len - number) / 2 ].to = i;
					t->cl[ i - number -1 + number * (len - 1 + len - number) / 2 ].xf =  r->x;
					t->cl[ i - number -1 + number * (len - 1 + len - number) / 2].yf = r->y;
					t->cl[ i - number -1 + number * (len - 1 + len - number) / 2].xt = ra[i]->x;
					t->cl[ i - number -1 + number * (len - 1 + len - number) / 2 ].yt = ra[i]->y;
					t->cl[ i - number -1 + number * (len - 1 + len - number) / 2].length = rr;
				}
				if(!c_v && rr < MAX_RANGE)
				{
					r->s.d_a[i].to = i;
					ra[i]->s.d_a[r->pub.num].to = r->pub.num;
					r->s.d_a[i].dis = rr;
					ra[i]->s.d_a[r->pub.num].dis = rr;
					r->s.d_a[i].angel = atan2(ry, rx) - r->angel;
					if(r->s.d_a[i].angel > Pi)
						r->s.d_a[i].angel -= Pi * 2;
					if(r->s.d_a[i].angel < -Pi)
						r->s.d_a[i].angel += Pi * 2;
					
					ra[i]->s.d_a[r->pub.num].angel = atan2(-ry, -rx)  - ra[i]->angel;
					if(ra[i]->s.d_a[r->pub.num].angel > Pi)
						ra[i]->s.d_a[r->pub.num].angel -= Pi * 2;
					if(ra[i]->s.d_a[r->pub.num].angel< -Pi)
						ra[i]->s.d_a[r->pub.num].angel += Pi * 2;
					r->s.d_a[i].flag = 1;
					ra[i]->s.d_a[r->pub.num].flag = 1;
				}
				if(rr < 2 * RR)
				{
					r->fr.fx -= E * (2 * RR - rr) * rx / rr;
					r->fr.fy -= E * (2 * RR - rr) * ry / rr;
					ff = sqrt(r->fr.fx * r->fr.fx + r->fr.fy * r->fr.fy);
					if(ff > MASS * 2)
					{
						
						r->fr.fx =  r->fr.fx / ff * MASS * 2;
						r->fr.fy = r->fr.fy/ ff *  MASS * 2;
					}
					ra[i]->fr.fx -= r->fr.fx;
					ra[i]->fr.fy -= r->fr.fy;

					if(ROTATION)
					{
						r->angel += sqrt((r->vx - ra[i]->vx) * (r->vx - ra[i]->vx) + (r->vy - ra[i]->vy) * (r->vy - ra[i]->vy)) * atan2(r->vx - ra[i]->vx, r->vy - ra[i]->vy);
						r->angel = r->angel > 2 * Pi ? r->angel - 2 * Pi : r->angel;
						ra[i]->angel += -sqrt((r->vx - ra[i]->vx) * (r->vx - ra[i]->vx) + (r->vy - ra[i]->vy) * (r->vy - ra[i]->vy)) * atan2(r->vx - ra[i]->vx, r->vy - ra[i]->vy);
						ra[i]->angel = ra[i]->angel > 2 * Pi ? ra[i]->angel - 2 * Pi : ra[i]->angel;
					}
				}
			}
			///********************************controll the communication *********************************
			if(!c_v && r->s.d_a[i].dis < MAX_RANGE )
			{
				ra[i]->pub.angel = ra[i]->s.d_a[number].angel - ra[i]->m_o;
				ra[i]->pub.flag = 1;
				if(ra[i]->pub.angel > Pi)
					ra[i]->pub.angel -= 2 * Pi;
				if(ra[i]->pub.angel < -Pi)
					ra[i]->pub.angel += 2 * Pi;
				if(ra[i]->s.d_a[number].flag)
					memcpy(&(r->buffer[i]), &(ra[i]->pub), sizeof(msg));
				r->pub.angel = r->s.d_a[i].angel - r->m_o;
				r->pub.flag = 1;
				if(r->pub.angel > Pi)
					r->pub.angel -= 2 * Pi;
				if(r->pub.angel < -Pi)
					r->pub.angel += 2 * Pi;
				if(r->s.d_a[i].flag)
					memcpy(&(ra[i]->buffer[number]), &(r->pub), sizeof(msg));
				r->s.d_a[i].flag = 0;
				ra[i]->s.d_a[number].flag = 0;
			}
			///************************************controll the communication****************************
		}
	}
}