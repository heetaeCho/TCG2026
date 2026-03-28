#include <gtest/gtest.h>

#include "TestProjects/re2/util/rune.cc"



namespace {



using namespace re2;



TEST_F(RuneConversionTest_204, SingleByteCharacter_204) {

    Rune rune;

    const char* str = "\x41";  // ASCII 'A'

    int result = chartorune(&rune, str);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(rune, 65);  // Unicode for 'A'

}



TEST_F(RuneConversionTest_204, TwoByteCharacter_204) {

    Rune rune;

    const char* str = "\xc3\xa9";  // UTF-8 for é

    int result = chartorune(&rune, str);

    EXPECT_EQ(result, 2);

    EXPECT_EQ(rune, 233);  // Unicode for 'é'

}



TEST_F(RuneConversionTest_204, ThreeByteCharacter_204) {

    Rune rune;

    const char* str = "\xe9\x81\x93";  // UTF-8 for 道

    int result = chartorune(&rune, str);

    EXPECT_EQ(result, 3);

    EXPECT_EQ(rune, 29654);  // Unicode for '道'

}



TEST_F(RuneConversionTest_204, FourByteCharacter_204) {

    Rune rune;

    const char* str = "\xf0\x9f\x8c\x88";  // UTF-8 for 🌈

    int result = chartorune(&rune, str);

    EXPECT_EQ(result, 4);

    EXPECT_EQ(rune, 127752);  // Unicode for '🌈'

}



TEST_F(RuneConversionTest_204, InvalidTwoByteSequence_204) {

    Rune rune;

    const char* str = "\xc3\x80";  // Invalid UTF-8 sequence

    int result = chartorune(&rune, str);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(rune, Bad);  // Expected to return Bad for invalid sequence

}



TEST_F(RuneConversionTest_204, InvalidThreeByteSequence_204) {

    Rune rune;

    const char* str = "\xe9\x81";  // Incomplete UTF-8 sequence

    int result = chartorune(&rune, str);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(rune, Bad);  // Expected to return Bad for invalid sequence

}



TEST_F(RuneConversionTest_204, InvalidFourByteSequence_204) {

    Rune rune;

    const char* str = "\xf0\x9f\x8c";  // Incomplete UTF-8 sequence

    int result = chartorune(&rune, str);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(rune, Bad);  // Expected to return Bad for invalid sequence

}



TEST_F(RuneConversionTest_204, EmptyString_204) {

    Rune rune;

    const char* str = "";

    int result = chartorune(&rune, str);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(rune, Bad);  // Expected to return Bad for empty string

}



TEST_F(RuneConversionTest_204, OverlongEncodingTwoBytes_204) {

    Rune rune;

    const char* str = "\xc0\x80";  // Overlong encoding of null character

    int result = chartorune(&rune, str);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(rune, Bad);  // Expected to return Bad for overlong encoding

}



TEST_F(RuneConversionTest_204, OverlongEncodingThreeBytes_204) {

    Rune rune;

    const char* str = "\xe0\x80\x80";  // Overlong encoding of null character

    int result = chartorune(&rune, str);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(rune, Bad);  // Expected to return Bad for overlong encoding

}



TEST_F(RuneConversionTest_204, OverlongEncodingFourBytes_204) {

    Rune rune;

    const char* str = "\xf0\x80\x80\x80";  // Overlong encoding of null character

    int result = chartorune(&rune, str);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(rune, Bad);  // Expected to return Bad for overlong encoding

}



}  // namespace
