#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/ostream_wrapper.h"

// We need to include the header that declares WriteTagWithPrefix
// Since it's in emitterutils, we include the relevant headers
namespace YAML {
namespace Utils {
bool WriteTagWithPrefix(ostream_wrapper& out, const std::string& prefix,
                        const std::string& tag);
}
}

class WriteTagWithPrefixTest_637 : public ::testing::Test {
 protected:
  std::string GetOutput(YAML::ostream_wrapper& out) {
    return std::string(out.str());
  }
};

// Test normal operation with simple valid prefix and tag
TEST_F(WriteTagWithPrefixTest_637, SimpleValidPrefixAndTag_637) {
  YAML::ostream_wrapper out;
  bool result = YAML::Utils::WriteTagWithPrefix(out, "yaml", "value");
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  // Should start with '!' and have '!' separating prefix from tag
  EXPECT_EQ(output[0], '!');
  // Find the second '!'
  std::size_t secondBang = output.find('!', 1);
  EXPECT_NE(secondBang, std::string::npos);
  EXPECT_EQ(output, "!yaml!value");
}

// Test with empty prefix and empty tag
TEST_F(WriteTagWithPrefixTest_637, EmptyPrefixAndEmptyTag_637) {
  YAML::ostream_wrapper out;
  bool result = YAML::Utils::WriteTagWithPrefix(out, "", "");
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  // With empty prefix and tag, should just write "!!"
  EXPECT_EQ(output, "!!");
}

// Test with empty prefix and valid tag
TEST_F(WriteTagWithPrefixTest_637, EmptyPrefixValidTag_637) {
  YAML::ostream_wrapper out;
  bool result = YAML::Utils::WriteTagWithPrefix(out, "", "sometag");
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  EXPECT_EQ(output, "!!sometag");
}

// Test with valid prefix and empty tag
TEST_F(WriteTagWithPrefixTest_637, ValidPrefixEmptyTag_637) {
  YAML::ostream_wrapper out;
  bool result = YAML::Utils::WriteTagWithPrefix(out, "prefix", "");
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  EXPECT_EQ(output, "!prefix!");
}

// Test with URI-valid characters in prefix
TEST_F(WriteTagWithPrefixTest_637, URIValidPrefixCharacters_637) {
  YAML::ostream_wrapper out;
  bool result =
      YAML::Utils::WriteTagWithPrefix(out, "tag:yaml.org,2002:", "str");
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  EXPECT_EQ(output, "!tag:yaml.org,2002:!str");
}

// Test with alphanumeric prefix and tag
TEST_F(WriteTagWithPrefixTest_637, AlphanumericPrefixAndTag_637) {
  YAML::ostream_wrapper out;
  bool result = YAML::Utils::WriteTagWithPrefix(out, "abc123", "def456");
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  EXPECT_EQ(output, "!abc123!def456");
}

// Test output goes to a stream
TEST_F(WriteTagWithPrefixTest_637, OutputToStream_637) {
  std::stringstream ss;
  YAML::ostream_wrapper out(ss);
  bool result = YAML::Utils::WriteTagWithPrefix(out, "pre", "tag");
  EXPECT_TRUE(result);
  EXPECT_EQ(ss.str(), "!pre!tag");
}

// Test with single character prefix and tag
TEST_F(WriteTagWithPrefixTest_637, SingleCharPrefixAndTag_637) {
  YAML::ostream_wrapper out;
  bool result = YAML::Utils::WriteTagWithPrefix(out, "a", "b");
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  EXPECT_EQ(output, "!a!b");
}

// Test with prefix containing hyphens and underscores (valid URI chars)
TEST_F(WriteTagWithPrefixTest_637, PrefixWithHyphensAndUnderscores_637) {
  YAML::ostream_wrapper out;
  bool result = YAML::Utils::WriteTagWithPrefix(out, "my-prefix_v1", "my-tag");
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  EXPECT_EQ(output, "!my-prefix_v1!my-tag");
}

// Test with prefix containing dots and slashes (valid URI chars)
TEST_F(WriteTagWithPrefixTest_637, PrefixWithDotsAndSlashes_637) {
  YAML::ostream_wrapper out;
  bool result =
      YAML::Utils::WriteTagWithPrefix(out, "example.com/path", "item");
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  EXPECT_EQ(output, "!example.com/path!item");
}

