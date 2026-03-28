#include <gtest/gtest.h>
#include <catch2/catch_test_spec.hpp>
#include <catch2/internal/catch_test_spec_parser.hpp>
#include <catch2/internal/catch_tag_alias_registry.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <string>
#include <vector>

namespace {

class TestSpecParserTest_1045 : public ::testing::Test {
protected:
    Catch::TagAliasRegistry tagAliasRegistry;
};

TEST_F(TestSpecParserTest_1045, DefaultTestSpecMatchesNothing_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters() == false);
}

TEST_F(TestSpecParserTest_1045, ParseEmptyStringProducesNoFilters_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_FALSE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseSimpleNameProducesFilter_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("TestName");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseWildcardProducesFilter_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("*");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseTagProducesFilter_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("[tag]");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseExclusionProducesFilter_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("~[tag]");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseMultipleFiltersWithComma_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("Test1,Test2");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseReturnsReferenceForChaining_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    Catch::TestSpecParser& ref = parser.parse("TestName");
    EXPECT_EQ(&ref, &parser);
}

TEST_F(TestSpecParserTest_1045, ParseChainedCalls_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("Test1").parse("Test2");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseNameWithWildcardPrefix_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("*Suffix");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseNameWithWildcardSuffix_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("Prefix*");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseNameWithWildcardBothEnds_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("*Middle*");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseExcludedName_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("~TestName");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseMultipleTagsCombined_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("[tag1][tag2]");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseQuotedName_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("\"Test with spaces\"");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseEscapedCharacter_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("Test\\,Name");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, TestSpecCalledMultipleTimes_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("TestName");
    Catch::TestSpec spec1 = parser.testSpec();
    // After testSpec() is called, internal state is moved; calling again should give empty
    Catch::TestSpec spec2 = parser.testSpec();
    EXPECT_TRUE(spec1.hasFilters());
    // spec2 may or may not have filters depending on implementation, but shouldn't crash
}

TEST_F(TestSpecParserTest_1045, ParseOnlyWhitespace_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("   ");
    Catch::TestSpec spec = parser.testSpec();
    // Whitespace-only may or may not produce filters; just ensure no crash
    // The behavior depends on implementation
}

TEST_F(TestSpecParserTest_1045, ParseCommaOnly_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse(",");
    Catch::TestSpec spec = parser.testSpec();
    // Comma is a separator; parsing just comma should not crash
}

TEST_F(TestSpecParserTest_1045, ParseExcludedTag_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("~[excluded]");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseNameAndTag_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("TestName[tag]");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseComplexExpression_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("TestA*[tagA],~[tagB]");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseSpecialCharactersInName_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("Test-Name_123");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseVeryLongString_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    std::string longName(10000, 'a');
    parser.parse(longName);
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseUnclosedTag_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("[unclosed");
    Catch::TestSpec spec = parser.testSpec();
    // Should not crash even with unclosed tag bracket
}

TEST_F(TestSpecParserTest_1045, ParseEmptyTag_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("[]");
    Catch::TestSpec spec = parser.testSpec();
    // Empty tag may or may not produce a meaningful filter
}

TEST_F(TestSpecParserTest_1045, ParseMultipleSeparatedFilters_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("A,B,C,D");
    Catch::TestSpec spec = parser.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecParserTest_1045, ParseTildeAlone_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("~");
    Catch::TestSpec spec = parser.testSpec();
    // Tilde alone - should not crash
}

TEST_F(TestSpecParserTest_1045, ParseQuotedWithEscapes_1045) {
    Catch::TestSpecParser parser(tagAliasRegistry);
    parser.parse("\"Test\\\"Quoted\"");
    Catch::TestSpec spec = parser.testSpec();
    // Should handle escaped quotes in quoted strings
}

}  // namespace
