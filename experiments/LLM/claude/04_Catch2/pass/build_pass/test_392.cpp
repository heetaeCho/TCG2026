#include "catch2/internal/catch_clara.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace Catch;
using namespace Catch::Clara;

// Test fixture for Opt tests
class OptTest_392 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that operator[] adds an option name and returns reference to self
TEST_F(OptTest_392, OperatorBracketReturnsSelf_392) {
    bool flag = false;
    Opt opt(flag);
    Opt& result = opt["--test"];
    EXPECT_EQ(&result, &opt);
}

// Test that operator[] can be chained
TEST_F(OptTest_392, OperatorBracketChaining_392) {
    bool flag = false;
    Opt opt(flag);
    Opt& result = opt["--test"]["-t"];
    EXPECT_EQ(&result, &opt);
}

// Test that isMatch returns true for a registered option name
TEST_F(OptTest_392, IsMatchReturnsTrueForRegisteredName_392) {
    bool flag = false;
    Opt opt(flag);
    opt["--verbose"];
    EXPECT_TRUE(opt.isMatch("--verbose"));
}

// Test that isMatch returns false for an unregistered option name
TEST_F(OptTest_392, IsMatchReturnsFalseForUnregisteredName_392) {
    bool flag = false;
    Opt opt(flag);
    opt["--verbose"];
    EXPECT_FALSE(opt.isMatch("--debug"));
}

// Test that isMatch works with short option names
TEST_F(OptTest_392, IsMatchWorksWithShortOption_392) {
    bool flag = false;
    Opt opt(flag);
    opt["-v"];
    EXPECT_TRUE(opt.isMatch("-v"));
}

// Test that isMatch works when multiple names are registered
TEST_F(OptTest_392, IsMatchWorksWithMultipleNames_392) {
    bool flag = false;
    Opt opt(flag);
    opt["--verbose"]["-v"];
    EXPECT_TRUE(opt.isMatch("--verbose"));
    EXPECT_TRUE(opt.isMatch("-v"));
}

// Test that isMatch returns false when no option names are registered
TEST_F(OptTest_392, IsMatchReturnsFalseWhenNoNamesRegistered_392) {
    bool flag = false;
    Opt opt(flag);
    EXPECT_FALSE(opt.isMatch("--anything"));
}

// Test construction with bool reference
TEST_F(OptTest_392, ConstructionWithBoolRef_392) {
    bool flag = false;
    Opt opt(flag);
    opt["--flag"];
    EXPECT_TRUE(opt.isMatch("--flag"));
}

// Test construction with value reference and hint
TEST_F(OptTest_392, ConstructionWithValueRefAndHint_392) {
    std::string value;
    Opt opt(value, "value");
    opt["--name"]["-n"];
    EXPECT_TRUE(opt.isMatch("--name"));
    EXPECT_TRUE(opt.isMatch("-n"));
}

// Test validate succeeds for option with at least one name
TEST_F(OptTest_392, ValidateSucceedsWithOptionName_392) {
    bool flag = false;
    Opt opt(flag);
    opt["--flag"];
    auto result = opt.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test validate fails for option with no names (boundary)
TEST_F(OptTest_392, ValidateFailsWithNoOptionNames_392) {
    bool flag = false;
    Opt opt(flag);
    auto result = opt.validate();
    // An option without any names should fail validation
    // (This is an expected behavior based on the interface)
    // We check if validate reports an error
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test that operator[] works with StringRef from std::string
TEST_F(OptTest_392, OperatorBracketWithStdString_392) {
    bool flag = false;
    Opt opt(flag);
    std::string name = "--option";
    opt[StringRef(name)];
    EXPECT_TRUE(opt.isMatch("--option"));
}

// Test that operator[] works with const char*
TEST_F(OptTest_392, OperatorBracketWithConstCharPtr_392) {
    bool flag = false;
    Opt opt(flag);
    opt["--test-option"];
    EXPECT_TRUE(opt.isMatch("--test-option"));
}

// Test adding many option names
TEST_F(OptTest_392, ManyOptionNames_392) {
    bool flag = false;
    Opt opt(flag);
    opt["--alpha"]["-a"]["--bravo"]["-b"]["--charlie"]["-c"];
    EXPECT_TRUE(opt.isMatch("--alpha"));
    EXPECT_TRUE(opt.isMatch("-a"));
    EXPECT_TRUE(opt.isMatch("--bravo"));
    EXPECT_TRUE(opt.isMatch("-b"));
    EXPECT_TRUE(opt.isMatch("--charlie"));
    EXPECT_TRUE(opt.isMatch("-c"));
    EXPECT_FALSE(opt.isMatch("--delta"));
}

// Test getHelpColumns returns valid help columns
TEST_F(OptTest_392, GetHelpColumnsReturnsValidData_392) {
    std::string value;
    Opt opt(value, "filename");
    opt["--output"]["-o"];
    auto helpCols = opt.getHelpColumns();
    // Just verify it doesn't crash and returns something
    // The help columns should contain the option names
    EXPECT_FALSE(helpCols.left.empty());
}

// Test with lambda accepting a string
TEST_F(OptTest_392, ConstructionWithLambdaAndHint_392) {
    std::string captured;
    auto lambda = [&captured](std::string const& s) { captured = s; };
    Opt opt(lambda, "value");
    opt["--input"]["-i"];
    EXPECT_TRUE(opt.isMatch("--input"));
    EXPECT_TRUE(opt.isMatch("-i"));
}

// Test isMatch with empty string
TEST_F(OptTest_392, IsMatchWithEmptyString_392) {
    bool flag = false;
    Opt opt(flag);
    opt["--test"];
    EXPECT_FALSE(opt.isMatch(""));
}

// Test that validate works for option names starting with single dash
TEST_F(OptTest_392, ValidateWithSingleDashOption_392) {
    bool flag = false;
    Opt opt(flag);
    opt["-f"];
    auto result = opt.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}
