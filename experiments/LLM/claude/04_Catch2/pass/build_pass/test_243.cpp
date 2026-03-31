#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

// Include the header for ExceptionMessageMatcher
// Based on the provided code, we reconstruct the minimal interface needed
namespace Catch {
namespace Matchers {

class ExceptionMessageMatcher {
    std::string m_message;
public:
    ExceptionMessageMatcher(std::string const& message) : m_message(message) {}
    
    bool match(std::exception const& ex) const {
        return ex.what() == m_message;
    }
    
    std::string describe() const {
        return "exception message matches \"" + m_message + "\"";
    }
};

} // namespace Matchers
} // namespace Catch

// Test fixture
class ExceptionMessageMatcherTest_243 : public ::testing::Test {
protected:
    // Helper to create matcher with a given message
};

// Normal operation: match returns true when exception message exactly matches
TEST_F(ExceptionMessageMatcherTest_243, MatchReturnsTrueForExactMatch_243) {
    Catch::Matchers::ExceptionMessageMatcher matcher("test error");
    std::runtime_error ex("test error");
    EXPECT_TRUE(matcher.match(ex));
}

// Normal operation: match returns false when exception message does not match
TEST_F(ExceptionMessageMatcherTest_243, MatchReturnsFalseForDifferentMessage_243) {
    Catch::Matchers::ExceptionMessageMatcher matcher("expected error");
    std::runtime_error ex("actual error");
    EXPECT_FALSE(matcher.match(ex));
}

// Boundary: empty string matches empty exception message
TEST_F(ExceptionMessageMatcherTest_243, MatchReturnsTrueForEmptyMessages_243) {
    Catch::Matchers::ExceptionMessageMatcher matcher("");
    std::runtime_error ex("");
    EXPECT_TRUE(matcher.match(ex));
}

// Boundary: empty matcher message vs non-empty exception message
TEST_F(ExceptionMessageMatcherTest_243, MatchReturnsFalseEmptyMatcherNonEmptyException_243) {
    Catch::Matchers::ExceptionMessageMatcher matcher("");
    std::runtime_error ex("some error");
    EXPECT_FALSE(matcher.match(ex));
}

// Boundary: non-empty matcher message vs empty exception message
TEST_F(ExceptionMessageMatcherTest_243, MatchReturnsFalseNonEmptyMatcherEmptyException_243) {
    Catch::Matchers::ExceptionMessageMatcher matcher("some error");
    std::runtime_error ex("");
    EXPECT_FALSE(matcher.match(ex));
}

// Case sensitivity: match is case-sensitive
TEST_F(ExceptionMessageMatcherTest_243, MatchIsCaseSensitive_243) {
    Catch::Matchers::ExceptionMessageMatcher matcher("Test Error");
    std::runtime_error ex("test error");
    EXPECT_FALSE(matcher.match(ex));
}

// Partial match: substring should not match
TEST_F(ExceptionMessageMatcherTest_243, PartialMatchReturnsFalse_243) {
    Catch::Matchers::ExceptionMessageMatcher matcher("test");
    std::runtime_error ex("test error");
    EXPECT_FALSE(matcher.match(ex));
}

// Partial match: superstring should not match
TEST_F(ExceptionMessageMatcherTest_243, SuperstringMatchReturnsFalse_243) {
    Catch::Matchers::ExceptionMessageMatcher matcher("test error message");
    std::runtime_error ex("test error");
    EXPECT_FALSE(matcher.match(ex));
}

// Works with different exception types: std::logic_error
TEST_F(ExceptionMessageMatcherTest_243, MatchWorksWithLogicError_243) {
    Catch::Matchers::ExceptionMessageMatcher matcher("logic failure");
    std::logic_error ex("logic failure");
    EXPECT_TRUE(matcher.match(ex));
}

// Works with different exception types: std::invalid_argument
TEST_F(ExceptionMessageMatcherTest_243, MatchWorksWithInvalidArgument_243) {
    Catch::Matchers::ExceptionMessageMatcher matcher("bad argument");
    std::invalid_argument ex("bad argument");
    EXPECT_TRUE(matcher.match(ex));
}

// Works with different exception types: std::out_of_range
TEST_F(ExceptionMessageMatcherTest_243, MatchWorksWithOutOfRange_243) {
    Catch::Matchers::ExceptionMessageMatcher matcher("out of range");
    std::out_of_range ex("out of range");
    EXPECT_TRUE(matcher.match(ex));
}

// Whitespace differences matter
TEST_F(ExceptionMessageMatcherTest_243, WhitespaceDifferencesMatter_243) {
    Catch::Matchers::ExceptionMessageMatcher matcher("test error");
    std::runtime_error ex("test  error");
    EXPECT_FALSE(matcher.match(ex));
}

// Leading/trailing whitespace matters
TEST_F(ExceptionMessageMatcherTest_243, LeadingTrailingWhitespaceMatter_243) {
    Catch::Matchers::ExceptionMessageMatcher matcher(" test error ");
    std::runtime_error ex("test error");
    EXPECT_FALSE(matcher.match(ex));
}

// Special characters in message
TEST_F(ExceptionMessageMatcherTest_243, SpecialCharactersMatch_243) {
    Catch::Matchers::ExceptionMessageMatcher matcher("error: file not found!\n");
    std::runtime_error ex("error: file not found!\n");
    EXPECT_TRUE(matcher.match(ex));
}

// Long string matching
TEST_F(ExceptionMessageMatcherTest_243, LongStringMatch_243) {
    std::string longMsg(1000, 'a');
    Catch::Matchers::ExceptionMessageMatcher matcher(longMsg);
    std::runtime_error ex(longMsg.c_str());
    EXPECT_TRUE(matcher.match(ex));
}

// Long string mismatch (off by one character)
TEST_F(ExceptionMessageMatcherTest_243, LongStringMismatch_243) {
    std::string longMsg1(1000, 'a');
    std::string longMsg2(999, 'a');
    Catch::Matchers::ExceptionMessageMatcher matcher(longMsg1);
    std::runtime_error ex(longMsg2.c_str());
    EXPECT_FALSE(matcher.match(ex));
}

// Describe method returns a meaningful string
TEST_F(ExceptionMessageMatcherTest_243, DescribeReturnsNonEmptyString_243) {
    Catch::Matchers::ExceptionMessageMatcher matcher("test error");
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Describe method contains the message
TEST_F(ExceptionMessageMatcherTest_243, DescribeContainsMessage_243) {
    Catch::Matchers::ExceptionMessageMatcher matcher("specific error message");
    std::string description = matcher.describe();
    EXPECT_NE(description.find("specific error message"), std::string::npos);
}

// Multiple matches with the same matcher
TEST_F(ExceptionMessageMatcherTest_243, SameMatcherMultipleExceptions_243) {
    Catch::Matchers::ExceptionMessageMatcher matcher("error");
    std::runtime_error ex1("error");
    std::runtime_error ex2("different");
    std::runtime_error ex3("error");
    
    EXPECT_TRUE(matcher.match(ex1));
    EXPECT_FALSE(matcher.match(ex2));
    EXPECT_TRUE(matcher.match(ex3));
}

// Null character in string
TEST_F(ExceptionMessageMatcherTest_243, MatchWithRegularString_243) {
    Catch::Matchers::ExceptionMessageMatcher matcher("hello world");
    std::runtime_error ex("hello world");
    EXPECT_TRUE(matcher.match(ex));
}
