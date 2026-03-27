#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"

#include "yaml-cpp/node/detail/memory.h"



using namespace YAML::detail;



class NodeDataTest_652 : public ::testing::Test {

protected:

    node_data nd;

    shared_memory_holder pMemory;

    node key1, key2;

    node value1, value2;



    void SetUp() override {

        pMemory = std::make_shared<memory>();

        key1.set_scalar("key1");

        key2.set_scalar("key2");

        value1.set_scalar("value1");

        value2.set_scalar("value2");

    }

};



TEST_F(NodeDataTest_652, GetUndefinedConvertsToMap_652) {

    nd.set_type(NodeType::Undefined);

    node& result = nd.get(key1, pMemory);

    EXPECT_EQ(nd.type(), NodeType::Map);

}



TEST_F(NodeDataTest_652, GetNullConvertsToMap_652) {

    nd.set_type(NodeType::Null);

    node& result = nd.get(key1, pMemory);

    EXPECT_EQ(nd.type(), NodeType::Map);

}



TEST_F(NodeDataTest_652, GetSequenceConvertsToMap_652) {

    nd.set_type(NodeType::Sequence);

    node& result = nd.get(key1, pMemory);

    EXPECT_EQ(nd.type(), NodeType::Map);

}



TEST_F(NodeDataTest_652, GetScalarThrowsBadSubscript_652) {

    nd.set_type(NodeType::Scalar);

    EXPECT_THROW(nd.get(key1, pMemory), BadSubscript);

}



TEST_F(NodeDataTest_652, GetExistingKeyReturnsCorrectValue_652) {

    nd.set_type(NodeType::Map);

    nd.insert_map_pair(key1, value1);

    node& result = nd.get(key1, pMemory);

    EXPECT_EQ(&result, &value1);

}



TEST_F(NodeDataTest_652, GetNonExistingKeyCreatesNewNode_652) {

    nd.set_type(NodeType::Map);

    node& result = nd.get(key1, pMemory);

    EXPECT_NE(&result, nullptr);

    EXPECT_TRUE(result.is_defined());

}
