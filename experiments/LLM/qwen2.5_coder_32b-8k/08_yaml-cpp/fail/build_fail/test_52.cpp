#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"

#include <sstream>



using namespace YAML;



class EmitterTest_52 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_52, WriteIntegralType_NormalOperation_52) {

    long value = 42;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_52, WriteIntegralType_BoundaryConditionZero_52) {

    long value = 0;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_52, WriteIntegralType_NegativeValue_52) {

    long value = -12345;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_52, WriteIntegralType_MaxLong_52) {

    long value = LONG_MAX;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_52, WriteIntegralType_MinLong_52) {

    long value = LONG_MIN;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_52, WriteIntegralType_VerifyOutput_52) {

    long value = 42;

    emitter << value;

    std::string expected_output = "42";

    EXPECT_EQ(expected_output, emitter.c_str());

}
