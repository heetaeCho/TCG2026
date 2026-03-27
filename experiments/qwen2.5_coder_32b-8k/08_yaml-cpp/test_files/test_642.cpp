#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;



class NodeDataTest_642 : public ::testing::Test {

protected:

    node_data data;

};



TEST_F(NodeDataTest_642, SetTypeUndefined_SetsIsDefinedFalse_642) {

    data.set_type(NodeType::Undefined);

    EXPECT_FALSE(data.is_defined());

}



TEST_F(NodeDataTest_642, SetTypeNull_IsDefinedTrueAndTypeNull_642) {

    data.set_type(NodeType::Null);

    EXPECT_TRUE(data.is_defined());

    EXPECT_EQ(data.type(), NodeType::Null);

}



TEST_F(NodeDataTest_642, SetTypeScalar_IsDefinedTrueAndTypeScalar_642) {

    data.set_type(NodeType::Scalar);

    EXPECT_TRUE(data.is_defined());

    EXPECT_EQ(data.type(), NodeType::Scalar);

}



TEST_F(NodeDataTest_642, SetTypeSequence_IsDefinedTrueAndTypeSequence_642) {

    data.set_type(NodeType::Sequence);

    EXPECT_TRUE(data.is_defined());

    EXPECT_EQ(data.type(), NodeType::Sequence);

}



TEST_F(NodeDataTest_642, SetTypeMap_IsDefinedTrueAndTypeMap_642) {

    data.set_type(NodeType::Map);

    EXPECT_TRUE(data.is_defined());

    EXPECT_EQ(data.type(), NodeType::Map);

}



TEST_F(NodeDataTest_642, SetSameTypeTwice_NoChange_642) {

    data.set_type(NodeType::Scalar);

    auto initial_type = data.type();

    data.set_type(initial_type);

    EXPECT_EQ(data.type(), initial_type);

}
