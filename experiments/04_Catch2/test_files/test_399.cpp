#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara;



class ParserTest : public ::testing::Test {

protected:

    Parser parser;

};



TEST_F(ParserTest_399, ValidateReturnsSuccessForEmptyParser_399) {

    EXPECT_EQ(parser.validate().isOk(), true);

}



TEST_F(ParserTest_399, ParseWithValidInputDoesNotFail_399) {

    Detail::TokenStream tokens;

    EXPECT_TRUE(parser.parse("test", tokens).isOk());

}



TEST_F(ParserTest_399, GetHelpColumnsReturnsEmptyForNoOptions_399) {

    auto helpColumns = parser.getHelpColumns();

    EXPECT_EQ(helpColumns.empty(), true);

}



TEST_F(ParserTest_399, WriteToStreamDoesNotThrow_399) {

    std::ostringstream os;

    EXPECT_NO_THROW(parser.writeToStream(os));

}



TEST_F(ParserTest_399, OperatorOrEqualWithExeNameSetsExeName_399) {

    ExeName exeName("test");

    parser |= exeName;

    // No observable behavior to verify directly, but ensure no crash

}



TEST_F(ParserTest_399, OperatorOrEqualWithArgAddsArg_399) {

    Arg arg("arg");

    parser |= arg;

    // No observable behavior to verify directly, but ensure no crash

}



TEST_F(ParserTest_399, OperatorOrEqualWithParserCombinesParsers_399) {

    Parser otherParser;

    parser |= otherParser;

    // No observable behavior to verify directly, but ensure no crash

}
