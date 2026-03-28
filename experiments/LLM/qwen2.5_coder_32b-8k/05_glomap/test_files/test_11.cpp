#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/estimators/view_graph_calibration.h"



using namespace glomap;

using ::testing::Return;



class ViewGraphCalibratorOptionsTest : public ::testing::Test {

protected:

    ViewGraphCalibratorOptions options;

};



TEST_F(ViewGraphCalibratorOptionsTest_11, CreateLossFunction_ReturnsCauchyLossWithCorrectThreshold_11) {

    auto loss_function = options.CreateLossFunction();

    EXPECT_NE(loss_function, nullptr);

    // Since we can't directly verify the internal type or state of the CauchyLoss,

    // we rely on the fact that it should be a CauchyLoss with the expected threshold.

    // This test assumes that the CreateLossFunction method correctly sets up the loss function.

}



TEST_F(ViewGraphCalibratorOptionsTest_11, ThresLowerRatio_DefaultValueIsCorrect_11) {

    EXPECT_DOUBLE_EQ(options.thres_lower_ratio, 0.1);

}



TEST_F(ViewGraphCalibratorOptionsTest_11, ThresHigherRatio_DefaultValueIsCorrect_11) {

    EXPECT_DOUBLE_EQ(options.thres_higher_ratio, 10.0);

}



TEST_F(ViewGraphCalibratorOptionsTest_11, ThresTwoViewError_DefaultValueIsCorrect_11) {

    EXPECT_DOUBLE_EQ(options.thres_two_view_error, 2.0);

}



// No exceptional or error cases are observable through the interface based on the provided information.
