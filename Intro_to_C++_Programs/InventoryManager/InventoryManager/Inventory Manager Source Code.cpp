// Joseph Garcia
// COS 220
// This program allows the user to display and update inventory
# include <iostream>
# include <iomanip>
# include <fstream>                // header files
# include <string>
using namespace std;

struct Productinfo
{
	string productname;
	int productcount;              // struct declaration
	double productprice;
};
int Esearch(Productinfo productarray [], int length, string s, char sign2, int inputval);
// PRE: len < 100 && len > 0
//POST: actual function to search through the array, find an index, and reassign the productcount
void Rremove(Productinfo productarray [], int &length, string s);                 // function prototypes
//PRE: Must be user input, length > 0 && length < 100
//POST:  Removes a product or says the product does not exist
void Iinsert(Productinfo productarray [], int &length, string s, int inputval, double funcprice);
//PRE: length > 0 && length < 100
//POST: Inserts a product or says it does not exist
double Ddisplay(Productinfo productarray [], int &length, double inventsum);
//PRE: There must be an incoming file and an array to input data to
//POST: The function displays the up-to-date inventory
ifstream fin;
int main()
{
	Productinfo productarray[100];    // array of structs with theoretical size
	int k =0;                // for-loop control variable initialization
	int len = 7;		// length of the subarray
	string productinput;      // string declaration for user input
	double inventorysum =0;  // inventory money value sum initialization
	double inputprice =0;    // double declaration for user input
	char sign ='0';         // initialization and declaration of sign (+,-)
	int inputvalue = 0;     // declaration and initialization of user stock amount input
	char characterchoice = '0';  // declaration and initialization of character selection input
	cout << "Select from menu: " << endl << "E - Edit" << endl << "I - Insert" << endl << "R - Remove" << endl <<
	"D - Display Table" << endl << "Q - Quit" << endl << endl;
	fin.open("inventory.txt");   // opening of in-file

	do                   // loop to display the user interface
	{
		cout << "Enter a valid code: E,I,R,D, or Q ";
		cin >> characterchoice;
		switch (characterchoice)
		{
            case 'D':
            cout << Ddisplay(productarray, len, inventorysum);
            cout << endl << endl;
            break;
            case 'E':
                cout << "Enter product: ";
                cin >> productinput;
                bool found = false;
                for (int k = 0; k < len && !found; k++)
                {
                if (productarray[k].productname == productinput) found=true;
                else (found = false);
                }
				if(found==true)
				{
                    cout << "Enter amount to add (+) or remove (-)";
                    cin >> sign >> inputvalue;
                    cout << "Item " << productinput << " has new amount " << Esearch(productarray,len, productinput, sign, inputvalue) << " in stock\n\n";
				}
                else (cout << "Item " << productinput << " is not found.\n\n");
            break;
	case 'Q':
	cout << "Program is Ending...\n\n";   // causes the program to close
	break;
	case 'R':
		cout << "Enter ID of product to remove: ";
		cin >> productinput;             // user input of desired product to remove
		Rremove(productarray, len, productinput); // function call
		cout << endl;
	break;
	case 'I':
		cout << "Enter new product ID, stock, and unit price: ";
		cin >> productinput >> inputvalue >> inputprice; // user input of product’s name, stock, price
		Iinsert(productarray, len, productinput, inputvalue, inputprice); // function call
		cout << endl;
	break;
	default:
		cout << "Enter a valid code- E,I,R,D, or Q: ";   // default line displayed by loop
		}
	} while(characterchoice !='Q');     // test condition that makes the loop eventually false

	return 0;

}
int Esearch(Productinfo productarray [],int length, string s, char sign2, int inputval)
// PRE: len < 100 && len > 0
//POST: actual function to search through the array, find an index, and reassign the productcount
	{
		int k =0;
		for (k =0; k < length; k++)
		{
			if(s == productarray[k].productname && sign2 =='+') return productarray[k].productcount = productarray[k].productcount + inputval;
			else if(s == productarray[k].productname && sign2 =='-') return productarray[k].productcount = productarray[k].productcount - inputval;
		}
	}
  void Rremove(Productinfo productarray [], int &length, string s)  // make sdure to include stock and count si that they can change as well.
//PRE: Must be user input, length > 0 && length < 100
//POST:  Removes a product or says the product does not exist
	{
	bool found = false;
	for (int k = 0; k < length && !found; k++)
		{
			if (productarray[k].productname == s) found = true;
		}
	if(found) cout << "Item " << s << " is removed.\n";
	else if(!found) cout << "Item " << s << " is not found.\n";
	for (int i =0; i < length; i++)
	  {
		  if( s == productarray[i].productname)
		  {
			  length--;
			  productarray[i].productname = productarray[length].productname;
			  productarray[i].productcount = productarray[length].productcount;             // new
			  productarray[i].productprice = productarray[length].productprice;               // new
		  }
	  }
}

  void Iinsert(Productinfo productarray [], int &length, string s, int inputval, double funcprice)
//PRE: length > 0 && length < 100
//POST: Inserts a product or says it does not exist
{
	bool found = false;
	for (int k = 0; k < length && !found; k++)
		{
			if (productarray[k].productname == s) found = true;
		}
	if(found) cout << "Item " << s << " already exists.\n";
	else if(!found)
	{
	  productarray[length].productname = s,
	  productarray[length].productcount = inputval,
	  productarray[length].productprice = funcprice,
	  length++,
	  cout << "Item " << s << " is inserted.\n";
	}
  }
double Ddisplay(Productinfo productarray [], int &length,double inventsum)
//PRE: There must be an incoming file and an array to input data to
//POST: The function displays the up-to-date inventory
{
	int WID1 = 20;
	cout << "ID" << setw(WID1+1) << "Stock" << setw(WID1+4) << "Unit Price\n";
	for(int k =0; k < length; k++)
		{
		fin >> productarray[k].productname >> productarray[k].productcount >> productarray[k].productprice;
		cout << left << setw(WID1)  << productarray[k].productname << left << setw(WID1) << productarray[k].productcount << setw(WID1) << productarray[k].productprice << endl;
		inventsum = inventsum + (productarray[k].productcount * productarray[k].productprice);
		}
	cout << endl << "Total Inventory: ";
	return inventsum;
}
