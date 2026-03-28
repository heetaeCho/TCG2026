#include <gtest/gtest.h>
#include <string>
#include "catch2/matchers/catch_matchers.hpp"

using namespace Catch::Matchers;

// A simple concrete matcher for testing purposes
template <typename T>
class AlwaysTrueMatcher : public MatcherBase<T> {
    std::string m_desc;
public:
    AlwaysTrueMatcher(std::string desc = "always true") : m_desc(std::move(desc)) {}
    bool match(T const&) const override { return true; }
    std::string describe() const override { return m_desc; }
};

template <typename T>
class AlwaysFalseMatcher : public MatcherBase<T> {
    std::string m_desc;
public:
    AlwaysFalseMatcher(std::string desc = "always false") : m_desc(std::move(desc)) {}
    bool match(T const&) const override { return false; }
    std::string describe() const override { return m_desc; }
};

class MatchAnyOfOperatorTest_142 : public ::testing::Test {
protected:
};

// Test that operator|| with a true lhs matcher results in matching
TEST_F(MatchAnyOfOperatorTest_142, TrueMatcherOrEmptyAnyOf_Matches_142) {
    AlwaysTrueMatcher<int> trueMatcher("true matcher");
    Detail::MatchAnyOf<int> anyOf;
    
    auto combined = trueMatcher || std::move(anyOf);
    
    EXPECT_TRUE(combined.match(42));
}

// Test that operator|| with a false lhs and empty anyOf does not match
TEST_F(MatchAnyOfOperatorTest_142, FalseMatcherOrEmptyAnyOf_DoesNotMatch_142) {
    AlwaysFalseMatcher<int> falseMatcher("false matcher");
    Detail::MatchAnyOf<int> anyOf;
    
    auto combined = falseMatcher || std::move(anyOf);
    
    EXPECT_FALSE(combined.match(42));
}

// Test that operator|| inserts lhs at the beginning - true lhs with false in anyOf
TEST_F(MatchAnyOfOperatorTest_142, TrueMatcherOrFalseAnyOf_Matches_142) {
    AlwaysTrueMatcher<int> trueMatcher("true matcher");
    AlwaysFalseMatcher<int> falseMatcher("false matcher");
    
    // Build an anyOf that contains a false matcher first
    Detail::MatchAnyOf<int> anyOf;
    auto anyOfWithFalse = falseMatcher || std::move(anyOf);
    
    // Now combine true || anyOfWithFalse
    auto combined = trueMatcher || std::move(anyOfWithFalse);
    
    EXPECT_TRUE(combined.match(42));
}

// Test that operator|| with all false matchers does not match
TEST_F(MatchAnyOfOperatorTest_142, AllFalseMatchersDoNotMatch_142) {
    AlwaysFalseMatcher<int> false1("false1");
    AlwaysFalseMatcher<int> false2("false2");
    
    Detail::MatchAnyOf<int> anyOf;
    auto step1 = false1 || std::move(anyOf);
    auto combined = false2 || std::move(step1);
    
    EXPECT_FALSE(combined.match(42));
}

// Test describe includes information about matchers
TEST_F(MatchAnyOfOperatorTest_142, DescribeReturnsNonEmptyString_142) {
    AlwaysTrueMatcher<int> trueMatcher("my true matcher");
    Detail::MatchAnyOf<int> anyOf;
    
    auto combined = trueMatcher || std::move(anyOf);
    
    std::string description = combined.describe();
    EXPECT_FALSE(description.empty());
}

// Test with string type
TEST_F(MatchAnyOfOperatorTest_142, WorksWithStringType_142) {
    AlwaysTrueMatcher<std::string> trueMatcher("string true");
    Detail::MatchAnyOf<std::string> anyOf;
    
    auto combined = trueMatcher || std::move(anyOf);
    
    EXPECT_TRUE(combined.match("hello"));
}

// Test chaining multiple matchers via operator||
TEST_F(MatchAnyOfOperatorTest_142, ChainingMultipleMatchers_142) {
    AlwaysFalseMatcher<int> false1("f1");
    AlwaysFalseMatcher<int> false2("f2");
    AlwaysTrueMatcher<int> true1("t1");
    
    Detail::MatchAnyOf<int> anyOf;
    auto step1 = false1 || std::move(anyOf);
    auto step2 = false2 || std::move(step1);
    auto combined = true1 || std::move(step2);
    
    EXPECT_TRUE(combined.match(0));
}

// Test that the result is a valid MatchAnyOf that can be further combined
TEST_F(MatchAnyOfOperatorTest_142, ResultCanBeFurtherCombined_142) {
    AlwaysFalseMatcher<int> false1("f1");
    AlwaysTrueMatcher<int> true1("t1");
    
    Detail::MatchAnyOf<int> anyOf;
    auto step1 = false1 || std::move(anyOf);
    auto combined = true1 || std::move(step1);
    
    // The result should still be usable as a matcher
    EXPECT_TRUE(combined.match(100));
}
