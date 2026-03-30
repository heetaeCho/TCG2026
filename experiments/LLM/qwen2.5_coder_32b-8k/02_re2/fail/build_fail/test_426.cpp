#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "re2/simplify.cc"



namespace re2 {



class CoalesceWalkerTest_426 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(CoalesceWalkerTest_426, PostVisit_NoSubs_ReturnsSameRegexp_426) {

    Regexp* re = new Regexp(kRegexpLiteral, 0);

    CoalesceWalker walker;

    Regexp* result = walker.PostVisit(re, nullptr, nullptr, nullptr, 0);



    EXPECT_EQ(result, re);

    re->Decref();

}



TEST_F(CoalesceWalkerTest_426, PostVisit_NoCoalesce_ReturnsNewRegexp_426) {

    Regexp* child1 = new Regexp(kRegexpLiteral, 0);

    Regexp* child2 = new Regexp(kRegexpLiteralString, 0);

    Regexp** children = new Regexp*[2]{child1, child2};

    

    Regexp* re = Regexp::Concat(children, 2, 0);

    CoalesceWalker walker;

    Regexp* result = walker.PostVisit(re, nullptr, nullptr, children, 2);



    EXPECT_NE(result, re);

    EXPECT_EQ(result->op(), kRegexpConcat);

    EXPECT_EQ(result->nsub(), 2);

    

    result->Decref();

    re->Decref();

}



TEST_F(CoalesceWalkerTest_426, PostVisit_CanCoalesce_ReturnsSimplifiedRegexp_426) {

    Regexp* child1 = new Regexp(kRegexpLiteral, 0);

    Regexp* child2 = new Regexp(kRegexpLiteralString, 0);

    Regexp** children = new Regexp*[2]{child1, child2};

    

    // Mock CanCoalesce to always return true for this test

    testing::ReplaceFunction(&CoalesceWalker::CanCoalesce,

        [](const Regexp* r1, const Regexp* r2) -> bool {

            return true;

        });



    CoalesceWalker walker;

    Regexp* re = Regexp::Concat(children, 2, 0);

    Regexp* result = walker.PostVisit(re, nullptr, nullptr, children, 2);



    EXPECT_NE(result, re);

    EXPECT_EQ(result->op(), kRegexpConcat);

    EXPECT_LE(result->nsub(), 1); // Coalesced should have less or equal sub patterns



    result->Decref();

    re->Decref();

}



TEST_F(CoalesceWalkerTest_426, PostVisit_EmptyMatch_RemovedFromResult_426) {

    Regexp* child1 = new Regexp(kRegexpEmptyMatch, 0);

    Regexp* child2 = new Regexp(kRegexpLiteral, 0);

    Regexp** children = new Regexp*[2]{child1, child2};

    

    CoalesceWalker walker;

    Regexp* re = Regexp::Concat(children, 2, 0);

    Regexp* result = walker.PostVisit(re, nullptr, nullptr, children, 2);



    EXPECT_NE(result, re);

    EXPECT_EQ(result->op(), kRegexpConcat);

    EXPECT_EQ(result->nsub(), 1); // EmptyMatch should be removed



    result->Decref();

    re->Decref();

}



TEST_F(CoalesceWalkerTest_426, PostVisit_RegexpRepeat_ReturnsNewRegexpWithSameBounds_426) {

    Regexp* child = new Regexp(kRegexpLiteral, 0);

    Regexp** children = new Regexp*[1]{child};

    

    Regexp* re = Regexp::Repeat(child, 0, 5, 3); // min=3, max=5

    CoalesceWalker walker;

    Regexp* result = walker.PostVisit(re, nullptr, nullptr, children, 1);



    EXPECT_NE(result, re);

    EXPECT_EQ(result->op(), kRegexpRepeat);

    EXPECT_EQ(result->min(), 3);

    EXPECT_EQ(result->max(), 5);

    

    result->Decref();

    re->Decref();

}



TEST_F(CoalesceWalkerTest_426, PostVisit_RegexpCapture_ReturnsNewRegexpWithSameCap_426) {

    Regexp* child = new Regexp(kRegexpLiteral, 0);

    Regexp** children = new Regexp*[1]{child};

    

    Regexp* re = Regexp::Capture(child, 0, 7); // cap=7

    CoalesceWalker walker;

    Regexp* result = walker.PostVisit(re, nullptr, nullptr, children, 1);



    EXPECT_NE(result, re);

    EXPECT_EQ(result->op(), kRegexpCapture);

    EXPECT_EQ(result->cap(), 7);

    

    result->Decref();

    re->Decref();

}



} // namespace re2
