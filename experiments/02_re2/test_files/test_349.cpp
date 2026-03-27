#include <gtest/gtest.h>

#include "regexp.h"

#include "re2/testing/test_utils.h"



namespace re2 {



class RegexpTest_349 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Cleanup if needed

    }

};



TEST_F(RegexpTest_349, TopEqual_SameOpNoMatch_349) {

    Regexp* a = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* b = Regexp::NewLiteral('b', Regexp::NoParseFlags);



    a->op_ = kRegexpNoMatch;

    b->op_ = kRegexpNoMatch;



    EXPECT_TRUE(TopEqual(a, b));



    delete a;

    delete b;

}



TEST_F(RegexpTest_349, TopEqual_DifferentOps_349) {

    Regexp* a = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* b = Regexp::NewLiteral('b', Regexp::NoParseFlags);



    b->op_ = kRegexpEmptyMatch;



    EXPECT_FALSE(TopEqual(a, b));



    delete a;

    delete b;

}



TEST_F(RegexpTest_349, TopEqual_LiteralSameRuneAndFlags_349) {

    Regexp* a = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* b = Regexp::NewLiteral('a', Regexp::NoParseFlags);



    EXPECT_TRUE(TopEqual(a, b));



    delete a;

    delete b;

}



TEST_F(RegexpTest_349, TopEqual_LiteralDifferentRune_349) {

    Regexp* a = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* b = Regexp::NewLiteral('b', Regexp::NoParseFlags);



    EXPECT_FALSE(TopEqual(a, b));



    delete a;

    delete b;

}



TEST_F(RegexpTest_349, TopEqual_LiteralDifferentFoldCaseFlag_349) {

    Regexp* a = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* b = Regexp::NewLiteral('a', Regexp::FoldCase);



    EXPECT_FALSE(TopEqual(a, b));



    delete a;

    delete b;

}



TEST_F(RegexpTest_349, TopEqual_LiteralStringSameContentAndFlags_349) {

    Rune runes1[] = {'a', 'b'};

    Rune runes2[] = {'a', 'b'};



    Regexp* a = Regexp::LiteralString(runes1, 2, Regexp::NoParseFlags);

    Regexp* b = Regexp::LiteralString(runes2, 2, Regexp::NoParseFlags);



    EXPECT_TRUE(TopEqual(a, b));



    delete a;

    delete b;

}



TEST_F(RegexpTest_349, TopEqual_LiteralStringDifferentContent_349) {

    Rune runes1[] = {'a', 'b'};

    Rune runes2[] = {'c', 'd'};



    Regexp* a = Regexp::LiteralString(runes1, 2, Regexp::NoParseFlags);

    Regexp* b = Regexp::LiteralString(runes2, 2, Regexp::NoParseFlags);



    EXPECT_FALSE(TopEqual(a, b));



    delete a;

    delete b;

}



TEST_F(RegexpTest_349, TopEqual_LiteralStringDifferentFoldCaseFlag_349) {

    Rune runes1[] = {'a', 'b'};

    Rune runes2[] = {'a', 'b'};



    Regexp* a = Regexp::LiteralString(runes1, 2, Regexp::NoParseFlags);

    Regexp* b = Regexp::LiteralString(runes2, 2, Regexp::FoldCase);



    EXPECT_FALSE(TopEqual(a, b));



    delete a;

    delete b;

}



TEST_F(RegexpTest_349, TopEqual_AlternateSameNsub_349) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* subs1[] = {sub1};

    Regexp* a = Regexp::Alternate(subs1, 1, Regexp::NoParseFlags);



    Regexp* sub2 = Regexp::NewLiteral('b', Regexp::NoParseFlags);

    Regexp* subs2[] = {sub2};

    Regexp* b = Regexp::Alternate(subs2, 1, Regexp::NoParseFlags);



    EXPECT_TRUE(TopEqual(a, b));



    delete a;

    delete sub1;

    delete b;

    delete sub2;

}



TEST_F(RegexpTest_349, TopEqual_AlternateDifferentNsub_349) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* subs1[] = {sub1};

    Regexp* a = Regexp::Alternate(subs1, 1, Regexp::NoParseFlags);



    Regexp* sub2_1 = Regexp::NewLiteral('b', Regexp::NoParseFlags);

    Regexp* sub2_2 = Regexp::NewLiteral('c', Regexp::NoParseFlags);

    Regexp* subs2[] = {sub2_1, sub2_2};

    Regexp* b = Regexp::Alternate(subs2, 2, Regexp::NoParseFlags);



    EXPECT_FALSE(TopEqual(a, b));



    delete a;

    delete sub1;

    delete b;

    delete sub2_1;

    delete sub2_2;

}



