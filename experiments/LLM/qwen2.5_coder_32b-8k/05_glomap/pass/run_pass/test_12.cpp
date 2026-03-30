#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "TestProjects/glomap/glomap/estimators/cost_function.h"



using namespace glomap;

using ::testing::ElementsAre;



class BATAPairwiseDirectionErrorTest_12 : public ::testing::Test {

protected:

    Eigen::Vector3d translation_obs_{1.0, 2.0, 3.0};

    std::unique_ptr<BATAPairwiseDirectionError> error_;



    void SetUp() override {

        error_ = std::make_unique<BATAPairwiseDirectionError>(translation_obs_);

    }

};



TEST_F(BATAPairwiseDirectionErrorTest_12, NormalOperation_12) {

    double position1[3] = {0.0, 0.0, 0.0};

    double position2[3] = {4.0, 5.0, 6.0};

    double scale[1] = {1.0};

    double residuals[3];



    bool result = (*error_)(position1, position2, scale, residuals);



    EXPECT_TRUE(result);

    EXPECT_THAT(residuals, ElementsAre(-3.0, -3.0, -3.0));

}



TEST_F(BATAPairwiseDirectionErrorTest_12, BoundaryConditions_ZeroScale_12) {

    double position1[3] = {0.0, 0.0, 0.0};

    double position2[3] = {4.0, 5.0, 6.0};

    double scale[1] = {0.0};

    double residuals[3];



    bool result = (*error_)(position1, position2, scale, residuals);



    EXPECT_TRUE(result);

    EXPECT_THAT(residuals, ElementsAre(1.0, 2.0, 3.0));

}



TEST_F(BATAPairwiseDirectionErrorTest_12, BoundaryConditions_SamePositions_12) {

    double position1[3] = {4.0, 5.0, 6.0};

    double position2[3] = {4.0, 5.0, 6.0};

    double scale[1] = {1.0};

    double residuals[3];



    bool result = (*error_)(position1, position2, scale, residuals);



    EXPECT_TRUE(result);

    EXPECT_THAT(residuals, ElementsAre(1.0, 2.0, 3.0));

}



TEST_F(BATAPairwiseDirectionErrorTest_12, ExceptionalCase_NegativeScale_12) {

    double position1[3] = {0.0, 0.0, 0.0};

    double position2[3] = {4.0, 5.0, 6.0};

    double scale[1] = {-1.0};

    double residuals[3];



    bool result = (*error_)(position1, position2, scale, residuals);



    EXPECT_TRUE(result);

    EXPECT_THAT(residuals, ElementsAre(7.0, 7.0, 7.0));

}



TEST_F(BATAPairwiseDirectionErrorTest_12, CreateFunction_ReturnsNonNull_12) {

    ceres::CostFunction* cost_function = BATAPairwiseDirectionError::Create(translation_obs_);



    EXPECT_NE(cost_function, nullptr);

    delete cost_function;

}
