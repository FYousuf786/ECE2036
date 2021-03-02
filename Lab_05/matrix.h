/* 
* Lab 05: Complex Matrix Objects
* Faiza Yousaf
* Course Code: ECE2036
* 
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "complex.h"
#include <string>

#define MATRIX_FIELD 30

/*
* Class Matrix
* Manipulates Complex Matrix Objects
*/
class Matrix
{
	//Operator << overloaded to display matrix using cout stream
	friend std::ostream& operator<< (std::ostream &, const Matrix &);
	
	//Operator * overloaded to multiply Complex with Matrix
	friend Matrix operator*(Complex, Matrix &);
	
	//Operator * overloaded to multiply Matrix with Complex
	friend Matrix operator*(Matrix &, Complex);
	
	
public:
	//Constructor to create a matrix object based on the rows and columns input
	Matrix(int r, int c);
	
	//Copy Constructor to create deep copy of a matrix object
	Matrix(const Matrix & m);
	
	//Destructor to deallocate memory specified by new operator
	~Matrix();
	
	//Get Number of Rows
	int getRows();
	
	//Get Number of Cols
	int getCols();
	
	//Print Matrix
	void printMatrix();
	
	//Transpose the Matrix
	void transpose();
	
	//Assignment Opertor Overloaded for deep copy
	const Matrix& operator=(const Matrix & RHS);
	
	//Parenthesis Opertor Overload for indexing matrix (Constant Objects) (reading)
	const Complex& operator()(int row, int col) const;
	
	//Parenthesis Opertor Overload for indexing matrix (Assigning Values) (writing)
	Complex& operator()(int row, int col);
	
	//Operator * Overload for Multiplying two Matrix Objects
	Matrix operator*(Matrix & RHS);
	
	//Operator + Overload for Adding two Matrix Objects
	Matrix operator+(Matrix & RHS);
	
	//Operator - Overload for Subtracting two Matrix Objects
	Matrix operator-(Matrix & RHS);
	
	//Operator ~ Overload for Transposing Matrix Object
	Matrix operator~();
	
	//Operator ! Overload for Conjugate Transposing Matrix Object
	Matrix operator!();

private:
	//Stores number of Rows a matrix have
	int rows;
	
	//Stores number of Columns a matrix have
	int cols;
	
	//Stores Complex Pointer which serves as elements of matrix
	Complex* complexPtr;
};

#endif

