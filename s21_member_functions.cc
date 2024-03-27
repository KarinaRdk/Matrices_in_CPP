#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_ * cols_; i++) {
    if (abs(matrix_[i] - other.matrix_[i]) > 1e-6) {
      return false;
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error(" different matrix dimensions");
  }
  for (int i = 0; i < rows_ * cols_; i++) {
    matrix_[i] += other.matrix_[i];
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("different matrix dimensions");
  }
  for (int i = 0; i < rows_ * cols_; i++) {
    matrix_[i] -= other.matrix_[i];
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_ * cols_; i++) {
    matrix_[i] *= num;
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::logic_error(
        "the number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < other.rows_; k++) {
        result(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  (*this) = result;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; j++) {
      result(i, j) = (*this)(j, i);
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::logic_error("the matrix is not square");
  }
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result(0, 0) = 1;
    return result;
  }
  for (int i = 0; i < (*this).rows_; ++i) {
    for (int j = 0; j < (*this).cols_; ++j) {
      S21Matrix smaller_table(rows_ - 1, cols_ - 1);
      FillSmallerTable(smaller_table, i, j);
      //  fills in the table of minors
      double determinant = smaller_table.Determinant();
      result(i, j) = determinant * pow(-1, i + j);
    }
  }
  return result;
}

void S21Matrix::FillSmallerTable(S21Matrix& smaller_table, int k_to_skip,
                                 int l_to_skip) const {
  int k = 0;
  int l = 0;
  int skiped_k = 0;
  for (int i = 0; i < smaller_table.rows_; ++i, ++k) {
    int skiped_l = 0;
    for (int j = 0; j < smaller_table.cols_; ++j, ++l) {
      if (i == k_to_skip || skiped_k == 1) {
        k = i + 1;
        skiped_k = 1;
      } else {
        k = i;
      }
      if (j == l_to_skip || skiped_l == 1) {
        l = j + 1;
        skiped_l = 1;
      } else {
        l = j;
      }
      smaller_table(i, j) = (*this)(k, l);
    }
  }
}

double S21Matrix::Determinant() const {
  int lines_swapped = 0;
  S21Matrix copy(*this);  //  otherwise the A matrix would change
  lines_swapped = copy.Gauss();
  double result = 0;
  copy.MultiplyMainDiagonal(&result, lines_swapped);
  return result;
}

int S21Matrix::Gauss() {
  int lines_swapped = 0;
  int stop = 1;  //  value changes if there is a null in the main diagonal and
                 //  swap is not possible
  for (int k = 0; stop && k < rows_; k++) {
    if (((*this)(k, k) < 1e-6)) {
      stop = SwapLines(k);
      if (stop) {
        lines_swapped++;
      }
    }
    for (int i = k; stop && i < rows_; ++i) {
      int j = k;
      double factor = (*this)(i, j) / (*this)(k, k);
      for (; j < rows_; ++j) {
        if (i > k) {
          (*this)(i, j) = (*this)(i, j) - (factor * (*this)(k, j));
        }
      }
    }
  }
  return lines_swapped;
}

int S21Matrix::SwapLines(int k) {
  int swap_is_possible = 1;
  if (k == rows_ - 1) {
    swap_is_possible = 0;
  } else {  //  find the line with the max element:
    double max_element = abs((*this)(k + 1, k));
    int line_of_max_element = k + 1;
    for (int i = k + 1; i < cols_; ++i) {
      if (abs((*this)(i, k) > max_element)) {
        line_of_max_element = i;
      }
    }
    if (max_element < 1e-6) {
      swap_is_possible = 0;
    } else {
      (*this).SwapItself(k, line_of_max_element);
    }
  }
  return swap_is_possible;
}

void S21Matrix::SwapItself(int k, int line_of_max_element) {
  for (int j = 0; j < rows_; ++j) {
    double tmp = (*this)(k, j);
    (*this)(k, j) = (*this)(line_of_max_element, j);
    (*this)(line_of_max_element, j) = tmp;
  }
}

void S21Matrix::MultiplyMainDiagonal(double* result, int lines_swapped) const {
  *result = (*this)(0, 0);
  for (int k = 1; k < rows_; ++k) {
    *result = *result * (*this)(k, k);
  }
  if (lines_swapped % 2 != 0) {
    *result = -*result;
  }
}

S21Matrix S21Matrix::InverseMatrix() const {
  double determinant = (*this).Determinant();
  if (abs(determinant) < 0.0000001) {
    throw std::logic_error("matrix determinant is 0");
  }
  S21Matrix copy = CalcComplements().Transpose();
  copy.MulNumber(1 / determinant);
  return copy;
}

void S21Matrix::FillRandomly() {
  srand((unsigned)time(NULL));
  for (int i = 0; i < rows_ * cols_; i++) {
    int random = rand() % 101;
    matrix_[i] = random;
  }
}

void S21Matrix::FillArbitrarily(double x) {
  srand((unsigned)time(NULL));
  for (int i = 0; i < rows_ * cols_; i++) {
    matrix_[i] = x;
  }
}

// void S21Matrix::PrintMatrix() const {
//   for (int i = 0; i < rows_; i++) {
//     for (int j = 0; j < cols_; j++) {
//       std::cout << (*this)(i, j) << " ";
//     }
//     std::cout << std::endl;
//   }
//   std::cout << std::endl;
// }