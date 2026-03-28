#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"

#include <sstream>



using namespace YAML;



class EmitterTest_57 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_57, WriteDoubleNormalOperation_57) {

    double value = 3.14159;

    emitter << value;

    EXPECT_EQ(emitter.good(), true);

}



TEST_F(EmitterTest_57, WriteDoubleBoundaryCondition_57) {

    double zero = 0.0;

    double max = std::numeric_limits<double>::max();

    double min = std::numeric_limits<double>::lowest();



    emitter << zero;

    EXPECT_EQ(emitter.good(), true);



    emitter << max;

    EXPECT_EQ(emitter.good(), true);



    emitter << min;

    EXPECT_EQ(emitter.good(), true);

}



TEST_F(EmitterTest_57, WriteDoubleExceptionalCase_57) {

    double nan = std::numeric_limits<double>::quiet_NaN();

    double inf = std::numeric_limits<double>::infinity();



    emitter << nan;

    EXPECT_EQ(emitter.good(), false);



    emitter << inf;

    EXPECT_EQ(emitter.good(), false);

}



TEST_F(EmitterTest_57, WriteDoublePrecisionSetting_57) {

    double value = 3.141592653589793;

    emitter.SetDoublePrecision(5);

    emitter << value;

    EXPECT_EQ(std::string(emitter.c_str()).find("3.14159"), std::string::npos);



    emitter.SetDoublePrecision(10);

    emitter << value;

    EXPECT_EQ(std::string(emitter.c_str()).find("3.1415926536"), std::string::npos);

}
