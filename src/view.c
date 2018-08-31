
#include <fdf.h>

t_point		project_point(t_fdf *fdf, t_point p)
{
	t_point		pp;
	double		x;
	double		y;
	double		z;
	double		c;

	c = M_PI / 180;
	x = p.x;
	y = p.y;
	z = p.z;
	pp.x = (WID / 2) + (cos(fdf->cam->x * c) * (x - (WID / 2)))
			+ (z * sin(fdf->cam->x * c) * fdf->zs * cos(c * fdf->cam->y))
			- ((LEN / 2) * sin(c * fdf->cam->y) * sin(c * fdf->cam->x)
					* ((y - (LEN / 2)) / (LEN / 2)));
	pp.y = (LEN / 2) + (cos(fdf->cam->y * c) * (y - (LEN / 2)))
			+ (z * sin(fdf->cam->y * c) * fdf->zs);
	pp.z = p.z;
	return (pp);
}

int			color_select(int color, int num)
{
	color += num;
	color %= 1536;
	if (color >= 0 && color < 256)
		color = 0xFF0000 + (color << 8);
	else if (color >= 256 && color < 512)
		color = 0xFFFF00 - ((color % 256) << 16);
	else if (color >= 512 && color < 768)
		color = 0x00FF00 + ((color % 256));
	else if (color >= 512 && color < 1024)
		color = 0x00FFFF - ((color % 256) << 8);
	else if (color >= 512 && color < 1280)
		color = 0x0000FF + ((color % 256) << 16);
	else if (color >= 512 && color < 1536)
		color = 0xFF00FF - ((color % 256));
	return (color);
}
