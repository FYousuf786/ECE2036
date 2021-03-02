/*
* Lab 05: Complex Matrix Objects
* Faiza Yousef
* ECE2036
*
*/

#include "matrix.h"
#include <iostream>
#include <iomanip>
using namespace std;

//Constructor to create a matrix object based on the rows and columns input
Matrix::Matrix(int r, int c) : rows(r), cols(c)
{
	this->complexPtr = new Complex[r * c];//assign matrix size to complexPtr
	//size=row*column
}

//Copy Constructor to create deep copy of a matrix object
Matrix::Matrix(const Matrix & m) {
	this->rows = m.rows;//set copy's row number to match the input's (m)
	this->cols = m.cols;//set copy's column number to match the input's (m)
	this->complexPtr = new Complex[rows * cols];//set size of copy to match the size of m
	for (int i = 1; i <= rows; ++i) {
		for (int j = 1; j <= cols; j++)
			(*this)(i, j) = m(i, j);
	}
}

//Get Number of Rows
int Matrix::getRows() {
	return rows;
}

//Get Number of Columns
int Matrix::getCols() {
	return cols;
}

//Destructor to deallocate memory specified by new operator
Matrix::~Matrix()
{
	delete[] complexPtr;
}

//Transpose the Matrix
void Matrix::transpose() {
	for (int i = 1; i <= rows; i++) {
		for (int j = i + 1; j <= cols; j++) {
			Complex t = (*this)(i, j);//save current (row, column) index in temporary Complex object
			(*this)(i, j) = (*this)(j, i);//transpose indeces (swap rows with columns)
			(*this)(j, i) = t;//continue transpose 
		}
	}
	//swap the number of rows and number of columns
	int temp = this->rows;//place number of rows in temporary integer
	this->rows = this->cols;//set new number of rows to current number of columns
	this->cols = temp;//set new number of columns to current number of rows
}

//Print The Matrix
void Matrix::printMatrix() {
	cout << *this;
}

//Operator << overloaded to display matrix using cout stream
std::ostream& operator<< (std::ostream & stream, const Matrix & matrix) {
	if ((matrix.rows == 0) || (matrix.cols == 0)) {//if either dimension is 0 the matrix is empty
		stream << "This matrix has zero elements" <<endl;
		return stream;
	}
	for (int i = 1; i <= matrix.rows; ++i) {
		for (int j = 1; j <= matrix.cols; ++j)
			stream << left << setw(MATRIX_FIELD) << matrix(i, j);//set the width with MATRIX_FIELD, left align, print current index of the matrix
		stream << endl;//next line
	}
	return stream;
}

//Operator * overloaded to multiply Complex with Matrix
Matrix operator*(Complex comp, Matrix & RHS) {
	Matrix result(RHS.getRows(), RHS.getCols());//set result to have RHS's number of rows and columns
	for (int i = 1; i <= RHS.getRows(); ++i) {
		for (int j = 1; j <= RHS.getCols(); ++j) {
			result(i, j) = RHS(i, j) * comp;//multiply current index by the complex number
		}
	}
	return result;
}

//Operator * overloaded to multiply Matrix with Complex
Matrix operator*(Matrix & RHS, Complex comp) {
	return comp * RHS;//multiply the RHS by the complex number
}

//Operator * Overload for Multiplying two Matrix Objects
Matrix Matrix::operator*(Matrix & RHS) {
	if (this->getCols() != RHS.getRows()) {//if the LHS's column total doesn't match the RHS's row total
		cout << "Matrix Mismatch Error!" << endl;//there's a mismatch error
		return Matrix(0,0);
	}
	Matrix result(this->getRows(), RHS.getCols());//set result ro LHS's rows and RHS's columns
	for (int r = 1; r <= result.getRows(); r++) {
		for (int k = 1; k <= result.getCols(); k++) {
			Complex sum(0, 0);//create new Complex object to begin multiplication
			for (int c = 1; c <= getCols(); c++)
				sum = sum + (*this)(r, c) * RHS(c, k);//current sum+LHS index+RHS index
			result(r, k) = sum;//set sum to current result index
		}
	}
	return result;
}

//Assignment Opertor Overloaded for deep copy
const Matrix& Matrix::operator=(const Matrix & m) {
	this->rows = m.rows;//set the LHS total rows to the input's total rows
	this->cols = m.cols;//set the LHS total columns to the input's total columns
	delete[] complexPtr;//deallocate space in complexPtr
	complexPtr = new Complex[rows * cols];//reallocate space based on size
	for (int i = 1; i <= rows; ++i) {
		for (int j = 1; j <= cols; j++)
			(*this)(i, j) = m(i, j);//set current index from input matrix to the current index of new matrix
	}
	return (*this);
}

//Operator + Overload for Adding two Matrix Objects
Matrix Matrix::operator+(Matrix & RHS) {
	if ((this->getCols() != RHS.getCols()) || (this->getRows() != RHS.getRows())) {//if LHS column doesn't match RHS cols or LHS rows don't match RHS rows
		cout << "Matrix Mismatch Error!" << endl;//can't add the matrices and mismatch error
		return Matrix(0,0);
	}
	Matrix result(this->getRows(), this->getCols());//set result to LHS's rows and columns
	for (int r = 1; r <= result.getRows(); r++) {
		for (int k = 1; k <= result.getCols(); k++) {
			result(r, k) = (*this)(r, k) + RHS(r, k);//add current index of LHS and RHS and store in result
		}
	}
	return result;
}

//Operator - Overload for Subtracting two Matrix Objects
Matrix Matrix::operator-(Matrix & RHS) {
	if ((this->getCols() != RHS.getCols()) || (this->getRows() != RHS.getRows())) {//if LHS column doesn't match RHS cols or LHS rows don't match RHS rows
		cout << "Matrix Mismatch Error!" << endl;//can't subtract the matrices and mismatch error
		return Matrix(0, 0);
	}
	Matrix result(this->getRows(), this->getCols());//set result to LHS's rows and columns
	for (int r = 1; r <= result.getRows(); r++) {
		for (int k = 1; k <= result.getCols(); k++) {
			result(r, k) = (*this)(r, k) - RHS(r, k);//subtract current index of RHS form LHS and store in result
		}
	}
	return result;
}

//Operator ~ Overload for Transposing Matrix Object
Matrix Matrix::operator~() {
	Matrix result(*this);//set result to have same data from RHS
	result.transpose();//call transpose function from result object
	return result;
}

//Operator ! Overload for Conjugate Transposed Matrix Object
Matrix Matrix::operator!() {
	Matrix result(*this);//set result to have same data from RHS
	for (int i = 1; i <= result.getRows(); ++i)
		for (int j = 1; j <= result.getCols(); j++)
			result(i,j) = !result(i,j);//call conjugate operator from Complex class

	result.transpose();//transpose entire result with transpose function
	return result;
}

//Parenthesis Operator Overload for indexing matrix (Assigning Values)
Complex& Matrix::operator()(int row, int col)
{	//assigning won't use const objects because we want to write/change data
	return complexPtr[(row - 1)*(this->getCols()) + col - 1];//index a matrix with both rows and columns
}

//Parenthesis Opertor Overload for indexing matrix (Constant Objects)
const Complex& Matrix::operator()(int row, int col) const {
	//uses const objects (so data isn't accidently changed) to read data from a matrix 
	return complexPtr[(row - 1)*(this->cols) + col - 1];
}
