#include <gtest/gtest.h>

#include "regexp.h"



using namespace re2;



class CharClassTest_379 : public ::testing::Test {

protected:

    void SetUp() override {

        // Assuming there's a way to create a CharClass instance with known ranges.

        // Since we can't instantiate directly, this is a placeholder for setup if needed.

    }



    void TearDown() override {

        // Clean up if necessary

    }

};



TEST_F(CharClassTest_379, Contains_ReturnsTrueForInRangeValue_379) {

    RuneRange range(10, 20);

    CharClass* charClass = CharClass::New(1);

    charClass->ranges_[0] = range;

    charClass->nranges_ = 1;



    EXPECT_TRUE(charClass->Contains(15));



    charClass->Delete();

}



TEST_F(CharClassTest_379, Contains_ReturnsFalseForOutOfRangeValue_379) {

    RuneRange range(10, 20);

    CharClass* charClass = CharClass::New(1);

    charClass->ranges_[0] = range;

    charClass->nranges_ = 1;



    EXPECT_FALSE(charClass->Contains(5));

    EXPECT_FALSE(charClass->Contains(25));



    charClass->Delete();

}



TEST_F(CharClassTest_379, Contains_ReturnsTrueForBoundaryValue_379) {

    RuneRange range(10, 20);

    CharClass* charClass = CharClass::New(1);

    charClass->ranges_[0] = range;

    charClass->nranges_ = 1;



    EXPECT_TRUE(charClass->Contains(10));

    EXPECT_TRUE(charClass->Contains(20));



    charClass->Delete();

}



TEST_F(CharClassTest_379, Contains_ReturnsFalseForEmptyRange_379) {

    CharClass* charClass = CharClass::New(0);

    charClass->nranges_ = 0;



    EXPECT_FALSE(charClass->Contains(15));



    charClass->Delete();

}



TEST_F(CharClassTest_379, Contains_ReturnsTrueForMultipleRanges_379) {

    RuneRange range1(10, 20);

    RuneRange range2(30, 40);

    CharClass* charClass = CharClass::New(2);

    charClass->ranges_[0] = range1;

    charClass->ranges_[1] = range2;

    charClass->nranges_ = 2;



    EXPECT_TRUE(charClass->Contains(15));

    EXPECT_TRUE(charClass->Contains(35));



    charClass->Delete();

}



TEST_F(CharClassTest_379, Contains_ReturnsFalseForValueBetweenRanges_379) {

    RuneRange range1(10, 20);

    RuneRange range2(30, 40);

    CharClass* charClass = CharClass::New(2);

    charClass->ranges_[0] = range1;

    charClass->ranges_[1] = range2;

    charClass->nranges_ = 2;



    EXPECT_FALSE(charClass->Contains(25));



    charClass->Delete();

}
