#include <gtest/gtest.h>
#include <Eigen/Core>
#include "./TestProjects/glomap/glomap/estimators/cost_function.h"

namespace glomap {
namespace {

class FetzerDTest_91 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test basic computation with simple unit vectors
TEST_F(FetzerDTest_91, BasicComputation_91) {
  Eigen::Vector3d ai(1.0, 0.0, 0.0);
  Eigen::Vector3d bi(0.0, 1.0, 0.0);
  Eigen::Vector3d aj(0.0, 0.0, 1.0);
  Eigen::Vector3d bj(1.0, 1.0, 1.0);

  // u=0, v=1: 
  // d(0) = ai(0)*aj(1) - ai(1)*aj(0) = 1*0 - 0*0 = 0
  // d(1) = ai(0)*bj(1) - ai(1)*bj(0) = 1*1 - 0*1 = 1
  // d(2) = bi(0)*aj(1) - bi(1)*aj(0) = 0*0 - 1*0 = 0
  // d(3) = bi(0)*bj(1) - bi(1)*bj(0) = 0*1 - 1*1 = -1
  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, 0, 1);
  EXPECT_DOUBLE_EQ(result(0), 0.0);
  EXPECT_DOUBLE_EQ(result(1), 1.0);
  EXPECT_DOUBLE_EQ(result(2), 0.0);
  EXPECT_DOUBLE_EQ(result(3), -1.0);
}

// Test with u=0, v=2
TEST_F(FetzerDTest_91, IndicesZeroTwo_91) {
  Eigen::Vector3d ai(1.0, 2.0, 3.0);
  Eigen::Vector3d bi(4.0, 5.0, 6.0);
  Eigen::Vector3d aj(7.0, 8.0, 9.0);
  Eigen::Vector3d bj(10.0, 11.0, 12.0);

  // u=0, v=2:
  // d(0) = ai(0)*aj(2) - ai(2)*aj(0) = 1*9 - 3*7 = 9-21 = -12
  // d(1) = ai(0)*bj(2) - ai(2)*bj(0) = 1*12 - 3*10 = 12-30 = -18
  // d(2) = bi(0)*aj(2) - bi(2)*aj(0) = 4*9 - 6*7 = 36-42 = -6
  // d(3) = bi(0)*bj(2) - bi(2)*bj(0) = 4*12 - 6*10 = 48-60 = -12
  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, 0, 2);
  EXPECT_DOUBLE_EQ(result(0), -12.0);
  EXPECT_DOUBLE_EQ(result(1), -18.0);
  EXPECT_DOUBLE_EQ(result(2), -6.0);
  EXPECT_DOUBLE_EQ(result(3), -12.0);
}

// Test with u=1, v=2
TEST_F(FetzerDTest_91, IndicesOneTwo_91) {
  Eigen::Vector3d ai(1.0, 2.0, 3.0);
  Eigen::Vector3d bi(4.0, 5.0, 6.0);
  Eigen::Vector3d aj(7.0, 8.0, 9.0);
  Eigen::Vector3d bj(10.0, 11.0, 12.0);

  // u=1, v=2:
  // d(0) = ai(1)*aj(2) - ai(2)*aj(1) = 2*9 - 3*8 = 18-24 = -6
  // d(1) = ai(1)*bj(2) - ai(2)*bj(1) = 2*12 - 3*11 = 24-33 = -9
  // d(2) = bi(1)*aj(2) - bi(2)*aj(1) = 5*9 - 6*8 = 45-48 = -3
  // d(3) = bi(1)*bj(2) - bi(2)*bj(1) = 5*12 - 6*11 = 60-66 = -6
  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, 1, 2);
  EXPECT_DOUBLE_EQ(result(0), -6.0);
  EXPECT_DOUBLE_EQ(result(1), -9.0);
  EXPECT_DOUBLE_EQ(result(2), -3.0);
  EXPECT_DOUBLE_EQ(result(3), -6.0);
}

// Test all-zero vectors produce zero result
TEST_F(FetzerDTest_91, AllZeroVectors_91) {
  Eigen::Vector3d zero = Eigen::Vector3d::Zero();
  Eigen::Vector4d result = fetzer_d(zero, zero, zero, zero, 0, 1);
  EXPECT_DOUBLE_EQ(result(0), 0.0);
  EXPECT_DOUBLE_EQ(result(1), 0.0);
  EXPECT_DOUBLE_EQ(result(2), 0.0);
  EXPECT_DOUBLE_EQ(result(3), 0.0);
}

