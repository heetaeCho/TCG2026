#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <valarray>
#include <string>
#include <vector>

// Test fixture for valarray decode tests
class ValarrayConvertTest_618 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test decoding a sequence of integers into a valarray<int>
TEST_F(ValarrayConvertTest_618, DecodeIntSequence_618) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    node.push_back(4);
    node.push_back(5);

    std::valarray<int> result = node.as<std::valarray<int>>();

    ASSERT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
    EXPECT_EQ(result[3], 4);
    EXPECT_EQ(result[4], 5);
}

// Test decoding a sequence of doubles into a valarray<double>
TEST_F(ValarrayConvertTest_618, DecodeDoubleSequence_618) {
    YAML::Node node;
    node.push_back(1.5);
    node.push_back(2.5);
    node.push_back(3.5);

    std::valarray<double> result = node.as<std::valarray<double>>();

    ASSERT_EQ(result.size(), 3u);
    EXPECT_DOUBLE_EQ(result[0], 1.5);
    EXPECT_DOUBLE_EQ(result[1], 2.5);
    EXPECT_DOUBLE_EQ(result[2], 3.5);
}

// Test decoding a sequence of strings into a valarray<std::string>
TEST_F(ValarrayConvertTest_618, DecodeStringSequence_618) {
    YAML::Node node;
    node.push_back("hello");
    node.push_back("world");

    std::valarray<std::string> result = node.as<std::valarray<std::string>>();

    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "hello");
    EXPECT_EQ(result[1], "world");
}

// Test decoding an empty sequence into a valarray
TEST_F(ValarrayConvertTest_618, DecodeEmptySequence_618) {
    YAML::Node node(YAML::NodeType::Sequence);

    std::valarray<int> result = node.as<std::valarray<int>>();

    EXPECT_EQ(result.size(), 0u);
}

// Test that decoding a scalar node fails (returns false / throws)
TEST_F(ValarrayConvertTest_618, DecodeScalarNodeFails_618) {
    YAML::Node node("just a string");

    EXPECT_THROW(node.as<std::valarray<int>>(), YAML::TypedBadConversion<std::valarray<int>>);
}

// Test that decoding a map node fails
TEST_F(ValarrayConvertTest_618, DecodeMapNodeFails_618) {
    YAML::Node node(YAML::NodeType::Map);
    node["key"] = "value";

    EXPECT_THROW(node.as<std::valarray<int>>(), YAML::TypedBadConversion<std::valarray<int>>);
}

// Test that decoding a null node fails
TEST_F(ValarrayConvertTest_618, DecodeNullNodeFails_618) {
    YAML::Node node(YAML::NodeType::Null);

    EXPECT_THROW(node.as<std::valarray<int>>(), YAML::TypedBadConversion<std::valarray<int>>);
}

// Test decoding a single-element sequence
TEST_F(ValarrayConvertTest_618, DecodeSingleElementSequence_618) {
    YAML::Node node;
    node.push_back(42);

    std::valarray<int> result = node.as<std::valarray<int>>();

    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 42);
}

// Test decoding from a YAML string
TEST_F(ValarrayConvertTest_618, DecodeFromYAMLString_618) {
    YAML::Node node = YAML::Load("[10, 20, 30, 40]");

    std::valarray<int> result = node.as<std::valarray<int>>();

    ASSERT_EQ(result.size(), 4u);
    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 20);
    EXPECT_EQ(result[2], 30);
    EXPECT_EQ(result[3], 40);
}

// Test decoding a sequence of floats
TEST_F(ValarrayConvertTest_618, DecodeFloatSequence_618) {
    YAML::Node node = YAML::Load("[1.1, 2.2, 3.3]");

    std::valarray<float> result = node.as<std::valarray<float>>();

    ASSERT_EQ(result.size(), 3u);
    EXPECT_FLOAT_EQ(result[0], 1.1f);
    EXPECT_FLOAT_EQ(result[1], 2.2f);
    EXPECT_FLOAT_EQ(result[2], 3.3f);
}

// Test decoding a large sequence
TEST_F(ValarrayConvertTest_618, DecodeLargeSequence_618) {
    YAML::Node node;
    const int count = 1000;
    for (int i = 0; i < count; ++i) {
        node.push_back(i);
    }

    std::valarray<int> result = node.as<std::valarray<int>>();

    ASSERT_EQ(result.size(), static_cast<size_t>(count));
    for (int i = 0; i < count; ++i) {
        EXPECT_EQ(result[i], i);
    }
}

// Test that as() with fallback works when node is not a sequence
TEST_F(ValarrayConvertTest_618, DecodeWithFallbackOnNonSequence_618) {
    YAML::Node node("not a sequence");

    std::valarray<int> fallback = {99, 100};
    std::valarray<int> result = node.as<std::valarray<int>>(fallback);

    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], 99);
    EXPECT_EQ(result[1], 100);
}

// Test decoding a sequence with negative integers
TEST_F(ValarrayConvertTest_618, DecodeNegativeIntegers_618) {
    YAML::Node node = YAML::Load("[-1, -2, -3, 0, 1]");

    std::valarray<int> result = node.as<std::valarray<int>>();

    ASSERT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], -1);
    EXPECT_EQ(result[1], -2);
    EXPECT_EQ(result[2], -3);
    EXPECT_EQ(result[3], 0);
    EXPECT_EQ(result[4], 1);
}

// Test decoding a sequence of booleans
TEST_F(ValarrayConvertTest_618, DecodeBoolSequence_618) {
    YAML::Node node = YAML::Load("[true, false, true]");

    std::valarray<bool> result = node.as<std::valarray<bool>>();

    ASSERT_EQ(result.size(), 3u);
    EXPECT_TRUE(result[0]);
    EXPECT_FALSE(result[1]);
    EXPECT_TRUE(result[2]);
}

// Test encoding a valarray back to a Node (if encode is supported)
TEST_F(ValarrayConvertTest_618, EncodeValarray_618) {
    std::valarray<int> va = {10, 20, 30};
    YAML::Node node(va);

    EXPECT_TRUE(node.IsSequence());
    ASSERT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 10);
    EXPECT_EQ(node[1].as<int>(), 20);
    EXPECT_EQ(node[2].as<int>(), 30);
}

// Test round-trip: encode then decode
TEST_F(ValarrayConvertTest_618, RoundTripValarray_618) {
    std::valarray<double> original = {1.1, 2.2, 3.3, 4.4};
    YAML::Node node(original);

    std::valarray<double> decoded = node.as<std::valarray<double>>();

    ASSERT_EQ(decoded.size(), original.size());
    for (size_t i = 0; i < original.size(); ++i) {
        EXPECT_DOUBLE_EQ(decoded[i], original[i]);
    }
}

// Test that an undefined node fails decoding
TEST_F(ValarrayConvertTest_618, DecodeUndefinedNodeFails_618) {
    YAML::Node node(YAML::NodeType::Undefined);

    EXPECT_THROW(node.as<std::valarray<int>>(), YAML::TypedBadConversion<std::valarray<int>>);
}
