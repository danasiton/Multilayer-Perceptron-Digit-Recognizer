#include "Matrix.h"

using std::swap;

// constructor
Matrix ::Matrix (int rows, int cols): _rows(rows), _cols(cols)
{
  if (rows <= 0 || cols <= 0)
  {
    throw std::invalid_argument(NEG_DIM_MSG);
  }
  _data = new(std::nothrow) float* [rows];
  for (int i = 0; i < rows; i++)
  {
    // Initialize all elements to 0
    _data[i] = new(std::nothrow) float [cols]{0};
  }
}

// default constructor
Matrix ::Matrix (): Matrix (1,1)
{}

// copy constructor (rule of 3)
Matrix::Matrix (const Matrix &m) : Matrix(m._rows, m._cols)
{
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      this->_data[i][j] = m._data[i][j];
    }
  }
}

// copy assignment (rule of 3)
Matrix& Matrix::operator=(Matrix other)
{
  mat_swap(*this,other);
  return *this;
}

// deconstructor (rule of 3)
Matrix::~Matrix()
{
  for (int i = 0; i < this->_rows; ++i)
  {
    delete[] this->_data[i];
  }
  delete[] this->_data;
}

int Matrix::get_cols() const noexcept
{
  return this->_cols;
}

int Matrix::get_rows() const noexcept
{
  return this->_rows;
}

void mat_swap(Matrix& first, Matrix& second) noexcept
{
  swap(first._rows, second._rows);
  swap(first._cols, second._cols);
  swap(first._data, second._data);
}

Matrix& Matrix:: transpose() noexcept
{
  // create new matrix with transposed dimensions
  Matrix transposed_matrix(_cols,_rows);
  // copy the elements one by one according to the transposed indices
  for (int i = 0; i < _rows; i++){
    for (int j = 0; j < _cols; j++)
    {
      transposed_matrix._data[j][i] = this->_data[i][j];
    }
  }
  *this = transposed_matrix;
  return  *this;
}
//
Matrix& Matrix:: vectorize() noexcept
{
  int total_elems = (this->_rows * this->_cols);
  // create new matrix with new dimensions
  Matrix vectorized_matrix (total_elems, 1);
  int index = 0;

  for (int i = 0; i < _rows; i++){
    for (int j = 0; j < _cols; j++)
    {
      vectorized_matrix._data[index++][0] = this->_data[i][j];
    }
  }
    mat_swap (*this,vectorized_matrix);
    return *this;
}

void Matrix:: plain_print() const noexcept
{
  for (int i = 0; i < _rows; i++){
    for (int j = 0; j < _cols; j++)
    {
      std::cout << this->_data[i][j] << " " ;
    }
    std::cout << std::endl;
  }
}

Matrix Matrix::dot(const Matrix &other) const
{
  if (_rows != other._rows || _cols != other._cols) {
    throw std::invalid_argument(MULT_DIM_MSG);
  }
  Matrix doted_matrix (this->_rows, this->_cols);
  for (int i = 0; i < _rows; i++){
    for (int j = 0; j < _cols; j++)
    {
      doted_matrix._data[i][j] = (this->_data[i][j]) * (other._data[i][j]);
    }
  }
  return doted_matrix;
}

float Matrix:: norm() const noexcept
{
  float sum = 0.0;
  for (int i = 0; i < _rows; i++){
    for (int j = 0; j < _cols; j++)
    {
      sum += this->_data[i][j] * this->_data[i][j];
    }
  }
  return std::sqrt(sum);
}

Matrix Matrix::rref() const noexcept
{
  Matrix rref_matrix(*this);

  int lead = 0;
  int row_count = rref_matrix._rows;
  int col_count = rref_matrix._cols;

  for (int row = 0; row < row_count; row++) {
    if (col_count <= lead) {
      break;
    }

    int i = row;
    while (std::abs(rref_matrix._data[i][lead]) < EXP_PARAM) {
      ++i;
      if (i == row_count) {
        i = row;
        ++lead;
        if (col_count == lead) {
          return rref_matrix;
        }
      }
    }

    row_swap(rref_matrix, i, row);
    row_scale(rref_matrix, row, FLOAT_ONE / rref_matrix._data[row][lead]);

    for (int j = 0; j < row_count; ++j) {
      if (j != row) {
        row_combine(rref_matrix, j, row, -rref_matrix._data[j][lead]);
      }
    }

    ++lead;
  }
  return rref_matrix;
}

// helper functions implementations (row_swap, row_scale, row_combine, etc.)
void row_swap(Matrix& mat, int row1, int row2)
{
  float* temp = mat._data[row1];
  mat._data[row1] = mat._data[row2];
  mat._data[row2] = temp;
}

void row_scale(Matrix& mat, int row, float scalar) {
  for (int j = 0; j < mat._cols; ++j) {
    mat._data[row][j] *= scalar;
  }
}

void row_combine(Matrix& mat, int dest_row, int src_row, float scalar) {
  for (int j = 0; j < mat._cols; ++j) {
    mat._data[dest_row][j] += scalar * mat._data[src_row][j];
  }
}

