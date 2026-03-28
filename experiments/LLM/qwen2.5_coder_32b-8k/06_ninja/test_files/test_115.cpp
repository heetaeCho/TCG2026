#include <gtest/gtest.h>

#include <string>



// Assuming EncodeJSONString is declared in a header file named json.h

extern std::string EncodeJSONString(const std::string& in);



TEST(EncodeJSONStringTest_115, NormalOperation_SimpleString_115) {

    EXPECT_EQ(EncodeJSONString("hello"), "hello");

}



TEST(EncodeJSONStringTest_115, NormalOperation_StringWithEscapableChars_115) {

    EXPECT_EQ(EncodeJSONString("hello\nworld"), "hello\\nworld");

    EXPECT_EQ(EncodeJSONString("hello\tworld"), "hello\\tworld");

    EXPECT_EQ(EncodeJSONString("hello\"world"), "hello\\\"world");

    EXPECT_EQ(EncodeJSONString("hello\\world"), "hello\\\\world");

}



TEST(EncodeJSONStringTest_115, BoundaryCondition_EmptyString_115) {

    EXPECT_EQ(EncodeJSONString(""), "");

}



TEST(EncodeJSONStringTest_115, BoundaryCondition_SingleCharacterEscapable_115) {

    EXPECT_EQ(EncodeJSONString("\n"), "\\n");

    EXPECT_EQ(EncodeJSONString("\t"), "\\t");

    EXPECT_EQ(EncodeJSONString("\""), "\\\"");

    EXPECT_EQ(EncodeJSONString("\\"), "\\\\");

}



TEST(EncodeJSONStringTest_115, BoundaryCondition_SingleCharacterNonEscapable_115) {

    EXPECT_EQ(EncodeJSONString("a"), "a");

}



TEST(EncodeJSONStringTest_115, BoundaryCondition_ControlCharacters_115) {

    EXPECT_EQ(EncodeJSONString("\x00"), "\\u0000");

    EXPECT_EQ(EncodeJSONString("\x1f"), "\\u001f");

    EXPECT_EQ(EncodeJSONString("\x7f"), "\x7f"); // 127 is not a control character in JSON

}



TEST(EncodeJSONStringTest_115, ExceptionalCase_AllControlCharacters_115) {

    std::string all_control_chars;

    for (char c = 0; c < 0x20; ++c) {

        all_control_chars += c;

    }

    EXPECT_EQ(EncodeJSONString(all_control_chars), "\\u0000\\u0001\\u0002\\u0003\\u0004\\u0005\\u0006\\u0007\\b\\t\\n\\u000b\\f\\r\\u000e\\u000f\\u0010\\u0011\\u0012\\u0013\\u0014\\u0015\\u0016\\u0017\\u0018\\u0019\\u001a\\u001b\\u001c\\u001d\\u001e\\u001f");

}



TEST(EncodeJSONStringTest_115, ExceptionalCase_MixedCharacters_115) {

    EXPECT_EQ(EncodeJSONString("hello\x01world"), "hello\\u0001world");

}
