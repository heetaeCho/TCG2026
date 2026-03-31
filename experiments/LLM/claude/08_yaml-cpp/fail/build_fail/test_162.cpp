#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "yaml-cpp/exceptions.h"
#include "stream.h"
#include "exp.h"
#include "scantoken.h"

// Forward declare the function we're testing
namespace YAML {
const std::string ScanVerbatimTag(Stream& INPUT);
}

class ScanVerbatimTagTest_162 : public ::testing::Test {
protected:
};

// Test normal verbatim tag: "!<tag:yaml.org,2002:str>" after the '!' is consumed externally
// ScanVerbatimTag expects the stream to start at '<' (which it consumes via get()),
// then reads URI characters until '>'
TEST_F(ScanVerbatimTagTest_162, NormalVerbatimTag_162) {
    // The function calls INPUT.get() first to consume the '<', then reads until '>'
    std::stringstream ss("<tag:yaml.org,2002:str>");
    YAML::Stream stream(ss);
    std::string result = YAML::ScanVerbatimTag(stream);
    EXPECT_EQ(result, "tag:yaml.org,2002:str");
}

// Test empty verbatim tag: "<>"
TEST_F(ScanVerbatimTagTest_162, EmptyVerbatimTag_162) {
    std::stringstream ss("<>");
    YAML::Stream stream(ss);
    std::string result = YAML::ScanVerbatimTag(stream);
    EXPECT_EQ(result, "");
}

// Test verbatim tag with simple ASCII content
TEST_F(ScanVerbatimTagTest_162, SimpleASCIITag_162) {
    std::stringstream ss("<hello>");
    YAML::Stream stream(ss);
    std::string result = YAML::ScanVerbatimTag(stream);
    EXPECT_EQ(result, "hello");
}

// Test verbatim tag with URI characters including percent-encoded
TEST_F(ScanVerbatimTagTest_162, URIWithPercentEncoding_162) {
    std::stringstream ss("<tag%21test>");
    YAML::Stream stream(ss);
    std::string result = YAML::ScanVerbatimTag(stream);
    EXPECT_EQ(result, "tag%21test");
}

// Test missing closing '>' - should throw ParserException
TEST_F(ScanVerbatimTagTest_162, MissingClosingBracketThrows_162) {
    // Stream with valid URI chars but no '>' at the end - stream ends
    std::stringstream ss("<tag:yaml.org");
    YAML::Stream stream(ss);
    EXPECT_THROW(YAML::ScanVerbatimTag(stream), YAML::ParserException);
}

// Test invalid character in tag (non-URI character) - should throw ParserException
TEST_F(ScanVerbatimTagTest_162, InvalidCharacterThrows_162) {
    // Space is not a valid URI character
    std::stringstream ss("< invalid>");
    YAML::Stream stream(ss);
    EXPECT_THROW(YAML::ScanVerbatimTag(stream), YAML::ParserException);
}

// Test completely empty stream after '<' - should throw
TEST_F(ScanVerbatimTagTest_162, EmptyStreamAfterOpenThrows_162) {
    std::stringstream ss("<");
    YAML::Stream stream(ss);
    EXPECT_THROW(YAML::ScanVerbatimTag(stream), YAML::ParserException);
}

// Test verbatim tag with numbers and slashes (common URI)
TEST_F(ScanVerbatimTagTest_162, URIWithSlashesAndNumbers_162) {
    std::stringstream ss("<http://example.com/ns/2023>");
    YAML::Stream stream(ss);
    std::string result = YAML::ScanVerbatimTag(stream);
    EXPECT_EQ(result, "http://example.com/ns/2023");
}

// Test verbatim tag with single character
TEST_F(ScanVerbatimTagTest_162, SingleCharacterTag_162) {
    std::stringstream ss("<a>");
    YAML::Stream stream(ss);
    std::string result = YAML::ScanVerbatimTag(stream);
    EXPECT_EQ(result, "a");
}

// Test that exception message contains expected error
TEST_F(ScanVerbatimTagTest_162, ExceptionMessageContent_162) {
    std::stringstream ss("<no-end-bracket");
    YAML::Stream stream(ss);
    try {
        YAML::ScanVerbatimTag(stream);
        FAIL() << "Expected ParserException to be thrown";
    } catch (const YAML::ParserException& e) {
        std::string msg = e.what();
        EXPECT_NE(msg.find("end of verbatim tag not found"), std::string::npos);
    }
}

// Test tag with exclamation mark (valid URI char)
TEST_F(ScanVerbatimTagTest_162, TagWithExclamation_162) {
    std::stringstream ss("<!foo>");
    YAML::Stream stream(ss);
    std::string result = YAML::ScanVerbatimTag(stream);
    EXPECT_EQ(result, "!foo");
}

// Test verbatim tag with hash and other URI-valid special chars
TEST_F(ScanVerbatimTagTest_162, TagWithSpecialURIChars_162) {
    std::stringstream ss("<tag:example.com,2000:app/int#fragment>");
    YAML::Stream stream(ss);
    std::string result = YAML::ScanVerbatimTag(stream);
    EXPECT_EQ(result, "tag:example.com,2000:app/int#fragment");
}

// Test newline in tag should cause an error (not valid URI)
TEST_F(ScanVerbatimTagTest_162, NewlineInTagThrows_162) {
    std::stringstream ss("<tag\n>");
    YAML::Stream stream(ss);
    EXPECT_THROW(YAML::ScanVerbatimTag(stream), YAML::ParserException);
}
