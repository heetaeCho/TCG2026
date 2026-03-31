#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <map>
#include <list>
#include <utility>

// Tests for convert.h - specifically the std::pair decode functionality
// and other convert specializations accessible through Node::as<T>()

class ConvertPairTest_620 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Decode a valid pair of integers from a sequence node
TEST_F(ConvertPairTest_620, DecodeValidIntPair_620) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);

    auto result = node.as<std::pair<int, int>>();
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 2);
}

// Test: Decode a valid pair of strings from a sequence node
TEST_F(ConvertPairTest_620, DecodeValidStringPair_620) {
    YAML::Node node;
    node.push_back("hello");
    node.push_back("world");

    auto result = node.as<std::pair<std::string, std::string>>();
    EXPECT_EQ(result.first, "hello");
    EXPECT_EQ(result.second, "world");
}

// Test: Decode a pair with mixed types (string, int)
TEST_F(ConvertPairTest_620, DecodeMixedTypePair_620) {
    YAML::Node node;
    node.push_back("key");
    node.push_back(42);

    auto result = node.as<std::pair<std::string, int>>();
    EXPECT_EQ(result.first, "key");
    EXPECT_EQ(result.second, 42);
}

// Test: Decode fails for non-sequence node (scalar)
TEST_F(ConvertPairTest_620, DecodeFailsForScalarNode_620) {
    YAML::Node node("just a scalar");

    std::pair<int, int> fallback{-1, -1};
    auto result = node.as<std::pair<int, int>>(fallback);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

// Test: Decode fails for map node
TEST_F(ConvertPairTest_620, DecodeFailsForMapNode_620) {
    YAML::Node node;
    node["a"] = 1;

    std::pair<std::string, int> fallback{"default", 0};
    auto result = node.as<std::pair<std::string, int>>(fallback);
    EXPECT_EQ(result.first, "default");
    EXPECT_EQ(result.second, 0);
}

// Test: Decode fails for sequence with wrong size (1 element)
TEST_F(ConvertPairTest_620, DecodeFailsForSequenceOfSizeOne_620) {
    YAML::Node node;
    node.push_back(1);

    std::pair<int, int> fallback{-1, -1};
    auto result = node.as<std::pair<int, int>>(fallback);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

// Test: Decode fails for sequence with wrong size (3 elements)
TEST_F(ConvertPairTest_620, DecodeFailsForSequenceOfSizeThree_620) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);

    std::pair<int, int> fallback{-1, -1};
    auto result = node.as<std::pair<int, int>>(fallback);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

// Test: Decode fails for empty sequence
TEST_F(ConvertPairTest_620, DecodeFailsForEmptySequence_620) {
    YAML::Node node(YAML::NodeType::Sequence);

    std::pair<int, int> fallback{-1, -1};
    auto result = node.as<std::pair<int, int>>(fallback);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

// Test: Decode a pair of doubles
TEST_F(ConvertPairTest_620, DecodeDoublePair_620) {
    YAML::Node node;
    node.push_back(3.14);
    node.push_back(2.72);

    auto result = node.as<std::pair<double, double>>();
    EXPECT_DOUBLE_EQ(result.first, 3.14);
    EXPECT_DOUBLE_EQ(result.second, 2.72);
}

// Test: Decode a pair of bool values
TEST_F(ConvertPairTest_620, DecodeBoolPair_620) {
    YAML::Node node;
    node.push_back(true);
    node.push_back(false);

    auto result = node.as<std::pair<bool, bool>>();
    EXPECT_EQ(result.first, true);
    EXPECT_EQ(result.second, false);
}

// Test: Decode fails for null/undefined node
TEST_F(ConvertPairTest_620, DecodeFailsForNullNode_620) {
    YAML::Node node;

    std::pair<int, int> fallback{-1, -1};
    auto result = node.as<std::pair<int, int>>(fallback);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

// Test: Decode a pair from YAML string
TEST_F(ConvertPairTest_620, DecodeFromYAMLString_620) {
    YAML::Node node = YAML::Load("[10, 20]");

    auto result = node.as<std::pair<int, int>>();
    EXPECT_EQ(result.first, 10);
    EXPECT_EQ(result.second, 20);
}

// Test: Decode pair with nested types (pair of int and string from YAML)
TEST_F(ConvertPairTest_620, DecodeFromYAMLStringMixedTypes_620) {
    YAML::Node node = YAML::Load("[hello, 42]");

    auto result = node.as<std::pair<std::string, int>>();
    EXPECT_EQ(result.first, "hello");
    EXPECT_EQ(result.second, 42);
}

// Tests for other convert specializations

class ConvertBasicTest_620 : public ::testing::Test {};

// Test: Convert node to string
TEST_F(ConvertBasicTest_620, DecodeString_620) {
    YAML::Node node("hello");
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test: Convert node to int
TEST_F(ConvertBasicTest_620, DecodeInt_620) {
    YAML::Node node(42);
    EXPECT_EQ(node.as<int>(), 42);
}

// Test: Convert node to double
TEST_F(ConvertBasicTest_620, DecodeDouble_620) {
    YAML::Node node(3.14);
    EXPECT_DOUBLE_EQ(node.as<double>(), 3.14);
}

// Test: Convert node to bool (true)
TEST_F(ConvertBasicTest_620, DecodeBoolTrue_620) {
    YAML::Node node(true);
    EXPECT_EQ(node.as<bool>(), true);
}

// Test: Convert node to bool (false)
TEST_F(ConvertBasicTest_620, DecodeBoolFalse_620) {
    YAML::Node node(false);
    EXPECT_EQ(node.as<bool>(), false);
}

// Test: Convert node to vector of ints
TEST_F(ConvertBasicTest_620, DecodeVectorInt_620) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);

    auto result = node.as<std::vector<int>>();
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
}

// Test: Convert node to map of string to int
TEST_F(ConvertBasicTest_620, DecodeMapStringInt_620) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;

    auto result = node.as<std::map<std::string, int>>();
    EXPECT_EQ(result["a"], 1);
    EXPECT_EQ(result["b"], 2);
}

// Test: as<T> with fallback when conversion fails
TEST_F(ConvertBasicTest_620, AsFallbackOnFailure_620) {
    YAML::Node node;  // Null node
    int result = node.as<int>(99);
    EXPECT_EQ(result, 99);
}

// Test: as<T> with fallback when conversion succeeds
TEST_F(ConvertBasicTest_620, AsFallbackNotUsedOnSuccess_620) {
    YAML::Node node(42);
    int result = node.as<int>(99);
    EXPECT_EQ(result, 42);
}

// Test: Encode an int and decode it back
TEST_F(ConvertBasicTest_620, RoundTripInt_620) {
    YAML::Node node;
    node = 123;
    EXPECT_EQ(node.as<int>(), 123);
}

// Test: Encode a string and decode it back
TEST_F(ConvertBasicTest_620, RoundTripString_620) {
    YAML::Node node;
    node = std::string("test_value");
    EXPECT_EQ(node.as<std::string>(), "test_value");
}

// Test: Encode a pair and decode it back
TEST_F(ConvertBasicTest_620, RoundTripPair_620) {
    YAML::Node node;
    std::pair<std::string, int> original{"key", 100};
    node.push_back(original.first);
    node.push_back(original.second);

    auto result = node.as<std::pair<std::string, int>>();
    EXPECT_EQ(result.first, "key");
    EXPECT_EQ(result.second, 100);
}

// Test: Decode empty vector from empty sequence
TEST_F(ConvertBasicTest_620, DecodeEmptyVector_620) {
    YAML::Node node(YAML::NodeType::Sequence);
    auto result = node.as<std::vector<int>>();
    EXPECT_TRUE(result.empty());
}

// Test: Pair decode with negative numbers
TEST_F(ConvertPairTest_620, DecodeNegativeIntPair_620) {
    YAML::Node node;
    node.push_back(-5);
    node.push_back(-10);

    auto result = node.as<std::pair<int, int>>();
    EXPECT_EQ(result.first, -5);
    EXPECT_EQ(result.second, -10);
}

// Test: Pair decode with zero values
TEST_F(ConvertPairTest_620, DecodeZeroPair_620) {
    YAML::Node node;
    node.push_back(0);
    node.push_back(0);

    auto result = node.as<std::pair<int, int>>();
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 0);
}

