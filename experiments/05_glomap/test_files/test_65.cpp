#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "two_view_geometry.h"

#include <Eigen/Dense>



namespace glomap {



class CheckCheiralityTest_65 : public ::testing::Test {

protected:

    Rigid3d pose;

    Eigen::Vector3d x1;

    Eigen::Vector3d x2;

    double min_depth;

    double max_depth;



    void SetUp() override {

        // Default setup for tests

        pose = Rigid3d(Eigen::Quaterniond::Identity(), Eigen::Vector3d(0, 0, 0));

        x1 = Eigen::Vector3d(1, 0, 0);

        x2 = Eigen::Vector3d(0, 1, 0);

        min_depth = 0.1;

        max_depth = 1.0;

    }

};



TEST_F(CheckCheiralityTest_65, NormalOperationPositive_65) {

    EXPECT_TRUE(CheckCheirality(pose, x1, x2, min_depth, max_depth));

}



TEST_F(CheckCheiralityTest_65, NormalOperationNegative_65) {

    x2 = Eigen::Vector3d(1, 0, 0); // Collinear points

    EXPECT_FALSE(CheckCheirality(pose, x1, x2, min_depth, max_depth));

}



TEST_F(CheckCheiralityTest_65, BoundaryConditionMinDepth_65) {

    min_depth = 0.0;

    max_depth = 1.0;

    EXPECT_TRUE(CheckCheirality(pose, x1, x2, min_depth, max_depth));

}



TEST_F(CheckCheiralityTest_65, BoundaryConditionMaxDepth_65) {

    min_depth = 0.1;

    max_depth = std::numeric_limits<double>::max();

    EXPECT_TRUE(CheckCheirality(pose, x1, x2, min_depth, max_depth));

}



TEST_F(CheckCheiralityTest_65, BoundaryConditionDepthRange_65) {

    min_depth = 0.5;

    max_depth = 0.4; // Inverted range

    EXPECT_FALSE(CheckCheirality(pose, x1, x2, min_depth, max_depth));

}



TEST_F(CheckCheiralityTest_65, ZeroMinDepth_65) {

    min_depth = 0.0;

    EXPECT_TRUE(CheckCheirality(pose, x1, x2, min_depth, max_depth));

}



TEST_F(CheckCheiralityTest_65, ZeroMaxDepth_65) {

    max_depth = 0.0;

    EXPECT_FALSE(CheckCheirality(pose, x1, x2, min_depth, max_depth));

}



TEST_F(CheckCheiralityTest_65, NegativeMinDepth_65) {

    min_depth = -0.1; // Negative depth

    EXPECT_TRUE(CheckCheirality(pose, x1, x2, min_depth, max_depth));

}



TEST_F(CheckCheiralityTest_65, NegativeMaxDepth_65) {

    max_depth = -0.1; // Negative depth

    EXPECT_FALSE(CheckCheirality(pose, x1, x2, min_depth, max_depth));

}



TEST_F(CheckCheiralityTest_65, LargeValues_65) {

    x1 *= 1e6;

    x2 *= 1e6;

    min_depth *= 1e6;

    max_depth *= 1e6;

    EXPECT_TRUE(CheckCheirality(pose, x1, x2, min_depth, max_depth));

}



TEST_F(CheckCheiralityTest_65, SmallValues_65) {

    x1 /= 1e6;

    x2 /= 1e6;

    min_depth /= 1e6;

    max_depth /= 1e6;

    EXPECT_TRUE(CheckCheirality(pose, x1, x2, min_depth, max_depth));

}



} // namespace glomap
