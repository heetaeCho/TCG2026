#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <array>
#include <deque>
#include <functional>

// Include the Catch2 amalgamated header for the ContainsElementMatcher
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// Helper: default equality predicate (std::equal_to)
using namespace Catch::Matchers;

// ============================================================
// Tests for ContainsElementMatcher
// ============================================================

class ContainsElementMatcherTest_949 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// --- Normal Operation Tests ---

TEST_F(ContainsElementMatcherTest_949, MatchFindsExistingElementInVector_949) {
    auto matcher = ContainsElementMatcher<int, std::equal_to<>>(3, std::equal_to<>{});
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsElementMatcherTest_949, MatchReturnsFalseWhenElementNotInVector_949) {
    auto matcher = ContainsElementMatcher<int, std::equal_to<>>(10, std::equal_to<>{});
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(ContainsElementMatcherTest_949, MatchFindsStringInVectorOfStrings_949) {
    auto matcher = ContainsElementMatcher<std::string, std::equal_to<>>(std::string("hello"), std::equal_to<>{});
    std::vector<std::string> v = {"world", "hello", "foo"};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsElementMatcherTest_949, MatchReturnsFalseForMissingString_949) {
    auto matcher = ContainsElementMatcher<std::string, std::equal_to<>>(std::string("bar"), std::equal_to<>{});
    std::vector<std::string> v = {"world", "hello", "foo"};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(ContainsElementMatcherTest_949, MatchWorksWithList_949) {
    auto matcher = ContainsElementMatcher<int, std::equal_to<>>(42, std::equal_to<>{});
    std::list<int> lst = {10, 20, 42, 50};
    EXPECT_TRUE(matcher.match(lst));
}

TEST_F(ContainsElementMatcherTest_949, MatchWorksWithSet_949) {
    auto matcher = ContainsElementMatcher<int, std::equal_to<>>(7, std::equal_to<>{});
    std::set<int> s = {1, 3, 5, 7, 9};
    EXPECT_TRUE(matcher.match(s));
}

TEST_F(ContainsElementMatcherTest_949, MatchWorksWithDeque_949) {
    auto matcher = ContainsElementMatcher<double, std::equal_to<>>(3.14, std::equal_to<>{});
    std::deque<double> d = {1.0, 2.0, 3.14, 4.0};
    EXPECT_TRUE(matcher.match(d));
}

TEST_F(ContainsElementMatcherTest_949, MatchWorksWithArray_949) {
    auto matcher = ContainsElementMatcher<int, std::equal_to<>>(5, std::equal_to<>{});
    std::array<int, 4> arr = {2, 4, 5, 8};
    EXPECT_TRUE(matcher.match(arr));
}

// --- Boundary Conditions ---

TEST_F(ContainsElementMatcherTest_949, MatchReturnsFalseForEmptyContainer_949) {
    auto matcher = ContainsElementMatcher<int, std::equal_to<>>(1, std::equal_to<>{});
    std::vector<int> v;
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(ContainsElementMatcherTest_949, MatchFindsSingleElementInSingleElementContainer_949) {
    auto matcher = ContainsElementMatcher<int, std::equal_to<>>(42, std::equal_to<>{});
    std::vector<int> v = {42};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsElementMatcherTest_949, MatchReturnsFalseForSingleElementContainerWithDifferentValue_949) {
    auto matcher = ContainsElementMatcher<int, std::equal_to<>>(99, std::equal_to<>{});
    std::vector<int> v = {42};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(ContainsElementMatcherTest_949, MatchFindsFirstElement_949) {
    auto matcher = ContainsElementMatcher<int, std::equal_to<>>(1, std::equal_to<>{});
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsElementMatcherTest_949, MatchFindsLastElement_949) {
    auto matcher = ContainsElementMatcher<int, std::equal_to<>>(5, std::equal_to<>{});
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsElementMatcherTest_949, MatchWithDuplicateElements_949) {
    auto matcher = ContainsElementMatcher<int, std::equal_to<>>(3, std::equal_to<>{});
    std::vector<int> v = {3, 3, 3, 3};
    EXPECT_TRUE(matcher.match(v));
}

// --- Custom Equality Predicate Tests ---

TEST_F(ContainsElementMatcherTest_949, MatchWithCustomPredicate_949) {
    // Custom predicate: compare absolute values
    auto abs_eq = [](int a, int b) { return std::abs(a) == std::abs(b); };
    auto matcher = ContainsElementMatcher<int, decltype(abs_eq)>(-5, abs_eq);
    std::vector<int> v = {1, 2, 5, 4};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsElementMatcherTest_949, MatchWithCustomPredicateNotFound_949) {
    auto abs_eq = [](int a, int b) { return std::abs(a) == std::abs(b); };
    auto matcher = ContainsElementMatcher<int, decltype(abs_eq)>(-10, abs_eq);
    std::vector<int> v = {1, 2, 5, 4};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(ContainsElementMatcherTest_949, MatchWithCaseInsensitiveStringPredicate_949) {
    auto ci_eq = [](const std::string& a, const std::string& b) {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i) {
            if (std::tolower(a[i]) != std::tolower(b[i])) return false;
        }
        return true;
    };
    auto matcher = ContainsElementMatcher<std::string, decltype(ci_eq)>(std::string("HELLO"), ci_eq);
    std::vector<std::string> v = {"world", "hello", "foo"};
    EXPECT_TRUE(matcher.match(v));
}

// --- describe() Tests ---

TEST_F(ContainsElementMatcherTest_949, DescribeContainsElementText_949) {
    auto matcher = ContainsElementMatcher<int, std::equal_to<>>(42, std::equal_to<>{});
    std::string desc = matcher.describe();
    EXPECT_NE(desc.find("contains element"), std::string::npos);
    EXPECT_NE(desc.find("42"), std::string::npos);
}

TEST_F(ContainsElementMatcherTest_949, DescribeContainsStringElement_949) {
    auto matcher = ContainsElementMatcher<std::string, std::equal_to<>>(std::string("test"), std::equal_to<>{});
    std::string desc = matcher.describe();
    EXPECT_NE(desc.find("contains element"), std::string::npos);
    EXPECT_NE(desc.find("test"), std::string::npos);
}

// --- Const container tests ---

TEST_F(ContainsElementMatcherTest_949, MatchWorksWithConstVector_949) {
    auto matcher = ContainsElementMatcher<int, std::equal_to<>>(3, std::equal_to<>{});
    const std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsElementMatcherTest_949, MatchWorksWithConstVectorNotFound_949) {
    auto matcher = ContainsElementMatcher<int, std::equal_to<>>(99, std::equal_to<>{});
    const std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_FALSE(matcher.match(v));
}

// --- Edge cases with zero and negative values ---

TEST_F(ContainsElementMatcherTest_949, MatchFindsZero_949) {
    auto matcher = ContainsElementMatcher<int, std::equal_to<>>(0, std::equal_to<>{});
    std::vector<int> v = {-1, 0, 1};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsElementMatcherTest_949, MatchFindsNegativeValue_949) {
    auto matcher = ContainsElementMatcher<int, std::equal_to<>>(-5, std::equal_to<>{});
    std::vector<int> v = {-5, 0, 5};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsElementMatcherTest_949, MatchEmptyString_949) {
    auto matcher = ContainsElementMatcher<std::string, std::equal_to<>>(std::string(""), std::equal_to<>{});
    std::vector<std::string> v = {"hello", "", "world"};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsElementMatcherTest_949, MatchEmptyStringNotFound_949) {
    auto matcher = ContainsElementMatcher<std::string, std::equal_to<>>(std::string(""), std::equal_to<>{});
    std::vector<std::string> v = {"hello", "world"};
    EXPECT_FALSE(matcher.match(v));
}

// --- Large container test ---

TEST_F(ContainsElementMatcherTest_949, MatchInLargeContainer_949) {
    auto matcher = ContainsElementMatcher<int, std::equal_to<>>(99999, std::equal_to<>{});
    std::vector<int> v(100000);
    for (int i = 0; i < 100000; ++i) {
        v[i] = i;
    }
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsElementMatcherTest_949, MatchNotFoundInLargeContainer_949) {
    auto matcher = ContainsElementMatcher<int, std::equal_to<>>(100000, std::equal_to<>{});
    std::vector<int> v(100000);
    for (int i = 0; i < 100000; ++i) {
        v[i] = i;
    }
    EXPECT_FALSE(matcher.match(v));
}
