// File: fetzer_focal_length_same_camera_cost_test.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <type_traits>

#include "glomap/estimators/cost_function.h"

namespace glomap {

class FetzerFocalLengthSameCameraCostTest_164 : public ::testing::Test {
 protected:
  Eigen::Matrix3d MakeFundamentalMatrix(double scale = 1.0) {
    Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
    F(0, 1) = -scale;
    F(1, 0) = scale;
    F(2, 2) = 1.0;
    return F;
  }
};

// Basic sanity: construction with identity-like fundamental matrix and zero principal point
TEST_F(FetzerFocalLengthSameCameraCostTest_164,
       ConstructWithZeroPrincipalPoint_164) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
  Eigen::Vector2d principal_point(0.0, 0.0);

  // Just verify that construction succeeds without throwing.
  ASSERT_NO_THROW({
    FetzerFocalLengthSameCameraCost cost(F, principal_point);
    (void)cost;  // silence unused variable warning
  });
}

// Construction with a typical non-zero principal point (normal operation)
TEST_F(FetzerFocalLengthSameCameraCostTest_164,
       ConstructWithTypicalPrincipalPoint_164) {
  Eigen::Matrix3d F = MakeFundamentalMatrix(1.0);
  Eigen::Vector2d principal_point(320.0, 240.0);

  ASSERT_NO_THROW({
    FetzerFocalLengthSameCameraCost cost(F, principal_point);
    (void)cost;
  });
}

// Boundary-like construction: large magnitude principal point values
TEST_F(FetzerFocalLengthSameCameraCostTest_164,
       ConstructWithExtremePrincipalPoint_164) {
  Eigen::Matrix3d F = MakeFundamentalMatrix(10.0);
  Eigen::Vector2d principal_point(1e6, -1e6);

  ASSERT_NO_THROW({
    FetzerFocalLengthSameCameraCost cost(F, principal_point);
    (void)cost;
  });
}

// Interface property: type traits (copy / move constructible)
TEST_F(FetzerFocalLengthSameCameraCostTest_164,
       TypeTraitsCopyMoveConstructible_164) {
  // These checks are about the public interface of the type, not internals.
  EXPECT_TRUE((std::is_copy_constructible<FetzerFocalLengthSameCameraCost>::value));
  EXPECT_TRUE((std::is_move_constructible<FetzerFocalLengthSameCameraCost>::value));
}

}  // namespace glomap
