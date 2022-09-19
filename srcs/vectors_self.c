#include "minirt.h"

void    add_vec3_self(t_vec3 *a, t_vec3 b)
{
        a->x += b.x;
        a->y += b.y;
        a->z += b.z;
}

void    add3_vec3_self(t_vec3 *a, t_vec3 b, t_vec3 c)
{
        a->x += b.x + c.x;
        a->y += b.y + c.y;
        a->z += b.z + c.z;
}

void    sub_vec3_self(t_vec3 *a, t_vec3 b)
{
        a->x -= b.x;
        a->y -= b.y;
        a->z -= b.z;
}

void    mult_vec3_vec3_self(t_vec3 *a, t_vec3 b)
{
        a->x *= b.x;
        a->y *= b.y;
        a->z *= b.z;
}

void    mult_vec3_self(t_vec3 *v, double b)
{
        v->x *= b;
        v->y *= b;
        v->z *= b;
}

void    div_vec3_self(t_vec3 *v, double b)
{
    return mult_vec3_self(v, 1.0f / b);
}

void    unit_vec3_self(t_vec3 *v)
{
    double is;

    is = invsqrt(
        v->x * v->x
        + v->y * v->y
        + v->z * v->z);
    return mult_vec3_self(v, is);
}

void    cross_vec3_self(t_vec3 *a, t_vec3 b)
{
    a->x = (a->y * b.z) - (a->z * b.y);
    a->y = (a->z * b.x) - (a->x * b.z);
    a->z = (a->x * b.y) - (a->y * b.x);
}

void    negate_vec3_self(t_vec3 *v)
{
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
}
