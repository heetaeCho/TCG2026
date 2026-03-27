#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the function to be tested is part of a class or namespace

// For this example, let's assume it's a standalone function and wrap it in a class for testing purposes.

class UnicodeConversionsTest {

public:

    static void CodePoint_to_UTF16Swp ( const UTF32Unit cpIn, UTF16Unit * utf16Out, const size_t utf16Len, size_t * utf16Written ) {

        ::CodePoint_to_UTF16Swp(cpIn, utf16Out, utf16Len, utf16Written);

    }

};



// Mock function to replace UTF16OutSwap if needed

void mock_UTF16OutSwap(UTF16Unit* utf16Out, UTF16Unit value) {

    *utf16Out = value;

}



TEST_F(UnicodeConversionsTest_2077, NormalOperation_BMP_2077) {

    UTF32Unit cpIn = 0x4E2D; // Chinese character '中'

    UTF16Unit utf16Out[1];

    size_t utf16Len = 1;

    size_t utf16Written;



    UnicodeConversionsTest::CodePoint_to_UTF16Swp(cpIn, utf16Out, utf16Len, &utf16Written);



    EXPECT_EQ(utf16Written, 1);

    EXPECT_EQ(utf16Out[0], cpIn);

}



TEST_F(UnicodeConversionsTest_2077, NormalOperation_SurrogatePair_2077) {

    UTF32Unit cpIn = 0x1F600; // Grinning Face emoji

    UTF16Unit utf16Out[2];

    size_t utf16Len = 2;

    size_t utf16Written;



    UnicodeConversionsTest::CodePoint_to_UTF16Swp(cpIn, utf16Out, utf16Len, &utf16Written);



    EXPECT_EQ(utf16Written, 2);

    EXPECT_EQ(utf16Out[0], 0xD83D); // High surrogate

    EXPECT_EQ(utf16Out[1], 0xDE00); // Low surrogate

}



TEST_F(UnicodeConversionsTest_2077, BoundaryCondition_UTF16LenZero_2077) {

    UTF32Unit cpIn = 0x4E2D; // Chinese character '中'

    UTF16Unit utf16Out[1];

    size_t utf16Len = 0;

    size_t utf16Written;



    UnicodeConversionsTest::CodePoint_to_UTF16Swp(cpIn, utf16Out, utf16Len, &utf16Written);



    EXPECT_EQ(utf16Written, 0);

}



TEST_F(UnicodeConversionsTest_2077, ErrorCase_SurrogateCodePoint_2077) {

    UTF32Unit cpIn = 0xD800; // High surrogate

    UTF16Unit utf16Out[1];

    size_t utf16Len = 1;

    size_t utf16Written;



    EXPECT_THROW(UnicodeConversionsTest::CodePoint_to_UTF16Swp(cpIn, utf16Out, utf16Len, &utf16Written), XMP_Error);

}



TEST_F(UnicodeConversionsTest_2077, ErrorCase_OutOfRange_2077) {

    UTF32Unit cpIn = 0x110000; // Out of range

    UTF16Unit utf16Out[2];

    size_t utf16Len = 2;

    size_t utf16Written;



    EXPECT_THROW(UnicodeConversionsTest::CodePoint_to_UTF16Swp(cpIn, utf16Out, utf16Len, &utf16Written), XMP_Error);

}
