#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

using namespace Catch::Clara;
using namespace Catch::Clara::Detail;

class ParserTest_398 : public ::testing::Test {
protected:
    Parser parser;
};

TEST_F(ParserTest_398, DefaultParserValidates_398) {
    auto result = parser.validate();
    // A default-constructed parser should be valid
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_398, PipeCombineTwoParsers_398) {
    Parser p1;
    Parser p2;
    
    // Combining two default parsers should produce a valid parser
    Parser combined = p1 | p2;
    auto result = combined.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_398, PipeOperatorDoesNotModifyOriginal_398) {
    Parser p1;
    Parser p2;
    
    // The pipe operator should create a new parser without modifying p1
    Parser combined = p1 | p2;
    
    // Original parser should still be valid and unchanged
    auto result = p1.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_398, PipeWithExeName_398) {
    Parser p;
    ExeName exeName("testapp");
    
    Parser combined = p | exeName;
    auto result = combined.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_398, PipeWithOpt_398) {
    bool flag = false;
    Opt opt(flag, "flag");
    opt["-f"]["--flag"].description("A test flag");
    
    Parser combined = parser | opt;
    auto result = combined.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_398, PipeWithArg_398) {
    std::string value;
    Arg arg(value, "input");
    arg.description("An input argument");
    
    Parser combined = parser | arg;
    auto result = combined.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_398, PipeChainingMultipleOpts_398) {
    bool flag1 = false;
    bool flag2 = false;
    
    Opt opt1(flag1, "flag1");
    opt1["-a"]["--alpha"].description("First flag");
    
    Opt opt2(flag2, "flag2");
    opt2["-b"]["--beta"].description("Second flag");
    
    Parser combined = parser | opt1 | opt2;
    auto result = combined.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_398, PipeResultHasHelpColumns_398) {
    bool flag = false;
    Opt opt(flag, "flag");
    opt["-f"]["--flag"].description("A test flag");
    
    Parser combined = parser | opt;
    auto columns = combined.getHelpColumns();
    
    // After adding an opt, there should be at least one help column
    EXPECT_GE(columns.size(), 1u);
}

TEST_F(ParserTest_398, PipeResultWriteToStream_398) {
    bool flag = false;
    Opt opt(flag, "flag");
    opt["-f"]["--flag"].description("A test flag");
    
    Parser combined = parser | opt;
    
    std::ostringstream oss;
    combined.writeToStream(oss);
    
    std::string output = oss.str();
    // The output should contain something related to our flag
    EXPECT_FALSE(output.empty());
}

TEST_F(ParserTest_398, DefaultParserGetHelpColumnsEmpty_398) {
    auto columns = parser.getHelpColumns();
    EXPECT_TRUE(columns.empty());
}

TEST_F(ParserTest_398, PipeWithMultipleArgsAndOpts_398) {
    bool flag = false;
    std::string input;
    
    Opt opt(flag, "flag");
    opt["-f"]["--flag"].description("A flag");
    
    Arg arg(input, "input");
    arg.description("Input file");
    
    Parser combined = parser | opt | arg;
    auto result = combined.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_398, PipeOperatorReturnsCopy_398) {
    bool flag = false;
    Opt opt(flag, "flag");
    opt["-f"]["--flag"].description("A flag");
    
    Parser combined = parser | opt;
    
    // Original should have no help columns
    auto originalColumns = parser.getHelpColumns();
    EXPECT_TRUE(originalColumns.empty());
    
    // Combined should have help columns
    auto combinedColumns = combined.getHelpColumns();
    EXPECT_GE(combinedColumns.size(), 1u);
}

TEST_F(ParserTest_398, WriteToStreamDefaultParserNotCrash_398) {
    std::ostringstream oss;
    parser.writeToStream(oss);
    // Just verifying it doesn't crash
    SUCCEED();
}

TEST_F(ParserTest_398, PipeCombineParserWithOptsFromBoth_398) {
    bool flag1 = false;
    bool flag2 = false;
    
    Opt opt1(flag1, "flag1");
    opt1["-a"]["--alpha"].description("Alpha");
    
    Opt opt2(flag2, "flag2");
    opt2["-b"]["--beta"].description("Beta");
    
    Parser p1 = Parser() | opt1;
    Parser p2 = Parser() | opt2;
    
    Parser combined = p1 | p2;
    
    auto columns = combined.getHelpColumns();
    // Should have columns from both parsers
    EXPECT_GE(columns.size(), 2u);
}

TEST_F(ParserTest_398, ParseEmptyTokens_398) {
    auto result = parser.parse("testapp", Detail::TokenStream(Detail::Args()));
    // Parsing with no tokens on a default parser should succeed
}

TEST_F(ParserTest_398, PipeOperatorAssociativity_398) {
    bool f1 = false, f2 = false, f3 = false;
    
    Opt o1(f1, "f1");
    o1["-a"].description("A");
    Opt o2(f2, "f2");
    o2["-b"].description("B");
    Opt o3(f3, "f3");
    o3["-c"].description("C");
    
    // Chain multiple pipes
    Parser combined = parser | o1 | o2 | o3;
    auto columns = combined.getHelpColumns();
    EXPECT_GE(columns.size(), 3u);
}
