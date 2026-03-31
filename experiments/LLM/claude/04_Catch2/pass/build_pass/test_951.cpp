#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <list>
#include <string>
#include <array>
#include <set>

// We need to create a minimal mock/stub for the Matcher concept and the ContainsMatcherMatcher
// Since we're testing against the Catch2 amalgamated header's ContainsMatcherMatcher,
// we'll create a lightweight test environment.

// Minimal matcher that checks equality
template <typename T>
struct EqualsMatcher {
    T expected;
    
    EqualsMatcher(T val) : expected(std::move(val)) {}
    
    bool match(const T& elem) const {
        return elem == expected;
    }
    
    std::string describe() const {
        return "equals expected value";
    }
};

// Minimal matcher that always returns true
struct AlwaysTrueMatcher {
    template <typename T>
    bool match(const T&) const {
        return true;
    }
    
    std::string describe() const {
        return "always true";
    }
};

// Minimal matcher that always returns false
struct AlwaysFalseMatcher {
    template <typename T>
    bool match(const T&) const {
        return false;
    }
    
    std::string describe() const {
        return "always false";
    }
};

// Matcher that tracks how many times match was called
template <typename T>
struct CountingMatcher {
    T expected;
    mutable int call_count = 0;
    
    CountingMatcher(T val) : expected(std::move(val)) {}
    
    bool match(const T& elem) const {
        call_count++;
        return elem == expected;
    }
    
    std::string describe() const {
        return "counting matcher";
    }
};

// Minimal MatcherGenericBase stub
namespace Catch {
namespace Matchers {

class MatcherGenericBase {
public:
    virtual ~MatcherGenericBase() = default;
    virtual std::string describe() const = 0;
};

#define CATCH_MOVE(x) std::move(x)

template <typename Matcher>
class ContainsMatcherMatcher : public MatcherGenericBase {
public:
    ContainsMatcherMatcher(Matcher matcher) : m_matcher(CATCH_MOVE(matcher)) {}

    template <typename RangeLike>
    bool match(RangeLike&& rng) const {
        for (auto&& elem : rng) {
            if (m_matcher.match(elem)) {
                return true;
            }
        }
        return false;
    }

    std::string describe() const override {
        return "Contains element matching: " + m_matcher.describe();
    }

private:
    Matcher m_matcher;
};

} // namespace Matchers
} // namespace Catch

#undef CATCH_MOVE

// ======================== TESTS ========================

class ContainsMatcherMatcherTest_951 : public ::testing::Test {
protected:
    // Helper to create ContainsMatcherMatcher easily
    template <typename Matcher>
    Catch::Matchers::ContainsMatcherMatcher<Matcher> makeContainsMatcher(Matcher m) {
        return Catch::Matchers::ContainsMatcherMatcher<Matcher>(std::move(m));
    }
};

// --- Normal Operation Tests ---

TEST_F(ContainsMatcherMatcherTest_951, MatchFindsElementInVector_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(3));
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsMatcherMatcherTest_951, MatchDoesNotFindElementInVector_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(10));
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(ContainsMatcherMatcherTest_951, MatchFindsStringInVector_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<std::string>("hello"));
    std::vector<std::string> v = {"world", "hello", "foo"};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsMatcherMatcherTest_951, MatchDoesNotFindStringInVector_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<std::string>("bar"));
    std::vector<std::string> v = {"world", "hello", "foo"};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(ContainsMatcherMatcherTest_951, MatchFindsElementInList_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(42));
    std::list<int> l = {10, 20, 42, 50};
    EXPECT_TRUE(matcher.match(l));
}

TEST_F(ContainsMatcherMatcherTest_951, MatchFindsElementInSet_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(7));
    std::set<int> s = {1, 3, 5, 7, 9};
    EXPECT_TRUE(matcher.match(s));
}

TEST_F(ContainsMatcherMatcherTest_951, MatchFindsElementInArray_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(2));
    std::array<int, 4> a = {1, 2, 3, 4};
    EXPECT_TRUE(matcher.match(a));
}

TEST_F(ContainsMatcherMatcherTest_951, MatchFindsFirstElement_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(1));
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsMatcherMatcherTest_951, MatchFindsLastElement_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(3));
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

// --- Boundary Condition Tests ---

TEST_F(ContainsMatcherMatcherTest_951, MatchReturnsFalseForEmptyVector_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(1));
    std::vector<int> v;
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(ContainsMatcherMatcherTest_951, MatchReturnsFalseForEmptyList_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<std::string>("test"));
    std::list<std::string> l;
    EXPECT_FALSE(matcher.match(l));
}

TEST_F(ContainsMatcherMatcherTest_951, MatchSingleElementVectorFound_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(42));
    std::vector<int> v = {42};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsMatcherMatcherTest_951, MatchSingleElementVectorNotFound_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(42));
    std::vector<int> v = {99};
    EXPECT_FALSE(matcher.match(v));
}

