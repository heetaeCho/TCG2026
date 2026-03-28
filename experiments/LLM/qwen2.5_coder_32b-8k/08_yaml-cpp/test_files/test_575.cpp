#include <gtest/gtest.h>

#include "yaml-cpp/node/impl.h"

#include "yaml-cpp/node/node.h"



namespace YAML {

class Node;

}



using namespace YAML;



TEST(NodeTest_575, RemoveExistingKey_NormalOperation_575) {

    Node mapNode = Load("{key1: value1, key2: value2}");

    Node keyToRemove = Load("key1");



    EXPECT_TRUE(mapNode.remove(keyToRemove));

    EXPECT_EQ(1u, mapNode.size());

    EXPECT_FALSE(mapNode["key1"]);

    EXPECT_TRUE(mapNode["key2"].IsDefined());

}



TEST(NodeTest_575, RemoveNonExistingKey_NormalOperation_575) {

    Node mapNode = Load("{key1: value1}");

    Node keyToRemove = Load("nonexistent");



    EXPECT_FALSE(mapNode.remove(keyToRemove));

    EXPECT_EQ(1u, mapNode.size());

    EXPECT_TRUE(mapNode["key1"].IsDefined());

}



TEST(NodeTest_575, RemoveFromEmptyMap_NormalOperation_575) {

    Node emptyMapNode;

    Node keyToRemove = Load("anyKey");



    EXPECT_FALSE(emptyMapNode.remove(keyToRemove));

    EXPECT_EQ(0u, emptyMapNode.size());

}



TEST(NodeTest_575, RemoveAllKeys_NormalOperation_575) {

    Node mapNode = Load("{key1: value1, key2: value2}");

    Node key1 = Load("key1");

    Node key2 = Load("key2");



    EXPECT_TRUE(mapNode.remove(key1));

    EXPECT_TRUE(mapNode.remove(key2));

    EXPECT_EQ(0u, mapNode.size());

}



TEST(NodeTest_575, RemoveKeyWithInvalidNode_ExceptionalCase_575) {

    Node mapNode = Load("{key1: value1}");

    Node invalidNode;



    EXPECT_FALSE(mapNode.remove(invalidNode));

    EXPECT_EQ(1u, mapNode.size());

    EXPECT_TRUE(mapNode["key1"].IsDefined());

}



TEST(NodeTest_575, RemoveKeyFromNonMapNode_ExceptionalCase_575) {

    Node scalarNode = Load("scalarValue");

    Node keyToRemove = Load("anyKey");



    EXPECT_FALSE(scalarNode.remove(keyToRemove));

    EXPECT_TRUE(scalarNode.IsScalar());

    EXPECT_EQ("scalarValue", scalarNode.Scalar());

}
