#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"

#include "re2/simplify.cc"



using namespace re2;

using ::testing::Return;



class CoalesceWalkerTest_424 : public ::testing::Test {

protected:

    CoalesceWalker walker;

    Regexp* CreateMockRegexp() {

        return new Regexp(RegexpOp::kAnyChar, ParseFlags::None);

    }

};



TEST_F(CoalesceWalkerTest_424, CopyReturnsSamePointer_424) {

    Regexp* re = CreateMockRegexp();

    EXPECT_EQ(walker.Copy(re), re);

    delete re;

}



TEST_F(CoalesceWalkerTest_424, ShortVisitReturnsSamePointer_424) {

    Regexp* re = CreateMockRegexp();

    EXPECT_EQ(walker.ShortVisit(re, nullptr), re);

    delete re;

}



TEST_F(CoalesceWalkerTest_424, PostVisitWithoutChildrenReturnsSamePointer_424) {

    Regexp* re = CreateMockRegexp();

    EXPECT_EQ(walker.PostVisit(re, nullptr, nullptr, nullptr, 0), re);

    delete re;

}



TEST_F(CoalesceWalkerTest_424, PostVisitWithNullParentAndChildArgsReturnsSamePointer_424) {

    Regexp* re = CreateMockRegexp();

    EXPECT_EQ(walker.PostVisit(re, nullptr, nullptr, nullptr, 1), re);

    delete re;

}



TEST_F(CoalesceWalkerTest_424, PostVisitWithValidParentAndNullChildArgsReturnsSamePointer_424) {

    Regexp* re = CreateMockRegexp();

    Regexp* parent = new Regexp(RegexpOp::kConcat, ParseFlags::None);

    EXPECT_EQ(walker.PostVisit(re, parent, nullptr, nullptr, 1), re);

    delete re;

    delete parent;

}



TEST_F(CoalesceWalkerTest_424, PostVisitWithValidParentAndChildArgsReturnsSamePointer_424) {

    Regexp* re = CreateMockRegexp();

    Regexp* parent = new Regexp(RegexpOp::kConcat, ParseFlags::None);

    Regexp** child_args = new Regexp*[1];

    child_args[0] = re;

    EXPECT_EQ(walker.PostVisit(re, parent, nullptr, child_args, 1), re);

    delete re;

    delete[] child_args;

    delete parent;

}
