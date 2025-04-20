#include "Dense.h"

Matrix Dense::operator() (const Matrix& input) const
{
  if (input.get_rows() != this->_weights.get_cols())
  {
    throw std::invalid_argument("failed at dense");
  }
  // apply the layer operation = activation_function(weights * input + bias)
  Matrix output_mat = this->_weights * input;
  output_mat += this->_bias;
  return this->_activation_function(output_mat);
}
