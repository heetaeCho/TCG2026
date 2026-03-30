// TEST_ID: 157
// File: test_strpair_setstr_157.cpp

#include <gtest/gtest.h>
#include <cstring>

#include "tinyxml2.h"

namespace {

class StrPairSetStrTest_157 : public ::testing::Test {
protected:
    static bool IsNullOrEmptyCStr(const char* s) {
        return (s == nullptr) || (s[0] == '\0');
    }
};

TEST_F(StrPairSetStrTest_157, SetStrStoresAndGetStrReturnsSameText_157) {
    tinyxml2::StrPair sp;

    sp.SetStr("hello", 0);
    const char* out = sp.GetStr();

    ASSERT_NE(out, nullptr);
    EXPECT_STREQ(out, "hello");
    EXPECT_FALSE(sp.Empty());
}

TEST_F(StrPairSetStrTest_157, SetStrWithEmptyStringReturnsEmptyString_157) {
    tinyxml2::StrPair sp;

    sp.SetStr("", 0);
    const char* out = sp.GetStr();

    // Observable boundary: the resulting string content should be empty.
    ASSERT_NE(out, nullptr);
    EXPECT_STREQ(out, "");
    EXPECT_EQ(std::strlen(out), static_cast<size_t>(0));
    // Don't assert Empty() here; implementations may treat empty as empty/nonnull differently.
}

TEST_F(StrPairSetStrTest_157, ResetAfterSetStrMakesPairEmpty_157) {
    tinyxml2::StrPair sp;

    sp.SetStr("abc", 0);
    ASSERT_NE(sp.GetStr(), nullptr);
    ASSERT_STREQ(sp.GetStr(), "abc");

    sp.Reset();

    EXPECT_TRUE(sp.Empty());
    const char* out = sp.GetStr();
    // Some implementations may return nullptr after reset; others may return "".
    EXPECT_TRUE(IsNullOrEmptyCStr(out));
}

TEST_F(StrPairSetStrTest_157, SetStrCalledTwiceOverwritesPreviousValue_157) {
    tinyxml2::StrPair sp;

    sp.SetStr("first", 0);
    ASSERT_NE(sp.GetStr(), nullptr);
    EXPECT_STREQ(sp.GetStr(), "first");

    sp.SetStr("second", 0);
    const char* out = sp.GetStr();

    ASSERT_NE(out, nullptr);
    EXPECT_STREQ(out, "second");
}

TEST_F(StrPairSetStrTest_157, TransferToMovesStringToOther_157) {
    tinyxml2::StrPair a;
    tinyxml2::StrPair b;

    a.SetStr("moved", 0);
    ASSERT_NE(a.GetStr(), nullptr);
    ASSERT_STREQ(a.GetStr(), "moved");

    a.TransferTo(&b);

    const char* bout = b.GetStr();
    ASSERT_NE(bout, nullptr);
    EXPECT_STREQ(bout, "moved");

    // After transfer, the source should be observably empty.
    EXPECT_TRUE(a.Empty());
    const char* aout = a.GetStr();
    EXPECT_TRUE(IsNullOrEmptyCStr(aout));
}

TEST_F(StrPairSetStrTest_157, TransferToOnEmptySourceLeavesOtherEmptyOrUnchanged_157) {
    tinyxml2::StrPair a;
    tinyxml2::StrPair b;

    // Put something into b first to observe behavior if implementation overwrites/clears.
    b.SetStr("keep", 0);
    ASSERT_NE(b.GetStr(), nullptr);
    ASSERT_STREQ(b.GetStr(), "keep");

    // a is empty; transferring should not crash and should leave both in valid states.
    EXPECT_NO_THROW(a.TransferTo(&b));

    // We can only assert "valid string state" for b (either unchanged or emptied by design).
    const char* bout = b.GetStr();
    EXPECT_TRUE(bout == nullptr || bout[0] == '\0' || std::strcmp(bout, "keep") == 0);

    EXPECT_TRUE(a.Empty());
}

#if GTEST_HAS_DEATH_TEST
TEST_F(StrPairSetStrTest_157, SetStrWithNullptrTriggersAssertDeath_157) {
    tinyxml2::StrPair sp;

    // SetStr has TIXMLASSERT(str); treat as a contract violation.
    EXPECT_DEATH_IF_SUPPORTED(sp.SetStr(nullptr, 0), "");
}
#endif

}  // namespace
