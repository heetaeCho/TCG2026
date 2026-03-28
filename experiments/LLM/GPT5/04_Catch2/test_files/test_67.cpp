// MessageInfo_less_than_tests_67.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_message_info.hpp"

using namespace Catch;

// Helper to construct MessageInfo objects without relying on internal state.
// We vary the SourceLineInfo to avoid any accidental deduplication, but we
// never assert on it—only on observable comparison behavior.
static MessageInfo makeMsg(const char* file, int line) {
    // Choose any valid ResultWas::OfType; its specific value is irrelevant
    // for operator< behavior (treated as a black box).
    return MessageInfo(StringRef("MACRO_67"), SourceLineInfo(file, line),
                       ResultWas::OfType::Ok);
}

class MessageInfoTest_67 : public ::testing::Test {};

// Earlier construction has a smaller sequence → should compare less-than
TEST_F(MessageInfoTest_67, EarlierConstructionIsLess_67) {
    auto m1 = makeMsg(__FILE__, __LINE__);
    auto m2 = makeMsg(__FILE__, __LINE__ + 1);

    EXPECT_TRUE(m1 < m2);
    EXPECT_FALSE(m2 < m1);
}

// Copying preserves identity for ordering: neither is less than the other
TEST_F(MessageInfoTest_67, CopyHasSameOrderRelation_67) {
    auto original = makeMsg(__FILE__, __LINE__);
    auto copy = original; // copy-construct

    EXPECT_FALSE(original < copy);
    EXPECT_FALSE(copy < original);
}

// Transitivity: if a < b and b < c, then a < c
TEST_F(MessageInfoTest_67, StrictWeakOrdering_Transitive_67) {
    auto a = makeMsg(__FILE__, __LINE__);
    auto b = makeMsg(__FILE__, __LINE__ + 1);
    auto c = makeMsg(__FILE__, __LINE__ + 2);

    ASSERT_TRUE(a < b);
    ASSERT_TRUE(b < c);
    EXPECT_TRUE(a < c);
}

// Antisymmetry (as expected for a strict-weak-ordered comparator):
// if a < b then !(b < a)
TEST_F(MessageInfoTest_67, StrictWeakOrdering_AntiSymmetry_67) {
    auto a = makeMsg(__FILE__, __LINE__);
    auto b = makeMsg(__FILE__, __LINE__ + 1);

    ASSERT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}
