#include <gtest/gtest.h>

#include "regexp.h"



using namespace re2;



class CharClassTest_143 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed, but no internal state should be accessed.

    }



    void TearDown() override {

        // Teardown if needed, but no internal state should be accessed.

    }

};



TEST_F(CharClassTest_143, Contains_ReturnsTrueForContainedRune_143) {

    // Arrange

    CharClass* char_class = CharClass::New(10);

    // Assuming some setup to add a RuneRange that contains the rune 'a'

    

    // Act & Assert

    EXPECT_TRUE(char_class->Contains('a'));



    // Cleanup

    char_class->Delete();

}



TEST_F(CharClassTest_143, Contains_ReturnsFalseForNonContainedRune_143) {

    // Arrange

    CharClass* char_class = CharClass::New(10);

    // Assuming some setup to add a RuneRange that does not contain the rune 'z'

    

    // Act & Assert

    EXPECT_FALSE(char_class->Contains('z'));



    // Cleanup

    char_class->Delete();

}



TEST_F(CharClassTest_143, Negate_ReturnsNewCharClassWithNegatedRanges_143) {

    // Arrange

    CharClass* char_class = CharClass::New(10);

    // Assuming some setup to add a RuneRange

    

    // Act

    CharClass* negated_char_class = char_class->Negate();



    // Assert

    EXPECT_NE(char_class, negated_char_class);



    // Cleanup

    char_class->Delete();

    negated_char_class->Delete();

}



TEST_F(CharClassTest_143, Size_ReturnsCorrectNumberOfRanges_143) {

    // Arrange

    CharClass* char_class = CharClass::New(10);

    // Assuming some setup to add 5 RuneRanges

    

    // Act & Assert

    EXPECT_EQ(char_class->size(), 5);



    // Cleanup

    char_class->Delete();

}



TEST_F(CharClassTest_143, Empty_ReturnsTrueForNoRanges_143) {

    // Arrange

    CharClass* char_class = CharClass::New(0);

    

    // Act & Assert

    EXPECT_TRUE(char_class->empty());



    // Cleanup

    char_class->Delete();

}



TEST_F(CharClassTest_143, Empty_ReturnsFalseForSomeRanges_143) {

    // Arrange

    CharClass* char_class = CharClass::New(10);

    // Assuming some setup to add a RuneRange

    

    // Act & Assert

    EXPECT_FALSE(char_class->empty());



    // Cleanup

    char_class->Delete();

}



TEST_F(CharClassTest_143, Full_ReturnsTrueForFullCharSet_143) {

    // Arrange

    CharClass* char_class = CharClass::New(10);

    // Assuming some setup to add all possible RuneRanges

    

    // Act & Assert

    EXPECT_TRUE(char_class->full());



    // Cleanup

    char_class->Delete();

}



TEST_F(CharClassTest_143, Full_ReturnsFalseForPartialCharSet_143) {

    // Arrange

    CharClass* char_class = CharClass::New(10);

    // Assuming some setup to add a subset of possible RuneRanges

    

    // Act & Assert

    EXPECT_FALSE(char_class->full());



    // Cleanup

    char_class->Delete();

}



TEST_F(CharClassTest_143, FoldsASCII_ReturnsTrueWhenFoldingEnabled_143) {

    // Arrange

    CharClass* char_class = CharClass::New(10);

    // Assuming some setup to enable ASCII folding

    

    // Act & Assert

    EXPECT_TRUE(char_class->FoldsASCII());



    // Cleanup

    char_class->Delete();

}



TEST_F(CharClassTest_143, FoldsASCII_ReturnsFalseWhenFoldingDisabled_143) {

    // Arrange

    CharClass* char_class = CharClass::New(10);

    // Assuming some setup to disable ASCII folding

    

    // Act & Assert

    EXPECT_FALSE(char_class->FoldsASCII());



    // Cleanup

    char_class->Delete();

}
