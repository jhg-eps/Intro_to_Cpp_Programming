#include "error_propagation.h"   // include the header file which created the class (data_analysis tool)

error_propagation::error_propagation()  // construct the default object, initialize the default variables
{
    x = 1;
    dx = 1;
    y = 1;           // initialize variables
    dy = 1;
    z = 1;
    dz = 1;
    percent_error = 1;
}

error_propagation::error_propagation(double x_1, double dx_1, double y_1, double dy_1, double z_1, double dz_1, double percent_error)   // construct a specific instance of the circle object
{
    x = x_1;
    dx = dx_1;
    y = y_1;           // initialize variables
    dy = dy_1;
    z = z_1;
    dz = dz_1;
    percent_error = percent_error_1;
}

error_propagation::div_error(double * x, double * dx, double * y, double * dy, double * z, double * dz)     // function prototypes are going down here.
{
        //first things first. z = x/y
        *z = *x/ *y;                         //z = x/y
        *dz = *z *(*dx/ *x + *dy/ *y);       //dz = z*(dx/x + dy/y)
}

error_propagation::mult_error(double * x, double * dx, double * y, double * dy, double * z, double * dz)     // function prototypes are going down here.
{
        //first things first. z = x/y
        *z = *x * *y;                         //z = x*y
        *dz = *z *(*dx/ *x + *dy/ *y);       //dz = z*(dx/x + dy/y)
}


error_propagation::add_error(double * x, double * dx, double * y, double * dy, double * z, double * dz)
{
       *z = *x +*y;
       *dz = *dx + *dy;
}

error_propagation::sub_error(double * x, double * dx, double * y, double * dy, double * z, double * dz)
{
       *z = *x - *y;
       *dz = *dx + *dy;
}
error_propagation::maximize_error(double x, double *dx, double y, double *dy, double percent_error)
{
            // for the x value
    if (*dx < percent_error*x) *dx = percent_error*x;
                //else if *dx >= percent_error*x, do nothing
    if (*dy < percent_error*y) *dy = percent_error*y;
                //else if *dy >= percent_error*y, do nothing
}

error_propagation::~error_propagation()
{
    //dtor
}
