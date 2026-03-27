#include <gtest/gtest.h>

#include "regexp.h"



using namespace re2;



class CharClassBuilderTest_372 : public ::testing::Test {

protected:

    void SetUp() override {

        charClassBuilder = new CharClassBuilder();

    }



    void TearDown() override {

        delete charClassBuilder;

    }



    CharClassBuilder* charClassBuilder;

};



TEST_F(CharClassBuilderTest_372, AddRange_SingleRune_372) {

    Rune lo = 65; // 'A'

    Rune hi = 65; // 'A'

    charClassBuilder->AddRange(lo, hi);

    EXPECT_TRUE(charClassBuilder->Contains(65));

}



TEST_F(CharClassBuilderTest_372, AddRange_RangeOfRunes_372) {

    Rune lo = 97; // 'a'

    Rune hi = 102; // 'f'

    charClassBuilder->AddRange(lo, hi);

    EXPECT_TRUE(charClassBuilder->Contains(98)); // 'b'

    EXPECT_FALSE(charClassBuilder->Contains(65)); // 'A'

}



TEST_F(CharClassBuilderTest_372, AddRange_EmptyRange_372) {

    Rune lo = 100; // 'd'

    Rune hi = 99; // 'c' (invalid range)

    charClassBuilder->AddRange(lo, hi);

    EXPECT_FALSE(charClassBuilder->Contains(100)); // 'd'

}



TEST_F(CharClassBuilderTest_372, AddRangeFlags_DefaultFlags_372) {

    Rune lo = 65; // 'A'

    Rune hi = 90; // 'Z'

    Regexp::ParseFlags flags = 0;

    charClassBuilder->AddRangeFlags(lo, hi, flags);

    EXPECT_TRUE(charClassBuilder->Contains(65)); // 'A'

    EXPECT_TRUE(charClassBuilder->Contains(90)); // 'Z'

}



TEST_F(CharClassBuilderTest_372, Contains_OutOfRange_372) {

    Rune lo = 104; // 'h'

    Rune hi = 108; // 'l'

    charClassBuilder->AddRange(lo, hi);

    EXPECT_FALSE(charClassBuilder->Contains(109)); // 'm'

}



TEST_F(CharClassBuilderTest_372, Negate_EmptySet_372) {

    charClassBuilder->Negate();

    EXPECT_TRUE(charClassBuilder->full());

}



TEST_F(CharClassBuilderTest_372, Negate_NonEmptySet_372) {

    Rune lo = 65; // 'A'

    Rune hi = 90; // 'Z'

    charClassBuilder->AddRange(lo, hi);

    charClassBuilder->Negate();

    EXPECT_TRUE(charClassBuilder->Contains(91)); // '['

    EXPECT_FALSE(charClassBuilder->Contains(65)); // 'A'

}



TEST_F(CharClassBuilderTest_372, RemoveAbove_BelowThreshold_372) {

    Rune lo = 65; // 'A'

    Rune hi = 90; // 'Z'

    charClassBuilder->AddRange(lo, hi);

    charClassBuilder->RemoveAbove(91); // '['

    EXPECT_TRUE(charClassBuilder->Contains(65)); // 'A'

}



TEST_F(CharClassBuilderTest_372, RemoveAbove_AboveThreshold_372) {

    Rune lo = 65; // 'A'

    Rune hi = 90; // 'Z'

    charClassBuilder->AddRange(lo, hi);

    charClassBuilder->RemoveAbove(89); // 'Y'

    EXPECT_FALSE(charClassBuilder->Contains(90)); // 'Z'

}



TEST_F(CharClassBuilderTest_372, AddCharClass_Empty_372) {

    CharClassBuilder* cc = new CharClassBuilder();

    charClassBuilder->AddCharClass(cc);

    delete cc;

    EXPECT_TRUE(charClassBuilder->empty());

}



TEST_F(CharClassBuilderTest_372, AddCharClass_NonEmpty_372) {

    CharClassBuilder* cc = new CharClassBuilder();

    Rune lo = 65; // 'A'

    Rune hi = 90; // 'Z'

    cc->AddRange(lo, hi);

    charClassBuilder->AddCharClass(cc);

    delete cc;

    EXPECT_TRUE(charClassBuilder->Contains(65)); // 'A'

}



TEST_F(CharClassBuilderTest_372, FoldsASCII_Default_372) {

    EXPECT_FALSE(charClassBuilder->FoldsASCII());

}
