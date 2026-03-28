#include <vector>
#include <string>
#include <list>
#include <array>
#include <set>
#include <functional>

// Include Catch2's amalgamated header for the matchers
#define CATCH_CONFIG_MAIN
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

#include <gtest/gtest.h>

class ContainsElementMatcherTest_955 : public ::testing::Test {
protected:
    // Custom equality comparator
    struct CaseInsensitiveEqual {
        bool operator()(const std::string& a, const std::string& b) const {
            if (a.size() != b.size()) return false;
            for (size_t i = 0; i < a.size(); ++i) {
                if (std::tolower(a[i]) != std::tolower(b[i])) return false;
            }
            return true;
        }
    };

    struct ApproxEqual {
        double tolerance;
        bool operator()(double a, double b) const {
            return std::abs(a - b) < tolerance;
        }
    };

    struct AlwaysTrue {
        bool operator()(int, int) const { return true; }
    };

    struct AlwaysFalse {
        bool operator()(int, int) const { return false; }
    };
};

// Test: Contains with custom equality finds an existing element
TEST_F(ContainsElementMatcherTest_955, MatchesWhenElementExistsWithCustomEquality_955) {
    std::vector<std::string> vec = {"Hello", "World", "Foo"};
    auto matcher = Catch::Matchers::Contains(std::string("hello"), CaseInsensitiveEqual{});
    EXPECT_TRUE(matcher.match(vec));
}

// Test: Contains with custom equality does not match when element is absent
TEST_F(ContainsElementMatcherTest_955, DoesNotMatchWhenElementAbsentWithCustomEquality_955) {
    std::vector<std::string> vec = {"Hello", "World", "Foo"};
    auto matcher = Catch::Matchers::Contains(std::string("bar"), CaseInsensitiveEqual{});
    EXPECT_FALSE(matcher.match(vec));
}

// Test: Contains with approximate equality for doubles
TEST_F(ContainsElementMatcherTest_955, MatchesWithApproximateEquality_955) {
    std::vector<double> vec = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::Contains(2.0001, ApproxEqual{0.001});
    EXPECT_TRUE(matcher.match(vec));
}

// Test: Contains with approximate equality that doesn't match
TEST_F(ContainsElementMatcherTest_955, DoesNotMatchWhenOutsideTolerance_955) {
    std::vector<double> vec = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::Contains(2.5, ApproxEqual{0.001});
    EXPECT_FALSE(matcher.match(vec));
}

// Test: Empty container never matches
TEST_F(ContainsElementMatcherTest_955, EmptyContainerDoesNotMatch_955) {
    std::vector<int> vec = {};
    auto matcher = Catch::Matchers::Contains(42, AlwaysTrue{});
    EXPECT_FALSE(matcher.match(vec));
}

// Test: AlwaysTrue equality matches first element in non-empty container
TEST_F(ContainsElementMatcherTest_955, AlwaysTrueMatchesNonEmptyContainer_955) {
    std::vector<int> vec = {1, 2, 3};
    auto matcher = Catch::Matchers::Contains(999, AlwaysTrue{});
    EXPECT_TRUE(matcher.match(vec));
}

// Test: AlwaysFalse equality never matches
TEST_F(ContainsElementMatcherTest_955, AlwaysFalseNeverMatches_955) {
    std::vector<int> vec = {1, 2, 3};
    auto matcher = Catch::Matchers::Contains(1, AlwaysFalse{});
    EXPECT_FALSE(matcher.match(vec));
}

// Test: Single element container that matches
TEST_F(ContainsElementMatcherTest_955, SingleElementContainerMatches_955) {
    std::vector<int> vec = {42};
    auto matcher = Catch::Matchers::Contains(42, std::equal_to<int>{});
    EXPECT_TRUE(matcher.match(vec));
}

