#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"

#include "yaml-cpp/mark.h"



using namespace YAML::detail;



class NodeDataTest_207 : public ::testing::Test {

protected:

    node_data data;

};



TEST_F(NodeDataTest_207, InitialTypeIsUndefined_207) {

    EXPECT_EQ(data.type(), NodeType::Undefined);

}



TEST_F(NodeDataTest_207, MarkDefinedChangesTypeToNull_207) {

    data.mark_defined();

    EXPECT_EQ(data.type(), NodeType::Null);

}



TEST_F(NodeDataTest_207, SetTypeChangesType_207) {

    data.mark_defined();

    data.set_type(NodeType::Scalar);

    EXPECT_EQ(data.type(), NodeType::Scalar);

}



TEST_F(NodeDataTest_207, InitialIsDefinedIsFalse_207) {

    EXPECT_FALSE(data.is_defined());

}



TEST_F(NodeDataTest_207, MarkDefinedSetsIsDefinedToTrue_207) {

    data.mark_defined();

    EXPECT_TRUE(data.is_defined());

}



TEST_F(NodeDataTest_207, SetTagChangesTag_207) {

    const std::string expectedTag = "!tag";

    data.set_tag(expectedTag);

    EXPECT_EQ(data.tag(), expectedTag);

}



TEST_F(NodeDataTest_207, SetScalarChangesScalar_207) {

    const std::string expectedScalar = "value";

    data.set_scalar(expectedScalar);

    EXPECT_EQ(data.scalar(), expectedScalar);

}



TEST_F(NodeDataTest_207, SetStyleChangesStyle_207) {

    EmitterStyle::value style = EmitterStyle::Flow;

    data.set_style(style);

    EXPECT_EQ(data.style(), style);

}



TEST_F(NodeDataTest_207, SetNullSetsTypeToNull_207) {

    data.mark_defined();

    data.set_null();

    EXPECT_EQ(data.type(), NodeType::Null);

}



TEST_F(NodeDataTest_207, SizeInitiallyZero_207) {

    EXPECT_EQ(data.size(), 0);

}



TEST_F(NodeDataTest_207, EmptyScalarReturnsEmptyString_207) {

    EXPECT_EQ(node_data::empty_scalar(), "");

}
