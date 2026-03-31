#include <gtest/gtest.h>
#include <Eigen/Core>

namespace glomap {
double GetOrientationSignum(const Eigen::Matrix3d& F,
                            const Eigen::Vector3d& epipole,
                            const Eigen::Vector2d& pt1,
                            const Eigen::Vector2d& pt2);
}

class GetOrientationSignumTest_136 : public ::testing::Test {
 protected:
  Eigen::Matrix3d F;
  Eigen::Vector3d epipole;
  Eigen::Vector2d pt1;
  Eigen::Vector2d pt2;

  void SetUp() override {
    F.setZero();
    epipole.setZero();
    pt1.setZero();
    pt2.setZero();
  }
};

// Test with all zeros: result should be 0
TEST_F(GetOrientationSignumTest_136, AllZeros_136) {
  double result = glomap::GetOrientationSignum(F, epipole, pt1, pt2);
  EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test with identity fundamental matrix and known values
TEST_F(GetOrientationSignumTest_136, IdentityF_136) {
  F = Eigen::Matrix3d::Identity();
  epipole << 1.0, 2.0, 3.0;
  pt1 << 0.5, 0.5;
  pt2 << 1.0, 1.0;

  // signum1 = F(0,0)*pt2[0] + F(1,0)*pt2[1] + F(2,0)
  //         = 1.0*1.0 + 0.0*1.0 + 0.0 = 1.0
  // signum2 = epipole(1) - epipole(2)*pt1[1]
  //         = 2.0 - 3.0*0.5 = 0.5
  // result  = 1.0 * 0.5 = 0.5
  double result = glomap::GetOrientationSignum(F, epipole, pt1, pt2);
  EXPECT_DOUBLE_EQ(result, 0.5);
}

// Test that the result can be positive
TEST_F(GetOrientationSignumTest_136, PositiveResult_136) {
  F << 1.0, 0.0, 0.0,
       0.0, 1.0, 0.0,
       0.0, 0.0, 1.0;
  epipole << 0.0, 5.0, 1.0;
  pt1 << 1.0, 2.0;
  pt2 << 3.0, 4.0;

  // signum1 = 1.0*3.0 + 0.0*4.0 + 0.0 = 3.0
  // signum2 = 5.0 - 1.0*2.0 = 3.0
  // result  = 3.0 * 3.0 = 9.0
  double result = glomap::GetOrientationSignum(F, epipole, pt1, pt2);
  EXPECT_DOUBLE_EQ(result, 9.0);
}

// Test that the result can be negative
TEST_F(GetOrientationSignumTest_136, NegativeResult_136) {
  F << 1.0, 0.0, 0.0,
       0.0, 1.0, 0.0,
       0.0, 0.0, 1.0;
  epipole << 0.0, 1.0, 1.0;
  pt1 << 0.0, 5.0;
  pt2 << 1.0, 0.0;

  // signum1 = 1.0*1.0 + 0.0*0.0 + 0.0 = 1.0
  // signum2 = 1.0 - 1.0*5.0 = -4.0
  // result  = 1.0 * (-4.0) = -4.0
  double result = glomap::GetOrientationSignum(F, epipole, pt1, pt2);
  EXPECT_DOUBLE_EQ(result, -4.0);
}

// Test that only the first column of F matters
TEST_F(GetOrientationSignumTest_136, OnlyFirstColumnOfFMatters_136) {
  Eigen::Matrix3d F1;
  F1 << 2.0, 99.0, 99.0,
        3.0, 99.0, 99.0,
        4.0, 99.0, 99.0;

  Eigen::Matrix3d F2;
  F2 << 2.0, -5.0, 0.0,
        3.0, 100.0, -7.0,
        4.0, 42.0, 13.0;

  epipole << 1.0, 2.0, 0.5;
  pt1 << 1.0, 1.0;
  pt2 << 1.0, 1.0;

  double result1 = glomap::GetOrientationSignum(F1, epipole, pt1, pt2);
  double result2 = glomap::GetOrientationSignum(F2, epipole, pt1, pt2);
  EXPECT_DOUBLE_EQ(result1, result2);
}

// Test with pt2 being zero: signum1 depends only on F(2,0)
TEST_F(GetOrientationSignumTest_136, Pt2Zero_136) {
  F << 5.0, 0.0, 0.0,
       6.0, 0.0, 0.0,
       7.0, 0.0, 0.0;
  epipole << 0.0, 3.0, 1.0;
  pt1 << 0.0, 1.0;
  pt2 << 0.0, 0.0;

  // signum1 = 5.0*0.0 + 6.0*0.0 + 7.0 = 7.0
  // signum2 = 3.0 - 1.0*1.0 = 2.0
  // result  = 7.0 * 2.0 = 14.0
  double result = glomap::GetOrientationSignum(F, epipole, pt1, pt2);
  EXPECT_DOUBLE_EQ(result, 14.0);
}

// Test with pt1 being zero: signum2 depends only on epipole(1)
TEST_F(GetOrientationSignumTest_136, Pt1Zero_136) {
  F << 1.0, 0.0, 0.0,
       0.0, 0.0, 0.0,
       0.0, 0.0, 0.0;
  epipole << 0.0, 7.0, 3.0;
  pt1 << 0.0, 0.0;
  pt2 << 2.0, 0.0;

  // signum1 = 1.0*2.0 + 0.0*0.0 + 0.0 = 2.0
  // signum2 = 7.0 - 3.0*0.0 = 7.0
  // result  = 2.0 * 7.0 = 14.0
  double result = glomap::GetOrientationSignum(F, epipole, pt1, pt2);
  EXPECT_DOUBLE_EQ(result, 14.0);
}

// Test where signum1 is zero (result should be zero regardless of signum2)
TEST_F(GetOrientationSignumTest_136, Signum1Zero_136) {
  F.setZero();
  epipole << 0.0, 100.0, 0.0;
  pt1 << 1.0, 1.0;
  pt2 << 1.0, 1.0;

  // signum1 = 0 + 0 + 0 = 0
  // signum2 = 100.0 - 0.0*1.0 = 100.0
  // result  = 0.0 * 100.0 = 0.0
  double result = glomap::GetOrientationSignum(F, epipole, pt1, pt2);
  EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test where signum2 is zero (result should be zero regardless of signum1)
TEST_F(GetOrientationSignumTest_136, Signum2Zero_136) {
  F << 1.0, 0.0, 0.0,
       0.0, 0.0, 0.0,
       0.0, 0.0, 0.0;
  epipole << 0.0, 2.0, 1.0;
  pt1 << 0.0, 2.0;  // signum2 = 2.0 - 1.0*2.0 = 0.0
  pt2 << 5.0, 0.0;

  // signum1 = 1.0*5.0 = 5.0
  // signum2 = 0.0
  // result  = 0.0
  double result = glomap::GetOrientationSignum(F, epipole, pt1, pt2);
  EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test with large values
TEST_F(GetOrientationSignumTest_136, LargeValues_136) {
  F << 1e6, 0.0, 0.0,
       1e6, 0.0, 0.0,
       1e6, 0.0, 0.0;
  epipole << 0.0, 1e6, 1.0;
  pt1 << 0.0, 0.0;
  pt2 << 1.0, 1.0;

  // signum1 = 1e6*1.0 + 1e6*1.0 + 1e6 = 3e6
  // signum2 = 1e6 - 1.0*0.0 = 1e6
  // result  = 3e6 * 1e6 = 3e12
  double result = glomap::GetOrientationSignum(F, epipole, pt1, pt2);
  EXPECT_DOUBLE_EQ(result, 3e12);
}

// Test with negative values in F
TEST_F(GetOrientationSignumTest_136, NegativeFValues_136) {
  F << -1.0, 0.0, 0.0,
       -2.0, 0.0, 0.0,
       -3.0, 0.0, 0.0;
  epipole << 0.0, 1.0, 0.0;
  pt1 << 1.0, 1.0;
  pt2 << 1.0, 1.0;

  // signum1 = -1.0*1.0 + (-2.0)*1.0 + (-3.0) = -6.0
  // signum2 = 1.0 - 0.0*1.0 = 1.0
  // result  = -6.0 * 1.0 = -6.0
  double result = glomap::GetOrientationSignum(F, epipole, pt1, pt2);
  EXPECT_DOUBLE_EQ(result, -6.0);
}

// Test with fractional values
TEST_F(GetOrientationSignumTest_136, FractionalValues_136) {
  F << 0.5, 0.0, 0.0,
       0.25, 0.0, 0.0,
       0.125, 0.0, 0.0;
  epipole << 0.0, 0.75, 0.5;
  pt1 << 0.0, 0.5;
  pt2 << 0.5, 0.5;

  // signum1 = 0.5*0.5 + 0.25*0.5 + 0.125 = 0.25 + 0.125 + 0.125 = 0.5
  // signum2 = 0.75 - 0.5*0.5 = 0.75 - 0.25 = 0.5
  // result  = 0.5 * 0.5 = 0.25
  double result = glomap::GetOrientationSignum(F, epipole, pt1, pt2);
  EXPECT_DOUBLE_EQ(result, 0.25);
}

// Test that epipole(0) does not affect the result
TEST_F(GetOrientationSignumTest_136, Epipole0DoesNotMatter_136) {
  F << 1.0, 0.0, 0.0,
       0.0, 0.0, 0.0,
       0.0, 0.0, 0.0;
  Eigen::Vector3d epipole1(0.0, 2.0, 1.0);
  Eigen::Vector3d epipole2(999.0, 2.0, 1.0);
  pt1 << 1.0, 0.5;
  pt2 << 3.0, 0.0;

  double result1 = glomap::GetOrientationSignum(F, epipole1, pt1, pt2);
  double result2 = glomap::GetOrientationSignum(F, epipole2, pt1, pt2);
  EXPECT_DOUBLE_EQ(result1, result2);
}

// Test with negative epipole values
TEST_F(GetOrientationSignumTest_136, NegativeEpipole_136) {
  F << 1.0, 0.0, 0.0,
       1.0, 0.0, 0.0,
       1.0, 0.0, 0.0;
  epipole << 0.0, -3.0, -2.0;
  pt1 << 0.0, 1.0;
  pt2 << 1.0, 1.0;

  // signum1 = 1.0*1.0 + 1.0*1.0 + 1.0 = 3.0
  // signum2 = -3.0 - (-2.0)*1.0 = -3.0 + 2.0 = -1.0
  // result  = 3.0 * (-1.0) = -3.0
  double result = glomap::GetOrientationSignum(F, epipole, pt1, pt2);
  EXPECT_DOUBLE_EQ(result, -3.0);
}

// Test symmetry: swapping sign of both signum1 and signum2 inputs should give positive result
TEST_F(GetOrientationSignumTest_136, DoubleNegationPreservesSign_136) {
  // Setup where both signum1 and signum2 are negative
  F << -1.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0;
  epipole << 0.0, -1.0, 0.0;
  pt1 << 0.0, 0.0;
  pt2 << 1.0, 0.0;

  // signum1 = -1.0*1.0 + 0 + 0 = -1.0
  // signum2 = -1.0 - 0 = -1.0
  // result  = (-1.0) * (-1.0) = 1.0
  double result = glomap::GetOrientationSignum(F, epipole, pt1, pt2);
  EXPECT_DOUBLE_EQ(result, 1.0);
  EXPECT_GT(result, 0.0);
}
