// Joseph Garcia
// COS 220 Homework #6
// This program takes numberical score input and assigns a letter grade to the score based on the standard deviation of the scores entered.

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double mean(double values[], int n);
//PRE: n is the size of the array
//POST: return the arithmetic average of numbers in the array
double stddev(double values[], int n, double m);
//PRE: n is the size of the array, m is the mean 
//POST: return the standard deviation of numbers in array given the mean m
char grade(double score, double m, double s);
//POST: return letter grade for score with mean m and standard deviation s

int main()
{
	double values[8]={0};
	cout << setprecision(1);
	cout.setf(ios::fixed|ios::showpoint);
	int k =0;
	int WID1 = 3;
	cout << "Enter scores separated by blanks: ";
	for (k =0; k <8; k++)
	{
	cin >> values[k];
	}
	cout << "\n";
	cout << "Grade Scores by Student" << endl; 
	cout << "Score"  << setw(WID1+5) << "Grade" << endl;
	cout << "---------------------------";
	/////////////////////////////////////////////////////////////////////////////
	cout << "\n";
	for(k =0; k < 8 ;k++)
	{
		cout << values[k] << right << setw(WID1*3) << grade(values[k], mean(values, 8), stddev(values, 8, mean(values, 8))) << endl;
	}  
	cout << "----------------------------------------------\n"; 
	cout << "The Mean is " << mean(values, 8) << endl; //<< // dummyvalues here  this is showing score 1 (e.g.) 55/ divided by the array size (8);                            func 1 from the bottom will be used here
	cout << "The Standard Deviation is " << stddev(values, 8, mean(values, 8)) << endl; // << stddev(values, n, m) << endl; // << // dummyvalues here. << "\n\n";                  func 2 from the bottom will be used here
return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////// - this is the computation section.
double mean(double values[], int n)        // make a sum for values[]
//PRE: n is the size of the array
//POST: return the arithmetic average of numbers in the array
{
	double valuessum = 0;
	for(int k =0; k <8; k++)												
	{
		valuessum = valuessum + values[k];
	}
	return ( valuessum / 8.0);
}

double stddev(double values[], int n, double m)
//PRE: n is the size of the array, m is the mean 
//POST: return the standard deviation of numbers in array given the mean m
{		
	double stddevsum =0;
	double s =0;
	for(int k =0; k < 8; k++)
	{
		stddevsum = stddevsum + (( values[k] - m)*( values[k] - m));
	}									// s needs to be constantly overwritten, as it is changing all the time with the updates
	s = sqrt(stddevsum/8.0);
	return s;					// that is why i kept getting the square root of my final number.
}

char grade(double score, double m, double s)
//PRE: None
//POST: return letter grade for score with mean m and standard deviation s
{ 
	if (score < (m - 1.5* s)) return 'F';
	else if (score >= m - (1.5* s) && score < m - (0.5* s)) return 'D';     // thegrading function from below will go here
	else if (score >= m - (0.5* s) && score < m + (0.5* s)) return 'C';   // functions alone do not have to associate, but once in the main function,
	else if (score >= m + (0.5* s) && score < m + (1.5* s)) return 'B';	// make sure to relate them using specific parameters.
	else if  (score >= m + (1.5* s)) return 'A';
}
