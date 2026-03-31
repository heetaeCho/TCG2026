#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <sstream>

class EmitterTest_542 : public ::testing::Test {
protected:
    YAML::Emitter emitter;
};

// Test that writing a null value produces valid output
TEST_F(EmitterTest_542, WriteNullProducesOutput_542) {
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// Test that writing null produces the expected null representation (typically "~" or "null")
TEST_F(EmitterTest_542, WriteNullProducesNullString_542) {
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // YAML null is typically represented as "~" or "null"
    EXPECT_TRUE(output == "~" || output == "null");
}

// Test that emitter remains in good state after writing null
TEST_F(EmitterTest_542, WriteNullEmitterRemainsGood_542) {
    EXPECT_TRUE(emitter.good());
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
}

// Test writing null as a value in a map
TEST_F(EmitterTest_542, WriteNullAsMapValue_542) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key";
    emitter << YAML::Value << YAML::Null;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// Test writing null as a sequence element
TEST_F(EmitterTest_542, WriteNullInSequence_542) {
    emitter << YAML::BeginSeq;
    emitter << YAML::Null;
    emitter << YAML::Null;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// Test writing null as a map key
TEST_F(EmitterTest_542, WriteNullAsMapKey_542) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << YAML::Null;
    emitter << YAML::Value << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// Test that the output of null can be parsed back as null
TEST_F(EmitterTest_542, WriteNullRoundTrip_542) {
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    YAML::Node node = YAML::Load(emitter.c_str());
    EXPECT_TRUE(node.IsNull());
}

// Test writing multiple nulls in a sequence round-trips correctly
TEST_F(EmitterTest_542, WriteMultipleNullsInSequenceRoundTrip_542) {
    emitter << YAML::BeginSeq;
    emitter << YAML::Null;
    emitter << "hello";
    emitter << YAML::Null;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    YAML::Node node = YAML::Load(emitter.c_str());
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_TRUE(node[0].IsNull());
    EXPECT_EQ(node[1].as<std::string>(), "hello");
    EXPECT_TRUE(node[2].IsNull());
}

// Test writing null in flow sequence
TEST_F(EmitterTest_542, WriteNullInFlowSequence_542) {
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << YAML::Null;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// Test writing null in flow map
TEST_F(EmitterTest_542, WriteNullInFlowMap_542) {
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key";
    emitter << YAML::Value << YAML::Null;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// Test that size of emitter output is non-zero after writing null
TEST_F(EmitterTest_542, WriteNullOutputSizeNonZero_542) {
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test that a standalone null is a valid YAML scalar
TEST_F(EmitterTest_542, WriteNullIsScalar_542) {
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    YAML::Node node = YAML::Load(emitter.c_str());
    // A null node should be recognized
    EXPECT_TRUE(node.IsNull() || node.IsScalar());
}

// Test null combined with other types in a map
TEST_F(EmitterTest_542, WriteNullWithMixedTypesInMap_542) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "null_val" << YAML::Value << YAML::Null;
    emitter << YAML::Key << "int_val" << YAML::Value << 42;
    emitter << YAML::Key << "str_val" << YAML::Value << "hello";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());

    YAML::Node node = YAML::Load(emitter.c_str());
    EXPECT_TRUE(node["null_val"].IsNull());
    EXPECT_EQ(node["int_val"].as<int>(), 42);
    EXPECT_EQ(node["str_val"].as<std::string>(), "hello");
}

// Test that chaining Write(Null) returns the emitter reference (fluent interface)
TEST_F(EmitterTest_542, WriteNullReturnsSelf_542) {
    // The operator<< should return a reference to emitter, enabling chaining
    YAML::Emitter& ref = (emitter << YAML::Null);
    EXPECT_EQ(&ref, &emitter);
}
