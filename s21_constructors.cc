#include "s21_matrix_oop.h"

// Default constructor
S21Matrix::S21Matrix()
    : rows_(0), cols_(0), matrix_(new double[rows_ * cols_]()) {}

// Parametarised constructor
S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols) {  // Parameterised constructor
  if (rows < 0 && cols < 0) {
    throw std::logic_error("number of rows and cols cant't be negative");
  }
  matrix_ = new double[rows * cols]();
}

// Copy constructor
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double[rows_ * cols_]();
  std::copy(other.matrix_, other.matrix_ + rows_ * cols_, matrix_);
}

/* A move constructor allows the resources owned by an rvalue object to be
moved into an lvalue without creating it's copy. An rvalue is an expression that
does not have any memory address, and an lvalue is an expression with a memory
address */

S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  matrix_ = std::move(other.matrix_);
  cols_ = std::move(other.cols_);
  rows_ = std::move(other.rows_);
}

//  Destructor
S21Matrix::~S21Matrix() {
  delete[] matrix_;
  cols_ = 0;
  rows_ = 0;
}
