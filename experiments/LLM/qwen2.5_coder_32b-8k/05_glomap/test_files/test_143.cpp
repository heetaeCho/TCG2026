#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/math/rigid3d.cc" // Adjust path as necessary



using namespace glomap;



class Rigid3dTest_143 : public ::testing::Test {

protected:

    Rigid3d pose1;

    Rigid3d pose2;

};



TEST_F(Rigid3dTest_143, IdenticalPoses_ReturnZeroAngle_143) {

    EXPECT_DOUBLE_EQ(CalcTransAngle(pose1, pose1), 0.0);

}



TEST_F(Rigid3dTest_143, OrthogonalPoses_Return90DegreeAngle_143) {

    pose1.translation = Eigen::Vector3d(1, 0, 0);

    pose2.translation = Eigen::Vector3d(0, 1, 0);

    EXPECT_DOUBLE_EQ(CalcTransAngle(pose1, pose2), 90.0);

}



TEST_F(Rigid3dTest_143, OppositePoses_Return180DegreeAngle_143) {

    pose1.translation = Eigen::Vector3d(1, 0, 0);

    pose2.translation = Eigen::Vector3d(-1, 0, 0);

    EXPECT_DOUBLE_EQ(CalcTransAngle(pose1, pose2), 180.0);

}



TEST_F(Rigid3dTest_143, SmallAngle_ReturnApproximateAngle_143) {

    pose1.translation = Eigen::Vector3d(1, 0, 0);

    pose2.translation = Eigen::Vector3d(1.001, 0, 0);

    EXPECT_NEAR(CalcTransAngle(pose1, pose2), 0.0572958, 0.0001); // cos^-1(1 - epsilon) * 180 / pi

}



TEST_F(Rigid3dTest_143, LargeAngle_ReturnApproximateAngle_143) {

    pose1.translation = Eigen::Vector3d(1, 0, 0);

    pose2.translation = Eigen::Vector3d(-0.5, -sqrt(3)/2, 0);

    EXPECT_NEAR(CalcTransAngle(pose1, pose2), 150.0, 0.01); // cos^-1(-0.5) * 180 / pi

}



TEST_F(Rigid3dTest_143, ZeroLengthTranslation_ReturnZeroAngle_143) {

    pose1.translation = Eigen::Vector3d(0, 0, 0);

    pose2.translation = Eigen::Vector3d(1, 1, 1);

    EXPECT_DOUBLE_EQ(CalcTransAngle(pose1, pose2), 0.0); // Assuming zero length vector is treated as no translation

}



TEST_F(Rigid3dTest_143, ZeroLengthTranslationInBoth_ReturnZeroAngle_143) {

    pose1.translation = Eigen::Vector3d(0, 0, 0);

    pose2.translation = Eigen::Vector3d(0, 0, 0);

    EXPECT_DOUBLE_EQ(CalcTransAngle(pose1, pose2), 0.0); // Both zero length vectors

}
