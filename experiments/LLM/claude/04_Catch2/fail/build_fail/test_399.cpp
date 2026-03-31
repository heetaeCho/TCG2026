#include <catch2/internal/catch_clara.hpp>
#include <catch2/catch_all.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

using namespace Catch::Clara;
using namespace Catch::Clara::Detail;

class ParserTest_399 : public ::testing::Test {
protected:
    Parser parser;
};

TEST_F(ParserTest_399, DefaultParserValidates_399) {
    auto result = parser.validate();
    // A default-constructed parser should be valid
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_399, PipeOperatorWithOpt_399) {
    bool flag = false;
    auto opt = Opt(flag, "flag")["-f"]["--flag"]("A test flag");
    Parser combined = Parser{} | opt;
    auto result = combined.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_399, PipeOperatorWithArg_399) {
    std::string value;
    auto arg = Arg(value, "value")("A positional argument");
    Parser combined = Parser{} | arg;
    auto result = combined.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_399, PipeOperatorWithExeName_399) {
    Parser combined = Parser{} | ExeName("testapp");
    auto result = combined.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_399, PipeOperatorWithParser_399) {
    bool flag1 = false;
    bool flag2 = false;
    Parser p1 = Parser{} | Opt(flag1, "f1")["-a"]("flag a");
    Parser p2 = Parser{} | Opt(flag2, "f2")["-b"]("flag b");
    Parser combined = std::move(p1) | std::move(p2);
    auto result = combined.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_399, PipeEqualsMergesParsers_399) {
    bool flag = false;
    Parser other = Parser{} | Opt(flag, "flag")["-x"]("x flag");
    parser |= other;
    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_399, PipeEqualsExeName_399) {
    parser |= ExeName("myexe");
    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_399, PipeEqualsArg_399) {
    std::string val;
    parser |= Arg(val, "val")("a value");
    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_399, GetHelpColumnsEmpty_399) {
    auto columns = parser.getHelpColumns();
    // Default parser should have no help columns (no options/args added)
    EXPECT_TRUE(columns.empty());
}

TEST_F(ParserTest_399, GetHelpColumnsWithOpt_399) {
    bool flag = false;
    parser |= Opt(flag, "flag")["-f"]["--flag"]("A test flag");
    auto columns = parser.getHelpColumns();
    EXPECT_FALSE(columns.empty());
}

TEST_F(ParserTest_399, WriteToStreamEmpty_399) {
    std::ostringstream oss;
    parser.writeToStream(oss);
    // Should not crash; output may be empty or minimal
    std::string output = oss.str();
    // No crash is the primary assertion
    SUCCEED();
}

TEST_F(ParserTest_399, WriteToStreamWithOptions_399) {
    bool flag = false;
    parser |= Opt(flag, "flag")["-f"]["--flag"]("A test flag");
    std::ostringstream oss;
    parser.writeToStream(oss);
    std::string output = oss.str();
    // The output should contain something related to the flag
    EXPECT_FALSE(output.empty());
}

TEST_F(ParserTest_399, ChainingMultiplePipeOperators_399) {
    bool f1 = false, f2 = false;
    std::string arg_val;
    Parser combined = Parser{}
        | ExeName("app")
        | Opt(f1, "f1")["-a"]("flag a")
        | Opt(f2, "f2")["-b"]("flag b")
        | Arg(arg_val, "input")("input file");
    auto result = combined.validate();
    EXPECT_TRUE(static_cast<bool>(result));
    auto columns = combined.getHelpColumns();
    EXPECT_GE(columns.size(), 2u);
}

TEST_F(ParserTest_399, ParseEmptyArgs_399) {
    bool flag = false;
    parser |= Opt(flag)["-f"]["--flag"]("A flag");
    auto args = std::vector<std::string>{};
    auto tokenStream = Detail::TokenStream(Detail::Args(0, nullptr));
    auto result = parser.parse("testexe", tokenStream);
    // Parsing with no arguments should succeed for optional flags
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(ParserTest_399, PipeOperatorPreservesRValue_399) {
    bool flag = false;
    // Test that operator| works with rvalue parser
    auto opt = Opt(flag)["-z"]("z flag");
    Parser result = Parser{} | opt;
    EXPECT_TRUE(static_cast<bool>(result.validate()));
}

TEST_F(ParserTest_399, MultipleArgsCombined_399) {
    std::string val1, val2;
    parser |= Arg(val1, "first")("first arg");
    parser |= Arg(val2, "second")("second arg");
    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}
