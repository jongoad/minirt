#include "minirt.h"
#include "hooks.h"

static int	handle_mouse_xy_translation(float pcnt_x, float pcnt_y, t_data *rt);
static int	handle_mouse_z_translation(t_data *rt, int button);

static void	print_selected_object_info(t_data *rt)
{
	if (rt->selected_obj_id == NO_HIT)
		return ;
	printf("You have selected object #%d, a ", rt->selected_obj_id + 1);
	if (rt->objs[rt->selected_obj_id]->type == T_CYL)
		printf("cylinder.");
	if (rt->objs[rt->selected_obj_id]->type == T_PLANE)
		printf("plane.");
	if (rt->objs[rt->selected_obj_id]->type == T_SPH)
		printf("sphere.");

	printf("(Press `F1' to display keyboard controls)\n");
	printf("(Press SPACE to display object info)\n");
}

int	handle_mouse_btn_release(int button, int x, int y, t_data *rt)
{
	(void)rt;
	(void)x;
	(void)y;
	if (button == RIGHT_CLICK)
		rt->cam.is_move = false;
	else if (button == 1)
		rt->toggle.is_left_click = false;
	return (0);
}

int	handle_mouse_hook(int button, int x, int y, t_data *rt)
{
	(void)rt;
	(void)x;
	(void)y;
	if (button == LEFT_CLICK)
	{
		rt->selected_obj_id = cast_ray_at_pixel(rt, x, y);
		print_selected_object_info(rt);
		rt->toggle.is_left_click = true;
	}
	else if (button == RIGHT_CLICK)
		rt->cam.is_move = true;
	else if (button == WHEEL_UP || button == WHEEL_DOWN)
		handle_mouse_z_translation(rt, button);
	else
		return (0);
	rt->cam.prev_mouse = vec3((float)x, (float)y, 0);
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

	

	//Moving mouse up is a negative delta
	//Moving mouse down is a positive delta

	//Moving mouse left is a negative delta
	//Moving mouse right is a positive delta

	//Horizontal movement matches our expectations for rotation
	//Vertical movement is inverted
	if (rt->cam.is_move && (delta_x != 0 && delta_y != 0))											/* Only apply changes if there is movement */
	{
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
	if (handle_mouse_xy_translation(pcnt_x, pcnt_y, rt))
		rt->cam.prev_mouse = vec3((float)x, (float)y, 0);
	return (0);
}

static int	handle_mouse_xy_translation(float pcnt_x, float pcnt_y, t_data *rt)
{
	float	z_dist;
	
	if (rt->toggle.is_left_click && rt->selected_obj_id != NO_HIT
		&& pcnt_x != 0 && pcnt_y != 0)		/* Object xy rotation */
	{
		z_dist = length_vec3(project_a_on_b(sub_vec3(rt->objs[rt->selected_obj_id]->pos, rt->cam.pos), rt->cam.forward));
		add_vec3_self(&rt->objs[rt->selected_obj_id]->pos, 
			mult_vec3(rt->cam.right, rt->cam.view_w * pcnt_x * z_dist));
		add_vec3_self(&rt->objs[rt->selected_obj_id]->pos, 
			mult_vec3(rt->cam.real_up, rt->cam.view_h * -pcnt_y * z_dist));
		render_scene(rt);
		return (true);
	}
	return (false);
}


static int	handle_mouse_z_translation(t_data *rt, int button)
{
	float	z_offset;
	
	if (rt->selected_obj_id != NO_HIT)		/* Object xy rotation */
	{
		if (button == WHEEL_UP)
			z_offset = 1.0F;
		else
			z_offset = -1.0F;
		add_vec3_self(&rt->objs[rt->selected_obj_id]->pos, 
			mult_vec3(rt->cam.forward, z_offset));
		render_scene(rt);
		return (true);
	}
	return (false);
}

