#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/src/nodeevents.h"

#include "yaml-cpp/node/detail/node.h"



using namespace YAML;



class AliasManagerTest_264 : public ::testing::Test {

protected:

    NodeEvents::AliasManager aliasManager;

    detail::node node1;

    detail::node node2;

};



TEST_F(AliasManagerTest_264, RegisterReference_SingleNode_264) {

    aliasManager.RegisterReference(node1);

    EXPECT_NE(aliasManager.LookupAnchor(node1), 0);

}



TEST_F(AliasManagerTest_264, RegisterReference_MultipleNodes_264) {

    aliasManager.RegisterReference(node1);

    aliasManager.RegisterReference(node2);



    EXPECT_NE(aliasManager.LookupAnchor(node1), 0);

    EXPECT_NE(aliasManager.LookupAnchor(node2), 0);

    EXPECT_NE(aliasManager.LookupAnchor(node1), aliasManager.LookupAnchor(node2));

}



TEST_F(AliasManagerTest_264, RegisterReference_SameNodeTwice_264) {

    aliasManager.RegisterReference(node1);

    anchor_t firstAnchor = aliasManager.LookupAnchor(node1);



    aliasManager.RegisterReference(node1);

    anchor_t secondAnchor = aliasManager.LookupAnchor(node1);



    EXPECT_EQ(firstAnchor, secondAnchor);

}



TEST_F(AliasManagerTest_264, LookupAnchor_UnregisteredNode_264) {

    EXPECT_EQ(aliasManager.LookupAnchor(node1), 0);

}
