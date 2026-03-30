#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "rigid3d.h"

#include <Eigen/Dense>



namespace glomap {

    class Rigid3dTest_70 : public ::testing::Test {

    protected:

        Rigid3d pose1;

        Rigid3d pose2;



        void SetUp() override {

            // Initialize poses with known translations

            pose1.translation << 1.0, 0.0, 0.0;

            pose2.translation << 0.0, 1.0, 0.0;

        }

    };



    TEST_F(Rigid3dTest_70, CalcTransAngle_NinetyDegrees_70) {

        // Arrange

        pose1.translation << 1.0, 0.0, 0.0;

        pose2.translation << 0.0, 1.0, 0.0;



        // Act

        double angle = CalcTransAngle(pose1, pose2);



        // Assert

        EXPECT_DOUBLE_EQ(angle, 90.0);

    }



    TEST_F(Rigid3dTest_70, CalcTransAngle_ZeroDegrees_70) {

        // Arrange

        pose1.translation << 1.0, 0.0, 0.0;

        pose2.translation << 1.0, 0.0, 0.0;



        // Act

        double angle = CalcTransAngle(pose1, pose2);



        // Assert

        EXPECT_DOUBLE_EQ(angle, 0.0);

    }



    TEST_F(Rigid3dTest_70, CalcTransAngle_OneEightyDegrees_70) {

        // Arrange

        pose1.translation << 1.0, 0.0, 0.0;

        pose2.translation << -1.0, 0.0, 0.0;



        // Act

        double angle = CalcTransAngle(pose1, pose2);



        // Assert

        EXPECT_DOUBLE_EQ(angle, 180.0);

    }



    TEST_F(Rigid3dTest_70, CalcTransAngle_SmallAngle_70) {

        // Arrange

        pose1.translation << 1.0, 0.0, 0.0;

        pose2.translation << 0.996194698, 0.087155743, 0.0;



        // Act

        double angle = CalcTransAngle(pose1, pose2);



        // Assert

        EXPECT_NEAR(angle, 5.0, 0.01);

    }



    TEST_F(Rigid3dTest_70, CalcTransAngle_IdenticalPoints_70) {

        // Arrange

        pose1.translation << 1.0, 0.0, 0.0;

        pose2.translation << 1.0, 0.0, 0.0;



        // Act

        double angle = CalcTransAngle(pose1, pose2);



        // Assert

        EXPECT_DOUBLE_EQ(angle, 0.0);

    }



    TEST_F(Rigid3dTest_70, CalcTransAngle_AntipodalPoints_70) {

        // Arrange

        pose1.translation << 1.0, 0.0, 0.0;

        pose2.translation << -1.0, 0.0, 0.0;



        // Act

        double angle = CalcTransAngle(pose1, pose2);



        // Assert

        EXPECT_DOUBLE_EQ(angle, 180.0);

    }



    TEST_F(Rigid3dTest_70, CalcTransAngle_UnitVectorsOrthogonal_70) {

        // Arrange

        pose1.translation << 1.0, 0.0, 0.0;

        pose2.translation << 0.0, 1.0, 0.0;



        // Act

        double angle = CalcTransAngle(pose1, pose2);



        // Assert

        EXPECT_DOUBLE_EQ(angle, 90.0);

    }



    TEST_F(Rigid3dTest_70, CalcTransAngle_UnitVectorsSameDirection_70) {

        // Arrange

        pose1.translation << 1.0, 0.0, 0.0;

        pose2.translation << 1.0, 0.0, 0.0;



        // Act

        double angle = CalcTransAngle(pose1, pose2);



        // Assert

        EXPECT_DOUBLE_EQ(angle, 0.0);

    }



    TEST_F(Rigid3dTest_70, CalcTransAngle_UnitVectorsOppositeDirection_70) {

        // Arrange

        pose1.translation << 1.0, 0.0, 0.0;

        pose2.translation << -1.0, 0.0, 0.0;



        // Act

        double angle = CalcTransAngle(pose1, pose2);



        // Assert

        EXPECT_DOUBLE_EQ(angle, 180.0);

    }

}
