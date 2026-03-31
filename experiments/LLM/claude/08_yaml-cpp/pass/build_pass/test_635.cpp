#include <gtest/gtest.h>
#include <sstream>
#include "yaml-cpp/ostream_wrapper.h"

// We need to declare the function we're testing
namespace YAML {
namespace Utils {
bool WriteAnchor(ostream_wrapper& out, const char* str, std::size_t size);
bool WriteAliasName(ostream_wrapper& out, const char* str, std::size_t size);
}
}

class WriteAnchorTest_635 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that WriteAnchor writes the '&' prefix followed by the alias name for a simple string
TEST_F(WriteAnchorTest_635, SimpleAnchorName_635) {
    YAML::ostream_wrapper out;
    const char* name = "anchor1";
    bool result = YAML::Utils::WriteAnchor(out, name, 7);
    
    std::string output(out.str());
    // Should start with '&'
    ASSERT_FALSE(output.empty());
    EXPECT_EQ(output[0], '&');
    // The rest should contain the anchor name
    EXPECT_NE(output.find("anchor1"), std::string::npos);
}

// Test that WriteAnchor returns true for a valid anchor name
TEST_F(WriteAnchorTest_635, ReturnsTrueForValidName_635) {
    YAML::ostream_wrapper out;
    const char* name = "valid";
    bool result = YAML::Utils::WriteAnchor(out, name, 5);
    EXPECT_TRUE(result);
}

// Test WriteAnchor with a single character name
TEST_F(WriteAnchorTest_635, SingleCharacterName_635) {
    YAML::ostream_wrapper out;
    const char* name = "a";
    bool result = YAML::Utils::WriteAnchor(out, name, 1);
    
    std::string output(out.str());
    EXPECT_EQ(output[0], '&');
    EXPECT_NE(output.find("a"), std::string::npos);
}

// Test WriteAnchor with an empty string
TEST_F(WriteAnchorTest_635, EmptyName_635) {
    YAML::ostream_wrapper out;
    const char* name = "";
    bool result = YAML::Utils::WriteAnchor(out, name, 0);
    
    std::string output(out.str());
    // At minimum, '&' should be written
    EXPECT_GE(output.size(), 1u);
    EXPECT_EQ(output[0], '&');
}

// Test WriteAnchor with a longer anchor name
TEST_F(WriteAnchorTest_635, LongAnchorName_635) {
    YAML::ostream_wrapper out;
    std::string longName(100, 'x');
    bool result = YAML::Utils::WriteAnchor(out, longName.c_str(), longName.size());
    
    std::string output(out.str());
    EXPECT_EQ(output[0], '&');
}

// Test WriteAnchor with alphanumeric name
TEST_F(WriteAnchorTest_635, AlphanumericName_635) {
    YAML::ostream_wrapper out;
    const char* name = "anchor123";
    bool result = YAML::Utils::WriteAnchor(out, name, 9);
    
    std::string output(out.str());
    EXPECT_EQ(output[0], '&');
    EXPECT_NE(output.find("anchor123"), std::string::npos);
}

// Test WriteAnchor writes to stream-backed ostream_wrapper
TEST_F(WriteAnchorTest_635, WritesToStream_635) {
    std::stringstream ss;
    YAML::ostream_wrapper out(ss);
    const char* name = "streamanchor";
    bool result = YAML::Utils::WriteAnchor(out, name, 12);
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output[0], '&');
    EXPECT_NE(output.find("streamanchor"), std::string::npos);
}

// Test WriteAnchor with name containing hyphens (common in YAML anchors)
TEST_F(WriteAnchorTest_635, NameWithHyphens_635) {
    YAML::ostream_wrapper out;
    const char* name = "my-anchor";
    bool result = YAML::Utils::WriteAnchor(out, name, 9);
    
    std::string output(out.str());
    EXPECT_EQ(output[0], '&');
}

// Test WriteAnchor with name containing underscores
TEST_F(WriteAnchorTest_635, NameWithUnderscores_635) {
    YAML::ostream_wrapper out;
    const char* name = "my_anchor";
    bool result = YAML::Utils::WriteAnchor(out, name, 9);
    
    std::string output(out.str());
    EXPECT_EQ(output[0], '&');
    EXPECT_NE(output.find("my_anchor"), std::string::npos);
}

// Test that pos advances after WriteAnchor
TEST_F(WriteAnchorTest_635, PosAdvancesAfterWrite_635) {
    YAML::ostream_wrapper out;
    std::size_t initialPos = out.pos();
    const char* name = "test";
    YAML::Utils::WriteAnchor(out, name, 4);
    
    // Position should have advanced by at least 1 (for '&') + some amount for the name
    EXPECT_GT(out.pos(), initialPos);
}

// Test WriteAnchor with partial size (less than actual string length)
TEST_F(WriteAnchorTest_635, PartialSize_635) {
    YAML::ostream_wrapper out;
    const char* name = "longanchorname";
    bool result = YAML::Utils::WriteAnchor(out, name, 4);
    
    std::string output(out.str());
    EXPECT_EQ(output[0], '&');
}

// Test that col advances after WriteAnchor
TEST_F(WriteAnchorTest_635, ColAdvancesAfterWrite_635) {
    YAML::ostream_wrapper out;
    std::size_t initialCol = out.col();
    const char* name = "abc";
    YAML::Utils::WriteAnchor(out, name, 3);
    
    EXPECT_GT(out.col(), initialCol);
}

// Test WriteAnchor with name containing dots
TEST_F(WriteAnchorTest_635, NameWithDots_635) {
    YAML::ostream_wrapper out;
    const char* name = "anchor.name";
    bool result = YAML::Utils::WriteAnchor(out, name, 11);
    
    std::string output(out.str());
    EXPECT_EQ(output[0], '&');
}
