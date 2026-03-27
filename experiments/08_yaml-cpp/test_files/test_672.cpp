#include <gtest/gtest.h>

#include "yaml-cpp/node/node.h"

#include <iostream>

#include <string>



using namespace YAML;



class NodeTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(NodeTest_672, BasicScalarAccess_672) {

    Node root = "Hello";

    EXPECT_EQ(root.as<std::string>(), "Hello");

}



TEST_F(NodeTest_672, SequenceCreationAndAccess_672) {

    Node seq = YAML::Sequence();

    seq.push_back(0);

    seq[2] = "two";

    EXPECT_EQ(seq[0].as<int>(), 0);

    EXPECT_TRUE(seq[1].IsNull());

    EXPECT_EQ(seq[2].as<std::string>(), "two");

}



TEST_F(NodeTest_672, MapCreationAndAccess_672) {

    Node map;

    map[3] = 1;

    EXPECT_EQ(map[3].as<int>(), 1);

}



TEST_F(NodeTest_672, SequenceAliasBehavior_672) {

    Node root = YAML::Sequence();

    root.push_back(0);

    Node other = root;

    other[0] = 5;

    EXPECT_EQ(root[0].as<int>(), 0); // Root should remain unchanged

}



TEST_F(NodeTest_672, MapToSequenceConversionError_672) {

    Node node;

    node[0] = 1;

    node["key"] = 5;

    try {

        node.push_back(10);

        FAIL() << "Expected an exception due to invalid operation";

    } catch (...) {

        SUCCEED(); // Exception was thrown as expected

    }

}



TEST_F(NodeTest_672, NodeResetAndReassignment_672) {

    Node root = YAML::Parse("test.yaml");

    root[0].reset();

    root[0]["key"] = "value";

    EXPECT_EQ(root[0]["key"].as<std::string>(), "value");

}



TEST_F(NodeTest_672, SelfReferencingNode_672) {

    Node node;

    node[0] = node;

    EXPECT_TRUE(node[0].is(node));

}



TEST_F(NodeTest_672, ScalarToSequenceConversion_672) {

    Node root;

    root.push_back("zero");

    root.push_back("one");

    root.push_back("two");

    Node two = root[2];

    root = "scalar";

    EXPECT_EQ(two.as<std::string>(), "two"); // 'two' is still "two", even though 'root' is "scalar"

}



TEST_F(NodeTest_672, NestedNodeAssignment_672) {

    Node root;

    Node subnode = root["key"];

    subnode = "value";

    Node subnode2 = node["key2"];

    node["key3"] = subnode2;

    subnode2 = "monkey";

    EXPECT_EQ(root["key"].as<std::string>(), "value");

    EXPECT_TRUE(root["key2"].is(root["key3"]));

}



TEST_F(NodeTest_672, SequenceSelfAliasing_672) {

    Node seq = YAML::Sequence();

    seq[0] = "zero";

    seq[1] = seq[0];

    seq[0] = seq[1];

    EXPECT_TRUE(seq[0].is(seq[1]));

}



TEST_F(NodeTest_672, AccessNonExistentKeyThrows_672) {

    Node root = YAML::Parse("test.yaml");

    try {

        std::cout << root[1]["odds"][6].as<int>();

        FAIL() << "Expected an exception due to non-existent key";

    } catch (...) {

        SUCCEED(); // Exception was thrown as expected

    }

}
