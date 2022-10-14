#include "minirt.h"

/* Setup constant variables for camera */
void	cam_init(t_data *rt)
{
	rt->cam.pos_ref = rt->cam.pos;
	rt->cam.up = vec3(0, 1, 0);
	rt->cam.near = 1.0f;
	rt->cam.far = 1e10;
	rt->cam.is_move = false;
}

/* Calculate matrices for camera view based on direction vectors */
void	cam_calc_view(t_data *rt)
{

	rt->cam.right = unit_vec3(cross_vec3(rt->cam.forward, vec3(0, 1, 0)));
	rt->cam.up = unit_vec3(cross_vec3(rt->cam.forward, rt->cam.right));
	rt->cam.view = mat4(vec3_to_vec4(rt->cam.right, T_VEC), vec3_to_vec4(rt->cam.up, T_VEC),
		vec3_to_vec4(rt->cam.forward, T_VEC), vec3_to_vec4(rt->cam.pos, T_POINT));
	rt->cam.inv_view = mat_inv(rt->cam.view, 4);
}

/* Calculate matrices for camera projection */
void	cam_calc_project(t_data *rt)
{
	float bot;
	float top;
	float left;
	float right;

	float aspect_ratio;

	aspect_ratio = (float)IMG_W / (float)IMG_H;
	top = tan(rt->cam.fov / 2) * rt->cam.near;
	bot = -top;
	right = top * aspect_ratio;
	left = -top * aspect_ratio;

	rt->cam.project.m[0][0] = (2 * rt->cam.near) / (right - left);
	rt->cam.project.m[0][1] = 0;
	rt->cam.project.m[0][2] = (right + left) / (right - left);
	rt->cam.project.m[0][3] = 0;

	rt->cam.project.m[1][0] = 0;
	rt->cam.project.m[1][1] = (2 * rt->cam.near) / (top - bot);
	rt->cam.project.m[1][2] = (top + bot) / (top - bot);
	rt->cam.project.m[1][3] = 0;

	rt->cam.project.m[2][0] = 0;
	rt->cam.project.m[2][1] = 0;
	rt->cam.project.m[2][2] = ((rt->cam.far + rt->cam.near) / (rt->cam.far - rt->cam.near)) * -1;
	rt->cam.project.m[2][3] = ((2 * rt->cam.far * rt->cam.near) / (rt->cam.far - rt->cam.near)) * -1;

	rt->cam.project.m[3][0] = 0;
	rt->cam.project.m[3][1] = 0;
	rt->cam.project.m[3][2] = -1;
	rt->cam.project.m[3][3] = 0;

	rt->cam.inv_project = mat_inv(rt->cam.project, 4);
}

/* Generate and pre-cache camera rays */
void	cam_generate_rays(t_data *rt)
{
	t_i i;
	t_vec3 coord;
	t_vec3 target;

	i.y = 0;
	while (i.y < IMG_H)
	{
		i.x = 0;
		while (i.x < IMG_W)
		{
			
			coord.x = (float)i.x / (float)IMG_W;
			coord.y = (float)i.y / (float)IMG_H;
			
			coord.x = coord.x * 2.0f - 1.0f;
			coord.y = coord.y * 2.0f - 1.0f;
			
			target = vec3(coord.x, coord.y, 1);



			// target = mat_mult_vec4(vec4(coord.x, coord.y, 1, 1), rt->cam.inv_project);
			// t_vec4 normed = vec3_to_vec4(unit_vec3(div_vec3(vec4_to_vec3(target), target.w)), T_VEC);
			// t_vec4 invert = mat_mult_vec4(normed, rt->cam.inv_view);
			rt->cam.rays[i.y][i.x] = unit_vec3(vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(target, T_VEC), rt->cam.view)));
			
			
			// rt->cam.rays[i.y][i.x] = unit_vec3(vec3(coord.x, coord.y, 1));
			i.x++;
		}
		i.y++;
	}
}


/* Recalculate view & projection matrices and regenerate rays */
void	cam_recalc(t_data *rt)
{
	// rt->cam.pos = mult_vec3_vec3(rt->cam.pos_ref, rt->cam.translate);

	/* Recalc everything */
	cam_calc_view(rt);
	cam_calc_project(rt);
	cam_generate_rays(rt);
}
