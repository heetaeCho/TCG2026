#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"

#include <sstream>



using namespace YAML;



class EmitterTest_50 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_50, WriteShortValueNormalOperation_50) {

    short value = 42;

    emitter << value;

    EXPECT_EQ(emitter.c_str(), "42");

}



TEST_F(EmitterTest_50, WriteShortValueBoundaryConditionMin_50) {

    short value = SHRT_MIN;

    emitter << value;

    std::ostringstream oss;

    oss << value;

    EXPECT_EQ(emitter.c_str(), oss.str());

}



TEST_F(EmitterTest_50, WriteShortValueBoundaryConditionMax_50) {

    short value = SHRT_MAX;

    emitter << value;

    std::ostringstream oss;

    oss << value;

    EXPECT_EQ(emitter.c_str(), oss.str());

}



TEST_F(EmitterTest_50, WriteShortValueMultipleWrites_50) {

    short value1 = 42;

    short value2 = -7;

    emitter << value1 << value2;

    EXPECT_EQ(emitter.c_str(), "42-7");

}
