#include <gtest/gtest.h>

#include <re2/prefilter.cc>  // Adjust include path as necessary



using namespace re2;



// Test fixture for ToLowerRuneLatin1 function

class ToLowerRuneLatin1Test : public ::testing::Test {

protected:

    // You can add setup code here if needed

};



TEST_F(ToLowerRuneLatin1Test, NormalOperation_538) {

    EXPECT_EQ('a', ToLowerRuneLatin1('A'));

    EXPECT_EQ('b', ToLowerRuneLatin1('B'));

    EXPECT_EQ('z', ToLowerRuneLatin1('Z'));

}



TEST_F(ToLowerRuneLatin1Test, BoundaryConditions_538) {

    EXPECT_EQ('A', ToLowerRuneLatin1('A'));  // Edge case: already lower

    EXPECT_EQ('Z', ToLowerRuneLatin1('Z'));  // Edge case: already upper

    EXPECT_EQ('a' - 'A' + '@', ToLowerRuneLatin1('@'));  // Just below 'A'

    EXPECT_EQ('z' + 1, ToLowerRuneLatin1('['));  // Just above 'Z'

}



TEST_F(ToLowerRuneLatin1Test, NonAlphabetCharacters_538) {

    EXPECT_EQ('0', ToLowerRuneLatin1('0'));  // Digit

    EXPECT_EQ(' ', ToLowerRuneLatin1(' '));  // Space

    EXPECT_EQ('_', ToLowerRuneLatin1('_'));  // Special character

}



TEST_F(ToLowerRuneLatin1Test, LowerCaseInput_538) {

    EXPECT_EQ('a', ToLowerRuneLatin1('a'));

    EXPECT_EQ('m', ToLowerRuneLatin1('m'));

    EXPECT_EQ('z', ToLowerRuneLatin1('z'));

}
