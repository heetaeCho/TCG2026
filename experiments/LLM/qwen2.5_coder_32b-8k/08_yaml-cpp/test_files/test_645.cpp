#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;



class NodeDataTest : public ::testing::Test {

protected:

    node_data data;

};



TEST_F(NodeDataTest_645, InitiallyUndefined_645) {

    EXPECT_FALSE(data.is_defined());

}



TEST_F(NodeDataTest_645, SetNull_MarksDefined_645) {

    data.set_null();

    EXPECT_TRUE(data.is_defined());

}



TEST_F(NodeDataTest_645, SetNull_SetsTypeToNull_645) {

    data.set_null();

    EXPECT_EQ(data.type(), NodeType::Null);

}



TEST_F(NodeDataTest_645, SetTag_MarksDefined_645) {

    data.set_tag("test_tag");

    EXPECT_TRUE(data.is_defined());

}



TEST_F(NodeDataTest_645, SetTag_SetsCorrectTag_645) {

    data.set_tag("test_tag");

    EXPECT_EQ(data.tag(), "test_tag");

}



TEST_F(NodeDataTest_645, SetScalar_MarksDefined_645) {

    data.set_scalar("test_scalar");

    EXPECT_TRUE(data.is_defined());

}



TEST_F(NodeDataTest_645, SetScalar_SetsCorrectScalar_645) {

    data.set_scalar("test_scalar");

    EXPECT_EQ(data.scalar(), "test_scalar");

}



TEST_F(NodeDataTest_645, SetType_MarksDefined_645) {

    data.set_type(NodeType::Sequence);

    EXPECT_TRUE(data.is_defined());

}



TEST_F(NodeDataTest_645, SetType_SetsCorrectType_645) {

    data.set_type(NodeType::Sequence);

    EXPECT_EQ(data.type(), NodeType::Sequence);

}



TEST_F(NodeDataTest_645, MarkDefined_MarksAsDefined_645) {

    data.mark_defined();

    EXPECT_TRUE(data.is_defined());

}
