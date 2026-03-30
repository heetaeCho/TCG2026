#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"

#include <sstream>



class EmitterTest_59 : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_59, WriteString_NormalOperation_59) {

    emitter << "test";

    EXPECT_STREQ(emitter.c_str(), "test");

}



TEST_F(EmitterTest_59, WriteString_EmptyString_59) {

    emitter << "";

    EXPECT_STREQ(emitter.c_str(), "");

}



TEST_F(EmitterTest_59, WriteBool_NormalOperation_59) {

    emitter << true;

    EXPECT_STREQ(emitter.c_str(), "true");

}



TEST_F(EmitterTest_59, WriteBool_FalseValue_59) {

    emitter << false;

    EXPECT_STREQ(emitter.c_str(), "false");

}



TEST_F(EmitterTest_59, WriteChar_NormalOperation_59) {

    emitter << 'a';

    EXPECT_STREQ(emitter.c_str(), "a");

}



TEST_F(EmitterTest_59, SetIndent_ValidValue_59) {

    YAML::_Indent indent(2);

    emitter.SetLocalIndent(indent);

    // This test only checks if the function call does not throw or crash

}



TEST_F(EmitterTest_59, SetIndent_ZeroValue_59) {

    YAML::_Indent indent(0);

    emitter.SetLocalIndent(indent);

    // This test only checks if the function call does not throw or crash for boundary value

}



TEST_F(EmitterTest_59, WriteIntegralType_NormalOperation_59) {

    emitter << 42;

    EXPECT_STREQ(emitter.c_str(), "42");

}



TEST_F(EmitterTest_59, WriteStreamable_NormalOperation_59) {

    std::string str = "streamable";

    emitter << str;

    EXPECT_STREQ(emitter.c_str(), "streamable");

}



TEST_F(EmitterTest_59, SetOutputCharset_ValidValue_59) {

    bool result = emitter.SetOutputCharset(YAML::EMITTER_MANIP::Utf8);

    EXPECT_TRUE(result);

}



TEST_F(EmitterTest_59, Good_ReturnsTrueInitially_59) {

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_59, GetLastError_EmptyStringInitially_59) {

    EXPECT_EQ(emitter.GetLastError(), "");

}