// Test with prefix containing percent-encoded characters (valid URI)
TEST_F(WriteTagWithPrefixTest_637, PrefixWithPercentEncoding_637) {
  YAML::ostream_wrapper out;
  bool result = YAML::Utils::WriteTagWithPrefix(out, "hello%20world", "tag");
  // %20 should be valid URI encoding
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  EXPECT_EQ(output, "!hello%20world!tag");
}

// Test that invalid prefix characters cause failure
TEST_F(WriteTagWithPrefixTest_637, InvalidPrefixCharacterSpace_637) {
  YAML::ostream_wrapper out;
  bool result = YAML::Utils::WriteTagWithPrefix(out, "hello world", "tag");
  // Space is not a valid URI character, should fail
  EXPECT_FALSE(result);
}

// Test that invalid tag characters cause failure
TEST_F(WriteTagWithPrefixTest_637, InvalidTagCharacterSpace_637) {
  YAML::ostream_wrapper out;
  bool result = YAML::Utils::WriteTagWithPrefix(out, "prefix", "hello world");
  // Space is not a valid tag character, should fail
  EXPECT_FALSE(result);
}

// Test with prefix containing a hash/fragment identifier
TEST_F(WriteTagWithPrefixTest_637, PrefixWithHash_637) {
  YAML::ostream_wrapper out;
  bool result = YAML::Utils::WriteTagWithPrefix(out, "pre#fix", "tag");
  // '#' is valid in URI
  EXPECT_TRUE(result);
}

// Test with numbers only
TEST_F(WriteTagWithPrefixTest_637, NumericPrefixAndTag_637) {
  YAML::ostream_wrapper out;
  bool result = YAML::Utils::WriteTagWithPrefix(out, "123", "456");
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  EXPECT_EQ(output, "!123!456");
}

// Test with tag containing special but valid characters
TEST_F(WriteTagWithPrefixTest_637, TagWithSpecialValidChars_637) {
  YAML::ostream_wrapper out;
  bool result = YAML::Utils::WriteTagWithPrefix(out, "ns", "my-tag_v2.0");
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  EXPECT_EQ(output, "!ns!my-tag_v2.0");
}

// Test that output always starts with '!' regardless of inputs
TEST_F(WriteTagWithPrefixTest_637, OutputStartsWithBang_637) {
  YAML::ostream_wrapper out;
  YAML::Utils::WriteTagWithPrefix(out, "x", "y");
  std::string output = GetOutput(out);
  EXPECT_FALSE(output.empty());
  EXPECT_EQ(output[0], '!');
}

// Test with longer strings
TEST_F(WriteTagWithPrefixTest_637, LongerStrings_637) {
  YAML::ostream_wrapper out;
  std::string longPrefix = "tag:example.com,2023:schema/types";
  std::string longTag = "custom-type-definition-v2";
  bool result = YAML::Utils::WriteTagWithPrefix(out, longPrefix, longTag);
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  EXPECT_EQ(output, "!" + longPrefix + "!" + longTag);
}

// Test with prefix that has invalid character at the beginning
TEST_F(WriteTagWithPrefixTest_637, InvalidCharAtBeginningOfPrefix_637) {
  YAML::ostream_wrapper out;
  bool result = YAML::Utils::WriteTagWithPrefix(out, "\x01prefix", "tag");
  EXPECT_FALSE(result);
}

// Test with tag that has invalid character at the beginning
TEST_F(WriteTagWithPrefixTest_637, InvalidCharAtBeginningOfTag_637) {
  YAML::ostream_wrapper out;
  bool result = YAML::Utils::WriteTagWithPrefix(out, "prefix", "\x01tag");
  EXPECT_FALSE(result);
}

// Test with prefix containing tab character (invalid)
TEST_F(WriteTagWithPrefixTest_637, PrefixWithTab_637) {
  YAML::ostream_wrapper out;
  bool result = YAML::Utils::WriteTagWithPrefix(out, "pre\tfix", "tag");
  EXPECT_FALSE(result);
}

// Test with tag containing newline character (invalid)
TEST_F(WriteTagWithPrefixTest_637, TagWithNewline_637) {
  YAML::ostream_wrapper out;
  bool result = YAML::Utils::WriteTagWithPrefix(out, "prefix", "ta\ng");
  EXPECT_FALSE(result);
}
