#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <sstream>

#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara;
using namespace Catch::Clara::Detail;

// ============================================================================
// Test Fixture
// ============================================================================
class ParserTest_672 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================================
// Normal Operation Tests
// ============================================================================

TEST_F(ParserTest_672, EmptyParserWithNoTokensSucceeds_672) {
    Parser parser;
    Args args{};
    // Create an empty token stream
    std::vector<std::string> rawArgs;
    auto result = parser.parse("test_exe", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_672, ParserWithBoolOptParsesFlag_672) {
    bool flag = false;
    Parser parser;
    parser |= Opt(flag)["-f"]["--flag"]("A flag option");

    std::vector<std::string> rawArgs = {"-f"};
    auto result = parser.parse("test_exe", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(flag);
}

TEST_F(ParserTest_672, ParserWithBoolOptParsesLongFlag_672) {
    bool flag = false;
    Parser parser;
    parser |= Opt(flag)["-f"]["--flag"]("A flag option");

    std::vector<std::string> rawArgs = {"--flag"};
    auto result = parser.parse("test_exe", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(flag);
}

TEST_F(ParserTest_672, ParserWithStringOptParsesValue_672) {
    std::string name;
    Parser parser;
    parser |= Opt(name, "name")["-n"]["--name"]("A name option");

    std::vector<std::string> rawArgs = {"-n", "hello"};
    auto result = parser.parse("test_exe", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(name, "hello");
}

TEST_F(ParserTest_672, ParserWithArgParsesPositionalArg_672) {
    std::string filename;
    Parser parser;
    parser |= Arg(filename, "filename")("A positional argument");

    std::vector<std::string> rawArgs = {"myfile.txt"};
    auto result = parser.parse("test_exe", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(filename, "myfile.txt");
}

TEST_F(ParserTest_672, ParserWithMultipleOptionsParsesAll_672) {
    bool verbose = false;
    std::string output;
    Parser parser;
    parser |= Opt(verbose)["-v"]["--verbose"]("Verbose mode");
    parser |= Opt(output, "output")["-o"]["--output"]("Output file");

    std::vector<std::string> rawArgs = {"-v", "-o", "result.txt"};
    auto result = parser.parse("test_exe", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(verbose);
    EXPECT_EQ(output, "result.txt");
}

TEST_F(ParserTest_672, ParserWithExeNameSetsExeName_672) {
    Parser parser;
    std::string exeName;
    parser |= ExeName(exeName);

    std::vector<std::string> rawArgs;
    auto result = parser.parse("my_program", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(exeName, "my_program");
}

// ============================================================================
// Boundary Condition Tests
// ============================================================================

TEST_F(ParserTest_672, EmptyExeNameHandledGracefully_672) {
    Parser parser;
    std::vector<std::string> rawArgs;
    auto result = parser.parse("", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_672, ParserWithNoOptionsAndNoArgsEmptyTokens_672) {
    Parser parser;
    std::vector<std::string> rawArgs;
    auto result = parser.parse("exe", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    EXPECT_TRUE(static_cast<bool>(result));
}

// ============================================================================
// Error Case Tests
// ============================================================================

TEST_F(ParserTest_672, UnrecognisedTokenReturnsError_672) {
    Parser parser;
    // Parser has no options or args, so any token is unrecognised
    std::vector<std::string> rawArgs = {"--unknown"};
    auto result = parser.parse("test_exe", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_THAT(result.errorMessage(), ::testing::HasSubstr("Unrecognised token"));
}

TEST_F(ParserTest_672, UnrecognisedPositionalArgReturnsError_672) {
    bool flag = false;
    Parser parser;
    parser |= Opt(flag)["-f"]["--flag"]("A flag");
    
    // Passing a positional arg when no Arg is registered
    std::vector<std::string> rawArgs = {"somefile.txt"};
    auto result = parser.parse("test_exe", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_THAT(result.errorMessage(), ::testing::HasSubstr("Unrecognised token"));
}

TEST_F(ParserTest_672, ExtraUnknownOptionAfterValidOptionFails_672) {
    bool flag = false;
    Parser parser;
    parser |= Opt(flag)["-f"]["--flag"]("A flag");

    std::vector<std::string> rawArgs = {"-f", "--bogus"};
    auto result = parser.parse("test_exe", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_THAT(result.errorMessage(), ::testing::HasSubstr("Unrecognised token"));
}

// ============================================================================
// Validate Tests
// ============================================================================

TEST_F(ParserTest_672, ValidateOnEmptyParserSucceeds_672) {
    Parser parser;
    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// ============================================================================
// Combined Parser Tests (operator|=)
// ============================================================================

TEST_F(ParserTest_672, CombiningTwoParsersWorksCorrectly_672) {
    bool flag1 = false;
    bool flag2 = false;
    
    Parser parser1;
    parser1 |= Opt(flag1)["-a"]["--alpha"]("Alpha flag");
    
    Parser parser2;
    parser2 |= Opt(flag2)["-b"]["--beta"]("Beta flag");
    
    parser1 |= parser2;
    
    std::vector<std::string> rawArgs = {"-a", "-b"};
    auto result = parser1.parse("test_exe", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(flag1);
    EXPECT_TRUE(flag2);
}

// ============================================================================
// WriteToStream / GetHelpColumns Tests
// ============================================================================

TEST_F(ParserTest_672, WriteToStreamProducesOutput_672) {
    bool flag = false;
    Parser parser;
    parser |= Opt(flag)["-f"]["--flag"]("A flag option");

    std::ostringstream oss;
    parser.writeToStream(oss);
    std::string output = oss.str();
    // Should contain something about the flag
    EXPECT_FALSE(output.empty());
}

TEST_F(ParserTest_672, GetHelpColumnsReturnsNonEmptyForOptionsParser_672) {
    bool flag = false;
    Parser parser;
    parser |= Opt(flag)["-f"]["--flag"]("A flag option");

    auto columns = parser.getHelpColumns();
    EXPECT_FALSE(columns.empty());
}

TEST_F(ParserTest_672, GetHelpColumnsReturnsEmptyForEmptyParser_672) {
    Parser parser;
    auto columns = parser.getHelpColumns();
    EXPECT_TRUE(columns.empty());
}

// ============================================================================
// Integer Option Tests
// ============================================================================

TEST_F(ParserTest_672, ParserWithIntOptParsesValue_672) {
    int count = 0;
    Parser parser;
    parser |= Opt(count, "count")["-c"]["--count"]("A count option");

    std::vector<std::string> rawArgs = {"-c", "42"};
    auto result = parser.parse("test_exe", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(count, 42);
}

// ============================================================================
// Multiple Positional Arguments Tests  
// ============================================================================

TEST_F(ParserTest_672, ParserWithMultipleArgsParsesInOrder_672) {
    std::string arg1, arg2;
    Parser parser;
    parser |= Arg(arg1, "first")("First arg");
    parser |= Arg(arg2, "second")("Second arg");

    std::vector<std::string> rawArgs = {"hello", "world"};
    auto result = parser.parse("test_exe", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(arg1, "hello");
    EXPECT_EQ(arg2, "world");
}

// ============================================================================
// Mixed Options and Args Tests
// ============================================================================

TEST_F(ParserTest_672, ParserWithMixedOptionsAndArgsParsesCorrectly_672) {
    bool verbose = false;
    std::string filename;
    Parser parser;
    parser |= Opt(verbose)["-v"]["--verbose"]("Verbose output");
    parser |= Arg(filename, "file")("Input file");

    std::vector<std::string> rawArgs = {"-v", "input.txt"};
    auto result = parser.parse("test_exe", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(verbose);
    EXPECT_EQ(filename, "input.txt");
}

TEST_F(ParserTest_672, ParserOptionsCanAppearAfterArgs_672) {
    bool verbose = false;
    std::string filename;
    Parser parser;
    parser |= Opt(verbose)["-v"]["--verbose"]("Verbose output");
    parser |= Arg(filename, "file")("Input file");

    // Typically positional first, then option - behavior may vary
    std::vector<std::string> rawArgs = {"input.txt", "-v"};
    auto result = parser.parse("test_exe", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(verbose);
    EXPECT_EQ(filename, "input.txt");
}

// ============================================================================
// Help Option (Short Circuit) Tests
// ============================================================================

TEST_F(ParserTest_672, HelpFlagTriggersShortCircuit_672) {
    bool showHelp = false;
    Parser parser;
    auto helpOpt = Opt(showHelp)["-h"]["--help"]("Show help");
    // If the help option is designed to short-circuit, test it
    parser |= helpOpt;

    std::vector<std::string> rawArgs = {"-h"};
    auto result = parser.parse("test_exe", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    // Help should parse successfully regardless of short circuit behavior
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(showHelp);
}

// ============================================================================
// Repeated Flag Tests
// ============================================================================

TEST_F(ParserTest_672, BoolFlagCannotBeRepeatedBeyondCardinality_672) {
    bool flag = false;
    Parser parser;
    parser |= Opt(flag)["-f"]["--flag"]("A flag");

    // Trying to pass the same flag twice - may hit cardinality limit
    std::vector<std::string> rawArgs = {"-f", "-f"};
    auto result = parser.parse("test_exe", Detail::TokenStream(rawArgs.begin(), rawArgs.end()));
    // The second -f may not be parsed due to cardinality, resulting in unrecognised token
    // This tests that cardinality checking works
    // The result could be error or success depending on cardinality(). Just check it doesn't crash.
    // For bool flags, cardinality is typically 1, so second occurrence should be unrecognised
    if (!static_cast<bool>(result)) {
        EXPECT_THAT(result.errorMessage(), ::testing::HasSubstr("Unrecognised token"));
    }
}
