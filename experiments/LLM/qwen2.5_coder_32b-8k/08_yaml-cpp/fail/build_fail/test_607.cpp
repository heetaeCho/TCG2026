#include "gtest/gtest.h"

#include "yaml-cpp/node/convert.h"



using namespace YAML;



TEST_F(YamlNodeEncodeTest_607, EncodeEmptyMap_ReturnsValidNode_607) {

    std::map<std::string, int> emptyMap;

    Node node = encode(emptyMap);

    EXPECT_TRUE(node.IsDefined());

    EXPECT_EQ(NodeType::Map, node.Type());

}



TEST_F(YamlNodeEncodeTest_607, EncodeNonEmptyMap_ReturnsValidNodeWithElements_607) {

    std::map<std::string, int> map = {{"key1", 1}, {"key2", 2}};

    Node node = encode(map);

    EXPECT_TRUE(node.IsDefined());

    EXPECT_EQ(NodeType::Map, node.Type());

    EXPECT_EQ(2, node.size());

    EXPECT_EQ(1, node["key1"].as<int>());

    EXPECT_EQ(2, node["key2"].as<int>());

}



TEST_F(YamlNodeEncodeTest_607, EncodeMapWithSingleElement_ReturnsValidNodeWithOneElement_607) {

    std::map<std::string, int> map = {{"singleKey", 42}};

    Node node = encode(map);

    EXPECT_TRUE(node.IsDefined());

    EXPECT_EQ(NodeType::Map, node.Type());

    EXPECT_EQ(1, node.size());

    EXPECT_EQ(42, node["singleKey"].as<int>());

}



TEST_F(YamlNodeEncodeTest_607, EncodeMapWithDuplicateKeys_LastValueIsInserted_607) {

    std::map<std::string, int> map = {{"key", 1}, {"key", 2}};

    Node node = encode(map);

    EXPECT_TRUE(node.IsDefined());

    EXPECT_EQ(NodeType::Map, node.Type());

    EXPECT_EQ(1, node.size());

    EXPECT_EQ(2, node["key"].as<int>());

}



TEST_F(YamlNodeEncodeTest_607, EncodeMapWithDifferentTypes_ReturnsValidNodeWithMixedTypes_607) {

    std::map<std::string, Node> map = {{"intKey", Node(42)}, {"stringKey", Node("value")}};

    Node node = encode(map);

    EXPECT_TRUE(node.IsDefined());

    EXPECT_EQ(NodeType::Map, node.Type());

    EXPECT_EQ(2, node.size());

    EXPECT_EQ(42, node["intKey"].as<int>());

    EXPECT_EQ("value", node["stringKey"].as<std::string>());

}
