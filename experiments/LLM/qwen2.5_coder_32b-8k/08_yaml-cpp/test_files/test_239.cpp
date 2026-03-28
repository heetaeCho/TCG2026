#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"



using namespace YAML::detail;



class NodeTest_239 : public ::testing::Test {

protected:

    Node node;

};



TEST_F(NodeTest_239, Mark_ReturnsValidMark_239) {

    // Since we cannot infer the internal state, we assume that mark() returns a valid Mark object.

    const Mark& mark = node.mark();

    EXPECT_TRUE(mark.line >= 0); // Assuming line number is non-negative

}



TEST_F(NodeTest_239, IsDefined_ReturnsFalseInitially_239) {

    EXPECT_FALSE(node.is_defined());

}



TEST_F(NodeTest_239, SetMark_And_Mark_ReturnsSameMark_239) {

    Mark newMark = {10, 5};

    node.set_mark(newMark);

    const Mark& retrievedMark = node.mark();

    EXPECT_EQ(retrievedMark.line, newMark.line);

    EXPECT_EQ(retrievedMark.column, newMark.column);

}



TEST_F(NodeTest_239, MarkDefined_And_IsDefined_ReturnsTrue_239) {

    node.mark_defined();

    EXPECT_TRUE(node.is_defined());

}



TEST_F(NodeTest_239, SetTypeAndGetNode_ReturnsSameType_239) {

    NodeType::value newType = NodeType::Map;

    node.set_type(newType);

    EXPECT_EQ(node.type(), newType);

}



TEST_F(NodeTest_239, SetScalarAndGetScalar_ReturnsSameScalar_239) {

    std::string scalarValue = "test_scalar";

    node.set_scalar(scalarValue);

    EXPECT_EQ(node.scalar(), scalarValue);

}



TEST_F(NodeTest_239, SetTagAndGetTag_ReturnsSameTag_239) {

    std::string tagValue = "!test_tag";

    node.set_tag(tagValue);

    EXPECT_EQ(node.tag(), tagValue);

}



TEST_F(NodeTest_239, SetStyleAndGetStyle_ReturnsSameStyle_239) {

    EmitterStyle::value newStyle = EmitterStyle::Flow;

    node.set_style(newStyle);

    EXPECT_EQ(node.style(), newStyle);

}



TEST_F(NodeTest_239, SetNull_And_TypeIsUndefined_239) {

    node.set_null();

    EXPECT_EQ(node.type(), NodeType::Undefined);

}
