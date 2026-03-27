#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"



class EmitterTest : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_513, InitialCStrReturnsEmptyString_513) {

    EXPECT_STREQ(emitter.c_str(), "");

}



TEST_F(EmitterTest_513, WriteStringUpdatesCStr_513) {

    emitter.Write("Hello");

    EXPECT_STREQ(emitter.c_str(), "Hello");

}



TEST_F(EmitterTest_513, WriteMultipleStringsConcatenates_513) {

    emitter.Write("Hello").Write(" ").Write("World");

    EXPECT_STREQ(emitter.c_str(), "Hello World");

}



TEST_F(EmitterTest_513, WriteBoolUpdatesCStr_513) {

    emitter.Write(true);

    EXPECT_STREQ(emitter.c_str(), "true");



    emitter.Write(false);

    EXPECT_STREQ(emitter.c_str(), "truefalse");

}



TEST_F(EmitterTest_513, WriteCharUpdatesCStr_513) {

    emitter.Write('A');

    EXPECT_STREQ(emitter.c_str(), "A");



    emitter.Write('B');

    EXPECT_STREQ(emitter.c_str(), "AB");

}



TEST_F(EmitterTest_513, SetIndentAndWriteString_513) {

    emitter.SetIndent(4);

    emitter.Write("Indented Text");

    // Assuming indentation is applied as spaces before the text

    EXPECT_STREQ(emitter.c_str(), "    Indented Text");

}



TEST_F(EmitterTest_513, SetFloatPrecisionAndWriteDouble_513) {

    double value = 123.456789;

    emitter.SetFloatPrecision(2);

    emitter.Write(value);

    EXPECT_STREQ(emitter.c_str(), "123.46");



    emitter.Write(value);

    EXPECT_STREQ(emitter.c_str(), "123.46123.46");

}



TEST_F(EmitterTest_513, SetDoublePrecisionAndWriteDouble_513) {

    double value = 123.456789;

    emitter.SetDoublePrecision(5);

    emitter.Write(value);

    EXPECT_STREQ(emitter.c_str(), "123.45679");



    emitter.Write(value);

    EXPECT_STREQ(emitter.c_str(), "123.45679123.45679");

}



TEST_F(EmitterTest_513, SetBoolFormatAndWriteBool_513) {

    emitter.SetBoolFormat(YAML::TrueFalseBool);

    emitter.Write(true);

    EXPECT_STREQ(emitter.c_str(), "true");



    emitter.Write(false);

    EXPECT_STREQ(emitter.c_str(), "truefalse");

}



TEST_F(EmitterTest_513, SetStringFormatAndWriteString_513) {

    emitter.SetStringFormat(YAML::SingleQuoted);

    emitter.Write("Hello World");

    EXPECT_STREQ(emitter.c_str(), "'Hello World'");



    emitter.Write("Another String");

    EXPECT_STREQ(emitter.c_str(), "'Hello World''Another String'");

}



TEST_F(EmitterTest_513, WriteEmptyStringDoesNotChangeCStr_513) {

    emitter.Write("");

    EXPECT_STREQ(emitter.c_str(), "");

}



TEST_F(EmitterTest_513, SetIndentWithZeroDoesNotAddSpaces_513) {

    emitter.SetIndent(0);

    emitter.Write("No Indent");

    EXPECT_STREQ(emitter.c_str(), "No Indent");



    emitter.Write("More Text");

    EXPECT_STREQ(emitter.c_str(), "No IndentMore Text");

}
