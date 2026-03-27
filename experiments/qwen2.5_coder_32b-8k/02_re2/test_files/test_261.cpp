#include <gtest/gtest.h>

#include "re2/re2.cc"  // Adjust path as necessary



namespace re2 {



TEST(AsciiStrcasecmpTest_261, EqualStringsLowerCase_261) {

    const char* a = "test";

    const char* b = "test";

    size_t len = 4;

    EXPECT_EQ(ascii_strcasecmp(a, b, len), 0);

}



TEST(AsciiStrcasecmpTest_261, EqualStringsUpperCase_261) {

    const char* a = "TEST";

    const char* b = "TEST";

    size_t len = 4;

    EXPECT_EQ(ascii_strcasecmp(a, b, len), 0);

}



TEST(AsciiStrcasecmpTest_261, EqualMixedCase_261) {

    const char* a = "TeSt";

    const char* b = "tEsT";

    size_t len = 4;

    EXPECT_EQ(ascii_strcasecmp(a, b, len), 0);

}



TEST(AsciiStrcasecmpTest_261, DifferentStringsLowerCase_261) {

    const char* a = "test";

    const char* b = "text";

    size_t len = 4;

    EXPECT_NE(ascii_strcasecmp(a, b, len), 0);

}



TEST(AsciiStrcasecmpTest_261, DifferentStringsUpperCase_261) {

    const char* a = "TEST";

    const char* b = "TEXT";

    size_t len = 4;

    EXPECT_NE(ascii_strcasecmp(a, b, len), 0);

}



TEST(AsciiStrcasecmpTest_261, DifferentMixedCase_261) {

    const char* a = "TeSt";

    const char* b = "tExT";

    size_t len = 4;

    EXPECT_NE(ascii_strcasecmp(a, b, len), 0);

}



TEST(AsciiStrcasecmpTest_261, DifferentLengthStrings_261) {

    const char* a = "test";

    const char* b = "tes";

    size_t len = 4;

    EXPECT_NE(ascii_strcasecmp(a, b, len), 0);

}



TEST(AsciiStrcasecmpTest_261, EmptyStrings_261) {

    const char* a = "";

    const char* b = "";

    size_t len = 0;

    EXPECT_EQ(ascii_strcasecmp(a, b, len), 0);

}



TEST(AsciiStrcasecmpTest_261, SingleCharacterSame_261) {

    const char* a = "a";

    const char* b = "A";

    size_t len = 1;

    EXPECT_EQ(ascii_strcasecmp(a, b, len), 0);

}



TEST(AsciiStrcasecmpTest_261, SingleCharacterDifferent_261) {

    const char* a = "a";

    const char* b = "b";

    size_t len = 1;

    EXPECT_NE(ascii_strcasecmp(a, b, len), 0);

}



}  // namespace re2