// Test: Single element container that does not match
TEST_F(ContainsElementMatcherTest_955, SingleElementContainerDoesNotMatch_955) {
    std::vector<int> vec = {41};
    auto matcher = Catch::Matchers::Contains(42, std::equal_to<int>{});
    EXPECT_FALSE(matcher.match(vec));
}

// Test: Works with std::list container
TEST_F(ContainsElementMatcherTest_955, WorksWithListContainer_955) {
    std::list<int> lst = {10, 20, 30, 40};
    auto matcher = Catch::Matchers::Contains(30, std::equal_to<int>{});
    EXPECT_TRUE(matcher.match(lst));
}

// Test: Works with std::array container
TEST_F(ContainsElementMatcherTest_955, WorksWithArrayContainer_955) {
    std::array<int, 4> arr = {10, 20, 30, 40};
    auto matcher = Catch::Matchers::Contains(25, std::equal_to<int>{});
    EXPECT_FALSE(matcher.match(arr));
}

// Test: Lambda as custom equality
TEST_F(ContainsElementMatcherTest_955, WorksWithLambdaEquality_955) {
    std::vector<int> vec = {2, 4, 6, 8};
    // Check if any element has the same remainder when divided by 5
    auto matcher = Catch::Matchers::Contains(13, [](int a, int b) { return a % 5 == b % 5; });
    // 13 % 5 = 3, and 8 % 5 = 3, so should match
    EXPECT_TRUE(matcher.match(vec));
}

// Test: Lambda equality that doesn't find a match
TEST_F(ContainsElementMatcherTest_955, LambdaEqualityNoMatch_955) {
    std::vector<int> vec = {2, 4, 6, 8};
    auto matcher = Catch::Matchers::Contains(10, [](int a, int b) { return a % 5 == b % 5; });
    // 10 % 5 = 0, none of {2,4,6,8} has remainder 0 mod 5
    EXPECT_FALSE(matcher.match(vec));
}

// Test: Large container match at the end
TEST_F(ContainsElementMatcherTest_955, MatchesElementAtEndOfLargeContainer_955) {
    std::vector<int> vec(10000);
    for (int i = 0; i < 10000; ++i) vec[i] = i;
    auto matcher = Catch::Matchers::Contains(9999, std::equal_to<int>{});
    EXPECT_TRUE(matcher.match(vec));
}

// Test: Large container no match
TEST_F(ContainsElementMatcherTest_955, DoesNotMatchInLargeContainer_955) {
    std::vector<int> vec(10000);
    for (int i = 0; i < 10000; ++i) vec[i] = i;
    auto matcher = Catch::Matchers::Contains(10000, std::equal_to<int>{});
    EXPECT_FALSE(matcher.match(vec));
}

// Test: Matcher has a describe method that returns a non-empty string
TEST_F(ContainsElementMatcherTest_955, DescribeReturnsNonEmptyString_955) {
    auto matcher = Catch::Matchers::Contains(42, std::equal_to<int>{});
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test: Contains with string elements using custom equality
TEST_F(ContainsElementMatcherTest_955, CaseInsensitiveStringMatchExactCase_955) {
    std::vector<std::string> vec = {"HELLO", "WORLD"};
    auto matcher = Catch::Matchers::Contains(std::string("HELLO"), CaseInsensitiveEqual{});
    EXPECT_TRUE(matcher.match(vec));
}

// Test: Contains element at the beginning
TEST_F(ContainsElementMatcherTest_955, MatchesFirstElement_955) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto matcher = Catch::Matchers::Contains(1, std::equal_to<int>{});
    EXPECT_TRUE(matcher.match(vec));
}

// Test: Contains with duplicate elements
TEST_F(ContainsElementMatcherTest_955, MatchesWithDuplicateElements_955) {
    std::vector<int> vec = {5, 5, 5, 5};
    auto matcher = Catch::Matchers::Contains(5, std::equal_to<int>{});
    EXPECT_TRUE(matcher.match(vec));
}
