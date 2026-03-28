#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <catch2/internal/catch_clara.hpp>

#include <sstream>



using namespace Catch::Clara;

using ::testing::_;

using ::testing::Return;



class ParserTest : public ::testing::Test {

protected:

    Parser parser1;

    Parser parser2;

};



TEST_F(ParserTest_398, OperatorOrEqual_IncreasesOptionsCount_398) {

    Arg arg("testArg");

    size_t initialOptionCount = parser1.getHelpColumns().size();

    parser1 |= arg;

    EXPECT_EQ(parser1.getHelpColumns().size(), initialOptionCount + 1);

}



TEST_F(ParserTest_398, OperatorOrEqual_CombinesOptionsFromTwoParsers_398) {

    Arg arg1("testArg1");

    Arg arg2("testArg2");

    parser1 |= arg1;

    parser2 |= arg2;



    size_t initialOptionCount = parser1.getHelpColumns().size();

    parser1 |= parser2;

    EXPECT_EQ(parser1.getHelpColumns().size(), initialOptionCount + 1);

}



TEST_F(ParserTest_398, WriteToStream_OutputIsNotEmpty_398) {

    std::ostringstream oss;

    parser1.writeToStream(oss);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(ParserTest_398, Validate_ReturnsSuccessForDefaultParser_398) {

    Detail::Result result = parser1.validate();

    EXPECT_TRUE(result.m_ok);

}



TEST_F(ParserTest_398, Parse_WithValidInput_ReturnsSuccess_398) {

    Arg arg("testArg");

    parser1 |= arg;

    std::string exeName = "testExe";

    Detail::TokenStream tokens{"--testArg", "value"};

    Detail::InternalParseResult result = parser1.parse(exeName, tokens);

    EXPECT_TRUE(result.m_matched);

}



TEST_F(ParserTest_398, Parse_WithInvalidInput_ReturnsFailure_398) {

    Arg arg("testArg");

    parser1 |= arg;

    std::string exeName = "testExe";

    Detail::TokenStream tokens{"--invalidArg", "value"};

    Detail::InternalParseResult result = parser1.parse(exeName, tokens);

    EXPECT_FALSE(result.m_matched);

}



TEST_F(ParserTest_398, Parse_EmptyTokens_ReturnsFailure_398) {

    std::string exeName = "testExe";

    Detail::TokenStream tokens{};

    Detail::InternalParseResult result = parser1.parse(exeName, tokens);

    EXPECT_FALSE(result.m_matched);

}



TEST_F(ParserTest_398, OperatorOrEqual_ExeNameSetsCorrectly_398) {

    ExeName exeName("testExe");

    parser1 |= exeName;

    // Since we don't have direct access to m_exeName, this test is limited

    // We can only ensure that no exception occurs and the behavior seems consistent.

}



TEST_F(ParserTest_398, GetHelpColumns_ReturnsNonEmptyVectorForAddedArg_398) {

    Arg arg("testArg");

    parser1 |= arg;

    EXPECT_FALSE(parser1.getHelpColumns().empty());

}



TEST_F(ParserTest_398, GetHelpColumns_ReturnsEmptyVectorForDefaultParser_398) {

    EXPECT_TRUE(parser1.getHelpColumns().empty());

}
