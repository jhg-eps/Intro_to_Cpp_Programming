#ifndef ERROR_PROPAGATION_H
#define ERROR_PROPAGATION_H

class error_propagation    // declaring the error_propagation class
{
    public:
        double x;
        double dx;
        double y;            // create variables which can be "modified"
        double dy;
        double z;
        double dz;
        double percent_error;

        error_propagation()                  // constructing a default error propagation analysis tool (object)
        {
            x =1;
            dx = 1;
            y = 1;
            dy = 1;
            z = 1;
            dz = 1;
            percent_error = 1;
        }
        error_propagation(double x, double dx , double y , double dy , double z , double dz );  // put the specifics of what the object can intake

        void div_error(double x , double dx, double y, double dy, double * z, double * dz)     // function prototypes are going down here.
        {
            *z = (double)x/(double)y;                        //z = x/y
            *dz = (*z) *((double)dx/(double)x + (double)dy/(double)y);       //dz = z*(dx/x + dy/y)
            std::cout << *z << " " << *dz << std::endl;
        }

        void mult_error(double x , double dx, double y, double dy, double * z, double * dz)     //FIX THESE OTHER MATH FUNCTIONS!!!!!
        {
            //first things first. z = x/y
            *z = (double)x * (double)y;                         //z = x*y
            *dz = (*z) *((double)dx/(double)x + (double)dy/(double)y);       //dz = z*(dx/x + dy/y)
            std::cout << *z << " " << *dz << std::endl;
        }


        void add_error(double x , double dx, double y, double dy, double * z, double * dz)
        {
            *z = x + y;
            *dz = dx + dy;
            std::cout << *z << " " << *dz << std::endl;
        }

        void sub_error(double x , double dx, double y, double dy, double * z, double * dz)
        {
            *z = x - y;
            *dz = dx + dy;
            std::cout << *z << " " << *dz << std::endl;
        }

        void maximize_error(double x, double *dx, double y, double *dy, double percent_error)
        {
            // for the x value
            if (*dx < percent_error*x) *dx = percent_error*x;
                //else if *dx >= percent_error*x, do nothing
            if (*dy < percent_error*y) *dy = percent_error*y;
                //else if *dy >= percent_error*y, do nothing
        }
    private:
     //   void div_error();
     //   void mult_error();
     //   void add_error();           // function declarations
     //   void sub_error();
};

#endif // ERROR_PROPAGATION_H
