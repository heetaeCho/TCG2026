#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/estimators/view_graph_calibration.h"

#include <memory>



using namespace glomap;

using ::testing::Return;



// Test fixture for ViewGraphCalibratorOptions tests

class ViewGraphCalibratorOptionsTest_162 : public ::testing::Test {

protected:

    ViewGraphCalibratorOptions options;

};



// Test default constructor and initial values 162

TEST_F(ViewGraphCalibratorOptionsTest_162, DefaultConstructorInitialValues_162) {

    EXPECT_DOUBLE_EQ(options.thres_loss_function, 1e-2);

    EXPECT_DOUBLE_EQ(options.thres_lower_ratio, 0.10000000000000001);

    EXPECT_DOUBLE_EQ(options.thres_higher_ratio, 10);

    EXPECT_DOUBLE_EQ(options.thres_two_view_error, 2.);

}



// Test CreateLossFunction return type and behavior 162

TEST_F(ViewGraphCalibratorOptionsTest_162, CreateLossFunction_ReturnTypeAndBehavior_162) {

    auto loss_function = options.CreateLossFunction();

    EXPECT_NE(loss_function.get(), nullptr);

}
