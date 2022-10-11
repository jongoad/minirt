#include "minirt.h"



//FOV is the "scale" value of the camera??
/*
Changing the dimensions of the viewing plane while keeping the distance from the viewing point
to the plane the same will change the angle, and thus the amount of the scene that can be created.

The actual pixel size of the screen remains the same, but there is either more or less of the scene squeezed
into the same space.

This also will increases or decreases the distance between each ray that is cast, resulting in a change in 
distortion as the angle between each ray changes.



FOV Coord Examples:

Assuming that z-offset of camera is always 1:

z-offset = 1;
view plane size = 2;
FOV = 90;




To calculate focal legth

for non normalized view plane:
f = (w/2) / tan(FOV/2) = (h/2) / tan(FOV/2)

for normalized view plane:
f = 1/tan(FOV/2)


*/
