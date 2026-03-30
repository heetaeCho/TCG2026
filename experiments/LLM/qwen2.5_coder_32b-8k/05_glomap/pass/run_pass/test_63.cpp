#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/math/gravity.h"

#include <Eigen/Dense>

#include <vector>



using namespace glomap;

using namespace Eigen;



TEST(AverageGravityTest_63, SingleGravityVector_63) {

    std::vector<Vector3d> gravities = {Vector3d(1.0, 2.0, 3.0)};

    Vector3d expected_result = Vector3d(1.0, 2.0, 3.0).normalized();

    EXPECT_TRUE(AverageGravity(gravities).isApprox(expected_result));

}



TEST(AverageGravityTest_63, MultipleGravityVectors_63) {

    std::vector<Vector3d> gravities = {Vector3d(1.0, 2.0, 3.0), Vector3d(-1.0, -2.0, -3.0)};

    Vector3d expected_result = Vector3d(1.0, 2.0, 3.0).normalized();

    EXPECT_TRUE(AverageGravity(gravities).isApprox(expected_result) || AverageGravity(gravities).isApprox(-expected_result));

}



TEST(AverageGravityTest_63, ZeroVectors_63) {

    std::vector<Vector3d> gravities = {Vector3d::Zero(), Vector3d::Zero()};

    EXPECT_TRUE(AverageGravity(gravities).isApprox(Vector3d::Zero()));

}



TEST(AverageGravityTest_63, EmptyInput_63) {

    std::vector<Vector3d> gravities;

    EXPECT_TRUE(AverageGravity(gravities).isApprox(Vector3d::Zero()));

}



TEST(AverageGravityTest_63, OppositeVectors_63) {

    std::vector<Vector3d> gravities = {Vector3d(1.0, 2.0, 3.0), Vector3d(-1.0, -2.0, -3.0)};

    EXPECT_TRUE(AverageGravity(gravities).isApprox(Vector3d(1.0, 2.0, 3.0).normalized()) || AverageGravity(gravities).isApprox(-Vector3d(1.0, 2.0, 3.0).normalized()));

}



TEST(AverageGravityTest_63, LargeNumberOfVectors_63) {

    std::vector<Vector3d> gravities;

    for (int i = 0; i < 100; ++i) {

        gravities.push_back(Vector3d(1.0, 2.0, 3.0));

    }

    Vector3d expected_result = Vector3d(1.0, 2.0, 3.0).normalized();

    EXPECT_TRUE(AverageGravity(gravities).isApprox(expected_result));

}



TEST(AverageGravityTest_63, MixedPositiveNegativeVectors_63) {

    std::vector<Vector3d> gravities = {Vector3d(1.0, 2.0, 3.0), Vector3d(-1.0, -2.0, -3.0), Vector3d(1.0, 2.0, 3.0)};

    Vector3d expected_result = Vector3d(1.0, 2.0, 3.0).normalized();

    EXPECT_TRUE(AverageGravity(gravities).isApprox(expected_result));

}
