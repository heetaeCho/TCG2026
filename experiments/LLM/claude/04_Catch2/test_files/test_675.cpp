#include <gtest/gtest.h>
#include "catch2/internal/catch_tag_alias_registry.hpp"
#include "catch2/catch_tag_alias.hpp"
#include "catch2/internal/catch_source_line_info.hpp"

namespace {

class TagAliasRegistryTest_675 : public ::testing::Test {
protected:
    Catch::TagAliasRegistry registry;
};

// Test that find returns nullptr when registry is empty
TEST_F(TagAliasRegistryTest_675, FindReturnsNullptrWhenEmpty_675) {
    auto result = registry.find("[@someAlias]");
    EXPECT_EQ(result, nullptr);
}

// Test that find returns nullptr for a non-existent alias
TEST_F(TagAliasRegistryTest_675, FindReturnsNullptrForNonExistentAlias_675) {
    registry.add("[@existing]", "[sometag]", Catch::SourceLineInfo("file.cpp", 10));
    auto result = registry.find("[@nonexistent]");
    EXPECT_EQ(result, nullptr);
}

// Test that find returns a valid pointer after adding an alias
TEST_F(TagAliasRegistryTest_675, FindReturnsValidPointerAfterAdd_675) {
    registry.add("[@myAlias]", "[myTag]", Catch::SourceLineInfo("file.cpp", 5));
    auto result = registry.find("[@myAlias]");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag, "[myTag]");
}

// Test that add and find work with multiple aliases
TEST_F(TagAliasRegistryTest_675, FindWorksWithMultipleAliases_675) {
    registry.add("[@alias1]", "[tag1]", Catch::SourceLineInfo("file1.cpp", 1));
    registry.add("[@alias2]", "[tag2]", Catch::SourceLineInfo("file2.cpp", 2));
    registry.add("[@alias3]", "[tag3]", Catch::SourceLineInfo("file3.cpp", 3));

    auto result1 = registry.find("[@alias1]");
    auto result2 = registry.find("[@alias2]");
    auto result3 = registry.find("[@alias3]");

    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    ASSERT_NE(result3, nullptr);

    EXPECT_EQ(result1->tag, "[tag1]");
    EXPECT_EQ(result2->tag, "[tag2]");
    EXPECT_EQ(result3->tag, "[tag3]");
}

// Test that adding a duplicate alias throws an exception
TEST_F(TagAliasRegistryTest_675, AddDuplicateAliasThrows_675) {
    registry.add("[@dup]", "[tag1]", Catch::SourceLineInfo("file.cpp", 10));
    EXPECT_THROW(
        registry.add("[@dup]", "[tag2]", Catch::SourceLineInfo("file.cpp", 20)),
        std::exception
    );
}

// Test that find with empty string returns nullptr
TEST_F(TagAliasRegistryTest_675, FindWithEmptyStringReturnsNullptr_675) {
    auto result = registry.find("");
    EXPECT_EQ(result, nullptr);
}

// Test expandAliases with no aliases returns the original string
TEST_F(TagAliasRegistryTest_675, ExpandAliasesNoAliasesReturnsOriginal_675) {
    std::string input = "[someTag]";
    std::string result = registry.expandAliases(input);
    EXPECT_EQ(result, input);
}

// Test expandAliases expands a known alias
TEST_F(TagAliasRegistryTest_675, ExpandAliasesExpandsKnownAlias_675) {
    registry.add("[@myAlias]", "[expanded][tags]", Catch::SourceLineInfo("file.cpp", 1));
    std::string result = registry.expandAliases("[@myAlias]");
    EXPECT_EQ(result, "[expanded][tags]");
}

// Test expandAliases with unknown alias leaves it unchanged
TEST_F(TagAliasRegistryTest_675, ExpandAliasesUnknownAliasUnchanged_675) {
    std::string input = "[@unknownAlias]";
    std::string result = registry.expandAliases(input);
    EXPECT_EQ(result, input);
}

// Test expandAliases with empty string
TEST_F(TagAliasRegistryTest_675, ExpandAliasesEmptyString_675) {
    std::string result = registry.expandAliases("");
    EXPECT_EQ(result, "");
}

// Test that the source line info is preserved in the tag alias
TEST_F(TagAliasRegistryTest_675, SourceLineInfoPreserved_675) {
    Catch::SourceLineInfo lineInfo("testfile.cpp", 42);
    registry.add("[@srcTest]", "[tagSrc]", lineInfo);
    auto result = registry.find("[@srcTest]");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lineInfo.line, 42u);
}

// Test that find is case-sensitive
TEST_F(TagAliasRegistryTest_675, FindIsCaseSensitive_675) {
    registry.add("[@CaseSensitive]", "[tag]", Catch::SourceLineInfo("file.cpp", 1));
    auto result = registry.find("[@casesensitive]");
    EXPECT_EQ(result, nullptr);

    auto resultCorrect = registry.find("[@CaseSensitive]");
    ASSERT_NE(resultCorrect, nullptr);
    EXPECT_EQ(resultCorrect->tag, "[tag]");
}

// Test expandAliases with mixed regular tags and aliases
TEST_F(TagAliasRegistryTest_675, ExpandAliasesMixedContent_675) {
    registry.add("[@fast]", "[quick][performance]", Catch::SourceLineInfo("file.cpp", 1));
    std::string result = registry.expandAliases("[unit][@fast]");
    // The alias should be expanded while the regular tag remains
    EXPECT_NE(result.find("[quick]"), std::string::npos);
    EXPECT_NE(result.find("[performance]"), std::string::npos);
    EXPECT_NE(result.find("[unit]"), std::string::npos);
}

} // anonymous namespace
