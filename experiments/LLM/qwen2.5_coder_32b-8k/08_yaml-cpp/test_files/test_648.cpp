#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;



class NodeDataTest_648 : public ::testing::Test {

protected:

    node_data data;

};



TEST_F(NodeDataTest_648, BeginReturnsEndWhenNotDefined_648) {

    EXPECT_EQ(data.begin(), data.end());

}



TEST_F(NodeDataTest_648, BeginReturnsSequenceBeginWhenTypeIsSequence_648) {

    data.set_type(NodeType::Sequence);

    data.mark_defined();

    EXPECT_NE(data.begin(), data.end());

}



TEST_F(NodeDataTest_648, BeginReturnsMapBeginWhenTypeIsMap_648) {

    data.set_type(NodeType::Map);

    data.mark_defined();

    EXPECT_NE(data.begin(), data.end());

}



TEST_F(NodeDataTest_648, BeginReturnsEmptyIteratorForUnknownTypes_648) {

    data.set_type(static_cast<NodeType::value>(-1)); // Assuming an invalid type

    data.mark_defined();

    EXPECT_EQ(data.begin(), data.end());

}
