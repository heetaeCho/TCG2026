#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara;

class OptTest_662 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test getHelpColumns with a single short option name and no hint
TEST_F(OptTest_662, GetHelpColumns_SingleShortOption_NoHint_662) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]("A flag option");
    
    auto cols = opt.getHelpColumns();
    EXPECT_EQ(cols.left, "-f");
    EXPECT_EQ(cols.right, "A flag option");
}

// Test getHelpColumns with a single long option name and no hint
TEST_F(OptTest_662, GetHelpColumns_SingleLongOption_NoHint_662) {
    bool flag = false;
    auto opt = Opt(flag)["--flag"]("A flag option");
    
    auto cols = opt.getHelpColumns();
    EXPECT_EQ(cols.left, "--flag");
    EXPECT_EQ(cols.right, "A flag option");
}

// Test getHelpColumns with both short and long option names
TEST_F(OptTest_662, GetHelpColumns_ShortAndLongOption_NoHint_662) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]("A flag option");
    
    auto cols = opt.getHelpColumns();
    EXPECT_EQ(cols.left, "-f, --flag");
    EXPECT_EQ(cols.right, "A flag option");
}

// Test getHelpColumns with a hint (value option, not flag)
TEST_F(OptTest_662, GetHelpColumns_WithHint_662) {
    std::string value;
    auto opt = Opt(value, "filename")["-o"]["--output"]("Output filename");
    
    auto cols = opt.getHelpColumns();
    EXPECT_EQ(cols.left, "-o, --output <filename>");
    EXPECT_EQ(cols.right, "Output filename");
}

// Test getHelpColumns with single option and hint
TEST_F(OptTest_662, GetHelpColumns_SingleOptionWithHint_662) {
    int count = 0;
    auto opt = Opt(count, "count")["-n"]("Number of items");
    
    auto cols = opt.getHelpColumns();
    EXPECT_EQ(cols.left, "-n <count>");
    EXPECT_EQ(cols.right, "Number of items");
}

// Test getHelpColumns with empty description
TEST_F(OptTest_662, GetHelpColumns_EmptyDescription_662) {
    bool flag = false;
    auto opt = Opt(flag)["-v"]("");
    
    auto cols = opt.getHelpColumns();
    EXPECT_EQ(cols.left, "-v");
    EXPECT_EQ(cols.right, "");
}

// Test getHelpColumns with multiple option names (more than two)
TEST_F(OptTest_662, GetHelpColumns_MultipleOptionNames_662) {
    bool flag = false;
    auto opt = Opt(flag)["-v"]["--verbose"]["--verb"]("Verbose output");
    
    auto cols = opt.getHelpColumns();
    EXPECT_EQ(cols.left, "-v, --verbose, --verb");
    EXPECT_EQ(cols.right, "Verbose output");
}

// Test getHelpColumns with hint but no option names (edge case)
TEST_F(OptTest_662, GetHelpColumns_WithHintNoNames_662) {
    std::string value;
    auto opt = Opt(value, "value")("Some value");
    
    auto cols = opt.getHelpColumns();
    // No option names, so just the hint
    EXPECT_EQ(cols.left, " <value>");
    EXPECT_EQ(cols.right, "Some value");
}

// Test isMatch with matching short option
TEST_F(OptTest_662, IsMatch_ShortOption_Matches_662) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]("A flag");
    
    EXPECT_TRUE(opt.isMatch("-f"));
}

// Test isMatch with matching long option
TEST_F(OptTest_662, IsMatch_LongOption_Matches_662) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]("A flag");
    
    EXPECT_TRUE(opt.isMatch("--flag"));
}

// Test isMatch with non-matching option
TEST_F(OptTest_662, IsMatch_NonMatchingOption_662) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]("A flag");
    
    EXPECT_FALSE(opt.isMatch("-g"));
    EXPECT_FALSE(opt.isMatch("--other"));
}

// Test that Opt created with bool ref works as flag
TEST_F(OptTest_662, BoolRefConstruction_662) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]("A boolean flag");
    
    auto cols = opt.getHelpColumns();
    EXPECT_EQ(cols.left, "-f, --flag");
    EXPECT_EQ(cols.right, "A boolean flag");
}

// Test validate on a well-formed option
TEST_F(OptTest_662, Validate_WellFormedOption_662) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]("A flag");
    
    auto result = opt.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test optional and required
TEST_F(OptTest_662, OptionalByDefault_662) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]("A flag");
    
    EXPECT_TRUE(opt.isOptional());
}

TEST_F(OptTest_662, RequiredOption_662) {
    std::string value;
    auto opt = Opt(value, "val")["-v"]("A value").required();
    
    EXPECT_FALSE(opt.isOptional());
}

// Test hint
TEST_F(OptTest_662, HintReturnsCorrectValue_662) {
    std::string value;
    auto opt = Opt(value, "myHint")["-v"]("A value");
    
    EXPECT_EQ(opt.hint(), "myHint");
}

// Test with lambda accepting string
TEST_F(OptTest_662, LambdaConstructionWithHint_662) {
    std::string captured;
    auto opt = Opt([&captured](std::string const& s) { captured = s; }, "name")["-n"]["--name"]("Set name");
    
    auto cols = opt.getHelpColumns();
    EXPECT_EQ(cols.left, "-n, --name <name>");
    EXPECT_EQ(cols.right, "Set name");
}

// Test getHelpColumns with flag (no hint expected in output)
TEST_F(OptTest_662, GetHelpColumns_FlagNoHintInOutput_662) {
    bool flag = false;
    auto opt = Opt(flag)["-q"]["--quiet"]("Quiet mode");
    
    auto cols = opt.getHelpColumns();
    // Flag options should not have a hint appended
    EXPECT_EQ(cols.left, "-q, --quiet");
    EXPECT_EQ(cols.right, "Quiet mode");
}

// Test that operator[] chains correctly
TEST_F(OptTest_662, OperatorBracketChaining_662) {
    bool flag = false;
    auto opt = Opt(flag)["-a"]["-b"]["-c"]("Multiple short names");
    
    auto cols = opt.getHelpColumns();
    EXPECT_EQ(cols.left, "-a, -b, -c");
}

// Test getHelpColumns consistency - calling twice yields same result
TEST_F(OptTest_662, GetHelpColumns_Consistency_662) {
    std::string value;
    auto opt = Opt(value, "path")["-p"]["--path"]("File path");
    
    auto cols1 = opt.getHelpColumns();
    auto cols2 = opt.getHelpColumns();
    
    EXPECT_EQ(cols1.left, cols2.left);
    EXPECT_EQ(cols1.right, cols2.right);
}
