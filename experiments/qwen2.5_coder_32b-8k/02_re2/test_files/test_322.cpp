#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"



using namespace re2;



class IsAnchorStartTest : public ::testing::Test {

protected:

    Regexp* CreateRegexp(RegexpOp op) {

        return new Regexp(op, kParseFlagsNone);

    }

};



TEST_F(IsAnchorStartTest, NormalConcatWithAnchorStart_322) {

    Regexp* sub = CreateRegexp(kRegexpBeginText);

    Regexp* concatSubs[] = {sub};

    Regexp* concat = Regexp::Concat(concatSubs, 1, kParseFlagsNone);

    Regexp* pre = concat;

    EXPECT_TRUE(IsAnchorStart(&pre, 0));

    pre->Decref();

}



TEST_F(IsAnchorStartTest, NormalCaptureWithAnchorStart_322) {

    Regexp* sub = CreateRegexp(kRegexpBeginText);

    Regexp* capture = Regexp::Capture(sub, kParseFlagsNone, 1);

    Regexp* pre = capture;

    EXPECT_TRUE(IsAnchorStart(&pre, 0));

    pre->Decref();

}



TEST_F(IsAnchorStartTest, NormalLiteralString_322) {

    Regexp* literal = CreateRegexp(kRegexpLiteralString);

    Regexp* pre = literal;

    EXPECT_FALSE(IsAnchorStart(&pre, 0));

    pre->Decref();

}



TEST_F(IsAnchorStartTest, DepthLimitReached_322) {

    Regexp* sub = CreateRegexp(kRegexpBeginText);

    Regexp* concatSubs[] = {sub};

    Regexp* concat = Regexp::Concat(concatSubs, 1, kParseFlagsNone);

    Regexp* pre = concat;

    EXPECT_FALSE(IsAnchorStart(&pre, 4));

    pre->Decref();

}



TEST_F(IsAnchorStartTest, EmptyRegexp_322) {

    Regexp* pre = nullptr;

    EXPECT_FALSE(IsAnchorStart(&pre, 0));

}



TEST_F(IsAnchorStartTest, NestedConcatWithAnchorStart_322) {

    Regexp* innerSub = CreateRegexp(kRegexpBeginText);

    Regexp* concatInnerSubs[] = {innerSub};

    Regexp* innerConcat = Regexp::Concat(concatInnerSubs, 1, kParseFlagsNone);

    Regexp* outerConcatSubs[] = {innerConcat};

    Regexp* outerConcat = Regexp::Concat(outerConcatSubs, 1, kParseFlagsNone);

    Regexp* pre = outerConcat;

    EXPECT_TRUE(IsAnchorStart(&pre, 0));

    pre->Decref();

}



TEST_F(IsAnchorStartTest, NestedCaptureWithAnchorStart_322) {

    Regexp* innerSub = CreateRegexp(kRegexpBeginText);

    Regexp* captureInner = Regexp::Capture(innerSub, kParseFlagsNone, 1);

    Regexp* outerConcatSubs[] = {captureInner};

    Regexp* outerConcat = Regexp::Concat(outerConcatSubs, 1, kParseFlagsNone);

    Regexp* pre = outerConcat;

    EXPECT_TRUE(IsAnchorStart(&pre, 0));

    pre->Decref();

}
