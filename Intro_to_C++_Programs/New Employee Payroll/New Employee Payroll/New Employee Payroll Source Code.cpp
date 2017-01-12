//Joseph Garcia
//COS 220 Assignment 4
//This program takes a payroll file and calculates the payroll.
#include <fstream> 
#include <iomanip>
#include <iostream>
using namespace std;
const int WID1 = 3;
const int WID2 = 10;

int main()
{
	int ein;
	double payrate = 0;
	int totalhours = 0;
	int reghours = 0;
	double totalpay = 0;
	double otpay = 0;
	int otreceivers = 0;
	int otreceiversum = 0;
	double otpaysum = 0;
	double othours = 0;
	double regpay = 0;
	double bottomsum = 0;
	ifstream fin;
	fin.open("New Employee Payroll Input.txt");
	if(fin.fail()) 
		cout << "ERROR";
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ofstream fout;
	fout.open("payrollout.txt");
	cout << setprecision(2) << fixed << right;
	cout << "Payroll Report By Joseph Garcia" << "\n\n";
	cout << "ID" << setw(WID1+2)<< "Pay" << setw(WID2) << "Regular" << setw(WID2)<< "Overtime" << setw(WID2) << "Regular" << setw(WID2) <<
	"Overtime" << setw(WID2) << "Total" << endl;
	cout << setw(WID1+5) << "Rate" << setw(WID2-3) << "Hours" << setw(WID2-1) << "Hours" << setw(WID2-1) << "Pay" << setw(WID2-1) << "Pay" << setw(WID2+3)
	<< "Pay" << endl;
	cout << "---------------------------------------------------------\n";
	// Display section is below.
	fin >> ein;
	fin.ignore(30);
	fin >> totalhours >> payrate;
	while (!fin.fail())
	{
			int reghours = totalhours - (totalhours - 40); 
			int othours = totalhours - 40;
			double regpay = (totalhours - (totalhours - 40))*payrate;
			double otpay = (totalhours - 40)*1.5*payrate;
			double totalpay = ((totalhours - (totalhours - 40))*payrate)+ (totalhours - 40)*1.5*payrate;
		if(otpay > 0)                          // Make sure to have a spot for calculating the overtime pay.
		{
			otpaysum = otpaysum + otpay;
		}
		if (totalhours > 40) //
		{
			otreceivers = 0;
			cout << ein << " " << payrate << "    " << reghours << "     " << othours << "        " << 
			regpay << "   " << otpay << "      " << totalpay << endl;
			otreceivers ++;
			otreceiversum = otreceiversum + otreceivers;
			bottomsum = bottomsum + totalpay;
		} 
		else if (totalhours <=40)
		{
			double totalpay = (totalhours*payrate);		
			cout << ein << " " << payrate << "    " << totalhours << "     " << 0 << "         " << totalpay <<
			"   " << 0.00 << "        " << totalpay<< endl;
			bottomsum = bottomsum + totalpay;
		}
		fin >> ein;
		fin.ignore(31);
		fin >> totalhours >> payrate;
	}
	cout << "---------------------------------------------------------\n";
	cout << setw(WID1*19) << bottomsum << "\n";
	cout << "Number of employees receiving overtime: " << otreceiversum << "\n";
	cout << "Sum of Overtime: " << otpaysum << "\n";
	return 0;
}

