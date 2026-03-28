#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <list>
#include <string>
#include <vector>

// Test encoding an empty list
TEST(ConvertListTest_613, EncodeEmptyList_613) {
    std::list<int> emptyList;
    YAML::Node node = YAML::convert<std::list<int>>::encode(emptyList);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 0u);
}

// Test encoding a list with a single integer element
TEST(ConvertListTest_613, EncodeSingleElementIntList_613) {
    std::list<int> singleList = {42};
    YAML::Node node = YAML::convert<std::list<int>>::encode(singleList);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node[0].as<int>(), 42);
}

// Test encoding a list with multiple integer elements
TEST(ConvertListTest_613, EncodeMultipleElementIntList_613) {
    std::list<int> intList = {1, 2, 3, 4, 5};
    YAML::Node node = YAML::convert<std::list<int>>::encode(intList);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 5u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
    EXPECT_EQ(node[3].as<int>(), 4);
    EXPECT_EQ(node[4].as<int>(), 5);
}

// Test encoding a list of strings
TEST(ConvertListTest_613, EncodeStringList_613) {
    std::list<std::string> strList = {"hello", "world", "yaml"};
    YAML::Node node = YAML::convert<std::list<std::string>>::encode(strList);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<std::string>(), "hello");
    EXPECT_EQ(node[1].as<std::string>(), "world");
    EXPECT_EQ(node[2].as<std::string>(), "yaml");
}

// Test encoding a list of doubles
TEST(ConvertListTest_613, EncodeDoubleList_613) {
    std::list<double> dblList = {1.1, 2.2, 3.3};
    YAML::Node node = YAML::convert<std::list<double>>::encode(dblList);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_DOUBLE_EQ(node[0].as<double>(), 1.1);
    EXPECT_DOUBLE_EQ(node[1].as<double>(), 2.2);
    EXPECT_DOUBLE_EQ(node[2].as<double>(), 3.3);
}

// Test that the encoded node type is Sequence
TEST(ConvertListTest_613, EncodedNodeTypeIsSequence_613) {
    std::list<int> intList = {10, 20};
    YAML::Node node = YAML::convert<std::list<int>>::encode(intList);
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

// Test encoding preserves order of elements
TEST(ConvertListTest_613, EncodePreservesOrder_613) {
    std::list<int> intList = {100, 50, 200, 25, 75};
    YAML::Node node = YAML::convert<std::list<int>>::encode(intList);
    EXPECT_EQ(node.size(), 5u);
    EXPECT_EQ(node[0].as<int>(), 100);
    EXPECT_EQ(node[1].as<int>(), 50);
    EXPECT_EQ(node[2].as<int>(), 200);
    EXPECT_EQ(node[3].as<int>(), 25);
    EXPECT_EQ(node[4].as<int>(), 75);
}

// Test encoding a list with negative integers
TEST(ConvertListTest_613, EncodeNegativeIntList_613) {
    std::list<int> intList = {-1, -2, -3};
    YAML::Node node = YAML::convert<std::list<int>>::encode(intList);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), -1);
    EXPECT_EQ(node[1].as<int>(), -2);
    EXPECT_EQ(node[2].as<int>(), -3);
}

// Test encoding a list of booleans
TEST(ConvertListTest_613, EncodeBoolList_613) {
    std::list<bool> boolList = {true, false, true};
    YAML::Node node = YAML::convert<std::list<bool>>::encode(boolList);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<bool>(), true);
    EXPECT_EQ(node[1].as<bool>(), false);
    EXPECT_EQ(node[2].as<bool>(), true);
}

// Test encoding a large list
TEST(ConvertListTest_613, EncodeLargeList_613) {
    std::list<int> largeList;
    for (int i = 0; i < 1000; ++i) {
        largeList.push_back(i);
    }
    YAML::Node node = YAML::convert<std::list<int>>::encode(largeList);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

// Test encoding a list with duplicate values
TEST(ConvertListTest_613, EncodeDuplicateValues_613) {
    std::list<int> dupList = {5, 5, 5, 5};
    YAML::Node node = YAML::convert<std::list<int>>::encode(dupList);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 4u);
    for (std::size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(node[i].as<int>(), 5);
    }
}

// Test encoding a list of empty strings
TEST(ConvertListTest_613, EncodeEmptyStringList_613) {
    std::list<std::string> strList = {"", "", ""};
    YAML::Node node = YAML::convert<std::list<std::string>>::encode(strList);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<std::string>(), "");
    EXPECT_EQ(node[1].as<std::string>(), "");
    EXPECT_EQ(node[2].as<std::string>(), "");
}

// Test that encoded node can be iterated
TEST(ConvertListTest_613, EncodeIterableResult_613) {
    std::list<int> intList = {10, 20, 30};
    YAML::Node node = YAML::convert<std::list<int>>::encode(intList);
    
    std::vector<int> result;
    for (auto it = node.begin(); it != node.end(); ++it) {
        result.push_back(it->as<int>());
    }
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 20);
    EXPECT_EQ(result[2], 30);
}

// Test round-trip: encode then decode back to list
TEST(ConvertListTest_613, RoundTripIntList_613) {
    std::list<int> original = {7, 14, 21, 28};
    YAML::Node node = YAML::convert<std::list<int>>::encode(original);
    
    std::list<int> decoded = node.as<std::list<int>>();
    EXPECT_EQ(original, decoded);
}

// Test round-trip with string list
TEST(ConvertListTest_613, RoundTripStringList_613) {
    std::list<std::string> original = {"foo", "bar", "baz"};
    YAML::Node node = YAML::convert<std::list<std::string>>::encode(original);
    
    std::list<std::string> decoded = node.as<std::list<std::string>>();
    EXPECT_EQ(original, decoded);
}

// Test encoding a list with a single zero element
TEST(ConvertListTest_613, EncodeSingleZeroElement_613) {
    std::list<int> zeroList = {0};
    YAML::Node node = YAML::convert<std::list<int>>::encode(zeroList);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node[0].as<int>(), 0);
}

// Test that encoded node is not null
TEST(ConvertListTest_613, EncodedNodeIsNotNull_613) {
    std::list<int> intList = {1};
    YAML::Node node = YAML::convert<std::list<int>>::encode(intList);
    EXPECT_FALSE(node.IsNull());
    EXPECT_TRUE(node.IsDefined());
}

// Test encoding an empty list results in a defined sequence node
TEST(ConvertListTest_613, EmptyListNodeIsDefined_613) {
    std::list<int> emptyList;
    YAML::Node node = YAML::convert<std::list<int>>::encode(emptyList);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_TRUE(node.IsSequence());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsMap());
}
