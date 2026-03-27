#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    void UTF32Swp_to_UTF16Swp(const unsigned int* utf32In, size_t utf32Len, unsigned short* utf16Out, size_t utf16Len, size_t* utf32Read, size_t* utf16Written);

}



namespace {



class UnicodeConversionsTest_2085 : public ::testing::Test {

protected:

    static constexpr size_t kMaxBufferLength = 1024;

    unsigned int utf32In[kMaxBufferLength];

    unsigned short utf16Out[kMaxBufferLength];

    size_t utf32Read;

    size_t utf16Written;



    void SetUp() override {

        memset(utf32In, 0, sizeof(utf32In));

        memset(utf16Out, 0, sizeof(utf16Out));

        utf32Read = 0;

        utf16Written = 0;

    }

};



TEST_F(UnicodeConversionsTest_2085, NormalOperation_2085) {

    // Test normal operation with simple ASCII characters

    utf32In[0] = 'A';

    utf32In[1] = 'B';

    UTF32Swp_to_UTF16Swp(utf32In, 2, utf16Out, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf16Out[0], 'A');

    EXPECT_EQ(utf16Out[1], 'B');

    EXPECT_EQ(utf32Read, 2);

    EXPECT_EQ(utf16Written, 2);

}



TEST_F(UnicodeConversionsTest_2085, BoundaryCondition_ZeroLengthInput_2085) {

    // Test with zero length input

    UTF32Swp_to_UTF16Swp(utf32In, 0, utf16Out, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 0);

    EXPECT_EQ(utf16Written, 0);

}



TEST_F(UnicodeConversionsTest_2085, BoundaryCondition_ZeroLengthOutput_2085) {

    // Test with zero length output

    utf32In[0] = 'A';

    UTF32Swp_to_UTF16Swp(utf32In, 1, utf16Out, 0, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 0);

    EXPECT_EQ(utf16Written, 0);

}



TEST_F(UnicodeConversionsTest_2085, BoundaryCondition_EqualLengths_2085) {

    // Test with equal input and output lengths

    utf32In[0] = 'A';

    UTF32Swp_to_UTF16Swp(utf32In, 1, utf16Out, 1, &utf32Read, &utf16Written);

    EXPECT_EQ(utf16Out[0], 'A');

    EXPECT_EQ(utf32Read, 1);

    EXPECT_EQ(utf16Written, 1);

}



TEST_F(UnicodeConversionsTest_2085, BoundaryCondition_OutputBufferTooSmall_2085) {

    // Test with output buffer too small for surrogate pair

    utf32In[0] = 0x10FFF; // A code point requiring a surrogate pair

    UTF32Swp_to_UTF16Swp(utf32In, 1, utf16Out, 1, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 0); // Should not read any input due to insufficient output space

    EXPECT_EQ(utf16Written, 0);

}



TEST_F(UnicodeConversionsTest_2085, NormalOperation_SurrogatePairs_2085) {

    // Test with a code point that requires a surrogate pair

    utf32In[0] = 0x10FFF; // A code point requiring a surrogate pair

    UTF32Swp_to_UTF16Swp(utf32In, 1, utf16Out, 4, &utf32Read, &utf16Written);

    EXPECT_EQ((utf16Out[0] >> 10) + 0xD7C0, (0x10FFF >> 10));

    EXPECT_EQ((utf16Out[0] & 0x3FF), ((0x10FFF >> 10) & 0x3FF));

    EXPECT_EQ(utf16Out[1], 0xDC00 + (0x10FFF & 0x3FF));

    EXPECT_EQ(utf32Read, 1);

    EXPECT_EQ(utf16Written, 2);

}



TEST_F(UnicodeConversionsTest_2085, ExceptionalOperation_IllegalCodePoint_2085) {

    // Test with an illegal code point (e.g., one outside the range of UTF-32)

    utf32In[0] = 0x110000; // Outside valid Unicode range

    UTF32Swp_to_UTF16Swp(utf32In, 1, utf16Out, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 0); // Should not read any input due to illegal code point

    EXPECT_EQ(utf16Written, 0);

}



} // namespace
