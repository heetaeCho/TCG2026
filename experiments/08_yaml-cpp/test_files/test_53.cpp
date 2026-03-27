#include <gtest/gtest.h>

#include <yaml-cpp/emitter.h>



class EmitterTest_53 : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_53, WriteUnsignedLong_NormalOperation_53) {

    unsigned long value = 123456789;

    emitter << value;

    EXPECT_EQ(emitter.c_str(), "123456789");

}



TEST_F(EmitterTest_53, WriteUnsignedLong_BoundaryConditionZero_53) {

    unsigned long value = 0;

    emitter << value;

    EXPECT_EQ(emitter.c_str(), "0");

}



TEST_F(EmitterTest_53, WriteUnsignedLong_BoundaryConditionMaxValue_53) {

    unsigned long value = ULONG_MAX;

    emitter << value;

    std::stringstream ss;

    ss << ULONG_MAX;

    EXPECT_EQ(emitter.c_str(), ss.str());

}



TEST_F(EmitterTest_53, EmitterGood_AfterWrite_53) {

    unsigned long value = 123456789;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_53, GetLastError_EmptyAfterSuccessfulWrite_53) {

    unsigned long value = 123456789;

    emitter << value;

    EXPECT_EQ(emitter.GetLastError(), "");

}
