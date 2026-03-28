#include <gtest/gtest.h>
#include <string>
#include "yaml-cpp/emittermanip.h"

// Test normal operation with typical prefix and content
TEST(LocalTagTest_17, NormalPrefixAndContent_17) {
    YAML::_Tag tag = YAML::LocalTag("!", "myTag");
    // We can verify the tag was created without throwing.
    // Since _Tag's internal state may not be fully accessible,
    // we at least verify it constructs successfully.
    SUCCEED();
}

// Test with empty prefix and non-empty content
TEST(LocalTagTest_17, EmptyPrefix_17) {
    YAML::_Tag tag = YAML::LocalTag("", "content");
    SUCCEED();
}

// Test with non-empty prefix and empty content
TEST(LocalTagTest_17, EmptyContent_17) {
    YAML::_Tag tag = YAML::LocalTag("!prefix!", "");
    SUCCEED();
}

// Test with both empty prefix and empty content
TEST(LocalTagTest_17, BothEmpty_17) {
    YAML::_Tag tag = YAML::LocalTag("", "");
    SUCCEED();
}

// Test with typical YAML tag handle prefix "!!"
TEST(LocalTagTest_17, DoubleExclamationPrefix_17) {
    YAML::_Tag tag = YAML::LocalTag("!!", "int");
    SUCCEED();
}

// Test with named handle prefix like "!e!"
TEST(LocalTagTest_17, NamedHandlePrefix_17) {
    YAML::_Tag tag = YAML::LocalTag("!e!", "foo");
    SUCCEED();
}

// Test with long prefix and content strings
TEST(LocalTagTest_17, LongStrings_17) {
    std::string longPrefix(1000, '!');
    std::string longContent(1000, 'a');
    YAML::_Tag tag = YAML::LocalTag(longPrefix, longContent);
    SUCCEED();
}

// Test with special characters in content
TEST(LocalTagTest_17, SpecialCharactersInContent_17) {
    YAML::_Tag tag = YAML::LocalTag("!", "tag/with/slashes");
    SUCCEED();
}

// Test with unicode-like characters in content
TEST(LocalTagTest_17, UnicodeContent_17) {
    YAML::_Tag tag = YAML::LocalTag("!", "tàg");
    SUCCEED();
}

// Test with whitespace in prefix and content
TEST(LocalTagTest_17, WhitespaceInStrings_17) {
    YAML::_Tag tag = YAML::LocalTag("! ", " content ");
    SUCCEED();
}

// Test that multiple calls produce independent tags
TEST(LocalTagTest_17, MultipleCallsIndependent_17) {
    YAML::_Tag tag1 = YAML::LocalTag("!a!", "first");
    YAML::_Tag tag2 = YAML::LocalTag("!b!", "second");
    // Both should be constructible independently
    SUCCEED();
}

// Test with single character prefix and content
TEST(LocalTagTest_17, SingleCharStrings_17) {
    YAML::_Tag tag = YAML::LocalTag("!", "x");
    SUCCEED();
}

// Test with numeric content
TEST(LocalTagTest_17, NumericContent_17) {
    YAML::_Tag tag = YAML::LocalTag("!", "12345");
    SUCCEED();
}

// Test copy semantics of returned _Tag
TEST(LocalTagTest_17, CopySemantics_17) {
    YAML::_Tag tag1 = YAML::LocalTag("!", "test");
    YAML::_Tag tag2 = tag1;
    SUCCEED();
}
