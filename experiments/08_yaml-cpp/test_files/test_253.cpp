#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/node.h>



using namespace YAML::detail;



class NodeTest_253 : public ::testing::Test {

protected:

    node testNode;

};



TEST_F(NodeTest_253, SetStyle_DefaultBehavior_253) {

    EmitterStyle::value style = EmitterStyle::Block;

    testNode.set_style(style);

    EXPECT_EQ(testNode.style(), style);

}



TEST_F(NodeTest_253, IsDefined_DefaultState_253) {

    EXPECT_FALSE(testNode.is_defined());

}



TEST_F(NodeTest_253, MarkDefined_ChangesIsDefined_253) {

    testNode.mark_defined();

    EXPECT_TRUE(testNode.is_defined());

}



TEST_F(NodeTest_253, SetStyle_MultipleStyles_253) {

    EmitterStyle::value styles[] = {EmitterStyle::Flow, EmitterStyle::Block};

    for (auto style : styles) {

        testNode.set_style(style);

        EXPECT_EQ(testNode.style(), style);

    }

}



TEST_F(NodeTest_253, SetScalar_DefaultBehavior_253) {

    std::string scalarValue = "test_scalar";

    testNode.set_scalar(scalarValue);

    EXPECT_EQ(testNode.scalar(), scalarValue);

}



TEST_F(NodeTest_253, SetTag_DefaultBehavior_253) {

    std::string tagValue = "!mytag";

    testNode.set_tag(tagValue);

    EXPECT_EQ(testNode.tag(), tagValue);

}



TEST_F(NodeTest_253, SetType_DefaultBehavior_253) {

    NodeType::value nodeTypes[] = {NodeType::Null, NodeType::Scalar};

    for (auto type : nodeTypes) {

        testNode.set_type(type);

        EXPECT_EQ(testNode.type(), type);

    }

}



TEST_F(NodeTest_253, SetMark_DefaultBehavior_253) {

    Mark mark;

    mark.column = 10;

    mark.line = 5;

    mark.pos = 42;

    testNode.set_mark(mark);

    EXPECT_EQ(testNode.mark(), mark);

}
