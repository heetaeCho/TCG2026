#include <gtest/gtest.h>

#include "yaml-cpp/emittermanip.h"



class EmitterManipTest_12 : public ::testing::Test {};



TEST_F(EmitterManipTest_12, IndentPositiveValue_12) {

    YAML::_Indent indent = YAML::Indent(5);

    EXPECT_EQ(indent.value, 5);

}



TEST_F(EmitterManipTest_12, IndentZeroValue_12) {

    YAML::_Indent indent = YAML::Indent(0);

    EXPECT_EQ(indent.value, 0);

}



TEST_F(EmitterManipTest_12, IndentNegativeValue_12) {

    YAML::_Indent indent = YAML::Indent(-3);

    EXPECT_EQ(indent.value, -3);

}