// Test identical vectors: when ai==bi and aj==bj, all four components should be equal
TEST_F(FetzerDTest_91, IdenticalAiBiAndAjBj_91) {
  Eigen::Vector3d ai(3.0, 5.0, 7.0);
  Eigen::Vector3d aj(2.0, 4.0, 6.0);

  Eigen::Vector4d result = fetzer_d(ai, ai, aj, aj, 0, 1);
  // All four should be equal since ai==bi and aj==bj
  EXPECT_DOUBLE_EQ(result(0), result(1));
  EXPECT_DOUBLE_EQ(result(0), result(2));
  EXPECT_DOUBLE_EQ(result(0), result(3));
  // Actual value: ai(0)*aj(1) - ai(1)*aj(0) = 3*4 - 5*2 = 12-10 = 2
  EXPECT_DOUBLE_EQ(result(0), 2.0);
}

// Test when u == v, the result should be zero
TEST_F(FetzerDTest_91, SameIndicesProduceZero_91) {
  Eigen::Vector3d ai(1.0, 2.0, 3.0);
  Eigen::Vector3d bi(4.0, 5.0, 6.0);
  Eigen::Vector3d aj(7.0, 8.0, 9.0);
  Eigen::Vector3d bj(10.0, 11.0, 12.0);

  // When u == v, each component is a(u)*b(v) - a(v)*b(u) = a(u)*b(u) - a(u)*b(u) = 0
  Eigen::Vector4d result0 = fetzer_d(ai, bi, aj, bj, 0, 0);
  EXPECT_DOUBLE_EQ(result0(0), 0.0);
  EXPECT_DOUBLE_EQ(result0(1), 0.0);
  EXPECT_DOUBLE_EQ(result0(2), 0.0);
  EXPECT_DOUBLE_EQ(result0(3), 0.0);

  Eigen::Vector4d result1 = fetzer_d(ai, bi, aj, bj, 1, 1);
  EXPECT_DOUBLE_EQ(result1(0), 0.0);
  EXPECT_DOUBLE_EQ(result1(1), 0.0);
  EXPECT_DOUBLE_EQ(result1(2), 0.0);
  EXPECT_DOUBLE_EQ(result1(3), 0.0);

  Eigen::Vector4d result2 = fetzer_d(ai, bi, aj, bj, 2, 2);
  EXPECT_DOUBLE_EQ(result2(0), 0.0);
  EXPECT_DOUBLE_EQ(result2(1), 0.0);
  EXPECT_DOUBLE_EQ(result2(2), 0.0);
  EXPECT_DOUBLE_EQ(result2(3), 0.0);
}

// Test antisymmetry: swapping u and v should negate all components
TEST_F(FetzerDTest_91, AntisymmetryOnSwappingUV_91) {
  Eigen::Vector3d ai(1.5, 2.5, 3.5);
  Eigen::Vector3d bi(4.5, 5.5, 6.5);
  Eigen::Vector3d aj(7.5, 8.5, 9.5);
  Eigen::Vector3d bj(10.5, 11.5, 12.5);

  Eigen::Vector4d result_01 = fetzer_d(ai, bi, aj, bj, 0, 1);
  Eigen::Vector4d result_10 = fetzer_d(ai, bi, aj, bj, 1, 0);

  for (int k = 0; k < 4; ++k) {
    EXPECT_DOUBLE_EQ(result_01(k), -result_10(k));
  }
}

// Test with negative values
TEST_F(FetzerDTest_91, NegativeValues_91) {
  Eigen::Vector3d ai(-1.0, -2.0, -3.0);
  Eigen::Vector3d bi(-4.0, -5.0, -6.0);
  Eigen::Vector3d aj(-7.0, -8.0, -9.0);
  Eigen::Vector3d bj(-10.0, -11.0, -12.0);

  // u=0, v=1:
  // d(0) = (-1)*(-8) - (-2)*(-7) = 8 - 14 = -6
  // d(1) = (-1)*(-11) - (-2)*(-10) = 11 - 20 = -9
  // d(2) = (-4)*(-8) - (-5)*(-7) = 32 - 35 = -3
  // d(3) = (-4)*(-11) - (-5)*(-10) = 44 - 50 = -6
  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, 0, 1);
  EXPECT_DOUBLE_EQ(result(0), -6.0);
  EXPECT_DOUBLE_EQ(result(1), -9.0);
  EXPECT_DOUBLE_EQ(result(2), -3.0);
  EXPECT_DOUBLE_EQ(result(3), -6.0);
}

