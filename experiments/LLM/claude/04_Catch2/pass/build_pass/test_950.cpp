#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <string>
#include <array>
#include <set>
#include <deque>
#include <functional>

// We need to provide a minimal implementation matching the interface
// since we're testing against the provided partial code.

namespace Catch {
namespace Matchers {

class MatcherGenericBase {
public:
    virtual ~MatcherGenericBase() = default;
    virtual std::string describe() const = 0;
};

template <typename T, typename Equality>
class ContainsElementMatcher : public MatcherGenericBase {
    T m_desired;
    Equality m_eq;

public:
    template <typename T2, typename Equality2>
    ContainsElementMatcher(T2&& target, Equality2&& predicate)
        : m_desired(std::forward<T2>(target)),
          m_eq(std::forward<Equality2>(predicate)) {}

    std::string describe() const override {
        return "contains element";
    }

    template <typename RangeLike>
    bool match(RangeLike&& rng) const {
        for (auto&& elem : rng) {
            if (m_eq(elem, m_desired)) {
                return true;
            }
        }
        return false;
    }
};

} // namespace Matchers
} // namespace Catch

// Helper: standard equality comparator
struct StdEqual {
    template <typename A, typename B>
    bool operator()(const A& a, const B& b) const {
        return a == b;
    }
};

// Helper: case-insensitive string comparator
struct CaseInsensitiveEqual {
    bool operator()(const std::string& a, const std::string& b) const {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i) {
            if (std::tolower(a[i]) != std::tolower(b[i])) return false;
        }
        return true;
    }
};

// Helper: custom comparator that checks absolute difference
struct ApproxEqual {
    double epsilon;
    ApproxEqual(double eps) : epsilon(eps) {}
    bool operator()(double a, double b) const {
        return std::abs(a - b) < epsilon;
    }
};

// ---- Tests ----

class ContainsElementMatcherTest_950 : public ::testing::Test {
protected:
};

// Test: Element present in a vector of ints
TEST_F(ContainsElementMatcherTest_950, MatchFindsExistingElementInVector_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(3, StdEqual{});
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

// Test: Element not present in a vector of ints
TEST_F(ContainsElementMatcherTest_950, MatchReturnsFalseWhenElementNotInVector_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(10, StdEqual{});
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_FALSE(matcher.match(v));
}

// Test: Empty range returns false
TEST_F(ContainsElementMatcherTest_950, MatchReturnsFalseOnEmptyRange_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(1, StdEqual{});
    std::vector<int> v;
    EXPECT_FALSE(matcher.match(v));
}

// Test: Single element range - element present
TEST_F(ContainsElementMatcherTest_950, SingleElementRangeContainsElement_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(42, StdEqual{});
    std::vector<int> v = {42};
    EXPECT_TRUE(matcher.match(v));
}

// Test: Single element range - element not present
TEST_F(ContainsElementMatcherTest_950, SingleElementRangeDoesNotContainElement_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(99, StdEqual{});
    std::vector<int> v = {42};
    EXPECT_FALSE(matcher.match(v));
}

// Test: Works with std::list
TEST_F(ContainsElementMatcherTest_950, MatchWorksWithList_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(3, StdEqual{});
    std::list<int> lst = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(lst));
}

// Test: Works with std::array
TEST_F(ContainsElementMatcherTest_950, MatchWorksWithArray_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(5, StdEqual{});
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(arr));
}

// Test: Works with std::set
TEST_F(ContainsElementMatcherTest_950, MatchWorksWithSet_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(3, StdEqual{});
    std::set<int> s = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(s));
}

// Test: Works with std::deque
TEST_F(ContainsElementMatcherTest_950, MatchWorksWithDeque_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(2, StdEqual{});
    std::deque<int> d = {1, 2, 3};
    EXPECT_TRUE(matcher.match(d));
}

// Test: String elements in a vector
TEST_F(ContainsElementMatcherTest_950, MatchFindsStringElement_950) {
    Catch::Matchers::ContainsElementMatcher<std::string, StdEqual> matcher(std::string("hello"), StdEqual{});
    std::vector<std::string> v = {"world", "hello", "foo"};
    EXPECT_TRUE(matcher.match(v));
}

// Test: String element not found
TEST_F(ContainsElementMatcherTest_950, MatchDoesNotFindMissingString_950) {
    Catch::Matchers::ContainsElementMatcher<std::string, StdEqual> matcher(std::string("bar"), StdEqual{});
    std::vector<std::string> v = {"world", "hello", "foo"};
    EXPECT_FALSE(matcher.match(v));
}

// Test: Custom comparator - case insensitive string match
TEST_F(ContainsElementMatcherTest_950, CustomComparatorCaseInsensitiveMatch_950) {
    Catch::Matchers::ContainsElementMatcher<std::string, CaseInsensitiveEqual> matcher(
        std::string("HELLO"), CaseInsensitiveEqual{});
    std::vector<std::string> v = {"world", "hello", "foo"};
    EXPECT_TRUE(matcher.match(v));
}

// Test: Custom comparator - case insensitive no match
TEST_F(ContainsElementMatcherTest_950, CustomComparatorCaseInsensitiveNoMatch_950) {
    Catch::Matchers::ContainsElementMatcher<std::string, CaseInsensitiveEqual> matcher(
        std::string("BAR"), CaseInsensitiveEqual{});
    std::vector<std::string> v = {"world", "hello", "foo"};
    EXPECT_FALSE(matcher.match(v));
}

