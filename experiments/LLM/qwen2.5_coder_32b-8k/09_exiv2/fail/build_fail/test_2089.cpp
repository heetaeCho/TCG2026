#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    typedef uint32_t UTF32Unit;

    typedef uint16_t UTF16Unit;

    void UTF32Swp_to_UTF16Nat(const UTF32Unit * utf32In, const size_t utf32Len, UTF16Unit * utf16Out, const size_t utf16Len, size_t * utf32Read, size_t * utf16Written);

}



class UnicodeConversionsTest_2089 : public ::testing::Test {

protected:

    static constexpr size_t kBufferLength = 1024;

    UTF32Unit utf32Input[kBufferLength];

    UTF16Unit utf16Output[kBufferLength];

    size_t utf32Read;

    size_t utf16Written;



    void SetUp() override {

        memset(utf32Input, 0, sizeof(utf32Input));

        memset(utf16Output, 0, sizeof(utf16Output));

        utf32Read = 0;

        utf16Written = 0;

    }

};



TEST_F(UnicodeConversionsTest_2089, NormalOperationBasic_2089) {

    utf32Input[0] = 0x0041; // 'A'

    utf32Input[1] = 0x0065; // 'e'



    UTF32Swp_to_UTF16Nat(utf32Input, 2, utf16Output, kBufferLength, &utf32Read, &utf16Written);



    EXPECT_EQ(utf32Read, 2);

    EXPECT_EQ(utf16Written, 2);

    EXPECT_EQ(utf16Output[0], 0x0041);

    EXPECT_EQ(utf16Output[1], 0x0065);

}



TEST_F(UnicodeConversionsTest_2089, NormalOperationSurrogatePair_2089) {

    utf32Input[0] = 0x1D11E; // Musical Symbol G Clef



    UTF32Swp_to_UTF16Nat(utf32Input, 1, utf16Output, kBufferLength, &utf32Read, &utf16Written);



    EXPECT_EQ(utf32Read, 1);

    EXPECT_EQ(utf16Written, 2);

    EXPECT_EQ(utf16Output[0], 0xD834);

    EXPECT_EQ(utf16Output[1], 0xDD1E);

}



TEST_F(UnicodeConversionsTest_2089, BoundaryConditionEmptyInput_2089) {

    UTF32Swp_to_UTF16Nat(utf32Input, 0, utf16Output, kBufferLength, &utf32Read, &utf16Written);



    EXPECT_EQ(utf32Read, 0);

    EXPECT_EQ(utf16Written, 0);

}



TEST_F(UnicodeConversionsTest_2089, BoundaryConditionEmptyOutput_2089) {

    utf32Input[0] = 0x0041; // 'A'



    UTF32Swp_to_UTF16Nat(utf32Input, 1, utf16Output, 0, &utf32Read, &utf16Written);



    EXPECT_EQ(utf32Read, 0);

    EXPECT_EQ(utf16Written, 0);

}



TEST_F(UnicodeConversionsTest_2089, BoundaryConditionExactFitBasic_2089) {

    utf32Input[0] = 0x0041; // 'A'



    UTF32Swp_to_UTF16Nat(utf32Input, 1, utf16Output, 1, &utf32Read, &utf16Written);



    EXPECT_EQ(utf32Read, 1);

    EXPECT_EQ(utf16Written, 1);

    EXPECT_EQ(utf16Output[0], 0x0041);

}



TEST_F(UnicodeConversionsTest_2089, BoundaryConditionExactFitSurrogatePair_2089) {

    utf32Input[0] = 0x1D11E; // Musical Symbol G Clef



    UTF32Swp_to_UTF16Nat(utf32Input, 1, utf16Output, 2, &utf32Read, &utf16Written);



    EXPECT_EQ(utf32Read, 1);

    EXPECT_EQ(utf16Written, 2);

    EXPECT_EQ(utf16Output[0], 0xD834);

    EXPECT_EQ(utf16Output[1], 0xDD1E);

}



TEST_F(UnicodeConversionsTest_2089, BoundaryConditionInsufficientOutputBufferBasic_2089) {

    utf32Input[0] = 0x0041; // 'A'

    utf32Input[1] = 0x0065; // 'e'



    UTF32Swp_to_UTF16Nat(utf32Input, 2, utf16Output, 1, &utf32Read, &utf16Written);



    EXPECT_EQ(utf32Read, 0);

    EXPECT_EQ(utf16Written, 0);

}



TEST_F(UnicodeConversionsTest_2089, BoundaryConditionInsufficientOutputBufferSurrogatePair_2089) {

    utf32Input[0] = 0x1D11E; // Musical Symbol G Clef



    UTF32Swp_to_UTF16Nat(utf32Input, 1, utf16Output, 1, &utf32Read, &utf16Written);



    EXPECT_EQ(utf32Read, 0);

    EXPECT_EQ(utf16Written, 0);

}



TEST_F(UnicodeConversionsTest_2089, ExceptionalCaseNullInputPointer_2089) {

    UTF32Swp_to_UTF16Nat(nullptr, 1, utf16Output, kBufferLength, &utf32Read, &utf16Written);



    // This case is not expected to be handled gracefully by the function as per implementation.

}



TEST_F(UnicodeConversionsTest_2089, ExceptionalCaseNullOutputPointer_2089) {

    UTF32Swp_to_UTF16Nat(utf32Input, 1, nullptr, kBufferLength, &utf32Read, &utf16Written);



    // This case is not expected to be handled gracefully by the function as per implementation.

}



TEST_F(UnicodeConversionsTest_2089, ExceptionalCaseNullCountersPointer_2089) {

    UTF32Swp_to_UTF16Nat(utf32Input, 1, utf16Output, kBufferLength, nullptr, &utf16Written);

    UTF32Swp_to_UTF16Nat(utf32Input, 1, utf16Output, kBufferLength, &utf32Read, nullptr);



    // This case is not expected to be handled gracefully by the function as per implementation.

}
