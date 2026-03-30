// File: none_true_matcher_tests_183.cpp

#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <list>
#include <cstddef> // for nullptr_t
#include "catch2/matchers/catch_matchers_quantifiers.hpp"

using Catch::Matchers::NoneTrueMatcher;

namespace {

// Simple alias to keep names tidy in test bodies
bool MatchNoneTrue(auto&& range) {
    NoneTrueMatcher matcher;
    return matcher.match(std::forward<decltype(range)>(range));
}

} // namespace

// ----- Boundary cases -----

TEST(NoneTrueMatcherTest_183, EmptyRange_ReturnsTrue_183) {
    std::vector<int> empty;
    EXPECT_TRUE(MatchNoneTrue(empty));
}

TEST(NoneTrueMatcherTest_183, SingleFalseElement_ReturnsTrue_183) {
    std::array<bool, 1> a{false};
    EXPECT_TRUE(MatchNoneTrue(a));
}

TEST(NoneTrueMatcherTest_183, SingleTrueElement_ReturnsFalse_183) {
    std::array<bool, 1> a{true};
    EXPECT_FALSE(MatchNoneTrue(a));
}

// ----- Normal operation -----

TEST(NoneTrueMatcherTest_183, AllFalse_ReturnsTrue_183) {
    std::vector<int> vals{0, 0, 0, 0};
    EXPECT_TRUE(MatchNoneTrue(vals));
}

TEST(NoneTrueMatcherTest_183, ContainsTrue_ReturnsFalse_183) {
    std::vector<int> vals{0, 0, 1, 0};
    EXPECT_FALSE(MatchNoneTrue(vals));
}

TEST(NoneTrueMatcherTest_183, AllTrue_ReturnsFalse_183) {
    std::list<int> vals{1, 2, 3};
    EXPECT_FALSE(MatchNoneTrue(vals));
}

// ----- Type/usage variations (still black-box observable behavior) -----

TEST(NoneTrueMatcherTest_183, WorksWithInitializerList_AllFalse_True_183) {
    EXPECT_TRUE(MatchNoneTrue({false, false, false}));
}

TEST(NoneTrueMatcherTest_183, WorksWithInitializerList_Mixed_False_183) {
    EXPECT_FALSE(MatchNoneTrue({false, true, false}));
}

TEST(NoneTrueMatcherTest_183, WorksWithRvalueTemporaryRange_183) {
    // Passing a temporary rvalue container
    EXPECT_TRUE(MatchNoneTrue(std::vector<int>{0, 0, 0}));
    EXPECT_FALSE(MatchNoneTrue(std::vector<int>{0, 2, 0}));
}

TEST(NoneTrueMatcherTest_183, WorksWithPointerElements_AllNull_True_183) {
    std::vector<const char*> ptrs{nullptr, nullptr};
    EXPECT_TRUE(MatchNoneTrue(ptrs));
}

TEST(NoneTrueMatcherTest_183, WorksWithPointerElements_Mixed_False_183) {
    const char a = 'x';
    std::vector<const void*> ptrs{nullptr, &a, nullptr};
    EXPECT_FALSE(MatchNoneTrue(ptrs));
}

TEST(NoneTrueMatcherTest_183, WorksWithStdArray_Empty_ReturnsTrue_183) {
    std::array<int, 0> arr{};
    EXPECT_TRUE(MatchNoneTrue(arr));
}

