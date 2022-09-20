#include "minirt.h"

t_vec3    *new_vec3(double x, double y, double z)
{
    t_vec3  *v;

    v = ft_xalloc(sizeof(t_vec3));
    v->x = x;
    v->y = y;
    v->z = z;
    return (v);
}

t_vec3 *add_vec3_new(t_vec3 *a, t_vec3 *b)
{
    return new_vec3(
        a->x + b->x,
        a->y + b->y,
        a->z + b->z);
}

t_vec3 *add3_vec3_new(t_vec3 *a, t_vec3 *b, t_vec3 *c)
{
    return new_vec3(
        a->x + b->x + c->x,
        a->y + b->y + c->y,
        a->z + b->z + c->z);
}

t_vec3 *sub_vec3_new(t_vec3 *a, t_vec3 *b)
{
    return new_vec3(
        a->x - b->x,
        a->y - b->y,
        a->z - b->z);
}

t_vec3 *mult_vec3_vec3_new(t_vec3 *a, t_vec3 *b)
{
    return new_vec3(
        a->x * b->x,
        a->y * b->y,
        a->z * b->z);
}

t_vec3 *mult_vec3_new(t_vec3 *v, double b)
{
    return new_vec3(
        v->x * b,
        v->y * b,
        v->z * b);
}

t_vec3 *div_vec3_new(t_vec3 *v, double b)
{
    return mult_vec3_new(v, 1.0f / b);
}

t_vec3 *unit_vec3_new(t_vec3 *v)
{
    double is;

    is = 1 / sqrtf(
        (v->x) * (v->x)
        + (v->y) * (v->y)
        + (v->z) * (v->z));
    return mult_vec3_new(v, is);
}

t_vec3 *cross_vec3_new(t_vec3 *a, t_vec3 *b)
{
    return new_vec3(
        (a->y * b->z) - (a->z * b->y),
        (a->z * b->x) - (a->x * b->z),
        (a->x * b->y) - (a->y * b->x));
}

t_vec3 *negate_vec3_new(t_vec3 *v)
{
    return new_vec3(-v->x, -v->y, -v->z);
}
