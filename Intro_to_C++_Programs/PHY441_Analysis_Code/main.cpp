# include <iostream>
# include <fstream>
# include "error_propagation.h"
#include <string>

using namespace std;

//function prototype
void appropriate_math(int input, double percent_error);

int main(void)
{
    double percent_error;
    cout << "Welcome to the Error Analysis Calculator. Please select one of the following options\n";
    cout << "1: Multiplication (X*Y = Z)\n2: Division (X/Y = Z)\n3: Addition(X + Y = Z)\n4: Subtraction (X-Y = Z)\n\n";
    cout << "Make sure to enter X and then Y\n\n";
    cout << "What is the percent error (e.g. 0.02) in the measurements you are studying? ";
    cin >> percent_error;  // this actually is in the form %/100, so 2% = 0.02.
    int input = 6;
    do
    {
        cin >> input;
        appropriate_math(input,percent_error);
    }
    while(input !=0);

return 0;
}

// function implementation
void appropriate_math (int input, double percent_error)
{
    double x, x_unc, y_unc, y, z, z_unc;
    error_propagation tool;
    cout << "Enter X, dX, Y, and dY:";
    cin >> x >> x_unc >> y >> y_unc;
    if(input == 1)
    {
        cout << "You are doing multiplication right now.\n";
        tool.maximize_error(x,&x_unc,y,&y_unc,percent_error);
        cout << "x = " << x << " dx = " << x_unc<< " y = " << y << " dy = " << y_unc << endl;
        tool.mult_error(x,x_unc,y,y_unc,&z,&z_unc);
    }
    else if(input == 2)
    {
        cout << "You are doing division right now.\n";
        tool.maximize_error(x,&x_unc,y,&y_unc,percent_error);
        cout << "x = " << x << " dx = " << x_unc<< " y = " << y << " dy = " << y_unc << endl;
        tool.div_error(x,x_unc,y,y_unc,&z,&z_unc);
    }
    else if(input == 3)
    {
        cout << "You are doing addition right now.\n";
        tool.maximize_error(x,&x_unc,y,&y_unc,percent_error);
        cout << "x = " << x << " dx = " << x_unc<< " y = " << y << " dy = " << y_unc << endl;
        tool.add_error(x,x_unc,y,y_unc,&z,&z_unc);
    }
    else if(input == 4)
    {
        cout << "You are doing subtraction right now.\n";
        tool.maximize_error(x,&x_unc,y,&y_unc,percent_error);
        cout << "x = " << x << " dx = " << x_unc<< " y = " << y << " dy = " << y_unc << endl;
        tool.sub_error(x,x_unc,y,y_unc,&z,&z_unc);
    }
}
