#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/src/emitterutils.h"

#include "yaml-cpp/ostream_wrapper.h"



using namespace YAML::Utils;

using ::testing::_;

using ::testing::StrEq;



class EmitterUtilsTest : public ::testing::Test {

protected:

    std::ostringstream stream;

    ostream_wrapper out{stream};

};



TEST_F(EmitterUtilsTest, WriteChar_LowercaseLetter_632) {

    EXPECT_TRUE(WriteChar(out, 'a', StringEscaping::None));

    EXPECT_STREQ(stream.str().c_str(), "a");

}



TEST_F(EmitterUtilsTest, WriteChar_UppercaseLetter_632) {

    EXPECT_TRUE(WriteChar(out, 'Z', StringEscaping::None));

    EXPECT_STREQ(stream.str().c_str(), "Z");

}



TEST_F(EmitterUtilsTest, WriteChar_DoubleQuote_632) {

    EXPECT_TRUE(WriteChar(out, '\"', StringEscaping::None));

    EXPECT_STREQ(stream.str().c_str(), "\"\"");

}



TEST_F(EmitterUtilsTest, WriteChar_Tab_632) {

    EXPECT_TRUE(WriteChar(out, '\t', StringEscaping::None));

    EXPECT_STREQ(stream.str().c_str(), "\"\t\"");

}



TEST_F(EmitterUtilsTest, WriteChar_Newline_632) {

    EXPECT_TRUE(WriteChar(out, '\n', StringEscaping::None));

    EXPECT_STREQ(stream.str().c_str(), "\"\n\"");

}



TEST_F(EmitterUtilsTest, WriteChar_Backspace_632) {

    EXPECT_TRUE(WriteChar(out, '\b', StringEscaping::None));

    EXPECT_STREQ(stream.str().c_str(), "\"\b\"");

}



TEST_F(EmitterUtilsTest, WriteChar_CarriageReturn_632) {

    EXPECT_TRUE(WriteChar(out, '\r', StringEscaping::None));

    EXPECT_STREQ(stream.str().c_str(), "\"\r\"");

}



TEST_F(EmitterUtilsTest, WriteChar_FormFeed_632) {

    EXPECT_TRUE(WriteChar(out, '\f', StringEscaping::None));

    EXPECT_STREQ(stream.str().c_str(), "\"\f\"");

}



TEST_F(EmitterUtilsTest, WriteChar_Backslash_632) {

    EXPECT_TRUE(WriteChar(out, '\\', StringEscaping::None));

    EXPECT_STREQ(stream.str().c_str(), "\"\\\\\"");

}



TEST_F(EmitterUtilsTest, WriteChar_PrintableAscii_632) {

    EXPECT_TRUE(WriteChar(out, '!', StringEscaping::None));

    EXPECT_STREQ(stream.str().c_str(), "\"!\"");

}



TEST_F(EmitterUtilsTest, WriteChar_UnprintableAscii_632) {

    EXPECT_TRUE(WriteChar(out, '\x1F', StringEscaping::None));

    EXPECT_THAT(stream.str(), testing::StartsWith("\"\\u001"));

}



TEST_F(EmitterUtilsTest, WriteChar_HigherAscii_632) {

    EXPECT_TRUE(WriteChar(out, '\x80', StringEscaping::None));

    EXPECT_STREQ(stream.str().c_str(), "\"\x80\"");

}
