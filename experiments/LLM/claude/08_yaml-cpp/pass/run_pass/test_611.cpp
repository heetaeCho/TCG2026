#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <vector>
#include <string>
#include <list>

// Test encoding an empty vector
TEST(ConvertVectorTest_611, EncodeEmptyVector_611) {
    std::vector<int> empty_vec;
    YAML::Node node = YAML::convert<std::vector<int>>::encode(empty_vec);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 0u);
}

// Test encoding a vector of integers
TEST(ConvertVectorTest_611, EncodeIntVector_611) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    YAML::Node node = YAML::convert<std::vector<int>>::encode(vec);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 5u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
    EXPECT_EQ(node[3].as<int>(), 4);
    EXPECT_EQ(node[4].as<int>(), 5);
}

// Test encoding a vector of strings
TEST(ConvertVectorTest_611, EncodeStringVector_611) {
    std::vector<std::string> vec = {"hello", "world", "foo"};
    YAML::Node node = YAML::convert<std::vector<std::string>>::encode(vec);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<std::string>(), "hello");
    EXPECT_EQ(node[1].as<std::string>(), "world");
    EXPECT_EQ(node[2].as<std::string>(), "foo");
}

// Test encoding a vector of doubles
TEST(ConvertVectorTest_611, EncodeDoubleVector_611) {
    std::vector<double> vec = {1.1, 2.2, 3.3};
    YAML::Node node = YAML::convert<std::vector<double>>::encode(vec);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_DOUBLE_EQ(node[0].as<double>(), 1.1);
    EXPECT_DOUBLE_EQ(node[1].as<double>(), 2.2);
    EXPECT_DOUBLE_EQ(node[2].as<double>(), 3.3);
}

// Test encoding a single-element vector
TEST(ConvertVectorTest_611, EncodeSingleElementVector_611) {
    std::vector<int> vec = {42};
    YAML::Node node = YAML::convert<std::vector<int>>::encode(vec);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node[0].as<int>(), 42);
}

// Test encoding a vector of booleans
TEST(ConvertVectorTest_611, EncodeBoolVector_611) {
    std::vector<bool> vec = {true, false, true};
    YAML::Node node = YAML::convert<std::vector<bool>>::encode(vec);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<bool>(), true);
    EXPECT_EQ(node[1].as<bool>(), false);
    EXPECT_EQ(node[2].as<bool>(), true);
}

// Test that the encoded node type is Sequence
TEST(ConvertVectorTest_611, EncodedNodeTypeIsSequence_611) {
    std::vector<int> vec = {10, 20};
    YAML::Node node = YAML::convert<std::vector<int>>::encode(vec);
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

// Test encoding a large vector
TEST(ConvertVectorTest_611, EncodeLargeVector_611) {
    std::vector<int> vec;
    for (int i = 0; i < 1000; ++i) {
        vec.push_back(i);
    }
    YAML::Node node = YAML::convert<std::vector<int>>::encode(vec);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
    EXPECT_EQ(node[500].as<int>(), 500);
}

// Test encoding preserves order
TEST(ConvertVectorTest_611, EncodePreservesOrder_611) {
    std::vector<int> vec = {5, 3, 1, 4, 2};
    YAML::Node node = YAML::convert<std::vector<int>>::encode(vec);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 5u);
    for (std::size_t i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(node[i].as<int>(), vec[i]);
    }
}

// Test encoding a vector of negative integers
TEST(ConvertVectorTest_611, EncodeNegativeIntVector_611) {
    std::vector<int> vec = {-1, -2, -3};
    YAML::Node node = YAML::convert<std::vector<int>>::encode(vec);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), -1);
    EXPECT_EQ(node[1].as<int>(), -2);
    EXPECT_EQ(node[2].as<int>(), -3);
}

// Test encoding a vector with duplicate elements
TEST(ConvertVectorTest_611, EncodeDuplicateElements_611) {
    std::vector<int> vec = {7, 7, 7};
    YAML::Node node = YAML::convert<std::vector<int>>::encode(vec);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    for (std::size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(node[i].as<int>(), 7);
    }
}

// Test encoding a vector of empty strings
TEST(ConvertVectorTest_611, EncodeEmptyStringVector_611) {
    std::vector<std::string> vec = {"", "", ""};
    YAML::Node node = YAML::convert<std::vector<std::string>>::encode(vec);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    for (std::size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(node[i].as<std::string>(), "");
    }
}

// Test round-trip: encode then decode back to vector
TEST(ConvertVectorTest_611, RoundTripIntVector_611) {
    std::vector<int> original = {10, 20, 30, 40};
    YAML::Node node = YAML::convert<std::vector<int>>::encode(original);
    std::vector<int> decoded = node.as<std::vector<int>>();
    EXPECT_EQ(original, decoded);
}

// Test round-trip with strings
TEST(ConvertVectorTest_611, RoundTripStringVector_611) {
    std::vector<std::string> original = {"alpha", "beta", "gamma"};
    YAML::Node node = YAML::convert<std::vector<std::string>>::encode(original);
    std::vector<std::string> decoded = node.as<std::vector<std::string>>();
    EXPECT_EQ(original, decoded);
}

// Test round-trip with empty vector
TEST(ConvertVectorTest_611, RoundTripEmptyVector_611) {
    std::vector<int> original;
    YAML::Node node = YAML::convert<std::vector<int>>::encode(original);
    std::vector<int> decoded = node.as<std::vector<int>>();
    EXPECT_EQ(original, decoded);
}

// Test that iteration over encoded node yields correct elements
TEST(ConvertVectorTest_611, IterateEncodedNode_611) {
    std::vector<int> vec = {100, 200, 300};
    YAML::Node node = YAML::convert<std::vector<int>>::encode(vec);
    
    std::vector<int> result;
    for (auto it = node.begin(); it != node.end(); ++it) {
        result.push_back(it->as<int>());
    }
    EXPECT_EQ(result, vec);
}

// Test encoding vector of floats
TEST(ConvertVectorTest_611, EncodeFloatVector_611) {
    std::vector<float> vec = {1.5f, 2.5f, 3.5f};
    YAML::Node node = YAML::convert<std::vector<float>>::encode(vec);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_FLOAT_EQ(node[0].as<float>(), 1.5f);
    EXPECT_FLOAT_EQ(node[1].as<float>(), 2.5f);
    EXPECT_FLOAT_EQ(node[2].as<float>(), 3.5f);
}

// Test encoding vector of unsigned integers
TEST(ConvertVectorTest_611, EncodeUnsignedIntVector_611) {
    std::vector<unsigned int> vec = {0, 1, 4294967295u};
    YAML::Node node = YAML::convert<std::vector<unsigned int>>::encode(vec);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<unsigned int>(), 0u);
    EXPECT_EQ(node[1].as<unsigned int>(), 1u);
    EXPECT_EQ(node[2].as<unsigned int>(), 4294967295u);
}
