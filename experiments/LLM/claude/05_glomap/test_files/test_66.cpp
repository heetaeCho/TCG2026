#include <gtest/gtest.h>
#include <Eigen/Core>

namespace glomap {
double GetOrientationSignum(const Eigen::Matrix3d& F,
                            const Eigen::Vector3d& epipole,
                            const Eigen::Vector2d& pt1,
                            const Eigen::Vector2d& pt2);
}

class GetOrientationSignumTest_66 : public ::testing::Test {
 protected:
  Eigen::Matrix3d F_;
  Eigen::Vector3d epipole_;
  Eigen::Vector2d pt1_;
  Eigen::Vector2d pt2_;

  void SetUp() override {
    F_.setZero();
    epipole_.setZero();
    pt1_.setZero();
    pt2_.setZero();
  }
};

// Test with identity-like F matrix and simple inputs
TEST_F(GetOrientationSignumTest_66, IdentityFSimpleInputs_66) {
  F_.setIdentity();
  epipole_ << 0.0, 3.0, 1.0;
  pt1_ << 1.0, 1.0;
  pt2_ << 1.0, 1.0;

  // signum1 = F(0,0)*pt2[0] + F(1,0)*pt2[1] + F(2,0) = 1*1 + 0*1 + 0 = 1
  // signum2 = epipole(1) - epipole(2)*pt1[1] = 3 - 1*1 = 2
  // result = 1 * 2 = 2
  double result = glomap::GetOrientationSignum(F_, epipole_, pt1_, pt2_);
  EXPECT_DOUBLE_EQ(result, 2.0);
}

