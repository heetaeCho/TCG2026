#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_test_spec.hpp"

#include "catch_test_spec_parser.hpp"

#include "catch_interfaces_tag_alias_registry.hpp"



using namespace Catch;

using ::testing::Return;



class MockTagAliasRegistry : public ITagAliasRegistry {

public:

    MOCK_CONST_METHOD1(find, const TagAlias*(const std::string& alias));

    MOCK_CONST_METHOD1(expandAliases, std::string(const std::string& unexpandedTestSpec));

};



class TestSpecParserTest_1044 : public ::testing::Test {

protected:

    MockTagAliasRegistry mockTagAliasRegistry;

    TestSpecParser parser;



    TestSpecParserTest_1044() : parser(mockTagAliasRegistry) {}

};



TEST_F(TestSpecParserTest_1044, ParseEmptyString_1044) {

    EXPECT_CALL(mockTagAliasRegistry, expandAliases("")).WillOnce(Return(""));

    auto& result = parser.parse("");

    EXPECT_FALSE(result.testSpec().hasFilters());

}



TEST_F(TestSpecParserTest_1044, ParseSimpleName_1044) {

    EXPECT_CALL(mockTagAliasRegistry, expandAliases("test_case_name")).WillOnce(Return("test_case_name"));

    auto& result = parser.parse("test_case_name");

    EXPECT_TRUE(result.testSpec().hasFilters());

}



TEST_F(TestSpecParserTest_1044, ParseWithExclusion_1044) {

    EXPECT_CALL(mockTagAliasRegistry, expandAliases("~[tag]")).WillOnce(Return("~[tag]"));

    auto& result = parser.parse("~[tag]");

    EXPECT_TRUE(result.testSpec().hasFilters());

}



TEST_F(TestSpecParserTest_1044, ParseWithQuotedName_1044) {

    EXPECT_CALL(mockTagAliasRegistry, expandAliases("\"quoted name\"")).WillOnce(Return("\"quoted name\""));

    auto& result = parser.parse("\"quoted name\"");

    EXPECT_TRUE(result.testSpec().hasFilters());

}



TEST_F(TestSpecParserTest_1044, ParseWithEscapedCharacter_1044) {

    EXPECT_CALL(mockTagAliasRegistry, expandAliases("name\\:with\\:colon")).WillOnce(Return("name\\:with\\:colon"));

    auto& result = parser.parse("name\\:with\\:colon");

    EXPECT_TRUE(result.testSpec().hasFilters());

}



TEST_F(TestSpecParserTest_1044, ParseInvalidSpec_1044) {

    EXPECT_CALL(mockTagAliasRegistry, expandAliases("invalid spec")).WillOnce(Return("invalid spec"));

    auto& result = parser.parse("invalid spec");

    EXPECT_TRUE(result.testSpec().getInvalidSpecs().size() > 0);

}



TEST_F(TestSpecParserTest_1044, ParseWithMultipleFilters_1044) {

    EXPECT_CALL(mockTagAliasRegistry, expandAliases("test_case_name [tag]")).WillOnce(Return("test_case_name [tag]"));

    auto& result = parser.parse("test_case_name [tag]");

    EXPECT_TRUE(result.testSpec().hasFilters());

}



TEST_F(TestSpecParserTest_1044, ParseWithMultipleTags_1044) {

    EXPECT_CALL(mockTagAliasRegistry, expandAliases("[tag1][tag2]")).WillOnce(Return("[tag1][tag2]"));

    auto& result = parser.parse("[tag1][tag2]");

    EXPECT_TRUE(result.testSpec().hasFilters());

}
