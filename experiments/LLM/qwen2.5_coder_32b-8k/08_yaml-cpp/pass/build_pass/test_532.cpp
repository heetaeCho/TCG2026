#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitter.h"

#include "yaml-cpp/emittermanip.h"



using namespace YAML;



class EmitterTest_532 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_532, SetLocalPrecision_ValidFloatAndDoublePrecision_532) {

    _Precision precision(6, 10);

    EXPECT_EQ(&emitter, &emitter.SetLocalPrecision(precision));

}



TEST_F(EmitterTest_532, SetLocalPrecision_NegativeFloatPrecision_Ignored_532) {

    _Precision precision(-1, 10);

    EXPECT_EQ(&emitter, &emitter.SetLocalPrecision(precision));

}



TEST_F(EmitterTest_532, SetLocalPrecision_NegativeDoublePrecision_Ignored_532) {

    _Precision precision(6, -1);

    EXPECT_EQ(&emitter, &emitter.SetLocalPrecision(precision));

}



TEST_F(EmitterTest_532, SetLocalPrecision_ZeroFloatAndDoublePrecision_SetToZero_532) {

    _Precision precision(0, 0);

    EXPECT_EQ(&emitter, &emitter.SetLocalPrecision(precision));

}
