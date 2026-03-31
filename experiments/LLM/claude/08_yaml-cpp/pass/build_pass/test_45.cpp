#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterNullTest_45 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that writing _Null produces valid output and emitter remains in good state
TEST_F(EmitterNullTest_45, WriteNullDefaultFormat_45) {
    YAML::Emitter emitter;
    emitter << YAML::_Null();
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output(emitter.c_str());
    // Default null representation should be "~" or "null"
    EXPECT_TRUE(output == "~" || output == "null") << "Got: " << output;
}

// Test using the inline operator<< for _Null
TEST_F(EmitterNullTest_45, OperatorShiftNull_45) {
    YAML::Emitter emitter;
    YAML::_Null n;
    emitter << n;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    EXPECT_GT(emitter.size(), 0u);
}

// Test that SetNullFormat with LowerNull works
TEST_F(EmitterNullTest_45, SetNullFormatLowerNull_45) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
    emitter << YAML::_Null();
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "null");
}

// Test that SetNullFormat with UpperNull works
TEST_F(EmitterNullTest_45, SetNullFormatUpperNull_45) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::UpperNull));
    emitter << YAML::_Null();
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "NULL");
}

// Test that SetNullFormat with CamelNull works
TEST_F(EmitterNullTest_45, SetNullFormatCamelNull_45) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::CamelNull));
    emitter << YAML::_Null();
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "Null");
}

// Test that SetNullFormat with TildeNull works
TEST_F(EmitterNullTest_45, SetNullFormatTildeNull_45) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
    emitter << YAML::_Null();
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "~");
}

// Test null value inside a sequence
TEST_F(EmitterNullTest_45, NullInSequence_45) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::_Null();
    emitter << "value";
    emitter << YAML::_Null();
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

// Test null value as map value
TEST_F(EmitterNullTest_45, NullAsMapValue_45) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key";
    emitter << YAML::Value << YAML::_Null();
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("key"), std::string::npos);
}

// Test null value as map key
TEST_F(EmitterNullTest_45, NullAsMapKey_45) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << YAML::_Null();
    emitter << YAML::Value << "value";
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("value"), std::string::npos);
}

// Test writing null to a stream-based emitter
TEST_F(EmitterNullTest_45, NullToStream_45) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << YAML::_Null();
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = ss.str();
    EXPECT_TRUE(output == "~" || output == "null") << "Got: " << output;
}

// Test writing null after setting format, to stream
TEST_F(EmitterNullTest_45, NullToStreamWithFormat_45) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter.SetNullFormat(YAML::UpperNull);
    emitter << YAML::_Null();
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = ss.str();
    EXPECT_EQ(output, "NULL");
}

// Test multiple nulls in a flow sequence
TEST_F(EmitterNullTest_45, MultipleNullsFlowSeq_45) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq;
    emitter << YAML::_Null();
    emitter << YAML::_Null();
    emitter << YAML::_Null();
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

// Test null in a block sequence
TEST_F(EmitterNullTest_45, NullInBlockSeq_45) {
    YAML::Emitter emitter;
    emitter << YAML::Block << YAML::BeginSeq;
    emitter << YAML::_Null();
    emitter << "hello";
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("-"), std::string::npos);
}

// Test that emitter good() returns true initially
TEST_F(EmitterNullTest_45, EmitterInitiallyGood_45) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
}

// Test that c_str returns empty string initially
TEST_F(EmitterNullTest_45, EmitterInitiallyEmpty_45) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.size(), 0u);
}

// Test size after writing null
TEST_F(EmitterNullTest_45, SizeAfterWritingNull_45) {
    YAML::Emitter emitter;
    emitter << YAML::_Null();
    ASSERT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test that null Null object is YAML Null constant
TEST_F(EmitterNullTest_45, NullConstant_45) {
    YAML::Emitter emitter;
    emitter << YAML::Null;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output(emitter.c_str());
    EXPECT_TRUE(output == "~" || output == "null" || output == "Null" || output == "NULL")
        << "Got: " << output;
}

// Test null combined with a tag
TEST_F(EmitterNullTest_45, NullWithTag_45) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "tagged";
    emitter << YAML::Value;
    emitter << YAML::_Null();
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
}

// Test flow map with null key and value
TEST_F(EmitterNullTest_45, FlowMapNullKeyAndValue_45) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginMap;
    emitter << YAML::Key << YAML::_Null();
    emitter << YAML::Value << YAML::_Null();
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

// Test that SetLocalValue with null format works
TEST_F(EmitterNullTest_45, SetLocalValueNullFormat_45) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::UpperNull << YAML::_Null();
    emitter << YAML::_Null(); // Should revert to default
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
}

// Test that RestoreGlobalModifiedSettings works after setting null format
TEST_F(EmitterNullTest_45, RestoreGlobalModifiedSettingsNull_45) {
    YAML::Emitter emitter;
    emitter.SetNullFormat(YAML::UpperNull);
    emitter.RestoreGlobalModifiedSettings();
    emitter << YAML::_Null();
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output(emitter.c_str());
    // After restore, should be back to default
    EXPECT_TRUE(output == "~" || output == "null") << "Got: " << output;
}

// Test nested sequences with nulls
TEST_F(EmitterNullTest_45, NestedSeqWithNulls_45) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginSeq;
    emitter << YAML::_Null();
    emitter << YAML::EndSeq;
    emitter << YAML::_Null();
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
}

// Test that the operator<< returns a reference to the same emitter
TEST_F(EmitterNullTest_45, OperatorReturnsSameEmitter_45) {
    YAML::Emitter emitter;
    YAML::_Null n;
    YAML::Emitter& ref = (emitter << n);
    EXPECT_EQ(&ref, &emitter);
}
