#include <gtest/gtest.h>

#include "re2/regexp.h"



namespace re2 {



class CharClassTest_145 : public ::testing::Test {

protected:

    void SetUp() override {

        charClass = CharClass::New(10);

    }



    void TearDown() override {

        charClass->Delete();

    }



    CharClass* charClass;

};



TEST_F(CharClassTest_145, Size_ReturnsCorrectValue_145) {

    // Assuming the size is initialized to 0

    EXPECT_EQ(charClass->size(), 0);

}



TEST_F(CharClassTest_145, Empty_ReturnsTrueForEmptyCharClass_145) {

    EXPECT_TRUE(charClass->empty());

}



TEST_F(CharClassTest_145, Full_ReturnsFalseForEmptyCharClass_145) {

    EXPECT_FALSE(charClass->full());

}



TEST_F(CharClassTest_145, FoldsASCII_ReturnsCorrectValue_145) {

    // Assuming folds_ascii_ is initialized to false

    EXPECT_FALSE(charClass->FoldsASCII());

}



TEST_F(CharClassTest_145, Negate_ReturnsNewCharClassInstance_145) {

    CharClass* negated = charClass->Negate();

    ASSERT_NE(negated, nullptr);

    negated->Delete(); // Clean up the negated instance

}



TEST_F(CharClassTest_145, BeginEnd_IteratorsAreConsistent_145) {

    auto start = charClass->begin();

    auto end = charClass->end();

    EXPECT_EQ(start, end); // Initially empty, begin and end should be equal

}



TEST_F(CharClassTest_145, Contains_ReturnsFalseForNonContainedRune_145) {

    Rune r = 97; // Example rune 'a'

    EXPECT_FALSE(charClass->Contains(r));

}



// Assuming there's a way to add runes to CharClass for more comprehensive testing

// Since we can't modify the class, this is a theoretical test case

/*

TEST_F(CharClassTest_145, Contains_ReturnsTrueForContainedRune_145) {

    // Add rune 'a' to charClass

    Rune r = 97; // Example rune 'a'

    EXPECT_TRUE(charClass->Contains(r));

}

*/



} // namespace re2
