#include <gtest/gtest.h>

#include "regexp.h"



using namespace re2;



class ParseStateTest_512 : public ::testing::Test {

protected:

    RegexpStatus status_;

    ParseState state_{NoParseFlags, "", &status_};



    void PushLiteral(Rune r) {

        ASSERT_TRUE(state_.PushRegexp(Regexp::NewLiteral(r, NoParseFlags)));

    }



    void PushLiteralString(const std::string& str) {

        for (Rune rune : str) {

            PushLiteral(rune);

        }

    }

};



TEST_F(ParseStateTest_512, MaybeConcatString_NormalOperation_512) {

    PushLiteral('a');

    PushLiteral('b');

    EXPECT_TRUE(state_.MaybeConcatString('c', NoParseFlags));

}



TEST_F(ParseStateTest_512, MaybeConcatString_BoundaryConditions_EmptyStack_512) {

    EXPECT_FALSE(state_.MaybeConcatString('c', NoParseFlags));

}



TEST_F(ParseStateTest_512, MaybeConcatString_BoundaryConditions_OneElementStack_512) {

    PushLiteral('a');

    EXPECT_FALSE(state_.MaybeConcatString('b', NoParseFlags));

}



TEST_F(ParseStateTest_512, MaybeConcatString_ErrorCase_DifferentOps_512) {

    PushLiteral('a');

    auto* re = new Regexp(kRegexpAnyChar, NoParseFlags);

    ASSERT_TRUE(state_.PushRegexp(re));

    EXPECT_FALSE(state_.MaybeConcatString('b', NoParseFlags));

}



TEST_F(ParseStateTest_512, MaybeConcatString_ErrorCase_DifferentFoldCases_512) {

    PushLiteral('a');

    auto* re = Regexp::NewLiteral('b', FoldCase);

    ASSERT_TRUE(state_.PushRegexp(re));

    EXPECT_FALSE(state_.MaybeConcatString('c', NoParseFlags));

}



TEST_F(ParseStateTest_512, MaybeConcatString_ErrorCase_TopNotLiteralOrLiteralString_512) {

    auto* re = new Regexp(kRegexpAnyChar, NoParseFlags);

    ASSERT_TRUE(state_.PushRegexp(re));

    re = Regexp::NewLiteral('a', NoParseFlags);

    ASSERT_TRUE(state_.PushRegexp(re));

    EXPECT_FALSE(state_.MaybeConcatString('b', NoParseFlags));

}



TEST_F(ParseStateTest_512, MaybeConcatString_ErrorCase_SecondNotLiteralOrLiteralString_512) {

    PushLiteral('a');

    auto* re = new Regexp(kRegexpAnyChar, NoParseFlags);

    ASSERT_TRUE(state_.PushRegexp(re));

    EXPECT_FALSE(state_.MaybeConcatString('b', NoParseFlags));

}



TEST_F(ParseStateTest_512, MaybeConcatString_ErrorCase_TopNotLiteralString_SecondIsLiteral_512) {

    auto* re = Regexp::NewLiteral('a', NoParseFlags);

    ASSERT_TRUE(state_.PushRegexp(re));

    PushLiteral('b');

    EXPECT_FALSE(state_.MaybeConcatString('c', NoParseFlags));

}



TEST_F(ParseStateTest_512, MaybeConcatString_ErrorCase_TopIsLiteral_SecondIsLiteralString_DifferentRuneMax_512) {

    state_.rune_max_ = 2;

    PushLiteral('a');

    auto* re = Regexp::NewLiteral('b', NoParseFlags);

    ASSERT_TRUE(state_.PushRegexp(re));

    EXPECT_FALSE(state_.MaybeConcatString('c', NoParseFlags));

}
