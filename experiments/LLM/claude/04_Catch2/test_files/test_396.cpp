#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara;

class ParserOptOperatorTest_396 : public ::testing::Test {
protected:
    Parser parser;
};

// Test that adding a single Opt to a Parser works and the parser remains valid
TEST_F(ParserOptOperatorTest_396, AddSingleOptToParser_396) {
    bool flag = false;
    Opt opt(flag);
    opt["-f"]["--flag"];
    
    parser |= opt;
    
    auto result = parser.validate();
    EXPECT_TRUE(result);
}

// Test that adding multiple Opts to a Parser works
TEST_F(ParserOptOperatorTest_396, AddMultipleOptsToParser_396) {
    bool flag1 = false;
    bool flag2 = false;
    
    Opt opt1(flag1);
    opt1["-a"]["--alpha"];
    
    Opt opt2(flag2);
    opt2["-b"]["--beta"];
    
    parser |= opt1;
    parser |= opt2;
    
    auto result = parser.validate();
    EXPECT_TRUE(result);
}

// Test that the operator returns a reference to the same parser (chaining)
TEST_F(ParserOptOperatorTest_396, OperatorReturnsParserReference_396) {
    bool flag = false;
    Opt opt(flag);
    opt["-x"]["--xray"];
    
    Parser& returned = (parser |= opt);
    
    EXPECT_EQ(&returned, &parser);
}

// Test that added Opt appears in help columns
TEST_F(ParserOptOperatorTest_396, AddedOptAppearsInHelpColumns_396) {
    std::string value;
    Opt opt(value, "value");
    opt["-v"]["--value"];
    
    parser |= opt;
    
    auto helpCols = parser.getHelpColumns();
    EXPECT_FALSE(helpCols.empty());
}

// Test that adding no opts results in empty help columns for options
TEST_F(ParserOptOperatorTest_396, EmptyParserHasNoHelpColumns_396) {
    auto helpCols = parser.getHelpColumns();
    EXPECT_TRUE(helpCols.empty());
}

// Test that multiple opts produce multiple help columns
TEST_F(ParserOptOperatorTest_396, MultipleOptsProduceMultipleHelpColumns_396) {
    bool flag1 = false;
    bool flag2 = false;
    bool flag3 = false;
    
    Opt opt1(flag1);
    opt1["-a"]["--alpha"];
    
    Opt opt2(flag2);
    opt2["-b"]["--beta"];
    
    Opt opt3(flag3);
    opt3["-c"]["--charlie"];
    
    parser |= opt1;
    parser |= opt2;
    parser |= opt3;
    
    auto helpCols = parser.getHelpColumns();
    EXPECT_EQ(helpCols.size(), 3u);
}

// Test that writeToStream does not crash after adding opts
TEST_F(ParserOptOperatorTest_396, WriteToStreamAfterAddingOpt_396) {
    bool flag = false;
    Opt opt(flag);
    opt["-f"]["--flag"];
    
    parser |= opt;
    
    std::ostringstream oss;
    EXPECT_NO_THROW(parser.writeToStream(oss));
    // The output should contain something related to the option
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test chaining multiple |= operations
TEST_F(ParserOptOperatorTest_396, ChainingMultipleOperations_396) {
    bool f1 = false, f2 = false;
    
    Opt opt1(f1);
    opt1["-a"];
    
    Opt opt2(f2);
    opt2["-b"];
    
    // Chain operations
    (parser |= opt1) |= opt2;
    
    auto helpCols = parser.getHelpColumns();
    EXPECT_EQ(helpCols.size(), 2u);
}

// Test adding an Opt with a value hint (non-flag)
TEST_F(ParserOptOperatorTest_396, AddOptWithValueHint_396) {
    int value = 0;
    Opt opt(value, "number");
    opt["-n"]["--number"];
    
    parser |= opt;
    
    auto result = parser.validate();
    EXPECT_TRUE(result);
    
    auto helpCols = parser.getHelpColumns();
    EXPECT_EQ(helpCols.size(), 1u);
}

// Test that validate works after adding opt without option name
TEST_F(ParserOptOperatorTest_396, AddOptWithoutNameFailsValidation_396) {
    bool flag = false;
    Opt opt(flag);
    // No option name set via operator[]
    
    parser |= opt;
    
    auto result = parser.validate();
    // An opt without a name should fail validation
    EXPECT_FALSE(result);
}

// Test combining Parser |= Parser and Parser |= Opt
TEST_F(ParserOptOperatorTest_396, CombineParserAndOptOperators_396) {
    bool f1 = false, f2 = false;
    
    Parser other;
    Opt opt1(f1);
    opt1["-a"]["--alpha"];
    other |= opt1;
    
    Opt opt2(f2);
    opt2["-b"]["--beta"];
    
    parser |= other;
    parser |= opt2;
    
    auto helpCols = parser.getHelpColumns();
    EXPECT_EQ(helpCols.size(), 2u);
}

// Test that parser can be written to stream when empty
TEST_F(ParserOptOperatorTest_396, EmptyParserWriteToStream_396) {
    std::ostringstream oss;
    EXPECT_NO_THROW(parser.writeToStream(oss));
}

// Test adding Opt with lambda
TEST_F(ParserOptOperatorTest_396, AddOptWithLambda_396) {
    std::string captured;
    auto opt = Opt([&captured](std::string const& val) {
        captured = val;
    }, "val")["-s"]["--str"];
    
    parser |= opt;
    
    auto result = parser.validate();
    EXPECT_TRUE(result);
    
    auto helpCols = parser.getHelpColumns();
    EXPECT_EQ(helpCols.size(), 1u);
}
