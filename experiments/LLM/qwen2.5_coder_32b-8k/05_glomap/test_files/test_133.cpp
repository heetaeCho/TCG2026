#include <gtest/gtest.h>

#include <Eigen/Dense>

#include "glomap/glomap/math/gravity.h"



namespace {



using namespace glomap;

using namespace Eigen;



TEST(AverageGravityTest_133, SingleGravityVector_ReturnsSameVector_133) {

    std::vector<Vector3d> gravities = { Vector3d(1.0, 2.0, 3.0) };

    EXPECT_EQ(AverageGravity(gravities), Vector3d(1.0, 2.0, 3.0));

}



TEST(AverageGravityTest_133, MultipleGravityVectors_ReturnsCorrectAverageDirection_133) {

    std::vector<Vector3d> gravities = { 

        Vector3d(1.0, 0.0, 0.0),

        Vector3d(0.0, 1.0, 0.0),

        Vector3d(0.0, 0.0, 1.0)

    };

    Vector3d expected = (Vector3d(1.0, 1.0, 1.0) / std::sqrt(3)).normalized();

    EXPECT_TRUE(AverageGravity(gravities).isApprox(expected));

}



TEST(AverageGravityTest_133, EmptyGravities_ReturnsZeroVector_133) {

    std::vector<Vector3d> gravities;

    EXPECT_EQ(AverageGravity(gravities), Vector3d::Zero());

}



TEST(AverageGravityTest_133, OppositeVectors_ReturnsAverageDirection_133) {

    std::vector<Vector3d> gravities = { 

        Vector3d(1.0, 0.0, 0.0),

        Vector3d(-1.0, 0.0, 0.0)

    };

    EXPECT_EQ(AverageGravity(gravities), Vector3d::Zero());

}



TEST(AverageGravityTest_133, MoreNegativeVectors_ReturnsNegatedAverage_133) {

    std::vector<Vector3d> gravities = { 

        Vector3d(1.0, 0.0, 0.0),

        Vector3d(-2.0, 0.0, 0.0)

    };

    EXPECT_EQ(AverageGravity(gravities), Vector3d(-1.0, 0.0, 0.0));

}



TEST(AverageGravityTest_133, MixedDirectionVectors_ReturnsCorrectAverage_133) {

    std::vector<Vector3d> gravities = { 

        Vector3d(2.0, 0.0, 0.0),

        Vector3d(-1.0, -1.0, 0.0)

    };

    EXPECT_TRUE(AverageGravity(gravities).isApprox(Vector3d(1.0, 1.0, 0.0) / std::sqrt(2)));

}



} // namespace
