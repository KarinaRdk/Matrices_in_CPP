#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(TestEqMatrix, test1) {
  S21Matrix i(3, 3);
  i.FillArbitrarily(2);
  S21Matrix j(3, 3);
  j.FillArbitrarily(2);
  ASSERT_EQ(i.EqMatrix(j), 1);
}

TEST(TestEqMatrix, test2) {
  S21Matrix i(3, 3);
  i.FillArbitrarily(1);
  S21Matrix j(3, 3);
  j.FillArbitrarily(2);
  ASSERT_EQ(i.EqMatrix(j), 0);
}

TEST(TestEqMatrix, test3) {
  S21Matrix i(2, 3);
  i.FillArbitrarily(1);
  S21Matrix j(3, 3);
  j.FillArbitrarily(2);
  ASSERT_EQ(i.EqMatrix(j), 0);
}

TEST(TestCopyConstructor, test1) {
  S21Matrix i(3, 3);
  i.FillRandomly();
  S21Matrix j(i);
  ASSERT_EQ(i.EqMatrix(j), 1);
}

TEST(TestConstructorD, test1) {
  S21Matrix a;
  ASSERT_EQ(a.GetCols(), 0);
  ASSERT_EQ(a.GetRows(), 0);
}

TEST(TestConstructorD, test2) {
  S21Matrix a;
  ASSERT_EQ(a.GetCols(), 0);
  ASSERT_EQ(a.GetRows(), 0);
  ASSERT_ANY_THROW(a(1, 2));
}

TEST(TestConstructorParam, test1) {
  S21Matrix a(3, 3);
  ASSERT_EQ(a.GetRows(), 3);
  ASSERT_EQ(a.GetCols(), 3);
  a(2, 2) = 285.4532;
  ASSERT_DOUBLE_EQ(a(2, 2), 285.4532);
}

TEST(TestConstructorParam, test2) {
  S21Matrix a(3, 5);
  ASSERT_EQ(a.GetRows(), 3);
  ASSERT_EQ(a.GetCols(), 5);
  a(2, 4) = 8525.45;
  ASSERT_DOUBLE_EQ(a(2, 4), 8525.45);
}

TEST(TestConstructorParam, test3) { ASSERT_ANY_THROW(S21Matrix M(-2, -2)); }

TEST(TestConstructorParam, test4) { ASSERT_ANY_THROW(S21Matrix M(5, -2)); }

TEST(TestConstructorMove, test1) {
  S21Matrix m(6, 6);
  for (int i = 0; i < m.GetRows(); i++) {
    for (int j = 0; j < m.GetCols(); j++) {
      m(i, j) = 5;
    }
  }
  S21Matrix other = std::move(m);
  ASSERT_EQ(other.GetRows(), 6);
  ASSERT_EQ(other.GetCols(), 6);
  ASSERT_EQ(m.GetRows(), 0);
  ASSERT_EQ(m.GetCols(), 0);
}

TEST(SumMatrix, test1) {
  S21Matrix m(6, 6);
  m.FillArbitrarily(10);
  S21Matrix other = m;
  m.SumMatrix(other);
  for (int i = 0; i < m.GetRows(); i++) {
    for (int j = 0; j < m.GetCols(); j++) {
      ASSERT_EQ(m(i, j), 20);
    }
  }
}

TEST(SumMatrix, test2) {
  S21Matrix m(6, 6);
  m.FillArbitrarily(10);
  S21Matrix n(5, 6);
  ASSERT_ANY_THROW(m.SumMatrix(n));
}

TEST(SubMatrix, test1) {
  S21Matrix m(6, 6);
  m.FillArbitrarily(10);
  S21Matrix n(5, 6);
  ASSERT_ANY_THROW(m.SubMatrix(n));
}

TEST(SubMatrix, test2) {
  S21Matrix m(6, 6);
  m.FillRandomly();
  S21Matrix other = m;
  m.SubMatrix(other);
  for (int i = 0; i < m.GetRows(); i++) {
    for (int j = 0; j < m.GetCols(); j++) {
      ASSERT_EQ(m(i, j), 0);
    }
  }
}

