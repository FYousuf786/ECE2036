/*
* Lab 05: Complex Matrix Objects
* Faiza Yousaf
* Course Code: ECE2036
*
*/

#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

/*
* Class Complex
* Manipultes Complex Object
*/
class Complex
{
public:
	//Default Constructor, assigns 0 to data memebers and false to NaN
	Complex();
	
	//Paraterized Constructor, assigns 0 imaginary and input double real part
	Complex(double r);
	
	//Paraterized Constructor, assigns real and imaginary parts based on input
	Complex(double r, double i);
	
	//Descructor - Currently unused
	~Complex();
	
	//Get Real Part of Complex Object
	double getReal();
	
	//Get Imaginary Part of Complex Object
	double getImag();
	
	//Check if Complex object is set to NaN
	bool isNaN();
	
	//Set Complex Object to NaN
	void setNaN(bool nan);
	
	//Set Real part of Complex Object
	void setReal(double r);
	
	//Set Imaginary part of Complex Object
	void setImag(double i);
	
	//Set Whole Complex Object with appropriate real and imaginary
	void setComplex(double r, double i);
	
	//Display Complex Object in Polar Format
	void displayPolar();
	
	//Display Complex Object in Rectangular Format
	void displayRect();
	
	//Operator + Overloaded for Addition
	Complex operator+(Complex RHS);
	
	//Operator - Overloaded for Subtration
	Complex operator-(Complex RHS);
	
	//Operator * Overloaded for Multiplication
	Complex operator*(Complex RHS);
	
	//Operator / Overloaded for Division
	Complex operator/(Complex RHS);
	
	//Operator ! Overload for Conjugating Complex Number
	Complex operator!();
	
	//Operator << Overloaded for Displaying using cout stream
	friend std::ostream& operator<< (std::ostream &, const Complex &);

private:
	//Stores the real part of object
	double real;
	
	//Stores the imaginary part of object
	double imag;
	
	//Stores information wheather number is set to NaN
	bool NaN;
};

#endif
