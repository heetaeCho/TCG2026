#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterUnsignedLongTest_53 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Basic unsigned long value emission
TEST_F(EmitterUnsignedLongTest_53, EmitZero_53) {
    YAML::Emitter emitter;
    emitter << 0UL;
    EXPECT_TRUE(emitter.good());
    EXPECT_STREQ("0", emitter.c_str());
}

TEST_F(EmitterUnsignedLongTest_53, EmitSmallValue_53) {
    YAML::Emitter emitter;
    emitter << 42UL;
    EXPECT_TRUE(emitter.good());
    EXPECT_STREQ("42", emitter.c_str());
}

TEST_F(EmitterUnsignedLongTest_53, EmitOne_53) {
    YAML::Emitter emitter;
    emitter << 1UL;
    EXPECT_TRUE(emitter.good());
    EXPECT_STREQ("1", emitter.c_str());
}

TEST_F(EmitterUnsignedLongTest_53, EmitLargeValue_53) {
    YAML::Emitter emitter;
    unsigned long val = 4294967295UL;  // 2^32 - 1
    emitter << val;
    EXPECT_TRUE(emitter.good());
    EXPECT_STREQ("4294967295", emitter.c_str());
}

TEST_F(EmitterUnsignedLongTest_53, EmitMaxUnsignedLong_53) {
    YAML::Emitter emitter;
    unsigned long val = std::numeric_limits<unsigned long>::max();
    emitter << val;
    EXPECT_TRUE(emitter.good());
    std::string expected = std::to_string(val);
    EXPECT_EQ(expected, std::string(emitter.c_str()));
}

// Test: Emission to an ostream
TEST_F(EmitterUnsignedLongTest_53, EmitToStream_53) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << 12345UL;
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ("12345", ss.str());
}

// Test: Emitter good state after emission
TEST_F(EmitterUnsignedLongTest_53, GoodStateAfterEmission_53) {
    YAML::Emitter emitter;
    emitter << 100UL;
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ("", emitter.GetLastError());
}

// Test: Size is non-zero after emission
TEST_F(EmitterUnsignedLongTest_53, SizeNonZeroAfterEmission_53) {
    YAML::Emitter emitter;
    emitter << 999UL;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test: Unsigned long in a sequence
TEST_F(EmitterUnsignedLongTest_53, UnsignedLongInSequence_53) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << 10UL;
    emitter << 20UL;
    emitter << 30UL;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("10"), std::string::npos);
    EXPECT_NE(output.find("20"), std::string::npos);
    EXPECT_NE(output.find("30"), std::string::npos);
}

// Test: Unsigned long in a flow sequence
TEST_F(EmitterUnsignedLongTest_53, UnsignedLongInFlowSequence_53) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq;
    emitter << 1UL << 2UL << 3UL;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
}

// Test: Unsigned long as a map value
TEST_F(EmitterUnsignedLongTest_53, UnsignedLongAsMapValue_53) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "count" << YAML::Value << 500UL;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("count"), std::string::npos);
    EXPECT_NE(output.find("500"), std::string::npos);
}

// Test: Unsigned long as a map key
TEST_F(EmitterUnsignedLongTest_53, UnsignedLongAsMapKey_53) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << 42UL << YAML::Value << "answer";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("42"), std::string::npos);
    EXPECT_NE(output.find("answer"), std::string::npos);
}

// Test: Hex base for unsigned long
TEST_F(EmitterUnsignedLongTest_53, UnsignedLongHexBase_53) {
    YAML::Emitter emitter;
    emitter << YAML::Hex;
    emitter << 255UL;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // Hex representation of 255 should contain "0xff" or "0xFF"
    // Convert to lowercase for comparison
    std::string lower_output = output;
    std::transform(lower_output.begin(), lower_output.end(), lower_output.begin(), ::tolower);
    EXPECT_NE(lower_output.find("0xff"), std::string::npos);
}

// Test: Oct base for unsigned long
TEST_F(EmitterUnsignedLongTest_53, UnsignedLongOctBase_53) {
    YAML::Emitter emitter;
    emitter << YAML::Oct;
    emitter << 8UL;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // Octal representation of 8 should be 010
    EXPECT_NE(output.find("010"), std::string::npos);
}

// Test: Multiple unsigned longs emitted sequentially
TEST_F(EmitterUnsignedLongTest_53, MultipleUnsignedLongsInBlockSeq_53) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    for (unsigned long i = 0; i < 5; ++i) {
        emitter << i;
    }
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0"), std::string::npos);
    EXPECT_NE(output.find("4"), std::string::npos);
}

// Test: c_str returns correct string after emission
TEST_F(EmitterUnsignedLongTest_53, CStrMatchesExpected_53) {
    YAML::Emitter emitter;
    emitter << 123456789UL;
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ(std::string("123456789"), std::string(emitter.c_str()));
}

// Test: size matches the string length
TEST_F(EmitterUnsignedLongTest_53, SizeMatchesStringLength_53) {
    YAML::Emitter emitter;
    emitter << 9876UL;
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ(emitter.size(), std::string(emitter.c_str()).size());
}

// Test: Emitter initially good with no output
TEST_F(EmitterUnsignedLongTest_53, InitiallyGood_53) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ(0u, emitter.size());
}

// Test: Unsigned long with anchor
TEST_F(EmitterUnsignedLongTest_53, UnsignedLongWithAnchor_53) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("myanchor") << 77UL;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("myanchor"), std::string::npos);
    EXPECT_NE(output.find("77"), std::string::npos);
}

// Test: Unsigned long with tag
TEST_F(EmitterUnsignedLongTest_53, UnsignedLongWithTag_53) {
    YAML::Emitter emitter;
    emitter << YAML::LocalTag("mytag") << 88UL;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("mytag"), std::string::npos);
    EXPECT_NE(output.find("88"), std::string::npos);
}

// Test: Unsigned long after document begin
TEST_F(EmitterUnsignedLongTest_53, UnsignedLongWithBeginDoc_53) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc;
    emitter << 55UL;
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("55"), std::string::npos);
}

// Test: Streaming to ostream and verifying content
TEST_F(EmitterUnsignedLongTest_53, StreamOutputMatchesCStr_53) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << 2023UL;
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ(ss.str(), std::string(emitter.c_str()));
}

// Test: Unsigned long in nested structure
TEST_F(EmitterUnsignedLongTest_53, UnsignedLongNestedMapSeq_53) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "values" << YAML::Value;
    emitter << YAML::BeginSeq;
    emitter << 100UL << 200UL << 300UL;
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("values"), std::string::npos);
    EXPECT_NE(output.find("100"), std::string::npos);
    EXPECT_NE(output.find("200"), std::string::npos);
    EXPECT_NE(output.find("300"), std::string::npos);
}

// Test: Emitting unsigned long with comment
TEST_F(EmitterUnsignedLongTest_53, UnsignedLongWithComment_53) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("This is a number");
    emitter << 64UL;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("This is a number"), std::string::npos);
    EXPECT_NE(output.find("64"), std::string::npos);
}
