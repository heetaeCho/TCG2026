#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/math/two_view_geometry.cc"

#include <Eigen/Dense>



using namespace glomap;

using namespace Eigen;



TEST(CheckCheiralityTest_135, NormalOperationWithinRange_135) {

    Rigid3d pose(AngleAxisd(0.785, Vector3d::UnitZ()), Vector3d(1, 2, 3));

    Vector3d x1(4, 5, 6);

    Vector3d x2(7, 8, 9);

    double min_depth = 0.1;

    double max_depth = 1.0;



    EXPECT_TRUE(CheckCheirality(pose, x1, x2, min_depth, max_depth));

}



TEST(CheckCheiralityTest_135, NormalOperationOutsideRange_135) {

    Rigid3d pose(AngleAxisd(0.785, Vector3d::UnitZ()), Vector3d(1, 2, 3));

    Vector3d x1(4, 5, 6);

    Vector3d x2(7, 8, 9);

    double min_depth = 2.0;

    double max_depth = 3.0;



    EXPECT_FALSE(CheckCheirality(pose, x1, x2, min_depth, max_depth));

}



TEST(CheckCheiralityTest_135, BoundaryConditionMinDepthZero_135) {

    Rigid3d pose(AngleAxisd(0.785, Vector3d::UnitZ()), Vector3d(1, 2, 3));

    Vector3d x1(4, 5, 6);

    Vector3d x2(7, 8, 9);

    double min_depth = 0.0;

    double max_depth = 1.0;



    EXPECT_TRUE(CheckCheirality(pose, x1, x2, min_depth, max_depth));

}



TEST(CheckCheiralityTest_135, BoundaryConditionMaxDepthZero_135) {

    Rigid3d pose(AngleAxisd(0.785, Vector3d::UnitZ()), Vector3d(1, 2, 3));

    Vector3d x1(4, 5, 6);

    Vector3d x2(7, 8, 9);

    double min_depth = 0.0;

    double max_depth = 0.0;



    EXPECT_FALSE(CheckCheirality(pose, x1, x2, min_depth, max_depth));

}



TEST(CheckCheiralityTest_135, BoundaryConditionMinDepthGreaterThanMaxDepth_135) {

    Rigid3d pose(AngleAxisd(0.785, Vector3d::UnitZ()), Vector3d(1, 2, 3));

    Vector3d x1(4, 5, 6);

    Vector3d x2(7, 8, 9);

    double min_depth = 1.0;

    double max_depth = 0.1;



    EXPECT_FALSE(CheckCheirality(pose, x1, x2, min_depth, max_depth));

}
