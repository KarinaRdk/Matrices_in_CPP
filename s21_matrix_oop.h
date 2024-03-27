#ifndef SRC_HEADER_H
#define SRC_HEADER_H

#include <cmath>
#include <cstring>
#include <iostream>
#include <random>

class S21Matrix {
 public:
  //  Constructors:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;

  //  Assignment operators:
  //  Move:
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  //  Copy:
  S21Matrix& operator=(S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);

  //  Destructor
  ~S21Matrix();

  //  Member Functions:
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  void FillSmallerTable(S21Matrix& smaller_table, int k_to_skip,
                        int l_to_skip) const;
  double Determinant() const;
  int Gauss();
  int SwapLines(int k);
  void SwapItself(int k, int line_of_max_element);
  void MultiplyMainDiagonal(double* result, int lines_swapped) const;
  S21Matrix InverseMatrix() const;

  //  Operator functions:
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  bool operator==(const S21Matrix& other) const;
  double& operator()(int row, int col);
  double operator()(int row, int col) const;

  //  Utility functions:
  void FillRandomly();
  void FillArbitrarily(double x);
  //  void PrintMatrix() const;

  //  Getters and setters:
  int GetRows() const;
  int GetCols() const;
  void SetRows(int number);
  void SetCols(int number);

 private:
  //  Attributes:
  int rows_, cols_;
  double* matrix_;
};

#endif  //  SRC_HEADER_H
