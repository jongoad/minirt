#include "minirt.h"

t_vec3  vec3(double x, double y, double z)
{
    t_vec3  v;

    v.x = x;
    v.y = y;
    v.z = z;
    return (v);
}

t_vec3  add_vec3(t_vec3 a, t_vec3 b)
{
    return vec3(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z);
}

t_vec3  add3_vec3(t_vec3 a, t_vec3 b, t_vec3 c)
{
    return vec3(
        a.x + b.x + c.x,
        a.y + b.y + c.y,
        a.z + b.z + c.z);
}

double   dot_vec3(t_vec3 a, t_vec3 b)
{
    return (a.x * b.x)
        + (a.y * b.y)
        + (a.z * b.z);
}

t_vec3  sub_vec3(t_vec3 a, t_vec3 b)
{
    return vec3(
        a.x - b.x,
        a.y - b.y,
        a.z - b.z);
}

t_vec3  mult_vec3_vec3(t_vec3 a, t_vec3 b)
{
    return vec3(
        a.x * b.x,
        a.y * b.y,
        a.z * b.z);
}

t_vec3  mult_vec3(t_vec3 v, double b)
{
    return vec3(
        v.x * b,
        v.y * b,
        v.z * b);
}

t_vec3  div_vec3(t_vec3 v, double b)
{
    if (b == 0)
        return (v);
    return mult_vec3(v, 1.0f / b);
}

double  length_vec3(t_vec3 v)
{
    return sqrtf(
        (v.x) * (v.x)
        + (v.y) * (v.y)
        + (v.z) * (v.z));
}

t_vec3  unit_vec3(t_vec3 v)
{
    double is;

    is = 1 / sqrtf(
        (v.x) * (v.x)
        + (v.y) * (v.y)
        + (v.z) * (v.z));
    return mult_vec3(v, is);
}

t_vec3  cross_vec3(t_vec3 a, t_vec3 b)
{
    return vec3(
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x));
}

t_vec3  mean_vec3( t_vec3 a, t_vec3 b )
{
    return vec3(
        (a.y + b.z) * 0.5F,
        (a.z + b.x) * 0.5F,
        (a.x + b.y) * 0.5F);
}

t_vec3  lerp_vec3( t_vec3 a, t_vec3 b, float factor )
{
    t_vec3  diff;
    
    if (factor <= 0.0F || factor > 1.0F)
    {
        return vec3(a.x, a.y, a.z);
    }
    diff = sub_vec3(b, a);
    return add_vec3(a, mult_vec3(diff, factor));
}

t_vec3  negate_vec3(t_vec3 v)
{
    return vec3(-v.x, -v.y, -v.z);
}

double  cos_vec3(t_vec3 a, t_vec3 b)
{
    return dot_vec3(a, b) / (length_vec3(a) * length_vec3(b));
}
