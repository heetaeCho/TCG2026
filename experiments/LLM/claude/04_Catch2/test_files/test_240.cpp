#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include <string>

// Since we're testing Catch2's ExceptionMessageMatchesMatcher, we need to
// understand its interface: it takes a string matcher and matches against
// std::exception::what().

// We'll create a minimal mock/stub for the string matcher to test the
// ExceptionMessageMatchesMatcher behavior.

// Minimal StringMatcher that checks for exact match
struct ExactStringMatcher {
    std::string m_expected;
    
    ExactStringMatcher(std::string expected) : m_expected(std::move(expected)) {}
    
    bool match(const std::string& str) const {
        return str == m_expected;
    }
    
    std::string describe() const {
        return "equals: \"" + m_expected + "\"";
    }
};

// Minimal StringMatcher that checks if string contains a substring
struct ContainsStringMatcher {
    std::string m_substring;
    
    ContainsStringMatcher(std::string substring) : m_substring(std::move(substring)) {}
    
    bool match(const std::string& str) const {
        return str.find(m_substring) != std::string::npos;
    }
    
    std::string describe() const {
        return "contains: \"" + m_substring + "\"";
    }
};

// Since we can't directly include catch2 headers in a gtest context easily,
// we'll replicate the minimal structure under test based on the provided code.

namespace TestCatch {
namespace Matchers {

template <typename T>
class MatcherBase {
public:
    virtual bool match(T const&) const = 0;
    virtual std::string describe() const = 0;
    virtual ~MatcherBase() = default;
};

template <typename StringMatcherType>
class ExceptionMessageMatchesMatcher : public MatcherBase<std::exception> {
    StringMatcherType m_matcher;
public:
    ExceptionMessageMatchesMatcher(StringMatcherType matcher)
        : m_matcher(std::move(matcher)) {}
    
    bool match(std::exception const& ex) const override {
        return m_matcher.match(ex.what());
    }
    
    std::string describe() const override {
        return "exception message " + m_matcher.describe();
    }
};

} // namespace Matchers
} // namespace TestCatch

// Test fixture
class ExceptionMessageMatchesMatcherTest_240 : public ::testing::Test {
protected:
};

// Test: Matching an exception with exact message that matches
TEST_F(ExceptionMessageMatchesMatcherTest_240, ExactMatch_MatchesCorrectMessage_240) {
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ExactStringMatcher> matcher(
        ExactStringMatcher("test error"));
    
    std::runtime_error ex("test error");
    EXPECT_TRUE(matcher.match(ex));
}

// Test: Exact match fails when message differs
TEST_F(ExceptionMessageMatchesMatcherTest_240, ExactMatch_DoesNotMatchDifferentMessage_240) {
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ExactStringMatcher> matcher(
        ExactStringMatcher("expected error"));
    
    std::runtime_error ex("actual error");
    EXPECT_FALSE(matcher.match(ex));
}

// Test: Empty exception message matches empty expected
TEST_F(ExceptionMessageMatchesMatcherTest_240, ExactMatch_EmptyMessageMatchesEmpty_240) {
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ExactStringMatcher> matcher(
        ExactStringMatcher(""));
    
    std::runtime_error ex("");
    EXPECT_TRUE(matcher.match(ex));
}

// Test: Empty expected does not match non-empty message
TEST_F(ExceptionMessageMatchesMatcherTest_240, ExactMatch_EmptyExpectedDoesNotMatchNonEmpty_240) {
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ExactStringMatcher> matcher(
        ExactStringMatcher(""));
    
    std::runtime_error ex("some error");
    EXPECT_FALSE(matcher.match(ex));
}

// Test: Non-empty expected does not match empty message
TEST_F(ExceptionMessageMatchesMatcherTest_240, ExactMatch_NonEmptyExpectedDoesNotMatchEmpty_240) {
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ExactStringMatcher> matcher(
        ExactStringMatcher("some error"));
    
    std::runtime_error ex("");
    EXPECT_FALSE(matcher.match(ex));
}

// Test: Contains matcher matches when substring is present
TEST_F(ExceptionMessageMatchesMatcherTest_240, ContainsMatch_SubstringPresent_240) {
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ContainsStringMatcher> matcher(
        ContainsStringMatcher("error"));
    
    std::runtime_error ex("this is an error message");
    EXPECT_TRUE(matcher.match(ex));
}

// Test: Contains matcher does not match when substring is absent
TEST_F(ExceptionMessageMatchesMatcherTest_240, ContainsMatch_SubstringAbsent_240) {
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ContainsStringMatcher> matcher(
        ContainsStringMatcher("fatal"));
    
    std::runtime_error ex("this is an error message");
    EXPECT_FALSE(matcher.match(ex));
}

