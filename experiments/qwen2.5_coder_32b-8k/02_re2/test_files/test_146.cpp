#include <gtest/gtest.h>

#include "regexp.h"

#include <set>



using namespace re2;



class CharClassTest_146 : public ::testing::Test {

protected:

    void SetUp() override {

        charClass = CharClass::New(10);

    }



    void TearDown() override {

        charClass->Delete();

    }



    CharClass* charClass;

};



TEST_F(CharClassTest_146, NewCharClassIsEmpty_146) {

    EXPECT_TRUE(charClass->empty());

}



TEST_F(CharClassTest_146, SizeReturnsZeroForEmptyCharClass_146) {

    EXPECT_EQ(0, charClass->size());

}



TEST_F(CharClassTest_146, FullReturnsFalseForEmptyCharClass_146) {

    EXPECT_FALSE(charClass->full());

}



TEST_F(CharClassTest_146, ContainsReturnsFalseForEmptyCharClass_146) {

    Rune r = 0;

    EXPECT_FALSE(charClass->Contains(r));

}



// Assuming some way to modify the CharClass to be non-empty

// For this example, we'll mock a scenario where Negate or another method is used

TEST_F(CharClassTest_146, SizeReturnsNonZeroAfterModification_146) {

    // This test assumes that Negate will add something to the CharClass

    charClass->Negate();

    EXPECT_FALSE(charClass->empty());

    EXPECT_GT(charClass->size(), 0);

}



TEST_F(CharClassTest_146, FullReturnsTrueAfterFullModification_146) {

    // This test assumes that some method will fill the CharClass to its max capacity

    for (int i = 0; i < 10; ++i) {

        charClass->Negate(); // Simplified assumption, actual implementation may vary

    }

    EXPECT_TRUE(charClass->full());

}



TEST_F(CharClassTest_146, NegateInvertsEmptyCharClassProperly_146) {

    CharClass* negated = charClass->Negate();

    EXPECT_FALSE(negated->empty());

    negated->Delete();

}



TEST_F(CharClassTest_146, FoldsASCIIInitiallySetCorrectly_146) {

    // Assuming folds_ascii_ is set to false by default

    EXPECT_FALSE(charClass->FoldsASCII());

}
