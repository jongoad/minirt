#include <stdio.h>
#include <math.h>

# define PI 3.14159265359f



typedef struct s_vec2
{
	float u;
	float v;
}	t_vec2;

typedef struct s_vec3
{
	float x;
	float y;
	float z;
}	t_vec3;

typedef struct s_texture
{
	int		width;
	int		height;
	char	*c1;
	char	*c2;
}	t_texture;

t_vec3 vec3(float x, float y, float z)
{
	t_vec3 res;

	res.x = x;
	res.y = y;
	res.z = z;

	return (res);
}

double  length_vec3(t_vec3 v)
{
    return sqrtf(
        (v.x) * (v.x)
        + (v.y) * (v.y)
        + (v.z) * (v.z));
}

t_vec2 spherical_map(t_vec3 p)
{
	t_vec2 res;

	// compute the azimuthal angle
  	// -π < theta <= π
  	// angle increases clockwise as viewed from above,
  	// which is opposite of what we want, but we'll fix it later.
	float theta = atan2(p.x, p.z);

	// vec is the vector pointing from the sphere's origin (the world origin)
  	// to the point, which will also happen to be exactly equal to the sphere's
  	// radius.
	t_vec3 vec = vec3(p.x, p.y, p.z);
	float radius = length_vec3(vec);

	// compute the polar angle
  	// 0 <= phi <= π
	float phi = acos(p.y / radius);

	// -0.5 < raw_u <= 0.5
	float raw_u = theta / (2 * PI);

	// 0 <= u < 1
	// here's also where we fix the direction of u. Subtract it from 1,
	// so that it increases counterclockwise as viewed from above.
	res.u = 1 - (raw_u + 0.5f);

	// we want v to be 0 at the south pole of the sphere,
  	// and 1 at the north pole, so we have to "flip it over"
  	// by subtracting it from 1.
	res.v = 1 - (phi / PI);

	return (res);
}




/* Function to create a checkerboard pattern */
t_texture uv_checkers(int width, int height, char *c1, char *c2)
{
	t_texture res;

	res.width = width;
	res.height = height;
	res.c1 = c1;
	res.c2 = c2;

	return (res);
}
//Returns a struct containing texture data



/* Return color at a given uv coordinate */
char	*uv_pattern_at(t_texture texture, float u, float v)
{
	int	u2 = floor(u * texture.width);
	int	v2 = floor(v * texture.height);

	if ((u2 + v2) % 2 == 0)
		return (texture.c1);
	else
		return (texture.c2);
}


char *pattern_at(t_vec3 p, t_texture texture)
{
	t_vec2 uv;

	uv = spherical_map(p);
	return (uv_pattern_at(texture, uv.u, uv.v));
}


int	main(void)
{
	char c1[] = "black"; // BLACK
	char c2[] = "white"; // WHITE

	t_texture texture = uv_checkers(16, 8, c1, c2);

	// printf("u: %f | v: %f | clr: %s\n", 0.0, 0.0, uv_pattern_at(texture, 0.0f, 0.0f));
	// printf("u: %f | v: %f | clr: %s\n", 0.5, 0.0, uv_pattern_at(texture, 0.5f, 0.0f));
	// printf("u: %f | v: %f | clr: %s\n", 0.0, 0.5, uv_pattern_at(texture, 0.0f, 0.5f));
	// printf("u: %f | v: %f | clr: %s\n", 0.5, 0.5, uv_pattern_at(texture, 0.5f, 0.5f));
	// printf("u: %f | v: %f | clr: %s\n", 1.0, 1.0, uv_pattern_at(texture, 1.0f, 1.0f));
	

	t_vec3 p;
	t_vec2 res;

	// p = vec3(0,0,-1);
	// res = spherical_map(p);
	// printf ("point(%f,%f,%f)	| %f | %f |\n", p.x, p.y, p.z, res.u, res.v);

	// p = vec3(1,0,0);
	// res = spherical_map(p);
	// printf ("point(%f,%f,%f)	| %f | %f |\n", p.x, p.y, p.z, res.u, res.v);

	// p = vec3(0,0,1);
	// res = spherical_map(p);
	// printf ("point(%f,%f,%f)	| %f | %f |\n", p.x, p.y, p.z, res.u, res.v);
	
	// p = vec3(-1,0,0);
	// res = spherical_map(p);
	// printf ("point(%f,%f,%f)	| %f | %f |\n", p.x, p.y, p.z, res.u, res.v);

	// p = vec3(0,1,0);
	// res = spherical_map(p);
	// printf ("point(%f,%f,%f)	| %f | %f |\n", p.x, p.y, p.z, res.u, res.v);

	// p = vec3(0,-1,0);
	// res = spherical_map(p);
	// printf ("point(%f,%f,%f)	| %f | %f |\n", p.x, p.y, p.z, res.u, res.v);

	// p = vec3(sqrt(2)/2,sqrt(2)/2,0);
	// res = spherical_map(p);
	// printf ("point(%f,%f,%f)	| %f | %f |\n", p.x, p.y, p.z, res.u, res.v);

	p = vec3(0.4315, 0.4670, 0.7719);
	printf("point(%f,%f,%f)	| %s\n |", p.x, p.y, p.z, pattern_at(p, texture));
	
	p = vec3(-0.9654, 0.2552, -0.0534);
	printf("point(%f,%f,%f)	| %s\n |", p.x, p.y, p.z, pattern_at(p, texture));

	p = vec3(0.1039, 0.7090, 0.6975);
	printf("point(%f,%f,%f)	| %s\n |", p.x, p.y, p.z, pattern_at(p, texture));

	p = vec3(-0.4986, -0.7856, -0.3663);
	printf("point(%f,%f,%f)	| %s\n |", p.x, p.y, p.z, pattern_at(p, texture));

	p = vec3(-0.0317, -0.9395, 0.3411);
	printf("point(%f,%f,%f)	| %s\n |", p.x, p.y, p.z, pattern_at(p, texture));

	p = vec3(0.4809, -0.7721, 0.4154);
	printf("point(%f,%f,%f)	| %s\n |", p.x, p.y, p.z, pattern_at(p, texture));

	p = vec3(0.0285, -0.9612, -0.2745);
	printf("point(%f,%f,%f)	| %s\n |", p.x, p.y, p.z, pattern_at(p, texture));

	p = vec3(-0.5734, -0.2162, -0.7903);
	printf("point(%f,%f,%f)	| %s\n |", p.x, p.y, p.z, pattern_at(p, texture));

	p = vec3(0.7688, -0.1470, 0.6223);
	printf("point(%f,%f,%f)	| %s\n |", p.x, p.y, p.z, pattern_at(p, texture));

	p = vec3(-0.7652, 0.2175, 0.6060);
	printf("point(%f,%f,%f)	| %s\n |", p.x, p.y, p.z, pattern_at(p, texture));





}