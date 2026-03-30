#include <gtest/gtest.h>

#include <yaml-cpp/emitter.h>

#include <sstream>



class EmitterTest_51 : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_51, WriteIntegralType_NormalOperation_51) {

    unsigned short value = 42;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_51, WriteIntegralType_BoundaryCondition_Zero_51) {

    unsigned short value = 0;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_51, WriteIntegralType_BoundaryCondition_MaxValue_51) {

    unsigned short value = USHRT_MAX;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_51, WriteIntegralType_ErrorCase_AfterBadState_51) {

    // Assuming some operation that sets the emitter to a bad state

    emitter.SetIndent(0); // Invalid indent should set the emitter to a bad state

    unsigned short value = 42;

    emitter << value;

    EXPECT_FALSE(emitter.good());

}



TEST_F(EmitterTest_51, WriteIntegralType_VerifyOutput_51) {

    unsigned short value = 42;

    emitter << value;

    std::string output = emitter.c_str();

    EXPECT_EQ(output, "42");

}
