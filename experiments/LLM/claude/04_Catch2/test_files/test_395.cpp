#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

using namespace Catch::Clara;
using namespace Catch::Clara::Detail;

class ParserTest_395 : public ::testing::Test {
protected:
    Parser parser;
};

// Test that a default-constructed Parser has no help columns (no args/options added)
TEST_F(ParserTest_395, DefaultConstructedParserHasEmptyHelpColumns_395) {
    auto columns = parser.getHelpColumns();
    EXPECT_TRUE(columns.empty());
}

// Test that operator|= with an Arg returns a reference to the same parser
TEST_F(ParserTest_395, OperatorOrEqualsArgReturnsSelf_395) {
    std::string value;
    Arg arg = Arg(value, "test");
    Parser& result = (parser |= arg);
    EXPECT_EQ(&result, &parser);
}

// Test that adding an Arg increases the help columns
TEST_F(ParserTest_395, AddingArgIncreasesHelpColumns_395) {
    std::string value;
    Arg arg = Arg(value, "testarg");
    parser |= arg;
    auto columns = parser.getHelpColumns();
    // After adding one arg, we expect at least one help column entry
    EXPECT_GE(columns.size(), 1u);
}

// Test that adding multiple Args increases help columns accordingly
TEST_F(ParserTest_395, AddingMultipleArgsIncreasesHelpColumns_395) {
    std::string value1, value2, value3;
    parser |= Arg(value1, "arg1");
    parser |= Arg(value2, "arg2");
    parser |= Arg(value3, "arg3");
    auto columns = parser.getHelpColumns();
    EXPECT_GE(columns.size(), 3u);
}

// Test that operator|= with ExeName returns a reference to the same parser
TEST_F(ParserTest_395, OperatorOrEqualsExeNameReturnsSelf_395) {
    ExeName exeName("myapp");
    Parser& result = (parser |= exeName);
    EXPECT_EQ(&result, &parser);
}

// Test that operator|= with another Parser returns a reference to the same parser
TEST_F(ParserTest_395, OperatorOrEqualsParserReturnsSelf_395) {
    Parser other;
    Parser& result = (parser |= other);
    EXPECT_EQ(&result, &parser);
}

// Test that merging two parsers combines their args
TEST_F(ParserTest_395, MergingParsersCombiensArgs_395) {
    std::string val1, val2;
    Parser other;
    other |= Arg(val1, "otherarg1");
    other |= Arg(val2, "otherarg2");

    parser |= other;
    auto columns = parser.getHelpColumns();
    EXPECT_GE(columns.size(), 2u);
}

// Test that validate on a default parser succeeds
TEST_F(ParserTest_395, ValidateOnDefaultParserSucceeds_395) {
    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test writeToStream does not crash on empty parser
TEST_F(ParserTest_395, WriteToStreamEmptyParserDoesNotCrash_395) {
    std::ostringstream oss;
    EXPECT_NO_THROW(parser.writeToStream(oss));
}

// Test writeToStream produces output after adding an Opt
TEST_F(ParserTest_395, WriteToStreamWithOptProducesOutput_395) {
    bool flag = false;
    Opt opt = Opt(flag, "flag")["-f"]["--flag"]("A flag option");
    parser |= opt;
    std::ostringstream oss;
    parser.writeToStream(oss);
    std::string output = oss.str();
    // We expect some output containing the flag info
    EXPECT_FALSE(output.empty());
}

// Test that adding Opt increases help columns
TEST_F(ParserTest_395, AddingOptIncreasesHelpColumns_395) {
    bool flag = false;
    Opt opt = Opt(flag, "flag")["-f"]["--flag"]("A flag option");
    parser |= opt;
    auto columns = parser.getHelpColumns();
    EXPECT_GE(columns.size(), 1u);
}

// Test parse with empty token stream
TEST_F(ParserTest_395, ParseWithEmptyTokenStream_395) {
    std::vector<std::string> args;
    std::vector<const char*> argv;
    // Parse with no arguments
    auto result = parser.parse("testapp", Detail::TokenStream(Detail::Args(0, nullptr)));
    // The parse result should indicate success for an empty parser with no tokens
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test chaining multiple operator|= calls
TEST_F(ParserTest_395, ChainingMultipleOperatorOrEquals_395) {
    std::string val1, val2;
    bool flag = false;
    
    Parser& ref1 = (parser |= Arg(val1, "arg1"));
    Parser& ref2 = (parser |= Arg(val2, "arg2"));
    Parser& ref3 = (parser |= Opt(flag, "flag")["-f"]("flag"));
    
    EXPECT_EQ(&ref1, &parser);
    EXPECT_EQ(&ref2, &parser);
    EXPECT_EQ(&ref3, &parser);
}

// Test merging an empty parser does not change help columns
TEST_F(ParserTest_395, MergingEmptyParserNoChange_395) {
    std::string val;
    parser |= Arg(val, "myarg");
    auto columnsBefore = parser.getHelpColumns();
    
    Parser emptyParser;
    parser |= emptyParser;
    
    auto columnsAfter = parser.getHelpColumns();
    EXPECT_EQ(columnsBefore.size(), columnsAfter.size());
}

// Test validate after adding args
TEST_F(ParserTest_395, ValidateAfterAddingArgs_395) {
    std::string val;
    parser |= Arg(val, "testarg");
    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test writeToStream with ExeName set
TEST_F(ParserTest_395, WriteToStreamWithExeName_395) {
    parser |= ExeName("myapplication");
    std::ostringstream oss;
    parser.writeToStream(oss);
    std::string output = oss.str();
    // Output should contain the exe name
    EXPECT_NE(output.find("myapplication"), std::string::npos);
}
