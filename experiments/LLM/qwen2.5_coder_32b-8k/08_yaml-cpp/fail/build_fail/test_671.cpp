#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/impl.h"

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;

using ::testing::_;

using ::testing::Return;



class NodeDataTest : public ::testing::Test {

protected:

    shared_memory_holder pMemory = std::make_shared<node>(); // Mock or placeholder

    node_data nd;

};



TEST_F(NodeDataTest_671, ForceInsertConvertsUndefinedToMap_671) {

    nd.set_type(NodeType::Undefined);

    EXPECT_NO_THROW(nd.force_insert("key", "value", pMemory));

    EXPECT_EQ(nd.type(), NodeType::Map);

}



TEST_F(NodeDataTest_671, ForceInsertConvertsNullToMap_671) {

    nd.set_type(NodeType::Null);

    EXPECT_NO_THROW(nd.force_insert("key", "value", pMemory));

    EXPECT_EQ(nd.type(), NodeType::Map);

}



TEST_F(NodeDataTest_671, ForceInsertConvertsSequenceToMap_671) {

    nd.set_type(NodeType::Sequence);

    EXPECT_NO_THROW(nd.force_insert("key", "value", pMemory));

    EXPECT_EQ(nd.type(), NodeType::Map);

}



TEST_F(NodeDataTest_671, ForceInsertThrowsOnScalar_671) {

    nd.set_type(NodeType::Scalar);

    EXPECT_THROW(nd.force_insert("key", "value", pMemory), BadInsert);

}



TEST_F(NodeDataTest_671, ForceInsertDoesNothingOnMap_671) {

    nd.set_type(NodeType::Map);

    EXPECT_NO_THROW(nd.force_insert("key", "value", pMemory));

    EXPECT_EQ(nd.type(), NodeType::Map);

}
