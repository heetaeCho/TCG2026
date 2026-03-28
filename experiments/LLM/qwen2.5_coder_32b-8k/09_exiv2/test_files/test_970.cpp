#include <gtest/gtest.h>

#include "exiv2/types.hpp"

#include "pngimage.cpp"



namespace Exiv2 {



class tEXtToDataBufTest_970 : public ::testing::Test {

protected:

    DataBuf result;

};



TEST_F(tEXtToDataBufTest_970, EmptyInput_ReturnsFalse_970) {

    const byte* bytes = nullptr;

    size_t length = 0;

    EXPECT_TRUE(tEXtToDataBuf(bytes, length, result));

    EXPECT_EQ(result.size(), 0);

}



TEST_F(tEXtToDataBufTest_970, NoValidCharacters_ReturnsEmptyResult_970) {

    const byte bytes[] = "xyz";

    size_t length = sizeof(bytes) - 1;

    EXPECT_TRUE(tEXtToDataBuf(bytes, length, result));

    EXPECT_EQ(result.size(), 0);

}



TEST_F(tEXtToDataBufTest_970, SingleValidCharacter_ReturnsCorrectResult_970) {

    const byte bytes[] = "a";

    size_t length = sizeof(bytes) - 1;

    EXPECT_TRUE(tEXtToDataBuf(bytes, length, result));

    EXPECT_EQ(result.size(), 1);

    EXPECT_EQ(result.c_data()[0], 0xA); // 'a' -> 10 -> 0xA

}



TEST_F(tEXtToDataBufTest_970, MultipleValidCharacters_ReturnsCorrectResult_970) {

    const byte bytes[] = "abc";

    size_t length = sizeof(bytes) - 1;

    EXPECT_TRUE(tEXtToDataBuf(bytes, length, result));

    EXPECT_EQ(result.size(), 1);

    EXPECT_EQ(result.c_data()[0], 0xA + 0xB); // 'a' -> 10, 'b' -> 11 -> 0xAB

}



TEST_F(tEXtToDataBufTest_970, ValidCharactersWithNewlines_ReturnsCorrectResult_970) {

    const byte bytes[] = "\n\n\nabc";

    size_t length = sizeof(bytes) - 1;

    EXPECT_TRUE(tEXtToDataBuf(bytes, length, result));

    EXPECT_EQ(result.size(), 1);

    EXPECT_EQ(result.c_data()[0], 0xA + 0xB); // 'a' -> 10, 'b' -> 11 -> 0xAB

}



TEST_F(tEXtToDataBufTest_970, OnlyNewlines_ReturnsEmptyResult_970) {

    const byte bytes[] = "\n\n\n";

    size_t length = sizeof(bytes) - 1;

    EXPECT_TRUE(tEXtToDataBuf(bytes, length, result));

    EXPECT_EQ(result.size(), 0);

}



TEST_F(tEXtToDataBufTest_970, MixedCharacters_ReturnsCorrectResult_970) {

    const byte bytes[] = "a\nb\ncd";

    size_t length = sizeof(bytes) - 1;

    EXPECT_TRUE(tEXtToDataBuf(bytes, length, result));

    EXPECT_EQ(result.size(), 2);

    EXPECT_EQ(result.c_data()[0], 0xA); // 'a' -> 10 -> 0xA

    EXPECT_EQ(result.c_data()[1], 0xB + 0xC); // 'b' -> 11, 'c' -> 12 -> 0xBC

}



TEST_F(tEXtToDataBufTest_970, LargeInput_ReturnsCorrectResult_970) {

    const byte bytes[] = "aabbccddeeff";

    size_t length = sizeof(bytes) - 1;

    EXPECT_TRUE(tEXtToDataBuf(bytes, length, result));

    EXPECT_EQ(result.size(), 6);

    EXPECT_EQ(result.c_data()[0], 0xA + 0xB); // 'a' -> 10, 'b' -> 11 -> 0xAB

    EXPECT_EQ(result.c_data()[1], 0xC + 0xD); // 'c' -> 12, 'd' -> 13 -> 0xCD

    EXPECT_EQ(result.c_data()[2], 0xE + 0xF); // 'e' -> 14, 'f' -> 15 -> 0xEF

}



TEST_F(tEXtToDataBufTest_970, BoundaryCondition_NewlinesOnly_ReturnsEmptyResult_970) {

    const byte bytes[] = "\n\n\n";

    size_t length = sizeof(bytes) - 1;

    EXPECT_TRUE(tEXtToDataBuf(bytes, length, result));

    EXPECT_EQ(result.size(), 0);

}



TEST_F(tEXtToDataBufTest_970, BoundaryCondition_MaxValidCharacters_ReturnsCorrectResult_970) {

    const byte bytes[] = "abcdef";

    size_t length = sizeof(bytes) - 1;

    EXPECT_TRUE(tEXtToDataBuf(bytes, length, result));

    EXPECT_EQ(result.size(), 3);

    EXPECT_EQ(result.c_data()[0], 0xA + 0xB); // 'a' -> 10, 'b' -> 11 -> 0xAB

    EXPECT_EQ(result.c_data()[1], 0xC + 0xD); // 'c' -> 12, 'd' -> 13 -> 0xCD

    EXPECT_EQ(result.c_data()[2], 0xE + 0xF); // 'e' -> 14, 'f' -> 15 -> 0xEF

}



} // namespace Exiv2
