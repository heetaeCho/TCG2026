#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"



using YAML::detail::node_data;



class NodeDataTest_205 : public ::testing::Test {

protected:

    node_data data;

};



TEST_F(NodeDataTest_205, IsDefinedInitiallyFalse_205) {

    EXPECT_FALSE(data.is_defined());

}



TEST_F(NodeDataTest_205, MarkDefinedChangesIsDefinedToTrue_205) {

    data.mark_defined();

    EXPECT_TRUE(data.is_defined());

}



TEST_F(NodeDataTest_205, SetTypeAndGetCorrectType_205) {

    NodeType::value type = NodeType::Scalar;

    data.set_type(type);

    EXPECT_EQ(data.type(), type);

}



TEST_F(NodeDataTest_205, SetTagAndGetCorrectTag_205) {

    std::string tag = "test_tag";

    data.set_tag(tag);

    EXPECT_EQ(data.tag(), tag);

}



TEST_F(NodeDataTest_205, SetStyleAndGetCorrectStyle_205) {

    EmitterStyle::value style = EmitterStyle::Flow;

    data.set_style(style);

    EXPECT_EQ(data.style(), style);

}



TEST_F(NodeDataTest_205, SetScalarAndGetCorrectScalar_205) {

    std::string scalar = "test_scalar";

    data.set_scalar(scalar);

    EXPECT_EQ(data.scalar(), scalar);

}



TEST_F(NodeDataTest_205, SetNullTypeAndGetTypeAsNull_205) {

    data.set_null();

    EXPECT_EQ(data.type(), NodeType::Null);

}



TEST_F(NodeDataTest_205, SizeInitiallyZero_205) {

    EXPECT_EQ(data.size(), 0);

}
