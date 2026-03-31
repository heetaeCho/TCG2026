#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

// Include the header for ExceptionMessageMatcher
// Based on the provided code, we need to include the relevant header
namespace Catch {
namespace Matchers {

class ExceptionMessageMatcher {
    std::string m_message;

public:
    ExceptionMessageMatcher(std::string const& message) : m_message(message) {}

    bool match(std::exception const& ex) const {
        return m_message == ex.what();
    }

    std::string describe() const {
        return "exception message matches \"" + m_message + '"';
    }
};

} // namespace Matchers
} // namespace Catch

// ===== TESTS =====

class ExceptionMessageMatcherTest_244 : public ::testing::Test {
protected:
    // Helper to create matchers with various messages
};

// Test that describe() returns the expected format with a simple message
TEST_F(ExceptionMessageMatcherTest_244, DescribeReturnsFormattedMessage_244) {
    Catch::Matchers::ExceptionMessageMatcher matcher("test error");
    std::string result = matcher.describe();
    EXPECT_EQ(result, "exception message matches \"test error\"");
}

// Test that describe() works with an empty message
TEST_F(ExceptionMessageMatcherTest_244, DescribeWithEmptyMessage_244) {
    Catch::Matchers::ExceptionMessageMatcher matcher("");
    std::string result = matcher.describe();
    EXPECT_EQ(result, "exception message matches \"\"");
}

// Test that describe() works with special characters in message
TEST_F(ExceptionMessageMatcherTest_244, DescribeWithSpecialCharacters_244) {
    Catch::Matchers::ExceptionMessageMatcher matcher("error: \"unexpected\" value");
    std::string result = matcher.describe();
    EXPECT_EQ(result, "exception message matches \"error: \"unexpected\" value\"");
}

// Test that match() returns true when exception message matches exactly
TEST_F(ExceptionMessageMatcherTest_244, MatchReturnsTrueForExactMatch_244) {
    Catch::Matchers::ExceptionMessageMatcher matcher("test error");
    std::runtime_error ex("test error");
    EXPECT_TRUE(matcher.match(ex));
}

// Test that match() returns false when exception message does not match
TEST_F(ExceptionMessageMatcherTest_244, MatchReturnsFalseForMismatch_244) {
    Catch::Matchers::ExceptionMessageMatcher matcher("test error");
    std::runtime_error ex("different error");
    EXPECT_FALSE(matcher.match(ex));
}

// Test that match() returns false for partial match (substring)
TEST_F(ExceptionMessageMatcherTest_244, MatchReturnsFalseForPartialMatch_244) {
    Catch::Matchers::ExceptionMessageMatcher matcher("test");
    std::runtime_error ex("test error");
    EXPECT_FALSE(matcher.match(ex));
}

// Test that match() returns false when matcher message is longer than exception message
TEST_F(ExceptionMessageMatcherTest_244, MatchReturnsFalseWhenMatcherMessageLonger_244) {
    Catch::Matchers::ExceptionMessageMatcher matcher("test error message extended");
    std::runtime_error ex("test error");
    EXPECT_FALSE(matcher.match(ex));
}

// Test that match() works with empty expected message and empty exception message
TEST_F(ExceptionMessageMatcherTest_244, MatchWithEmptyMessages_244) {
    Catch::Matchers::ExceptionMessageMatcher matcher("");
    std::runtime_error ex("");
    EXPECT_TRUE(matcher.match(ex));
}

// Test that match() returns false when expected is empty but exception is not
TEST_F(ExceptionMessageMatcherTest_244, MatchEmptyExpectedNonEmptyException_244) {
    Catch::Matchers::ExceptionMessageMatcher matcher("");
    std::runtime_error ex("some error");
    EXPECT_FALSE(matcher.match(ex));
}

// Test that match() returns false when expected is non-empty but exception is empty
TEST_F(ExceptionMessageMatcherTest_244, MatchNonEmptyExpectedEmptyException_244) {
    Catch::Matchers::ExceptionMessageMatcher matcher("some error");
    std::runtime_error ex("");
    EXPECT_FALSE(matcher.match(ex));
}

// Test match with std::logic_error (another std::exception subclass)
TEST_F(ExceptionMessageMatcherTest_244, MatchWithLogicError_244) {
    Catch::Matchers::ExceptionMessageMatcher matcher("logic failure");
    std::logic_error ex("logic failure");
    EXPECT_TRUE(matcher.match(ex));
}

// Test match with std::invalid_argument
TEST_F(ExceptionMessageMatcherTest_244, MatchWithInvalidArgument_244) {
    Catch::Matchers::ExceptionMessageMatcher matcher("bad argument");
    std::invalid_argument ex("bad argument");
    EXPECT_TRUE(matcher.match(ex));
}

// Test that match is case-sensitive
TEST_F(ExceptionMessageMatcherTest_244, MatchIsCaseSensitive_244) {
    Catch::Matchers::ExceptionMessageMatcher matcher("Test Error");
    std::runtime_error ex("test error");
    EXPECT_FALSE(matcher.match(ex));
}

// Test describe with a very long message
TEST_F(ExceptionMessageMatcherTest_244, DescribeWithLongMessage_244) {
    std::string longMsg(1000, 'x');
    Catch::Matchers::ExceptionMessageMatcher matcher(longMsg);
    std::string result = matcher.describe();
    EXPECT_EQ(result, "exception message matches \"" + longMsg + "\"");
}

// Test match with a message containing newlines
TEST_F(ExceptionMessageMatcherTest_244, MatchWithNewlineInMessage_244) {
    Catch::Matchers::ExceptionMessageMatcher matcher("line1\nline2");
    std::runtime_error ex("line1\nline2");
    EXPECT_TRUE(matcher.match(ex));
}

// Test match with a message containing whitespace differences
TEST_F(ExceptionMessageMatcherTest_244, MatchWithTrailingWhitespace_244) {
    Catch::Matchers::ExceptionMessageMatcher matcher("test error ");
    std::runtime_error ex("test error");
    EXPECT_FALSE(matcher.match(ex));
}

// Test match with a message containing leading whitespace differences
TEST_F(ExceptionMessageMatcherTest_244, MatchWithLeadingWhitespace_244) {
    Catch::Matchers::ExceptionMessageMatcher matcher(" test error");
    std::runtime_error ex("test error");
    EXPECT_FALSE(matcher.match(ex));
}
