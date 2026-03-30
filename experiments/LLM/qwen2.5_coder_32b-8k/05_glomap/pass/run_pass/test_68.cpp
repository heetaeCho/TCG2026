#include <gtest/gtest.h>

#include <Eigen/Dense>

#include "glomap/math/two_view_geometry.cc"



using namespace glomap;

using Eigen::Matrix3d;

using Eigen::Vector2d;



class HomographyErrorTest_68 : public ::testing::Test {

protected:

    Matrix3d H;

    Vector2d x1, x2;



    void SetUp() override {

        // Set up a default homography matrix and points for testing

        H << 1, 0, 0,

             0, 1, 0,

             0, 0, 1;

        x1 << 1, 1;

        x2 << 1, 1;

    }

};



TEST_F(HomographyErrorTest_68, IdentityHomography_ZeroError_68) {

    // Test with identity homography and points that match

    double error = HomographyError(H, x1, x2);

    EXPECT_DOUBLE_EQ(error, 0.0);

}



TEST_F(HomographyErrorTest_68, NonIdentityHomography_NonZeroError_68) {

    // Test with a non-identity homography and points that do not match

    H << 1, 0, 1,

         0, 1, 1,

         0, 0, 1;

    double error = HomographyError(H, x1, x2);

    EXPECT_GT(error, 0.0);

}



TEST_F(HomographyErrorTest_68, ZeroPoint_ZeroError_68) {

    // Test with zero points which should result in zero error for identity homography

    x1 << 0, 0;

    x2 << 0, 0;

    double error = HomographyError(H, x1, x2);

    EXPECT_DOUBLE_EQ(error, 0.0);

}



TEST_F(HomographyErrorTest_68, LargePoints_ErrorCalculation_68) {

    // Test with large points to check for numerical stability

    x1 << 1e6, 1e6;

    x2 << 1e6 + 1, 1e6 + 1;

    double error = HomographyError(H, x1, x2);

    EXPECT_NEAR(error, 2.0, 1e-9); // Allow for some numerical precision issues

}



TEST_F(HomographyErrorTest_68, NegativePoints_ErrorCalculation_68) {

    // Test with negative points

    x1 << -1, -1;

    x2 << -2, -2;

    double error = HomographyError(H, x1, x2);

    EXPECT_DOUBLE_EQ(error, 2.0);

}
