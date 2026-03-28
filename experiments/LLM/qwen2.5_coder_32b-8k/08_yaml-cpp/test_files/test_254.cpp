#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"



using namespace YAML::detail;



class NodeTest_254 : public ::testing::Test {

protected:

    node testNode;

};



TEST_F(NodeTest_254, Size_ReturnsZeroForEmptyNode_254) {

    EXPECT_EQ(testNode.size(), 0);

}



TEST_F(NodeTest_254, IsDefined_ReturnsFalseInitially_254) {

    EXPECT_FALSE(testNode.is_defined());

}



TEST_F(NodeTest_254, Mark_ReturnsDefaultConstructedMark_254) {

    Mark defaultMark;

    EXPECT_EQ(testNode.mark(), defaultMark);

}



TEST_F(NodeTest_254, Type_ReturnsUndefinedInitially_254) {

    EXPECT_EQ(testNode.type(), NodeType::Undefined);

}



TEST_F(NodeTest_254, Scalar_ReturnsEmptyStringInitially_254) {

    EXPECT_TRUE(testNode.scalar().empty());

}



TEST_F(NodeTest_254, Tag_ReturnsEmptyStringInitially_254) {

    EXPECT_TRUE(testNode.tag().empty());

}



TEST_F(NodeTest_254, Style_ReturnsDefaultStyleInitially_254) {

    EXPECT_EQ(testNode.style(), EmitterStyle::Default);

}



TEST_F(NodeTest_254, MarkDefined_SetsIsDefinedToTrue_254) {

    testNode.mark_defined();

    EXPECT_TRUE(testNode.is_defined());

}



TEST_F(NodeTest_254, SetMark_UpdatesMark_254) {

    Mark customMark{10, 20, "filename.yaml"};

    testNode.set_mark(customMark);

    EXPECT_EQ(testNode.mark(), customMark);

}



TEST_F(NodeTest_254, SetType_UpdatesNodeType_254) {

    testNode.set_type(NodeType::Scalar);

    EXPECT_EQ(testNode.type(), NodeType::Scalar);

}



TEST_F(NodeTest_254, SetScalar_UpdatesScalarValue_254) {

    std::string scalarValue = "test_scalar";

    testNode.set_scalar(scalarValue);

    EXPECT_EQ(testNode.scalar(), scalarValue);

}



TEST_F(NodeTest_254, SetTag_UpdatesTagValue_254) {

    std::string tagValue = "!custom_tag";

    testNode.set_tag(tagValue);

    EXPECT_EQ(testNode.tag(), tagValue);

}



TEST_F(NodeTest_254, SetStyle_UpdatesEmitterStyle_254) {

    testNode.set_style(EmitterStyle::Block);

    EXPECT_EQ(testNode.style(), EmitterStyle::Block);

}
