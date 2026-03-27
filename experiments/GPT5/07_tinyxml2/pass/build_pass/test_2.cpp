// File: TestProjects/tinyxml2/strpair_empty_test_2.cpp

#include "gtest/gtest.h"
#include "tinyxml2.h"

namespace {

class StrPairTest_2 : public ::testing::Test {
protected:
    tinyxml2::StrPair p;
};

TEST_F(StrPairTest_2, DefaultConstructedIsEmpty_2) {
    EXPECT_TRUE(p.Empty());
}

TEST_F(StrPairTest_2, SetWithSameStartAndEndIsEmpty_2) {
    char buf[] = "abc";
    p.Set(buf, buf, 0);
    EXPECT_TRUE(p.Empty());
}

TEST_F(StrPairTest_2, SetWithDifferentStartAndEndIsNotEmpty_2) {
    char buf[] = "abc";
    p.Set(buf, buf + 3, 0);
    EXPECT_FALSE(p.Empty());
}

TEST_F(StrPairTest_2, ResetMakesEmptyAfterNonEmpty_2) {
    char buf[] = "abc";
    p.Set(buf, buf + 3, 0);
    ASSERT_FALSE(p.Empty());

    p.Reset();
    EXPECT_TRUE(p.Empty());
}

TEST_F(StrPairTest_2, EmptyIsConstAndDoesNotModifyState_2) {
    char buf[] = "abc";
    p.Set(buf, buf + 3, 0);

    const tinyxml2::StrPair& cref = p;
    const bool first = cref.Empty();
    const bool second = cref.Empty();

    EXPECT_EQ(first, second);
}

}  // namespace
