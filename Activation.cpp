
#include "Activation.h"


Matrix activation::relu (const Matrix &matrix) noexcept
{
  Matrix res_mat (matrix.get_rows(),matrix.get_cols());
  for (int i = 0; i < matrix.get_rows(); i++){
    for (int j = 0; j < matrix.get_cols(); j++)
    {
      res_mat(i,j) = std::max (FLOAT_ZERO, matrix(i,j));
    }
  }
  return res_mat;
}

Matrix activation::softmax (const Matrix &matrix) noexcept
{
  Matrix res_mat (matrix.get_rows(),matrix.get_cols());
  float max_elem = matrix(0,0);
  // find the max elem in the matrix
  for (int i = 0; i < matrix.get_rows(); i++){
    for (int j = 0; j < matrix.get_cols(); j++)
    {
      if (matrix(i,j) > max_elem)
      {
        max_elem = matrix(i,j);
      }
    }
  }
  // compute exp values and sun them
  float sum = 0.0F;
  for (int i = 0; i < matrix.get_rows(); i++){
    for (int j = 0; j < matrix.get_cols(); j++)
    {
      res_mat(i,j) = std::exp (matrix(i,j) - max_elem);
      sum += res_mat(i,j);
    }
  }
  // normalize the values to get softmax
  for (int i = 0; i < matrix.get_rows(); i++){
    for (int j = 0; j < matrix.get_cols(); j++)
    {
      res_mat(i, j) /= sum;
    }
  }
  return res_mat;
}

