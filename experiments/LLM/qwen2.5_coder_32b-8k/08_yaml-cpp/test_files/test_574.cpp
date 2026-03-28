#include <gtest/gtest.h>

#include "yaml-cpp/node/impl.h"

#include "yaml-cpp/node/node.h"



using namespace YAML;



// Fixture for Node tests

class NodeTest_574 : public ::testing::Test {

protected:

    Node root;

};



// Test normal operation with existing key

TEST_F(NodeTest_574, OperatorBracketExistingKey_574) {

    root["key1"] = "value1";

    Node node = root["key1"];

    EXPECT_TRUE(node.IsDefined());

    EXPECT_EQ(node.as<std::string>(), "value1");

}



// Test normal operation with non-existing key

TEST_F(NodeTest_574, OperatorBracketNonExistingKey_574) {

    Node node = root["nonexistent_key"];

    EXPECT_FALSE(node.IsDefined());

}



// Test boundary condition with empty string as key

TEST_F(NodeTest_574, OperatorBracketEmptyStringKey_574) {

    root[""] = "value_empty";

    Node node = root[Node("")];

    EXPECT_TRUE(node.IsDefined());

    EXPECT_EQ(node.as<std::string>(), "value_empty");

}



// Test boundary condition with integer key

TEST_F(NodeTest_574, OperatorBracketIntegerKey_574) {

    root["123"] = "value_int";

    Node node = root[Node(123)];

    EXPECT_TRUE(node.IsDefined());

    EXPECT_EQ(node.as<std::string>(), "value_int");

}



// Test boundary condition with float key

TEST_F(NodeTest_574, OperatorBracketFloatKey_574) {

    root["3.14"] = "value_float";

    Node node = root[Node(3.14)];

    EXPECT_TRUE(node.IsDefined());

    EXPECT_EQ(node.as<std::string>(), "value_float");

}



// Test exceptional case with null key

TEST_F(NodeTest_574, OperatorBracketNullKey_574) {

    Node nullNode;

    Node node = root[nullNode];

    EXPECT_FALSE(node.IsDefined());

}



// Test verification of external interactions (not applicable here as no mocks are needed)

```


