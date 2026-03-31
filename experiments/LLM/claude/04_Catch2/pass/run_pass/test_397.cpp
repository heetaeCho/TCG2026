#include <catch2/internal/catch_clara.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

using namespace Catch::Clara;

class ParserOptOperatorTest_397 : public ::testing::Test {
protected:
    Parser parser;
};

// Test that operator|= with an Opt compiles and returns a reference to the parser
TEST_F(ParserOptOperatorTest_397, AddOptToParser_ReturnsParserReference_397) {
    bool flag = false;
    Opt opt(flag);
    opt["-f"]["--flag"];
    
    Parser& result = (parser |= std::move(opt));
    EXPECT_EQ(&result, &parser);
}

// Test adding a single option to the parser
TEST_F(ParserOptOperatorTest_397, AddSingleOpt_397) {
    bool flag = false;
    Opt opt(flag);
    opt["-f"]["--flag"];
    
    parser |= std::move(opt);
    
    // Verify through getHelpColumns that the option was added
    auto columns = parser.getHelpColumns();
    EXPECT_GE(columns.size(), 1u);
}

// Test adding multiple options to the parser
TEST_F(ParserOptOperatorTest_397, AddMultipleOpts_397) {
    bool flag1 = false;
    bool flag2 = false;
    
    Opt opt1(flag1);
    opt1["-a"]["--alpha"];
    
    Opt opt2(flag2);
    opt2["-b"]["--beta"];
    
    parser |= std::move(opt1);
    parser |= std::move(opt2);
    
    auto columns = parser.getHelpColumns();
    EXPECT_GE(columns.size(), 2u);
}

// Test adding an Opt with a string reference and hint
TEST_F(ParserOptOperatorTest_397, AddOptWithStringRefAndHint_397) {
    std::string value;
    Opt opt(value, "value");
    opt["-v"]["--value"];
    
    parser |= std::move(opt);
    
    auto columns = parser.getHelpColumns();
    EXPECT_GE(columns.size(), 1u);
}

// Test adding an Opt with a lambda
TEST_F(ParserOptOperatorTest_397, AddOptWithLambda_397) {
    std::string captured;
    Opt opt([&captured](std::string const& val) { captured = val; }, "name");
    opt["-n"]["--name"];
    
    parser |= std::move(opt);
    
    auto columns = parser.getHelpColumns();
    EXPECT_GE(columns.size(), 1u);
}

// Test that parser validates successfully after adding a valid opt
TEST_F(ParserOptOperatorTest_397, ValidateAfterAddingOpt_397) {
    bool flag = false;
    Opt opt(flag);
    opt["-f"]["--flag"];
    
    parser |= std::move(opt);
    
    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test chaining multiple operator|= calls
TEST_F(ParserOptOperatorTest_397, ChainingOperator_397) {
    bool flag1 = false;
    bool flag2 = false;
    bool flag3 = false;
    
    Opt opt1(flag1);
    opt1["-a"];
    Opt opt2(flag2);
    opt2["-b"];
    Opt opt3(flag3);
    opt3["-c"];
    
    // Chain: since operator|= returns Parser&, we can chain
    (parser |= std::move(opt1));
    (parser |= std::move(opt2));
    (parser |= std::move(opt3));
    
    auto columns = parser.getHelpColumns();
    EXPECT_GE(columns.size(), 3u);
}

// Test writeToStream after adding options
TEST_F(ParserOptOperatorTest_397, WriteToStreamAfterAddingOpt_397) {
    bool flag = false;
    Opt opt(flag);
    opt["-f"]["--flag"];
    
    parser |= std::move(opt);
    
    std::ostringstream oss;
    parser.writeToStream(oss);
    std::string output = oss.str();
    // The output should contain something related to the option
    EXPECT_FALSE(output.empty());
}

// Test empty parser has no help columns
TEST_F(ParserOptOperatorTest_397, EmptyParserHasNoHelpColumns_397) {
    auto columns = parser.getHelpColumns();
    EXPECT_EQ(columns.size(), 0u);
}

// Test that Opt's isMatch works correctly for added option names
TEST(OptTest_397, IsMatchReturnsTrueForMatchingName_397) {
    bool flag = false;
    Opt opt(flag);
    opt["-f"]["--flag"];
    
    EXPECT_TRUE(opt.isMatch("-f"));
    EXPECT_TRUE(opt.isMatch("--flag"));
}

// Test that Opt's isMatch returns false for non-matching names
TEST(OptTest_397, IsMatchReturnsFalseForNonMatchingName_397) {
    bool flag = false;
    Opt opt(flag);
    opt["-f"]["--flag"];
    
    EXPECT_FALSE(opt.isMatch("-g"));
    EXPECT_FALSE(opt.isMatch("--other"));
}

// Test that Opt validates correctly when it has option names
TEST(OptTest_397, ValidateWithOptionNames_397) {
    bool flag = false;
    Opt opt(flag);
    opt["-f"]["--flag"];
    
    auto result = opt.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test Opt operator[] returns reference to self for chaining
TEST(OptTest_397, OperatorBracketReturnsSelfReference_397) {
    bool flag = false;
    Opt opt(flag);
    
    Opt& ref = opt["-f"];
    EXPECT_EQ(&ref, &opt);
    
    Opt& ref2 = ref["--flag"];
    EXPECT_EQ(&ref2, &opt);
}

// Test adding Opt with integer ref
TEST_F(ParserOptOperatorTest_397, AddOptWithIntRef_397) {
    int value = 0;
    Opt opt(value, "count");
    opt["-c"]["--count"];
    
    parser |= std::move(opt);
    
    auto columns = parser.getHelpColumns();
    EXPECT_GE(columns.size(), 1u);
}

// Test parser |= with another parser
TEST_F(ParserOptOperatorTest_397, MergeParserWithAnotherParser_397) {
    bool flag1 = false;
    Opt opt1(flag1);
    opt1["-a"];
    parser |= std::move(opt1);
    
    Parser other;
    bool flag2 = false;
    Opt opt2(flag2);
    opt2["-b"];
    other |= std::move(opt2);
    
    parser |= other;
    
    auto columns = parser.getHelpColumns();
    EXPECT_GE(columns.size(), 2u);
}

// Test getHelpColumns content
TEST(OptTest_397, GetHelpColumnsContent_397) {
    bool flag = false;
    Opt opt(flag);
    opt["-f"]["--flag"];
    
    auto columns = opt.getHelpColumns();
    // Should have left/right columns with option info
    EXPECT_FALSE(columns.left.empty());
}
