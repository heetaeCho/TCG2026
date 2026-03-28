#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/convert.h"

#include "yaml-cpp/node/node.h"



using namespace YAML;

using ::testing::ElementsAre;



class DecodeMapTest_608 : public ::testing::Test {

protected:

    Node node;

    std::map<std::string, int> map;



    void SetUp() override {

        // Initialize the node as a map for testing

        node = Node(NodeType::Map);

    }

};



TEST_F(DecodeMapTest_608, DecodeEmptyMap_608) {

    bool result = decode(node, map);

    EXPECT_TRUE(result);

    EXPECT_TRUE(map.empty());

}



TEST_F(DecodeMapTest_608, DecodeNonEmptyMap_608) {

    node.force_insert("key1", 1);

    node.force_insert("key2", 2);



    bool result = decode(node, map);

    EXPECT_TRUE(result);

    EXPECT_THAT(map, ElementsAre(std::make_pair("key1", 1), std::make_pair("key2", 2)));

}



TEST_F(DecodeMapTest_608, DecodeNonMapNode_608) {

    node = Node(NodeType::Scalar); // Change node type to Scalar

    bool result = decode(node, map);

    EXPECT_FALSE(result);

}



TEST_F(DecodeMapTest_608, DecodeMapWithInvalidKey_608) {

    node.force_insert("key1", 1);

    node.force_insert("", 2); // Invalid key



    bool result = decode(node, map);

    EXPECT_TRUE(result);

    EXPECT_THAT(map, ElementsAre(std::make_pair("key1", 1))); // Only valid key should be present

}



TEST_F(DecodeMapTest_608, DecodeMapWithInvalidValue_608) {

    node.force_insert("key1", "invalid_value"); // Invalid value type



    bool result = decode(node, map);

    EXPECT_TRUE(result);

    EXPECT_TRUE(map.empty()); // No valid entries should be present

}



TEST_F(DecodeMapTest_608, DecodeMapWithMixedTypes_608) {

    node.force_insert("key1", 1);

    node.force_insert("key2", "invalid_value"); // Invalid value type



    bool result = decode(node, map);

    EXPECT_TRUE(result);

    EXPECT_THAT(map, ElementsAre(std::make_pair("key1", 1))); // Only valid entries should be present

}
