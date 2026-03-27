#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Eigen/Geometry"

#include "rigid3d.cc"  // Adjust the include path as necessary



using namespace glomap;

using namespace Eigen;



class Rigid3dTest_148 : public ::testing::Test {

protected:

    Rigid3d pose;

};



TEST_F(Rigid3dTest_148, CenterFromPose_ZeroTranslationAndRotation_148) {

    pose.translation = Vector3d(0.0, 0.0, 0.0);

    pose.rotation = Quaterniond::Identity();

    

    Vector3d center = CenterFromPose(pose);

    EXPECT_EQ(center, Vector3d(0.0, 0.0, 0.0));

}



TEST_F(Rigid3dTest_148, CenterFromPose_NonZeroTranslation_ZeroRotation_148) {

    pose.translation = Vector3d(1.0, 2.0, 3.0);

    pose.rotation = Quaterniond::Identity();

    

    Vector3d center = CenterFromPose(pose);

    EXPECT_EQ(center, -pose.translation);

}



TEST_F(Rigid3dTest_148, CenterFromPose_ZeroTranslation_NonZeroRotation_148) {

    pose.translation = Vector3d(0.0, 0.0, 0.0);

    Quaterniond rotation;

    rotation.setAngleAxis(M_PI / 2, Vector3d::UnitZ());

    pose.rotation = rotation;

    

    Vector3d center = CenterFromPose(pose);

    EXPECT_EQ(center, Vector3d(0.0, 0.0, 0.0));

}



TEST_F(Rigid3dTest_148, CenterFromPose_NonZeroTranslation_NonZeroRotation_148) {

    pose.translation = Vector3d(1.0, 2.0, 3.0);

    Quaterniond rotation;

    rotation.setAngleAxis(M_PI / 2, Vector3d::UnitZ());

    pose.rotation = rotation;

    

    Vector3d center = CenterFromPose(pose);

    EXPECT_EQ(center, -rotation.inverse() * pose.translation);

}
