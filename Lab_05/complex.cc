/*
* Lab 05: Complex Matrix Objects
* Faiza Yousuf
* ECE2036
*
*/

#include "complex.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <math.h>

using namespace std;

//Default Constructor, assigns 0 to data memebers and false to NaN
Complex::Complex()
{
	setComplex(0, 0);
	NaN = false;
}

//Paraterized Constructor, assigns 0 imaginary and input double real part
Complex::Complex(double r)
{
	setComplex(r, 0);
	NaN = false;
}

//Paraterized Constructor, assigns real and imaginary parts based on input
Complex::Complex(double r, double i)
{
	setComplex(r, i);
	NaN = false;
}

//Descructor - Currently unused
Complex::~Complex()
{
}

//Get Real Part of Complex Object
double Complex::getReal() {
	return real;
}

//Get Imaginary Part of Complex Object
double Complex::getImag() {
	return imag;
}

//Check if Compelx object is set to NaN
bool Complex::isNaN() {
	return NaN;
}

//Set Complex Object to NaN
void Complex::setNaN(bool nan) {
	this->NaN = nan;
}

//Set Real part of Complex Object
void Complex::setReal(double r) {
	this->real = r;
}

//Set Imaginary part of Complex Object
void Complex::setImag(double i) {
	this->imag = i;
}

//Set Whole Complex Object
void Complex::setComplex(double r, double i) {
	this->setReal(r);//call setReal()
	this->setImag(i);//call setImag()
}

//Display Complex Object in Polar Format
void Complex::displayPolar() {
	if (isnan(this->getReal()) || isnan(this->getImag()) || this->isNaN()) {//if the real or imaginary don't exist, or NaN is false
		cout << "NaN" <<endl;//can't calculate polar
		return;
	}
	double r = sqrt(pow(this->getReal(), 2) + pow(this->getImag(), 2));//radius=sqrt(real^2+imag^2)
	double theta = atan2(this->getImag(), this->getReal());//theta=arctan(imag/real)
	std::cout.precision(6);//set the number of decimals to 6, must use fixed
	cout << std::fixed;
	cout << r << " < " << theta <<endl;//print "r < theta"
}

//Display Complex Object in Rectangular Format
void Complex::displayRect() {
	cout << (*this) << endl;//assume object is already in rectangular
}

//Operator << Overloaded for Displaying using cout stream
std::ostream& operator<< (std::ostream & stream, const Complex & complex) {
	if (isnan(complex.real) || isnan(complex.imag) || complex.NaN) {//if the real or imaginary don't exist, or NaN is false
		stream << "NaN";//can't display any data
		return stream;
	}
	std::stringstream ss; //define the stringstream with the std namespace
	ss << std::fixed;//keep fixed
	ss << setprecision(6) << complex.real;//set to 6 decimal places, print real number (all in ss object)
	if(complex.imag != 0.0)//if the imaginary isn't 0
		ss << " + " << setprecision(6) << complex.imag << "j";//print + imaginary to 6 decimal places (all in ss object)
	stream << ss.str();//print all off ss as a string to the stream
	return stream;
}

//Operator + Overloaded for Addition
Complex Complex::operator+(Complex RHS)
{
	Complex result;//create result complex object
	result.setReal(this->getReal() + RHS.getReal());//add real values
	result.setImag(this->getImag() + RHS.getImag());//add imaginary values
	return(result);
}

//Operator - Overloaded for Subtration
Complex Complex::operator-(Complex RHS)
{
	Complex result;//create result complex object
	result.setReal(this->getReal() - RHS.getReal());//LHS real - RHS real
	result.setImag(this->getImag() - RHS.getImag());//LHS imag - RHS imag
	return(result);
}

//Operator ! Overload for Conjugting Complex Number
Complex Complex::operator!() {
	Complex result(this->getReal(), -this->getImag());//set imaginary value to a negative number (in the result object)
	return result;
}

//Operator * Overloaded for Multiplication
Complex Complex::operator*(Complex RHS) {
	Complex result;//create result object
	//simplification of distributive property
	result.setReal((this->getReal() * RHS.getReal()) - (this->getImag() * RHS.getImag()));//new real=(LHS real*RHS real)-(LHS imag*RHS imag)
	result.setImag((this->getReal() * RHS.getImag()) + (this->getImag() * RHS.getReal()));//new imag=(LHS real*RHS imag)-(LHS imag*RHS real)
	return(result);
}

//Operator / Overloaded for Division
Complex Complex::operator/(Complex RHS) {
	if (RHS.getImag() == 0 && RHS.getReal() == 0) {//if RHS imag and real are 0
		Complex c;//create new Complex object c
		c.setNaN(true);//set c's NaN to true
		return c;
	}
	Complex conjugate(RHS.getReal(), -RHS.getImag());//create new Complex object that the conjugate of the RHS
	Complex neum = *this * conjugate;//the numerator is the LHS*conjugate
	Complex den = RHS * conjugate;//denomenator is RHS*conjugate
	Complex result;//create result object
	result.setReal(neum.getReal() / den.getReal());//result's real=numerator real/denomenator real
	result.setImag(neum.getImag() / den.getReal());//result's imag=numerator imag/denominator imag
	return(result);
}
