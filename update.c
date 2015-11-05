#include "Pre.h"
void update(robot **ra, table *t) // number 
{
	float vxrt, vyrt;
	float vxrt_, vyrt_;
	float axt, ayt;
	float _f_, _f_x, _f_y;
	float press;
	float vxr, vyr, vr;
	int i;
	int j;
	robot *r;
	t->tt += DELTA_T;
	t->tt = t->tt > (2 * Pi / t->w)? t->tt - (2 * Pi / t->w) : t->tt;
	t->w += t->alpha * DELTA_T;
	vr = t->w * t->m_r;
	vxrt = t->vx;
	vyrt = t->vy;
	t->x = t->m_r * cos(t->w * t->tt);
	t->y =  t->m_r * sin(t->w * t->tt);
	vxrt_ = -vr * sin(t->w * t->tt);
	vyrt_ = vr * cos(t->w * t->tt);
	t->vx = vxrt_;
	t->vy = vyrt_;
	t->ax = axt = -vr * t->w * cos(t->w * t->tt);
	t->ay = ayt = -vr * t->w * sin(t->w * t->tt);
	for(i = 0; i != NUM; i++)
	{
		r = ra[i];
		if(r->is_show)
		{
			_f_x = (r->fr.fx - axt * r->m);
			_f_y = (r->fr.fx - ayt * r->m);
			_f_ = sqrt(_f_x * _f_x  + _f_y * _f_y);
			if (fabs(r->vx - vxrt) < 0.00001 && fabs(r->vy - vyrt) < 0.00001)
			{
				press = r->m * 9.8 + r->is_on * MAG_F;
				if (fabs(_f_) <= (press * MIU))
				{
					r->x = r->x + vxrt * DELTA_T;
					r->y = r->y + vyrt * DELTA_T;
					r->vx = vxrt_;
					r->vy = vyrt_;
					r->ax = axt;
					r->ay = ayt;
				}
				else
				{
					r->ft.fx = -t->miu * press * _f_x / _f_;
					r->ft.fy = -t->miu * press * _f_y / _f_;
					r->ax = (r->ft.fx + r->fr.fx) / r->m;
					r->ay = (r->ft.fy + r->fr.fy) / r->m;
					//r->ax = r->ax > 1 ? 1 : r->ax;
					//r->ay = r->ay > 1 ? 1 : r->ay;
					r->x += (r->vx * DELTA_T + 0.5 * r->ax * DELTA_T * DELTA_T);
					r->y += (r->vy * DELTA_T + 0.5 * r->ay * DELTA_T * DELTA_T);
					r->vx += (r->ax * DELTA_T);
					r->vy += (r->ay * DELTA_T);
				}
			}
			else
			{
				press = r->m * 9.8 + r->is_on * MAG_F;
				vxr = r->vx - vxrt;
				vyr = r->vy - vyrt;
				vr = sqrt(vxr * vxr + vyr * vyr);
				r->ft.fx = -(vxr / vr) * t->miu * press;
				r->ft.fy = -(vyr / vr) * t->miu * press;
				r->ax = (r->ft.fx + r->fr.fx) / r->m;
				r->ay = (r->ft.fy + r->fr.fy) / r->m;
				//r->ax = r->ax > 1 ? 1 : r->ax;
				//r->ay = r->ay > 1 ? 1 : r->ay;
				r->x += (r->vx * DELTA_T + 0.5 * r->ax * DELTA_T * DELTA_T);
				r->y += (r->vy * DELTA_T + 0.5 * r->ay * DELTA_T * DELTA_T);
				r->vx += (r->ax * DELTA_T);
				r->vy += (r->ay * DELTA_T);
				//printf("%f\n", r->ax);
				if(r->fr.fx == 0 && r->fr.fy == 0 && (r->vy - vyrt_) * vyr < 0)
				{
					r->vy = vyrt_;
					r->ay = ayt;
				}
				if(r->fr.fx == 0 && r->fr.fy == 0 && (r->vx - vxrt_) * vxr < 0)
				{
					r->vx = vxrt_;
					r->ax = axt;
				}
			}
			r->fr.fx = 0;
			r->fr.fy = 0;
			r->ft.fx = 0;
			r->ft.fy = 0;
			if((r->x - t->x) * (r->x - t->x) + (r->y - t->y) * (r->y - t->y) > RT * RT)
			{
					r->is_show = 0;
					t->rb_num--;
					for(j = 0; j != NUM * (NUM - 1) / 2; j++)
					{
						if(t->cl[j].from == i || t->cl[j].to == i)
						{
							t->cl[j].is_show = 0;
							t->line_num --;
						}
					}
			}
			if(r->is_on)
			{
				r->s.ax = r->ax * cos(r->angel) + r->ay * sin(r->angel);
				r->s.ay = -r->ax * sin(r->angel) + r->ay * cos(r->angel); 
			}
			if(!r->is_on)
			{
				r->s.ax = r->fr.fx / MASS;
				r->s.ay = r->fr.fy / MASS;
			}
			r->time = t->tt;
			ct(r, t);
		}
	}
	c_v++;
	c_v %= C_V;
}