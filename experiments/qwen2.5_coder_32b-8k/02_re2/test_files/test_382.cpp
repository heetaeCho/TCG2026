#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"

#include "re2/fuzzing/re2_fuzzer.cc"



using namespace re2;



class SubexpressionWalkerTest_382 : public ::testing::Test {

protected:

    SubexpressionWalker walker;

};



TEST_F(SubexpressionWalkerTest_382, ShortVisit_ReturnsParentArg_NormalCase_382) {

    Regexp* regexp = Regexp::Parse("abc", Regexp::NoParseFlags(), nullptr);

    int parent_arg = 42;



    int result = walker.ShortVisit(regexp, parent_arg);



    EXPECT_EQ(result, parent_arg);

    delete regexp;

}



TEST_F(SubexpressionWalkerTest_382, ShortVisit_ReturnsParentArg_EmptyRegexp_382) {

    Regexp* regexp = Regexp::Parse("", Regexp::NoParseFlags(), nullptr);

    int parent_arg = 0;



    int result = walker.ShortVisit(regexp, parent_arg);



    EXPECT_EQ(result, parent_arg);

    delete regexp;

}



TEST_F(SubexpressionWalkerTest_382, ShortVisit_ReturnsParentArg_ComplexRegexp_382) {

    Regexp* regexp = Regexp::Parse("(a|b)*c+", Regexp::NoParseFlags(), nullptr);

    int parent_arg = 100;



    int result = walker.ShortVisit(regexp, parent_arg);



    EXPECT_EQ(result, parent_arg);

    delete regexp;

}



TEST_F(SubexpressionWalkerTest_382, PostVisit_ReturnsParentArg_NormalCase_382) {

    Regexp* regexp = Regexp::Parse("abc", Regexp::NoParseFlags(), nullptr);

    int parent_arg = 42;

    int pre_arg = 0;

    int child_args[] = {1, 2, 3};

    int nchild_args = 3;



    int result = walker.PostVisit(regexp, parent_arg, pre_arg, child_args, nchild_args);



    EXPECT_EQ(result, parent_arg);

    delete regexp;

}



TEST_F(SubexpressionWalkerTest_382, PostVisit_ReturnsParentArg_EmptyRegexp_382) {

    Regexp* regexp = Regexp::Parse("", Regexp::NoParseFlags(), nullptr);

    int parent_arg = 0;

    int pre_arg = 0;

    int child_args[] = {};

    int nchild_args = 0;



    int result = walker.PostVisit(regexp, parent_arg, pre_arg, child_args, nchild_args);



    EXPECT_EQ(result, parent_arg);

    delete regexp;

}



TEST_F(SubexpressionWalkerTest_382, PostVisit_ReturnsParentArg_ComplexRegexp_382) {

    Regexp* regexp = Regexp::Parse("(a|b)*c+", Regexp::NoParseFlags(), nullptr);

    int parent_arg = 100;

    int pre_arg = 0;

    int child_args[] = {1, 2};

    int nchild_args = 2;



    int result = walker.PostVisit(regexp, parent_arg, pre_arg, child_args, nchild_args);



    EXPECT_EQ(result, parent_arg);

    delete regexp;

}
