#include <gtest/gtest.h>

#include "yaml-cpp/emittermanip.h"



class DoublePrecisionTest_21 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(DoublePrecisionTest_21, PositiveValueSetsCorrectPrecision_21) {

    YAML::_Precision precision = YAML::DoublePrecision(5);

    EXPECT_EQ(precision.value, -1);

    EXPECT_EQ(precision.precision, 5);

}



TEST_F(DoublePrecisionTest_21, ZeroValueSetsCorrectPrecision_21) {

    YAML::_Precision precision = YAML::DoublePrecision(0);

    EXPECT_EQ(precision.value, -1);

    EXPECT_EQ(precision.precision, 0);

}



TEST_F(DoublePrecisionTest_21, NegativeValueSetsCorrectPrecision_21) {

    YAML::_Precision precision = YAML::DoublePrecision(-3);

    EXPECT_EQ(precision.value, -1);

    EXPECT_EQ(precision.precision, -3);

}
