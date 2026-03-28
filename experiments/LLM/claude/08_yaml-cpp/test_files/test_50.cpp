#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

// Test fixture
class EmitterShortOperatorTest_50 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation: emit a positive short value
TEST_F(EmitterShortOperatorTest_50, EmitPositiveShort_50) {
    YAML::Emitter emitter;
    emitter << static_cast<short>(42);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_EQ(output, "42");
}

// Normal operation: emit zero
TEST_F(EmitterShortOperatorTest_50, EmitZeroShort_50) {
    YAML::Emitter emitter;
    emitter << static_cast<short>(0);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_EQ(output, "0");
}

// Normal operation: emit a negative short value
TEST_F(EmitterShortOperatorTest_50, EmitNegativeShort_50) {
    YAML::Emitter emitter;
    emitter << static_cast<short>(-100);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_EQ(output, "-100");
}

// Boundary: emit SHORT_MAX
TEST_F(EmitterShortOperatorTest_50, EmitShortMax_50) {
    YAML::Emitter emitter;
    short maxVal = std::numeric_limits<short>::max(); // 32767
    emitter << maxVal;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_EQ(output, std::to_string(maxVal));
}

// Boundary: emit SHORT_MIN
TEST_F(EmitterShortOperatorTest_50, EmitShortMin_50) {
    YAML::Emitter emitter;
    short minVal = std::numeric_limits<short>::min(); // -32768
    emitter << minVal;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_EQ(output, std::to_string(minVal));
}

// Normal operation: emit short value to a stream
TEST_F(EmitterShortOperatorTest_50, EmitShortToStream_50) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << static_cast<short>(123);
    EXPECT_TRUE(emitter.good());
    EXPECT_NE(ss.str().find("123"), std::string::npos);
}

// Normal operation: emit short as part of a sequence
TEST_F(EmitterShortOperatorTest_50, EmitShortInSequence_50) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << static_cast<short>(1);
    emitter << static_cast<short>(2);
    emitter << static_cast<short>(3);
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
}

// Normal operation: emit short as map value
TEST_F(EmitterShortOperatorTest_50, EmitShortAsMapValue_50) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "value";
    emitter << YAML::Value << static_cast<short>(42);
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("value"), std::string::npos);
    EXPECT_NE(output.find("42"), std::string::npos);
}

// Normal operation: emit short with hex base
TEST_F(EmitterShortOperatorTest_50, EmitShortHexBase_50) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Hex);
    emitter << static_cast<short>(255);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // Hex output should contain 0x prefix
    EXPECT_NE(output.find("0x"), std::string::npos);
}

// Normal operation: emit short with oct base
TEST_F(EmitterShortOperatorTest_50, EmitShortOctBase_50) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Oct);
    emitter << static_cast<short>(8);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // Octal output should contain 0 prefix
    EXPECT_NE(output.find("0"), std::string::npos);
}

// Verify emitter remains good after multiple short emissions
TEST_F(EmitterShortOperatorTest_50, EmitMultipleShortsGood_50) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    for (short i = -10; i <= 10; ++i) {
        emitter << i;
    }
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// Verify size is non-zero after emitting a short
TEST_F(EmitterShortOperatorTest_50, EmitShortSizeNonZero_50) {
    YAML::Emitter emitter;
    emitter << static_cast<short>(7);
    EXPECT_GT(emitter.size(), static_cast<std::size_t>(0));
}

// Verify c_str is not null after emitting a short
TEST_F(EmitterShortOperatorTest_50, EmitShortCStrNotNull_50) {
    YAML::Emitter emitter;
    emitter << static_cast<short>(99);
    EXPECT_NE(emitter.c_str(), nullptr);
}

// Normal operation: emit short value of 1
TEST_F(EmitterShortOperatorTest_50, EmitShortOne_50) {
    YAML::Emitter emitter;
    emitter << static_cast<short>(1);
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ(std::string(emitter.c_str()), "1");
}

// Normal operation: emit short value of -1
TEST_F(EmitterShortOperatorTest_50, EmitShortNegativeOne_50) {
    YAML::Emitter emitter;
    emitter << static_cast<short>(-1);
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ(std::string(emitter.c_str()), "-1");
}

// Verify chaining returns reference to emitter (flow sequence)
TEST_F(EmitterShortOperatorTest_50, EmitShortChaining_50) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq;
    YAML::Emitter& ref = (emitter << static_cast<short>(10));
    EXPECT_EQ(&ref, &emitter);
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// Emit short in a flow sequence to verify formatting
TEST_F(EmitterShortOperatorTest_50, EmitShortInFlowSequence_50) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq;
    emitter << static_cast<short>(10);
    emitter << static_cast<short>(20);
    emitter << static_cast<short>(30);
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
    EXPECT_NE(output.find("10"), std::string::npos);
    EXPECT_NE(output.find("20"), std::string::npos);
    EXPECT_NE(output.find("30"), std::string::npos);
}

// Initial state of emitter should be good
TEST_F(EmitterShortOperatorTest_50, InitialStateGood_50) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ(emitter.size(), static_cast<std::size_t>(0));
}

// Emit short as map key
TEST_F(EmitterShortOperatorTest_50, EmitShortAsMapKey_50) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << static_cast<short>(42);
    emitter << YAML::Value << "answer";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("42"), std::string::npos);
    EXPECT_NE(output.find("answer"), std::string::npos);
}
