#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/estimators/cost_function.h"

#include <ceres/ceres.h>

#include <Eigen/Dense>



using namespace glomap;

using ::testing::ElementsAre;



class GravErrorTest_19 : public ::testing::Test {

protected:

    Eigen::Vector3d grav_obs_;

    GravError error_;



    void SetUp() override {

        grav_obs_ << 1.0, 2.0, 3.0;

        error_ = GravError(grav_obs_);

    }

};



TEST_F(GravErrorTest_19, NormalOperation_19) {

    double gvec[3] = {1.5, 2.5, 3.5};

    double residuals[3];

    bool result = error_(gvec, residuals);



    EXPECT_TRUE(result);

    EXPECT_THAT(residuals, ElementsAre(0.5, 0.5, 0.5));

}



TEST_F(GravErrorTest_19, BoundaryConditions_ZeroInput_19) {

    double gvec[3] = {0.0, 0.0, 0.0};

    double residuals[3];

    bool result = error_(gvec, residuals);



    EXPECT_TRUE(result);

    EXPECT_THAT(residuals, ElementsAre(-1.0, -2.0, -3.0));

}



TEST_F(GravErrorTest_19, BoundaryConditions_EqualInput_19) {

    double gvec[3] = {1.0, 2.0, 3.0};

    double residuals[3];

    bool result = error_(gvec, residuals);



    EXPECT_TRUE(result);

    EXPECT_THAT(residuals, ElementsAre(0.0, 0.0, 0.0));

}



TEST_F(GravErrorTest_19, BoundaryConditions_NegativeInput_19) {

    double gvec[3] = {-1.0, -2.0, -3.0};

    double residuals[3];

    bool result = error_(gvec, residuals);



    EXPECT_TRUE(result);

    EXPECT_THAT(residuals, ElementsAre(-2.0, -4.0, -6.0));

}



TEST_F(GravErrorTest_19, BoundaryConditions_LargeInput_19) {

    double gvec[3] = {100.0, 200.0, 300.0};

    double residuals[3];

    bool result = error_(gvec, residuals);



    EXPECT_TRUE(result);

    EXPECT_THAT(residuals, ElementsAre(99.0, 198.0, 297.0));

}



TEST_F(GravErrorTest_19, CreateCostFunction_19) {

    ceres::CostFunction* cost_function = GravError::CreateCost(grav_obs_);

    EXPECT_NE(cost_function, nullptr);

    delete cost_function;

}
