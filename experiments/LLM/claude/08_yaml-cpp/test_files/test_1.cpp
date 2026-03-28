#include <gtest/gtest.h>
#include <string>
#include <map>

// Include the header for the class under test
#include "directives.h"

namespace YAML {
namespace {

class DirectivesTest_1 : public ::testing::Test {
 protected:
  Directives directives;
};

// Test that the default "!!" handle returns the standard YAML tag prefix
TEST_F(DirectivesTest_1, DoubleExclamationReturnsYamlOrgTag_1) {
  std::string result = directives.TranslateTagHandle("!!");
  EXPECT_EQ(result, "tag:yaml.org,2002:");
}

// Test that an unknown handle (not in tags map) is returned as-is
TEST_F(DirectivesTest_1, UnknownHandleReturnsHandleItself_1) {
  std::string result = directives.TranslateTagHandle("!foo!");
  EXPECT_EQ(result, "!foo!");
}

// Test that an empty string handle not in tags map returns empty string
TEST_F(DirectivesTest_1, EmptyHandleReturnsEmptyString_1) {
  std::string result = directives.TranslateTagHandle("");
  EXPECT_EQ(result, "");
}

// Test that a single exclamation mark not in tags returns itself
TEST_F(DirectivesTest_1, SingleExclamationReturnsItself_1) {
  std::string result = directives.TranslateTagHandle("!");
  EXPECT_EQ(result, "!");
}

// Test that when a handle is explicitly registered in the tags map, its mapped value is returned
TEST_F(DirectivesTest_1, RegisteredHandleReturnsMappedValue_1) {
  directives.tags["!myhandle!"] = "http://example.com/tags/";
  std::string result = directives.TranslateTagHandle("!myhandle!");
  EXPECT_EQ(result, "http://example.com/tags/");
}

// Test that when "!!" is explicitly registered in the tags map, it overrides the default
TEST_F(DirectivesTest_1, DoubleExclamationOverriddenByTagsMap_1) {
  directives.tags["!!"] = "http://custom.org/tags/";
  std::string result = directives.TranslateTagHandle("!!");
  EXPECT_EQ(result, "http://custom.org/tags/");
}

// Test that multiple handles can be registered and each returns its own mapped value
TEST_F(DirectivesTest_1, MultipleRegisteredHandlesReturnCorrectValues_1) {
  directives.tags["!a!"] = "http://a.com/";
  directives.tags["!b!"] = "http://b.com/";
  directives.tags["!c!"] = "http://c.com/";

  EXPECT_EQ(directives.TranslateTagHandle("!a!"), "http://a.com/");
  EXPECT_EQ(directives.TranslateTagHandle("!b!"), "http://b.com/");
  EXPECT_EQ(directives.TranslateTagHandle("!c!"), "http://c.com/");
}

// Test that a handle mapped to an empty string returns the empty string
TEST_F(DirectivesTest_1, HandleMappedToEmptyStringReturnsEmpty_1) {
  directives.tags["!empty!"] = "";
  std::string result = directives.TranslateTagHandle("!empty!");
  EXPECT_EQ(result, "");
}

// Test that a handle with special characters not in tags map returns itself
TEST_F(DirectivesTest_1, SpecialCharacterHandleReturnsItself_1) {
  std::string handle = "!@#$%^&*!";
  std::string result = directives.TranslateTagHandle(handle);
  EXPECT_EQ(result, handle);
}

// Test that a very long handle string not in tags returns itself
TEST_F(DirectivesTest_1, LongHandleReturnsItself_1) {
  std::string longHandle(1000, 'x');
  std::string result = directives.TranslateTagHandle(longHandle);
  EXPECT_EQ(result, longHandle);
}

// Test that a registered handle with a long mapped value returns the full value
TEST_F(DirectivesTest_1, RegisteredHandleWithLongValueReturnsFullValue_1) {
  std::string longValue(1000, 'y');
  directives.tags["!long!"] = longValue;
  std::string result = directives.TranslateTagHandle("!long!");
  EXPECT_EQ(result, longValue);
}

// Test that handles are case-sensitive
TEST_F(DirectivesTest_1, HandlesAreCaseSensitive_1) {
  directives.tags["!ABC!"] = "http://upper.com/";
  
  EXPECT_EQ(directives.TranslateTagHandle("!ABC!"), "http://upper.com/");
  // !abc! is not in the map, should return itself
  EXPECT_EQ(directives.TranslateTagHandle("!abc!"), "!abc!");
}

// Test triple exclamation is not treated as double exclamation
TEST_F(DirectivesTest_1, TripleExclamationIsNotDoubleExclamation_1) {
  std::string result = directives.TranslateTagHandle("!!!");
  EXPECT_EQ(result, "!!!");
}

}  // namespace
}  // namespace YAML
