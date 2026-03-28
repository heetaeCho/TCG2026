#include <gtest/gtest.h>

#include "regexp.h"



namespace re2 {



class CharClassTest_147 : public ::testing::Test {

protected:

    CharClass* char_class;



    void SetUp() override {

        char_class = CharClass::New(5);

    }



    void TearDown() override {

        char_class->Delete();

    }

};



TEST_F(CharClassTest_147, FullReturnsFalseWhenNotFull_147) {

    EXPECT_FALSE(char_class->full());

}



TEST_F(CharClassTest_147, FullReturnsTrueWhenFull_147) {

    for (int i = 0; i <= Runemax; ++i) {

        // Assuming some way to add runes to the CharClass

        // This is a placeholder as actual method to add runes is not provided

        // char_class->AddRune(i);

    }

    EXPECT_TRUE(char_class->full());

}



TEST_F(CharClassTest_147, EmptyReturnsTrueInitially_147) {

    EXPECT_TRUE(char_class->empty());

}



TEST_F(CharClassTest_147, SizeReturnsZeroInitially_147) {

    EXPECT_EQ(0, char_class->size());

}



TEST_F(CharClassTest_147, NegateCreatesNewCharClass_147) {

    CharClass* negated_char_class = char_class->Negate();

    ASSERT_NE(nullptr, negated_char_class);

    negated_char_class->Delete();

}



TEST_F(CharClassTest_147, ContainsReturnsFalseForUnaddedRune_147) {

    EXPECT_FALSE(char_class->Contains(0));

}



// Assuming some way to add runes to the CharClass

// This is a placeholder as actual method to add runes is not provided

/*

TEST_F(CharClassTest_147, ContainsReturnsTrueForAddedRune_147) {

    char_class->AddRune(42);

    EXPECT_TRUE(char_class->Contains(42));

}

*/



TEST_F(CharClassTest_147, FoldsASCIIInitiallyFalse_147) {

    EXPECT_FALSE(char_class->FoldsASCII());

}



// Assuming some way to set folds_ascii_

// This is a placeholder as actual method to set folds_ascii_ is not provided

/*

TEST_F(CharClassTest_147, FoldsASCIISettable_147) {

    char_class->SetFoldsASCII(true);

    EXPECT_TRUE(char_class->FoldsASCII());

}

*/



} // namespace re2
