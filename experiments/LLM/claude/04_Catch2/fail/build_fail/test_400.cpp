#include <catch2/internal/catch_clara.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

using namespace Catch::Clara;

class ParserTest_400 : public ::testing::Test {
protected:
    Parser parser;
};

// Test that a default-constructed parser can be streamed without crashing
TEST_F(ParserTest_400, DefaultParserStreamOutput_400) {
    std::ostringstream oss;
    oss << parser;
    // Should not throw; output may be empty or contain default info
    EXPECT_NO_THROW(oss.str());
}

// Test that writeToStream produces the same result as operator<<
TEST_F(ParserTest_400, WriteToStreamMatchesOperatorOutput_400) {
    std::ostringstream oss1;
    std::ostringstream oss2;
    
    parser.writeToStream(oss1);
    oss2 << parser;
    
    EXPECT_EQ(oss1.str(), oss2.str());
}

// Test that a default parser validates successfully
TEST_F(ParserTest_400, DefaultParserValidates_400) {
    auto result = parser.validate();
    // A default empty parser should validate without errors
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that getHelpColumns returns empty for a default parser
TEST_F(ParserTest_400, DefaultParserHelpColumnsEmpty_400) {
    auto columns = parser.getHelpColumns();
    EXPECT_TRUE(columns.empty());
}

// Test combining parser with an Opt and streaming
TEST_F(ParserTest_400, ParserWithOptStreams_400) {
    bool flag = false;
    auto opt = Opt(flag, "flag")["-f"]["--flag"]("A test flag");
    parser |= opt;
    
    std::ostringstream oss;
    EXPECT_NO_THROW(oss << parser);
    std::string output = oss.str();
    // The output should contain some reference to the flag option
    EXPECT_FALSE(output.empty());
}

// Test combining parser with an Opt produces help columns
TEST_F(ParserTest_400, ParserWithOptHasHelpColumns_400) {
    bool flag = false;
    auto opt = Opt(flag, "flag")["-f"]["--flag"]("A test flag");
    parser |= opt;
    
    auto columns = parser.getHelpColumns();
    EXPECT_FALSE(columns.empty());
}

// Test parsing with no arguments on a default parser
TEST_F(ParserTest_400, DefaultParserParseEmpty_400) {
    std::vector<std::string> args;
    auto result = parser.parse(Detail::Args(0, nullptr));
    // Parsing with no arguments should succeed for an empty parser
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test combining two parsers with operator|=
TEST_F(ParserTest_400, CombineTwoParsers_400) {
    Parser other;
    bool flag = false;
    other |= Opt(flag, "flag")["-f"]["--flag"]("A flag");
    
    parser |= other;
    
    auto columns = parser.getHelpColumns();
    EXPECT_FALSE(columns.empty());
}

// Test setting ExeName on parser
TEST_F(ParserTest_400, ParserWithExeName_400) {
    parser |= ExeName("test_app");
    
    std::ostringstream oss;
    EXPECT_NO_THROW(oss << parser);
}

// Test combining parser with Arg
TEST_F(ParserTest_400, ParserWithArg_400) {
    std::string input;
    auto arg = Arg(input, "input")("Input file");
    parser |= arg;
    
    std::ostringstream oss;
    EXPECT_NO_THROW(oss << parser);
    EXPECT_FALSE(oss.str().empty());
}

// Test that parser with option validates
TEST_F(ParserTest_400, ParserWithOptValidates_400) {
    bool flag = false;
    parser |= Opt(flag, "flag")["-f"]["--flag"]("A test flag");
    
    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test streaming after combining multiple opts
TEST_F(ParserTest_400, ParserWithMultipleOptsStreams_400) {
    bool flag1 = false;
    bool flag2 = false;
    parser |= Opt(flag1)["-a"]["--alpha"]("Alpha flag");
    parser |= Opt(flag2)["-b"]["--beta"]("Beta flag");
    
    std::ostringstream oss;
    oss << parser;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test that streaming to different stream objects is consistent
TEST_F(ParserTest_400, StreamOutputIsConsistent_400) {
    bool flag = false;
    parser |= Opt(flag)["-x"]["--xray"]("X-ray option");
    
    std::ostringstream oss1, oss2;
    oss1 << parser;
    oss2 << parser;
    
    EXPECT_EQ(oss1.str(), oss2.str());
}
