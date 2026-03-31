#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <valarray>
#include <string>
#include <vector>

// Test fixture for valarray encode tests
class ValarrayEncodeTest_617 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test encoding an empty valarray
TEST_F(ValarrayEncodeTest_617, EncodeEmptyValarray_617) {
    std::valarray<int> va;
    YAML::Node node = YAML::convert<std::valarray<int>>::encode(va);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 0u);
}

// Test encoding a valarray with a single element
TEST_F(ValarrayEncodeTest_617, EncodeSingleElementValarray_617) {
    std::valarray<int> va = {42};
    YAML::Node node = YAML::convert<std::valarray<int>>::encode(va);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node[0].as<int>(), 42);
}

// Test encoding a valarray with multiple integer elements
TEST_F(ValarrayEncodeTest_617, EncodeMultipleIntElements_617) {
    std::valarray<int> va = {1, 2, 3, 4, 5};
    YAML::Node node = YAML::convert<std::valarray<int>>::encode(va);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 5u);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(node[i].as<int>(), i + 1);
    }
}

// Test encoding a valarray of doubles
TEST_F(ValarrayEncodeTest_617, EncodeDoubleValarray_617) {
    std::valarray<double> va = {1.1, 2.2, 3.3};
    YAML::Node node = YAML::convert<std::valarray<double>>::encode(va);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_DOUBLE_EQ(node[0].as<double>(), 1.1);
    EXPECT_DOUBLE_EQ(node[1].as<double>(), 2.2);
    EXPECT_DOUBLE_EQ(node[2].as<double>(), 3.3);
}

// Test encoding a valarray of strings
TEST_F(ValarrayEncodeTest_617, EncodeStringValarray_617) {
    std::valarray<std::string> va = {"hello", "world", "yaml"};
    YAML::Node node = YAML::convert<std::valarray<std::string>>::encode(va);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<std::string>(), "hello");
    EXPECT_EQ(node[1].as<std::string>(), "world");
    EXPECT_EQ(node[2].as<std::string>(), "yaml");
}

// Test encoding a valarray of floats
TEST_F(ValarrayEncodeTest_617, EncodeFloatValarray_617) {
    std::valarray<float> va = {1.0f, 2.5f, -3.5f};
    YAML::Node node = YAML::convert<std::valarray<float>>::encode(va);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_FLOAT_EQ(node[0].as<float>(), 1.0f);
    EXPECT_FLOAT_EQ(node[1].as<float>(), 2.5f);
    EXPECT_FLOAT_EQ(node[2].as<float>(), -3.5f);
}

// Test that the resulting node type is Sequence
TEST_F(ValarrayEncodeTest_617, NodeTypeIsSequence_617) {
    std::valarray<int> va = {10, 20};
    YAML::Node node = YAML::convert<std::valarray<int>>::encode(va);
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

// Test encoding a valarray with negative values
TEST_F(ValarrayEncodeTest_617, EncodeNegativeValues_617) {
    std::valarray<int> va = {-1, -2, -3};
    YAML::Node node = YAML::convert<std::valarray<int>>::encode(va);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), -1);
    EXPECT_EQ(node[1].as<int>(), -2);
    EXPECT_EQ(node[2].as<int>(), -3);
}

// Test encoding a valarray with zeros
TEST_F(ValarrayEncodeTest_617, EncodeZeroValues_617) {
    std::valarray<int> va = {0, 0, 0};
    YAML::Node node = YAML::convert<std::valarray<int>>::encode(va);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    for (std::size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(node[i].as<int>(), 0);
    }
}

// Test encoding a larger valarray
TEST_F(ValarrayEncodeTest_617, EncodeLargeValarray_617) {
    const std::size_t size = 1000;
    std::valarray<int> va(size);
    for (std::size_t i = 0; i < size; ++i) {
        va[i] = static_cast<int>(i);
    }
    YAML::Node node = YAML::convert<std::valarray<int>>::encode(va);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), size);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

// Test encoding a valarray of bools
TEST_F(ValarrayEncodeTest_617, EncodeBoolValarray_617) {
    std::valarray<bool> va = {true, false, true};
    YAML::Node node = YAML::convert<std::valarray<bool>>::encode(va);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<bool>(), true);
    EXPECT_EQ(node[1].as<bool>(), false);
    EXPECT_EQ(node[2].as<bool>(), true);
}

// Test that encoded node can be iterated
TEST_F(ValarrayEncodeTest_617, EncodeIterableResult_617) {
    std::valarray<int> va = {10, 20, 30};
    YAML::Node node = YAML::convert<std::valarray<int>>::encode(va);
    
    std::vector<int> result;
    for (auto it = node.begin(); it != node.end(); ++it) {
        result.push_back(it->as<int>());
    }
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 20);
    EXPECT_EQ(result[2], 30);
}

// Test encoding preserves order
TEST_F(ValarrayEncodeTest_617, EncodePreservesOrder_617) {
    std::valarray<int> va = {5, 3, 1, 4, 2};
    YAML::Node node = YAML::convert<std::valarray<int>>::encode(va);
    EXPECT_EQ(node.size(), 5u);
    EXPECT_EQ(node[0].as<int>(), 5);
    EXPECT_EQ(node[1].as<int>(), 3);
    EXPECT_EQ(node[2].as<int>(), 1);
    EXPECT_EQ(node[3].as<int>(), 4);
    EXPECT_EQ(node[4].as<int>(), 2);
}

// Test encoding valarray with unsigned int type
TEST_F(ValarrayEncodeTest_617, EncodeUnsignedIntValarray_617) {
    std::valarray<unsigned int> va = {0u, 100u, 4294967295u};
    YAML::Node node = YAML::convert<std::valarray<unsigned int>>::encode(va);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<unsigned int>(), 0u);
    EXPECT_EQ(node[1].as<unsigned int>(), 100u);
    EXPECT_EQ(node[2].as<unsigned int>(), 4294967295u);
}

// Test that the node is not null after encoding
TEST_F(ValarrayEncodeTest_617, EncodeResultIsNotNull_617) {
    std::valarray<int> va = {1};
    YAML::Node node = YAML::convert<std::valarray<int>>::encode(va);
    EXPECT_FALSE(node.IsNull());
    EXPECT_TRUE(node.IsDefined());
}

// Test encoding empty valarray results in defined sequence
TEST_F(ValarrayEncodeTest_617, EncodeEmptyValarrayIsDefined_617) {
    std::valarray<int> va;
    YAML::Node node = YAML::convert<std::valarray<int>>::encode(va);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_TRUE(node.IsSequence());
    EXPECT_FALSE(node.IsNull());
}
