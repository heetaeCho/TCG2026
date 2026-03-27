#include <gtest/gtest.h>

#include "yaml-cpp/node/impl.h"

#include "yaml-cpp/node/node.h"



using namespace YAML;



class NodeTest_564 : public ::testing::Test {

protected:

    Node node1;

    Node node2;

};



TEST_F(NodeTest_564, SelfAssignmentDoesNotChangeNode_564) {

    Node& result = node1 = node1;

    EXPECT_EQ(&result, &node1);

}



TEST_F(NodeTest_564, AssignmentToDifferentNodeChangesState_564) {

    node2 = 42; // Assuming YAML::Node can be assigned from an integer

    Node& result = node1 = node2;

    EXPECT_EQ(&result, &node1);

    EXPECT_TRUE(node1.is(node2));

}



TEST_F(NodeTest_564, AssignmentFromSameTypePreservesType_564) {

    node1 = "hello"; // Assuming YAML::Node can be assigned from a string

    node2 = "world";

    Node& result = node1 = node2;

    EXPECT_EQ(node1.Type(), NodeType::Scalar);

}



TEST_F(NodeTest_564, AssignmentFromDifferentTypeChangesType_564) {

    node1 = 3.14; // Assuming YAML::Node can be assigned from a double

    node2 = "string";

    Node& result = node1 = node2;

    EXPECT_EQ(node1.Type(), NodeType::Scalar);

}



TEST_F(NodeTest_564, AssignmentPreservesDefinedState_564) {

    node1.reset(node2); // Assuming reset sets node1 to an undefined state

    node2 = 10; // Make node2 defined

    Node& result = node1 = node2;

    EXPECT_TRUE(result.IsDefined());

}



TEST_F(NodeTest_564, AssignmentOfUndefinedNodeResultsInUndefinedNode_564) {

    node1.reset(node2); // Assuming reset sets node1 to an undefined state

    Node& result = node2 = node1;

    EXPECT_FALSE(result.IsDefined());

}
