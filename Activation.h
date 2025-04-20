// activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H
#define FLOAT_ZERO 0.0f

#include "Matrix.h"
#include <cmath>
typedef Matrix (*Activation_Function) (const Matrix&);

 namespace activation
 {
     Matrix relu(const Matrix& matrix) noexcept;
     Matrix softmax(const Matrix& matrix) noexcept;
 }

#endif //ACTIVATION_H