#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"

#include <sstream>



using namespace YAML;



class EmitterTest_34 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_34, WriteIntegralType_NormalOperation_34) {

    emitter.WriteIntegralType(123);

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_34, WriteIntegralType_BoundaryCondition_Zero_34) {

    emitter.WriteIntegralType(0);

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_34, WriteIntegralType_BoundaryCondition_NegativeNumber_34) {

    emitter.WriteIntegralType(-123);

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_34, WriteIntegralType_ExceptionalCase_NotGood_34) {

    Emitter badEmitter;

    badEmitter.SetLocalValue(EMITTER_MANIP::BadManipulator); // Assuming there's a way to make the emitter not good

    badEmitter.WriteIntegralType(123);

    EXPECT_FALSE(badEmitter.good());

}



TEST_F(EmitterTest_34, WriteIntegralType_VerifyOutput_34) {

    std::ostringstream os;

    Emitter localEmitter(os);

    localEmitter.WriteIntegralType(456);

    EXPECT_EQ("456", os.str());

}
