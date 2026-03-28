#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "UnicodeConversions.cpp"  // Assuming this file contains the function declaration



// Test fixture for UTF32Nat_to_UTF16Nat tests

class UnicodeConversionsTest_2075 : public ::testing::Test {

protected:

    static const size_t kMaxSize = 1024;

    UTF32Unit utf32In[kMaxSize];

    UTF16Unit utf16Out[kMaxSize];

    size_t utf32Read, utf16Written;



    void SetUp() override {

        // Initialize input and output buffers

        memset(utf32In, 0, sizeof(utf32In));

        memset(utf16Out, 0, sizeof(utf16Out));

        utf32Read = 0;

        utf16Written = 0;

    }

};



// Test normal operation with ASCII characters

TEST_F(UnicodeConversionsTest_2075, NormalOperationASCII_2075) {

    // Setup: Fill the input buffer with ASCII characters (<= 0xFFFF)

    for (size_t i = 0; i < kMaxSize; ++i) {

        utf32In[i] = static_cast<UTF32Unit>('A' + (i % 26));

    }



    // Exercise: Convert the input buffer to UTF-16

    UTF32Nat_to_UTF16Nat(utf32In, kMaxSize, utf16Out, kMaxSize, &utf32Read, &utf16Written);



    // Verify: Check that all characters are converted correctly and counts are updated

    for (size_t i = 0; i < kMaxSize; ++i) {

        EXPECT_EQ(utf16Out[i], static_cast<UTF16Unit>('A' + (i % 26)));

    }

    EXPECT_EQ(utf32Read, kMaxSize);

    EXPECT_EQ(utf16Written, kMaxSize);

}



// Test normal operation with surrogate pairs

TEST_F(UnicodeConversionsTest_2075, NormalOperationSurrogatePairs_2075) {

    // Setup: Fill the input buffer with characters that require surrogate pairs (> 0xFFFF)

    for (size_t i = 0; i < kMaxSize; ++i) {

        utf32In[i] = 0x10437; // Character in the Supplementary Multilingual Plane

    }



    // Exercise: Convert the input buffer to UTF-16

    UTF32Nat_to_UTF16Nat(utf32In, kMaxSize, utf16Out, kMaxSize * 2, &utf32Read, &utf16Written);



    // Verify: Check that all characters are converted correctly and counts are updated

    for (size_t i = 0; i < kMaxSize; ++i) {

        EXPECT_EQ(utf16Out[i*2], 0xD801);   // High surrogate

        EXPECT_EQ(utf16Out[i*2+1], 0xDC37); // Low surrogate

    }

    EXPECT_EQ(utf32Read, kMaxSize);

    EXPECT_EQ(utf16Written, kMaxSize * 2);

}



// Test boundary condition with zero-length input buffer

TEST_F(UnicodeConversionsTest_2075, ZeroLengthInputBuffer_2075) {

    // Exercise: Convert an empty input buffer to UTF-16

    UTF32Nat_to_UTF16Nat(utf32In, 0, utf16Out, kMaxSize, &utf32Read, &utf16Written);



    // Verify: Check that no characters are converted and counts are zero

    EXPECT_EQ(utf32Read, 0);

    EXPECT_EQ(utf16Written, 0);

}



// Test boundary condition with zero-length output buffer

TEST_F(UnicodeConversionsTest_2075, ZeroLengthOutputBuffer_2075) {

    // Setup: Fill the input buffer with ASCII characters (<= 0xFFFF)

    for (size_t i = 0; i < kMaxSize; ++i) {

        utf32In[i] = static_cast<UTF32Unit>('A' + (i % 26));

    }



    // Exercise: Convert the input buffer to an empty output buffer

    UTF32Nat_to_UTF16Nat(utf32In, kMaxSize, utf16Out, 0, &utf32Read, &utf16Written);



    // Verify: Check that no characters are converted and counts reflect this

    EXPECT_EQ(utf32Read, 0);

    EXPECT_EQ(utf16Written, 0);

}



// Test boundary condition with partial output buffer (surrogate pairs)

TEST_F(UnicodeConversionsTest_2075, PartialOutputBufferSurrogates_2075) {

    // Setup: Fill the input buffer with characters that require surrogate pairs (> 0xFFFF)

    for (size_t i = 0; i < kMaxSize; ++i) {

        utf32In[i] = 0x10437; // Character in the Supplementary Multilingual Plane

    }



    // Exercise: Convert the input buffer to a partially filled output buffer

    UTF32Nat_to_UTF16Nat(utf32In, kMaxSize, utf16Out, (kMaxSize * 2) - 1, &utf32Read, &utf16Written);



    // Verify: Check that as many characters as possible are converted and counts reflect this

    EXPECT_EQ(utf32Read, kMaxSize - 1);

    EXPECT_EQ(utf16Written, (kMaxSize * 2) - 2);

}



// Test exceptional case with invalid UTF-32 input

TEST_F(UnicodeConversionsTest_2075, InvalidUTF32Input_2075) {

    // Setup: Fill the input buffer with an invalid UTF-32 character (e.g., surrogate range)

    utf32In[0] = 0xD801; // High surrogate in UTF-16



    // Exercise: Convert the input buffer to UTF-16

    UTF32Nat_to_UTF16Nat(utf32In, 1, utf16Out, kMaxSize, &utf32Read, &utf16Written);



    // Verify: Check that no characters are converted and counts reflect this

    EXPECT_EQ(utf32Read, 0);

    EXPECT_EQ(utf16Written, 0);

}