TEST_F(RegexpTest_349, TopEqual_ConcatSameNsub_349) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* subs1[] = {sub1};

    Regexp* a = Regexp::Concat(subs1, 1, Regexp::NoParseFlags);



    Regexp* sub2 = Regexp::NewLiteral('b', Regexp::NoParseFlags);

    Regexp* subs2[] = {sub2};

    Regexp* b = Regexp::Concat(subs2, 1, Regexp::NoParseFlags);



    EXPECT_TRUE(TopEqual(a, b));



    delete a;

    delete sub1;

    delete b;

    delete sub2;

}



TEST_F(RegexpTest_349, TopEqual_ConcatDifferentNsub_349) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* subs1[] = {sub1};

    Regexp* a = Regexp::Concat(subs1, 1, Regexp::NoParseFlags);



    Regexp* sub2_1 = Regexp::NewLiteral('b', Regexp::NoParseFlags);

    Regexp* sub2_2 = Regexp::NewLiteral('c', Regexp::NoParseFlags);

    Regexp* subs2[] = {sub2_1, sub2_2};

    Regexp* b = Regexp::Concat(subs2, 2, Regexp::NoParseFlags);



    EXPECT_FALSE(TopEqual(a, b));



    delete a;

    delete sub1;

    delete b;

    delete sub2_1;

    delete sub2_2;

}



TEST_F(RegexpTest_349, TopEqual_StarSameNonGreedyFlag_349) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* a = Regexp::Star(sub1, Regexp::NoParseFlags);



    Regexp* sub2 = Regexp::NewLiteral('b', Regexp::NoParseFlags);

    Regexp* b = Regexp::Star(sub2, Regexp::NoParseFlags);



    EXPECT_TRUE(TopEqual(a, b));



    delete a;

    delete sub1;

    delete b;

    delete sub2;

}



TEST_F(RegexpTest_349, TopEqual_StarDifferentNonGreedyFlag_349) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* a = Regexp::Star(sub1, Regexp::NoParseFlags);



    Regexp* sub2 = Regexp::NewLiteral('b', Regexp::NonGreedy);

    Regexp* b = Regexp::Star(sub2, Regexp::NonGreedy);



    EXPECT_FALSE(TopEqual(a, b));



    delete a;

    delete sub1;

    delete b;

    delete sub2;

}



TEST_F(RegexpTest_349, TopEqual_PlusSameNonGreedyFlag_349) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* a = Regexp::Plus(sub1, Regexp::NoParseFlags);



    Regexp* sub2 = Regexp::NewLiteral('b', Regexp::NoParseFlags);

    Regexp* b = Regexp::Plus(sub2, Regexp::NoParseFlags);



    EXPECT_TRUE(TopEqual(a, b));



    delete a;

    delete sub1;

    delete b;

    delete sub2;

}



TEST_F(RegexpTest_349, TopEqual_PlusDifferentNonGreedyFlag_349) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* a = Regexp::Plus(sub1, Regexp::NoParseFlags);



    Regexp* sub2 = Regexp::NewLiteral('b', Regexp::NonGreedy);

    Regexp* b = Regexp::Plus(sub2, Regexp::NonGreedy);



    EXPECT_FALSE(TopEqual(a, b));



    delete a;

    delete sub1;

    delete b;

    delete sub2;

}



TEST_F(RegexpTest_349, TopEqual_QuestSameNonGreedyFlag_349) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* a = Regexp::Quest(sub1, Regexp::NoParseFlags);



    Regexp* sub2 = Regexp::NewLiteral('b', Regexp::NoParseFlags);

    Regexp* b = Regexp::Quest(sub2, Regexp::NoParseFlags);



    EXPECT_TRUE(TopEqual(a, b));



    delete a;

    delete sub1;

    delete b;

    delete sub2;

}



TEST_F(RegexpTest_349, TopEqual_QuestDifferentNonGreedyFlag_349) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* a = Regexp::Quest(sub1, Regexp::NoParseFlags);



    Regexp* sub2 = Regexp::NewLiteral('b', Regexp::NonGreedy);

    Regexp* b = Regexp::Quest(sub2, Regexp::NonGreedy);



    EXPECT_FALSE(TopEqual(a, b));



    delete a;

    delete sub1;

    delete b;

    delete sub2;

}



