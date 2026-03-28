#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"



using namespace YAML::detail;



class NodeRefTest_217 : public ::testing::Test {

protected:

    node_ref node;

};



TEST_F(NodeRefTest_217, MarkDefinedInitiallyFalse_217) {

    EXPECT_FALSE(node.is_defined());

}



TEST_F(NodeRefTest_217, MarkDefinedSetsTrue_217) {

    node.mark_defined();

    EXPECT_TRUE(node.is_defined());

}



TEST_F(NodeRefTest_217, SetMarkAndGetMark_217) {

    Mark mark;

    mark.column = 10;

    mark.line = 5;

    node.set_mark(mark);

    EXPECT_EQ(node.mark().column, mark.column);

    EXPECT_EQ(node.mark().line, mark.line);

}



TEST_F(NodeRefTest_217, SetTypeAndGetType_217) {

    NodeType::value type = NodeType::Scalar;

    node.set_type(type);

    EXPECT_EQ(node.type(), type);

}



TEST_F(NodeRefTest_217, SetTagAndGetTag_217) {

    std::string tag = "test_tag";

    node.set_tag(tag);

    EXPECT_EQ(node.tag(), tag);

}



TEST_F(NodeRefTest_217, SetScalarAndGetScalar_217) {

    std::string scalar = "test_scalar";

    node.set_scalar(scalar);

    EXPECT_EQ(node.scalar(), scalar);

}



TEST_F(NodeRefTest_217, SetStyleAndGetStyle_217) {

    EmitterStyle::value style = EmitterStyle::Flow;

    node.set_style(style);

    EXPECT_EQ(node.style(), style);

}



TEST_F(NodeRefTest_217, SetNullAndCheckType_217) {

    node.set_null();

    EXPECT_EQ(node.type(), NodeType::Null);

}