// Test with large values to check no overflow issues at double precision
TEST_F(FetzerDTest_91, LargeValues_91) {
  double large = 1e15;
  Eigen::Vector3d ai(large, 2.0 * large, 3.0 * large);
  Eigen::Vector3d bi(4.0 * large, 5.0 * large, 6.0 * large);
  Eigen::Vector3d aj(7.0, 8.0, 9.0);
  Eigen::Vector3d bj(10.0, 11.0, 12.0);

  // u=0, v=1:
  // d(0) = large*8 - 2*large*7 = 8e15 - 14e15 = -6e15
  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, 0, 1);
  EXPECT_DOUBLE_EQ(result(0), -6.0e15);
}

// Test with fractional / floating point values
TEST_F(FetzerDTest_91, FractionalValues_91) {
  Eigen::Vector3d ai(0.1, 0.2, 0.3);
  Eigen::Vector3d bi(0.4, 0.5, 0.6);
  Eigen::Vector3d aj(0.7, 0.8, 0.9);
  Eigen::Vector3d bj(1.0, 1.1, 1.2);

  // u=0, v=1:
  // d(0) = 0.1*0.8 - 0.2*0.7 = 0.08 - 0.14 = -0.06
  // d(1) = 0.1*1.1 - 0.2*1.0 = 0.11 - 0.20 = -0.09
  // d(2) = 0.4*0.8 - 0.5*0.7 = 0.32 - 0.35 = -0.03
  // d(3) = 0.4*1.1 - 0.5*1.0 = 0.44 - 0.50 = -0.06
  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, 0, 1);
  EXPECT_NEAR(result(0), -0.06, 1e-14);
  EXPECT_NEAR(result(1), -0.09, 1e-14);
  EXPECT_NEAR(result(2), -0.03, 1e-14);
  EXPECT_NEAR(result(3), -0.06, 1e-14);
}

// Test swapping i and j vectors
TEST_F(FetzerDTest_91, SwappingIJVectors_91) {
  Eigen::Vector3d ai(1.0, 2.0, 3.0);
  Eigen::Vector3d bi(4.0, 5.0, 6.0);
  Eigen::Vector3d aj(7.0, 8.0, 9.0);
  Eigen::Vector3d bj(10.0, 11.0, 12.0);

  Eigen::Vector4d original = fetzer_d(ai, bi, aj, bj, 0, 1);
  Eigen::Vector4d swapped = fetzer_d(aj, bj, ai, bi, 0, 1);

  // d_orig(0) = ai(0)*aj(1) - ai(1)*aj(0)
  // d_swap(0) = aj(0)*ai(1) - aj(1)*ai(0) = -d_orig(0)
  EXPECT_DOUBLE_EQ(original(0), -swapped(0));
  // d_orig(1) = ai(0)*bj(1) - ai(1)*bj(0)
  // d_swap(2) = bj(0)*ai(1) - bj(1)*ai(0) = -d_orig(1)
  EXPECT_DOUBLE_EQ(original(1), -swapped(2));
  // d_orig(2) = bi(0)*aj(1) - bi(1)*aj(0)
  // d_swap(1) = aj(0)*bi(1) - aj(1)*bi(0) = -d_orig(2)
  EXPECT_DOUBLE_EQ(original(2), -swapped(1));
  // d_orig(3) = bi(0)*bj(1) - bi(1)*bj(0)
  // d_swap(3) = bj(0)*bi(1) - bj(1)*bi(0) = -d_orig(3)
  EXPECT_DOUBLE_EQ(original(3), -swapped(3));
}

