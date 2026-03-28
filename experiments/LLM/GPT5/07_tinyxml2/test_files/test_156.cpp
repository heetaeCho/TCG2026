// File: test_strpair_reset_156.cpp

#include <gtest/gtest.h>
#include <cstring>
#include <cstdlib>

#include "tinyxml2.h"

namespace {

constexpr int kNeedsDelete_156 = 512;  // From tinyxml2.h enum: NEEDS_DELETE = 512

class StrPairResetTest_156 : public ::testing::Test {
protected:
    tinyxml2::StrPair p_;
};

}  // namespace

TEST_F(StrPairResetTest_156, DefaultConstructedIsEmpty_156) {
    EXPECT_TRUE(p_.Empty());
}

TEST_F(StrPairResetTest_156, ResetOnDefaultConstructedKeepsEmpty_156) {
    p_.Reset();
    EXPECT_TRUE(p_.Empty());
}

TEST_F(StrPairResetTest_156, ResetIsIdempotent_156) {
    p_.Reset();
    EXPECT_TRUE(p_.Empty());

    p_.Reset();
    EXPECT_TRUE(p_.Empty());
}

TEST_F(StrPairResetTest_156, ResetAfterSetStrClearsToEmpty_156) {
    p_.SetStr("abc", /*flags*/ 0);
    // We don't assume how GetStr() behaves; only check observable Empty().
    EXPECT_FALSE(p_.Empty());

    p_.Reset();
    EXPECT_TRUE(p_.Empty());
}

TEST_F(StrPairResetTest_156, ResetAfterSetWithExternalBufferClearsToEmpty_156) {
    // Use malloc/free so StrPair should not be responsible for deleting this memory.
    char* buf = static_cast<char*>(std::malloc(8));
    ASSERT_NE(buf, nullptr);
    std::strcpy(buf, "hello");

    // Set start/end to cover "hello"
    p_.Set(buf, buf + 5, /*flags*/ 0);
    EXPECT_FALSE(p_.Empty());

    p_.Reset();
    EXPECT_TRUE(p_.Empty());

    std::free(buf);
}

TEST_F(StrPairResetTest_156, ResetAfterSetWithNeedsDeleteDoesNotCrashAndClears_156) {
    // Allocate with new[] and mark NEEDS_DELETE so Reset() is responsible for cleanup.
    char* buf = new char[4];
    std::strcpy(buf, "abc");

    p_.Set(buf, buf + 3, kNeedsDelete_156);
    EXPECT_FALSE(p_.Empty());

    // If Reset() correctly handles deletion, this should be safe (no crash).
    p_.Reset();
    EXPECT_TRUE(p_.Empty());

    // Do NOT delete buf here: ownership was given to StrPair via NEEDS_DELETE.
}

TEST_F(StrPairResetTest_156, CanReuseAfterReset_156) {
    p_.SetStr("first", /*flags*/ 0);
    EXPECT_FALSE(p_.Empty());

    p_.Reset();
    EXPECT_TRUE(p_.Empty());

    p_.SetStr("second", /*flags*/ 0);
    EXPECT_FALSE(p_.Empty());

    p_.Reset();
    EXPECT_TRUE(p_.Empty());
}
