#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;



class NodeDataTest_649 : public ::testing::Test {

protected:

    node_data data;

};



TEST_F(NodeDataTest_649, EndReturnsEmptyIteratorWhenUndefined_649) {

    EXPECT_EQ(data.end(), const_node_iterator{});

}



TEST_F(NodeDataTest_649, EndReturnsCorrectSequenceEndIterator_649) {

    data.set_type(NodeType::Sequence);

    data.mark_defined();

    EXPECT_NE(data.end(), const_node_iterator{});

}



TEST_F(NodeDataTest_649, EndReturnsCorrectMapEndIterator_649) {

    data.set_type(NodeType::Map);

    data.mark_defined();

    EXPECT_NE(data.end(), const_node_iterator{});

}



TEST_F(NodeDataTest_649, EndReturnsEmptyIteratorForUnknownTypes_649) {

    data.set_type(static_cast<NodeType::value>(-1));

    data.mark_defined();

    EXPECT_EQ(data.end(), const_node_iterator{});

}
