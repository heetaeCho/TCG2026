#include <gtest/gtest.h>
#include <sstream>
#include "yaml-cpp/ostream_wrapper.h"

// We need to declare the function we're testing
namespace YAML {
namespace Utils {
bool WriteAlias(ostream_wrapper& out, const char* str, std::size_t size);
bool WriteAliasName(ostream_wrapper& out, const char* str, std::size_t size);
}
}

class WriteAliasTest_634 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that WriteAlias writes the '*' prefix followed by the alias name
TEST_F(WriteAliasTest_634, BasicAlias_634) {
    YAML::ostream_wrapper out;
    const char* alias = "anchor";
    bool result = YAML::Utils::WriteAlias(out, alias, std::strlen(alias));
    
    // The output should start with '*'
    std::string output(out.str());
    EXPECT_EQ(output[0], '*');
    
    // Check that the alias name follows
    EXPECT_NE(output.find("anchor"), std::string::npos);
}

// Test that WriteAlias returns a boolean value for a simple alias
TEST_F(WriteAliasTest_634, ReturnsTrueForValidAlias_634) {
    YAML::ostream_wrapper out;
    const char* alias = "myalias";
    bool result = YAML::Utils::WriteAlias(out, alias, std::strlen(alias));
    EXPECT_TRUE(result);
}

// Test with a single character alias name
TEST_F(WriteAliasTest_634, SingleCharAlias_634) {
    YAML::ostream_wrapper out;
    const char* alias = "a";
    bool result = YAML::Utils::WriteAlias(out, alias, 1);
    
    std::string output(out.str());
    EXPECT_EQ(output[0], '*');
    EXPECT_NE(output.find("a"), std::string::npos);
}

// Test with an empty alias name (size = 0)
TEST_F(WriteAliasTest_634, EmptyAlias_634) {
    YAML::ostream_wrapper out;
    const char* alias = "";
    bool result = YAML::Utils::WriteAlias(out, alias, 0);
    
    // The '*' should still be written
    std::string output(out.str());
    EXPECT_GE(output.size(), 1u);
    EXPECT_EQ(output[0], '*');
}

// Test with a numeric alias name
TEST_F(WriteAliasTest_634, NumericAlias_634) {
    YAML::ostream_wrapper out;
    const char* alias = "123";
    bool result = YAML::Utils::WriteAlias(out, alias, std::strlen(alias));
    
    std::string output(out.str());
    EXPECT_EQ(output[0], '*');
}

// Test that WriteAlias works with stream-based ostream_wrapper
TEST_F(WriteAliasTest_634, StreamBasedOutput_634) {
    std::stringstream ss;
    YAML::ostream_wrapper out(ss);
    const char* alias = "streamalias";
    bool result = YAML::Utils::WriteAlias(out, alias, std::strlen(alias));
    
    std::string output = ss.str();
    EXPECT_EQ(output[0], '*');
    EXPECT_NE(output.find("streamalias"), std::string::npos);
}

// Test with alphanumeric alias
TEST_F(WriteAliasTest_634, AlphanumericAlias_634) {
    YAML::ostream_wrapper out;
    const char* alias = "anchor123";
    bool result = YAML::Utils::WriteAlias(out, alias, std::strlen(alias));
    
    std::string output(out.str());
    EXPECT_EQ(output[0], '*');
    EXPECT_NE(output.find("anchor123"), std::string::npos);
}

// Test that position advances after writing
TEST_F(WriteAliasTest_634, PositionAdvances_634) {
    YAML::ostream_wrapper out;
    std::size_t initial_pos = out.pos();
    const char* alias = "test";
    YAML::Utils::WriteAlias(out, alias, std::strlen(alias));
    
    // Position should have advanced (at least by 1 for '*' plus the alias name)
    EXPECT_GT(out.pos(), initial_pos);
}

// Test with alias containing underscores
TEST_F(WriteAliasTest_634, AliasWithUnderscore_634) {
    YAML::ostream_wrapper out;
    const char* alias = "my_anchor";
    bool result = YAML::Utils::WriteAlias(out, alias, std::strlen(alias));
    
    std::string output(out.str());
    EXPECT_EQ(output[0], '*');
}

// Test with alias containing hyphens
TEST_F(WriteAliasTest_634, AliasWithHyphen_634) {
    YAML::ostream_wrapper out;
    const char* alias = "my-anchor";
    bool result = YAML::Utils::WriteAlias(out, alias, std::strlen(alias));
    
    std::string output(out.str());
    EXPECT_EQ(output[0], '*');
}

// Test column advancement
TEST_F(WriteAliasTest_634, ColumnAdvances_634) {
    YAML::ostream_wrapper out;
    std::size_t initial_col = out.col();
    const char* alias = "test";
    YAML::Utils::WriteAlias(out, alias, std::strlen(alias));
    
    // Column should advance after writing
    EXPECT_GT(out.col(), initial_col);
}

// Test partial size (size less than actual string length)
TEST_F(WriteAliasTest_634, PartialSize_634) {
    YAML::ostream_wrapper out;
    const char* alias = "longalias";
    // Only pass part of the string
    bool result = YAML::Utils::WriteAlias(out, alias, 4);
    
    std::string output(out.str());
    EXPECT_EQ(output[0], '*');
}

// Test with a longer alias name
TEST_F(WriteAliasTest_634, LongAlias_634) {
    YAML::ostream_wrapper out;
    std::string long_alias(100, 'x');
    bool result = YAML::Utils::WriteAlias(out, long_alias.c_str(), long_alias.size());
    
    std::string output(out.str());
    EXPECT_EQ(output[0], '*');
}