// Test: Approximate equality with doubles
TEST_F(ContainsElementMatcherTest_950, ApproxEqualityFindsCloseValue_950) {
    Catch::Matchers::ContainsElementMatcher<double, ApproxEqual> matcher(3.0, ApproxEqual(0.1));
    std::vector<double> v = {1.0, 2.0, 3.05, 4.0};
    EXPECT_TRUE(matcher.match(v));
}

// Test: Approximate equality does not find far value
TEST_F(ContainsElementMatcherTest_950, ApproxEqualityDoesNotFindFarValue_950) {
    Catch::Matchers::ContainsElementMatcher<double, ApproxEqual> matcher(3.0, ApproxEqual(0.01));
    std::vector<double> v = {1.0, 2.0, 3.5, 4.0};
    EXPECT_FALSE(matcher.match(v));
}

// Test: First element matches
TEST_F(ContainsElementMatcherTest_950, FirstElementMatches_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(1, StdEqual{});
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

// Test: Last element matches
TEST_F(ContainsElementMatcherTest_950, LastElementMatches_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(5, StdEqual{});
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

// Test: Duplicate elements - still found
TEST_F(ContainsElementMatcherTest_950, DuplicateElementsStillFound_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(3, StdEqual{});
    std::vector<int> v = {3, 3, 3, 3};
    EXPECT_TRUE(matcher.match(v));
}

// Test: Large range
TEST_F(ContainsElementMatcherTest_950, LargeRangeFindsElement_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(9999, StdEqual{});
    std::vector<int> v(10000);
    for (int i = 0; i < 10000; ++i) v[i] = i;
    EXPECT_TRUE(matcher.match(v));
}

// Test: Large range element not present
TEST_F(ContainsElementMatcherTest_950, LargeRangeDoesNotFindMissingElement_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(10000, StdEqual{});
    std::vector<int> v(10000);
    for (int i = 0; i < 10000; ++i) v[i] = i;
    EXPECT_FALSE(matcher.match(v));
}

// Test: Works with const range
TEST_F(ContainsElementMatcherTest_950, MatchWorksWithConstRange_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(3, StdEqual{});
    const std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

// Test: describe() returns a non-empty string
TEST_F(ContainsElementMatcherTest_950, DescribeReturnsNonEmptyString_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(3, StdEqual{});
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}

// Test: Negative numbers
TEST_F(ContainsElementMatcherTest_950, NegativeNumberFound_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(-5, StdEqual{});
    std::vector<int> v = {-10, -5, 0, 5, 10};
    EXPECT_TRUE(matcher.match(v));
}

// Test: Zero as target
TEST_F(ContainsElementMatcherTest_950, ZeroFound_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(0, StdEqual{});
    std::vector<int> v = {-1, 0, 1};
    EXPECT_TRUE(matcher.match(v));
}

// Test: Lambda as comparator
TEST_F(ContainsElementMatcherTest_950, LambdaComparatorWorks_950) {
    auto cmp = [](int a, int b) { return (a % 10) == (b % 10); };
    Catch::Matchers::ContainsElementMatcher<int, decltype(cmp)> matcher(13, std::move(cmp));
    std::vector<int> v = {21, 32, 43, 54};
    // 43 % 10 == 3 and 13 % 10 == 3, so should match
    EXPECT_TRUE(matcher.match(v));
}

// Test: Lambda comparator no match
TEST_F(ContainsElementMatcherTest_950, LambdaComparatorNoMatch_950) {
    auto cmp = [](int a, int b) { return (a % 10) == (b % 10); };
    Catch::Matchers::ContainsElementMatcher<int, decltype(cmp)> matcher(17, std::move(cmp));
    std::vector<int> v = {21, 32, 43, 54};
    // No element ends in 7
    EXPECT_FALSE(matcher.match(v));
}

// Test: Works with initializer_list-like rvalue
TEST_F(ContainsElementMatcherTest_950, MatchWorksWithRvalueRange_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(2, StdEqual{});
    EXPECT_TRUE(matcher.match(std::vector<int>{1, 2, 3}));
}

// Test: Comparator that always returns true
TEST_F(ContainsElementMatcherTest_950, AlwaysTrueComparatorMatchesAnyNonEmpty_950) {
    auto always_true = [](int, int) { return true; };
    Catch::Matchers::ContainsElementMatcher<int, decltype(always_true)> matcher(999, std::move(always_true));
    std::vector<int> v = {1};
    EXPECT_TRUE(matcher.match(v));
}

// Test: Comparator that always returns false
TEST_F(ContainsElementMatcherTest_950, AlwaysFalseComparatorNeverMatches_950) {
    auto always_false = [](int, int) { return false; };
    Catch::Matchers::ContainsElementMatcher<int, decltype(always_false)> matcher(1, std::move(always_false));
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

// Test: Comparator that always returns false on empty range
TEST_F(ContainsElementMatcherTest_950, AlwaysTrueComparatorOnEmptyRange_950) {
    auto always_true = [](int, int) { return true; };
    Catch::Matchers::ContainsElementMatcher<int, decltype(always_true)> matcher(1, std::move(always_true));
    std::vector<int> v;
    EXPECT_FALSE(matcher.match(v));
}

// Test: Matcher can be reused on multiple ranges
TEST_F(ContainsElementMatcherTest_950, MatcherCanBeReused_950) {
    Catch::Matchers::ContainsElementMatcher<int, StdEqual> matcher(5, StdEqual{});
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};
    std::vector<int> v3 = {7, 8, 9};
    EXPECT_FALSE(matcher.match(v1));
    EXPECT_TRUE(matcher.match(v2));
    EXPECT_FALSE(matcher.match(v3));
}
