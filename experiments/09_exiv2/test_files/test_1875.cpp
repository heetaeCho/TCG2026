#include <gtest/gtest.h>



// Assuming XMP_Uns32 is defined as an unsigned 32-bit integer

using XMP_Uns32 = uint32_t;



// Function signature to be tested

extern "C" bool IsStartChar_ASCII(XMP_Uns32 cp);



class UnicodeInlinesTest_1875 : public ::testing::Test {

protected:

    // No setup or teardown needed for this function

};



TEST_F(UnicodeInlinesTest_1875, LowercaseAlphabetStartChar_1875) {

    EXPECT_TRUE(IsStartChar_ASCII('a'));

    EXPECT_TRUE(IsStartChar_ASCII('m'));

    EXPECT_TRUE(IsStartChar_ASCII('z'));

}



TEST_F(UnicodeInlinesTest_1875, UppercaseAlphabetStartChar_1875) {

    EXPECT_TRUE(IsStartChar_ASCII('A'));

    EXPECT_TRUE(IsStartChar_ASCII('M'));

    EXPECT_TRUE(IsStartChar_ASCII('Z'));

}



TEST_F(UnicodeInlinesTest_1875, UnderscoreStartChar_1875) {

    EXPECT_TRUE(IsStartChar_ASCII('_'));

}



TEST_F(UnicodeInlinesTest_1875, NonStartCharOutsideAlphabetRange_1875) {

    EXPECT_FALSE(IsStartChar_ASCII('0'));

    EXPECT_FALSE(IsStartChar_ASCII('@'));

    EXPECT_FALSE(IsStartChar_ASCII('['));

}



TEST_F(UnicodeInlinesTest_1875, NonStartCharInsideAlphabetRangeButNotAlphabet_1875) {

    EXPECT_FALSE(IsStartChar_ASCII('`')); // Just before 'a'

    EXPECT_FALSE(IsStartChar_ASCII('{')); // Just after 'z'

    EXPECT_FALSE(IsStartChar_ASCII('[')); // Just after 'Z'

}



TEST_F(UnicodeInlinesTest_1875, BoundaryConditionLowercaseA_1875) {

    EXPECT_TRUE(IsStartChar_ASCII('a'));

}



TEST_F(UnicodeInlinesTest_1875, BoundaryConditionUppercaseA_1875) {

    EXPECT_TRUE(IsStartChar_ASCII('A'));

}



TEST_F(UnicodeInlinesTest_1875, BoundaryConditionLowercaseZ_1875) {

    EXPECT_TRUE(IsStartChar_ASCII('z'));

}



TEST_F(UnicodeInlinesTest_1875, BoundaryConditionUppercaseZ_1875) {

    EXPECT_TRUE(IsStartChar_ASCII('Z'));

}
