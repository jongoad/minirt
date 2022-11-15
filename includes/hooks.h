#ifndef MINIRT_HOOKS_H
# define MINIRT_HOOKS_H
/**
 *	This header is for the hooks family of c files
 *		hooks.c
 *		key_hooks.c
 *		mouse_hooks.c
 */

/* Relevant struct protoypes */
typedef struct s_data	t_data;

/* macOS Key Codes */
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
	KEY_B = 11,
	KEY_C = 8,
	KEY_D = 2,
	KEY_E = 14,
	KEY_F = 3,
	KEY_G = 5,
	KEY_H = 4,
	KEY_I = 34,
	KEY_J = 38,
	KEY_K = 40,
	KEY_L = 37,
	KEY_M = 46,
	KEY_N = 45,
	KEY_O = 31,
	KEY_P = 35,
	KEY_Q = 12,
	KEY_R = 15,
	KEY_S = 1,
	KEY_T = 17,
	KEY_U = 32,
	KEY_V = 9,
	KEY_W = 13,
	KEY_X = 7,
	KEY_Y = 16,
	KEY_Z = 6,
	KEY_ESC = 53,
	KEY_SPACE = 49,
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
	KEY_1 = 18,
	KEY_2 = 19,
	KEY_3 = 20,
	KEY_4 = 21,
	KEY_5 = 23,
	KEY_6 = 22,
	KEY_7 = 26,
	KEY_8 = 28,
	KEY_9 = 25,
	NUMPAD_MINUS = 78,
	NUMPAD_PLUS = 69
}	t_keyhooks;

/* Mouse Keyhook Types */
typedef enum e_mousehooks
{
	LEFT_CLICK = 1,
	RIGHT_CLICK = 2,
	WHEEL_DOWN = 4,
	WHEEL_UP = 5
}	t_mousehooks;

/* X11 Event Define Codes */
typedef enum e_mlx_events
{
	KEYPRESS = 2,
	MOUSE_RELEASE = 5,
	MOTION_NOTIFY = 6,
	DESTROY_NOTIFY = 17
}	t_mlx_events;

typedef enum e_mlx_event_masks
{
	KEYPRESS_MASK = (1L << 0),
	MOUSE_RELEASE_MASK = (1L << 3),
	MOTION_NOTIFY_MASK = (1L << 3),
}	t_mlx_event_masks;

//FUNCTIONS
int		handle_key_release_hook(int keysym, t_data *rt);
int		handle_key_press_hook(int keysym, t_data *rt);
int		handle_key_press_hook_2(int keysym, t_data *rt);
int		handle_mouse_hook(int button, int x, int y, t_data *rt);
int		handle_mouse_btn_release(int button, int x, int y, t_data *rt);
int		handle_mouse_motion(int x, int y, t_data *rt);
int		default_hook(t_data *rt);

#endif // MINIRT_HOOKS_H