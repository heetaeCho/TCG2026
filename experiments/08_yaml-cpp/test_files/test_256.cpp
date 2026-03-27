#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"



using namespace YAML::detail;



class NodeTest_256 : public ::testing::Test {

protected:

    Node nodeUnderTest;

};



TEST_F(NodeTest_256, EndIterator_ReturnsValidIterator_256) {

    const_node_iterator it = nodeUnderTest.end();

    EXPECT_TRUE(it != nullptr);

}



TEST_F(NodeTest_256, IsDefined_DefaultConstructedNode_IsFalse_256) {

    EXPECT_FALSE(nodeUnderTest.is_defined());

}



TEST_F(NodeTest_256, Mark_DefaultConstructedNode_ReturnsDefaultMark_256) {

    const Mark& mark = nodeUnderTest.mark();

    EXPECT_EQ(mark.pos, 0);

    EXPECT_EQ(mark.line, 0);

    EXPECT_EQ(mark.column, 0);

}



TEST_F(NodeTest_256, Type_DefaultConstructedNode_IsUndefined_256) {

    EXPECT_EQ(nodeUnderTest.type(), NodeType::Undefined);

}



TEST_F(NodeTest_256, Scalar_DefaultConstructedNode_ReturnsEmptyString_256) {

    const std::string& scalar = nodeUnderTest.scalar();

    EXPECT_TRUE(scalar.empty());

}



TEST_F(NodeTest_256, Tag_DefaultConstructedNode_ReturnsEmptyString_256) {

    const std::string& tag = nodeUnderTest.tag();

    EXPECT_TRUE(tag.empty());

}



TEST_F(NodeTest_256, Style_DefaultConstructedNode_IsDefaultStyle_256) {

    EXPECT_EQ(nodeUnderTest.style(), EmitterStyle::Default);

}



TEST_F(NodeTest_256, Size_DefaultConstructedNode_ReturnsZero_256) {

    EXPECT_EQ(nodeUnderTest.size(), 0);

}



TEST_F(NodeTest_256, Begin_End_Iterators_AreEqualForEmptyNode_256) {

    const_node_iterator beginIt = nodeUnderTest.begin();

    const_node_iterator endIt = nodeUnderTest.end();

    EXPECT_TRUE(beginIt == endIt);

}
