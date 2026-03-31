#include "gtest/gtest.h"

#include "catch2/internal/catch_tag_alias_registry.hpp"
#include "catch2/catch_tag_alias.hpp"
#include "catch2/internal/catch_source_line_info.hpp"

#include <string>
#include <stdexcept>

class TagAliasRegistryTest_677 : public ::testing::Test {
protected:
    Catch::TagAliasRegistry registry;
    Catch::SourceLineInfo defaultLineInfo{"test_file.cpp", 1};
    Catch::SourceLineInfo secondLineInfo{"test_file2.cpp", 10};
};

// Test: Adding a valid alias succeeds and can be found
TEST_F(TagAliasRegistryTest_677, AddValidAlias_677) {
    EXPECT_NO_THROW(registry.add("[@fast]", "[fast]", defaultLineInfo));
    const Catch::TagAlias* result = registry.find("[@fast]");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag, "[fast]");
}

// Test: Finding a non-existent alias returns nullptr
TEST_F(TagAliasRegistryTest_677, FindNonExistentAliasReturnsNull_677) {
    const Catch::TagAlias* result = registry.find("[@nonexistent]");
    EXPECT_EQ(result, nullptr);
}

// Test: Adding an alias that doesn't start with [@ throws
TEST_F(TagAliasRegistryTest_677, AddAliasMissingBracketAtPrefix_677) {
    EXPECT_THROW(registry.add("fast]", "[fast]", defaultLineInfo), std::runtime_error);
}

// Test: Adding an alias that doesn't end with ] throws
TEST_F(TagAliasRegistryTest_677, AddAliasMissingSuffix_677) {
    EXPECT_THROW(registry.add("[@fast", "[fast]", defaultLineInfo), std::runtime_error);
}

// Test: Adding an alias with completely wrong format throws
TEST_F(TagAliasRegistryTest_677, AddAliasWrongFormat_677) {
    EXPECT_THROW(registry.add("fast", "[fast]", defaultLineInfo), std::runtime_error);
}

// Test: Adding a duplicate alias throws
TEST_F(TagAliasRegistryTest_677, AddDuplicateAliasThrows_677) {
    registry.add("[@fast]", "[fast]", defaultLineInfo);
    EXPECT_THROW(registry.add("[@fast]", "[speedy]", secondLineInfo), std::runtime_error);
}

// Test: Adding multiple different aliases succeeds
TEST_F(TagAliasRegistryTest_677, AddMultipleDifferentAliases_677) {
    EXPECT_NO_THROW(registry.add("[@fast]", "[fast]", defaultLineInfo));
    EXPECT_NO_THROW(registry.add("[@slow]", "[slow]", secondLineInfo));

    const Catch::TagAlias* fastResult = registry.find("[@fast]");
    const Catch::TagAlias* slowResult = registry.find("[@slow]");

    ASSERT_NE(fastResult, nullptr);
    ASSERT_NE(slowResult, nullptr);
    EXPECT_EQ(fastResult->tag, "[fast]");
    EXPECT_EQ(slowResult->tag, "[slow]");
}

// Test: ExpandAliases with no aliases returns the same string
TEST_F(TagAliasRegistryTest_677, ExpandAliasesNoAliases_677) {
    std::string result = registry.expandAliases("[fast]");
    EXPECT_EQ(result, "[fast]");
}

// Test: ExpandAliases expands a registered alias
TEST_F(TagAliasRegistryTest_677, ExpandAliasesExpandsRegisteredAlias_677) {
    registry.add("[@fast]", "[speed]", defaultLineInfo);
    std::string result = registry.expandAliases("[@fast]");
    EXPECT_EQ(result, "[speed]");
}

// Test: ExpandAliases with unregistered alias returns original
TEST_F(TagAliasRegistryTest_677, ExpandAliasesUnregisteredAlias_677) {
    std::string result = registry.expandAliases("[@unknown]");
    EXPECT_EQ(result, "[@unknown]");
}

// Test: Adding an alias with empty name but correct format ([@]) succeeds
TEST_F(TagAliasRegistryTest_677, AddAliasMinimalFormat_677) {
    // "[@]" starts with "[@" and ends with "]" so it should be accepted
    EXPECT_NO_THROW(registry.add("[@]", "[tag]", defaultLineInfo));
    const Catch::TagAlias* result = registry.find("[@]");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag, "[tag]");
}

// Test: Alias with spaces in name
TEST_F(TagAliasRegistryTest_677, AddAliasWithSpaces_677) {
    EXPECT_NO_THROW(registry.add("[@my alias]", "[mytag]", defaultLineInfo));
    const Catch::TagAlias* result = registry.find("[@my alias]");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag, "[mytag]");
}

// Test: Empty string as alias throws
TEST_F(TagAliasRegistryTest_677, AddEmptyAliasThrows_677) {
    EXPECT_THROW(registry.add("", "[tag]", defaultLineInfo), std::runtime_error);
}

// Test: Alias with just "[@" (no closing bracket) throws
TEST_F(TagAliasRegistryTest_677, AddAliasNoClosingBracketThrows_677) {
    EXPECT_THROW(registry.add("[@", "[tag]", defaultLineInfo), std::runtime_error);
}

// Test: Alias starting with "[" but not "[@" throws
TEST_F(TagAliasRegistryTest_677, AddAliasStartsWithBracketOnly_677) {
    EXPECT_THROW(registry.add("[fast]", "[tag]", defaultLineInfo), std::runtime_error);
}

// Test: SourceLineInfo stored in the alias is correct
TEST_F(TagAliasRegistryTest_677, AliasStoresCorrectLineInfo_677) {
    Catch::SourceLineInfo specificLine{"specific_file.cpp", 42};
    registry.add("[@info]", "[info_tag]", specificLine);
    const Catch::TagAlias* result = registry.find("[@info]");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lineInfo.line, 42u);
    EXPECT_STREQ(result->lineInfo.file, "specific_file.cpp");
}

// Test: ExpandAliases with empty string
TEST_F(TagAliasRegistryTest_677, ExpandAliasesEmptyString_677) {
    std::string result = registry.expandAliases("");
    EXPECT_EQ(result, "");
}

// Test: ExpandAliases with plain text (no brackets)
TEST_F(TagAliasRegistryTest_677, ExpandAliasesPlainText_677) {
    std::string result = registry.expandAliases("plain text");
    EXPECT_EQ(result, "plain text");
}

// Test: Tag value can be an empty string
TEST_F(TagAliasRegistryTest_677, AddAliasWithEmptyTag_677) {
    EXPECT_NO_THROW(registry.add("[@empty]", "", defaultLineInfo));
    const Catch::TagAlias* result = registry.find("[@empty]");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag, "");
}

// Test: Expand aliases with multiple aliases registered
TEST_F(TagAliasRegistryTest_677, ExpandAliasesMultipleRegistered_677) {
    registry.add("[@a]", "[alpha]", defaultLineInfo);
    registry.add("[@b]", "[beta]", secondLineInfo);
    
    std::string resultA = registry.expandAliases("[@a]");
    std::string resultB = registry.expandAliases("[@b]");
    
    EXPECT_EQ(resultA, "[alpha]");
    EXPECT_EQ(resultB, "[beta]");
}
