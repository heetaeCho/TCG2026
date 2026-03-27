#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"

#include <sstream>



class EmitterTest_39 : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_39, WriteChar_NormalOperation_39) {

    char ch = 'a';

    emitter << ch;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_39, WriteChar_BoundaryCondition_EmptyChar_39) {

    char ch = '\0';

    emitter << ch;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_39, WriteString_NormalOperation_39) {

    std::string str = "test";

    emitter << str;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_39, WriteString_BoundaryCondition_EmptyString_39) {

    std::string str = "";

    emitter << str;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_39, WriteBool_NormalOperation_True_39) {

    bool value = true;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_39, WriteBool_NormalOperation_False_39) {

    bool value = false;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_39, SetIndent_ValidValue_39) {

    EXPECT_TRUE(emitter.SetIndent(2));

}



TEST_F(EmitterTest_39, SetIndent_BoundaryCondition_Zero_39) {

    EXPECT_FALSE(emitter.SetIndent(0));

}



TEST_F(EmitterTest_39, SetIndent_ExceptionalCase_TooLarge_39) {

    // Assuming a reasonable upper limit for indentation

    EXPECT_FALSE(emitter.SetIndent(1024));

}



TEST_F(EmitterTest_39, WriteFloat_NormalOperation_39) {

    float value = 3.14f;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_39, WriteDouble_NormalOperation_39) {

    double value = 2.71828;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_39, SetFloatPrecision_ValidValue_39) {

    EXPECT_TRUE(emitter.SetFloatPrecision(5));

}



TEST_F(EmitterTest_39, SetDoublePrecision_ValidValue_39) {

    EXPECT_TRUE(emitter.SetDoublePrecision(10));

}



TEST_F(EmitterTest_39, SetFormatFunctions_NormalOperation_39) {

    EXPECT_TRUE(emitter.SetStringFormat(YAML::EMITTER_MANIP::Auto));

    EXPECT_TRUE(emitter.SetBoolFormat(YAML::EMITTER_MANIP::TrueFalse));

    EXPECT_TRUE(emitter.SetNullFormat(YAML::EMITTER_MANIP::Tilde));

    EXPECT_TRUE(emitter.SetIntBase(YAML::EMITTER_MANIP::Dec));

    EXPECT_TRUE(emitter.SetSeqFormat(YAML::EMITTER_MANIP::Block));

    EXPECT_TRUE(emitter.SetMapFormat(YAML::EMITTER_MANIP::Flow));

}



TEST_F(EmitterTest_39, SetOutputCharset_NormalOperation_Utf8_39) {

    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EMITTER_MANIP::Utf8));

}
