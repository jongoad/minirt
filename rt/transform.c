#include "../includes/minirt.h"



/*

Steps to set up scene for raytracing:

1. Apply local transforms to each object (scale, rotation, translate)
	a. Scale must be applied to the objects using a simple float multiplication.
	b. Rotation is applied to the direction vector of the object
	c. Translation is applied to the origin point of the object

2. Apply world to camera transform to all objects in the scene to move camera in to position.






*/


void	world_to_camera(t_data *rt, t_obj* obj)
{
	t_vec3 cam_rot;
	t_vec3 cam_scale;
	t_vec3 cam_trans;

	


}


Matrix<T, N> & invert() 
{ 
    Matrix<T, N> mat; 
    for (unsigned column = 0; column < N; ++column) { 
        // Swap row in case our pivot point is not working
        if (m[column][column] == 0) { 
            unsigned big = column; 
            for (unsigned row = 0; row < N; ++row) 
                if (fabs(m[row][column]) > fabs(m[big][column])) big = row; 
            // Print this is a singular matrix, return identity ?
            if (big == column) fprintf(stderr, "Singular matrix\n"); 
            // Swap rows                               
            else for (unsigned j = 0; j < N; ++j) { 
                std::swap(m[column][j], m[big][j]); 
                std::swap(mat.m[column][j], mat.m[big][j]); 
            } 
        } 
        // Set each row in the column to 0  
        for (unsigned row = 0; row < N; ++row) { 
            if (row != column) { 
                T coeff = m[row][column] / m[column][column]; 
                if (coeff != 0) { 
                    for (unsigned j = 0; j < N; ++j) { 
                        m[row][j] -= coeff * m[column][j]; 
                        mat.m[row][j] -= coeff * mat.m[column][j]; 
                    } 
                    // Set the element to 0 for safety
                    m[row][column] = 0; 
                } 
            } 
        } 
    } 
    // Set each element of the diagonal to 1
    for (unsigned row = 0; row < N; ++row) { 
        for (unsigned column = 0; column < N; ++column) { 
            mat.m[row][column] /= m[row][row]; 
        } 
    } 
    *this = mat; 
    return *this; 
}


float **mat_inverse(float **m)
{
	float** m2;
	t_i i;

	i.x = 0;
	while (i.x < 4)
	{
		i.z = i.x;
		i.y = 0;
		if (m[i.x][i.x] == 0)
		{
			while ()
		}
	}

}