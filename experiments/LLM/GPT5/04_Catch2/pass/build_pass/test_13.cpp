// File: tests/stringref_literal_sr_tests.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include "catch2/internal/catch_stringref.hpp"

using Catch::operator""_sr;

class StringRefLiteralTest_13 : public ::testing::Test {};

// Verifies the literal's return type is Catch::StringRef at compile time.
TEST_F(StringRefLiteralTest_13, ReturnsStringRefType_13) {
    static_assert(std::is_same<decltype("x"_sr), Catch::StringRef>::value,
                  "The _sr literal must return Catch::StringRef");
    SUCCEED(); // Keeps the test visible in runtime results.
}

// Empty literal should produce an empty StringRef (size 0, empty()).
TEST_F(StringRefLiteralTest_13, EmptyLiteralYieldsEmpty_13) {
    auto ref = ""_sr;
    EXPECT_EQ(ref.size(), 0u);
    EXPECT_TRUE(ref.empty());
}

// The size must match the literal length (no implicit null terminator included).
TEST_F(StringRefLiteralTest_13, SizeMatchesLiteralLength_13) {
    auto ref1 = "a"_sr;
    EXPECT_EQ(ref1.size(), sizeof("a") - 1);

    auto ref2 = "hello"_sr;
    EXPECT_EQ(ref2.size(), sizeof("hello") - 1);

    auto ref3 = "hello world"_sr;
    EXPECT_EQ(ref3.size(), sizeof("hello world") - 1);
}

// Content accessible via iterators should match the literal's characters.
TEST_F(StringRefLiteralTest_13, IterationYieldsSameContent_13) {
    constexpr const char* kText = "Catch2_StringRef";
    auto ref = "Catch2_StringRef"_sr;

    std::string reconstructed(ref.begin(), ref.end());
    EXPECT_EQ(reconstructed, kText);
    EXPECT_EQ(reconstructed.size(), ref.size());
}

// Different literals should not compare equal (observable difference).
TEST_F(StringRefLiteralTest_13, DifferentLiteralsAreNotEqual_13) {
    auto a = "cat"_sr;
    auto b = "cats"_sr;

    // Prefer observable behavior; size differs and content differs.
    EXPECT_NE(a.size(), b.size());
    // If operator== is available, also check inequality without relying on internals.
    // Using ASSERT_* to avoid cascading failures if sizes are equal by mistake.
    // Note: This line is safe only if operator== is part of the public interface.
    // If not, comment it out.
    // EXPECT_NE(a, b);
}

// Boundary-style check with a longer literal to ensure proper sizing.
TEST_F(StringRefLiteralTest_13, LongLiteralSizeConsistency_13) {
    auto ref = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"_sr;
    EXPECT_EQ(ref.size(), sizeof("abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ") - 1);

    // Spot-check first and last characters via iteration (observable behavior).
    ASSERT_FALSE(ref.empty());
    const char first = *ref.begin();
    const char last = *(ref.end() - 1);
    EXPECT_EQ(first, 'a');
    EXPECT_EQ(last, 'Z');
}
