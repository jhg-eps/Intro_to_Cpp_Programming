// Joseph Garcia
// Carol Roberts COS 220
// Reads the names and scores from a cooking competition's results, and reorders the scores, determining the winner

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void swap (double& v1, double &v2);                        //
void sort (double& v1, double& v2, double& v3);
double final (double v1, double v2, double v3);

int main ()
{
	string lastname;
	string firstname;
	string winnerslast;
	string winnersfirst;
	double score1=0, score2=0, score3=0;
	int WID1 = 10;
	int WID2 = 12;
	char lineender = ' ';
	cout.precision(2);
	cout.setf(ios::fixed|ios::right);
	double Maxscore = 0;
	ifstream fin;
	fin.open("CookingCompResults.txt");
	double weightedscore = 0;
	if (fin.fail())
	{
		cout << " Unable to Read File " << endl;
	}
	cout << "Cooking Contest by Joseph Garcia\n\n" << "Name" << setw(WID2*2-1) << "Score 1" << setw(WID1) << 
"Score 2" << setw(WID1) << "Score 3" << setw(WID1+4) << "Final Score" << endl;
	cout << "-------------------------------------------------------------\n";
	getline(fin, lastname,',');
	while (!fin.fail())
	{	
		fin >> firstname >> score1 >> score2 >> score3;
		fin.get(lineender);
		sort(score1, score2, score3);
		weightedscore = final(score1, score2, score3);
		cout << left << setw(WID1) << firstname << left << setw(WID1) << lastname << left << setw(WID1) << score1 << left << setw(WID1) 
		<< score2 << left << setw(WID1) << score3 << weightedscore << endl;
		if (weightedscore > Maxscore)
		{
			Maxscore = weightedscore;
			winnerslast = lastname;
			winnersfirst = firstname;
		}
		getline(fin, lastname, ',');
	}
	for(int c =0; c < 61; c++)
	{
		cout << "-";
	}
	cout << "\n\n";
	cout << "The winner is " << winnersfirst << " " << winnerslast << " " << "with a score of " << Maxscore << endl << endl;
	return 0;
}

void swap (double &v1, double &v2)
//POST: exchange the values in v1 and v2
{
	double namerelater =0;
	namerelater = v1;
	v1 = v2;
	v2 = namerelater;
}
void sort (double &v1, double& v2, double& v3)    
//POST: Reorder values such that v1 <= v2 <= v3
{
	int WID1 = 10;
	if (v2 < v1) swap (v2, v1);
	if (v3 < v2) swap (v3, v2);
	if (v1 > v2) swap (v2, v1);
}
double final (double v1, double v2, double v3)
// PRE: v1 <= v2 <= v3
// POST: Returns the weighted sum defined with the formula below
{
return  ((v1)/2) + v2 + ((v3)/2);
}

