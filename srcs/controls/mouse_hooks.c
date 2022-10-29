#include "minirt.h"
#include "hooks.h"


static void	print_selected_object_info(t_data *rt)
{
	if (rt->selected_obj_id == NO_HIT)
		return ;
	printf("You have selected a ");
	if (rt->objs[rt->selected_obj_id]->type == T_CYL)
		printf("cylinder.");
	if (rt->objs[rt->selected_obj_id]->type == T_PLANE)
		printf("plane.");
	if (rt->objs[rt->selected_obj_id]->type == T_SPH)
		printf("sphere.");
	

	printf(" It is object #%d. ", rt->selected_obj_id + 1);
	printf("(Press `F1' to display keyboard controls)\n");
}

int	handle_mouse_btn_release(int button, int x, int y, t_data *rt)
{
	if (button == 1)
	{

		(void)rt;
		(void)x;
		(void)y;
		// printf("mouse btn1 released at [%d, %d]\n", x, y);
		rt->selected_obj_id = cast_ray_at_pixel(rt, x, y);
		print_selected_object_info(rt);
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
	int delta_y = (cur_mouse.y - rt->cam.prev_mouse.y);
	//Changed to negative value to match expectations for rotation

	/* Convert to % of screen so movement does not change with different resolutions */
	float pcnt_x = (float)delta_x / (float)IMG_W;
	float pcnt_y = (float)delta_y / (float)IMG_H;

	

	//Moving mouse up is a negative delta
	//Moving mouse down is a positive delta

	//Moving mouse left is a negative delta
	//Moving mouse right is a positive delta

	//Horizontal movement matches our expectations for rotation
	//Vertical movement is inverted
	if (rt->cam.is_move && (delta_x != 0 && delta_y != 0))											/* Only apply changes if there is movement */
	{
		printf("delta_x: %d - delta_y: %d\n", delta_x, delta_y);
		/* Calculate tilt */
		if (CAM_TOGGLE_PITCH)
		{
			rt->cam.pitch += pcnt_y * CAM_ROT_RATE;
			if (rt->cam.pitch > CAM_MAX_TILT)
				rt->cam.pitch = CAM_MAX_TILT;
			else if (rt->cam.pitch < -CAM_MAX_TILT)
				rt->cam.pitch = -CAM_MAX_TILT;
		}
		/* Calculate pan */
		if (CAM_TOGGLE_YAW)
		{
			rt->cam.yaw += pcnt_x * CAM_ROT_RATE;
			if (rt->cam.yaw < 0)
				rt->cam.yaw = (int)rt->cam.yaw % 360;
			else if (rt->cam.yaw > 0)
				rt->cam.yaw = (int)rt->cam.yaw % -360;
		}

		//FIXME - Might want to store the fractional component and add back after mod for precision


		
		rt->cam.prev_mouse = cur_mouse;
		cam_recalc(rt);
		render_scene(rt);
	}
	return (0);
}



