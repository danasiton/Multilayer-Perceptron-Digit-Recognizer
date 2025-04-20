// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <istream>
#include <exception>

using std::swap;
using std::copy;

#define OUT_OF_RANGE_MSG "Matrix indices are out of range."
#define MULT_DIM_MSG "Matrix dimensions must be compatible for "
#define ADD_DIM_MSG "Matrix dimensions must match for addition."
#define NEG_DIM_MSG "Rows and columns must be positive integers."
#define FAIL_TO_READ_MSG "Failed to read matrix element."
#define ISTREAM_MSG "Failed to read the input stream multiplication"

#define PRINT_TRESHOLD 0.1
#define EXP_PARAM 1e-10
#define FLOAT_ONE 1.0f

// You don't have to use the struct. Can help you with MlpNetwork.h
struct matrix_dims {

    int get_rows () const {return rows;}

    int get_cols () const {return cols;}

    int rows, cols;
};


class Matrix
{
 public:
  // Constructors
  Matrix(
      int rows,
      int cols); // constructor
  Matrix(); // default constructor
  Matrix(const Matrix &m); // copy constructor
  ~Matrix(); // destructor

  // Methods & Functions

  int get_rows() const noexcept;

  int get_cols() const noexcept;
  Matrix& transpose() noexcept;
  Matrix& vectorize() noexcept;
  void plain_print() const noexcept;
  Matrix dot (const Matrix &other) const;
  float norm() const noexcept;
  Matrix rref() const noexcept;

  int argmax() const noexcept;
  float sum() const noexcept;

  // Operators
  Matrix& operator=(Matrix other); //copy assignment
  Matrix& operator += (const Matrix& rhs);
  Matrix operator + (const Matrix& rhs) const;
  Matrix operator * (const Matrix& rhs) const; // matrix multiplication
  // scalar multiplication on the right
  Matrix operator * (float scalar) const noexcept;
  float& operator () (
      int row,
      int col);
  float operator()(
      int row,
      int col) const;
  float& operator [] (
      int cell);
  float operator [] (
      int cell) const;

  // Friends Operators
  //scalar multiplication on the left
  friend Matrix operator * (float scalar,const Matrix& matrix) noexcept;
  friend std::ostream& operator << (std::ostream& os, const Matrix& matrix)
                                                                    noexcept ;
  friend std::istream & operator >> (std::istream& stream, Matrix& matrix);

  // Friends
  friend void mat_swap(Matrix& first, Matrix& second) noexcept;
  friend void row_swap(Matrix& mat, int row1, int row2);
  friend void row_scale(Matrix& mat, int row, float scalar);
  friend void row_combine(Matrix& mat, int dest_row, int src_row, float
  scalar);

 private:

  int _rows;
  int _cols;
  float** _data;
};


#endif //MATRIX_H