#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <list>
#include <array>
#include <set>

// We need to include the Catch2 matchers header
#include "catch2/matchers/catch_matchers_quantifiers.hpp"
#include "catch2/matchers/catch_matchers.hpp"
#include "catch2/matchers/catch_matchers_predicate.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

// Since we're testing AnyMatchMatcher which is a template class that wraps another matcher,
// we need a simple matcher to use with it. Let's create a minimal one for testing purposes.

// A simple matcher that checks if a value equals a specific target
template <typename T>
class EqualsMatcher : public Catch::Matchers::MatcherGenericBase {
    T m_target;
public:
    explicit EqualsMatcher(T target) : m_target(std::move(target)) {}
    
    bool match(const T& value) const {
        return value == m_target;
    }
    
    std::string describe() const override {
        return "equals target";
    }
};

// A matcher that checks if value is greater than a threshold
template <typename T>
class GreaterThanMatcher : public Catch::Matchers::MatcherGenericBase {
    T m_threshold;
public:
    explicit GreaterThanMatcher(T threshold) : m_threshold(threshold) {}
    
    bool match(const T& value) const {
        return value > m_threshold;
    }
    
    std::string describe() const override {
        return "is greater than threshold";
    }
};

// A matcher that always returns false
class NeverMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    template <typename T>
    bool match(const T&) const {
        return false;
    }
    
    std::string describe() const override {
        return "never matches";
    }
};

// A matcher that always returns true
class AlwaysMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    template <typename T>
    bool match(const T&) const {
        return true;
    }
    
    std::string describe() const override {
        return "always matches";
    }
};

// Test fixture
class AnyMatchMatcherTest_181 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: AnyMatchMatcher returns true when at least one element matches
TEST_F(AnyMatchMatcherTest_181, ReturnsTrueWhenOneElementMatches_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(3));
    std::vector<int> vec = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: AnyMatchMatcher returns false when no elements match
TEST_F(AnyMatchMatcherTest_181, ReturnsFalseWhenNoElementsMatch_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(10));
    std::vector<int> vec = {1, 2, 3, 4, 5};
    EXPECT_FALSE(matcher.match(vec));
}

// Test: AnyMatchMatcher returns false for empty container
TEST_F(AnyMatchMatcherTest_181, ReturnsFalseForEmptyContainer_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(1));
    std::vector<int> vec;
    EXPECT_FALSE(matcher.match(vec));
}

// Test: AnyMatchMatcher returns true when all elements match
TEST_F(AnyMatchMatcherTest_181, ReturnsTrueWhenAllElementsMatch_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<GreaterThanMatcher<int>>(GreaterThanMatcher<int>(0));
    std::vector<int> vec = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: AnyMatchMatcher with single element that matches
TEST_F(AnyMatchMatcherTest_181, ReturnsTrueForSingleMatchingElement_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(42));
    std::vector<int> vec = {42};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: AnyMatchMatcher with single element that does not match
TEST_F(AnyMatchMatcherTest_181, ReturnsFalseForSingleNonMatchingElement_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(42));
    std::vector<int> vec = {99};
    EXPECT_FALSE(matcher.match(vec));
}

// Test: AnyMatchMatcher works with std::list
TEST_F(AnyMatchMatcherTest_181, WorksWithStdList_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(3));
    std::list<int> lst = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(lst));
}

// Test: AnyMatchMatcher works with std::array
TEST_F(AnyMatchMatcherTest_181, WorksWithStdArray_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(5));
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(arr));
}

// Test: AnyMatchMatcher works with std::set
TEST_F(AnyMatchMatcherTest_181, WorksWithStdSet_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(3));
    std::set<int> s = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(s));
}

// Test: AnyMatchMatcher with NeverMatcher returns false for non-empty container
TEST_F(AnyMatchMatcherTest_181, NeverMatcherReturnsFalseForNonEmpty_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<NeverMatcher>(NeverMatcher{});
    std::vector<int> vec = {1, 2, 3};
    EXPECT_FALSE(matcher.match(vec));
}

