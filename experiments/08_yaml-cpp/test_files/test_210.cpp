#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;



class NodeDataTest_210 : public ::testing::Test {

protected:

    node_data data;

};



TEST_F(NodeDataTest_210, DefaultStyleIsBlock_210) {

    EXPECT_EQ(data.style(), EmitterStyle::Block);

}



TEST_F(NodeDataTest_210, SetAndGetStyle_210) {

    data.set_style(EmitterStyle::Flow);

    EXPECT_EQ(data.style(), EmitterStyle::Flow);

}



TEST_F(NodeDataTest_210, DefaultIsNotDefined_210) {

    EXPECT_FALSE(data.is_defined());

}



TEST_F(NodeDataTest_210, MarkAsDefined_210) {

    data.mark_defined();

    EXPECT_TRUE(data.is_defined());

}



TEST_F(NodeDataTest_210, SetAndGetMark_210) {

    Mark mark = Mark(1, 2, "file.yaml");

    data.set_mark(mark);

    EXPECT_EQ(data.mark(), mark);

}



TEST_F(NodeDataTest_210, SetAndGetType_210) {

    data.set_type(NodeType::Scalar);

    EXPECT_EQ(data.type(), NodeType::Scalar);

}



TEST_F(NodeDataTest_210, SetAndGetTag_210) {

    std::string tag = "!mytag";

    data.set_tag(tag);

    EXPECT_EQ(data.tag(), tag);

}



TEST_F(NodeDataTest_210, SetAndGetTypeNull_210) {

    data.set_null();

    EXPECT_EQ(data.type(), NodeType::Null);

}



TEST_F(NodeDataTest_210, SetAndGetScalar_210) {

    std::string scalar = "value";

    data.set_scalar(scalar);

    EXPECT_EQ(data.scalar(), scalar);

}



TEST_F(NodeDataTest_210, EmptyScalarIsConstant_210) {

    const std::string& empty = node_data::empty_scalar();

    EXPECT_TRUE(empty.empty());

}
