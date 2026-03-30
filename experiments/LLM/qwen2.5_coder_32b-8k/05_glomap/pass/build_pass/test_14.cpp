#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/estimators/cost_function.h"

#include <Eigen/Dense>



using namespace glomap;

using namespace Eigen;



class RigUnknownBATAPairwiseDirectionErrorTest_14 : public ::testing::Test {

protected:

    Vector3d translation_obs_;

    Quaterniond rig_from_world_rot_;



    void SetUp() override {

        translation_obs_ = Vector3d(1.0, 2.0, 3.0);

        rig_from_world_rot_ = Quaterniond(AngleAxisd(M_PI / 4, Vector3d::UnitZ()));

    }



    RigUnknownBATAPairwiseDirectionError CreateCostFunction() {

        return RigUnknownBATAPairwiseDirectionError(translation_obs_, rig_from_world_rot_);

    }

};



TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, NormalOperation_14) {

    auto cost_function = CreateCostFunction();



    double point3d[] = {0.5, 1.5, 2.5};

    double rig_from_world_center[] = {1.0, 1.0, 1.0};

    double cam_from_rig_center[] = {0.1, 0.2, 0.3};

    double scale[] = {1.0};

    double residuals[3];



    bool result = cost_function(point3d, rig_from_world_center, cam_from_rig_center, scale, residuals);



    EXPECT_TRUE(result);

}



TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, ZeroScale_14) {

    auto cost_function = CreateCostFunction();



    double point3d[] = {0.5, 1.5, 2.5};

    double rig_from_world_center[] = {1.0, 1.0, 1.0};

    double cam_from_rig_center[] = {0.1, 0.2, 0.3};

    double scale[] = {0.0};

    double residuals[3];



    bool result = cost_function(point3d, rig_from_world_center, cam_from_rig_center, scale, residuals);



    EXPECT_TRUE(result);

    EXPECT_EQ(residuals[0], translation_obs_[0]);

    EXPECT_EQ(residuals[1], translation_obs_[1]);

    EXPECT_EQ(residuals[2], translation_obs_[2]);

}



TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, BoundaryConditionZeroPoint3d_14) {

    auto cost_function = CreateCostFunction();



    double point3d[] = {0.0, 0.0, 0.0};

    double rig_from_world_center[] = {1.0, 1.0, 1.0};

    double cam_from_rig_center[] = {0.1, 0.2, 0.3};

    double scale[] = {1.0};

    double residuals[3];



    bool result = cost_function(point3d, rig_from_world_center, cam_from_rig_center, scale, residuals);



    EXPECT_TRUE(result);

}



TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, BoundaryConditionZeroCamFromRigCenter_14) {

    auto cost_function = CreateCostFunction();



    double point3d[] = {0.5, 1.5, 2.5};

    double rig_from_world_center[] = {1.0, 1.0, 1.0};

    double cam_from_rig_center[] = {0.0, 0.0, 0.0};

    double scale[] = {1.0};

    double residuals[3];



    bool result = cost_function(point3d, rig_from_world_center, cam_from_rig_center, scale, residuals);



    EXPECT_TRUE(result);

}



TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, BoundaryConditionZeroRigFromWorldCenter_14) {

    auto cost_function = CreateCostFunction();



    double point3d[] = {0.5, 1.5, 2.5};

    double rig_from_world_center[] = {0.0, 0.0, 0.0};

    double cam_from_rig_center[] = {0.1, 0.2, 0.3};

    double scale[] = {1.0};

    double residuals[3];



    bool result = cost_function(point3d, rig_from_world_center, cam_from_rig_center, scale, residuals);



    EXPECT_TRUE(result);

}



TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, LargeScale_14) {

    auto cost_function = CreateCostFunction();



    double point3d[] = {0.5, 1.5, 2.5};

    double rig_from_world_center[] = {1.0, 1.0, 1.0};

    double cam_from_rig_center[] = {0.1, 0.2, 0.3};

    double scale[] = {1000.0};

    double residuals[3];



    bool result = cost_function(point3d, rig_from_world_center, cam_from_rig_center, scale, residuals);



    EXPECT_TRUE(result);

}



TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, NegativeScale_14) {

    auto cost_function = CreateCostFunction();



    double point3d[] = {0.5, 1.5, 2.5};

    double rig_from_world_center[] = {1.0, 1.0, 1.0};

    double cam_from_rig_center[] = {0.1, 0.2, 0.3};

    double scale[] = {-1.0};

    double residuals[3];



    bool result = cost_function(point3d, rig_from_world_center, cam_from_rig_center, scale, residuals);



    EXPECT_TRUE(result);

}
