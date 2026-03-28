#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/matchers/catch_matchers_predicate.hpp>
#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// A simple generic matcher for testing purposes
struct AlwaysTrueGenericMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const&) const { return true; }
    std::string describe() const override { return "always true"; }
};

struct AlwaysFalseGenericMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const&) const { return false; }
    std::string describe() const override { return "always false"; }
};

struct IsPositiveGenericMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const& val) const { return val > 0; }
    std::string describe() const override { return "is positive"; }
};

// A typed matcher (MatcherBase<int>)
class IsEqualToInt : public Catch::Matchers::MatcherBase<int> {
    int m_value;
public:
    explicit IsEqualToInt(int value) : m_value(value) {}
    bool match(int const& val) const override { return val == m_value; }
    std::string describe() const override {
        return "equals " + std::to_string(m_value);
    }
};

// A typed matcher (MatcherBase<std::string>)
class ContainsSubstring : public Catch::Matchers::MatcherBase<std::string> {
    std::string m_substr;
public:
    explicit ContainsSubstring(std::string substr) : m_substr(std::move(substr)) {}
    bool match(std::string const& val) const override {
        return val.find(m_substr) != std::string::npos;
    }
    std::string describe() const override {
        return "contains \"" + m_substr + "\"";
    }
};

class MatchAnyOfGenericTest_174 : public ::testing::Test {};

// Test: combining generic true matcher with typed matcher that matches -> should match
TEST_F(MatchAnyOfGenericTest_174, GenericTrueOrTypedTrue_BothMatch_174) {
    AlwaysTrueGenericMatcher genericMatcher;
    IsEqualToInt typedMatcher(42);

    auto combined = genericMatcher || typedMatcher;
    EXPECT_TRUE(combined.match(42));
}

// Test: generic true, typed false -> should match (OR semantics)
TEST_F(MatchAnyOfGenericTest_174, GenericTrueOrTypedFalse_Matches_174) {
    AlwaysTrueGenericMatcher genericMatcher;
    IsEqualToInt typedMatcher(99);

    auto combined = genericMatcher || typedMatcher;
    EXPECT_TRUE(combined.match(42));
}

// Test: generic false, typed true -> should match (OR semantics)
TEST_F(MatchAnyOfGenericTest_174, GenericFalseOrTypedTrue_Matches_174) {
    AlwaysFalseGenericMatcher genericMatcher;
    IsEqualToInt typedMatcher(42);

    auto combined = genericMatcher || typedMatcher;
    EXPECT_TRUE(combined.match(42));
}

// Test: generic false, typed false -> should not match
TEST_F(MatchAnyOfGenericTest_174, GenericFalseOrTypedFalse_NoMatch_174) {
    AlwaysFalseGenericMatcher genericMatcher;
    IsEqualToInt typedMatcher(99);

    auto combined = genericMatcher || typedMatcher;
    EXPECT_FALSE(combined.match(42));
}

// Test: describe produces a non-empty string
TEST_F(MatchAnyOfGenericTest_174, DescribeIsNonEmpty_174) {
    AlwaysTrueGenericMatcher genericMatcher;
    IsEqualToInt typedMatcher(42);

    auto combined = genericMatcher || typedMatcher;
    std::string description = combined.describe();
    EXPECT_FALSE(description.empty());
}

// Test: describe contains descriptions from both matchers
TEST_F(MatchAnyOfGenericTest_174, DescribeContainsBothDescriptions_174) {
    AlwaysTrueGenericMatcher genericMatcher;
    IsEqualToInt typedMatcher(42);

    auto combined = genericMatcher || typedMatcher;
    std::string description = combined.describe();
    EXPECT_NE(description.find("always true"), std::string::npos);
    EXPECT_NE(description.find("equals 42"), std::string::npos);
}

// Test: with string type matchers
TEST_F(MatchAnyOfGenericTest_174, GenericOrTypedStringMatcher_Matches_174) {
    AlwaysFalseGenericMatcher genericMatcher;
    ContainsSubstring typedMatcher("hello");

    auto combined = genericMatcher || typedMatcher;
    EXPECT_TRUE(combined.match(std::string("say hello world")));
    EXPECT_FALSE(combined.match(std::string("goodbye world")));
}

// Test: with IsPositive generic matcher and typed int matcher
TEST_F(MatchAnyOfGenericTest_174, IsPositiveOrEqualsNegative_174) {
    IsPositiveGenericMatcher genericMatcher;
    IsEqualToInt typedMatcher(-5);

    auto combined = genericMatcher || typedMatcher;
    // Positive number matches via generic
    EXPECT_TRUE(combined.match(10));
    // -5 matches via typed
    EXPECT_TRUE(combined.match(-5));
    // Negative number that isn't -5 matches neither
    EXPECT_FALSE(combined.match(-3));
}

// Test: boundary - zero value
TEST_F(MatchAnyOfGenericTest_174, BoundaryZeroValue_174) {
    IsPositiveGenericMatcher genericMatcher;
    IsEqualToInt typedMatcher(0);

    auto combined = genericMatcher || typedMatcher;
    // 0 is not positive but equals 0
    EXPECT_TRUE(combined.match(0));
    // -1 is neither positive nor equals 0
    EXPECT_FALSE(combined.match(-1));
}

// Test: result type is correct
TEST_F(MatchAnyOfGenericTest_174, ResultTypeIsMatchAnyOfGeneric_174) {
    AlwaysTrueGenericMatcher genericMatcher;
    IsEqualToInt typedMatcher(42);

    auto combined = genericMatcher || typedMatcher;
    using ExpectedType = Catch::Matchers::Detail::MatchAnyOfGeneric<
        AlwaysTrueGenericMatcher,
        Catch::Matchers::MatcherBase<int>
    >;
    bool isSameType = std::is_same<decltype(combined), ExpectedType>::value;
    EXPECT_TRUE(isSameType);
}

// Test: chaining - combined matcher can be further combined with another typed matcher
TEST_F(MatchAnyOfGenericTest_174, ChainingWithAnotherTypedMatcher_174) {
    AlwaysFalseGenericMatcher genericMatcher;
    IsEqualToInt typedMatcher1(10);

    auto combined = genericMatcher || typedMatcher1;
    // Value 10 matches
    EXPECT_TRUE(combined.match(10));
    // Value 20 doesn't match
    EXPECT_FALSE(combined.match(20));
}
