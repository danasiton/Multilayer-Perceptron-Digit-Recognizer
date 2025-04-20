#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
#define WEIGHTS_DIM_MSG "input dimention do not match weights"

class Dense
{
 public:
  // constructor
  Dense (const Matrix &weights, const Matrix &bias,
                                Activation_Function activation_function) :
                                _weights (weights), _bias (bias),
                                _activation_function (activation_function) {}
  // getters
  const Matrix &get_weights () const noexcept { return this->_weights; }
  const Matrix &get_bias () const noexcept { return this->_bias; }
  Activation_Function get_activation () const noexcept
  { return _activation_function; }
  // operators
  Matrix operator() (const Matrix &input) const;

 private:
  Matrix _weights;
  Matrix _bias;
  Activation_Function _activation_function;

};

#endif //DENSE_H