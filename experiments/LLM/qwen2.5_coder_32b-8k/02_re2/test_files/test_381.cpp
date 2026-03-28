#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "re2/fuzzing/re2_fuzzer.cc"



using namespace re2;



class SubexpressionWalkerTest_381 : public ::testing::Test {

protected:

    void SetUp() override {

        walker = std::make_unique<SubexpressionWalker>();

    }



    std::unique_ptr<SubexpressionWalker> walker;

};



TEST_F(SubexpressionWalkerTest_381, PostVisit_ConcatNormal_381) {

    Regexp* reConcat = Regexp::Concat(nullptr, 0, Regexp::ParseFlags());

    int parent_arg = 10;

    int pre_arg = 20;

    int child_args[] = {5, 6};

    int nchild_args = 2;



    int result = walker->PostVisit(reConcat, parent_arg, pre_arg, child_args, nchild_args);

    EXPECT_EQ(result, 6);



    reConcat->Decref();

}



TEST_F(SubexpressionWalkerTest_381, PostVisit_AlternateNormal_381) {

    Regexp* reAlternate = Regexp::Alternate(nullptr, 0, Regexp::ParseFlags());

    int parent_arg = 10;

    int pre_arg = 20;

    int child_args[] = {5, 6};

    int nchild_args = 2;



    int result = walker->PostVisit(reAlternate, parent_arg, pre_arg, child_args, nchild_args);

    EXPECT_EQ(result, 6);



    reAlternate->Decref();

}



TEST_F(SubexpressionWalkerTest_381, PostVisit_NoChildren_381) {

    Regexp* reConcat = Regexp::Concat(nullptr, 0, Regexp::ParseFlags());

    int parent_arg = 10;

    int pre_arg = 20;

    int child_args[] = {};

    int nchild_args = 0;



    int result = walker->PostVisit(reConcat, parent_arg, pre_arg, child_args, nchild_args);

    EXPECT_EQ(result, 0);



    reConcat->Decref();

}



TEST_F(SubexpressionWalkerTest_381, PostVisit_DefaultCase_381) {

    Regexp* reLiteral = Regexp::NewLiteral('a', Regexp::ParseFlags());

    int parent_arg = 10;

    int pre_arg = 20;

    int child_args[] = {5};

    int nchild_args = 1;



    int result = walker->PostVisit(reLiteral, parent_arg, pre_arg, child_args, nchild_args);

    EXPECT_EQ(result, -1);



    reLiteral->Decref();

}



TEST_F(SubexpressionWalkerTest_381, PostVisit_MultipleChildrenConcat_381) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::ParseFlags());

    Regexp* sub2 = Regexp::NewLiteral('b', Regexp::ParseFlags());

    Regexp* sub3 = Regexp::NewLiteral('c', Regexp::ParseFlags());



    Regexp* subs[] = {sub1, sub2, sub3};

    Regexp* reConcat = Regexp::Concat(subs, 3, Regexp::ParseFlags());

    int parent_arg = 10;

    int pre_arg = 20;

    int child_args[] = {5, 6, 7};

    int nchild_args = 3;



    int result = walker->PostVisit(reConcat, parent_arg, pre_arg, child_args, nchild_args);

    EXPECT_EQ(result, 7);



    reConcat->Decref();

}



TEST_F(SubexpressionWalkerTest_381, PostVisit_MultipleChildrenAlternate_381) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::ParseFlags());

    Regexp* sub2 = Regexp::NewLiteral('b', Regexp::ParseFlags());

    Regexp* sub3 = Regexp::NewLiteral('c', Regexp::ParseFlags());



    Regexp* subs[] = {sub1, sub2, sub3};

    Regexp* reAlternate = Regexp::Alternate(subs, 3, Regexp::ParseFlags());

    int parent_arg = 10;

    int pre_arg = 20;

    int child_args[] = {5, 6, 7};

    int nchild_args = 3;



    int result = walker->PostVisit(reAlternate, parent_arg, pre_arg, child_args, nchild_args);

    EXPECT_EQ(result, 7);



    reAlternate->Decref();

}



TEST_F(SubexpressionWalkerTest_381, PostVisit_NegativeChildArgs_381) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::ParseFlags());

    Regexp* sub2 = Regexp::NewLiteral('b', Regexp::ParseFlags());



    Regexp* subs[] = {sub1, sub2};

    Regexp* reConcat = Regexp::Concat(subs, 2, Regexp::ParseFlags());

    int parent_arg = 10;

    int pre_arg = 20;

    int child_args[] = {-5, -6};

    int nchild_args = 2;



    int result = walker->PostVisit(reConcat, parent_arg, pre_arg, child_args, nchild_args);

    EXPECT_EQ(result, -5);



    reConcat->Decref();

}
