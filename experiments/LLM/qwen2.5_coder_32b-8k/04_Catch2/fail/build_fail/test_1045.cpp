#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.cpp"



using namespace Catch;



class TestSpecParserTest_1045 : public ::testing::Test {

protected:

    TestSpecParser parser;

    

    TestSpecParserTest_1045() : parser(*new ITagAliasRegistry()) {}

};



TEST_F(TestSpecParserTest_1045, DefaultConstructorInitializesCorrectly_1045) {

    // No direct observable behavior to test except that construction succeeds

}



TEST_F(TestSpecParserTest_1045, ParseWithEmptyStringReturnsDefaultTestSpec_1045) {

    parser.parse("");

    TestSpec spec = parser.testSpec();

    EXPECT_TRUE(spec.empty());

}



TEST_F(TestSpecParserTest_1045, ParseWithSimplePatternAddsFilter_1045) {

    parser.parse("testcase");

    TestSpec spec = parser.testSpec();

    EXPECT_EQ(spec.patterns.size(), 1);

    EXPECT_EQ(spec.patterns[0], "testcase");

}



TEST_F(TestSpecParserTest_1045, ParseWithMultiplePatternsAddsFilters_1045) {

    parser.parse("testcase1, testcase2");

    TestSpec spec = parser.testSpec();

    EXPECT_EQ(spec.patterns.size(), 2);

    EXPECT_EQ(spec.patterns[0], "testcase1");

    EXPECT_EQ(spec.patterns[1], "testcase2");

}



TEST_F(TestSpecParserTest_1045, ParseWithExclusionPatternAddsFilter_1045) {

    parser.parse("~testcase");

    TestSpec spec = parser.testSpec();

    EXPECT_EQ(spec.excludedPatterns.size(), 1);

    EXPECT_EQ(spec.excludedPatterns[0], "testcase");

}



TEST_F(TestSpecParserTest_1045, ParseWithMultipleExclusionPatternsAddsFilters_1045) {

    parser.parse("~testcase1, ~testcase2");

    TestSpec spec = parser.testSpec();

    EXPECT_EQ(spec.excludedPatterns.size(), 2);

    EXPECT_EQ(spec.excludedPatterns[0], "testcase1");

    EXPECT_EQ(spec.excludedPatterns[1], "testcase2");

}



TEST_F(TestSpecParserTest_1045, ParseWithMixedInclusionExclusionPatternsAddsFilters_1045) {

    parser.parse("testcase1, ~testcase2");

    TestSpec spec = parser.testSpec();

    EXPECT_EQ(spec.patterns.size(), 1);

    EXPECT_EQ(spec.excludedPatterns.size(), 1);

    EXPECT_EQ(spec.patterns[0], "testcase1");

    EXPECT_EQ(spec.excludedPatterns[0], "testcase2");

}



TEST_F(TestSpecParserTest_1045, ParseWithEscapedCommaAddsFilter_1045) {

    parser.parse("test\\,case");

    TestSpec spec = parser.testSpec();

    EXPECT_EQ(spec.patterns.size(), 1);

    EXPECT_EQ(spec.patterns[0], "test,case");

}



TEST_F(TestSpecParserTest_1045, ParseWithEscapedTildeAddsFilter_1045) {

    parser.parse("~\\~testcase");

    TestSpec spec = parser.testSpec();

    EXPECT_EQ(spec.patterns.size(), 1);

    EXPECT_EQ(spec.patterns[0], "~testcase");

}



TEST_F(TestSpecParserTest_1045, ParseWithEscapedBackslashAddsFilter_1045) {

    parser.parse("test\\\\case");

    TestSpec spec = parser.testSpec();

    EXPECT_EQ(spec.patterns.size(), 1);

    EXPECT_EQ(spec.patterns[0], "test\\case");

}



TEST_F(TestSpecParserTest_1045, ParseWithMultipleEscapedCharactersAddsFilter_1045) {

    parser.parse("test\\,case\\\\~name");

    TestSpec spec = parser.testSpec();

    EXPECT_EQ(spec.patterns.size(), 1);

    EXPECT_EQ(spec.patterns[0], "test,case\\~name");

}
