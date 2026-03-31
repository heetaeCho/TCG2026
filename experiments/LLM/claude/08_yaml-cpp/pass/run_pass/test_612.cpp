#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <vector>
#include <string>

class YamlVectorConvertTest_612 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Decoding a valid sequence node into a vector of integers
TEST_F(YamlVectorConvertTest_612, DecodeValidIntSequence_612) {
    YAML::Node node = YAML::Load("[1, 2, 3, 4, 5]");
    std::vector<int> result = node.as<std::vector<int>>();
    ASSERT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
    EXPECT_EQ(result[3], 4);
    EXPECT_EQ(result[4], 5);
}

// Test: Decoding a valid sequence node into a vector of strings
TEST_F(YamlVectorConvertTest_612, DecodeValidStringSequence_612) {
    YAML::Node node = YAML::Load("[hello, world, foo]");
    std::vector<std::string> result = node.as<std::vector<std::string>>();
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "hello");
    EXPECT_EQ(result[1], "world");
    EXPECT_EQ(result[2], "foo");
}

// Test: Decoding an empty sequence node into a vector
TEST_F(YamlVectorConvertTest_612, DecodeEmptySequence_612) {
    YAML::Node node = YAML::Load("[]");
    std::vector<int> result = node.as<std::vector<int>>();
    EXPECT_TRUE(result.empty());
}

// Test: Decoding a scalar node should fail (not a sequence)
TEST_F(YamlVectorConvertTest_612, DecodeScalarNodeFails_612) {
    YAML::Node node = YAML::Load("42");
    EXPECT_THROW(node.as<std::vector<int>>(), YAML::TypedBadConversion<std::vector<int>>);
}

// Test: Decoding a map node should fail (not a sequence)
TEST_F(YamlVectorConvertTest_612, DecodeMapNodeFails_612) {
    YAML::Node node = YAML::Load("{key: value}");
    EXPECT_THROW(node.as<std::vector<int>>(), YAML::TypedBadConversion<std::vector<int>>);
}

// Test: Decoding a null node should fail (not a sequence)
TEST_F(YamlVectorConvertTest_612, DecodeNullNodeFails_612) {
    YAML::Node node = YAML::Load("~");
    EXPECT_THROW(node.as<std::vector<int>>(), YAML::TypedBadConversion<std::vector<int>>);
}

// Test: Decoding a sequence with a single element
TEST_F(YamlVectorConvertTest_612, DecodeSingleElementSequence_612) {
    YAML::Node node = YAML::Load("[42]");
    std::vector<int> result = node.as<std::vector<int>>();
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 42);
}

// Test: Decoding a sequence of doubles
TEST_F(YamlVectorConvertTest_612, DecodeDoubleSequence_612) {
    YAML::Node node = YAML::Load("[1.5, 2.7, 3.14]");
    std::vector<double> result = node.as<std::vector<double>>();
    ASSERT_EQ(result.size(), 3u);
    EXPECT_DOUBLE_EQ(result[0], 1.5);
    EXPECT_DOUBLE_EQ(result[1], 2.7);
    EXPECT_DOUBLE_EQ(result[2], 3.14);
}

// Test: Decoding a sequence of booleans
TEST_F(YamlVectorConvertTest_612, DecodeBoolSequence_612) {
    YAML::Node node = YAML::Load("[true, false, true]");
    std::vector<bool> result = node.as<std::vector<bool>>();
    ASSERT_EQ(result.size(), 3u);
    EXPECT_TRUE(result[0]);
    EXPECT_FALSE(result[1]);
    EXPECT_TRUE(result[2]);
}

// Test: Decoding clears the existing vector contents
TEST_F(YamlVectorConvertTest_612, DecodeClearsExistingVector_612) {
    YAML::Node node = YAML::Load("[10, 20]");
    std::vector<int> result = {1, 2, 3, 4, 5};
    ASSERT_TRUE(YAML::convert<std::vector<int>>::decode(node, result));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 20);
}

// Test: Decoding a nested sequence (vector of vectors)
TEST_F(YamlVectorConvertTest_612, DecodeNestedSequence_612) {
    YAML::Node node = YAML::Load("[[1, 2], [3, 4], [5]]");
    std::vector<std::vector<int>> result = node.as<std::vector<std::vector<int>>>();
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0].size(), 2u);
    EXPECT_EQ(result[0][0], 1);
    EXPECT_EQ(result[0][1], 2);
    ASSERT_EQ(result[1].size(), 2u);
    EXPECT_EQ(result[1][0], 3);
    EXPECT_EQ(result[1][1], 4);
    ASSERT_EQ(result[2].size(), 1u);
    EXPECT_EQ(result[2][0], 5);
}

// Test: decode returns false for non-sequence node
TEST_F(YamlVectorConvertTest_612, DecodeReturnsFalseForNonSequence_612) {
    YAML::Node node = YAML::Load("not_a_sequence");
    std::vector<int> result;
    EXPECT_FALSE(YAML::convert<std::vector<int>>::decode(node, result));
}

// Test: decode returns true for valid sequence node
TEST_F(YamlVectorConvertTest_612, DecodeReturnsTrueForValidSequence_612) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    std::vector<int> result;
    EXPECT_TRUE(YAML::convert<std::vector<int>>::decode(node, result));
    EXPECT_EQ(result.size(), 3u);
}

// Test: Decoding a large sequence
TEST_F(YamlVectorConvertTest_612, DecodeLargeSequence_612) {
    std::string yaml = "[";
    for (int i = 0; i < 1000; ++i) {
        if (i > 0) yaml += ", ";
        yaml += std::to_string(i);
    }
    yaml += "]";
    YAML::Node node = YAML::Load(yaml);
    std::vector<int> result = node.as<std::vector<int>>();
    ASSERT_EQ(result.size(), 1000u);
    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(result[i], i);
    }
}

// Test: Decoding sequence with negative integers
TEST_F(YamlVectorConvertTest_612, DecodeNegativeIntSequence_612) {
    YAML::Node node = YAML::Load("[-1, -2, -3]");
    std::vector<int> result = node.as<std::vector<int>>();
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], -1);
    EXPECT_EQ(result[1], -2);
    EXPECT_EQ(result[2], -3);
}

// Test: Decoding with fallback when node is not a sequence
TEST_F(YamlVectorConvertTest_612, DecodeWithFallbackOnNonSequence_612) {
    YAML::Node node = YAML::Load("scalar_value");
    std::vector<int> fallback = {99, 100};
    std::vector<int> result = node.as<std::vector<int>>(fallback);
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], 99);
    EXPECT_EQ(result[1], 100);
}

// Test: Decoding a sequence built programmatically
TEST_F(YamlVectorConvertTest_612, DecodeProgrammaticSequence_612) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);
    node.push_back(30);
    std::vector<int> result = node.as<std::vector<int>>();
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 20);
    EXPECT_EQ(result[2], 30);
}

// Test: Map node returns false for decode
TEST_F(YamlVectorConvertTest_612, DecodeMapReturnsFalse_612) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    std::vector<std::string> result;
    EXPECT_FALSE(YAML::convert<std::vector<std::string>>::decode(node, result));
}

// Test: Undefined node fails decode
TEST_F(YamlVectorConvertTest_612, DecodeUndefinedNodeFails_612) {
    YAML::Node root = YAML::Load("{a: 1}");
    YAML::Node undefined = root["nonexistent"];
    std::vector<int> result;
    EXPECT_FALSE(YAML::convert<std::vector<int>>::decode(undefined, result));
}
