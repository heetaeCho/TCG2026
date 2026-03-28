#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/node.h>



using namespace YAML::detail;



class NodeTest_236 : public ::testing::Test {

protected:

    node defaultNode;

    node anotherDefaultNode;

};



TEST_F(NodeTest_236, IsFunctionReturnsTrueForSameNode_236) {

    EXPECT_TRUE(defaultNode.is(defaultNode));

}



TEST_F(NodeTest_236, IsFunctionReturnsFalseForDifferentNodes_236) {

    EXPECT_FALSE(defaultNode.is(anotherDefaultNode));

}



TEST_F(NodeTest_236, RefFunctionReturnsSamePointerForSameNode_236) {

    EXPECT_EQ(defaultNode.ref(), defaultNode.ref());

}



TEST_F(NodeTest_236, IsDefinedInitiallyFalse_236) {

    EXPECT_FALSE(defaultNode.is_defined());

}



TEST_F(NodeTest_236, MarkInitiallyDefaultConstructed_236) {

    Mark defaultMark;

    EXPECT_EQ(defaultNode.mark().index, defaultMark.index);

    EXPECT_EQ(defaultNode.mark().line, defaultMark.line);

    EXPECT_EQ(defaultNode.mark().column, defaultMark.column);

}



TEST_F(NodeTest_236, TypeInitiallyUndefined_236) {

    EXPECT_EQ(defaultNode.type(), NodeType::Undefined);

}



TEST_F(NodeTest_236, ScalarInitiallyEmptyString_236) {

    EXPECT_TRUE(defaultNode.scalar().empty());

}



TEST_F(NodeTest_236, TagInitiallyEmptyString_236) {

    EXPECT_TRUE(defaultNode.tag().empty());

}



TEST_F(NodeTest_236, StyleInitiallyDefault_236) {

    EXPECT_EQ(defaultNode.style(), EmitterStyle::Default);

}



TEST_F(NodeTest_236, SizeInitiallyZero_236) {

    EXPECT_EQ(defaultNode.size(), 0u);

}



TEST_F(NodeTest_236, BeginEqualsEndForEmptyNode_236) {

    EXPECT_EQ(defaultNode.begin(), defaultNode.end());

}
