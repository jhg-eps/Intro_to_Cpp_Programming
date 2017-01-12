//Joseph Garcia
//COS 220 Assignment 3
//This program does statistics on some packages
#include <iostream>
#include <iomanip>
using namespace std;
	
int main()
{
	cout.setf(ios::fixed | ios::showpoint | ios::right);
	cout.precision(2);
	const double Cat1cost = 2.75;
const double Cat2cost = 4.50;
const double Cat3cost = 6.75;       
const double Cat4cost = 8.25;                             
const int Cat1 = 1;
const int Cat2 = 2;
const int Cat3 = 3;
const int Cat4 = 4;
	double Cattype;
	double catcost;
	double packageweight; 
	double weighttotal = 0;	                                         //make sure to initialize these variables to zero
	double packagesum = 0;
	double weightsum = 0;
	double freighttotal = 0;
	double minweight = 10;		
	int cat1sum = 0;                    
	int cat2sum = 0;
	int cat3sum = 0;
	int cat4sum = 0;
	int Hist1count = 0;
	int Hist2count = 0;
	int Hist3count = 0;
	int Hist4count = 0;
	int Hist1sum = 0;
	int Hist2sum = 0;
	int Hist3sum = 0;
	int Hist4sum = 0;
	double maxweight = 0;
	int cat1count = 0;					
	int cat2count = 0;
	int cat3count = 0;
	int cat4count = 0;
	
	cout << "Enter package weights (0 to quit): ";
	cin >> packageweight;
	cout << "\n";
	cout << "Category" << setw(20) << "Weight (Lbs.)" << setw(14) << "Shipping" << endl;
	cout << "-----------------------------------------------\n";
	while (packageweight !=0)
	{
	if(packageweight < minweight)
	minweight = packageweight;
	if(packageweight > maxweight)
	maxweight = packageweight;
	if(packageweight > 0 && packageweight <= 2.0) (Cattype = Cat1) && (catcost = Cat1cost), freighttotal = freighttotal + catcost;
	else if(packageweight > 2.0 && packageweight <= 5.0) (Cattype = Cat2) && (catcost = Cat2cost), freighttotal = freighttotal + catcost; 		
	else if(packageweight > 5.0 && packageweight <= 8.0) (Cattype = Cat3) && (catcost = Cat3cost), freighttotal = freighttotal + catcost; 
	else if(packageweight > 8.0 && packageweight <= 10.0) (Cattype = Cat4) && (catcost = Cat4cost), freighttotal = freighttotal + catcost; 
	else if (packageweight = 0) (Cattype = 0) && (catcost = 0), freighttotal = freighttotal + catcost;
	if(packageweight > 0 && packageweight <= 2.0)
	{
		cat1count ++;
		cat1sum = cat1sum + cat1count;
	}
	else if(packageweight > 2.0 && packageweight <= 5.0) 
	{
		cat2count ++;
		cat2sum = cat2sum + cat2count;
	}
	else if(packageweight > 5.0 && packageweight <= 8.0) 
	{
		cat3count ++ ;
		cat3sum = cat3sum + cat3count;
	}
	else if(packageweight > 8.0 && packageweight <= 10.0) 
	{
		cat4count ++;
		cat4sum = cat4sum + cat4count;
	}
	packagesum++;
	cout << Cattype << setw(10) << packageweight << setw(15) << catcost << endl;
	weightsum = weightsum + packageweight;
	cin >> packageweight;
	}
	cout << "\n";
	cout << "Total number of packages:" << setw(17) << packagesum << endl;
	if(weightsum !=0)
	{
	cout << "Average package weight: " << setw(18) << (weightsum)/ (packagesum) << endl;
	cout << "Total Shipping Charges: " << setw(19) << freighttotal << endl;
	cout << "Lightest Weight: " << setw(25)<< minweight << endl;
	cout << "Heaviest weight: " << setw(25) << maxweight << endl;
	cout << "Histogram of Category counts:\n-----------------------------------------------\n";
	cout << "1" << setw(1);
	for(Hist1sum = 0; Hist1sum < cat1count; Hist1sum++)
	{
		cout << "*";
	}
	cout << "\n";
	cout << "2" << setw(1);
	for(Hist2sum = 0; Hist2sum < cat2count; Hist2sum++)
	{
		cout << "*";
	}
	cout << "\n";
	cout << "3" << setw(1);
	for(Hist3sum = 0; Hist3sum < cat3count; Hist3sum++)
	{
		cout << "*";
	}
	cout << "\n";
	cout << "4" << setw(1);
	for(Hist4sum = 0; Hist4sum < cat4count; Hist4sum++)
	{
		cout << "*";
	}
	cout << "\n\n";
	// testing some stuff here

	if(5)
	{
	}

	return 0;
	}
}

