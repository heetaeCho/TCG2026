#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "elide_middle.cc"  // Assuming this is the correct include path for the struct definitions



using namespace testing;



class VisibleInputCharsIteratorTest_106 : public Test {

protected:

    std::string input;

    VisibleInputCharsIterator* iterator;



    void SetUp() override {

        input = "\x1b[31mHello\x1b[0mWorld";

        iterator = new VisibleInputCharsIterator(input);

    }



    void TearDown() override {

        delete iterator;

    }

};



TEST_F(VisibleInputCharsIteratorTest_106, InitialStateHasChar_106) {

    EXPECT_TRUE(iterator->HasChar());

}



TEST_F(VisibleInputCharsIteratorTest_106, InitialStateIndices_106) {

    EXPECT_EQ(iterator->InputIndex(), 0);

    EXPECT_EQ(iterator->VisiblePosition(), 0);

}



TEST_F(VisibleInputCharsIteratorTest_106, NextCharAdvancesIndicesNormalOperation_106) {

    iterator->NextChar();

    EXPECT_EQ(iterator->InputIndex(), 1);

    EXPECT_EQ(iterator->VisiblePosition(), 0);



    for (int i = 1; i < input.size(); ++i) {

        iterator->NextChar();

    }

    EXPECT_EQ(iterator->InputIndex(), input.size());

}



TEST_F(VisibleInputCharsIteratorTest_106, NextCharHandlesAnsiEscapeCodes_106) {

    // Move through the escape code

    for (int i = 0; i < 5; ++i) {

        iterator->NextChar();

        EXPECT_EQ(iterator->VisiblePosition(), 0);

    }



    // Move through "Hello"

    for (int i = 0; i < 5; ++i) {

        iterator->NextChar();

        EXPECT_EQ(iterator->VisiblePosition(), i + 1);

    }



    // Move through the reset code

    for (int i = 0; i < 4; ++i) {

        iterator->NextChar();

        EXPECT_EQ(iterator->VisiblePosition(), 5);

    }



    // Move through "World"

    for (int i = 0; i < 5; ++i) {

        iterator->NextChar();

        EXPECT_EQ(iterator->VisiblePosition(), i + 6);

    }

}



TEST_F(VisibleInputCharsIteratorTest_106, NextCharAtEndDoesNotAdvanceIndices_106) {

    for (int i = 0; i < input.size(); ++i) {

        iterator->NextChar();

    }



    EXPECT_EQ(iterator->InputIndex(), input.size());

    iterator->NextChar();

    EXPECT_EQ(iterator->InputIndex(), input.size());

}



TEST_F(VisibleInputCharsIteratorTest_106, NoVisibleCharactersInAnsiSequence_106) {

    std::string ansiOnly = "\x1b[31m\x1b[0m";

    VisibleInputCharsIterator ansiIterator(ansiOnly);



    EXPECT_FALSE(ansiIterator.IsVisible());

    ansiIterator.NextChar();

    EXPECT_FALSE(ansiIterator.IsVisible());



    for (int i = 0; i < ansiOnly.size(); ++i) {

        ansiIterator.NextChar();

        EXPECT_FALSE(ansiIterator.IsVisible());

    }

}



TEST_F(VisibleInputCharsIteratorTest_106, BoundaryConditionEmptyString_106) {

    std::string empty;

    VisibleInputCharsIterator emptyIterator(empty);



    EXPECT_FALSE(emptyIterator.HasChar());

    EXPECT_EQ(emptyIterator.InputIndex(), 0);

    EXPECT_EQ(emptyIterator.VisiblePosition(), 0);

}



TEST_F(VisibleInputCharsIteratorTest_106, BoundaryConditionSingleVisibleChar_106) {

    std::string singleChar = "A";

    VisibleInputCharsIterator singleCharIterator(singleChar);



    EXPECT_TRUE(singleCharIterator.HasChar());

    EXPECT_EQ(singleCharIterator.InputIndex(), 0);

    EXPECT_EQ(singleCharIterator.VisiblePosition(), 0);



    singleCharIterator.NextChar();



    EXPECT_FALSE(singleCharIterator.HasChar());

    EXPECT_EQ(singleCharIterator.InputIndex(), 1);

    EXPECT_EQ(singleCharIterator.VisiblePosition(), 1);

}



TEST_F(VisibleInputCharsIteratorTest_106, BoundaryConditionSingleAnsiSequence_106) {

    std::string singleAnsi = "\x1b[31m";

    VisibleInputCharsIterator ansiIterator(singleAnsi);



    for (int i = 0; i < singleAnsi.size(); ++i) {

        EXPECT_FALSE(ansiIterator.IsVisible());

        ansiIterator.NextChar();

    }



    EXPECT_FALSE(ansiIterator.HasChar());

}



TEST_F(VisibleInputCharsIteratorTest_106, BoundaryConditionMixedSequenceEnds_106) {

    std::string mixed = "\x1b[31mHello\x1b[0m";

    VisibleInputCharsIterator mixedIterator(mixed);



    for (int i = 0; i < mixed.size(); ++i) {

        mixedIterator.NextChar();

    }



    EXPECT_FALSE(mixedIterator.HasChar());

}
