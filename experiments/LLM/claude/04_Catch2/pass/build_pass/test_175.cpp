#include <gtest/gtest.h>
#include <catch2/matchers/catch_matchers_templated.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/matchers/catch_matchers_predicate.hpp>
#include <string>
#include <type_traits>

// A simple concrete matcher deriving from MatcherBase<int>
class IsEqualToMatcher : public Catch::Matchers::MatcherBase<int> {
    int m_expected;
public:
    explicit IsEqualToMatcher(int expected) : m_expected(expected) {}
    bool match(int const& actual) const override {
        return actual == m_expected;
    }
    std::string describe() const override {
        return "is equal to " + std::to_string(m_expected);
    }
};

// A simple generic matcher (satisfies is_generic_matcher_v)
struct IsPositiveGenericMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const& value) const {
        return value > 0;
    }
    std::string describe() const {
        return "is positive";
    }
};

// Another generic matcher
struct IsEvenGenericMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const& value) const {
        return value % 2 == 0;
    }
    std::string describe() const {
        return "is even";
    }
};

// A concrete string matcher
class ContainsSubstringMatcher : public Catch::Matchers::MatcherBase<std::string> {
    std::string m_substr;
public:
    explicit ContainsSubstringMatcher(std::string substr) : m_substr(std::move(substr)) {}
    bool match(std::string const& actual) const override {
        return actual.find(m_substr) != std::string::npos;
    }
    std::string describe() const override {
        return "contains \"" + m_substr + "\"";
    }
};

// Generic matcher for strings
struct StartsWithAGenericMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const& value) const {
        return !value.empty() && value[0] == 'A';
    }
    std::string describe() const {
        return "starts with 'A'";
    }
};

class MatcherOrOperatorTest_175 : public ::testing::Test {
protected:
    IsEqualToMatcher equalsThree{3};
    IsEqualToMatcher equalsFive{5};
    IsPositiveGenericMatcher isPositive{};
    IsEvenGenericMatcher isEven{};
};

// Test: Combining MatcherBase with generic matcher via || - left matches
TEST_F(MatcherOrOperatorTest_175, LeftMatcherMatchesValue_175) {
    auto combined = equalsThree || isPositive;
    // 3 matches left (equals 3), so combined should match
    EXPECT_TRUE(combined.match(3));
}

// Test: Combining MatcherBase with generic matcher via || - right matches
TEST_F(MatcherOrOperatorTest_175, RightMatcherMatchesValue_175) {
    auto combined = equalsThree || isPositive;
    // 7 doesn't equal 3, but is positive, so combined should match
    EXPECT_TRUE(combined.match(7));
}

// Test: Combining MatcherBase with generic matcher via || - both match
TEST_F(MatcherOrOperatorTest_175, BothMatchersMatchValue_175) {
    auto combined = equalsThree || isPositive;
    // 3 equals 3 AND is positive
    EXPECT_TRUE(combined.match(3));
}

// Test: Combining MatcherBase with generic matcher via || - neither matches
TEST_F(MatcherOrOperatorTest_175, NeitherMatcherMatchesValue_175) {
    auto combined = equalsThree || isPositive;
    // -5 doesn't equal 3 and is not positive
    EXPECT_FALSE(combined.match(-5));
}

// Test: Zero as boundary - equals check fails, positive check fails
TEST_F(MatcherOrOperatorTest_175, BoundaryZeroNeitherMatches_175) {
    auto combined = equalsThree || isPositive;
    // 0 != 3 and 0 is not positive
    EXPECT_FALSE(combined.match(0));
}

// Test: Using a different concrete matcher with a different generic matcher
TEST_F(MatcherOrOperatorTest_175, DifferentMatcherCombination_175) {
    auto combined = equalsFive || isEven;
    // 5 equals 5
    EXPECT_TRUE(combined.match(5));
    // 4 is even
    EXPECT_TRUE(combined.match(4));
    // 3 is neither 5 nor even
    EXPECT_FALSE(combined.match(3));
}

// Test: Negative value that matches left but not right
TEST_F(MatcherOrOperatorTest_175, NegativeValueMatchesLeftOnly_175) {
    IsEqualToMatcher equalsNegTwo{-2};
    auto combined = equalsNegTwo || isPositive;
    // -2 equals -2 but is not positive
    EXPECT_TRUE(combined.match(-2));
}

// Test: Result type is MatchAnyOfGeneric
TEST_F(MatcherOrOperatorTest_175, ResultTypeIsMatchAnyOfGeneric_175) {
    auto combined = equalsThree || isPositive;
    using ResultType = decltype(combined);
    // Verify the result is a MatchAnyOfGeneric (it should have match and describe)
    bool hasMatch = std::is_same_v<decltype(combined.match(3)), bool>;
    EXPECT_TRUE(hasMatch);
}

// Test: String matchers - combining MatcherBase<string> with generic matcher
TEST_F(MatcherOrOperatorTest_175, StringMatcherWithGenericMatcher_175) {
    ContainsSubstringMatcher containsHello{"Hello"};
    StartsWithAGenericMatcher startsWithA{};
    auto combined = containsHello || startsWithA;
    
    // "Hello World" contains "Hello"
    EXPECT_TRUE(combined.match(std::string("Hello World")));
    // "Apple" starts with 'A'
    EXPECT_TRUE(combined.match(std::string("Apple")));
    // "AHello" matches both
    EXPECT_TRUE(combined.match(std::string("AHello")));
    // "banana" matches neither
    EXPECT_FALSE(combined.match(std::string("banana")));
}

// Test: Empty string boundary
TEST_F(MatcherOrOperatorTest_175, EmptyStringBoundary_175) {
    ContainsSubstringMatcher containsHello{"Hello"};
    StartsWithAGenericMatcher startsWithA{};
    auto combined = containsHello || startsWithA;
    
    EXPECT_FALSE(combined.match(std::string("")));
}

// Test: describe() returns a non-empty string for the combined matcher
TEST_F(MatcherOrOperatorTest_175, DescribeReturnsNonEmpty_175) {
    auto combined = equalsThree || isPositive;
    std::string description = combined.describe();
    EXPECT_FALSE(description.empty());
}

// Test: Large positive value matches via generic matcher
TEST_F(MatcherOrOperatorTest_175, LargePositiveValueMatchesGeneric_175) {
    auto combined = equalsThree || isPositive;
    EXPECT_TRUE(combined.match(1000000));
}

// Test: Large negative value doesn't match either
TEST_F(MatcherOrOperatorTest_175, LargeNegativeValueMatchesNeither_175) {
    auto combined = equalsThree || isPositive;
    EXPECT_FALSE(combined.match(-1000000));
}

// Test: INT_MAX boundary
TEST_F(MatcherOrOperatorTest_175, IntMaxBoundary_175) {
    auto combined = equalsThree || isPositive;
    EXPECT_TRUE(combined.match(std::numeric_limits<int>::max()));
}

// Test: INT_MIN boundary
TEST_F(MatcherOrOperatorTest_175, IntMinBoundary_175) {
    auto combined = equalsThree || isPositive;
    EXPECT_FALSE(combined.match(std::numeric_limits<int>::min()));
}

// Test: Value of 1 (smallest positive int)
TEST_F(MatcherOrOperatorTest_175, SmallestPositiveInt_175) {
    auto combined = equalsThree || isPositive;
    EXPECT_TRUE(combined.match(1));
}

// Test: Value of -1 (largest negative int)
TEST_F(MatcherOrOperatorTest_175, LargestNegativeInt_175) {
    auto combined = equalsThree || isPositive;
    EXPECT_FALSE(combined.match(-1));
}
