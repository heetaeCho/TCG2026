#include <gtest/gtest.h>

#include "yaml-cpp/node/impl.h"



using namespace YAML;



class NodeTest_576 : public ::testing::Test {

protected:

    Node node;

};



TEST_F(NodeTest_576, ForceInsertValidKeyAndValue_576) {

    node.force_insert("key", "value");

    EXPECT_EQ(node["key"].as<std::string>(), "value");

}



TEST_F(NodeTest_576, ForceInsertEmptyStringAsKey_576) {

    node.force_insert("", "value");

    EXPECT_EQ(node[""].as<std::string>(), "value");

}



TEST_F(NodeTest_576, ForceInsertEmptyStringAsValue_576) {

    node.force_insert("key", "");

    EXPECT_EQ(node["key"].as<std::string>(), "");

}



TEST_F(NodeTest_576, ForceInsertExistingKeyUpdatesValue_576) {

    node.force_insert("key", "initial_value");

    node.force_insert("key", "updated_value");

    EXPECT_EQ(node["key"].as<std::string>(), "updated_value");

}



TEST_F(NodeTest_576, ForceInsertNonStringTypes_576) {

    node.force_insert("int_key", 42);

    node.force_insert("double_key", 3.14);

    node.force_insert("bool_key", true);



    EXPECT_EQ(node["int_key"].as<int>(), 42);

    EXPECT_EQ(node["double_key"].as<double>(), 3.14);

    EXPECT_EQ(node["bool_key"].as<bool>(), true);

}



TEST_F(NodeTest_576, ForceInsertAfterReset_576) {

    node.force_insert("key", "value");

    node.reset(Node());

    node.force_insert("new_key", "new_value");



    EXPECT_EQ(node.size(), 1u);

    EXPECT_EQ(node["new_key"].as<std::string>(), "new_value");

}



TEST_F(NodeTest_576, ForceInsertNullNode_576) {

    Node null_node;

    node.force_insert("null_key", null_node);



    EXPECT_TRUE(node["null_key"].IsNull());

}
