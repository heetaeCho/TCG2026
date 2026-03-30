#include <gtest/gtest.h>



// Assuming XMP_Uns32 is defined as an unsigned 32-bit integer

typedef uint32_t XMP_Uns32;



extern bool IsStartChar_NonASCII(XMP_Uns32 cp);



class UnicodeInlinesTest_1876 : public ::testing::Test {

protected:

    void SetUp() override {

        // Set up any common state before tests (if needed)

    }



    void TearDown() override {

        // Clean up any common state after tests (if needed)

    }

};



// Normal operation

TEST_F(UnicodeInlinesTest_1876, IsStartChar_NonASCII_ReturnsTrueForValidStartChars_1876) {

    EXPECT_TRUE(IsStartChar_NonASCII(0xC0));

    EXPECT_TRUE(IsStartChar_NonASCII(0xD6));

    EXPECT_TRUE(IsStartChar_NonASCII(0xF8));

    EXPECT_TRUE(IsStartChar_NonASCII(0x2FF));

    EXPECT_TRUE(IsStartChar_NonASCII(0x370));

    EXPECT_TRUE(IsStartChar_NonASCII(0x37D));

    EXPECT_TRUE(IsStartChar_NonASCII(0x37F));

    EXPECT_TRUE(IsStartChar_NonASCII(0x1FFF));

    EXPECT_TRUE(IsStartChar_NonASCII(0x200C));

    EXPECT_TRUE(IsStartChar_NonASCII(0x200D));

    EXPECT_TRUE(IsStartChar_NonASCII(0x2070));

    EXPECT_TRUE(IsStartChar_NonASCII(0x218F));

    EXPECT_TRUE(IsStartChar_NonASCII(0x2C00));

    EXPECT_TRUE(IsStartChar_NonASCII(0x2FEF));

    EXPECT_TRUE(IsStartChar_NonASCII(0x3001));

    EXPECT_TRUE(IsStartChar_NonASCII(0xD7FF));

    EXPECT_TRUE(IsStartChar_NonASCII(0xF900));

    EXPECT_TRUE(IsStartChar_NonASCII(0xFDCF));

    EXPECT_TRUE(IsStartChar_NonASCII(0xFDF0));

    EXPECT_TRUE(IsStartChar_NonASCII(0xFFFD));

    EXPECT_TRUE(IsStartChar_NonASCII(0x10000));

    EXPECT_TRUE(IsStartChar_NonASCII(0xEFFFF));

}



// Boundary conditions

TEST_F(UnicodeInlinesTest_1876, IsStartChar_NonASCII_ReturnsTrueForBoundaryValues_1876) {

    EXPECT_TRUE(IsStartChar_NonASCII(0xC0));

    EXPECT_TRUE(IsStartChar_NonASCII(0xD6));

    EXPECT_TRUE(IsStartChar_NonASCII(0xF8));

    EXPECT_TRUE(IsStartChar_NonASCII(0x2FF));

    EXPECT_TRUE(IsStartChar_NonASCII(0x370));

    EXPECT_TRUE(IsStartChar_NonASCII(0x37D));

    EXPECT_TRUE(IsStartChar_NonASCII(0x37F));

    EXPECT_TRUE(IsStartChar_NonASCII(0x1FFF));

    EXPECT_TRUE(IsStartChar_NonASCII(0x200C));

    EXPECT_TRUE(IsStartChar_NonASCII(0x200D));

    EXPECT_TRUE(IsStartChar_NonASCII(0x2070));

    EXPECT_TRUE(IsStartChar_NonASCII(0x218F));

    EXPECT_TRUE(IsStartChar_NonASCII(0x2C00));

    EXPECT_TRUE(IsStartChar_NonASCII(0x2FEF));

    EXPECT_TRUE(IsStartChar_NonASCII(0x3001));

    EXPECT_TRUE(IsStartChar_NonASCII(0xD7FF));

    EXPECT_TRUE(IsStartChar_NonASCII(0xF900));

    EXPECT_TRUE(IsStartChar_NonASCII(0xFDCF));

    EXPECT_TRUE(IsStartChar_NonASCII(0xFDF0));

    EXPECT_TRUE(IsStartChar_NonASCII(0xFFFD));

    EXPECT_TRUE(IsStartChar_NonASCII(0x10000));

    EXPECT_TRUE(IsStartChar_NonASCII(0xEFFFF));

}



// Normal operation

TEST_F(UnicodeInlinesTest_1876, IsStartChar_NonASCII_ReturnsFalseForInvalidStartChars_1876) {

    EXPECT_FALSE(IsStartChar_NonASCII(0x00));

    EXPECT_FALSE(IsStartChar_NonASCII(0xBF));

    EXPECT_FALSE(IsStartChar_NonASCII(0xF7));

    EXPECT_FALSE(IsStartChar_NonASCII(0x300));

    EXPECT_FALSE(IsStartChar_NonASCII(0xD800));

    EXPECT_FALSE(IsStartChar_NonASCII(0xEFFF));

    EXPECT_FALSE(IsStartChar_NonASCII(0xFDD0));

    EXPECT_FALSE(IsStartChar_NonASCII(0x110000));

}



// Boundary conditions

TEST_F(UnicodeInlinesTest_1876, IsStartChar_NonASCII_ReturnsFalseForOutofRangeValues_1876) {

    EXPECT_FALSE(IsStartChar_NonASCII(0x00));

    EXPECT_FALSE(IsStartChar_NonASCII(0xBF));

    EXPECT_FALSE(IsStartChar_NonASCII(0xF7));

    EXPECT_FALSE(IsStartChar_NonASCII(0x300));

    EXPECT_FALSE(IsStartChar_NonASCII(0xD800));

    EXPECT_FALSE(IsStartChar_NonASCII(0xEFFF));

    EXPECT_FALSE(IsStartChar_NonASCII(0xFDD0));

    EXPECT_FALSE(IsStartChar_NonASCII(0x110000));

}
