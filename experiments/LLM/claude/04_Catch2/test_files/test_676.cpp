#include <gtest/gtest.h>
#include <string>

// Include necessary headers from the project
#include "catch2/internal/catch_tag_alias_registry.hpp"
#include "catch2/catch_tag_alias.hpp"

using namespace Catch;

class TagAliasRegistryTest_676 : public ::testing::Test {
protected:
    TagAliasRegistry registry;
};

// Test that expanding aliases on an empty registry returns the input unchanged
TEST_F(TagAliasRegistryTest_676, ExpandAliasesNoAliasesRegistered_676) {
    std::string input = "[some][tags]";
    std::string result = registry.expandAliases(input);
    EXPECT_EQ(result, input);
}

// Test that expanding an empty string returns an empty string
TEST_F(TagAliasRegistryTest_676, ExpandAliasesEmptyString_676) {
    std::string result = registry.expandAliases("");
    EXPECT_EQ(result, "");
}

// Test that a registered alias is expanded correctly
TEST_F(TagAliasRegistryTest_676, ExpandAliasesSingleAlias_676) {
    SourceLineInfo lineInfo("file.cpp", 1);
    registry.add("[@fast]", "[unit][fast]", lineInfo);
    
    std::string result = registry.expandAliases("[@fast]");
    EXPECT_EQ(result, "[unit][fast]");
}

// Test that text not matching any alias is returned unchanged
TEST_F(TagAliasRegistryTest_676, ExpandAliasesNoMatch_676) {
    SourceLineInfo lineInfo("file.cpp", 1);
    registry.add("[@fast]", "[unit][fast]", lineInfo);
    
    std::string result = registry.expandAliases("[slow]");
    EXPECT_EQ(result, "[slow]");
}

// Test expanding alias that appears in the middle of a string
TEST_F(TagAliasRegistryTest_676, ExpandAliasesAliasInMiddle_676) {
    SourceLineInfo lineInfo("file.cpp", 1);
    registry.add("[@fast]", "[unit][fast]", lineInfo);
    
    std::string result = registry.expandAliases("prefix[@fast]suffix");
    EXPECT_EQ(result, "prefix[unit][fast]suffix");
}

// Test that multiple different aliases can be registered and one is expanded
TEST_F(TagAliasRegistryTest_676, ExpandAliasesMultipleAliasesOneMatch_676) {
    SourceLineInfo lineInfo("file.cpp", 1);
    registry.add("[@fast]", "[unit][fast]", lineInfo);
    registry.add("[@slow]", "[integration][slow]", lineInfo);
    
    std::string result = registry.expandAliases("[@slow]");
    EXPECT_EQ(result, "[integration][slow]");
}

// Test that find returns nullptr when alias is not registered
TEST_F(TagAliasRegistryTest_676, FindNonexistentAlias_676) {
    const TagAlias* result = registry.find("[@nonexistent]");
    EXPECT_EQ(result, nullptr);
}

// Test that find returns a valid pointer after adding an alias
TEST_F(TagAliasRegistryTest_676, FindExistingAlias_676) {
    SourceLineInfo lineInfo("file.cpp", 42);
    registry.add("[@fast]", "[unit][fast]", lineInfo);
    
    const TagAlias* result = registry.find("[@fast]");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag, "[unit][fast]");
}

// Test that expanding aliases with a string that contains alias at the start
TEST_F(TagAliasRegistryTest_676, ExpandAliasesAliasAtStart_676) {
    SourceLineInfo lineInfo("file.cpp", 1);
    registry.add("[@ci]", "[continuous]", lineInfo);
    
    std::string result = registry.expandAliases("[@ci] and more");
    EXPECT_EQ(result, "[continuous] and more");
}

// Test that expanding aliases with a string that contains alias at the end
TEST_F(TagAliasRegistryTest_676, ExpandAliasesAliasAtEnd_676) {
    SourceLineInfo lineInfo("file.cpp", 1);
    registry.add("[@ci]", "[continuous]", lineInfo);
    
    std::string result = registry.expandAliases("something [@ci]");
    EXPECT_EQ(result, "something [continuous]");
}

// Test expanding an alias to an empty tag
TEST_F(TagAliasRegistryTest_676, ExpandAliasesToEmptyTag_676) {
    SourceLineInfo lineInfo("file.cpp", 1);
    registry.add("[@remove]", "", lineInfo);
    
    std::string result = registry.expandAliases("before[@remove]after");
    EXPECT_EQ(result, "beforeafter");
}

// Test that expanding aliases when input is exactly the alias
TEST_F(TagAliasRegistryTest_676, ExpandAliasesExactMatch_676) {
    SourceLineInfo lineInfo("file.cpp", 1);
    registry.add("[@all]", "[everything][everywhere]", lineInfo);
    
    std::string result = registry.expandAliases("[@all]");
    EXPECT_EQ(result, "[everything][everywhere]");
}

// Test that find returns correct line info
TEST_F(TagAliasRegistryTest_676, FindReturnsCorrectLineInfo_676) {
    SourceLineInfo lineInfo("myfile.cpp", 99);
    registry.add("[@test]", "[tag]", lineInfo);
    
    const TagAlias* result = registry.find("[@test]");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lineInfo.file, "myfile.cpp");
    EXPECT_EQ(result->lineInfo.line, 99u);
}

// Test that only the first occurrence of an alias is replaced
TEST_F(TagAliasRegistryTest_676, ExpandAliasesOnlyFirstOccurrence_676) {
    SourceLineInfo lineInfo("file.cpp", 1);
    registry.add("[@x]", "[replaced]", lineInfo);
    
    std::string result = registry.expandAliases("[@x][@x]");
    // Based on the implementation, find returns the first position and replaces it once per alias
    // The second occurrence may or may not be replaced depending on the result of the first replacement
    // The implementation iterates through registry entries and does one find+replace per entry
    EXPECT_EQ(result, "[replaced][@x]");
}

// Test adding an alias with special characters in the tag
TEST_F(TagAliasRegistryTest_676, ExpandAliasesSpecialCharactersInTag_676) {
    SourceLineInfo lineInfo("file.cpp", 1);
    registry.add("[@special]", "[tag with spaces][!shouldfail]", lineInfo);
    
    std::string result = registry.expandAliases("[@special]");
    EXPECT_EQ(result, "[tag with spaces][!shouldfail]");
}

// Test that registering multiple aliases expands both when both are present (if no overlap)
TEST_F(TagAliasRegistryTest_676, ExpandAliasesMultipleAliasesBothPresent_676) {
    SourceLineInfo lineInfo("file.cpp", 1);
    registry.add("[@a]", "[alpha]", lineInfo);
    registry.add("[@b]", "[beta]", lineInfo);
    
    // Both aliases present, non-overlapping
    std::string result = registry.expandAliases("[@a],[@b]");
    // Both should be expanded since they don't overlap
    EXPECT_NE(result.find("[alpha]"), std::string::npos);
    EXPECT_NE(result.find("[beta]"), std::string::npos);
}

// Test find with empty string
TEST_F(TagAliasRegistryTest_676, FindEmptyString_676) {
    const TagAlias* result = registry.find("");
    EXPECT_EQ(result, nullptr);
}

// Test expanding aliases when the input is a very long string with no match
TEST_F(TagAliasRegistryTest_676, ExpandAliasesLongStringNoMatch_676) {
    SourceLineInfo lineInfo("file.cpp", 1);
    registry.add("[@x]", "[y]", lineInfo);
    
    std::string longString(10000, 'a');
    std::string result = registry.expandAliases(longString);
    EXPECT_EQ(result, longString);
}
