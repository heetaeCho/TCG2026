#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

// Test fixture
class EmitterLongTest_52 : public ::testing::Test {
protected:
    YAML::Emitter emitter;
};

// Test: operator<< with long value emits correct decimal string
TEST_F(EmitterLongTest_52, EmitPositiveLong_52) {
    emitter << static_cast<long>(42);
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string result = emitter.c_str();
    EXPECT_EQ(result, "42");
}

// Test: operator<< with negative long value
TEST_F(EmitterLongTest_52, EmitNegativeLong_52) {
    emitter << static_cast<long>(-100);
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string result = emitter.c_str();
    EXPECT_EQ(result, "-100");
}

// Test: operator<< with zero
TEST_F(EmitterLongTest_52, EmitZeroLong_52) {
    emitter << static_cast<long>(0);
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string result = emitter.c_str();
    EXPECT_EQ(result, "0");
}

// Test: operator<< with LONG_MAX boundary
TEST_F(EmitterLongTest_52, EmitLongMax_52) {
    long maxVal = std::numeric_limits<long>::max();
    emitter << maxVal;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string result = emitter.c_str();
    EXPECT_EQ(result, std::to_string(maxVal));
}

// Test: operator<< with LONG_MIN boundary
TEST_F(EmitterLongTest_52, EmitLongMin_52) {
    long minVal = std::numeric_limits<long>::min();
    emitter << minVal;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string result = emitter.c_str();
    EXPECT_EQ(result, std::to_string(minVal));
}

// Test: operator<< with long value 1
TEST_F(EmitterLongTest_52, EmitLongOne_52) {
    emitter << static_cast<long>(1);
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    EXPECT_STREQ(emitter.c_str(), "1");
}

// Test: operator<< with long value -1
TEST_F(EmitterLongTest_52, EmitLongNegativeOne_52) {
    emitter << static_cast<long>(-1);
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    EXPECT_STREQ(emitter.c_str(), "-1");
}

// Test: Emitter outputs long to a stream
TEST_F(EmitterLongTest_52, EmitLongToStream_52) {
    std::stringstream ss;
    YAML::Emitter streamEmitter(ss);
    streamEmitter << static_cast<long>(12345);
    ASSERT_TRUE(streamEmitter.good()) << streamEmitter.GetLastError();
    EXPECT_NE(ss.str().find("12345"), std::string::npos);
}

// Test: Long value in a sequence
TEST_F(EmitterLongTest_52, EmitLongInSequence_52) {
    emitter << YAML::BeginSeq;
    emitter << static_cast<long>(10);
    emitter << static_cast<long>(20);
    emitter << static_cast<long>(30);
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string result = emitter.c_str();
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("20"), std::string::npos);
    EXPECT_NE(result.find("30"), std::string::npos);
}

// Test: Long value as map value
TEST_F(EmitterLongTest_52, EmitLongInMap_52) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "count";
    emitter << YAML::Value << static_cast<long>(999);
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string result = emitter.c_str();
    EXPECT_NE(result.find("count"), std::string::npos);
    EXPECT_NE(result.find("999"), std::string::npos);
}

// Test: Long value with hex base
TEST_F(EmitterLongTest_52, EmitLongHex_52) {
    emitter.SetIntBase(YAML::Hex);
    emitter << static_cast<long>(255);
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string result = emitter.c_str();
    EXPECT_NE(result.find("0xff"), std::string::npos);
}

// Test: Long value with oct base
TEST_F(EmitterLongTest_52, EmitLongOct_52) {
    emitter.SetIntBase(YAML::Oct);
    emitter << static_cast<long>(8);
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string result = emitter.c_str();
    EXPECT_NE(result.find("010"), std::string::npos);
}

// Test: size() is non-zero after emitting a long
TEST_F(EmitterLongTest_52, SizeNonZeroAfterEmit_52) {
    emitter << static_cast<long>(42);
    ASSERT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test: Good state initially
TEST_F(EmitterLongTest_52, InitialGoodState_52) {
    EXPECT_TRUE(emitter.good());
}

// Test: Chaining operator<< with long
TEST_F(EmitterLongTest_52, ChainingLongInFlowSeq_52) {
    emitter << YAML::Flow << YAML::BeginSeq;
    emitter << static_cast<long>(1) << static_cast<long>(2) << static_cast<long>(3);
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string result = emitter.c_str();
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("3"), std::string::npos);
}

// Test: Long as map key
TEST_F(EmitterLongTest_52, EmitLongAsMapKey_52) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << static_cast<long>(42);
    emitter << YAML::Value << "answer";
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string result = emitter.c_str();
    EXPECT_NE(result.find("42"), std::string::npos);
    EXPECT_NE(result.find("answer"), std::string::npos);
}

// Test: Multiple long values emitted at top level (document separation)
TEST_F(EmitterLongTest_52, EmitSingleLongCStr_52) {
    emitter << static_cast<long>(77);
    ASSERT_TRUE(emitter.good());
    EXPECT_STREQ(emitter.c_str(), "77");
    EXPECT_EQ(emitter.size(), 2u);
}

// Test: Large positive long
TEST_F(EmitterLongTest_52, EmitLargePositiveLong_52) {
    long largeVal = 1000000000L;
    emitter << largeVal;
    ASSERT_TRUE(emitter.good());
    EXPECT_EQ(std::string(emitter.c_str()), "1000000000");
}

// Test: Large negative long
TEST_F(EmitterLongTest_52, EmitLargeNegativeLong_52) {
    long largeNeg = -1000000000L;
    emitter << largeNeg;
    ASSERT_TRUE(emitter.good());
    EXPECT_EQ(std::string(emitter.c_str()), "-1000000000");
}
