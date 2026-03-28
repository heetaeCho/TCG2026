#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara;

class ParserWriteToStreamTest_670 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that writeToStream on a default-constructed (empty) parser produces some output
TEST_F(ParserWriteToStreamTest_670, DefaultParserWritesToStream_670) {
    Parser parser;
    std::ostringstream oss;
    parser.writeToStream(oss);
    // With no exe name set, the "usage:" section should be skipped,
    // but help columns for options (if any) could still appear.
    // At minimum, calling writeToStream should not crash.
    // A default parser has no options or args, so output may be empty or minimal.
    std::string output = oss.str();
    // We just verify it doesn't crash and produces a string (possibly empty).
    SUCCEED();
}

// Test writeToStream with an exe name set
TEST_F(ParserWriteToStreamTest_670, ParserWithExeNameShowsUsage_670) {
    Parser parser;
    std::string exeName;
    parser |= ExeName(exeName);
    
    // Parse to set the exe name
    std::ostringstream oss;
    parser.writeToStream(oss);
    std::string output = oss.str();
    // Default ExeName is "<executable>", so it should appear in usage
    // The output should contain "usage:" if exe name is non-empty
    // Since default ExeName is "<executable>", it's non-empty
    EXPECT_NE(output.find("usage:"), std::string::npos);
}

// Test writeToStream with options added
TEST_F(ParserWriteToStreamTest_670, ParserWithOptionShowsOptions_670) {
    Parser parser;
    bool flag = false;
    parser |= Opt(flag, "flag")["-f"]["--flag"]("A test flag");
    
    std::string exeName;
    parser |= ExeName(exeName);
    
    std::ostringstream oss;
    parser.writeToStream(oss);
    std::string output = oss.str();
    
    // Should contain the word "options" since we have options
    EXPECT_NE(output.find("options"), std::string::npos);
    // Should contain the flag names
    EXPECT_NE(output.find("-f"), std::string::npos);
    EXPECT_NE(output.find("--flag"), std::string::npos);
    // Should contain the description
    EXPECT_NE(output.find("A test flag"), std::string::npos);
}

// Test writeToStream with a required arg
TEST_F(ParserWriteToStreamTest_670, ParserWithRequiredArgShowsArg_670) {
    Parser parser;
    std::string inputFile;
    parser |= Arg(inputFile, "input")("The input file").required();
    
    std::string exeName;
    parser |= ExeName(exeName);
    
    std::ostringstream oss;
    parser.writeToStream(oss);
    std::string output = oss.str();
    
    // Should contain the hint for the arg
    EXPECT_NE(output.find("input"), std::string::npos);
}

// Test writeToStream with an optional arg
TEST_F(ParserWriteToStreamTest_670, ParserWithOptionalArgShowsBrackets_670) {
    Parser parser;
    std::string optionalArg;
    parser |= Arg(optionalArg, "optarg")("An optional argument").optional();
    
    std::string exeName;
    parser |= ExeName(exeName);
    
    std::ostringstream oss;
    parser.writeToStream(oss);
    std::string output = oss.str();
    
    // Optional args should be wrapped in brackets in the usage line
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
    EXPECT_NE(output.find("optarg"), std::string::npos);
}

// Test writeToStream with multiple options
TEST_F(ParserWriteToStreamTest_670, ParserWithMultipleOptionsShowsAll_670) {
    Parser parser;
    bool verbose = false;
    std::string output_file;
    int count = 0;
    
    parser |= Opt(verbose)["-v"]["--verbose"]("Enable verbose output");
    parser |= Opt(output_file, "file")["-o"]["--output"]("Output file path");
    parser |= Opt(count, "count")["-n"]["--count"]("Number of iterations");
    
    std::string exeName;
    parser |= ExeName(exeName);
    
    std::ostringstream oss;
    parser.writeToStream(oss);
    std::string result = oss.str();
    
    EXPECT_NE(result.find("-v"), std::string::npos);
    EXPECT_NE(result.find("--verbose"), std::string::npos);
    EXPECT_NE(result.find("-o"), std::string::npos);
    EXPECT_NE(result.find("--output"), std::string::npos);
    EXPECT_NE(result.find("-n"), std::string::npos);
    EXPECT_NE(result.find("--count"), std::string::npos);
}

// Test writeToStream with both args and options
TEST_F(ParserWriteToStreamTest_670, ParserWithArgsAndOptionsShowsBoth_670) {
    Parser parser;
    std::string inputFile;
    bool help = false;
    
    parser |= Arg(inputFile, "source")("Source file").required();
    parser |= Opt(help)["-h"]["--help"]("Show help");
    
    std::string exeName;
    parser |= ExeName(exeName);
    
    std::ostringstream oss;
    parser.writeToStream(oss);
    std::string result = oss.str();
    
    EXPECT_NE(result.find("source"), std::string::npos);
    EXPECT_NE(result.find("-h"), std::string::npos);
    EXPECT_NE(result.find("--help"), std::string::npos);
    EXPECT_NE(result.find("options"), std::string::npos);
}

