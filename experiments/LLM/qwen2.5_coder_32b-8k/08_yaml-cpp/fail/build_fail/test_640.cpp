#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;



class NodeDataTest_640 : public ::testing::Test {

protected:

    node_data data;

};



TEST_F(NodeDataTest_640, IsDefinedInitiallyFalse_640) {

    EXPECT_FALSE(data.is_defined());

}



TEST_F(NodeDataTest_640, MarkDefinedSetsIsDefinedToTrue_640) {

    data.mark_defined();

    EXPECT_TRUE(data.is_defined());

}



TEST_F(NodeDataTest_640, MarkDefinedDoesNotChangeTypeIfAlreadyDefined_640) {

    data.set_type(NodeType::Scalar);

    data.mark_defined();

    EXPECT_EQ(data.type(), NodeType::Scalar);

}



TEST_F(NodeDataTest_640, MarkDefinedChangesUndefinedToNull_640) {

    node_data undefinedNode;

    EXPECT_EQ(undefinedNode.type(), NodeType::Null);

    undefinedNode.mark_defined();

    EXPECT_EQ(undefinedNode.type(), NodeType::Null);

}



TEST_F(NodeDataTest_640, SetTypeAndMarkDefinedRetainsType_640) {

    data.set_type(NodeType::Map);

    data.mark_defined();

    EXPECT_EQ(data.type(), NodeType::Map);

}
