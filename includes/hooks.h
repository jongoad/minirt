#ifndef MINIRT_HOOKS_H
# define MINIRT_HOOKS_H
/**
 *	This header is for the hooks family of c files
 *		hooks.c
 *		key_hooks.c
 *		mouse_hooks.c
 */

# define TWO_PI 6.28318530718

typedef struct s_data	t_data;
typedef enum e_keyhooks
{
	KEY_0 = 29,
	KEY_UP = 126,
	KEY_DOWN = 125,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_PLUS = 24,
	KEY_MINUS = 27,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_Z = 6,
	KEY_X = 7,
	KEY_C = 8,
	KEY_Q = 12,
	KEY_W = 13,
	KEY_E = 14,
	KEY_R = 15,
	KEY_O = 31,
	KEY_P = 35,
	KEY_ESC = 53,
	KEY_F1 = 122,
	NUMPAD0 = 82,
	NUMPAD1 = 83,
	NUMPAD2 = 84,
	NUMPAD3 = 85,
	NUMPAD4 = 86,
	NUMPAD6 = 88,
	NUMPAD5 = 87,
	NUMPAD7 = 89,
	NUMPAD8 = 91,
	NUMPAD9 = 92,
	NUMPAD_MINUS = 78,
	NUMPAD_PLUS = 69
}	t_keyhooks;

typedef enum e_mlx_events
{
	KEYPRESS = 2,
	MOTION_NOTIFY = 6,
	DESTROY_NOTIFY = 17
}	t_mlx_events;

//FUNCTIONS
int		handle_key_release_hook(int keysym, t_data *rt);
int		handle_key_press_hook(int keysym, t_data *rt);
int		handle_key_press_hook_2(int keysym, t_data *rt);
int		handle_mouse_hook(int button, int x, int y, t_data *rt);
int		handle_mouse_motion(int x, int y, t_data *rt);
int		default_hook(t_data *rt);

#endif // MINIRT_HOOKS_H