#include <gtest/gtest.h>

#include "yaml-cpp/node/impl.h"



using namespace YAML;



class NodeTest_573 : public ::testing::Test {

protected:

    Node node;

};



TEST_F(NodeTest_573, RemoveNonExistentKey_ReturnsFalse_573) {

    EXPECT_FALSE(node.remove("non_existent_key"));

}



TEST_F(NodeTest_573, RemoveExistingKey_ReturnsTrue_573) {

    // Assuming the node is populated with some data

    node["key"] = "value";

    EXPECT_TRUE(node.remove("key"));

}



TEST_F(NodeTest_573, RemoveAfterRemoval_ReturnsFalse_573) {

    node["key"] = "value";

    node.remove("key");

    EXPECT_FALSE(node.remove("key"));

}



TEST_F(NodeTest_573, RemoveEmptyStringKey_ReturnsFalse_573) {

    EXPECT_FALSE(node.remove(""));

}



TEST_F(NodeTest_573, RemoveNullNode_ReturnsFalse_573) {

    Node nullNode;

    EXPECT_FALSE(nullNode.remove("key"));

}