TEST_F(RegexpTest_349, TopEqual_RepeatSameMinAndMax_349) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* a = Regexp::Repeat(sub1, Regexp::NoParseFlags, 2, 5);



    Regexp* sub2 = Regexp::NewLiteral('b', Regexp::NoParseFlags);

    Regexp* b = Regexp::Repeat(sub2, Regexp::NoParseFlags, 2, 5);



    EXPECT_TRUE(TopEqual(a, b));



    delete a;

    delete sub1;

    delete b;

    delete sub2;

}



TEST_F(RegexpTest_349, TopEqual_RepeatDifferentMinAndMax_349) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* a = Regexp::Repeat(sub1, Regexp::NoParseFlags, 2, 5);



    Regexp* sub2 = Regexp::NewLiteral('b', Regexp::NoParseFlags);

    Regexp* b = Regexp::Repeat(sub2, Regexp::NoParseFlags, 3, 6);



    EXPECT_FALSE(TopEqual(a, b));



    delete a;

    delete sub1;

    delete b;

    delete sub2;

}



TEST_F(RegexpTest_349, TopEqual_CaptureSameCapAndName_349) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* a = Regexp::Capture(sub1, Regexp::NoParseFlags, 1);



    Regexp* sub2 = Regexp::NewLiteral('b', Regexp::NoParseFlags);

    Regexp* b = Regexp::Capture(sub2, Regexp::NoParseFlags, 1);



    EXPECT_TRUE(TopEqual(a, b));



    delete a;

    delete sub1;

    delete b;

    delete sub2;

}



TEST_F(RegexpTest_349, TopEqual_CaptureDifferentCap_349) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* a = Regexp::Capture(sub1, Regexp::NoParseFlags, 1);



    Regexp* sub2 = Regexp::NewLiteral('b', Regexp::NoParseFlags);

    Regexp* b = Regexp::Capture(sub2, Regexp::NoParseFlags, 2);



    EXPECT_FALSE(TopEqual(a, b));



    delete a;

    delete sub1;

    delete b;

    delete sub2;

}



TEST_F(RegexpTest_349, TopEqual_EndTextSameWasDollarFlag_349) {

    Regexp* a = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    a->op_ = kRegexpEndText;



    Regexp* b = Regexp::NewLiteral('b', Regexp::NoParseFlags);

    b->op_ = kRegexpEndText;



    EXPECT_TRUE(TopEqual(a, b));



    delete a;

    delete b;

}



TEST_F(RegexpTest_349, TopEqual_EndTextDifferentWasDollarFlag_349) {

    Regexp* a = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    a->op_ = kRegexpEndText;



    Regexp* b = Regexp::NewLiteral('b', Regexp::WasDollar);

    b->op_ = kRegexpEndText;



    EXPECT_FALSE(TopEqual(a, b));



    delete a;

    delete b;

}



TEST_F(RegexpTest_349, TopEqual_CharClassSameRanges_349) {

    RuneRangeSet ranges1;

    RuneRange range1 = {0, 1};

    ranges1.insert(range1);



    CharClass* cc1 = CharClass::New(2);

    for (const auto& rr : ranges1)

        cc1->AddRange(rr.lo, rr.hi);



    Regexp* a = Regexp::NewCharClass(cc1, Regexp::NoParseFlags);



    RuneRangeSet ranges2;

    RuneRange range2 = {0, 1};

    ranges2.insert(range2);



    CharClass* cc2 = CharClass::New(2);

    for (const auto& rr : ranges2)

        cc2->AddRange(rr.lo, rr.hi);



    Regexp* b = Regexp::NewCharClass(cc2, Regexp::NoParseFlags);



    EXPECT_TRUE(TopEqual(a, b));



    delete a;

    cc1->Delete();

    delete b;

    cc2->Delete();

}



TEST_F(RegexpTest_349, TopEqual_CharClassDifferentRanges_349) {

    RuneRangeSet ranges1;

    RuneRange range1 = {0, 1};

    ranges1.insert(range1);



    CharClass* cc1 = CharClass::New(2);

    for (const auto& rr : ranges1)

        cc1->AddRange(rr.lo, rr.hi);



    Regexp* a = Regexp::NewCharClass(cc1, Regexp::NoParseFlags);



    RuneRangeSet ranges2;

    RuneRange range2 = {2, 3};

    ranges2.insert(range2);



    CharClass* cc2 = CharClass::New(2);

    for (const auto& rr : ranges2)

        cc2->AddRange(rr.lo, rr.hi);



    Regexp* b = Regexp::NewCharClass(cc2, Regexp::NoParseFlags);



    EXPECT_FALSE(TopEqual(a, b));



    delete a;

    cc1->Delete();

    delete b;

    cc2->Delete();

}



}  // namespace re2
