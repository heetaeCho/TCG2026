#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara;

using ::testing::_;

using ::testing::StrEq;



class ParserTest : public ::testing::Test {

protected:

    std::ostringstream os;

    Parser parser;

};



TEST_F(ParserTest, WriteToStream_WithNoExeNameAndArgs_670) {

    parser.writeToStream(os);

    EXPECT_EQ("", os.str());

}



TEST_F(ParserTest, WriteToStream_WithOnlyExeName_670) {

    std::string exeName = "test_exe";

    parser |= ExeName(exeName);

    parser.writeToStream(os);

    EXPECT_THAT(os.str(), StrEq("usage:\n test_exe \n\n"));

}



TEST_F(ParserTest, WriteToStream_WithRequiredAndOptionalArgs_670) {

    std::string exeName = "test_exe";

    parser |= ExeName(exeName);

    parser |= Arg().hint("req_arg").required();

    parser |= Arg().hint("opt_arg");

    parser.writeToStream(os);

    EXPECT_THAT(os.str(), StrEq("usage:\n test_exe <req_arg> [ <opt_arg> ]\n\n"));

}



TEST_F(ParserTest, WriteToStream_WithMultipleRequiredArgs_670) {

    std::string exeName = "test_exe";

    parser |= ExeName(exeName);

    parser |= Arg().hint("arg1").required();

    parser |= Arg().hint("arg2").required();

    parser.writeToStream(os);

    EXPECT_THAT(os.str(), StrEq("usage:\n test_exe <arg1> <arg2>\n\n"));

}



TEST_F(ParserTest, WriteToStream_WithMultipleOptionalArgs_670) {

    std::string exeName = "test_exe";

    parser |= ExeName(exeName);

    parser |= Arg().hint("opt_arg1");

    parser |= Arg().hint("opt_arg2");

    parser.writeToStream(os);

    EXPECT_THAT(os.str(), StrEq("usage:\n test_exe [ <opt_arg1> <opt_arg2> ]\n\n"));

}



TEST_F(ParserTest, WriteToStream_WithArgsHavingCardinalityZero_670) {

    std::string exeName = "test_exe";

    parser |= ExeName(exeName);

    parser |= Arg().hint("arg").cardinality(0);

    parser.writeToStream(os);

    EXPECT_THAT(os.str(), StrEq("usage:\n test_exe [ <arg> ... ]\n\n"));

}



TEST_F(ParserTest, WriteToStream_WithOptions_670) {

    std::string exeName = "test_exe";

    parser |= ExeName(exeName);

    parser |= Opt().hint("--opt1").description("Option 1");

    parser.writeToStream(os);

    EXPECT_THAT(os.str(), StrEq("usage:\n test_exe options\n\nwhere options are:\n  --opt1     Option 1\n"));

}



TEST_F(ParserTest, WriteToStream_WithMultipleOptions_670) {

    std::string exeName = "test_exe";

    parser |= ExeName(exeName);

    parser |= Opt().hint("--opt1").description("Option 1");

    parser |= Opt().hint("--opt2").description("Option 2");

    parser.writeToStream(os);

    EXPECT_THAT(os.str(), StrEq("usage:\n test_exe options\n\nwhere options are:\n  --opt1     Option 1\n  --opt2     Option 2\n"));

}
