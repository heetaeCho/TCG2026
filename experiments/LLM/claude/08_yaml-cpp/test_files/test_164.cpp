#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "yaml-cpp/exceptions.h"
#include "stream.h"
#include "exp.h"

// Forward declaration of the function under test
namespace YAML {
const std::string ScanTagSuffix(Stream& INPUT);
}

class ScanTagSuffixTest_164 : public ::testing::Test {
protected:
};

// Test normal operation: a simple alphanumeric tag suffix
TEST_F(ScanTagSuffixTest_164, SimpleAlphanumericSuffix_164) {
    std::stringstream ss("hello ");
    YAML::Stream stream(ss);
    std::string result = YAML::ScanTagSuffix(stream);
    EXPECT_FALSE(result.empty());
}

// Test that an empty input throws ParserException with TAG_WITH_NO_SUFFIX
TEST_F(ScanTagSuffixTest_164, EmptyInputThrowsException_164) {
    std::stringstream ss("");
    YAML::Stream stream(ss);
    EXPECT_THROW({
        YAML::ScanTagSuffix(stream);
    }, YAML::ParserException);
}

// Test that input starting with a non-tag character throws exception
TEST_F(ScanTagSuffixTest_164, NonTagCharacterThrowsException_164) {
    // Space is not a valid tag character, so it should result in empty tag -> exception
    std::stringstream ss(" ");
    YAML::Stream stream(ss);
    EXPECT_THROW({
        YAML::ScanTagSuffix(stream);
    }, YAML::ParserException);
}

// Test a single character tag suffix
TEST_F(ScanTagSuffixTest_164, SingleCharacterSuffix_164) {
    std::stringstream ss("a ");
    YAML::Stream stream(ss);
    std::string result = YAML::ScanTagSuffix(stream);
    EXPECT_EQ(result, "a");
}

// Test a tag suffix with URI-like characters
TEST_F(ScanTagSuffixTest_164, URILikeSuffix_164) {
    std::stringstream ss("tag:yaml.org,2002:str ");
    YAML::Stream stream(ss);
    std::string result = YAML::ScanTagSuffix(stream);
    EXPECT_FALSE(result.empty());
}

// Test a longer tag suffix
TEST_F(ScanTagSuffixTest_164, LongerTagSuffix_164) {
    std::stringstream ss("abcdefghijklmnopqrstuvwxyz ");
    YAML::Stream stream(ss);
    std::string result = YAML::ScanTagSuffix(stream);
    EXPECT_EQ(result, "abcdefghijklmnopqrstuvwxyz");
}

// Test tag suffix with digits
TEST_F(ScanTagSuffixTest_164, TagSuffixWithDigits_164) {
    std::stringstream ss("abc123 ");
    YAML::Stream stream(ss);
    std::string result = YAML::ScanTagSuffix(stream);
    EXPECT_EQ(result, "abc123");
}

// Test tag suffix stops at whitespace
TEST_F(ScanTagSuffixTest_164, TagSuffixStopsAtWhitespace_164) {
    std::stringstream ss("hello world");
    YAML::Stream stream(ss);
    std::string result = YAML::ScanTagSuffix(stream);
    // Should stop at space, so only "hello" is consumed
    EXPECT_EQ(result, "hello");
}

// Test exception message content
TEST_F(ScanTagSuffixTest_164, ExceptionContainsCorrectMessage_164) {
    std::stringstream ss("");
    YAML::Stream stream(ss);
    try {
        YAML::ScanTagSuffix(stream);
        FAIL() << "Expected ParserException";
    } catch (const YAML::ParserException& e) {
        std::string msg = e.what();
        EXPECT_NE(msg.find("tag handle with no suffix"), std::string::npos);
    }
}

// Test tag suffix with hyphen and underscore (common in tag URIs)
TEST_F(ScanTagSuffixTest_164, TagSuffixWithHyphenUnderscore_164) {
    std::stringstream ss("my-tag_name ");
    YAML::Stream stream(ss);
    std::string result = YAML::ScanTagSuffix(stream);
    EXPECT_FALSE(result.empty());
}

// Test that newline terminates tag suffix
TEST_F(ScanTagSuffixTest_164, NewlineTerminatesSuffix_164) {
    std::stringstream ss("tag\nrest");
    YAML::Stream stream(ss);
    std::string result = YAML::ScanTagSuffix(stream);
    EXPECT_EQ(result, "tag");
}

// Test that tab character (if not matching Tag regex) throws or stops
TEST_F(ScanTagSuffixTest_164, TabInputThrowsException_164) {
    std::stringstream ss("\t");
    YAML::Stream stream(ss);
    EXPECT_THROW({
        YAML::ScanTagSuffix(stream);
    }, YAML::ParserException);
}

// Test tag suffix with percent-encoded characters (common in URIs)
TEST_F(ScanTagSuffixTest_164, PercentEncodedCharacters_164) {
    std::stringstream ss("tag%20name ");
    YAML::Stream stream(ss);
    std::string result = YAML::ScanTagSuffix(stream);
    EXPECT_FALSE(result.empty());
}
