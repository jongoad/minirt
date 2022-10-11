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

	rt->cam.right = cross_vec3(rt->cam.forward, rt->cam.up); /* Calculate right vector */
	rt->cam.right = unit_vec3(rt->cam.right);
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
	t_vec4 target;

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

			target = mat_mult_vec4(vec4(coord.x, coord.y, 1, 1), rt->cam.inv_project);
			t_vec4 normed = vec3_to_vec4(unit_vec3(div_vec3(vec4_to_vec3(target), target.w)), T_VEC);
			t_vec4 invert = mat_mult_vec4(normed, rt->cam.inv_view);
			rt->cam.rays[i.y][i.x] = vec4_to_vec3(invert);
			i.x++;
		}
		i.y++;
	}
}

/* Recalculate view & projection matrices and regenerate rays */
void	cam_recalc(t_data *rt)
{
	/* Apply any movement vectors */
	if (rt->cam.is_move)
	{
		//rt->cam.forward = ; Create rotation matrix and apply to forward vector
		rt->cam.pos = add_vec3(rt->cam.pos_ref, rt->cam.translate);
	}

	/* Recalc everything */
	cam_calc_view(rt);
	cam_calc_project(rt);
	cam_generate_rays(rt);
}



/* Steps for camera movement (WASD or arrows)

Pseudocode:

if (keypress == W_KEY)
	rt->cam.pos += forward_vector * move_speed
*/



/* Steps for mouse camera control:


Pitch & Yaw (rotation):

Note: We will not support tilt (z-rotation)
1. Get rotation data from mouse input:
	- lateral movement is y-axis rotation
	- vertical movement is x-axis rotation
2. Apply rotation to each axis
	- Might want to use a rotation speed value for config options
	- rot_degrees = mouse_movement * rot_speed;

Pseudocode:

if (delta.x != 0 || delta.y != 0)									If mouse has moved
{
	pitch_delta = delta.y * rotation_speed
	yaw_delta = delta.x * rotation_speed

	Convert these values into rotation matrices
	Apply matrices to the forward (aim or direction) vector

	moved = true;
}
if (moved == true)
{
	recalculate ray directions
	recalculate view matrix
	recalculate projection matrix
}

remember to reset moved = false (probably when the right mouse button is released)


*/

/* Object Transform Steps 
1. Starting a with a point (vertex) apply the necessary transforms sequentially.

vertex * local_to_world * view_matrix * projection matrix

COLUMN VS ROW MAJOR IS IMPORTANT HERE! Check what we are using
If column major this is:

projecttion * view * transform * vertex

Ray calculation steps:

By precalculating and caching the rays, the costly matrix math does not need to be reapplied for every render frame, UNLESS there is movement

When this process if being used to calculate rays, the local_to_world is simply a u,v translation to select the correct pixel



Pseudocode for ray calculation

for(columns)
{
	for (rows)
	{
		vec2 coord = {(float)x / viewport_width, (float)y / viewport_height};
		coord = coord * 2.0f + 1.0f; //What is happening here? 

		//Target is the point on the viewing plane we are aiming at to create our ray
		vec4 target = inv_projection * vec4(coord.x, coord.y, 1, 1);
		vec3 ray_direction = vec3(inv_view * vec4(normalize(vec3(target) / target.w), 0)); // This translates us to world space and deals with perspective divide
		add ray direction to our cached array
	}
}

*/


//https://www.youtube.com/watch?v=lXlXqUEEJ94
