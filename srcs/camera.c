#include "minirt.h"

/* Setup constant variables for camera */
void	cam_init(t_data *rt)
{
	rt->cam.up = vec3(0, 1, 0);
	rt->cam.near = 1.0f;
	rt->cam.far = 1e10;
	rt->cam.is_move = false;
}

/* Calculate view matrix */
void	cam_calc_view(t_data *rt)
{
	float cosPitch = cos(deg_to_rad(rt->cam.pitch));
    float sinPitch = sin(deg_to_rad(rt->cam.pitch));
    float cosYaw = cos(deg_to_rad(rt->cam.yaw));
    float sinYaw = sin(deg_to_rad(rt->cam.yaw));
 
    t_vec3 xaxis = vec3(cosYaw, 0, -sinYaw);
    t_vec3 yaxis = vec3(sinYaw * sinPitch, cosPitch, cosYaw * sinPitch);
    t_vec3 zaxis = vec3(sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw);

	t_vec4 xaxis4 = vec4(xaxis.x, xaxis.y, xaxis.z, -dot_vec3(xaxis, rt->cam.pos));
	t_vec4 yaxis4 = vec4(yaxis.x, yaxis.y, yaxis.z, -dot_vec3(yaxis, rt->cam.pos));
	t_vec4 zaxis4 = vec4(zaxis.x, zaxis.y, zaxis.z, -dot_vec3(zaxis, rt->cam.pos));

	//Why is inv_view being calculated with a default pos?
	rt->cam.inv_view = mat4(xaxis4, yaxis4, zaxis4, vec4(0,0,0,1));
	// rt->cam.inv_view = mat4(xaxis4, yaxis4, zaxis4, rt->cam.pos);
	rt->cam.view = mat_inv(rt->cam.inv_view, 4);


	//Should be able to calc new axials vectors here
	// rt->cam.forward = unit_vec3(vec4_to_vec3(mat_mult_vec4(vec4(0,0,-1,0), rt->cam.inv_view)));
	// rt->cam.right = unit_vec3(cross_vec3(rt->cam.forward, rt->cam.up));
}

/* Calculate projection matrices */
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
	rt->cam.project.m[1][0] = 0;
	rt->cam.project.m[2][0] = (right + left) / (right - left);
	rt->cam.project.m[3][0] = 0;

	rt->cam.project.m[0][1] = 0;
	rt->cam.project.m[1][1] = (2 * rt->cam.near) / (top - bot);
	rt->cam.project.m[2][1] = (top + bot) / (top - bot);
	rt->cam.project.m[3][1] = 0;

	rt->cam.project.m[0][2] = 0;
	rt->cam.project.m[1][2] = 0;
	rt->cam.project.m[2][2] = ((rt->cam.far + rt->cam.near) / (rt->cam.far - rt->cam.near)) * -1;
	rt->cam.project.m[3][2] = ((2 * rt->cam.far * rt->cam.near) / (rt->cam.far - rt->cam.near)) * -1;

	rt->cam.project.m[0][3] = 0;
	rt->cam.project.m[1][3] = 0;
	rt->cam.project.m[2][3] = -1;
	rt->cam.project.m[3][3] = 0;

	rt->cam.inv_project = mat_inv(rt->cam.project, 4);
}

/* Generate and pre-cache camera rays */
void	cam_generate_rays(t_data *rt)
{
	t_i i;
	t_vec4 coord;
	t_vec4 target;
	t_vec4 norm;

	i.y = 0;
	while (i.y < IMG_H)
	{
		i.x = 0;
		while (i.x < IMG_W)
		{
			coord = vec4((float)i.x / (float)IMG_W, (float)i.y / (float)IMG_H, 1, 1);
			coord.x = coord.x * 2.0f - 1.0f;
			coord.y = coord.y * 2.0f - 1.0f;
			
			target = mat_mult_vec4(vec4(coord.x, coord.y, 1, 1), rt->cam.inv_project);
			norm = vec3_to_vec4(unit_vec3(mult_vec3(vec4_to_vec3(target), target.w)), 0);
			rt->cam.rays[i.y][i.x] = unit_vec3(vec4_to_vec3(mat_mult_vec4(norm, rt->cam.inv_view)));
			
			// FIXME - Testing inverted z axis
			// Figure out why z value for ray is inverted?
			if ((rt->cam.aim.z < 0 && rt->cam.rays[i.y][i.x].z > 0) ||
				(rt->cam.aim.z > 0 && rt->cam.rays[i.y][i.x].z < 0))
				rt->cam.rays[i.y][i.x].z = -rt->cam.rays[i.y][i.x].z;

			if ((rt->cam.aim.x < 0 && rt->cam.rays[i.y][i.x].x > 0) ||
				(rt->cam.aim.x > 0 && rt->cam.rays[i.y][i.x].x < 0))
				rt->cam.rays[i.y][i.x].x = -rt->cam.rays[i.y][i.x].x;

			rt->cam.rays[i.y][i.x].y *= -1; //TEMP FIX, FIND THE ROOT OF ALL THIS INVERSION!!!

			i.x++;
		}
		i.y++;
	}
}

/* Recalculate view & projection matrices and regenerate rays */
void	cam_recalc(t_data *rt)
{

	cam_calc_view(rt);


	//TEMP
		rt->cam.forward = unit_vec3(vec4_to_vec3(mat_mult_vec4(vec4(0,0,-1,0), rt->cam.inv_view)));
		rt->cam.right = unit_vec3(cross_vec3(rt->cam.forward, rt->cam.up));

		rt->cam.forward.x *= -1;	//TEMP FIXME


	cam_calc_project(rt);
	cam_generate_rays(rt);
}



/* Camera Cleanup:

	- Figure out why rays are ending up with inverted x and y components
	- Change flow so that axial vectors only need to be recalculated once
	- Change flow so that all transforms are applied in the same place
	- Review projection code to ensure it is behaving as expected (this could be source of inversion)


	Problems:
	- Currently the code to apply camera position translations relies on use of the view matrix.
		- This is a problem because the view matrix uses camera position.



	Init steps:
	1. Using the camera orientation vector, find the current rotation values for x and y axis.
	



	Loop Steps:
	1. Get input data from mouse and/or keyboard to update transforms for camera and thus for rays.
	2. Apply rotation data and then recalculate view matrix
	3. Recalculate axial vectors and apply camera translation (steps 2 and 3 are an issue. see problems)





*/