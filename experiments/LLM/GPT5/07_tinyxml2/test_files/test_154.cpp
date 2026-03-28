// TEST_ID: 154
// File: test_strpair_154.cpp

#include <gtest/gtest.h>
#include <cstring>
#include <string>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class StrPairTest_154 : public ::testing::Test {
protected:
    StrPair sp_;
};

static std::string SafeCStrToString_154(const char* s) {
    return s ? std::string(s) : std::string();
}

} // namespace

TEST_F(StrPairTest_154, DefaultConstructedIsEmpty_154) {
    EXPECT_TRUE(sp_.Empty());
    // GetStr() may return nullptr or empty string depending on implementation;
    // we only require it to be safe to call.
    EXPECT_NO_FATAL_FAILURE((void)sp_.GetStr());
}

TEST_F(StrPairTest_154, SetStrWithNormalStringMakesNonEmptyAndGetStrMatches_154) {
    sp_.SetStr("abc", 0);
    EXPECT_FALSE(sp_.Empty());
    EXPECT_EQ(SafeCStrToString_154(sp_.GetStr()), "abc");
}

TEST_F(StrPairTest_154, SetStrWithEmptyStringIsHandled_154) {
    sp_.SetStr("", 0);
    // Some implementations may consider this empty, others may store an empty string;
    // require that calls are safe and observable state is consistent.
    EXPECT_NO_FATAL_FAILURE((void)sp_.GetStr());
    // Empty() should be logically consistent with GetStr() content if non-null.
    const std::string got = SafeCStrToString_154(sp_.GetStr());
    if (!got.empty()) {
        EXPECT_FALSE(sp_.Empty());
    }
}

TEST_F(StrPairTest_154, ResetMakesEmptyAndGetStrSafe_154) {
    sp_.SetStr("abc", 0);
    ASSERT_FALSE(sp_.Empty());

    sp_.Reset();
    EXPECT_TRUE(sp_.Empty());
    EXPECT_NO_FATAL_FAILURE((void)sp_.GetStr());
}

TEST_F(StrPairTest_154, ResetIsIdempotent_154) {
    sp_.Reset();
    EXPECT_TRUE(sp_.Empty());
    EXPECT_NO_FATAL_FAILURE((void)sp_.GetStr());

    sp_.Reset();
    EXPECT_TRUE(sp_.Empty());
    EXPECT_NO_FATAL_FAILURE((void)sp_.GetStr());
}

TEST_F(StrPairTest_154, TransferToCopiesOrMovesContentToOther_154) {
    sp_.SetStr("payload", 0);
    ASSERT_FALSE(sp_.Empty());

    StrPair other;
    other.SetStr("other", 0);

    sp_.TransferTo(&other);

    // Observable requirement: destination should now reflect the source payload.
    EXPECT_EQ(SafeCStrToString_154(other.GetStr()), "payload");

    // Source may be emptied after transfer (move) or left valid (copy).
    // We only require that it's still safe to query and in a valid state.
    EXPECT_NO_FATAL_FAILURE((void)sp_.Empty());
    EXPECT_NO_FATAL_FAILURE((void)sp_.GetStr());
}

TEST_F(StrPairTest_154, TransferToNullptrDoesNotCrash_154) {
    sp_.SetStr("payload", 0);
    EXPECT_NO_FATAL_FAILURE(sp_.TransferTo(nullptr));
    // Object should remain in a valid state.
    EXPECT_NO_FATAL_FAILURE((void)sp_.Empty());
    EXPECT_NO_FATAL_FAILURE((void)sp_.GetStr());
}

TEST_F(StrPairTest_154, ParseNameParsesSimpleNameAndAdvancesPointer_154) {
    char input[] = "tagName attr='v'";
    char* p = input;

    char* after = sp_.ParseName(p);

    ASSERT_NE(after, nullptr);
    EXPECT_GT(after, p); // should have advanced
    EXPECT_EQ(SafeCStrToString_154(sp_.GetStr()), "tagName");
    // The next character should be a separator (space in this input).
    EXPECT_EQ(*after, ' ');
}

TEST_F(StrPairTest_154, ParseNameWithNonNameStartReturnsNullOrNoAdvance_154) {
    char input[] = "  leadingSpace";
    char* p = input;

    char* after = sp_.ParseName(p);

    // We don't assume exact semantics; require safe behavior.
    // If it returns nullptr, that's acceptable; if it returns p (no advance), also acceptable.
    if (after) {
        EXPECT_EQ(after, p) << "If ParseName doesn't accept leading whitespace, it may not advance.";
    }
    EXPECT_NO_FATAL_FAILURE((void)sp_.GetStr());
}

TEST_F(StrPairTest_154, DestructorAfterSetStrDoesNotCrash_154) {
    // Destructor is expected to be safe and release/reset internal state.
    EXPECT_NO_FATAL_FAILURE({
        StrPair local;
        local.SetStr("abc", 0);
        (void)local.GetStr();
    });
}

TEST_F(StrPairTest_154, LargeStringSetStrRoundTrips_154) {
    std::string big(4096, 'x');
    sp_.SetStr(big.c_str(), 0);
    EXPECT_FALSE(sp_.Empty());
    EXPECT_EQ(SafeCStrToString_154(sp_.GetStr()), big);
}
