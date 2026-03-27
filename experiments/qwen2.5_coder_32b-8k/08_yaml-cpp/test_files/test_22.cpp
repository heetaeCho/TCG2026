#include <gtest/gtest.h>

#include "yaml-cpp/emittermanip.h"



class PrecisionTest_22 : public ::testing::Test {

protected:

    YAML::_Precision precision;

};



TEST_F(PrecisionTest_22, ConstructorSetsCorrectValues_22) {

    int value = 5;

    YAML::_Precision prec = YAML::Precision(value);

    EXPECT_EQ(prec.value1(), value);

    EXPECT_EQ(prec.value2(), value);

}



TEST_F(PrecisionTest_22, ConstructorHandlesZeroValue_22) {

    int value = 0;

    YAML::_Precision prec = YAML::Precision(value);

    EXPECT_EQ(prec.value1(), value);

    EXPECT_EQ(prec.value2(), value);

}



TEST_F(PrecisionTest_22, ConstructorHandlesNegativeValue_22) {

    int value = -3;

    YAML::_Precision prec = YAML::Precision(value);

    EXPECT_EQ(prec.value1(), value);

    EXPECT_EQ(prec.value2(), value);

}
