#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"

#include "yaml-cpp/mark.h"



using namespace YAML::detail;



class NodeDataTest_206 : public ::testing::Test {

protected:

    node_data data;

};



TEST_F(NodeDataTest_206, MarkInitiallyNull_206) {

    EXPECT_EQ(data.mark(), Mark::null_mark());

}



TEST_F(NodeDataTest_206, SetMarkAndGetMark_206) {

    Mark mark(1, 2, "file.yaml");

    data.set_mark(mark);

    EXPECT_EQ(data.mark(), mark);

}



TEST_F(NodeDataTest_206, InitiallyUndefined_206) {

    EXPECT_FALSE(data.is_defined());

}



TEST_F(NodeDataTest_206, MarkDefinedSetsIsDefinedTrue_206) {

    data.mark_defined();

    EXPECT_TRUE(data.is_defined());

}



TEST_F(NodeDataTest_206, SetTypeAndGetNodeType_206) {

    NodeType::value type = NodeType::Map;

    data.set_type(type);

    EXPECT_EQ(data.type(), type);

}



TEST_F(NodeDataTest_206, SetTagAndGetTag_206) {

    std::string tag = "!map";

    data.set_tag(tag);

    EXPECT_EQ(data.tag(), tag);

}



TEST_F(NodeDataTest_206, SetScalarAndGetScalar_206) {

    std::string scalar = "value";

    data.set_scalar(scalar);

    EXPECT_EQ(data.scalar(), scalar);

}



TEST_F(NodeDataTest_206, SetStyleAndGetStyle_206) {

    EmitterStyle::value style = EmitterStyle::Flow;

    data.set_style(style);

    EXPECT_EQ(data.style(), style);

}



TEST_F(NodeDataTest_206, SizeInitiallyZero_206) {

    EXPECT_EQ(data.size(), 0);

}



TEST_F(NodeDataTest_206, SetNullSetsTypeToNull_206) {

    data.set_null();

    EXPECT_EQ(data.type(), NodeType::Null);

}