TEST(MulMatrix, test1) {
  S21Matrix m(5, 3);
  S21Matrix n(4, 5);
  ASSERT_ANY_THROW(m.MulMatrix(n));
}
TEST(MulNumber, test1) {
  S21Matrix m(2, 3);
  m.FillArbitrarily(6);
  m.MulNumber(2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_EQ(m(i, j), 12);
    }
  }
}

TEST(MulMatrix, test2) {
  S21Matrix m(2, 3);
  m.FillArbitrarily(6);
  S21Matrix n(3, 2);
  n.FillArbitrarily(4);
  m.MulMatrix(n);
  ASSERT_EQ(m.GetRows(), 2);
  ASSERT_EQ(m.GetCols(), 2);
  for (int i = 0; i < m.GetRows(); i++) {
    for (int j = 0; j < m.GetCols(); j++) {
      ASSERT_EQ(m(i, j), 72);
    }
  }
}

TEST(Transpose, test1) {
  S21Matrix M(3, 3);
  M(0, 0) = 13;
  M(0, 1) = 76;
  M(0, 2) = 54;

  M(1, 0) = 28;
  M(1, 1) = 578;
  M(1, 2) = 2;

  M(2, 0) = 9;
  M(2, 1) = 2;
  M(2, 2) = 2;
  S21Matrix M2 = M.Transpose();

  ASSERT_DOUBLE_EQ(M2(0, 0), 13);
  ASSERT_DOUBLE_EQ(M2(0, 1), 28);
  ASSERT_DOUBLE_EQ(M2(0, 2), 9);

  ASSERT_DOUBLE_EQ(M2(1, 0), 76);
  ASSERT_DOUBLE_EQ(M2(1, 1), 578);
  ASSERT_DOUBLE_EQ(M2(1, 2), 2);

  ASSERT_DOUBLE_EQ(M2(2, 0), 54);
  ASSERT_DOUBLE_EQ(M2(2, 1), 2);
  ASSERT_DOUBLE_EQ(M2(2, 2), 2);
}

TEST(CalcComplements, test1) {
  S21Matrix M(3, 3);
  M(0, 0) = 1;
  M(0, 1) = 2;
  M(0, 2) = 3;

  M(1, 0) = 0;
  M(1, 1) = 4;
  M(1, 2) = 2;

  M(2, 0) = 5;
  M(2, 1) = 2;
  M(2, 2) = 1;

  S21Matrix M2 = M.CalcComplements();
  ASSERT_DOUBLE_EQ(M2(0, 0), 0);
  ASSERT_DOUBLE_EQ(M2(0, 1), 10);
  ASSERT_DOUBLE_EQ(M2(0, 2), -20);

  ASSERT_DOUBLE_EQ(M2(1, 0), 4);
  ASSERT_DOUBLE_EQ(M2(1, 1), -14);
  ASSERT_DOUBLE_EQ(M2(1, 2), 8);

  ASSERT_DOUBLE_EQ(M2(2, 0), -8);
  ASSERT_DOUBLE_EQ(M2(2, 1), -2);
  ASSERT_DOUBLE_EQ(M2(2, 2), 4);
}

TEST(CalcComplements, test2) {
  S21Matrix M(1, 1);
  M(0, 0) = 5;
  S21Matrix M2 = M.CalcComplements();
  ASSERT_DOUBLE_EQ(M2(0, 0), 1);
}

TEST(CalcComplements, test3) {
  S21Matrix M(3, 1);
  M(0, 0) = 5;
  ASSERT_ANY_THROW(M.CalcComplements());
}

TEST(Determinant, test0) {
  S21Matrix m(3, 3);
  m(0, 0) = 73;
  m(0, 1) = 7;
  m(0, 2) = 6;
  m(1, 0) = 110;
  m(1, 1) = 16;
  m(1, 2) = 19;
  m(2, 0) = 148;
  m(2, 1) = 10;
  m(2, 2) = 7;
  ASSERT_NEAR(m.Determinant(), 992, 0.0000001);
}