// Test writeToStream with no exe name (empty name) - should skip usage header
TEST_F(ParserWriteToStreamTest_670, ParserNoExeNameSkipsUsageHeader_670) {
    Parser parser;
    // Don't set any exe name - leave parser as default constructed
    // Default ExeName has "<executable>" which is non-empty
    // Let's see what happens with default parser with just options
    bool flag = false;
    parser |= Opt(flag)["-f"]("flag desc");
    
    std::ostringstream oss;
    parser.writeToStream(oss);
    std::string result = oss.str();
    
    // Should still produce some output for the options help columns
    EXPECT_FALSE(result.empty());
}

// Test that writeToStream can be called multiple times
TEST_F(ParserWriteToStreamTest_670, WriteToStreamCanBeCalledMultipleTimes_670) {
    Parser parser;
    bool flag = false;
    parser |= Opt(flag)["-f"]["--flag"]("A flag");
    
    std::string exeName;
    parser |= ExeName(exeName);
    
    std::ostringstream oss1, oss2;
    parser.writeToStream(oss1);
    parser.writeToStream(oss2);
    
    // Both calls should produce the same output
    EXPECT_EQ(oss1.str(), oss2.str());
}

// Test writeToStream with long description text (wrapping behavior)
TEST_F(ParserWriteToStreamTest_670, LongDescriptionHandledCorrectly_670) {
    Parser parser;
    bool flag = false;
    std::string longDesc = "This is a very long description that should be wrapped "
                           "appropriately by the text flow system when writing to "
                           "the output stream because it exceeds normal column width.";
    parser |= Opt(flag)["-l"]["--long-option"](longDesc);
    
    std::string exeName;
    parser |= ExeName(exeName);
    
    std::ostringstream oss;
    parser.writeToStream(oss);
    std::string result = oss.str();
    
    // The description content should appear (possibly wrapped across lines)
    EXPECT_NE(result.find("very long description"), std::string::npos);
}

// Test writeToStream with combined parser (operator|=)
TEST_F(ParserWriteToStreamTest_670, CombinedParsersWriteCorrectly_670) {
    Parser parser1;
    bool flag1 = false;
    parser1 |= Opt(flag1)["-a"]("Option A");
    
    Parser parser2;
    bool flag2 = false;
    parser2 |= Opt(flag2)["-b"]("Option B");
    
    parser1 |= parser2;
    
    std::string exeName;
    parser1 |= ExeName(exeName);
    
    std::ostringstream oss;
    parser1.writeToStream(oss);
    std::string result = oss.str();
    
    EXPECT_NE(result.find("-a"), std::string::npos);
    EXPECT_NE(result.find("-b"), std::string::npos);
    EXPECT_NE(result.find("Option A"), std::string::npos);
    EXPECT_NE(result.find("Option B"), std::string::npos);
}

// Test writeToStream output starts with "usage:" when exe name is set
TEST_F(ParserWriteToStreamTest_670, OutputStartsWithUsageWhenExeNameSet_670) {
    Parser parser;
    std::string exeName;
    parser |= ExeName(exeName);
    bool flag = false;
    parser |= Opt(flag)["-x"]("X option");
    
    std::ostringstream oss;
    parser.writeToStream(oss);
    std::string result = oss.str();
    
    // Output should start with "usage:"
    EXPECT_EQ(result.substr(0, 6), "usage:");
}

// Test with multiple args, mixing required and optional
TEST_F(ParserWriteToStreamTest_670, MixedRequiredAndOptionalArgs_670) {
    Parser parser;
    std::string requiredArg;
    std::string optionalArg;
    
    parser |= Arg(requiredArg, "required")("A required arg").required();
    parser |= Arg(optionalArg, "optional")("An optional arg").optional();
    
    std::string exeName;
    parser |= ExeName(exeName);
    
    std::ostringstream oss;
    parser.writeToStream(oss);
    std::string result = oss.str();
    
    EXPECT_NE(result.find("required"), std::string::npos);
    EXPECT_NE(result.find("optional"), std::string::npos);
}

// Test getHelpColumns returns correct structure
TEST_F(ParserWriteToStreamTest_670, GetHelpColumnsReturnsColumns_670) {
    Parser parser;
    bool flag = false;
    parser |= Opt(flag)["-t"]["--test"]("Test description");
    
    auto columns = parser.getHelpColumns();
    
    EXPECT_FALSE(columns.empty());
    // The left column should contain the option flags
    bool foundFlag = false;
    for (const auto& col : columns) {
        if (col.left.find("-t") != std::string::npos) {
            foundFlag = true;
            break;
        }
    }
    EXPECT_TRUE(foundFlag);
}

// Test getHelpColumns is empty for parser with no options
TEST_F(ParserWriteToStreamTest_670, GetHelpColumnsEmptyForNoOptions_670) {
    Parser parser;
    auto columns = parser.getHelpColumns();
    
    // With no options added, help columns should be empty
    EXPECT_TRUE(columns.empty());
}

// Test validate on default parser
TEST_F(ParserWriteToStreamTest_670, ValidateOnDefaultParser_670) {
    Parser parser;
    auto result = parser.validate();
    // Default parser should validate successfully
    EXPECT_TRUE(static_cast<bool>(result));
}
