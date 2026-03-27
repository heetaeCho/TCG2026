#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Eigen/Dense"

#include "glomap/math/rigid3d.h"



namespace glomap {

class Rigid3d {

public:

    Eigen::Quaterniond rotation;

    Eigen::Vector3d translation;

};

}  // namespace glomap



using namespace glomap;



class CenterFromPoseTest_75 : public ::testing::Test {};



TEST_F(CenterFromPoseTest_75, IdentityRotationZeroTranslation_ReturnsOrigin_75) {

    Rigid3d pose;

    pose.rotation = Eigen::Quaterniond::Identity();

    pose.translation = Eigen::Vector3d(0.0, 0.0, 0.0);

    

    EXPECT_EQ(CenterFromPose(pose), Eigen::Vector3d(0.0, 0.0, 0.0));

}



TEST_F(CenterFromPoseTest_75, IdentityRotationNonZeroTranslation_ReturnsNegatedTranslation_75) {

    Rigid3d pose;

    pose.rotation = Eigen::Quaterniond::Identity();

    pose.translation = Eigen::Vector3d(1.0, 2.0, 3.0);

    

    EXPECT_EQ(CenterFromPose(pose), Eigen::Vector3d(-1.0, -2.0, -3.0));

}



TEST_F(CenterFromPoseTest_75, NonIdentityRotationZeroTranslation_ReturnsOrigin_75) {

    Rigid3d pose;

    pose.rotation = Eigen::Quaterniond(Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d(1.0, 0.0, 0.0)));

    pose.translation = Eigen::Vector3d(0.0, 0.0, 0.0);

    

    EXPECT_EQ(CenterFromPose(pose), Eigen::Vector3d(0.0, 0.0, 0.0));

}



TEST_F(CenterFromPoseTest_75, NonIdentityRotationNonZeroTranslation_ReturnsTransformedPoint_75) {

    Rigid3d pose;

    pose.rotation = Eigen::Quaterniond(Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d(1.0, 0.0, 0.0)));

    pose.translation = Eigen::Vector3d(1.0, 2.0, 3.0);

    

    Eigen::Vector3d expected_center = -pose.rotation.inverse() * pose.translation;

    EXPECT_EQ(CenterFromPose(pose), expected_center);

}



TEST_F(CenterFromPoseTest_75, BoundaryConditionLargeTranslation_ReturnsCorrectCenter_75) {

    Rigid3d pose;

    pose.rotation = Eigen::Quaterniond::Identity();

    pose.translation = Eigen::Vector3d(1e9, 1e9, 1e9);

    

    EXPECT_EQ(CenterFromPose(pose), Eigen::Vector3d(-1e9, -1e9, -1e9));

}



TEST_F(CenterFromPoseTest_75, BoundaryConditionSmallTranslation_ReturnsCorrectCenter_75) {

    Rigid3d pose;

    pose.rotation = Eigen::Quaterniond::Identity();

    pose.translation = Eigen::Vector3d(1e-9, 1e-9, 1e-9);

    

    EXPECT_EQ(CenterFromPose(pose), Eigen::Vector3d(-1e-9, -1e-9, -1e-9));

}
