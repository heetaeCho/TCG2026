#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "re2/fuzzing/re2_fuzzer.cc"



using namespace re2;



class SubstringWalkerTest_384 : public ::testing::Test {

protected:

    SubstringWalker walker;

};



TEST_F(SubstringWalkerTest_384, ShortVisit_ReturnsParentArg_384) {

    Regexp* mock_regexp = nullptr;  // Assuming a null pointer is safe to pass for this test

    int parent_arg = 123;

    EXPECT_EQ(walker.ShortVisit(mock_regexp, parent_arg), parent_arg);

}



TEST_F(SubstringWalkerTest_384, PostVisit_ReturnsParentArg_384) {

    Regexp* mock_regexp = nullptr;  // Assuming a null pointer is safe to pass for this test

    int parent_arg = 123;

    int pre_arg = 456;

    int child_args[] = {789, 101};

    int nchild_args = sizeof(child_args) / sizeof(child_args[0]);

    EXPECT_EQ(walker.PostVisit(mock_regexp, parent_arg, pre_arg, child_args, nchild_args), parent_arg);

}



TEST_F(SubstringWalkerTest_384, PostVisit_NoChildren_ReturnsParentArg_384) {

    Regexp* mock_regexp = nullptr;  // Assuming a null pointer is safe to pass for this test

    int parent_arg = 123;

    int pre_arg = 456;

    int child_args[] = {};

    int nchild_args = sizeof(child_args) / sizeof(child_args[0]);

    EXPECT_EQ(walker.PostVisit(mock_regexp, parent_arg, pre_arg, child_args, nchild_args), parent_arg);

}



TEST_F(SubstringWalkerTest_384, PostVisit_MultipleChildren_ReturnsParentArg_384) {

    Regexp* mock_regexp = nullptr;  // Assuming a null pointer is safe to pass for this test

    int parent_arg = 123;

    int pre_arg = 456;

    int child_args[] = {789, 101, 112, 131};

    int nchild_args = sizeof(child_args) / sizeof(child_args[0]);

    EXPECT_EQ(walker.PostVisit(mock_regexp, parent_arg, pre_arg, child_args, nchild_args), parent_arg);

}
