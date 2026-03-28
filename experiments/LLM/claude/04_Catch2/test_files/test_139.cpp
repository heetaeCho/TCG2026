#include <gtest/gtest.h>
#include <string>
#include <type_traits>

#include "catch2/matchers/catch_matchers.hpp"

// We need concrete matchers to test MatchAnyOf
// Using a simple custom matcher that always returns a fixed value
namespace {

template <typename ArgT>
class AlwaysTrueMatcher : public Catch::Matchers::MatcherBase<ArgT> {
public:
    bool match(ArgT const&) const override { return true; }
    std::string describe() const override { return "always true"; }
};

template <typename ArgT>
class AlwaysFalseMatcher : public Catch::Matchers::MatcherBase<ArgT> {
public:
    bool match(ArgT const&) const override { return false; }
    std::string describe() const override { return "always false"; }
};

template <typename ArgT>
class EqualsMatcher : public Catch::Matchers::MatcherBase<ArgT> {
    ArgT m_value;
public:
    explicit EqualsMatcher(ArgT value) : m_value(std::move(value)) {}
    bool match(ArgT const& arg) const override { return arg == m_value; }
    std::string describe() const override { return "equals " + std::to_string(m_value); }
};

// Specialization for std::string
template <>
class EqualsMatcher<std::string> : public Catch::Matchers::MatcherBase<std::string> {
    std::string m_value;
public:
    explicit EqualsMatcher(std::string value) : m_value(std::move(value)) {}
    bool match(std::string const& arg) const override { return arg == m_value; }
    std::string describe() const override { return "equals \"" + m_value + "\""; }
};

} // anonymous namespace

class MatchAnyOfTest_139 : public ::testing::Test {
protected:
    // Helper to create MatchAnyOf using operator||
    // MatchAnyOf is typically built by combining matchers with ||
};

// Test: MatchAnyOf with no matchers should return false (no matcher matches)
TEST_F(MatchAnyOfTest_139, EmptyMatchAnyOfReturnsFalse_139) {
    Catch::Matchers::Detail::MatchAnyOf<int> anyOf;
    // With no matchers in the collection, match should return false
    EXPECT_FALSE(anyOf.match(42));
}

// Test: MatchAnyOf with a single always-true matcher returns true
TEST_F(MatchAnyOfTest_139, SingleAlwaysTrueMatcherReturnsTrue_139) {
    AlwaysTrueMatcher<int> trueMatcher;
    auto combined = trueMatcher || AlwaysFalseMatcher<int>{};
    // The || operator on Catch2 matchers should produce a MatchAnyOf
    // At least one matcher is true, so match should return true
    EXPECT_TRUE(combined.match(42));
}

// Test: MatchAnyOf with all false matchers returns false
TEST_F(MatchAnyOfTest_139, AllFalseMatchersReturnsFalse_139) {
    auto combined = AlwaysFalseMatcher<int>{} || AlwaysFalseMatcher<int>{};
    EXPECT_FALSE(combined.match(42));
}

// Test: MatchAnyOf with first matcher true returns true
TEST_F(MatchAnyOfTest_139, FirstMatcherTrueReturnsTrue_139) {
    auto combined = AlwaysTrueMatcher<int>{} || AlwaysFalseMatcher<int>{};
    EXPECT_TRUE(combined.match(0));
}

// Test: MatchAnyOf with second matcher true returns true
TEST_F(MatchAnyOfTest_139, SecondMatcherTrueReturnsTrue_139) {
    auto combined = AlwaysFalseMatcher<int>{} || AlwaysTrueMatcher<int>{};
    EXPECT_TRUE(combined.match(0));
}

// Test: MatchAnyOf with all true matchers returns true
TEST_F(MatchAnyOfTest_139, AllTrueMatchersReturnsTrue_139) {
    auto combined = AlwaysTrueMatcher<int>{} || AlwaysTrueMatcher<int>{};
    EXPECT_TRUE(combined.match(99));
}

