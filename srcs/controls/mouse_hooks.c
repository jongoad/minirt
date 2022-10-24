#include "minirt.h"
#include "hooks.h"

int	handle_mouse_btn_release(int button, int x, int y, t_data *rt)
{
	if (button == 1)
	{

		(void)rt;
		(void)x;
		(void)y;
		// printf("mouse btn1 released at [%d, %d]\n", x, y);
		rt->selected_obj_id = cast_ray_at_pixel(rt, x, y);
		// printf("selected_obj_id = %d\n", rt->selected_obj_id);
	}
	if (button == 2)
		rt->cam.is_move = false;
	return (0);

}



int	handle_mouse_hook(int button, int x, int y, t_data *rt)
{
	if (button == 1)
	{

		(void)rt;
		(void)x;
		(void)y;
		// printf("mouse btn1 clicked at [%d, %d]\n", x, y);
	}
	if (button == 2)
	{
		rt->cam.prev_mouse = vec3((float)x, (float)y, 0);
		rt->cam.is_move = true;
	}
	return (0);
}



/* Need to implement restriction on tilt (prevent camera from inverting)*/
int	handle_mouse_motion(int x, int y, t_data *rt)
{
	t_vec3	cur_mouse;
	cur_mouse = vec3((float)x, (float)y, 0);
	
	/* Get magnitude and direction of movement */
	int delta_x = cur_mouse.x - rt->cam.prev_mouse.x;
	int delta_y = cur_mouse.y - rt->cam.prev_mouse.y;

	/* Convert to % of screen so movement does not change with different resolutions */
	float pcnt_x = (float)delta_x / (float)IMG_W;
	float pcnt_y = (float)delta_y / (float)IMG_H;

	if (rt->cam.is_move && (delta_x != 0 && delta_y != 0))											/* Only apply changes if there is movement */
	{
		
		/* Calculate tilt */
		if (CAM_TOGGLE_PITCH)
		{
			rt->cam.tilt -= pcnt_y * CAM_ROT_RATE;
			if (rt->cam.tilt > CAM_MAX_TILT)
				rt->cam.tilt = CAM_MAX_TILT;
			else if (rt->cam.tilt < -CAM_MAX_TILT)
				rt->cam.tilt = -CAM_MAX_TILT;
		}
		/* Calculate pan */
		if (CAM_TOGGLE_YAW)
		{
			rt->cam.pan += pcnt_x * CAM_ROT_RATE;
			if (rt->cam.pan < 0)
				rt->cam.pan = (int)rt->cam.pan % 360;
			else if (rt->cam.pan > 0)
				rt->cam.pan = (int)rt->cam.pan % -360;
		}


		
		rt->cam.prev_mouse = cur_mouse;
		cam_recalc(rt);
		render_scene(rt, rt->objs[0]);
	}
	return (0);
}



