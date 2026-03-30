// File: StrPair_setinternedstr_test_3.cpp

#include <gtest/gtest.h>
#include <cstring>

#include "TestProjects/tinyxml2/tinyxml2.h"

using tinyxml2::StrPair;

class StrPairSetInternedStrTest_3 : public ::testing::Test {
protected:
    StrPair sp;
};

TEST_F(StrPairSetInternedStrTest_3, DefaultConstructedIsEmpty_3) {
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairSetInternedStrTest_3, SetInternedStrSetsReadableString_3) {
    const char* input = "abc";

    sp.SetInternedStr(input);

    const char* out = sp.GetStr();
    ASSERT_NE(out, nullptr);
    EXPECT_STREQ(out, "abc");
    EXPECT_FALSE(sp.Empty());
}

TEST_F(StrPairSetInternedStrTest_3, SetInternedStrWithEmptyCStringIsReadable_3) {
    const char* input = "";

    sp.SetInternedStr(input);

    const char* out = sp.GetStr();
    ASSERT_NE(out, nullptr);
    EXPECT_STREQ(out, "");
}

TEST_F(StrPairSetInternedStrTest_3, SetInternedStrCanBeCalledMultipleTimes_3) {
    sp.SetInternedStr("first");
    EXPECT_STREQ(sp.GetStr(), "first");

    sp.SetInternedStr("second");
    EXPECT_STREQ(sp.GetStr(), "second");
}

TEST_F(StrPairSetInternedStrTest_3, ResetAfterSetInternedStrResultsInEmptyOrEmptyString_3) {
    sp.SetInternedStr("value");
    ASSERT_FALSE(sp.Empty());

    sp.Reset();

    EXPECT_TRUE(sp.Empty());

    // GetStr() behavior after Reset() may vary (nullptr vs empty string). Accept either.
    const char* out = sp.GetStr();
    EXPECT_TRUE(out == nullptr || out[0] == '\0');
}

TEST_F(StrPairSetInternedStrTest_3, TransferToAfterSetInternedStrMovesObservableString_3) {
    StrPair other;

    sp.SetInternedStr("moved");
    ASSERT_FALSE(sp.Empty());

    sp.TransferTo(&other);

    EXPECT_STREQ(other.GetStr(), "moved");
    EXPECT_FALSE(other.Empty());

    // Source should become empty after transfer.
    EXPECT_TRUE(sp.Empty());
    const char* out = sp.GetStr();
    EXPECT_TRUE(out == nullptr || out[0] == '\0');
}

TEST_F(StrPairSetInternedStrTest_3, TransferToNullptrDoesNotCrash_3) {
    // Observable behavior may be "no-op" or an assert in debug builds.
    // This test verifies at least it is safe in the current build configuration.
    sp.SetInternedStr("keep");
    EXPECT_NO_THROW(sp.TransferTo(nullptr));

    // Ensure original object is still in a valid observable state.
    const char* out = sp.GetStr();
    ASSERT_NE(out, nullptr);
    EXPECT_STREQ(out, "keep");
}
