#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitter.h"



namespace YAML {



class EmitterTest : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_47, WriteCString_NormalOperation_47) {

    const char* testStr = "test";

    emitter << testStr;

    EXPECT_EQ(emitter.size(), 4);

}



TEST_F(EmitterTest_47, WriteCString_EmptyString_47) {

    const char* emptyStr = "";

    emitter << emptyStr;

    EXPECT_EQ(emitter.size(), 0);

}



TEST_F(EmitterTest_47, WriteStdString_NormalOperation_47) {

    std::string testStr = "test";

    emitter << testStr;

    EXPECT_EQ(emitter.size(), 4);

}



TEST_F(EmitterTest_47, WriteStdString_EmptyString_47) {

    std::string emptyStr = "";

    emitter << emptyStr;

    EXPECT_EQ(emitter.size(), 0);

}



TEST_F(EmitterTest_47, WriteBool_True_47) {

    emitter << true;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_47, WriteBool_False_47) {

    emitter << false;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_47, WriteChar_NormalOperation_47) {

    char testChar = 'a';

    emitter << testChar;

    EXPECT_EQ(emitter.size(), 1);

}



TEST_F(EmitterTest_47, SetIndent_DefaultValue_47) {

    EXPECT_TRUE(emitter.SetIndent(2));

}



TEST_F(EmitterTest_47, SetIndent_ZeroValue_47) {

    EXPECT_FALSE(emitter.SetIndent(0));

}



TEST_F(EmitterTest_47, SetFloatPrecision_ValidValue_47) {

    EXPECT_TRUE(emitter.SetFloatPrecision(5));

}



TEST_F(EmitterTest_47, SetDoublePrecision_ValidValue_47) {

    EXPECT_TRUE(emitter.SetDoublePrecision(10));

}



TEST_F(EmitterTest_47, SetInvalidOption_ReturnsFalse_47) {

    EXPECT_FALSE(emitter.SetBoolFormat(static_cast<EMITTER_MANIP>(-1)));

}



TEST_F(EmitterTest_47, Good_DefaultState_47) {

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_47, GetLastError_EmptyStringInitially_47) {

    EXPECT_EQ(emitter.GetLastError(), "");

}



}  // namespace YAML
