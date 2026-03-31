#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

// Test fixture
class EmitterUnsignedIntTest_49 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Basic unsigned int emission
TEST_F(EmitterUnsignedIntTest_49, EmitUnsignedIntZero_49) {
    YAML::Emitter emitter;
    emitter << 0u;
    EXPECT_TRUE(emitter.good());
    std::string result = emitter.c_str();
    EXPECT_EQ(result, "0");
}

TEST_F(EmitterUnsignedIntTest_49, EmitUnsignedIntPositive_49) {
    YAML::Emitter emitter;
    emitter << 42u;
    EXPECT_TRUE(emitter.good());
    std::string result = emitter.c_str();
    EXPECT_EQ(result, "42");
}

TEST_F(EmitterUnsignedIntTest_49, EmitUnsignedIntMax_49) {
    YAML::Emitter emitter;
    unsigned int maxVal = std::numeric_limits<unsigned int>::max();
    emitter << maxVal;
    EXPECT_TRUE(emitter.good());
    std::string result = emitter.c_str();
    EXPECT_EQ(result, std::to_string(maxVal));
}

TEST_F(EmitterUnsignedIntTest_49, EmitUnsignedIntOne_49) {
    YAML::Emitter emitter;
    emitter << 1u;
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ(std::string(emitter.c_str()), "1");
}

// Test: Emit unsigned int to stream
TEST_F(EmitterUnsignedIntTest_49, EmitUnsignedIntToStream_49) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << 123u;
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ(ss.str(), "123");
}

// Test: Emit unsigned int in a sequence
TEST_F(EmitterUnsignedIntTest_49, EmitUnsignedIntInSequence_49) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << 10u;
    emitter << 20u;
    emitter << 30u;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string result = emitter.c_str();
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("20"), std::string::npos);
    EXPECT_NE(result.find("30"), std::string::npos);
}

// Test: Emit unsigned int in a map as value
TEST_F(EmitterUnsignedIntTest_49, EmitUnsignedIntInMapAsValue_49) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "count";
    emitter << YAML::Value << 100u;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string result = emitter.c_str();
    EXPECT_NE(result.find("count"), std::string::npos);
    EXPECT_NE(result.find("100"), std::string::npos);
}

// Test: Emit unsigned int in flow sequence
TEST_F(EmitterUnsignedIntTest_49, EmitUnsignedIntInFlowSequence_49) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << 1u << 2u << 3u;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string result = emitter.c_str();
    EXPECT_NE(result.find("["), std::string::npos);
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("3"), std::string::npos);
}

// Test: Emit unsigned int with hex base
TEST_F(EmitterUnsignedIntTest_49, EmitUnsignedIntHex_49) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Hex);
    emitter << 255u;
    EXPECT_TRUE(emitter.good());
    std::string result = emitter.c_str();
    EXPECT_NE(result.find("0x"), std::string::npos);
}

// Test: Emit unsigned int with oct base
TEST_F(EmitterUnsignedIntTest_49, EmitUnsignedIntOct_49) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Oct);
    emitter << 8u;
    EXPECT_TRUE(emitter.good());
    std::string result = emitter.c_str();
    EXPECT_NE(result.find("0"), std::string::npos);
}

// Test: Size is non-zero after emitting unsigned int
TEST_F(EmitterUnsignedIntTest_49, SizeNonZeroAfterEmit_49) {
    YAML::Emitter emitter;
    emitter << 42u;
    EXPECT_GT(emitter.size(), 0u);
}

// Test: Good state initially
TEST_F(EmitterUnsignedIntTest_49, GoodStateInitially_49) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
}

// Test: Emitter returns reference for chaining
TEST_F(EmitterUnsignedIntTest_49, ChainingUnsignedInt_49) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    unsigned int a = 5u, b = 10u;
    emitter << a << b;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string result = emitter.c_str();
    EXPECT_NE(result.find("5"), std::string::npos);
    EXPECT_NE(result.find("10"), std::string::npos);
}

// Test: Multiple unsigned ints as map keys and values
TEST_F(EmitterUnsignedIntTest_49, EmitUnsignedIntAsMapKey_49) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << 1u;
    emitter << YAML::Value << 100u;
    emitter << YAML::Key << 2u;
    emitter << YAML::Value << 200u;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string result = emitter.c_str();
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("100"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("200"), std::string::npos);
}

// Test: Large unsigned int value
TEST_F(EmitterUnsignedIntTest_49, EmitLargeUnsignedInt_49) {
    YAML::Emitter emitter;
    unsigned int val = 4000000000u;
    emitter << val;
    EXPECT_TRUE(emitter.good());
    std::string result = emitter.c_str();
    EXPECT_EQ(result, "4000000000");
}

// Test: Emit unsigned int after setting dec base (default)
TEST_F(EmitterUnsignedIntTest_49, EmitUnsignedIntDec_49) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Dec);
    emitter << 255u;
    EXPECT_TRUE(emitter.good());
    std::string result = emitter.c_str();
    EXPECT_EQ(result, "255");
}

// Test: c_str returns non-null after unsigned int emission
TEST_F(EmitterUnsignedIntTest_49, CStrNonNullAfterEmit_49) {
    YAML::Emitter emitter;
    emitter << 7u;
    EXPECT_NE(emitter.c_str(), nullptr);
}

// Test: Mixing unsigned int with string values
TEST_F(EmitterUnsignedIntTest_49, MixUnsignedIntWithStrings_49) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name";
    emitter << YAML::Value << "test";
    emitter << YAML::Key << "value";
    emitter << YAML::Value << 999u;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string result = emitter.c_str();
    EXPECT_NE(result.find("name"), std::string::npos);
    EXPECT_NE(result.find("test"), std::string::npos);
    EXPECT_NE(result.find("999"), std::string::npos);
}

// Test: Emit unsigned int with tag
TEST_F(EmitterUnsignedIntTest_49, EmitUnsignedIntWithTag_49) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("tag:yaml.org,2002:int") << 50u;
    EXPECT_TRUE(emitter.good());
    std::string result = emitter.c_str();
    EXPECT_NE(result.find("50"), std::string::npos);
}

// Test: Emit unsigned int with anchor
TEST_F(EmitterUnsignedIntTest_49, EmitUnsignedIntWithAnchor_49) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("myanchor") << 77u;
    EXPECT_TRUE(emitter.good());
    std::string result = emitter.c_str();
    EXPECT_NE(result.find("77"), std::string::npos);
    EXPECT_NE(result.find("myanchor"), std::string::npos);
}

// Test: Local hex setting for unsigned int
TEST_F(EmitterUnsignedIntTest_49, EmitUnsignedIntLocalHex_49) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Hex << 16u;
    emitter << 16u;  // Should revert to decimal
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string result = emitter.c_str();
    EXPECT_NE(result.find("0x10"), std::string::npos);
}
