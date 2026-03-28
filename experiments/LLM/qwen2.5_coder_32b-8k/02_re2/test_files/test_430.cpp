#include <gtest/gtest.h>

#include "regexp.h"

#include "simplify.cc"



namespace re2 {



class SimplifyWalkerTest : public ::testing::Test {

protected:

    SimplifyWalker walker;

};



TEST_F(SimplifyWalkerTest, PostVisitLiteral_430) {

    Regexp* literal = Regexp::NewLiteral('a', 0);

    EXPECT_EQ(literal->op(), kRegexpLiteral);



    Regexp** child_args = nullptr;

    int nchild_args = 0;



    Regexp* result = walker.PostVisit(literal, nullptr, nullptr, child_args, nchild_args);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->op(), kRegexpLiteral);

    EXPECT_TRUE(result->simple());



    literal->Decref();

    result->Decref();

}



TEST_F(SimplifyWalkerTest, PostVisitConcatSameChildren_430) {

    Regexp* re1 = Regexp::NewLiteral('a', 0);

    Regexp* re2 = Regexp::NewLiteral('b', 0);

    Regexp** subs = new Regexp*[2]{re1, re2};

    Regexp* concat = Regexp::Concat(subs, 2, 0);



    EXPECT_EQ(concat->op(), kRegexpConcat);



    Regexp** child_args = new Regexp*[2]{re1, re2};

    int nchild_args = 2;



    Regexp* result = walker.PostVisit(concat, nullptr, nullptr, child_args, nchild_args);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->op(), kRegexpConcat);

    EXPECT_TRUE(result->simple());



    concat->Decref();

    re1->Decref();

    re2->Decref();

    delete[] subs;

    delete[] child_args;

}



TEST_F(SimplifyWalkerTest, PostVisitStarEmptyMatch_430) {

    Regexp* empty = Regexp::Parse("", 0, nullptr);

    EXPECT_EQ(empty->op(), kRegexpEmptyMatch);



    Regexp** subs = new Regexp*[1]{empty};

    Regexp* star = Regexp::Star(subs[0], 0);

    EXPECT_EQ(star->op(), kRegexpStar);



    Regexp** child_args = new Regexp*[1]{empty};

    int nchild_args = 1;



    Regexp* result = walker.PostVisit(star, nullptr, nullptr, child_args, nchild_args);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->op(), kRegexpEmptyMatch);



    star->Decref();

    empty->Decref();

    delete[] subs;

    delete[] child_args;

}



TEST_F(SimplifyWalkerTest, PostVisitRepeatEmptyMatch_430) {

    Regexp* empty = Regexp::Parse("", 0, nullptr);

    EXPECT_EQ(empty->op(), kRegexpEmptyMatch);



    Regexp* repeat = Regexp::Repeat(empty, 0, 1, 2);

    EXPECT_EQ(repeat->op(), kRegexpRepeat);



    Regexp** child_args = new Regexp*[1]{empty};

    int nchild_args = 1;



    Regexp* result = walker.PostVisit(repeat, nullptr, nullptr, child_args, nchild_args);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->op(), kRegexpEmptyMatch);



    repeat->Decref();

    empty->Decref();

    delete[] child_args;

}



TEST_F(SimplifyWalkerTest, PostVisitCaptureSameChild_430) {

    Regexp* literal = Regexp::NewLiteral('a', 0);

    EXPECT_EQ(literal->op(), kRegexpLiteral);



    Regexp* capture = Regexp::Capture(literal, 0, 1);

    EXPECT_EQ(capture->op(), kRegexpCapture);



    Regexp** child_args = new Regexp*[1]{literal};

    int nchild_args = 1;



    Regexp* result = walker.PostVisit(capture, nullptr, nullptr, child_args, nchild_args);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->op(), kRegexpCapture);

    EXPECT_TRUE(result->simple());



    capture->Decref();

    literal->Decref();

    delete[] child_args;

}



TEST_F(SimplifyWalkerTest, PostVisitAlternateDifferentChildren_430) {

    Regexp* re1 = Regexp::NewLiteral('a', 0);

    Regexp* re2 = Regexp::NewLiteral('b', 0);

    Regexp** subs = new Regexp*[2]{re1, re2};

    Regexp* alternate = Regexp::Alternate(subs, 2, 0);



    EXPECT_EQ(alternate->op(), kRegexpAlternate);



    Regexp** child_args = new Regexp*[2]{re1, re2};

    int nchild_args = 2;



    Regexp* result = walker.PostVisit(alternate, nullptr, nullptr, child_args, nchild_args);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->op(), kRegexpAlternate);

    EXPECT_TRUE(result->simple());



    alternate->Decref();

    re1->Decref();

    re2->Decref();

    delete[] subs;

    delete[] child_args;

}



TEST_F(SimplifyWalkerTest, PostVisitCharClass_430) {

    CharClass* cc = new CharClass();

    Regexp* charclass = Regexp::NewCharClass(cc, 0);

    EXPECT_EQ(charclass->op(), kRegexpCharClass);



    Regexp** child_args = nullptr;

    int nchild_args = 0;



    Regexp* result = walker.PostVisit(charclass, nullptr, nullptr, child_args, nchild_args);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->op(), kRegexpCharClass);

    EXPECT_TRUE(result->simple());



    charclass->Decref();

    delete cc;

    result->Decref();

}



}  // namespace re2
