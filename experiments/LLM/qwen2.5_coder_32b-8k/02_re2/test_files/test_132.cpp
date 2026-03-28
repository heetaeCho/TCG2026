#include <gtest/gtest.h>

#include "re2/prog.h"

#include <string>



using namespace re2;



class ProgTest_132 : public ::testing::Test {

protected:

    Prog prog;

};



TEST_F(ProgTest_132, IsWordChar_LowercaseLetter_132) {

    EXPECT_TRUE(Prog::IsWordChar('a'));

}



TEST_F(ProgTest_132, IsWordChar_UppercaseLetter_132) {

    EXPECT_TRUE(Prog::IsWordChar('Z'));

}



TEST_F(ProgTest_132, IsWordChar_Digit_132) {

    EXPECT_TRUE(Prog::IsWordChar('5'));

}



TEST_F(ProgTest_132, IsWordChar_Underscore_132) {

    EXPECT_TRUE(Prog::IsWordChar('_'));

}



TEST_F(ProgTest_132, IsWordChar_SpecialCharacter_132) {

    EXPECT_FALSE(Prog::IsWordChar('$'));

}



TEST_F(ProgTest_132, IsWordChar_Space_132) {

    EXPECT_FALSE(Prog::IsWordChar(' '));

}



TEST_F(ProgTest_132, IsWordChar_BoundaryCondition_LowerBound_132) {

    EXPECT_FALSE(Prog::IsWordChar('@'));

}



TEST_F(ProgTest_132, IsWordChar_BoundaryCondition_UpperBound_132) {

    EXPECT_FALSE(Prog::IsWordChar('['));

}
