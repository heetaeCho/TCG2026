#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitterutils.h"

#include "yaml-cpp/ostream_wrapper.h"



using namespace YAML::Utils;

using namespace testing;



class EmitterUtilsTest_630 : public Test {

protected:

    std::ostringstream stream;

    ostream_wrapper out{stream};

};



TEST_F(EmitterUtilsTest_630, NormalOperation_NoSpecialCharacters_630) {

    const char* str = "normalString";

    size_t size = strlen(str);

    bool result = WriteDoubleQuotedString(out, str, size, StringEscaping::None);



    EXPECT_TRUE(result);

    EXPECT_EQ(stream.str(), "\"normalString\"");

}



TEST_F(EmitterUtilsTest_630, NormalOperation_EscapeCharacters_630) {

    const char* str = "special\"\\n\t\r\b\f";

    size_t size = strlen(str);

    bool result = WriteDoubleQuotedString(out, str, size, StringEscaping::None);



    EXPECT_TRUE(result);

    EXPECT_EQ(stream.str(), "\"special\\\"\\n\\t\\r\\b\\f\"");

}



TEST_F(EmitterUtilsTest_630, BoundaryCondition_EmptyString_630) {

    const char* str = "";

    size_t size = strlen(str);

    bool result = WriteDoubleQuotedString(out, str, size, StringEscaping::None);



    EXPECT_TRUE(result);

    EXPECT_EQ(stream.str(), "\"\"");

}



TEST_F(EmitterUtilsTest_630, BoundaryCondition_SingleCharacter_630) {

    const char* str = "a";

    size_t size = strlen(str);

    bool result = WriteDoubleQuotedString(out, str, size, StringEscaping::None);



    EXPECT_TRUE(result);

    EXPECT_EQ(stream.str(), "\"a\"");

}



TEST_F(EmitterUtilsTest_630, BoundaryCondition_SingleEscapeCharacter_630) {

    const char* str = "\\";

    size_t size = strlen(str);

    bool result = WriteDoubleQuotedString(out, str, size, StringEscaping::None);



    EXPECT_TRUE(result);

    EXPECT_EQ(stream.str(), "\"\\\\\"");

}



TEST_F(EmitterUtilsTest_630, ExceptionalCase_ControlCharacters_630) {

    const char* str = "\x1f";

    size_t size = strlen(str);

    bool result = WriteDoubleQuotedString(out, str, size, StringEscaping::None);



    EXPECT_TRUE(result);

    // Assuming the function escapes control characters properly

    // This is a placeholder as the actual escape sequence depends on implementation details

    EXPECT_EQ(stream.str(), "\"\\u001f\"");

}



TEST_F(EmitterUtilsTest_630, ExceptionalCase_NonAsciiCharacters_StringEscapingNone_630) {

    const char* str = "\xc2\xa9"; // Copyright symbol (UTF-8)

    size_t size = strlen(str);

    bool result = WriteDoubleQuotedString(out, str, size, StringEscaping::None);



    EXPECT_TRUE(result);

    // Non-ASCII characters should not be escaped

    EXPECT_EQ(stream.str(), "\"©\"");

}



TEST_F(EmitterUtilsTest_630, ExceptionalCase_NonAsciiCharacters_StringEscapingNonAscii_630) {

    const char* str = "\xc2\xa9"; // Copyright symbol (UTF-8)

    size_t size = strlen(str);

    bool result = WriteDoubleQuotedString(out, str, size, StringEscaping::NonAscii);



    EXPECT_TRUE(result);

    // Non-ASCII characters should be escaped

    EXPECT_EQ(stream.str(), "\"\\u00a9\"");

}



TEST_F(EmitterUtilsTest_630, ExceptionalCase_ByteOrderMark_630) {

    const char* str = "\xef\xbb\xbf"; // UTF-8 Byte Order Mark (BOM)

    size_t size = strlen(str);

    bool result = WriteDoubleQuotedString(out, str, size, StringEscaping::None);



    EXPECT_TRUE(result);

    // Assuming the function escapes BOM properly

    // This is a placeholder as the actual escape sequence depends on implementation details

    EXPECT_EQ(stream.str(), "\"\\ufeff\"");

}
