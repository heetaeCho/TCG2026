#include <gtest/gtest.h>

#include <yaml-cpp/emitter.h>



class EmitterTest_515 : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_515, GoodInitialStatus_515) {

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_515, WriteStringNormalOperation_515) {

    emitter.Write("test");

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_515, WriteBoolNormalOperation_515) {

    emitter.Write(true);

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_515, SetIndentBoundaryCondition_515) {

    EXPECT_TRUE(emitter.SetIndent(0));

    EXPECT_TRUE(emitter.SetIndent(1));

    EXPECT_TRUE(emitter.SetIndent(10));

    EXPECT_FALSE(emitter.SetIndent(20)); // Assuming 20 is an invalid indent value

}



TEST_F(EmitterTest_515, SetPrecisionBoundaryCondition_515) {

    EXPECT_TRUE(emitter.SetFloatPrecision(0));

    EXPECT_TRUE(emitter.SetDoublePrecision(0));

    EXPECT_TRUE(emitter.SetFloatPrecision(17));

    EXPECT_TRUE(emitter.SetDoublePrecision(17));

    EXPECT_FALSE(emitter.SetFloatPrecision(18)); // Assuming 18 is an invalid precision value

    EXPECT_FALSE(emitter.SetDoublePrecision(18)); // Assuming 18 is an invalid precision value

}



TEST_F(EmitterTest_515, SetFormatNormalOperation_515) {

    EXPECT_TRUE(emitter.SetStringFormat(YAML::EMITTER_MANIP::Auto));

    EXPECT_TRUE(emitter.SetBoolFormat(YAML::EMITTER_MANIP::TrueFalse));

    EXPECT_TRUE(emitter.SetNullFormat(YAML::EMITTER_MANIP::Tilde));

}



TEST_F(EmitterTest_515, SetInvalidFormat_515) {

    EXPECT_FALSE(emitter.SetStringFormat(static_cast<YAML::EMITTER_MANIP>(-1))); // Assuming -1 is an invalid format

    EXPECT_FALSE(emitter.SetBoolFormat(static_cast<YAML::EMITTER_MANIP>(-1)));

    EXPECT_FALSE(emitter.SetNullFormat(static_cast<YAML::EMITTER_MANIP>(-1)));

}



TEST_F(EmitterTest_515, GetLastErrorInitialStatus_515) {

    EXPECT_EQ(emitter.GetLastError(), "");

}
