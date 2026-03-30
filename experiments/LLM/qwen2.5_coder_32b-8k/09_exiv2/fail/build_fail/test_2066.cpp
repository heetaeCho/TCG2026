#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming UTF32Unit and UTF16Unit are defined as follows:

typedef uint32_t UTF32Unit;

typedef uint16_t UTF16Unit;



extern "C" void CodePoint_to_UTF16Nat_Surrogate(const UTF32Unit cpIn, UTF16Unit * utf16Out, const size_t utf16Len, size_t * utf16Written);



namespace {



class UnicodeConversionsTest_2066 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialization code if necessary

    }



    void TearDown() override {

        // Cleanup code if necessary

    }

};



TEST_F(UnicodeConversionsTest_2066, NormalOperation_2066) {

    UTF32Unit cpIn = 0x10400; // Example surrogate pair code point

    UTF16Unit utf16Out[2];

    size_t utf16Written;

    

    CodePoint_to_UTF16Nat_Surrogate(cpIn, utf16Out, 2, &utf16Written);



    EXPECT_EQ(utf16Written, 2);

    EXPECT_EQ(utf16Out[0], 0xD801); // High surrogate

    EXPECT_EQ(utf16Out[1], 0xDC00); // Low surrogate

}



TEST_F(UnicodeConversionsTest_2066, BoundaryCondition_MinimumSurrogate_2066) {

    UTF32Unit cpIn = 0x10000; // Minimum surrogate pair code point

    UTF16Unit utf16Out[2];

    size_t utf16Written;

    

    CodePoint_to_UTF16Nat_Surrogate(cpIn, utf16Out, 2, &utf16Written);



    EXPECT_EQ(utf16Written, 2);

    EXPECT_EQ(utf16Out[0], 0xD800); // High surrogate

    EXPECT_EQ(utf16Out[1], 0xDC00); // Low surrogate

}



TEST_F(UnicodeConversionsTest_2066, BoundaryCondition_MaximumSurrogate_2066) {

    UTF32Unit cpIn = 0x10FFFF; // Maximum surrogate pair code point

    UTF16Unit utf16Out[2];

    size_t utf16Written;

    

    CodePoint_to_UTF16Nat_Surrogate(cpIn, utf16Out, 2, &utf16Written);



    EXPECT_EQ(utf16Written, 2);

    EXPECT_EQ(utf16Out[0], 0xDBFF); // High surrogate

    EXPECT_EQ(utf16Out[1], 0xDFFF); // Low surrogate

}



TEST_F(UnicodeConversionsTest_2066, ErrorCondition_OutOfRange_2066) {

    UTF32Unit cpIn = 0x110000; // Out of range code point

    UTF16Unit utf16Out[2];

    size_t utf16Written;

    

    EXPECT_THROW(CodePoint_to_UTF16Nat_Surrogate(cpIn, utf16Out, 2, &utf16Written), XMP_Error);

}



TEST_F(UnicodeConversionsTest_2066, ErrorCondition_NotEnoughSpace_2066) {

    UTF32Unit cpIn = 0x10400; // Example surrogate pair code point

    UTF16Unit utf16Out[1]; // Not enough space for the output

    size_t utf16Written;

    

    CodePoint_to_UTF16Nat_Surrogate(cpIn, utf16Out, 1, &utf16Written);



    EXPECT_EQ(utf16Written, 0);

}



} // namespace
