// File: glomap/tests/fetzer_focal_length_cost_test_163.cc

#include <gtest/gtest.h>
#include <Eigen/Core>

#include "glomap/estimators/cost_function.h"

namespace glomap {

// Simple fixture for FetzerFocalLengthCost.
class FetzerFocalLengthCostTest_163 : public ::testing::Test {};

// -----------------------------------------------------------------------------
// Normal operation: construction with typical, valid inputs should succeed.
// -----------------------------------------------------------------------------
TEST_F(FetzerFocalLengthCostTest_163,
       ConstructWithIdentityFundamentalMatrix_163) {
  // Fundamental matrix (here just using identity as a simple valid 3x3 matrix).
  Eigen::Matrix3d i1_F_i0 = Eigen::Matrix3d::Identity();

  // Principal points at the image center (typical case).
  Eigen::Vector2d principal_point0(320.0, 240.0);
  Eigen::Vector2d principal_point1(320.0, 240.0);

  EXPECT_NO_THROW({
    FetzerFocalLengthCost cost(i1_F_i0, principal_point0, principal_point1);
    (void)cost;  // Silence unused variable warning.
  });
}

// -----------------------------------------------------------------------------
// Boundary condition: construction with a zero fundamental matrix.
// Even though this may not be meaningful numerically, the class should handle
// it without throwing at construction time (as far as the public interface
// reveals).
// -----------------------------------------------------------------------------
TEST_F(FetzerFocalLengthCostTest_163,
       ConstructWithZeroFundamentalMatrix_163) {
  Eigen::Matrix3d i1_F_i0 = Eigen::Matrix3d::Zero();

  Eigen::Vector2d principal_point0(0.0, 0.0);
  Eigen::Vector2d principal_point1(0.0, 0.0);

  EXPECT_NO_THROW({
    FetzerFocalLengthCost cost(i1_F_i0, principal_point0, principal_point1);
    (void)cost;
  });
}

// -----------------------------------------------------------------------------
// Boundary / stress case: construction with large principal point values.
// This checks that the constructor accepts a wide numeric range without
// exposing errors via the public interface (e.g., no exceptions).
// -----------------------------------------------------------------------------
TEST_F(FetzerFocalLengthCostTest_163,
       ConstructWithLargePrincipalPoints_163) {
  Eigen::Matrix3d i1_F_i0;
  i1_F_i0 << 0.1,  0.2, -0.3,
             -0.4, 0.5,  0.6,
              0.7, -0.8, 0.9;

  Eigen::Vector2d principal_point0(1e5, -1e5);
  Eigen::Vector2d principal_point1(-1e5, 1e5);

  EXPECT_NO_THROW({
    FetzerFocalLengthCost cost(i1_F_i0, principal_point0, principal_point1);
    (void)cost;
  });
}

}  // namespace glomap
