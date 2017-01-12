#pragma once
// function prototypes and data prototypes go here
class Rectangle
{
public:
	Rectangle(void);
	double getlength ();
	double getwidth ();  // these two copy out data that I input
	double area1 ();
	double area2 ();
	void setlength (double len);          
	void setwidth (double wid); 
	double getwidth2 ();
	double getlength2 ();
	~Rectangle(void);

private:
 double length;
 double width;
	
};