int Matrix::argmax() const noexcept
{
  Matrix vectorized_matrix(*this);
  vectorized_matrix.vectorize();
  int max_ind = 0;
  float max_value = vectorized_matrix._data[0][0];
  for (int i = 0; i < vectorized_matrix._rows; i++)
  {
    if (vectorized_matrix._data[i][0] > max_value){
      max_value = vectorized_matrix._data[i][0];
      max_ind = i;
    }
  }
  return max_ind;
}

float Matrix::sum() const noexcept
{
  float total_sum = 0;
  for (int i = 0; i < _rows; i++){
    for (int j = 0; j < _cols; j++)
    {
      total_sum += this->_data[i][j];
    }
  }
  return total_sum;
}

Matrix Matrix:: operator + (const Matrix& rhs) const
{
  if (this->_rows != rhs._rows || this->_cols != rhs._cols)
  {
    throw std::invalid_argument (ADD_DIM_MSG);
  }
  Matrix res_mat (_rows, _cols);
  for (int i = 0; i < this->_rows; i++){
    for (int j = 0; j < this->_cols; j++)
    {
      res_mat._data[i][j] = this->_data[i][j] + rhs._data[i][j];
    }
  }
  return res_mat;
}

Matrix& Matrix:: operator += (const Matrix& rhs)
{
  if (this->_rows != rhs._rows || this->_cols != rhs._cols){
    throw std::invalid_argument (ADD_DIM_MSG);
  }
  for (int i = 0; i < this->_rows; i++){
    for (int j = 0; j < this->_cols; j++){
      this->_data[i][j] += rhs._data[i][j];
    }
  }
  return *this;
}

Matrix Matrix:: operator * (const Matrix& rhs) const
{
  if (this->_cols != rhs._rows) {
    throw std::invalid_argument(MULT_DIM_MSG);
  }
  Matrix res_mat (_rows, rhs.get_cols());
  for (int i = 0; i < this->_rows; i++) {
    for (int j = 0; j < rhs._cols; j++) {
      res_mat._data[i][j] = 0;  // Initialize to 0 before summing products
      for (int k = 0; k < this->_cols; k++) {
        res_mat._data[i][j] += this->_data[i][k] * rhs._data[k][j];
      }
    }
  }
  return res_mat;
}

// scalar multiplication on the right
Matrix Matrix:: operator * (float scalar) const noexcept
{
  Matrix res_mat(_rows, _cols);
  for (int i = 0; i < this->_rows; i++)
  {
    for (int j = 0; j < this->_cols; j++)
    {
      res_mat._data[i][j] = (this->_data[i][j]) * scalar;
    }
  }
  return res_mat;
}

// scalar multiplication on the left
Matrix operator * (float scalar,const Matrix& matrix) noexcept
{
  Matrix res_mat(matrix._rows, matrix._cols);
  for (int i = 0; i < matrix._rows; i++)
  {
    for (int j = 0; j < matrix._cols; j++)
    {
      res_mat._data[i][j] = (matrix._data[i][j]) * scalar;
    }
  }
  return res_mat;
}

float& Matrix::operator() (int row, int col)
{
  if (row < 0 ||row >= _rows ||col < 0 || col >= _cols) {
    throw std::out_of_range(OUT_OF_RANGE_MSG);
  }
  return this->_data[row][col];
}

float Matrix::operator() (int row, int col) const
{
  if (row < 0 ||row >= _rows ||col < 0 || col >= _cols) {
    throw std::out_of_range(OUT_OF_RANGE_MSG);
  }
  return this->_data[row][col];
}

float& Matrix:: operator [] (int cell)
{
  int total_cells = this->_rows * this->_cols;
  if (cell >= total_cells || cell < 0)
  {
    throw std::out_of_range (OUT_OF_RANGE_MSG);
  }
  int row = cell / this->_cols;
  int col = cell % _cols;
  return this->_data[row][col];
}

float Matrix:: operator [] (int cell) const
{
  int total_cells = this->_rows* this->_cols;
  if (cell >= total_cells || cell < 0) {
    throw std::out_of_range(OUT_OF_RANGE_MSG);
  }
  int row = cell / this->_cols;
  int col = cell % _cols;
  return this->_data[row][col];
}

std::ostream& operator << (std::ostream& os, const Matrix& matrix) noexcept
{
  for (int i = 0; i < matrix._rows; i++){
    for (int j = 0; j < matrix._cols; j++){
      if (matrix._data[i][j] > PRINT_TRESHOLD){
        os << "**";
      }
      else{
        os << "  ";
      }
    }
    os << std::endl;
  }
  return os;
}

std::istream & operator >> (std::istream& stream, Matrix& matrix)
{
  if (!stream.good ()){
    throw std::runtime_error(ISTREAM_MSG);
  }
  int elements_read = 0;

  for (int i = 0; i < matrix._rows; i++) {
    for (int j = 0; j < matrix._cols; j++) {
      if (stream.eof()) {
        throw std::runtime_error(ISTREAM_MSG);
      }
      // Read the binary data into the matrix
      stream.read(reinterpret_cast<char*>(&matrix._data[i][j]), sizeof(float));
      if (!stream) {
        throw std::runtime_error(ISTREAM_MSG);
      }
      elements_read++;
    }
  }

  return stream;
}
