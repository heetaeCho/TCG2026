#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/glomap/glomap/math/rigid3d.cc"



using namespace glomap;

using namespace testing;



// Test fixture for Rigid3d tests

class Rigid3dTest_142 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed in the future

};



TEST_F(Rigid3dTest_142, CalcTrans_SamePose_ReturnsZero_142) {

    Rigid3d pose(Translation3d(), Quaternion());

    EXPECT_DOUBLE_EQ(CalcTrans(pose, pose), 0.0);

}



TEST_F(Rigid3dTest_142, CalcTrans_DifferentPoses_ReturnsNonZero_142) {

    Rigid3d pose1(Translation3d(1, 2, 3), Quaternion());

    Rigid3d pose2(Translation3d(4, 5, 6), Quaternion());

    EXPECT_DOUBLE_EQ(CalcTrans(pose1, pose2), 5.196152422706632);

}



TEST_F(Rigid3dTest_142, CalcTrans_PoseWithZeroTranslation_ReturnsNormOfOtherPose_142) {

    Rigid3d pose1(Translation3d(), Quaternion());

    Rigid3d pose2(Translation3d(3, 4, 0), Quaternion());

    EXPECT_DOUBLE_EQ(CalcTrans(pose1, pose2), 5.0);

}



TEST_F(Rigid3dTest_142, CalcTrans_PosesWithSameTranslationButDifferentRotations_ReturnsZero_142) {

    Rigid3d pose1(Translation3d(1, 2, 3), Quaternion(Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d::UnitX())));

    Rigid3d pose2(Translation3d(1, 2, 3), Quaternion(Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d::UnitZ())));

    EXPECT_DOUBLE_EQ(CalcTrans(pose1, pose2), 0.0);

}



TEST_F(Rigid3dTest_142, CalcTrans_LargeTranslation_ReturnsCorrectDistance_142) {

    Rigid3d pose1(Translation3d(-100, -200, -300), Quaternion());

    Rigid3d pose2(Translation3d(100, 200, 300), Quaternion());

    EXPECT_DOUBLE_EQ(CalcTrans(pose1, pose2), 670.8203932499369);

}
