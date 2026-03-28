// AllMatchMatcher_test_176.cpp
#include <gtest/gtest.h>
#include "catch2/matchers/catch_matchers_quantifiers.hpp"

using Catch::Matchers::AllMatchMatcher;

// ----- Helper “matchers” used as collaborators for AllMatchMatcher -----
// These are simple value matchers with the minimal interface required
// by AllMatchMatcher: `bool match(const T&) const` and `std::string describe() const`.

struct AlwaysTrueMatcher {
    std::string describe() const { return "always true"; }
    template <typename T>
    bool match(const T&) const { return true; }
};

struct AlwaysFalseMatcher {
    std::string describe() const { return "always false"; }
    template <typename T>
    bool match(const T&) const { return false; }
};

struct IsEvenMatcher {
    std::string describe() const { return "is even"; }
    bool match(int v) const { return v % 2 == 0; }
};

class AllMatchMatcherTest_176 : public ::testing::Test {};

// ----------------------------- Tests -----------------------------

// Verifies that describe() prefixes the inner description with "all match ".
TEST_F(AllMatchMatcherTest_176, DescribePrefixesInnerDescription_176) {
    AlwaysTrueMatcher inner{};
    AllMatchMatcher<AlwaysTrueMatcher> under_test(inner);

    EXPECT_EQ(under_test.describe(), std::string("all match ") + inner.describe());
}

// Normal case: all elements satisfy the inner matcher -> match() returns true.
TEST_F(AllMatchMatcherTest_176, Match_AllElementsSatisfy_ReturnsTrue_176) {
    IsEvenMatcher inner{};
    AllMatchMatcher<IsEvenMatcher> under_test(inner);

    std::vector<int> vals{2, 4, 6, 8};
    EXPECT_TRUE(under_test.match(vals));
}

// Error/exceptional observable behavior via interface: if any element does not satisfy,
// overall match should be false (observable outcome).
TEST_F(AllMatchMatcherTest_176, Match_AnyElementFails_ReturnsFalse_176) {
    IsEvenMatcher inner{};
    AllMatchMatcher<IsEvenMatcher> under_test(inner);

    std::vector<int> vals{2, 3, 4};
    EXPECT_FALSE(under_test.match(vals));
}

// Boundary condition: empty range. For an "all" quantifier, the usual observable
// contract is that an empty set vacuously satisfies the predicate -> true.
TEST_F(AllMatchMatcherTest_176, Match_EmptyRange_ReturnsTrue_176) {
    AlwaysFalseMatcher inner{};  // Even with an always-false inner, empty range has no failing element.
    AllMatchMatcher<AlwaysFalseMatcher> under_test(inner);

    std::vector<int> empty{};
    EXPECT_TRUE(under_test.match(empty));
}

// Template/Rangelike coverage: works with different range-like types (e.g., initializer_list).
TEST_F(AllMatchMatcherTest_176, Match_InitializerListRange_Works_176) {
    AlwaysTrueMatcher inner{};
    AllMatchMatcher<AlwaysTrueMatcher> under_test(inner);

    EXPECT_TRUE(under_test.match({1, 2, 3, 4}));
}
