// File: tests/vector_contains_matcher_978_tests.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <type_traits>

#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Matchers::VectorContains;

class VectorContainsTest_978 : public ::testing::Test {};

// --- Type traits / basic properties (no behavior inference) ---
TEST_F(VectorContainsTest_978, MatcherType_IsCopyableAndMovable_978) {
    auto m = VectorContains<int>(42);
    static_assert(std::is_copy_constructible<decltype(m)>::value,
                  "Matcher should be copy-constructible");
    static_assert(std::is_move_constructible<decltype(m)>::value,
                  "Matcher should be move-constructible");
    SUCCEED(); // compile-time checks are the point of this test
}

// --- Normal operation ---
TEST_F(VectorContainsTest_978, ContainsElement_ReturnsTrueWhenPresent_978) {
    auto m = VectorContains<int>(5);
    const std::vector<int> v{1, 5, 3};
    EXPECT_TRUE(m.match(v));
}

TEST_F(VectorContainsTest_978, ContainsElement_ReturnsFalseWhenAbsent_978) {
    auto m = VectorContains<int>(99);
    const std::vector<int> v{1, 5, 3};
    EXPECT_FALSE(m.match(v));
}

// --- Boundary conditions ---
TEST_F(VectorContainsTest_978, EmptyVector_ReturnsFalse_978) {
    auto m = VectorContains<int>(7);
    const std::vector<int> v;
    EXPECT_FALSE(m.match(v));
}

TEST_F(VectorContainsTest_978, SingleElementVector_MatchAndNoMatch_978) {
    {
        auto m = VectorContains<int>(10);
        const std::vector<int> v{10};
        EXPECT_TRUE(m.match(v));
    }
    {
        auto m = VectorContains<int>(11);
        const std::vector<int> v{10};
        EXPECT_FALSE(m.match(v));
    }
}

TEST_F(VectorContainsTest_978, MultipleOccurrences_StillReturnsTrue_978) {
    auto m = VectorContains<int>(2);
    const std::vector<int> v{2, 2, 2};
    EXPECT_TRUE(m.match(v));
}

// --- Type variations / const-correctness ---
TEST_F(VectorContainsTest_978, WorksWithStrings_978) {
    auto m = VectorContains<std::string>(std::string{"alpha"});
    const std::vector<std::string> v{"alpha", "beta", "gamma"};
    EXPECT_TRUE(m.match(v));
}

TEST_F(VectorContainsTest_978, WorksWithConstVector_978) {
    auto m = VectorContains<int>(3);
    const std::vector<int> v{1, 2, 3, 4};
    // Ensure it compiles and works when passing a const-qualified container
    EXPECT_TRUE(m.match(v));
}

// --- Description (observable text; do not depend on exact wording) ---
TEST_F(VectorContainsTest_978, Describe_IsNonEmpty_978) {
    auto m = VectorContains<int>(123);
    const std::string desc = m.describe();
    // Only verify it provides *some* description (no assumptions about exact text)
    EXPECT_FALSE(desc.empty());
}