// Test: AnyMatchMatcher with AlwaysMatcher returns true for non-empty container
TEST_F(AnyMatchMatcherTest_181, AlwaysMatcherReturnsTrueForNonEmpty_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<AlwaysMatcher>(AlwaysMatcher{});
    std::vector<int> vec = {1, 2, 3};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: AnyMatchMatcher with AlwaysMatcher returns false for empty container
TEST_F(AnyMatchMatcherTest_181, AlwaysMatcherReturnsFalseForEmpty_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<AlwaysMatcher>(AlwaysMatcher{});
    std::vector<int> vec;
    EXPECT_FALSE(matcher.match(vec));
}

// Test: AnyMatchMatcher with string vector
TEST_F(AnyMatchMatcherTest_181, WorksWithStringVector_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<std::string>>(
        EqualsMatcher<std::string>("hello"));
    std::vector<std::string> vec = {"world", "hello", "foo"};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: AnyMatchMatcher with string vector no match
TEST_F(AnyMatchMatcherTest_181, WorksWithStringVectorNoMatch_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<std::string>>(
        EqualsMatcher<std::string>("bar"));
    std::vector<std::string> vec = {"world", "hello", "foo"};
    EXPECT_FALSE(matcher.match(vec));
}

// Test: AnyMatchMatcher returns true when only the first element matches
TEST_F(AnyMatchMatcherTest_181, MatchesOnFirstElement_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(1));
    std::vector<int> vec = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: AnyMatchMatcher returns true when only the last element matches
TEST_F(AnyMatchMatcherTest_181, MatchesOnLastElement_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(5));
    std::vector<int> vec = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: AnyMatchMatcher with GreaterThan where no element satisfies
TEST_F(AnyMatchMatcherTest_181, GreaterThanNoElementSatisfies_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<GreaterThanMatcher<int>>(GreaterThanMatcher<int>(100));
    std::vector<int> vec = {1, 2, 3, 4, 5};
    EXPECT_FALSE(matcher.match(vec));
}

// Test: AnyMatchMatcher with large container
TEST_F(AnyMatchMatcherTest_181, WorksWithLargeContainer_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(9999));
    std::vector<int> vec(10000);
    for (int i = 0; i < 10000; ++i) {
        vec[i] = i;
    }
    EXPECT_TRUE(matcher.match(vec));
}

// Test: AnyMatchMatcher with large container no match
TEST_F(AnyMatchMatcherTest_181, LargeContainerNoMatch_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(-1));
    std::vector<int> vec(10000);
    for (int i = 0; i < 10000; ++i) {
        vec[i] = i;
    }
    EXPECT_FALSE(matcher.match(vec));
}

// Test: describe returns a non-empty string
TEST_F(AnyMatchMatcherTest_181, DescribeReturnsNonEmpty_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(42));
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test: AnyMatchMatcher with double values
TEST_F(AnyMatchMatcherTest_181, WorksWithDoubleValues_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<GreaterThanMatcher<double>>(GreaterThanMatcher<double>(3.14));
    std::vector<double> vec = {1.0, 2.0, 3.0, 4.0};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: AnyMatchMatcher with double values no match
TEST_F(AnyMatchMatcherTest_181, DoubleValuesNoMatch_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<GreaterThanMatcher<double>>(GreaterThanMatcher<double>(100.0));
    std::vector<double> vec = {1.0, 2.0, 3.0, 4.0};
    EXPECT_FALSE(matcher.match(vec));
}

// Test: AnyMatchMatcher with const reference container
TEST_F(AnyMatchMatcherTest_181, WorksWithConstReferenceContainer_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(3));
    const std::vector<int> vec = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: AnyMatchMatcher with negative numbers
TEST_F(AnyMatchMatcherTest_181, WorksWithNegativeNumbers_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(-5));
    std::vector<int> vec = {-10, -5, 0, 5, 10};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: AnyMatchMatcher with all same elements matching
TEST_F(AnyMatchMatcherTest_181, AllSameElementsMatching_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(7));
    std::vector<int> vec = {7, 7, 7, 7, 7};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: AnyMatchMatcher with all same elements not matching
TEST_F(AnyMatchMatcherTest_181, AllSameElementsNotMatching_181) {
    auto matcher = Catch::Matchers::AnyMatchMatcher<EqualsMatcher<int>>(EqualsMatcher<int>(8));
    std::vector<int> vec = {7, 7, 7, 7, 7};
    EXPECT_FALSE(matcher.match(vec));
}