// Test with all zeros - should return zero
TEST_F(GetOrientationSignumTest_66, AllZeros_66) {
  double result = glomap::GetOrientationSignum(F_, epipole_, pt1_, pt2_);
  EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test that the result can be negative
TEST_F(GetOrientationSignumTest_66, NegativeResult_66) {
  F_ << 1, 0, 0,
        0, 1, 0,
        0, 0, 1;
  epipole_ << 0.0, 1.0, 2.0;
  pt1_ << 0.0, 1.0;   // signum2 = 1 - 2*1 = -1
  pt2_ << 1.0, 0.0;   // signum1 = 1*1 + 0*0 + 0 = 1

  double result = glomap::GetOrientationSignum(F_, epipole_, pt1_, pt2_);
  EXPECT_DOUBLE_EQ(result, -1.0);
}

// Test signum1 depends on first column of F and pt2
TEST_F(GetOrientationSignumTest_66, Signum1DependsOnFirstColumnOfF_66) {
  F_ << 2, 99, 99,
        3, 99, 99,
        4, 99, 99;
  epipole_ << 0.0, 5.0, 1.0;
  pt1_ << 0.0, 2.0;
  pt2_ << 1.0, 1.0;

  // signum1 = F(0,0)*pt2[0] + F(1,0)*pt2[1] + F(2,0) = 2*1 + 3*1 + 4 = 9
  // signum2 = epipole(1) - epipole(2)*pt1[1] = 5 - 1*2 = 3
  // result = 9 * 3 = 27
  double result = glomap::GetOrientationSignum(F_, epipole_, pt1_, pt2_);
  EXPECT_DOUBLE_EQ(result, 27.0);
}

// Test that non-first-column entries of F don't affect the result
TEST_F(GetOrientationSignumTest_66, NonFirstColumnDoesNotAffect_66) {
  F_ << 1, 0, 0,
        0, 0, 0,
        0, 0, 0;
  epipole_ << 0.0, 1.0, 0.0;
  pt1_ << 0.0, 0.0;
  pt2_ << 5.0, 3.0;

  // signum1 = 1*5 + 0*3 + 0 = 5
  // signum2 = 1 - 0*0 = 1
  double result1 = glomap::GetOrientationSignum(F_, epipole_, pt1_, pt2_);

  // Change non-first-column entries
  F_ << 1, 100, 200,
        0, 300, 400,
        0, 500, 600;
  double result2 = glomap::GetOrientationSignum(F_, epipole_, pt1_, pt2_);

  EXPECT_DOUBLE_EQ(result1, result2);
}

// Test with large values
TEST_F(GetOrientationSignumTest_66, LargeValues_66) {
  F_ << 1e6, 0, 0,
        1e6, 0, 0,
        1e6, 0, 0;
  epipole_ << 0.0, 1e6, 1.0;
  pt1_ << 0.0, 0.0;
  pt2_ << 1.0, 1.0;

  // signum1 = 1e6*1 + 1e6*1 + 1e6 = 3e6
  // signum2 = 1e6 - 1*0 = 1e6
  // result = 3e6 * 1e6 = 3e12
  double result = glomap::GetOrientationSignum(F_, epipole_, pt1_, pt2_);
  EXPECT_DOUBLE_EQ(result, 3e12);
}

// Test where signum1 is zero
TEST_F(GetOrientationSignumTest_66, Signum1Zero_66) {
  F_.setZero();
  epipole_ << 0.0, 5.0, 1.0;
  pt1_ << 0.0, 1.0;
  pt2_ << 1.0, 1.0;

  // signum1 = 0
  // result = 0 * anything = 0
  double result = glomap::GetOrientationSignum(F_, epipole_, pt1_, pt2_);
  EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test where signum2 is zero
TEST_F(GetOrientationSignumTest_66, Signum2Zero_66) {
  F_.setIdentity();
  epipole_ << 0.0, 2.0, 1.0;
  pt1_ << 0.0, 2.0;  // signum2 = 2 - 1*2 = 0
  pt2_ << 1.0, 1.0;

  double result = glomap::GetOrientationSignum(F_, epipole_, pt1_, pt2_);
  EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test epipole(0) does not affect result
TEST_F(GetOrientationSignumTest_66, EpipoleFirstComponentIrrelevant_66) {
  F_.setIdentity();
  epipole_ << 100.0, 3.0, 1.0;
  pt1_ << 1.0, 1.0;
  pt2_ << 1.0, 1.0;

  double result1 = glomap::GetOrientationSignum(F_, epipole_, pt1_, pt2_);

  epipole_ << -999.0, 3.0, 1.0;
  double result2 = glomap::GetOrientationSignum(F_, epipole_, pt1_, pt2_);

  EXPECT_DOUBLE_EQ(result1, result2);
}

// Test pt1[0] does not affect result
TEST_F(GetOrientationSignumTest_66, Pt1FirstComponentIrrelevant_66) {
  F_.setIdentity();
  epipole_ << 0.0, 3.0, 1.0;
  pt1_ << 0.0, 1.0;
  pt2_ << 1.0, 1.0;

  double result1 = glomap::GetOrientationSignum(F_, epipole_, pt1_, pt2_);

  pt1_ << 999.0, 1.0;
  double result2 = glomap::GetOrientationSignum(F_, epipole_, pt1_, pt2_);

  EXPECT_DOUBLE_EQ(result1, result2);
}

// Test with negative coordinates
TEST_F(GetOrientationSignumTest_66, NegativeCoordinates_66) {
  F_ << -1, 0, 0,
         0, -1, 0,
         0,  0, -1;
  epipole_ << 0.0, -2.0, -1.0;
  pt1_ << 0.0, -3.0;
  pt2_ << -2.0, -1.0;

  // signum1 = (-1)*(-2) + 0*(-1) + 0 = 2
  // signum2 = (-2) - (-1)*(-3) = -2 - 3 = -5
  // result = 2 * (-5) = -10
  double result = glomap::GetOrientationSignum(F_, epipole_, pt1_, pt2_);
  EXPECT_DOUBLE_EQ(result, -10.0);
}

// Test positive * positive = positive
TEST_F(GetOrientationSignumTest_66, PositiveTimesPositive_66) {
  F_ << 1, 0, 0,
        1, 0, 0,
        1, 0, 0;
  epipole_ << 0.0, 10.0, 1.0;
  pt1_ << 0.0, 1.0;
  pt2_ << 1.0, 1.0;

  // signum1 = 1 + 1 + 1 = 3
  // signum2 = 10 - 1 = 9
  // result = 27 > 0
  double result = glomap::GetOrientationSignum(F_, epipole_, pt1_, pt2_);
  EXPECT_GT(result, 0.0);
  EXPECT_DOUBLE_EQ(result, 27.0);
}

// Test with fractional values
TEST_F(GetOrientationSignumTest_66, FractionalValues_66) {
  F_ << 0.5, 0, 0,
        0.5, 0, 0,
        0.5, 0, 0;
  epipole_ << 0.0, 1.5, 0.5;
  pt1_ << 0.0, 1.0;
  pt2_ << 2.0, 2.0;

  // signum1 = 0.5*2 + 0.5*2 + 0.5 = 1 + 1 + 0.5 = 2.5
  // signum2 = 1.5 - 0.5*1 = 1.0
  // result = 2.5 * 1.0 = 2.5
  double result = glomap::GetOrientationSignum(F_, epipole_, pt1_, pt2_);
  EXPECT_DOUBLE_EQ(result, 2.5);
}
