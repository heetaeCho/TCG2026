#include <gtest/gtest.h>

#include "regexp.h"



using namespace re2;



class CharClassTest_377 : public ::testing::Test {

protected:

    void SetUp() override {

        charClass = CharClass::New(10);

    }



    void TearDown() override {

        if (charClass) {

            charClass->Delete();

            charClass = nullptr;

        }

    }



    CharClass* charClass;

};



TEST_F(CharClassTest_377, NewCharClassNotNull_377) {

    EXPECT_NE(charClass, nullptr);

}



TEST_F(CharClassTest_377, DeleteDoesNotCrash_377) {

    charClass->Delete();

    charClass = nullptr;  // To prevent double deletion in TearDown

}



TEST_F(CharClassTest_377, ContainsReturnsFalseForEmptyCharClass_377) {

    EXPECT_FALSE(charClass->Contains(0));

}



TEST_F(CharClassTest_377, NegateCreatesNewInstance_377) {

    CharClass* negated = charClass->Negate();

    EXPECT_NE(negated, nullptr);

    negated->Delete();  // Clean up the negated instance

}



TEST_F(CharClassTest_377, SizeIsZeroForEmptyCharClass_377) {

    EXPECT_EQ(charClass->size(), 0);

}



TEST_F(CharClassTest_377, EmptyReturnsTrueForNewCharClass_377) {

    EXPECT_TRUE(charClass->empty());

}



TEST_F(CharClassTest_377, FullReturnsFalseForEmptyCharClass_377) {

    EXPECT_FALSE(charClass->full());

}



TEST_F(CharClassTest_377, FoldsASCIIReturnsDefaultConstructedValue_377) {

    // Assuming folds_ascii_ is false by default since it's not modified in the provided interface

    EXPECT_FALSE(charClass->FoldsASCII());

}



// Boundary and exceptional cases are not directly testable with the given interface,

// as there's no way to modify the state of the CharClass object or observe its internal state.