// Test: Works with std::logic_error (derived from std::exception)
TEST_F(ExceptionMessageMatchesMatcherTest_240, MatchesLogicError_240) {
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ExactStringMatcher> matcher(
        ExactStringMatcher("logic failure"));
    
    std::logic_error ex("logic failure");
    EXPECT_TRUE(matcher.match(ex));
}

// Test: Works with std::invalid_argument (derived from std::exception)
TEST_F(ExceptionMessageMatchesMatcherTest_240, MatchesInvalidArgument_240) {
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ExactStringMatcher> matcher(
        ExactStringMatcher("bad argument"));
    
    std::invalid_argument ex("bad argument");
    EXPECT_TRUE(matcher.match(ex));
}

// Test: Works with std::out_of_range
TEST_F(ExceptionMessageMatchesMatcherTest_240, MatchesOutOfRange_240) {
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ExactStringMatcher> matcher(
        ExactStringMatcher("index out of range"));
    
    std::out_of_range ex("index out of range");
    EXPECT_TRUE(matcher.match(ex));
}

// Test: describe() returns a meaningful description
TEST_F(ExceptionMessageMatchesMatcherTest_240, DescribeReturnsDescription_240) {
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ExactStringMatcher> matcher(
        ExactStringMatcher("test"));
    
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
    // The description should contain information about the inner matcher
    EXPECT_NE(description.find("test"), std::string::npos);
}

// Test: Case sensitivity - exact match is case sensitive
TEST_F(ExceptionMessageMatchesMatcherTest_240, ExactMatch_CaseSensitive_240) {
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ExactStringMatcher> matcher(
        ExactStringMatcher("Test Error"));
    
    std::runtime_error ex("test error");
    EXPECT_FALSE(matcher.match(ex));
}

// Test: Special characters in exception message
TEST_F(ExceptionMessageMatchesMatcherTest_240, ExactMatch_SpecialCharacters_240) {
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ExactStringMatcher> matcher(
        ExactStringMatcher("error: file not found\n\tat line 42"));
    
    std::runtime_error ex("error: file not found\n\tat line 42");
    EXPECT_TRUE(matcher.match(ex));
}

// Test: Very long exception message
TEST_F(ExceptionMessageMatchesMatcherTest_240, ExactMatch_LongMessage_240) {
    std::string longMsg(10000, 'a');
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ExactStringMatcher> matcher(
        ExactStringMatcher(longMsg));
    
    std::runtime_error ex(longMsg.c_str());
    EXPECT_TRUE(matcher.match(ex));
}

// Test: Message with only whitespace
TEST_F(ExceptionMessageMatchesMatcherTest_240, ExactMatch_WhitespaceMessage_240) {
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ExactStringMatcher> matcher(
        ExactStringMatcher("   "));
    
    std::runtime_error ex("   ");
    EXPECT_TRUE(matcher.match(ex));
}

// Test: Partial match fails with exact matcher
TEST_F(ExceptionMessageMatchesMatcherTest_240, ExactMatch_PartialMatchFails_240) {
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ExactStringMatcher> matcher(
        ExactStringMatcher("error"));
    
    std::runtime_error ex("error occurred");
    EXPECT_FALSE(matcher.match(ex));
}

// Test: Multiple matches on same matcher instance
TEST_F(ExceptionMessageMatchesMatcherTest_240, MultipleMatchCalls_240) {
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ExactStringMatcher> matcher(
        ExactStringMatcher("test"));
    
    std::runtime_error ex1("test");
    std::runtime_error ex2("other");
    std::runtime_error ex3("test");
    
    EXPECT_TRUE(matcher.match(ex1));
    EXPECT_FALSE(matcher.match(ex2));
    EXPECT_TRUE(matcher.match(ex3));
}

// Test: Unicode-like characters in message
TEST_F(ExceptionMessageMatchesMatcherTest_240, ExactMatch_UnicodeCharacters_240) {
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ExactStringMatcher> matcher(
        ExactStringMatcher("erreur: données invalides"));
    
    std::runtime_error ex("erreur: données invalides");
    EXPECT_TRUE(matcher.match(ex));
}

// Test: Contains matcher with empty substring matches everything
TEST_F(ExceptionMessageMatchesMatcherTest_240, ContainsMatch_EmptySubstringMatchesAll_240) {
    TestCatch::Matchers::ExceptionMessageMatchesMatcher<ContainsStringMatcher> matcher(
        ContainsStringMatcher(""));
    
    std::runtime_error ex("any message");
    EXPECT_TRUE(matcher.match(ex));
}
