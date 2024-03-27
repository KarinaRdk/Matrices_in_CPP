#include "s21_matrix_oop.h"

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (!(*this == other)) {
    delete[] matrix_;
    matrix_ = other.matrix_;
    cols_ = other.cols_;
    rows_ = other.rows_;
    other.matrix_ = nullptr;
    other.cols_ = 0;
    other.rows_ = 0;
  }
  return (*this);
}

S21Matrix& S21Matrix::operator=(S21Matrix& other) {
  S21Matrix copy(other);
  *this = std::move(copy);
  return (*this);
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("different matrix dimensions");
  }
  //  Copy constractor
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("different matrix dimensions");
  }
  //  Copy constractor
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  if (cols_ != other.rows_) {
    throw std::logic_error(
        "the number of columns of the first matrix does not equal the number "
        "of rows of the second matrix");
  }
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return (*this).EqMatrix(other);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("different matrix dimensions");
  }
  (*this).SumMatrix(other);
  return (*this);
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("different matrix dimensions");
  }

  (*this).SubMatrix(other);
  return (*this);
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::logic_error(
        "the number of columns of the first matrix does not equal the number "
        "of rows of the second matrix");
  }
  (*this).MulMatrix(other);
  return (*this);
}

double& S21Matrix::operator()(int row, int col) {  //  for testing purposes
  if (row >= rows_ || col >= cols_) {
    throw std::logic_error("index is outside the matrix");
  }
  if (row < 0 || col < 0) {
    throw std::logic_error("incorrect value");
  }
  return matrix_[row * cols_ + col];
}

double S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_) {
    throw std::logic_error("index is outside the matrix");
  }
  if (row < 0 || col < 0) {
    throw std::logic_error("incorrect value");
  }
  return matrix_[row * cols_ + col];
}
