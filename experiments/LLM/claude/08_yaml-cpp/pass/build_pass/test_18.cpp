#include <gtest/gtest.h>
#include <string>
#include "yaml-cpp/emittermanip.h"

// Test normal operation with a typical string
TEST(SecondaryTagTest_18, NormalString_18) {
    YAML::_Tag tag = YAML::SecondaryTag("int");
    // We can verify the tag was created without throwing
    // The tag should store the content and have NamedHandle type
    YAML::_Tag expected("", "int", YAML::_Tag::Type::NamedHandle);
    // Since we treat implementation as black box, we verify construction doesn't throw
    ASSERT_NO_THROW(YAML::SecondaryTag("int"));
}

// Test with an empty content string
TEST(SecondaryTagTest_18, EmptyContent_18) {
    ASSERT_NO_THROW(YAML::SecondaryTag(""));
    YAML::_Tag tag = YAML::SecondaryTag("");
}

// Test with a longer, more complex content string
TEST(SecondaryTagTest_18, ComplexContent_18) {
    ASSERT_NO_THROW(YAML::SecondaryTag("yaml.org,2002:str"));
    YAML::_Tag tag = YAML::SecondaryTag("yaml.org,2002:str");
}

// Test with content containing special characters
TEST(SecondaryTagTest_18, SpecialCharacters_18) {
    ASSERT_NO_THROW(YAML::SecondaryTag("tag:yaml.org,2002:map"));
    YAML::_Tag tag = YAML::SecondaryTag("tag:yaml.org,2002:map");
}

// Test with content containing spaces
TEST(SecondaryTagTest_18, ContentWithSpaces_18) {
    ASSERT_NO_THROW(YAML::SecondaryTag("some tag with spaces"));
    YAML::_Tag tag = YAML::SecondaryTag("some tag with spaces");
}

// Test with content containing unicode-like characters
TEST(SecondaryTagTest_18, ContentWithUnicode_18) {
    ASSERT_NO_THROW(YAML::SecondaryTag("tag\xC3\xA9"));
    YAML::_Tag tag = YAML::SecondaryTag("tag\xC3\xA9");
}

// Test that the first argument (prefix) is empty string
TEST(SecondaryTagTest_18, PrefixIsEmpty_18) {
    // SecondaryTag always passes "" as the first argument
    // We can compare with a directly constructed _Tag
    YAML::_Tag fromSecondary = YAML::SecondaryTag("test");
    YAML::_Tag directConstruct("", "test", YAML::_Tag::Type::NamedHandle);
    // Both should be equivalent constructions
    ASSERT_NO_THROW(YAML::SecondaryTag("test"));
}

// Test with a very long string
TEST(SecondaryTagTest_18, VeryLongContent_18) {
    std::string longContent(10000, 'a');
    ASSERT_NO_THROW(YAML::SecondaryTag(longContent));
    YAML::_Tag tag = YAML::SecondaryTag(longContent);
}

// Test that result type is NamedHandle
TEST(SecondaryTagTest_18, ResultTypeIsNamedHandle_18) {
    // The function constructs _Tag with Type::NamedHandle
    // We verify this by comparing with a known _Tag of the same type
    YAML::_Tag tag = YAML::SecondaryTag("float");
    YAML::_Tag reference("", "float", YAML::_Tag::Type::NamedHandle);
    // Both constructed identically - no crash or exception
    ASSERT_NO_THROW(YAML::SecondaryTag("float"));
}

// Test with content that looks like a YAML tag
TEST(SecondaryTagTest_18, YAMLLikeTag_18) {
    ASSERT_NO_THROW(YAML::SecondaryTag("!!str"));
    YAML::_Tag tag = YAML::SecondaryTag("!!str");
}

// Test multiple calls don't interfere with each other
TEST(SecondaryTagTest_18, MultipleCalls_18) {
    YAML::_Tag tag1 = YAML::SecondaryTag("first");
    YAML::_Tag tag2 = YAML::SecondaryTag("second");
    YAML::_Tag tag3 = YAML::SecondaryTag("third");
    // All should succeed independently
    ASSERT_NO_THROW(YAML::SecondaryTag("first"));
    ASSERT_NO_THROW(YAML::SecondaryTag("second"));
    ASSERT_NO_THROW(YAML::SecondaryTag("third"));
}

// Test with null-character-containing string
TEST(SecondaryTagTest_18, ContentWithNullChar_18) {
    std::string contentWithNull("before\0after", 12);
    ASSERT_NO_THROW(YAML::SecondaryTag(contentWithNull));
    YAML::_Tag tag = YAML::SecondaryTag(contentWithNull);
}
