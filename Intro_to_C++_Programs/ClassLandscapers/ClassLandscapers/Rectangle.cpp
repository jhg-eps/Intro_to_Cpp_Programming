#include "Rectangle.h"
// actual executable source code goes here.
Rectangle::Rectangle(void)
{
}

double length = 1;
double width = 1;

void Rectangle::setlength (double len)
{
	length = len;
}
void Rectangle::setwidth (double wid)
{
	width = wid;
}
double Rectangle::area1()                          // area for the large grass rectangle
{
	return length * width;
}
double Rectangle::area2()                        // area for the smaller gravel rectangle
{
	return 0.5 * length * 0.5 * width;
}
double Rectangle::getlength ()
{
	return length;                              // I will have to make a return statement for the length and width of the smaller rectangle
}												
double Rectangle::getwidth ()
{
	return width;
}
double Rectangle::getwidth2 ()
{
	return 0.5 * width;
}
double Rectangle::getlength2 ()
{
	return 0.5 * length;
}

Rectangle::~Rectangle(void)
{
}
