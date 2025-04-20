
#include "MlpNetwork.h"

MlpNetwork::MlpNetwork(const Matrix weights[], const Matrix biases[])
    : _layers{
    Dense(weights[0], biases[0], activation::relu),
    Dense(weights[1], biases[1], activation::relu),
    Dense(weights[2], biases[2], activation::relu),
    Dense(weights[3], biases[3], activation::softmax)
} {
  for (int i = 0; i < MLP_SIZE; ++i) {
    if (weights[i].get_rows() != weights_dims[i].rows ||
        weights[i].get_cols() != weights_dims[i].cols ||
        biases[i].get_rows() != bias_dims[i].rows ||
        biases[i].get_cols() != bias_dims[i].cols)
    {
      throw std::invalid_argument(WEIGHTS_DIM_MSG);
    }
  }
}


digit MlpNetwork::operator() (const Matrix &input) const
{
  Matrix res_mat = input;
  //pass the input through each layer in the network
  for (int i = 0; i < MLP_SIZE ; i++)
  {
    res_mat = this->_layers[i](res_mat);
  }
  // find the digit with the highest probability
  float max_probability = res_mat(0,0);
  unsigned int max_index = 0;
  for (int i = 1; i < res_mat.get_rows() ; i++)
  {
    if (res_mat(i,0) > max_probability){
      max_probability = res_mat(i,0);
      max_index = i;
    }
  }
  return digit {max_index,max_probability};
}


