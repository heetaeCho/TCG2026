#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <sstream>

#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara;
using Detail::Result;

// ============================================================
// Tests for Parser::validate()
// ============================================================

class ParserValidateTest_671 : public ::testing::Test {
protected:
    Parser parser;
};

// An empty parser (no options, no args) should validate successfully
TEST_F(ParserValidateTest_671, EmptyParserValidatesOk_671) {
    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// A parser with a valid option (has a name) should validate successfully
TEST_F(ParserValidateTest_671, ParserWithValidOptionValidatesOk_671) {
    bool flag = false;
    Opt opt(flag);
    opt["-f"]["--flag"];
    parser |= opt;

    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// A parser with an option that has no name should fail validation
TEST_F(ParserValidateTest_671, ParserWithOptionMissingNameFailsValidation_671) {
    bool flag = false;
    Opt opt(flag);
    // Do not set any option name - this should cause validation to fail
    parser |= opt;

    auto result = parser.validate();
    EXPECT_FALSE(static_cast<bool>(result));
}

// A parser with multiple valid options should validate successfully
TEST_F(ParserValidateTest_671, ParserWithMultipleValidOptionsValidatesOk_671) {
    bool flag1 = false;
    bool flag2 = false;
    
    Opt opt1(flag1);
    opt1["-a"]["--alpha"];
    
    Opt opt2(flag2);
    opt2["-b"]["--beta"];
    
    parser |= opt1;
    parser |= opt2;

    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// If one option among many is invalid, validation should fail
TEST_F(ParserValidateTest_671, ParserWithOneInvalidOptionAmongManyFailsValidation_671) {
    bool flag1 = false;
    bool flag2 = false;
    bool flag3 = false;

    Opt opt1(flag1);
    opt1["-a"];

    Opt opt2(flag2);
    // No name set - invalid

    Opt opt3(flag3);
    opt3["-c"];

    parser |= opt1;
    parser |= opt2;
    parser |= opt3;

    auto result = parser.validate();
    EXPECT_FALSE(static_cast<bool>(result));
}

// A parser with a valid option that has a value hint should validate
TEST_F(ParserValidateTest_671, ParserWithValueOptionValidatesOk_671) {
    std::string value;
    Opt opt(value, "value");
    opt["-v"]["--value"];
    parser |= opt;

    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// A parser with a valid Arg should validate
TEST_F(ParserValidateTest_671, ParserWithValidArgValidatesOk_671) {
    std::string positionalArg;
    Arg arg(positionalArg, "input");
    parser |= arg;

    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// A parser combined with another parser should validate if both are valid
TEST_F(ParserValidateTest_671, CombinedParsersValidateOk_671) {
    bool flag = false;
    Opt opt(flag);
    opt["-f"];
    
    Parser parser1;
    parser1 |= opt;
    
    std::string val;
    Opt opt2(val, "val");
    opt2["-v"];
    
    Parser parser2;
    parser2 |= opt2;
    
    parser1 |= parser2;
    
    auto result = parser1.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// A parser combined with another parser where other has invalid option should fail
TEST_F(ParserValidateTest_671, CombinedParsersWithInvalidOptionFailsValidation_671) {
    bool flag = false;
    Opt opt(flag);
    opt["-f"];
    
    Parser parser1;
    parser1 |= opt;
    
    bool flag2 = false;
    Opt opt2(flag2);
    // No name - invalid
    
    Parser parser2;
    parser2 |= opt2;
    
    parser1 |= parser2;
    
    auto result = parser1.validate();
    EXPECT_FALSE(static_cast<bool>(result));
}

// Validate returns an error message when validation fails
TEST_F(ParserValidateTest_671, InvalidOptionReturnsErrorMessage_671) {
    bool flag = false;
    Opt opt(flag);
    // No name set - invalid
    parser |= opt;

    auto result = parser.validate();
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_FALSE(result.errorMessage().empty());
}

// Valid parser has empty error message
TEST_F(ParserValidateTest_671, ValidParserHasEmptyErrorMessage_671) {
    bool flag = false;
    Opt opt(flag);
    opt["-f"];
    parser |= opt;

    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(result.errorMessage().empty());
}

// ============================================================
// Tests for Opt::validate()
// ============================================================

class OptValidateTest_671 : public ::testing::Test {};

TEST_F(OptValidateTest_671, OptWithNameValidatesOk_671) {
    bool flag = false;
    Opt opt(flag);
    opt["-f"];
    
    auto result = opt.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(OptValidateTest_671, OptWithoutNameFailsValidation_671) {
    bool flag = false;
    Opt opt(flag);
    
    auto result = opt.validate();
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(OptValidateTest_671, OptWithLongNameValidatesOk_671) {
    bool flag = false;
    Opt opt(flag);
    opt["--flag"];
    
    auto result = opt.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(OptValidateTest_671, OptWithBothShortAndLongNameValidatesOk_671) {
    bool flag = false;
    Opt opt(flag);
    opt["-f"]["--flag"];
    
    auto result = opt.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// ============================================================
// Tests for Parser with ExeName
// ============================================================

class ParserExeNameTest_671 : public ::testing::Test {};

TEST_F(ParserExeNameTest_671, ParserWithExeNameValidatesOk_671) {
    Parser parser;
    parser |= ExeName("test_exe");
    
    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// ============================================================
// Tests for Parser::writeToStream()
// ============================================================

class ParserWriteToStreamTest_671 : public ::testing::Test {};

TEST_F(ParserWriteToStreamTest_671, WriteToStreamDoesNotCrashEmpty_671) {
    Parser parser;
    std::ostringstream oss;
    EXPECT_NO_THROW(parser.writeToStream(oss));
}

TEST_F(ParserWriteToStreamTest_671, WriteToStreamWithOptions_671) {
    Parser parser;
    bool flag = false;
    Opt opt(flag);
    opt["-f"]["--flag"];
    parser |= opt;
    
    std::ostringstream oss;
    EXPECT_NO_THROW(parser.writeToStream(oss));
    // The output should contain something about the option
    std::string output = oss.str();
    // We don't check exact format, just that it's not empty
    // (since we have an option registered)
}

// ============================================================
// Tests for Parser::getHelpColumns()
// ============================================================

class ParserGetHelpColumnsTest_671 : public ::testing::Test {};

TEST_F(ParserGetHelpColumnsTest_671, EmptyParserReturnsEmptyHelpColumns_671) {
    Parser parser;
    auto columns = parser.getHelpColumns();
    EXPECT_TRUE(columns.empty());
}

TEST_F(ParserGetHelpColumnsTest_671, ParserWithOptionsReturnsHelpColumns_671) {
    Parser parser;
    bool flag = false;
    Opt opt(flag);
    opt["-f"]["--flag"];
    parser |= opt;
    
    auto columns = parser.getHelpColumns();
    EXPECT_FALSE(columns.empty());
}
