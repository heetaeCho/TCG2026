#include <gtest/gtest.h>
#include <string>
#include "yaml-cpp/emittermanip.h"

// Test normal operation with a regular string
TEST(VerbatimTagTest_15, NormalString_15) {
    YAML::_Tag tag = YAML::VerbatimTag("tag:yaml.org,2002:str");
    // Verify the tag is created successfully (we can only check that it compiles and runs)
    // Since _Tag's internals may not be fully public, we verify construction doesn't throw
    EXPECT_NO_THROW(YAML::VerbatimTag("tag:yaml.org,2002:str"));
}

// Test with an empty content string
TEST(VerbatimTagTest_15, EmptyContent_15) {
    EXPECT_NO_THROW(YAML::VerbatimTag(""));
    YAML::_Tag tag = YAML::VerbatimTag("");
    (void)tag;
}

// Test with a typical YAML tag URI
TEST(VerbatimTagTest_15, YAMLTagURI_15) {
    EXPECT_NO_THROW(YAML::VerbatimTag("tag:yaml.org,2002:int"));
    YAML::_Tag tag = YAML::VerbatimTag("tag:yaml.org,2002:int");
    (void)tag;
}

// Test with a long string
TEST(VerbatimTagTest_15, LongString_15) {
    std::string longContent(10000, 'x');
    EXPECT_NO_THROW(YAML::VerbatimTag(longContent));
    YAML::_Tag tag = YAML::VerbatimTag(longContent);
    (void)tag;
}

// Test with special characters in content
TEST(VerbatimTagTest_15, SpecialCharacters_15) {
    EXPECT_NO_THROW(YAML::VerbatimTag("!@#$%^&*()"));
    YAML::_Tag tag = YAML::VerbatimTag("!@#$%^&*()");
    (void)tag;
}

// Test with whitespace content
TEST(VerbatimTagTest_15, WhitespaceContent_15) {
    EXPECT_NO_THROW(YAML::VerbatimTag("  \t\n  "));
    YAML::_Tag tag = YAML::VerbatimTag("  \t\n  ");
    (void)tag;
}

// Test with Unicode-like content (multi-byte UTF-8)
TEST(VerbatimTagTest_15, UnicodeContent_15) {
    EXPECT_NO_THROW(YAML::VerbatimTag("tag:example.com,2024:日本語"));
    YAML::_Tag tag = YAML::VerbatimTag("tag:example.com,2024:日本語");
    (void)tag;
}

// Test that multiple calls produce independent tags
TEST(VerbatimTagTest_15, MultipleCallsIndependent_15) {
    YAML::_Tag tag1 = YAML::VerbatimTag("content1");
    YAML::_Tag tag2 = YAML::VerbatimTag("content2");
    // Both should be created without issues
    (void)tag1;
    (void)tag2;
}

// Test with URL-like content
TEST(VerbatimTagTest_15, URLContent_15) {
    EXPECT_NO_THROW(YAML::VerbatimTag("http://example.com/my-tag"));
    YAML::_Tag tag = YAML::VerbatimTag("http://example.com/my-tag");
    (void)tag;
}

// Test that the returned _Tag can be copied
TEST(VerbatimTagTest_15, CopyConstructible_15) {
    YAML::_Tag tag1 = YAML::VerbatimTag("test");
    YAML::_Tag tag2 = tag1;
    (void)tag2;
}

// Test with single character content
TEST(VerbatimTagTest_15, SingleCharContent_15) {
    EXPECT_NO_THROW(YAML::VerbatimTag("x"));
    YAML::_Tag tag = YAML::VerbatimTag("x");
    (void)tag;
}

// Test with null character embedded in string
TEST(VerbatimTagTest_15, EmbeddedNullCharacter_15) {
    std::string content("before\0after", 12);
    EXPECT_NO_THROW(YAML::VerbatimTag(content));
    YAML::_Tag tag = YAML::VerbatimTag(content);
    (void)tag;
}