TEST(Determinant, test1) {
  S21Matrix m(3, 3);
  m(0, 0) = 5;
  m(0, 1) = 7;
  m(0, 2) = 9;
  m(1, 0) = 11;
  m(1, 1) = 13;
  m(1, 2) = 15;
  m(2, 0) = 4;
  m(2, 1) = -5;
  m(2, 2) = 4;
  ASSERT_NEAR(m.Determinant(), -216, 0.0000001);
}

TEST(Determinant, test2) {
  S21Matrix m(3, 3);
  m(0, 0) = 5;
  m(0, 1) = 7;
  m(0, 2) = 6;
  m(1, 0) = 3;
  m(1, 1) = 16;
  m(1, 2) = 19;
  m(2, 0) = 13;
  m(2, 1) = 10;
  m(2, 2) = 7;
  ASSERT_NEAR(m.Determinant(), 124, 0.0000001);
}

TEST(Determinant, test3) {
  S21Matrix m(5, 5);
  m(0, 0) = 5;
  m(0, 1) = 7;
  m(0, 2) = 9;
  m(0, 3) = 11;
  m(0, 4) = 11;

  m(1, 0) = 13;
  m(1, 1) = 15;
  m(1, 2) = 17;
  m(1, 3) = 19;
  m(1, 4) = 19;

  m(2, 0) = 22;
  m(2, 1) = 25;
  m(2, 2) = 28;
  m(2, 3) = 1;
  m(2, 4) = 1;

  m(3, 0) = -10;
  m(3, 1) = 1;
  m(3, 2) = 5;
  m(3, 3) = 9;
  m(3, 4) = 9;

  m(4, 0) = 30;
  m(4, 1) = 1;
  m(4, 2) = 5;
  m(4, 3) = 9;
  m(4, 4) = -11;
  ASSERT_NEAR(m.Determinant(), -67200, 0.0000001);
}

TEST(Determinant, test4) {
  S21Matrix M(4, 4);
  M(0, 0) = 0;
  M(0, 1) = 56;
  M(0, 2) = 4;
  M(0, 3) = 89;

  M(1, 0) = 78;
  M(1, 1) = 8;
  M(1, 2) = 56;
  M(1, 3) = -76.67;

  M(2, 0) = 99.99;
  M(2, 1) = 996;
  M(2, 2) = 5.99;
  M(2, 3) = 76;

  M(3, 0) = 0.87;
  M(3, 1) = 76.67;
  M(3, 2) = 65;
  M(3, 3) = 678;
  double res = M.Determinant();
  ASSERT_NEAR(res, -26770223.207819, 1e-6);
}

TEST(Determinant, test5) {
  S21Matrix M(4, 4);
  M(0, 0) = 0;
  M(0, 1) = 56;
  M(0, 2) = 4;
  M(0, 3) = 89;

  M(1, 0) = 78;
  M(1, 1) = 8;
  M(1, 2) = 56;
  M(1, 3) = -76.67;

  M(2, 0) = 0;
  M(2, 1) = 0;
  M(2, 2) = 0;
  M(2, 3) = 0;

  M(3, 0) = 0;
  M(3, 1) = 0;
  M(3, 2) = 0;
  M(3, 3) = 0;
  double res = M.Determinant();
  ASSERT_NEAR(res, 0, 1e-6);
}

