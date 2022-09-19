#include "minirt.h"

t_vec3  vec3(double x, double y, double z)
{
    t_vec3  v;

    v.x = x;
    v.y = y;
    v.z = z;
    return (v);
}

double invsqrt(double y)
{
    double      yhalf;
    long long   i;

    yhalf = (double)0.5F * y;
    i = *(long long*)( &y );
    i = 0x5fe6ec85e7de30daLL - (i >> 1);
    // For floats:
    // i = 0x5f3759df - (i >> 1);
    y = *(double*)(&i);
    y = y * ((double)1.5F - yhalf * y * y);
    return y;
}

t_vec3 add_vec3(t_vec3 a, t_vec3 b)
{
    return vec3(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z);
}

t_vec3 add3_vec3(t_vec3 a, t_vec3 b, t_vec3 c)
{
    return vec3(
        a.x + b.x + c.x,
        a.y + b.y + c.y,
        a.z + b.z + c.z);
}

double  dot_vec3(t_vec3 a, t_vec3 b)
{
    return (a.x * b.x)
        + (a.y * b.y)
        + (a.z * b.z);
}

t_vec3 sub_vec3(t_vec3 a, t_vec3 b)
{
    return vec3(
        a.x - b.x,
        a.y - b.y,
        a.z - b.z);
}

t_vec3 mult_vec3_vec3(t_vec3 a, t_vec3 b)
{
    return vec3(
        a.x * b.x,
        a.y * b.y,
        a.z * b.z);
}

t_vec3 mult_vec3(t_vec3 v, double b)
{
    return vec3(
        v.x * b,
        v.y * b,
        v.z * b);
}

t_vec3 div_vec3(t_vec3 v, double b)
{
    return mult_vec3(v, 1.0f / b);
}

double length_vec3(t_vec3 v)
{
    return sqrtf(
        (v.x) * (v.x)
        + (v.y) * (v.y)
        + (v.z) * (v.z));
}

t_vec3 unit_vec3(t_vec3 v)
{
    double is;

    is = invsqrt(
        (v.x) * (v.x)
        + (v.y) * (v.y)
        + (v.z) * (v.z));
    return mult_vec3(v, is);
}

t_vec3 cross_vec3(t_vec3 a, t_vec3 b)
{
    return vec3(
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x));
}

t_vec3 negate_vec3(t_vec3 v)
{
    return vec3(-v.x, -v.y, -v.z);
}

double cos_vec3(t_vec3 a, t_vec3 b)
{
    return dot_vec3(a, b) / (length_vec3(a) * length_vec3(b));
}
