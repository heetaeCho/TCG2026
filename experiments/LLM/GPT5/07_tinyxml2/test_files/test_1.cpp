// File: ./TestProjects/tinyxml2/StrPair_set_test_1.cpp

#include <gtest/gtest.h>
#include <cstring>

#include "tinyxml2.h"

namespace {

class StrPairSetTest_1 : public ::testing::Test {
protected:
    tinyxml2::StrPair sp;
};

TEST_F(StrPairSetTest_1, SetWithValidRange_GetStrMatchesRangeAndNotEmpty_1) {
    char buf[] = "abc";
    sp.Set(buf, buf + 3, 0);

    EXPECT_FALSE(sp.Empty());
    const char* out = sp.GetStr();
    ASSERT_NE(out, nullptr);
    EXPECT_STREQ("abc", out);
}

TEST_F(StrPairSetTest_1, SetWithEmptyRange_EmptyTrueAndGetStrIsEmptyString_1) {
    char buf[] = "x"; // any non-null storage; use start==end to represent empty range
    sp.Set(buf, buf, 0);

    EXPECT_TRUE(sp.Empty());
    const char* out = sp.GetStr();
    ASSERT_NE(out, nullptr);
    EXPECT_STREQ("", out);
}

TEST_F(StrPairSetTest_1, ResetAfterSet_MakesEmpty_1) {
    char buf[] = "hello";
    sp.Set(buf, buf + 5, 0);
    ASSERT_FALSE(sp.Empty());

    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairSetTest_1, TransferTo_MovesContentToOther_1) {
    char buf[] = "move";
    sp.Set(buf, buf + 4, 0);

    tinyxml2::StrPair other;
    sp.TransferTo(&other);

    EXPECT_TRUE(sp.Empty());
    EXPECT_FALSE(other.Empty());

    const char* out = other.GetStr();
    ASSERT_NE(out, nullptr);
    EXPECT_STREQ("move", out);
}

TEST_F(StrPairSetTest_1, SetCalledTwice_SecondCallWins_1) {
    char a[] = "first";
    char b[] = "second";

    sp.Set(a, a + 5, 0);
    EXPECT_STREQ("first", sp.GetStr());

    sp.Set(b, b + 6, 0);
    EXPECT_STREQ("second", sp.GetStr());
}

#if defined(DEBUG) || defined(_DEBUG) || defined(__DEBUG__)
TEST_F(StrPairSetTest_1, SetWithNullStart_TriggersAssertionInDebug_1) {
    char buf[] = "x";
    EXPECT_DEATH(
        {
            tinyxml2::StrPair local;
            local.Set(nullptr, buf, 0);
        },
        ""
    );
}

TEST_F(StrPairSetTest_1, SetWithNullEnd_TriggersAssertionInDebug_1) {
    char buf[] = "x";
    EXPECT_DEATH(
        {
            tinyxml2::StrPair local;
            local.Set(buf, nullptr, 0);
        },
        ""
    );
}
#endif

} // namespace
