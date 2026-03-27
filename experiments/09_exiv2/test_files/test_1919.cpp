#include <gtest/gtest.h>

#include "XMPUtils-FileInfo.cpp"



// Mock function for ClassifyCharacter

void MockClassifyCharacter(const char* str, size_t offset, UniCharKind* kind, size_t* len, UniCodePoint* uniChar) {

    // This is a simple mock implementation. You can customize it based on your test needs.

    *kind = UCK_normal;

    *len = 1;

    *uniChar = static_cast<UniCodePoint>(str[offset]);

}



// Mock function for CodePointToUTF8

void MockCodePointToUTF8(UniCodePoint uniChar, XMP_VarString& str) {

    // This is a simple mock implementation. You can customize it based on your test needs.

    str += static_cast<char>(uniChar);

}



TEST(ApplyQuotesTest_1919, NormalOperation_NoQuotes_1919) {

    XMP_VarString item("HelloWorld");

    ApplyQuotes(&item, '"', '"', false);

    EXPECT_EQ(item, "HelloWorld");

}



TEST(ApplyQuotesTest_1919, NormalOperation_WithSpaces_1919) {

    XMP_VarString item("Hello World");

    ApplyQuotes(&item, '"', '"', false);

    EXPECT_EQ(item, "\"Hello World\"");

}



TEST(ApplyQuotesTest_1919, BoundaryCondition_EmptyString_1919) {

    XMP_VarString item("");

    ApplyQuotes(&item, '"', '"', false);

    EXPECT_EQ(item, "");

}



TEST(ApplyQuotesTest_1919, ExceptionalCase_ControlCharacter_1919) {

    XMP_VarString item("Hello\x01World");

    ApplyQuotes(&item, '"', '"', false);

    EXPECT_EQ(item, "\"Hello\"");

}



TEST(ApplyQuotesTest_1919, ExceptionalCase_Semicolon_1919) {

    XMP_VarString item("Hello;World");

    ApplyQuotes(&item, '"', '"', false);

    EXPECT_EQ(item, "\"Hello\"");

}



TEST(ApplyQuotesTest_1919, NormalOperation_AllowCommas_1919) {

    XMP_VarString item("Hello,World");

    ApplyQuotes(&item, '"', '"', true);

    EXPECT_EQ(item, "\"Hello,World\"");

}



TEST(ApplyQuotesTest_1919, ExceptionalCase_Comma_NotAllowed_1919) {

    XMP_VarString item("Hello,World");

    ApplyQuotes(&item, '"', '"', false);

    EXPECT_EQ(item, "\"Hello\"");

}



TEST(ApplyQuotesTest_1919, NormalOperation_WithQuotes_1919) {

    XMP_VarString item("He\"llo World");

    ApplyQuotes(&item, '"', '"', false);

    EXPECT_EQ(item, "\"He\"llo World\"");

}
