#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <array>
#include <string>
#include <vector>

// Test encoding an array of integers
TEST(ArrayConvertTest_615, EncodeIntArray_615) {
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    YAML::Node node = YAML::convert<std::array<int, 5>>::encode(arr);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 5u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
    EXPECT_EQ(node[3].as<int>(), 4);
    EXPECT_EQ(node[4].as<int>(), 5);
}

// Test encoding an empty array (size 0)
TEST(ArrayConvertTest_615, EncodeEmptyArray_615) {
    std::array<int, 0> arr = {};
    YAML::Node node = YAML::convert<std::array<int, 0>>::encode(arr);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 0u);
}

// Test encoding an array of strings
TEST(ArrayConvertTest_615, EncodeStringArray_615) {
    std::array<std::string, 3> arr = {"hello", "world", "test"};
    YAML::Node node = YAML::convert<std::array<std::string, 3>>::encode(arr);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<std::string>(), "hello");
    EXPECT_EQ(node[1].as<std::string>(), "world");
    EXPECT_EQ(node[2].as<std::string>(), "test");
}

// Test encoding an array of doubles
TEST(ArrayConvertTest_615, EncodeDoubleArray_615) {
    std::array<double, 3> arr = {1.1, 2.2, 3.3};
    YAML::Node node = YAML::convert<std::array<double, 3>>::encode(arr);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_DOUBLE_EQ(node[0].as<double>(), 1.1);
    EXPECT_DOUBLE_EQ(node[1].as<double>(), 2.2);
    EXPECT_DOUBLE_EQ(node[2].as<double>(), 3.3);
}

// Test encoding a single-element array
TEST(ArrayConvertTest_615, EncodeSingleElementArray_615) {
    std::array<int, 1> arr = {42};
    YAML::Node node = YAML::convert<std::array<int, 1>>::encode(arr);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node[0].as<int>(), 42);
}

// Test encoding an array of booleans
TEST(ArrayConvertTest_615, EncodeBoolArray_615) {
    std::array<bool, 4> arr = {true, false, true, false};
    YAML::Node node = YAML::convert<std::array<bool, 4>>::encode(arr);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 4u);
    EXPECT_EQ(node[0].as<bool>(), true);
    EXPECT_EQ(node[1].as<bool>(), false);
    EXPECT_EQ(node[2].as<bool>(), true);
    EXPECT_EQ(node[3].as<bool>(), false);
}

// Test that the node type is Sequence
TEST(ArrayConvertTest_615, NodeTypeIsSequence_615) {
    std::array<int, 3> arr = {10, 20, 30};
    YAML::Node node = YAML::convert<std::array<int, 3>>::encode(arr);
    
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
    EXPECT_FALSE(node.IsMap());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsNull());
}

// Test encoding an array with negative values
TEST(ArrayConvertTest_615, EncodeNegativeValues_615) {
    std::array<int, 3> arr = {-1, -100, -999};
    YAML::Node node = YAML::convert<std::array<int, 3>>::encode(arr);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), -1);
    EXPECT_EQ(node[1].as<int>(), -100);
    EXPECT_EQ(node[2].as<int>(), -999);
}

// Test encoding an array with duplicate values
TEST(ArrayConvertTest_615, EncodeDuplicateValues_615) {
    std::array<int, 4> arr = {5, 5, 5, 5};
    YAML::Node node = YAML::convert<std::array<int, 4>>::encode(arr);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 4u);
    for (std::size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(node[i].as<int>(), 5);
    }
}

// Test encoding a large array
TEST(ArrayConvertTest_615, EncodeLargeArray_615) {
    std::array<int, 100> arr;
    for (int i = 0; i < 100; ++i) {
        arr[i] = i * 10;
    }
    YAML::Node node = YAML::convert<std::array<int, 100>>::encode(arr);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 100u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[50].as<int>(), 500);
    EXPECT_EQ(node[99].as<int>(), 990);
}

// Test decoding back to array (round-trip) if decode is available
TEST(ArrayConvertTest_615, RoundTripIntArray_615) {
    std::array<int, 3> original = {10, 20, 30};
    YAML::Node node = YAML::convert<std::array<int, 3>>::encode(original);
    
    std::array<int, 3> decoded;
    bool success = YAML::convert<std::array<int, 3>>::decode(node, decoded);
    
    EXPECT_TRUE(success);
    EXPECT_EQ(decoded[0], 10);
    EXPECT_EQ(decoded[1], 20);
    EXPECT_EQ(decoded[2], 30);
}

// Test encoding array of empty strings
TEST(ArrayConvertTest_615, EncodeEmptyStringArray_615) {
    std::array<std::string, 2> arr = {"", ""};
    YAML::Node node = YAML::convert<std::array<std::string, 2>>::encode(arr);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0].as<std::string>(), "");
    EXPECT_EQ(node[1].as<std::string>(), "");
}

// Test encoding array of float values
TEST(ArrayConvertTest_615, EncodeFloatArray_615) {
    std::array<float, 2> arr = {1.5f, 2.5f};
    YAML::Node node = YAML::convert<std::array<float, 2>>::encode(arr);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_FLOAT_EQ(node[0].as<float>(), 1.5f);
    EXPECT_FLOAT_EQ(node[1].as<float>(), 2.5f);
}

// Test that iterating over encoded node gives correct elements
TEST(ArrayConvertTest_615, IterateEncodedNode_615) {
    std::array<int, 4> arr = {100, 200, 300, 400};
    YAML::Node node = YAML::convert<std::array<int, 4>>::encode(arr);
    
    int index = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        EXPECT_EQ(it->as<int>(), arr[index]);
        ++index;
    }
    EXPECT_EQ(index, 4);
}

// Test encoding preserves order
TEST(ArrayConvertTest_615, EncodePreservesOrder_615) {
    std::array<int, 5> arr = {9, 7, 5, 3, 1};
    YAML::Node node = YAML::convert<std::array<int, 5>>::encode(arr);
    
    EXPECT_EQ(node[0].as<int>(), 9);
    EXPECT_EQ(node[1].as<int>(), 7);
    EXPECT_EQ(node[2].as<int>(), 5);
    EXPECT_EQ(node[3].as<int>(), 3);
    EXPECT_EQ(node[4].as<int>(), 1);
}