// Test: Pair decode with large values
TEST_F(ConvertPairTest_620, DecodeLargeIntPair_620) {
    YAML::Node node;
    node.push_back(2147483647);  // INT_MAX
    node.push_back(-2147483647); // close to INT_MIN

    auto result = node.as<std::pair<int, int>>();
    EXPECT_EQ(result.first, 2147483647);
    EXPECT_EQ(result.second, -2147483647);
}

// Test: Pair decode with empty strings
TEST_F(ConvertPairTest_620, DecodeEmptyStringPair_620) {
    YAML::Node node;
    node.push_back("");
    node.push_back("");

    auto result = node.as<std::pair<std::string, std::string>>();
    EXPECT_EQ(result.first, "");
    EXPECT_EQ(result.second, "");
}

// Test: Decode a list type
TEST_F(ConvertBasicTest_620, DecodeListInt_620) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);
    node.push_back(30);

    auto result = node.as<std::list<int>>();
    ASSERT_EQ(result.size(), 3u);
    auto it = result.begin();
    EXPECT_EQ(*it++, 10);
    EXPECT_EQ(*it++, 20);
    EXPECT_EQ(*it++, 30);
}

// Test: Pair from parsed YAML with three elements should fail
TEST_F(ConvertPairTest_620, DecodeFromParsedYAMLThreeElements_620) {
    YAML::Node node = YAML::Load("[1, 2, 3]");

    std::pair<int, int> fallback{-1, -1};
    auto result = node.as<std::pair<int, int>>(fallback);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

// Test: Pair from parsed YAML with one element should fail
TEST_F(ConvertPairTest_620, DecodeFromParsedYAMLOneElement_620) {
    YAML::Node node = YAML::Load("[1]");

    std::pair<int, int> fallback{-1, -1};
    auto result = node.as<std::pair<int, int>>(fallback);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

// Test: Pair from parsed YAML scalar should fail
TEST_F(ConvertPairTest_620, DecodeFromParsedYAMLScalar_620) {
    YAML::Node node = YAML::Load("42");

    std::pair<int, int> fallback{-1, -1};
    auto result = node.as<std::pair<int, int>>(fallback);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

// Test: Pair from parsed YAML map should fail
TEST_F(ConvertPairTest_620, DecodeFromParsedYAMLMap_620) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");

    std::pair<std::string, int> fallback{"default", -1};
    auto result = node.as<std::pair<std::string, int>>(fallback);
    EXPECT_EQ(result.first, "default");
    EXPECT_EQ(result.second, -1);
}

// Test: Nested pair decode
TEST_F(ConvertPairTest_620, DecodeNestedPair_620) {
    // Build [[ 1, 2 ], 3]
    YAML::Node inner;
    inner.push_back(1);
    inner.push_back(2);

    YAML::Node outer;
    outer.push_back(inner);
    outer.push_back(3);

    auto result = outer.as<std::pair<std::pair<int, int>, int>>();
    EXPECT_EQ(result.first.first, 1);
    EXPECT_EQ(result.first.second, 2);
    EXPECT_EQ(result.second, 3);
}

// Test: Pair with float types
TEST_F(ConvertPairTest_620, DecodeFloatPair_620) {
    YAML::Node node;
    node.push_back(1.5f);
    node.push_back(2.5f);

    auto result = node.as<std::pair<float, float>>();
    EXPECT_FLOAT_EQ(result.first, 1.5f);
    EXPECT_FLOAT_EQ(result.second, 2.5f);
}
