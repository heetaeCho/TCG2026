#include <gtest/gtest.h>

#include "re2/parse.cc"

#include "re2/regexp.h"



using namespace re2;



class RepetitionWalkerTest_497 : public ::testing::Test {

protected:

    RepetitionWalker walker;

};



TEST_F(RepetitionWalkerTest_497, PostVisit_NoChildren_497) {

    Regexp* regexp = Regexp::Parse("a", kNone, nullptr);

    int parent_arg = 5;

    int pre_arg = 3;

    int child_args[] = {};

    int nchild_args = 0;



    int result = walker.PostVisit(regexp, parent_arg, pre_arg, child_args, nchild_args);



    EXPECT_EQ(result, pre_arg);

    delete regexp;

}



TEST_F(RepetitionWalkerTest_497, PostVisit_OneChild_LessThanPreArg_497) {

    Regexp* sub = Regexp::Parse("b", kNone, nullptr);

    Regexp* regexp = Regexp::Concat(&sub, 1, kNone);



    int parent_arg = 5;

    int pre_arg = 3;

    int child_args[] = {2};

    int nchild_args = 1;



    int result = walker.PostVisit(regexp, parent_arg, pre_arg, child_args, nchild_args);



    EXPECT_EQ(result, child_args[0]);

    delete regexp;

}



TEST_F(RepetitionWalkerTest_497, PostVisit_OneChild_GreaterThanPreArg_497) {

    Regexp* sub = Regexp::Parse("b", kNone, nullptr);

    Regexp* regexp = Regexp::Concat(&sub, 1, kNone);



    int parent_arg = 5;

    int pre_arg = 3;

    int child_args[] = {4};

    int nchild_args = 1;



    int result = walker.PostVisit(regexp, parent_arg, pre_arg, child_args, nchild_args);



    EXPECT_EQ(result, pre_arg);

    delete regexp;

}



TEST_F(RepetitionWalkerTest_497, PostVisit_MultipleChildren_AllLessThanPreArg_497) {

    Regexp* sub1 = Regexp::Parse("b", kNone, nullptr);

    Regexp* sub2 = Regexp::Parse("c", kNone, nullptr);

    Regexp* subs[] = {sub1, sub2};

    Regexp* regexp = Regexp::Concat(subs, 2, kNone);



    int parent_arg = 5;

    int pre_arg = 3;

    int child_args[] = {2, 1};

    int nchild_args = 2;



    int result = walker.PostVisit(regexp, parent_arg, pre_arg, child_args, nchild_args);



    EXPECT_EQ(result, child_args[1]);

    delete regexp;

}



TEST_F(RepetitionWalkerTest_497, PostVisit_MultipleChildren_MixedValues_497) {

    Regexp* sub1 = Regexp::Parse("b", kNone, nullptr);

    Regexp* sub2 = Regexp::Parse("c", kNone, nullptr);

    Regexp* subs[] = {sub1, sub2};

    Regexp* regexp = Regexp::Concat(subs, 2, kNone);



    int parent_arg = 5;

    int pre_arg = 3;

    int child_args[] = {4, 1};

    int nchild_args = 2;



    int result = walker.PostVisit(regexp, parent_arg, pre_arg, child_args, nchild_args);



    EXPECT_EQ(result, child_args[1]);

    delete regexp;

}



TEST_F(RepetitionWalkerTest_497, PostVisit_MultipleChildren_AllGreaterThanPreArg_497) {

    Regexp* sub1 = Regexp::Parse("b", kNone, nullptr);

    Regexp* sub2 = Regexp::Parse("c", kNone, nullptr);

    Regexp* subs[] = {sub1, sub2};

    Regexp* regexp = Regexp::Concat(subs, 2, kNone);



    int parent_arg = 5;

    int pre_arg = 3;

    int child_args[] = {4, 5};

    int nchild_args = 2;



    int result = walker.PostVisit(regexp, parent_arg, pre_arg, child_args, nchild_args);



    EXPECT_EQ(result, pre_arg);

    delete regexp;

}



TEST_F(RepetitionWalkerTest_497, PostVisit_LargeNumberOfChildren_AllLessThanPreArg_497) {

    const int num_children = 10;

    Regexp* subs[num_children];

    for (int i = 0; i < num_children; ++i) {

        subs[i] = Regexp::Parse("b", kNone, nullptr);

    }

    Regexp* regexp = Regexp::Concat(subs, num_children, kNone);



    int parent_arg = 5;

    int pre_arg = 3;

    int child_args[num_children];

    for (int i = 0; i < num_children; ++i) {

        child_args[i] = 2 - i;

    }

    int nchild_args = num_children;



    int result = walker.PostVisit(regexp, parent_arg, pre_arg, child_args, nchild_args);



    EXPECT_EQ(result, child_args[num_children - 1]);

    for (int i = 0; i < num_children; ++i) {

        delete subs[i];

    }

    delete regexp;

}
