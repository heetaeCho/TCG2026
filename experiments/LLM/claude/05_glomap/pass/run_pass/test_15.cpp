#include <gtest/gtest.h>
#include <Eigen/Core>
#include "./TestProjects/glomap/glomap/estimators/cost_function.h"

namespace glomap {
namespace {

class FetzerDTest_15 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test with zero vectors - all components should be zero
TEST_F(FetzerDTest_15, ZeroVectors_15) {
  Eigen::Vector3d ai = Eigen::Vector3d::Zero();
  Eigen::Vector3d bi = Eigen::Vector3d::Zero();
  Eigen::Vector3d aj = Eigen::Vector3d::Zero();
  Eigen::Vector3d bj = Eigen::Vector3d::Zero();

  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, 0, 1);
  EXPECT_DOUBLE_EQ(result(0), 0.0);
  EXPECT_DOUBLE_EQ(result(1), 0.0);
  EXPECT_DOUBLE_EQ(result(2), 0.0);
  EXPECT_DOUBLE_EQ(result(3), 0.0);
}

// Test with identity-like vectors and u=0, v=1
TEST_F(FetzerDTest_15, BasicComputation_UV01_15) {
  Eigen::Vector3d ai(1.0, 2.0, 3.0);
  Eigen::Vector3d bi(4.0, 5.0, 6.0);
  Eigen::Vector3d aj(7.0, 8.0, 9.0);
  Eigen::Vector3d bj(10.0, 11.0, 12.0);

  int u = 0, v = 1;
  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);

  // d(0) = ai(0)*aj(1) - ai(1)*aj(0) = 1*8 - 2*7 = 8 - 14 = -6
  EXPECT_DOUBLE_EQ(result(0), -6.0);
  // d(1) = ai(0)*bj(1) - ai(1)*bj(0) = 1*11 - 2*10 = 11 - 20 = -9
  EXPECT_DOUBLE_EQ(result(1), -9.0);
  // d(2) = bi(0)*aj(1) - bi(1)*aj(0) = 4*8 - 5*7 = 32 - 35 = -3
  EXPECT_DOUBLE_EQ(result(2), -3.0);
  // d(3) = bi(0)*bj(1) - bi(1)*bj(0) = 4*11 - 5*10 = 44 - 50 = -6
  EXPECT_DOUBLE_EQ(result(3), -6.0);
}

// Test with u=0, v=2
TEST_F(FetzerDTest_15, BasicComputation_UV02_15) {
  Eigen::Vector3d ai(1.0, 2.0, 3.0);
  Eigen::Vector3d bi(4.0, 5.0, 6.0);
  Eigen::Vector3d aj(7.0, 8.0, 9.0);
  Eigen::Vector3d bj(10.0, 11.0, 12.0);

  int u = 0, v = 2;
  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);

  // d(0) = ai(0)*aj(2) - ai(2)*aj(0) = 1*9 - 3*7 = 9 - 21 = -12
  EXPECT_DOUBLE_EQ(result(0), -12.0);
  // d(1) = ai(0)*bj(2) - ai(2)*bj(0) = 1*12 - 3*10 = 12 - 30 = -18
  EXPECT_DOUBLE_EQ(result(1), -18.0);
  // d(2) = bi(0)*aj(2) - bi(2)*aj(0) = 4*9 - 6*7 = 36 - 42 = -6
  EXPECT_DOUBLE_EQ(result(2), -6.0);
  // d(3) = bi(0)*bj(2) - bi(2)*bj(0) = 4*12 - 6*10 = 48 - 60 = -12
  EXPECT_DOUBLE_EQ(result(3), -12.0);
}

// Test with u=1, v=2
TEST_F(FetzerDTest_15, BasicComputation_UV12_15) {
  Eigen::Vector3d ai(1.0, 2.0, 3.0);
  Eigen::Vector3d bi(4.0, 5.0, 6.0);
  Eigen::Vector3d aj(7.0, 8.0, 9.0);
  Eigen::Vector3d bj(10.0, 11.0, 12.0);

  int u = 1, v = 2;
  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);

  // d(0) = ai(1)*aj(2) - ai(2)*aj(1) = 2*9 - 3*8 = 18 - 24 = -6
  EXPECT_DOUBLE_EQ(result(0), -6.0);
  // d(1) = ai(1)*bj(2) - ai(2)*bj(1) = 2*12 - 3*11 = 24 - 33 = -9
  EXPECT_DOUBLE_EQ(result(1), -9.0);
  // d(2) = bi(1)*aj(2) - bi(2)*aj(1) = 5*9 - 6*8 = 45 - 48 = -3
  EXPECT_DOUBLE_EQ(result(2), -3.0);
  // d(3) = bi(1)*bj(2) - bi(2)*bj(1) = 5*12 - 6*11 = 60 - 66 = -6
  EXPECT_DOUBLE_EQ(result(3), -6.0);
}

