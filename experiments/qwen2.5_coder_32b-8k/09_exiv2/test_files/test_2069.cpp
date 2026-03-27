#include <gtest/gtest.h>

#include "UnicodeConversions.cpp" // Assuming the function is in this file



// Test fixture for CodePoint_from_UTF16Nat tests

class CodePointFromUTF16NatTest_2069 : public ::testing::Test {

protected:

    UTF16Unit utf16In[4];

    UTF32Unit cpOut;

    size_t utf16Read;



    void SetUp() override {

        // Initialize variables before each test

        utf16In[0] = 0; // Reset input buffer

        cpOut = 0;      // Reset output code point

        utf16Read = 0;  // Reset number of units read

    }

};



// Test normal operation with a Basic Multilingual Plane (BMP) character

TEST_F(CodePointFromUTF16NatTest_2069, NormalOperation_BMP_2069) {

    utf16In[0] = 0x041F; // Cyrillic capital letter 'П'

    CodePoint_from_UTF16Nat(utf16In, 1, &cpOut, &utf16Read);

    EXPECT_EQ(cpOut, 0x041F);

    EXPECT_EQ(utf16Read, 1);

}



// Test normal operation with a character outside BMP (surrogate pair)

TEST_F(CodePointFromUTF16NatTest_2069, NormalOperation_SurrogatePair_2069) {

    utf16In[0] = 0xD834; // High surrogate

    utf16In[1] = 0xDD1E; // Low surrogate (musical symbol G clef)

    CodePoint_from_UTF16Nat(utf16In, 2, &cpOut, &utf16Read);

    EXPECT_EQ(cpOut, 0x1D11E);

    EXPECT_EQ(utf16Read, 2);

}



// Test boundary condition with empty input

TEST_F(CodePointFromUTF16NatTest_2069, BoundaryCondition_EmptyInput_2069) {

    CodePoint_from_UTF16Nat(utf16In, 0, &cpOut, &utf16Read);

    EXPECT_EQ(cpOut, 0);

    EXPECT_EQ(utf16Read, 0);

}



// Test boundary condition with single high surrogate

TEST_F(CodePointFromUTF16NatTest_2069, BoundaryCondition_SingleHighSurrogate_2069) {

    utf16In[0] = 0xD834; // High surrogate without pair

    CodePoint_from_UTF16Nat(utf16In, 1, &cpOut, &utf16Read);

    EXPECT_EQ(cpOut, 0); // Expect no valid code point

    EXPECT_EQ(utf16Read, 1); // Only one unit read

}



// Test boundary condition with single low surrogate

TEST_F(CodePointFromUTF16NatTest_2069, BoundaryCondition_SingleLowSurrogate_2069) {

    utf16In[0] = 0xDD1E; // Low surrogate without pair

    CodePoint_from_UTF16Nat(utf16In, 1, &cpOut, &utf16Read);

    EXPECT_EQ(cpOut, 0); // Expect no valid code point

    EXPECT_EQ(utf16Read, 1); // Only one unit read

}
