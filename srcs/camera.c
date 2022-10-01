#include "minirt.h"


/* Steps for applying transforms and camera position:

1. Apply scale, rotation and translation to each object
	- Scale is applied directly to the object values (radius, width, height)
		- Scale does not apply to planes (they are infinite is size)
	- Rotation is applied to orientation vectors
		- If the object is a sphere, do not apply rotation as it is irrelevant (there is no orientation vector)
	- Translation is applied to the origin point of each object.

2. 	Create inverse matrix for camera, then apply to all objects in scene to create final setup for raytracing
	- Cannot use a compound matrix, must create for rotation, translation and scale seperately

*/


/* Apply transforms to sphere */
void apply_transform_sp(t_data *rt, t_obj *cur)
{
	float **mat;
	t_vec3 res;

	cur->c_radius = cur->radius * cur->scale;			/* Apply scale to radius */
	mat = matrix_translate(cur->trans);					/* Apply translation to origin point */
	res = mat_mult_vec3(&cur->center, mat);

	cur->c_center.x = res.x;
	cur->c_center.y = res.y;
	cur->c_center.z = res.z;
	cur->c_center.w = res.w;
	
}


/* Apply current transforms to each object */
void	apply_transform_obj(t_data *rt)
{
	t_i i;

	i.x = 0;
	while (i.x < rt->nb_objs)
	{
		//Call correct transform function to apply transform to avoid using if/else statements
		i.x++;
	}
}

/* Apply camera transform to each object in scene */
void	apply_transform_cam()
{

}

/* Calculate inverse matrices to apply camera transform to scene */
void	calculate_transform_cam()
{

}




 
void	mat_inverse()
{
	int mat[3][3], i, j;
	float determinant = 0;
	printf("Enter elements of matrix row wise:\n");
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			scanf("%d", &mat[i][j]);
	printf("\nGiven matrix is:");
	for(i = 0; i < 3; i++){
	printf("\n");
	for(j = 0; j < 3; j++)
	printf("%d\t", mat[i][j]);
	}
	//finding determinant
	for(i = 0; i < 3; i++)
		determinant = determinant + (mat[0][i] * (mat[1][(i+1)%3] * mat[2][(i+2)%3] - mat[1][(i+2)%3] * mat[2][(i+1)%3]));
	printf("\n\ndeterminant: %f\n", determinant);
	printf("\nInverse of matrix is: \n");
	for(i = 0; i < 3; i++){
	for(j = 0; j < 3; j++)
	printf("%.2f\t",((mat[(j+1)%3][(i+1)%3] * mat[(j+2)%3][(i+2)%3]) - (mat[(j+1)%3][(i+2)%3] * mat[(j+2)%3][(i+1)%3]))/ determinant);
	printf("\n");

	
	return 0;
	}
}