// Test with u=v (same index), result should be zero
TEST_F(FetzerDTest_15, SameUV_ResultsInZero_15) {
  Eigen::Vector3d ai(1.0, 2.0, 3.0);
  Eigen::Vector3d bi(4.0, 5.0, 6.0);
  Eigen::Vector3d aj(7.0, 8.0, 9.0);
  Eigen::Vector3d bj(10.0, 11.0, 12.0);

  // When u == v, each component is ai(u)*aj(u) - ai(u)*aj(u) = 0
  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, 1, 1);
  EXPECT_DOUBLE_EQ(result(0), 0.0);
  EXPECT_DOUBLE_EQ(result(1), 0.0);
  EXPECT_DOUBLE_EQ(result(2), 0.0);
  EXPECT_DOUBLE_EQ(result(3), 0.0);
}

// Test with negative values
TEST_F(FetzerDTest_15, NegativeValues_15) {
  Eigen::Vector3d ai(-1.0, -2.0, -3.0);
  Eigen::Vector3d bi(-4.0, -5.0, -6.0);
  Eigen::Vector3d aj(-7.0, -8.0, -9.0);
  Eigen::Vector3d bj(-10.0, -11.0, -12.0);

  int u = 0, v = 1;
  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);

  // d(0) = (-1)*(-8) - (-2)*(-7) = 8 - 14 = -6
  EXPECT_DOUBLE_EQ(result(0), -6.0);
  // d(1) = (-1)*(-11) - (-2)*(-10) = 11 - 20 = -9
  EXPECT_DOUBLE_EQ(result(1), -9.0);
  // d(2) = (-4)*(-8) - (-5)*(-7) = 32 - 35 = -3
  EXPECT_DOUBLE_EQ(result(2), -3.0);
  // d(3) = (-4)*(-11) - (-5)*(-10) = 44 - 50 = -6
  EXPECT_DOUBLE_EQ(result(3), -6.0);
}

// Test antisymmetry: swapping u and v should negate the result
TEST_F(FetzerDTest_15, SwappingUVNegates_15) {
  Eigen::Vector3d ai(1.5, 2.5, 3.5);
  Eigen::Vector3d bi(4.5, 5.5, 6.5);
  Eigen::Vector3d aj(7.5, 8.5, 9.5);
  Eigen::Vector3d bj(10.5, 11.5, 12.5);

  Eigen::Vector4d result_01 = fetzer_d(ai, bi, aj, bj, 0, 1);
  Eigen::Vector4d result_10 = fetzer_d(ai, bi, aj, bj, 1, 0);

  EXPECT_DOUBLE_EQ(result_01(0), -result_10(0));
  EXPECT_DOUBLE_EQ(result_01(1), -result_10(1));
  EXPECT_DOUBLE_EQ(result_01(2), -result_10(2));
  EXPECT_DOUBLE_EQ(result_01(3), -result_10(3));
}

// Test with unit vectors
TEST_F(FetzerDTest_15, UnitVectors_15) {
  Eigen::Vector3d ai(1.0, 0.0, 0.0);
  Eigen::Vector3d bi(0.0, 1.0, 0.0);
  Eigen::Vector3d aj(0.0, 0.0, 1.0);
  Eigen::Vector3d bj(1.0, 0.0, 0.0);

  int u = 0, v = 1;
  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);

  // d(0) = ai(0)*aj(1) - ai(1)*aj(0) = 1*0 - 0*0 = 0
  EXPECT_DOUBLE_EQ(result(0), 0.0);
  // d(1) = ai(0)*bj(1) - ai(1)*bj(0) = 1*0 - 0*1 = 0
  EXPECT_DOUBLE_EQ(result(1), 0.0);
  // d(2) = bi(0)*aj(1) - bi(1)*aj(0) = 0*0 - 1*0 = 0
  EXPECT_DOUBLE_EQ(result(2), 0.0);
  // d(3) = bi(0)*bj(1) - bi(1)*bj(0) = 0*0 - 1*1 = -1
  EXPECT_DOUBLE_EQ(result(3), -1.0);
}

// Test with unit vectors for u=0, v=2
TEST_F(FetzerDTest_15, UnitVectors_UV02_15) {
  Eigen::Vector3d ai(1.0, 0.0, 0.0);
  Eigen::Vector3d bi(0.0, 1.0, 0.0);
  Eigen::Vector3d aj(0.0, 0.0, 1.0);
  Eigen::Vector3d bj(1.0, 0.0, 0.0);

  int u = 0, v = 2;
  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);

  // d(0) = ai(0)*aj(2) - ai(2)*aj(0) = 1*1 - 0*0 = 1
  EXPECT_DOUBLE_EQ(result(0), 1.0);
  // d(1) = ai(0)*bj(2) - ai(2)*bj(0) = 1*0 - 0*1 = 0
  EXPECT_DOUBLE_EQ(result(1), 0.0);
  // d(2) = bi(0)*aj(2) - bi(2)*aj(0) = 0*1 - 0*0 = 0
  EXPECT_DOUBLE_EQ(result(2), 0.0);
  // d(3) = bi(0)*bj(2) - bi(2)*bj(0) = 0*0 - 0*1 = 0
  EXPECT_DOUBLE_EQ(result(3), 0.0);
}

