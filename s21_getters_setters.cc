#include "s21_matrix_oop.h"

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int number) {
  //  Create matrix of a requred size
  S21Matrix result(number, cols_);
  //  Fill the requred number of rows with values from the original
  int mult = rows_ < number ? rows_ : number;
  for (int i = 0; i < mult * cols_; i++) {
    result.matrix_[i] = matrix_[i];
  }
  (*this) = std::move(result);
};

void S21Matrix::SetCols(int number) {
  if (number < 0) {
    throw std::logic_error("wrong value");
  }
  //  Create matrix of a requred size
  S21Matrix result(rows_, number);
  // Fill it with values from original matrix
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      if (j >= cols_) {
        result(i, j) = 0;
      } else {
        result(i, j) = (*this)(i, j);
      }
    }
  }
  (*this) = result;
};
