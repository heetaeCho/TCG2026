#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// Include the header under test
#include "catch2/matchers/catch_matchers_templated.hpp"

// We need to create a simple matcher that conforms to the expected interface
// to test the MatchNotOfGeneric and its operator!

namespace {

// A simple custom matcher for testing purposes
class SimpleMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    explicit SimpleMatcher(int expected) : m_expected(expected) {}

    template<typename T>
    bool match(T&& val) const {
        return val == m_expected;
    }

    std::string describe() const override {
        return "equals " + std::to_string(m_expected);
    }

private:
    int m_expected;
};

// A string matcher for more diverse testing
class StringContainsMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    explicit StringContainsMatcher(std::string substring) : m_substring(std::move(substring)) {}

    bool match(const std::string& val) const {
        return val.find(m_substring) != std::string::npos;
    }

    std::string describe() const override {
        return "contains \"" + m_substring + "\"";
    }

private:
    std::string m_substring;
};

} // anonymous namespace

class MatchNotOfGenericTest_168 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that operator! on MatchNotOfGeneric returns the original matcher reference
TEST_F(MatchNotOfGenericTest_168, OperatorNotReturnsOriginalMatcher_168) {
    SimpleMatcher original(42);
    // Create a MatchNotOfGeneric wrapping the original matcher
    Catch::Matchers::Detail::MatchNotOfGeneric<SimpleMatcher> notMatcher(original);
    
    // Applying operator! should return a reference to the original matcher
    const SimpleMatcher& returned = !notMatcher;
    
    // The returned reference should point to the stored matcher
    // We can verify by checking that it behaves the same way
    EXPECT_TRUE(returned.match(42));
    EXPECT_FALSE(returned.match(43));
}

// Test that the negated matcher inverts the match result
TEST_F(MatchNotOfGenericTest_168, MatchNotOfGenericInvertsMatch_168) {
    SimpleMatcher original(42);
    Catch::Matchers::Detail::MatchNotOfGeneric<SimpleMatcher> notMatcher(original);
    
    // The negated matcher should invert: match(42) should be false, match(43) should be true
    EXPECT_FALSE(notMatcher.match(42));
    EXPECT_TRUE(notMatcher.match(43));
}

// Test that describe() on MatchNotOfGeneric produces a meaningful description
TEST_F(MatchNotOfGenericTest_168, DescribeContainsNegation_168) {
    SimpleMatcher original(42);
    Catch::Matchers::Detail::MatchNotOfGeneric<SimpleMatcher> notMatcher(original);
    
    std::string description = notMatcher.describe();
    // The description should contain some form of negation and the original description
    EXPECT_FALSE(description.empty());
    // It should reference the original matcher's description in some way
    // Typically "not <original description>"
    EXPECT_NE(description.find("not"), std::string::npos);
}

// Test double negation: !(!matcher) should return the original matcher
TEST_F(MatchNotOfGenericTest_168, DoubleNegationReturnsOriginal_168) {
    SimpleMatcher original(42);
    Catch::Matchers::Detail::MatchNotOfGeneric<SimpleMatcher> notMatcher(original);
    
    // Double negation via operator!
    const SimpleMatcher& doubleNegated = !notMatcher;
    
    // Should behave exactly like the original
    EXPECT_TRUE(doubleNegated.match(42));
    EXPECT_FALSE(doubleNegated.match(0));
    EXPECT_FALSE(doubleNegated.match(-1));
}

// Test with string matcher
TEST_F(MatchNotOfGenericTest_168, StringMatcherNegation_168) {
    StringContainsMatcher original("hello");
    Catch::Matchers::Detail::MatchNotOfGeneric<StringContainsMatcher> notMatcher(original);
    
    // Negated: should NOT match strings containing "hello"
    EXPECT_FALSE(notMatcher.match(std::string("hello world")));
    EXPECT_TRUE(notMatcher.match(std::string("goodbye world")));
}

// Test that operator! returns a const reference
TEST_F(MatchNotOfGenericTest_168, OperatorNotReturnsConstReference_168) {
    SimpleMatcher original(10);
    Catch::Matchers::Detail::MatchNotOfGeneric<SimpleMatcher> notMatcher(original);
    
    const auto& ref = !notMatcher;
    
    // Verify it's the same type
    static_assert(std::is_same<decltype(ref), const SimpleMatcher&>::value,
                  "operator! should return const MatcherT&");
    
    EXPECT_TRUE(ref.match(10));
    EXPECT_FALSE(ref.match(11));
}

// Test move construction of MatchNotOfGeneric
TEST_F(MatchNotOfGenericTest_168, MoveConstruction_168) {
    SimpleMatcher original(99);
    Catch::Matchers::Detail::MatchNotOfGeneric<SimpleMatcher> notMatcher(original);
    
    // Move construct
    auto movedMatcher = std::move(notMatcher);
    
    // The moved-to matcher should still work correctly
    EXPECT_FALSE(movedMatcher.match(99));
    EXPECT_TRUE(movedMatcher.match(100));
}

// Test boundary: matching with zero
TEST_F(MatchNotOfGenericTest_168, BoundaryMatchWithZero_168) {
    SimpleMatcher original(0);
    Catch::Matchers::Detail::MatchNotOfGeneric<SimpleMatcher> notMatcher(original);
    
    EXPECT_FALSE(notMatcher.match(0));
    EXPECT_TRUE(notMatcher.match(1));
    EXPECT_TRUE(notMatcher.match(-1));
}

// Test boundary: matching with negative numbers
TEST_F(MatchNotOfGenericTest_168, BoundaryMatchWithNegative_168) {
    SimpleMatcher original(-1);
    Catch::Matchers::Detail::MatchNotOfGeneric<SimpleMatcher> notMatcher(original);
    
    EXPECT_FALSE(notMatcher.match(-1));
    EXPECT_TRUE(notMatcher.match(0));
    EXPECT_TRUE(notMatcher.match(1));
}

// Test with empty string
TEST_F(MatchNotOfGenericTest_168, BoundaryEmptyStringMatcher_168) {
    StringContainsMatcher original("");
    Catch::Matchers::Detail::MatchNotOfGeneric<StringContainsMatcher> notMatcher(original);
    
    // Empty string is contained in every string, so negation should be false for all
    EXPECT_FALSE(notMatcher.match(std::string("")));
    EXPECT_FALSE(notMatcher.match(std::string("anything")));
}

// Test that operator! on MatchNotOfGeneric preserves matcher state correctly
TEST_F(MatchNotOfGenericTest_168, OperatorNotPreservesMatcherState_168) {
    SimpleMatcher original(55);
    Catch::Matchers::Detail::MatchNotOfGeneric<SimpleMatcher> notMatcher(original);
    
    const SimpleMatcher& restored = !notMatcher;
    
    // Verify the describe is preserved
    std::string desc = restored.describe();
    EXPECT_NE(desc.find("55"), std::string::npos);
}
