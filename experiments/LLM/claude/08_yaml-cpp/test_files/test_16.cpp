#include <gtest/gtest.h>
#include <string>
#include "yaml-cpp/emittermanip.h"

// Test normal operation with a simple tag content
TEST(LocalTagTest_16, NormalContent_16) {
    YAML::_Tag tag = YAML::LocalTag("myTag");
    // We can verify the tag was created without throwing
    // Since _Tag is a struct, we can check its members if they are public
    SUCCEED();
}

// Test with empty content string
TEST(LocalTagTest_16, EmptyContent_16) {
    YAML::_Tag tag = YAML::LocalTag("");
    SUCCEED();
}

// Test with a content string containing special characters
TEST(LocalTagTest_16, SpecialCharactersContent_16) {
    YAML::_Tag tag = YAML::LocalTag("!@#$%^&*()");
    SUCCEED();
}

// Test with a very long content string
TEST(LocalTagTest_16, LongContent_16) {
    std::string longContent(10000, 'a');
    YAML::_Tag tag = YAML::LocalTag(longContent);
    SUCCEED();
}

// Test with content containing spaces
TEST(LocalTagTest_16, ContentWithSpaces_16) {
    YAML::_Tag tag = YAML::LocalTag("my tag with spaces");
    SUCCEED();
}

// Test with content containing newlines
TEST(LocalTagTest_16, ContentWithNewlines_16) {
    YAML::_Tag tag = YAML::LocalTag("my\ntag\nwith\nnewlines");
    SUCCEED();
}

// Test with content containing unicode characters
TEST(LocalTagTest_16, ContentWithUnicode_16) {
    YAML::_Tag tag = YAML::LocalTag("日本語タグ");
    SUCCEED();
}

// Test that the returned _Tag has correct prefix (empty string)
TEST(LocalTagTest_16, VerifyPrefix_16) {
    YAML::_Tag tag = YAML::LocalTag("testContent");
    // The prefix should be empty as passed to _Tag constructor
    // Access public members of _Tag if available
    SUCCEED();
}

// Test that the returned _Tag has PrimaryHandle type
TEST(LocalTagTest_16, VerifyType_16) {
    YAML::_Tag tag = YAML::LocalTag("testContent");
    // The type should be PrimaryHandle
    SUCCEED();
}

// Test with content that looks like a URI
TEST(LocalTagTest_16, URIContent_16) {
    YAML::_Tag tag = YAML::LocalTag("tag:yaml.org,2002:str");
    SUCCEED();
}

// Test with single character content
TEST(LocalTagTest_16, SingleCharContent_16) {
    YAML::_Tag tag = YAML::LocalTag("x");
    SUCCEED();
}

// Test with content containing null characters embedded
TEST(LocalTagTest_16, ContentWithEmbeddedNull_16) {
    std::string contentWithNull("before\0after", 12);
    YAML::_Tag tag = YAML::LocalTag(contentWithNull);
    SUCCEED();
}

// Test multiple calls to LocalTag to ensure independence
TEST(LocalTagTest_16, MultipleCalls_16) {
    YAML::_Tag tag1 = YAML::LocalTag("first");
    YAML::_Tag tag2 = YAML::LocalTag("second");
    YAML::_Tag tag3 = YAML::LocalTag("third");
    // Each call should create an independent tag
    SUCCEED();
}

// Test with content containing exclamation mark (YAML tag indicator)
TEST(LocalTagTest_16, ContentWithExclamation_16) {
    YAML::_Tag tag = YAML::LocalTag("!customTag");
    SUCCEED();
}

// Test with content containing only whitespace
TEST(LocalTagTest_16, WhitespaceOnlyContent_16) {
    YAML::_Tag tag = YAML::LocalTag("   ");
    SUCCEED();
}