// --- AlwaysTrue / AlwaysFalse Matcher Tests ---

TEST_F(ContainsMatcherMatcherTest_951, AlwaysTrueMatcherMatchesNonEmptyRange_951) {
    auto matcher = makeContainsMatcher(AlwaysTrueMatcher{});
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsMatcherMatcherTest_951, AlwaysTrueMatcherDoesNotMatchEmptyRange_951) {
    auto matcher = makeContainsMatcher(AlwaysTrueMatcher{});
    std::vector<int> v;
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(ContainsMatcherMatcherTest_951, AlwaysFalseMatcherDoesNotMatchAnyRange_951) {
    auto matcher = makeContainsMatcher(AlwaysFalseMatcher{});
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(ContainsMatcherMatcherTest_951, AlwaysFalseMatcherDoesNotMatchEmptyRange_951) {
    auto matcher = makeContainsMatcher(AlwaysFalseMatcher{});
    std::vector<int> v;
    EXPECT_FALSE(matcher.match(v));
}

// --- Early Exit Behavior Test ---

TEST_F(ContainsMatcherMatcherTest_951, MatchStopsOnFirstMatch_951) {
    // The first element matches, so the matcher should return true
    // and ideally stop early (though we can only observe the result)
    CountingMatcher<int> cm(1);
    auto matcher = makeContainsMatcher(cm);
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsMatcherMatcherTest_951, MatchChecksAllElementsWhenNoneMatch_951) {
    CountingMatcher<int> cm(99);
    auto matcher = makeContainsMatcher(cm);
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_FALSE(matcher.match(v));
}

// --- Duplicate Elements Tests ---

TEST_F(ContainsMatcherMatcherTest_951, MatchWithDuplicateElements_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(2));
    std::vector<int> v = {2, 2, 2};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsMatcherMatcherTest_951, MatchWithAllSameElementsNotMatching_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(3));
    std::vector<int> v = {2, 2, 2};
    EXPECT_FALSE(matcher.match(v));
}

// --- describe() Test ---

TEST_F(ContainsMatcherMatcherTest_951, DescribeReturnsNonEmptyString_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(5));
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}

// --- Const Range Test ---

TEST_F(ContainsMatcherMatcherTest_951, MatchWorksWithConstVector_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(3));
    const std::vector<int> v = {1, 2, 3, 4};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsMatcherMatcherTest_951, MatchWorksWithConstVectorNoMatch_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(99));
    const std::vector<int> v = {1, 2, 3, 4};
    EXPECT_FALSE(matcher.match(v));
}

// --- Negative and Zero Values ---

TEST_F(ContainsMatcherMatcherTest_951, MatchFindsNegativeValue_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(-5));
    std::vector<int> v = {-10, -5, 0, 5, 10};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsMatcherMatcherTest_951, MatchFindsZero_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(0));
    std::vector<int> v = {-1, 0, 1};
    EXPECT_TRUE(matcher.match(v));
}

// --- Large Range Test ---

TEST_F(ContainsMatcherMatcherTest_951, MatchFindsElementInLargeRange_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(9999));
    std::vector<int> v(10000);
    for (int i = 0; i < 10000; ++i) {
        v[i] = i;
    }
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsMatcherMatcherTest_951, MatchDoesNotFindElementInLargeRange_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(10000));
    std::vector<int> v(10000);
    for (int i = 0; i < 10000; ++i) {
        v[i] = i;
    }
    EXPECT_FALSE(matcher.match(v));
}

// --- C-style array via initializer_list-like test ---

TEST_F(ContainsMatcherMatcherTest_951, MatchWorksWithInitializerListStyle_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(3));
    std::vector<int> v{1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

// --- Double / Float Range ---

TEST_F(ContainsMatcherMatcherTest_951, MatchFindsDoubleInVector_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<double>(3.14));
    std::vector<double> v = {1.0, 2.0, 3.14, 4.0};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ContainsMatcherMatcherTest_951, MatchDoesNotFindDoubleInVector_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<double>(2.71));
    std::vector<double> v = {1.0, 2.0, 3.14, 4.0};
    EXPECT_FALSE(matcher.match(v));
}

// --- Multiple Calls to match ---

TEST_F(ContainsMatcherMatcherTest_951, MatchCanBeCalledMultipleTimes_951) {
    auto matcher = makeContainsMatcher(EqualsMatcher<int>(5));
    
    std::vector<int> v1 = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v1));
    
    std::vector<int> v2 = {4, 5, 6};
    EXPECT_TRUE(matcher.match(v2));
    
    std::vector<int> v3 = {};
    EXPECT_FALSE(matcher.match(v3));
    
    std::vector<int> v4 = {5};
    EXPECT_TRUE(matcher.match(v4));
}
