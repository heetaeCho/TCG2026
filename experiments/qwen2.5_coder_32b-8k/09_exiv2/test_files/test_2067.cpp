#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "UnicodeConversions.cpp"



class UnicodeConversionsTest_2067 : public ::testing::Test {

protected:

    UTF32Unit cpIn;

    UTF16Unit utf16Out[2];

    size_t utf16Len;

    size_t utf16Written;



    void SetUp() override {

        cpIn = 0x0;

        utf16Len = sizeof(utf16Out) / sizeof(UTF16Unit);

        utf16Written = 0;

    }

};



TEST_F(UnicodeConversionsTest_2067, PutBasicMultilingualPlaneCodePoint_2067) {

    cpIn = 0x005A; // 'Z'

    CodePoint_to_UTF16Nat(cpIn, utf16Out, utf16Len, &utf16Written);

    EXPECT_EQ(utf16Written, 1);

    EXPECT_EQ(utf16Out[0], 0x005A);

}



TEST_F(UnicodeConversionsTest_2067, PutHighSurrogateCodePoint_2067) {

    cpIn = 0xD800;

    EXPECT_THROW(CodePoint_to_UTF16Nat(cpIn, utf16Out, utf16Len, &utf16Written), XMP_Error);

}



TEST_F(UnicodeConversionsTest_2067, PutLowSurrogateCodePoint_2067) {

    cpIn = 0xDFFF;

    EXPECT_THROW(CodePoint_to_UTF16Nat(cpIn, utf16Out, utf16Len, &utf16Written), XMP_Error);

}



TEST_F(UnicodeConversionsTest_2067, PutSurrogatePairCodePoint_2067) {

    cpIn = 0x10437; // '䇷'

    CodePoint_to_UTF16Nat(cpIn, utf16Out, utf16Len, &utf16Written);

    EXPECT_EQ(utf16Written, 2);

    EXPECT_EQ(utf16Out[0], 0xD801); // High surrogate

    EXPECT_EQ(utf16Out[1], 0xDC37); // Low surrogate

}



TEST_F(UnicodeConversionsTest_2067, PutCodePointOutsideBMP_2067) {

    cpIn = 0x1F4A9; // '💩'

    CodePoint_to_UTF16Nat(cpIn, utf16Out, utf16Len, &utf16Written);

    EXPECT_EQ(utf16Written, 2);

    EXPECT_EQ(utf16Out[0], 0xD83D); // High surrogate

    EXPECT_EQ(utf16Out[1], 0xDCA9); // Low surrogate

}



TEST_F(UnicodeConversionsTest_2067, PutCodePointWithZeroLengthBuffer_2067) {

    cpIn = 0x005A; // 'Z'

    utf16Len = 0;

    CodePoint_to_UTF16Nat(cpIn, utf16Out, utf16Len, &utf16Written);

    EXPECT_EQ(utf16Written, 0);

}



TEST_F(UnicodeConversionsTest_2067, PutCodePointWithInsufficientBufferLengthForSurrogatePair_2067) {

    cpIn = 0x1F4A9; // '💩'

    utf16Len = 1;

    EXPECT_THROW(CodePoint_to_UTF16Nat(cpIn, utf16Out, utf16Len, &utf16Written), XMP_Error);

}