TEST(InverseMatrix, test1) {
  S21Matrix M(4, 4);
  M(0, 0) = 0;
  M(0, 1) = 56;
  M(0, 2) = 4;
  M(0, 3) = 89;

  M(1, 0) = 78;
  M(1, 1) = 8;
  M(1, 2) = 56;
  M(1, 3) = -76.67;

  M(2, 0) = 0;
  M(2, 1) = 0;
  M(2, 2) = 0;
  M(2, 3) = 0;

  M(3, 0) = 0;
  M(3, 1) = 0;
  M(3, 2) = 0;
  M(3, 3) = 0;
  ASSERT_ANY_THROW(M.InverseMatrix());
}
TEST(InverseMatrix, test2) {
  S21Matrix M(3, 3);
  M(0, 0) = 2;
  M(0, 1) = 5;
  M(0, 2) = 7;

  M(1, 0) = 6;
  M(1, 1) = 3;
  M(1, 2) = 4;

  M(2, 0) = 5;
  M(2, 1) = -2;
  M(2, 2) = -3;
  S21Matrix M2 = M.InverseMatrix();

  ASSERT_NEAR(M2(0, 0), 1, 0.0000001);
  ASSERT_NEAR(M2(0, 1), -1, 0.0000001);
  ASSERT_NEAR(M2(0, 2), 1, 0.0000001);

  ASSERT_NEAR(M2(1, 0), -38, 0.0000001);
  ASSERT_NEAR(M2(1, 1), 41, 0.0000001);
  ASSERT_NEAR(M2(1, 2), -34, 0.0000001);

  ASSERT_NEAR(M2(2, 0), 27, 0.0000001);
  ASSERT_NEAR(M2(2, 1), -29, 0.0000001);
  ASSERT_NEAR(M2(2, 2), 24, 0.0000001);
}

TEST(InverseMatrix, test4) {
  S21Matrix M;
  ASSERT_ANY_THROW(M.InverseMatrix());
}

TEST(SetCols, test1) {
  S21Matrix m(2, 2);
  ASSERT_ANY_THROW(m.SetCols(-1));
}

TEST(SetCols, test2) {
  S21Matrix m(2, 2);
  ASSERT_ANY_THROW(m.SetCols(-10));
}

TEST(SetCols, test3) {
  S21Matrix m(2, 2);
  m.FillRandomly();
  m.SetCols(10);
  ASSERT_EQ(m.GetCols(), 10);
}

TEST(SetRows, test1) {
  S21Matrix m(2, 2);
  ASSERT_ANY_THROW(m.SetRows(-2));
}

TEST(SetRows, test2) {
  S21Matrix m(2, 2);
  m.SetRows(10);
  ASSERT_EQ(m.GetRows(), 10);
}

TEST(SetRows, test3) {
  S21Matrix m(2, 2);
  ASSERT_ANY_THROW(m.SetRows(-5));
}

TEST(OperatorPlus, test1) {
  S21Matrix first(2, 2);
  first.FillArbitrarily(11);
  S21Matrix second(2, 2);
  second.FillArbitrarily(4);
  S21Matrix third = first + second;
  ASSERT_EQ(third(0, 0), 15);
  ASSERT_EQ(third(0, 1), 15);
  ASSERT_EQ(third(1, 0), 15);
  ASSERT_EQ(third(1, 1), 15);
}

TEST(OperatorPlus, test2) {
  S21Matrix first(2, 2);
  first.FillArbitrarily(11);
  S21Matrix second(2, 23);
  second.FillArbitrarily(4);
  ASSERT_ANY_THROW(first + second);
}

TEST(OperatorMinus, test1) {
  S21Matrix first(2, 2);
  first.FillArbitrarily(11);
  S21Matrix second(2, 2);
  second.FillArbitrarily(1);
  S21Matrix third = first - second;
  ASSERT_EQ(third(0, 0), 10);
  ASSERT_EQ(third(0, 1), 10);
  ASSERT_EQ(third(1, 0), 10);
  ASSERT_EQ(third(1, 1), 10);
}

TEST(OperatorMinus, test2) {
  S21Matrix first(2, 2);
  first.FillArbitrarily(11);
  S21Matrix second(23, 2);
  second.FillArbitrarily(4);
  ASSERT_ANY_THROW(first - second);
}

TEST(OperatorMult, test1) {
  S21Matrix first(2, 3);
  first.FillArbitrarily(11);
  S21Matrix second(3, 2);
  second.FillArbitrarily(2);
  S21Matrix third = first * second;
  ASSERT_EQ(third(0, 0), 66);
  ASSERT_EQ(third(0, 1), 66);
  ASSERT_EQ(third(1, 0), 66);
  ASSERT_EQ(third(1, 1), 66);
}

