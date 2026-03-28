#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_clara.hpp"

#include <sstream>



using namespace Catch::Clara;



class ParserTest_395 : public ::testing::Test {

protected:

    Parser parser;

};



TEST_F(ParserTest_395, AddArg_ReturnsReferenceToParser_395) {

    Arg arg;

    Parser& result = parser |= arg;

    EXPECT_EQ(&result, &parser);

}



TEST_F(ParserTest_395, GetHelpColumns_ReturnsNonEmptyVector_395) {

    std::vector<Detail::HelpColumns> helpColumns = parser.getHelpColumns();

    EXPECT_FALSE(helpColumns.empty());

}



TEST_F(ParserTest_395, WriteToStream_DoesNotThrow_395) {

    std::ostringstream os;

    EXPECT_NO_THROW(parser.writeToStream(os));

}



TEST_F(ParserTest_395, Validate_ReturnsResultObject_395) {

    Detail::Result result = parser.validate();

    // Assuming Result is default-constructible and can be checked for validity

}



TEST_F(ParserTest_395, Parse_ValidInput_ReturnsValidParseResult_395) {

    std::string exeName("test");

    Detail::TokenStream tokens; // Assuming TokenStream can be constructed without arguments or with appropriate setup

    Detail::InternalParseResult result = parser.parse(exeName, tokens);

    // Assuming InternalParseResult has a way to check validity

}



TEST_F(ParserTest_395, Parse_EmptyInput_ReturnsInvalidParseResult_395) {

    std::string exeName;

    Detail::TokenStream tokens; // Assuming TokenStream can be constructed without arguments or with appropriate setup

    Detail::InternalParseResult result = parser.parse(exeName, tokens);

    // Assuming InternalParseResult has a way to check validity and this should be invalid

}



TEST_F(ParserTest_395, AddExeName_ReturnsReferenceToParser_395) {

    ExeName exeName("test");

    Parser& result = parser |= exeName;

    EXPECT_EQ(&result, &parser);

}



TEST_F(ParserTest_395, CombineParsers_ReturnsReferenceToParser_395) {

    Parser otherParser;

    Parser& result = parser |= otherParser;

    EXPECT_EQ(&result, &parser);

}