// Test with large values to check no overflow in double precision
TEST_F(FetzerDTest_15, LargeValues_15) {
  double large = 1e10;
  Eigen::Vector3d ai(large, 2.0 * large, 3.0 * large);
  Eigen::Vector3d bi(4.0 * large, 5.0 * large, 6.0 * large);
  Eigen::Vector3d aj(7.0, 8.0, 9.0);
  Eigen::Vector3d bj(10.0, 11.0, 12.0);

  int u = 0, v = 1;
  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);

  // d(0) = large*8 - 2*large*7 = 8e10 - 14e10 = -6e10
  EXPECT_DOUBLE_EQ(result(0), -6.0 * large);
  // d(1) = large*11 - 2*large*10 = 11e10 - 20e10 = -9e10
  EXPECT_DOUBLE_EQ(result(1), -9.0 * large);
  // d(2) = 4*large*8 - 5*large*7 = 32e10 - 35e10 = -3e10
  EXPECT_DOUBLE_EQ(result(2), -3.0 * large);
  // d(3) = 4*large*11 - 5*large*10 = 44e10 - 50e10 = -6e10
  EXPECT_DOUBLE_EQ(result(3), -6.0 * large);
}

// Test with very small values
TEST_F(FetzerDTest_15, SmallValues_15) {
  double small = 1e-15;
  Eigen::Vector3d ai(small, 2.0 * small, 3.0 * small);
  Eigen::Vector3d bi(4.0 * small, 5.0 * small, 6.0 * small);
  Eigen::Vector3d aj(7.0, 8.0, 9.0);
  Eigen::Vector3d bj(10.0, 11.0, 12.0);

  int u = 0, v = 1;
  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);

  EXPECT_NEAR(result(0), -6.0 * small, 1e-28);
  EXPECT_NEAR(result(1), -9.0 * small, 1e-28);
  EXPECT_NEAR(result(2), -3.0 * small, 1e-28);
  EXPECT_NEAR(result(3), -6.0 * small, 1e-28);
}

// Test that when ai == aj and bi == bj, certain symmetry holds
TEST_F(FetzerDTest_15, IdenticalPairs_15) {
  Eigen::Vector3d a(1.0, 2.0, 3.0);
  Eigen::Vector3d b(4.0, 5.0, 6.0);

  // When ai==aj and bi==bj, d(1) should equal d(2)
  // d(1) = a(u)*b(v) - a(v)*b(u)
  // d(2) = b(u)*a(v) - b(v)*a(u) = -(a(u)*b(v) - a(v)*b(u)) = -d(1)
  Eigen::Vector4d result = fetzer_d(a, b, a, b, 0, 1);

  EXPECT_DOUBLE_EQ(result(0), 0.0);  // a cross a in 2D = 0
  EXPECT_DOUBLE_EQ(result(1), -result(2));
  EXPECT_DOUBLE_EQ(result(3), 0.0);  // b cross b in 2D = 0
}

// Test reversed u,v indices (2, 0)
TEST_F(FetzerDTest_15, ReversedIndices_UV20_15) {
  Eigen::Vector3d ai(3.0, 1.0, 4.0);
  Eigen::Vector3d bi(1.0, 5.0, 9.0);
  Eigen::Vector3d aj(2.0, 6.0, 5.0);
  Eigen::Vector3d bj(3.0, 5.0, 8.0);

  int u = 2, v = 0;
  Eigen::Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);

  // d(0) = ai(2)*aj(0) - ai(0)*aj(2) = 4*2 - 3*5 = 8 - 15 = -7
  EXPECT_DOUBLE_EQ(result(0), -7.0);
  // d(1) = ai(2)*bj(0) - ai(0)*bj(2) = 4*3 - 3*8 = 12 - 24 = -12
  EXPECT_DOUBLE_EQ(result(1), -12.0);
  // d(2) = bi(2)*aj(0) - bi(0)*aj(2) = 9*2 - 1*5 = 18 - 5 = 13
  EXPECT_DOUBLE_EQ(result(2), 13.0);
  // d(3) = bi(2)*bj(0) - bi(0)*bj(2) = 9*3 - 1*8 = 27 - 8 = 19
  EXPECT_DOUBLE_EQ(result(3), 19.0);
}

}  // namespace
}  // namespace glomap