TEST(OperatorMult, test2) {
  S21Matrix first(2, 2);
  first.FillArbitrarily(11);
  S21Matrix second(23, 2);
  second.FillArbitrarily(4);
  ASSERT_ANY_THROW(first * second);
}

TEST(OperatorPlusEq, test1) {
  S21Matrix first(2, 2);
  first.FillArbitrarily(11);
  S21Matrix second(2, 2);
  second.FillArbitrarily(4);
  S21Matrix third = first += second;
  ASSERT_EQ(third(0, 0), 15);
  ASSERT_EQ(third(0, 1), 15);
  ASSERT_EQ(third(1, 0), 15);
  ASSERT_EQ(third(1, 1), 15);
}

TEST(OperatorPlusEq, test2) {
  S21Matrix first(2, 2);
  first.FillArbitrarily(11);
  S21Matrix second(2, 23);
  second.FillArbitrarily(4);
  ASSERT_ANY_THROW(first += second);
}

TEST(OperatorMinusEq, test1) {
  S21Matrix first(2, 2);
  first.FillArbitrarily(11);
  S21Matrix second(2, 2);
  second.FillArbitrarily(1);
  S21Matrix third = first -= second;
  ASSERT_EQ(third(0, 0), 10);
  ASSERT_EQ(third(0, 1), 10);
  ASSERT_EQ(third(1, 0), 10);
  ASSERT_EQ(third(1, 1), 10);
}

TEST(OperatorMinusEq, test2) {
  S21Matrix first(2, 2);
  first.FillArbitrarily(11);
  S21Matrix second(23, 2);
  second.FillArbitrarily(4);
  ASSERT_ANY_THROW(first -= second);
}

TEST(OperatorMultEq, test1) {
  S21Matrix first(2, 3);
  first.FillArbitrarily(11);
  S21Matrix second(3, 2);
  second.FillArbitrarily(2);
  S21Matrix third = first *= second;
  ASSERT_EQ(third(0, 0), 66);
  ASSERT_EQ(third(0, 1), 66);
  ASSERT_EQ(third(1, 0), 66);
  ASSERT_EQ(third(1, 1), 66);
}

TEST(OperatorMultEq, test2) {
  S21Matrix first(2, 2);
  first.FillArbitrarily(11);
  S21Matrix second(23, 2);
  second.FillArbitrarily(4);
  ASSERT_ANY_THROW(first *= second);
}

TEST(OperatorEqAsMove, test2) {
  S21Matrix first(2, 2);
  first.FillArbitrarily(11);
  S21Matrix second(23, 2);
  second.FillArbitrarily(4);
  first = std::move(second);
  ASSERT_EQ(first(0, 0), 4);
}

TEST(OperatorEqMove, test1) {
  S21Matrix first(2, 2);
  first.FillArbitrarily(11);
  S21Matrix second(23, 2);
  second.FillArbitrarily(4);
  ASSERT_ANY_THROW(first -= second);
}

TEST(OperatorParenthesis, test1) {
  S21Matrix first(2, 2);
  ASSERT_ANY_THROW(first(-1, 0));
}

TEST(OperatorParenthesis, test2) {
  S21Matrix first(2, 2);
  // std::cout << first.GetCols() << std::endl;
  // std::cout << first.GetRows() << std::endl;
  ASSERT_ANY_THROW(first(3, 5));
}

TEST(OperatorParenthesis, test3) {
  S21Matrix first(2, 2);
  // std::cout << first.GetCols() << std::endl;
  // std::cout << first.GetRows() << std::endl;
  first.FillArbitrarily(11);
  ASSERT_EQ(first(0, 0), 11);
}

TEST(OperatorParenthesis, test4) {
  const S21Matrix first(2, 2);
  // std::cout << first.GetCols() << std::endl;
  // std::cout << first.GetRows() << std::endl;
  ASSERT_ANY_THROW(first(3, 5));
}

TEST(OperatorParenthesis, test5) {
  const S21Matrix first(2, 2);
  // std::cout << first.GetCols() << std::endl;
  // std::cout << first.GetRows() << std::endl;
  ASSERT_ANY_THROW(first(-3, 1));
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}