// Joseph Garcia
// COS 220 Assignment #8
// Program can search state by flower or flower by state

# include <iostream>
# include <fstream>
# include <iomanip>
# include <string>
using namespace std;

struct StateFlower
{
	string statename;                         // struct declaration and building
	string flowername;
};

// function prototypes
void selsort (StateFlower namearray[], int sublength); 
//Pre: 0 <= sublength <= 50 (array size)
//Post: sorts the array in alphabetical order
void swap( StateFlower &x, StateFlower &y);
//Pre: variables must be of the same data type as their main function counterparts (structs)
//Post: Switches the position of structs within the array
void binsearch(StateFlower namearray[], int sublength, string stateinput, int index);
//Pre: 0 <= sublength <= 50 (array size)
//Post: returns the array index of the item to match with input
ifstream fin;
int main ()
{
	int length = 50;                                       // declaration of array length
	int index =0;
	string ignorit;// declaration/initialization of index parameter
	char characterchoice =0;                               // declaration of character variable
	string inputstate;                                     // declaration of state/ partial state input
	string inputflower;                                    // declaration of flower/ partial flower input
	fin.open("stateflowers.txt");						   // opening the file
	StateFlower namearray[50];                             // declaration of the array
		for(int k =0; k < 50; k++)
		{
		getline(fin, namearray[k].statename, '\n');         // retrieval of data and assignment into the array of structs
		getline (fin, namearray[k].flowername, '\n');
		}
	selsort (namearray, 50);                                // calling of the sorting function
	cout << "Enter D to display all\n" << "Enter R to report flower of given state\n" 
	<< "Enter S to report list of states/flowers by partial state entry\n" << "Enter F to report list of states/flowers by partial flower entry\n\n\n";
do                                               // do loop for user input
{
	cin >> characterchoice;                               // input of character variable
	switch (characterchoice)
	{
	case 'D':
	{		
		
		for(int k =0; k < 50; k++)
		{
		cout << left << setw(20) << namearray[k].statename << left << namearray[k].flowername << endl;  // displays the ordered array
		}
	}
	break;
	case 'R':
	{
		cout << "Enter State name: ";
		getline(cin, ignorit);                                // ignores the white space
		getline(cin, inputstate);                                    // user input of full state name
		binsearch(namearray, 50, inputstate, index);          // call of binary search function
		cout << endl;
	}
	break;
	case 'S':
	{                                        
		cout << "Enter partial state name: ";
		cin >> inputstate;                                    // user input of partial state name
		bool found = false;                                   // initialization of boolean testing condition
		for (int k =0; k < 50; k++)
		{
			if (namearray[k].statename.find(inputstate) != -1)                     // sees if the input string matches any substrings in the array
			found = true,                                                          // if there is a match, the condition is true, displaying the match's
			cout << left << setw(20) << namearray[k].statename << left << namearray[k].flowername << endl;
		}
		if (found !=true) cout << "There are no states containing string " << inputstate << endl; // display if no match is found 
		cout << endl;
	}
	break;
	case 'F':
	{
		cout << "Enter partial flower name: ";
		cin >> inputflower;                               // input of partial flower name
		bool found = false;                               // initialization of boolean testing conditions
		for (int k =0; k < 50; k++)
		{
			if (namearray[k].flowername.find(inputflower) != -1)   // sees if the input string matches any substrings in the array
			found = true,                                          // if there is a match, the condition is true, displaying the match's
			// full state name and flower
			cout << left << setw(20) << namearray[k].statename << left << namearray[k].flowername << endl;
		}
			if(found != true) cout << "There are no flowers containing string " << inputflower << endl << endl;
			cout << endl;                                   // display if no match is found
	}
	break;
	case 'Q':
		cout << "Program is ending...\n\n";                   // Quits out of the program
	break;
}
} while (characterchoice !='Q');                           // test condition that quits the program when characterchoice is 'Q'

return 0;                                                  // for successful program execution
}

void swap(StateFlower &x, StateFlower &y)                                // actual swapping function 
//Pre: variables must be of the same data type as their main function counterparts (structs)
//Post: Switches the position of structs within the array
{
	StateFlower temp;
	temp = x;
	x = y;
	y = temp;
}
void selsort (StateFlower namearray [], int sublength)                   // actual selection sort function
//PRE: 0 < sublength <= arraylength
//POST: Values in the array are sorted in ascending order.
{
	int ct1 =0;
	int ct2 =0;
	int minimdex;
	for (int ct1 =0; ct1 < sublength - 1; ct1++)              
	{
	minimdex =ct1;
	for (ct2 = ct1 +1; ct2 < sublength; ct2++)
		if(namearray[ct2].statename < namearray[minimdex].statename) minimdex = ct2;
			swap(namearray[minimdex], namearray[ct1]);
	}
}
void binsearch(StateFlower namearray[], int sublength, string stateinput, int index)  // actual binary search function
//Pre: 0 <= sublength <= 50 (array size)
//Post: returns the array index of the item to match with input 
{
	int first =0;
	int last = sublength -1;
	bool found = false;
	while(!found && last >= first)
	{
		index = (first + last)/2;
		if (stateinput==namearray[index].statename) found = true, cout << "State " << stateinput << " has flower " << namearray[index].flowername << endl;
		else if(stateinput < namearray[index].statename) last = index -1;
		else first = index +1;
	}
	if(!found) cout << "State " << stateinput << " is not found.\n";
}