// Test all index combinations
TEST_F(FetzerDTest_91, AllIndexCombinations_91) {
  Eigen::Vector3d ai(1.0, 2.0, 3.0);
  Eigen::Vector3d bi(4.0, 5.0, 6.0);
  Eigen::Vector3d aj(7.0, 8.0, 9.0);
  Eigen::Vector3d bj(10.0, 11.0, 12.0);

  // u=1, v=0
  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, 1, 0);
  // d(0) = ai(1)*aj(0) - ai(0)*aj(1) = 2*7 - 1*8 = 14 - 8 = 6
  // d(1) = ai(1)*bj(0) - ai(0)*bj(1) = 2*10 - 1*11 = 20 - 11 = 9
  // d(2) = bi(1)*aj(0) - bi(0)*aj(1) = 5*7 - 4*8 = 35 - 32 = 3
  // d(3) = bi(1)*bj(0) - bi(0)*bj(1) = 5*10 - 4*11 = 50 - 44 = 6
  EXPECT_DOUBLE_EQ(result(0), 6.0);
  EXPECT_DOUBLE_EQ(result(1), 9.0);
  EXPECT_DOUBLE_EQ(result(2), 3.0);
  EXPECT_DOUBLE_EQ(result(3), 6.0);

  // u=2, v=0
  result = fetzer_d(ai, bi, aj, bj, 2, 0);
  // d(0) = ai(2)*aj(0) - ai(0)*aj(2) = 3*7 - 1*9 = 21 - 9 = 12
  // d(1) = ai(2)*bj(0) - ai(0)*bj(2) = 3*10 - 1*12 = 30 - 12 = 18
  // d(2) = bi(2)*aj(0) - bi(0)*aj(2) = 6*7 - 4*9 = 42 - 36 = 6
  // d(3) = bi(2)*bj(0) - bi(0)*bj(2) = 6*10 - 4*12 = 60 - 48 = 12
  EXPECT_DOUBLE_EQ(result(0), 12.0);
  EXPECT_DOUBLE_EQ(result(1), 18.0);
  EXPECT_DOUBLE_EQ(result(2), 6.0);
  EXPECT_DOUBLE_EQ(result(3), 12.0);

  // u=2, v=1
  result = fetzer_d(ai, bi, aj, bj, 2, 1);
  // d(0) = ai(2)*aj(1) - ai(1)*aj(2) = 3*8 - 2*9 = 24 - 18 = 6
  // d(1) = ai(2)*bj(1) - ai(1)*bj(2) = 3*11 - 2*12 = 33 - 24 = 9
  // d(2) = bi(2)*aj(1) - bi(1)*aj(2) = 6*8 - 5*9 = 48 - 45 = 3
  // d(3) = bi(2)*bj(1) - bi(1)*bj(2) = 6*11 - 5*12 = 66 - 60 = 6
  EXPECT_DOUBLE_EQ(result(0), 6.0);
  EXPECT_DOUBLE_EQ(result(1), 9.0);
  EXPECT_DOUBLE_EQ(result(2), 3.0);
  EXPECT_DOUBLE_EQ(result(3), 6.0);
}

// Test that result vector has exactly 4 elements
TEST_F(FetzerDTest_91, ResultSize_91) {
  Eigen::Vector3d ai(1.0, 0.0, 0.0);
  Eigen::Vector3d bi(0.0, 1.0, 0.0);
  Eigen::Vector3d aj(0.0, 0.0, 1.0);
  Eigen::Vector3d bj(1.0, 1.0, 1.0);

  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, 0, 1);
  EXPECT_EQ(result.size(), 4);
}

// Test with one vector being zero
TEST_F(FetzerDTest_91, OneZeroVector_91) {
  Eigen::Vector3d ai = Eigen::Vector3d::Zero();
  Eigen::Vector3d bi(4.0, 5.0, 6.0);
  Eigen::Vector3d aj(7.0, 8.0, 9.0);
  Eigen::Vector3d bj(10.0, 11.0, 12.0);

  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, 0, 1);
  // d(0) = 0*8 - 0*7 = 0
  // d(1) = 0*11 - 0*10 = 0
  EXPECT_DOUBLE_EQ(result(0), 0.0);
  EXPECT_DOUBLE_EQ(result(1), 0.0);
  // d(2) = 4*8 - 5*7 = 32 - 35 = -3
  // d(3) = 4*11 - 5*10 = 44 - 50 = -6
  EXPECT_DOUBLE_EQ(result(2), -3.0);
  EXPECT_DOUBLE_EQ(result(3), -6.0);
}

}  // namespace
}  // namespace glomap
