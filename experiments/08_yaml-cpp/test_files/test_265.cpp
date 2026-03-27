#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/src/nodeevents.h"

#include "yaml-cpp/node/detail/node.h"



using namespace YAML::detail;

using namespace YAML;



class AliasManagerTest_265 : public ::testing::Test {

protected:

    AliasManager alias_manager;

    node test_node1, test_node2;

};



TEST_F(AliasManagerTest_265, LookupAnchor_NewNode_ReturnsZero_265) {

    anchor_t result = alias_manager.LookupAnchor(test_node1);

    EXPECT_EQ(result, 0);

}



TEST_F(AliasManagerTest_265, RegisterReference_LookupAnchor_ReturnsNonZero_265) {

    alias_manager.RegisterReference(test_node1);

    anchor_t result = alias_manager.LookupAnchor(test_node1);

    EXPECT_NE(result, 0);

}



TEST_F(AliasManagerTest_265, LookupAnchor_DifferentNodes_ReturnDifferentAnchors_265) {

    alias_manager.RegisterReference(test_node1);

    alias_manager.RegisterReference(test_node2);



    anchor_t result1 = alias_manager.LookupAnchor(test_node1);

    anchor_t result2 = alias_manager.LookupAnchor(test_node2);



    EXPECT_NE(result1, 0);

    EXPECT_NE(result2, 0);

    EXPECT_NE(result1, result2);

}



TEST_F(AliasManagerTest_265, LookupAnchor_SameNode_MultipleTimes_ReturnsSameAnchor_265) {

    alias_manager.RegisterReference(test_node1);

    anchor_t result1 = alias_manager.LookupAnchor(test_node1);

    anchor_t result2 = alias_manager.LookupAnchor(test_node1);



    EXPECT_NE(result1, 0);

    EXPECT_EQ(result1, result2);

}



TEST_F(AliasManagerTest_265, LookupAnchor_UnregisteredNode_ReturnsZero_265) {

    alias_manager.RegisterReference(test_node1);

    node unregistered_node;

    anchor_t result = alias_manager.LookupAnchor(unregistered_node);

    EXPECT_EQ(result, 0);

}