// Test: MatchAnyOf with value-based matchers - one matches
TEST_F(MatchAnyOfTest_139, ValueBasedOneMatches_139) {
    auto combined = EqualsMatcher<int>(10) || EqualsMatcher<int>(20);
    EXPECT_TRUE(combined.match(10));
    EXPECT_TRUE(combined.match(20));
    EXPECT_FALSE(combined.match(30));
}

// Test: MatchAnyOf with value-based matchers - none matches
TEST_F(MatchAnyOfTest_139, ValueBasedNoneMatches_139) {
    auto combined = EqualsMatcher<int>(10) || EqualsMatcher<int>(20);
    EXPECT_FALSE(combined.match(15));
}

// Test: MatchAnyOf with string type
TEST_F(MatchAnyOfTest_139, StringTypeMatching_139) {
    auto combined = EqualsMatcher<std::string>("hello") || EqualsMatcher<std::string>("world");
    EXPECT_TRUE(combined.match(std::string("hello")));
    EXPECT_TRUE(combined.match(std::string("world")));
    EXPECT_FALSE(combined.match(std::string("foo")));
}

// Test: MatchAnyOf chaining multiple matchers with ||
TEST_F(MatchAnyOfTest_139, ChainingMultipleMatchers_139) {
    auto combined = EqualsMatcher<int>(1) || EqualsMatcher<int>(2) || EqualsMatcher<int>(3);
    EXPECT_TRUE(combined.match(1));
    EXPECT_TRUE(combined.match(2));
    EXPECT_TRUE(combined.match(3));
    EXPECT_FALSE(combined.match(4));
}

// Test: MatchAnyOf describe returns non-empty string
TEST_F(MatchAnyOfTest_139, DescribeReturnsNonEmptyString_139) {
    auto combined = EqualsMatcher<int>(10) || EqualsMatcher<int>(20);
    std::string description = combined.describe();
    EXPECT_FALSE(description.empty());
}

// Test: MatchAnyOf is move constructible
TEST_F(MatchAnyOfTest_139, MoveConstructible_139) {
    EXPECT_TRUE((std::is_move_constructible<Catch::Matchers::Detail::MatchAnyOf<int>>::value));
}

// Test: MatchAnyOf is not copy constructible
TEST_F(MatchAnyOfTest_139, NotCopyConstructible_139) {
    EXPECT_FALSE((std::is_copy_constructible<Catch::Matchers::Detail::MatchAnyOf<int>>::value));
}

// Test: Boundary - match with zero value
TEST_F(MatchAnyOfTest_139, BoundaryZeroValue_139) {
    auto combined = EqualsMatcher<int>(0) || EqualsMatcher<int>(-1);
    EXPECT_TRUE(combined.match(0));
    EXPECT_TRUE(combined.match(-1));
    EXPECT_FALSE(combined.match(1));
}

// Test: Boundary - match with negative values
TEST_F(MatchAnyOfTest_139, BoundaryNegativeValues_139) {
    auto combined = EqualsMatcher<int>(-100) || EqualsMatcher<int>(-200);
    EXPECT_TRUE(combined.match(-100));
    EXPECT_FALSE(combined.match(100));
}

// Test: Boundary - empty string
TEST_F(MatchAnyOfTest_139, BoundaryEmptyString_139) {
    auto combined = EqualsMatcher<std::string>("") || EqualsMatcher<std::string>("nonempty");
    EXPECT_TRUE(combined.match(std::string("")));
    EXPECT_TRUE(combined.match(std::string("nonempty")));
    EXPECT_FALSE(combined.match(std::string("other")));
}

// Test: MatchAnyOf with single matcher via direct construction behavior
TEST_F(MatchAnyOfTest_139, EmptyMatchAnyOfWithVariousArgs_139) {
    Catch::Matchers::Detail::MatchAnyOf<int> anyOf;
    EXPECT_FALSE(anyOf.match(0));
    EXPECT_FALSE(anyOf.match(-1));
    EXPECT_FALSE(anyOf.match(INT_MAX));
    EXPECT_FALSE(anyOf.match(INT_MIN));
}
