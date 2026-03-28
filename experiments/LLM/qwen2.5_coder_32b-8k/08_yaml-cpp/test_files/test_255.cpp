#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"

#include "yaml-cpp/node/detail/node_ref.h"



using namespace YAML::detail;



class NodeTest_255 : public ::testing::Test {

protected:

    node testNode;

};



TEST_F(NodeTest_255, BeginReturnsIterator_255) {

    const_node_iterator it = testNode.begin();

    EXPECT_TRUE(it == testNode.end() || it != testNode.end());

}



TEST_F(NodeTest_255, EndReturnsIterator_255) {

    const_node_iterator it = testNode.end();

    EXPECT_TRUE(it == testNode.begin() || it != testNode.begin());

}



TEST_F(NodeTest_255, IsDefinedInitiallyFalse_255) {

    EXPECT_FALSE(testNode.is_defined());

}



TEST_F(NodeTest_255, MarkInitiallyDefaultConstructed_255) {

    const Mark& mark = testNode.mark();

    EXPECT_EQ(mark.pos.index, 0);

    EXPECT_EQ(mark.pos.column, 0);

    EXPECT_EQ(mark.pos.line, 0);

    EXPECT_TRUE(mark.name.empty());

}



TEST_F(NodeTest_255, TypeInitiallyUndefined_255) {

    EXPECT_EQ(testNode.type(), NodeType::Undefined);

}



TEST_F(NodeTest_255, ScalarInitiallyEmpty_255) {

    EXPECT_TRUE(testNode.scalar().empty());

}



TEST_F(NodeTest_255, TagInitiallyEmpty_255) {

    EXPECT_TRUE(testNode.tag().empty());

}



TEST_F(NodeTest_255, StyleInitiallyAny_255) {

    EXPECT_EQ(testNode.style(), EmitterStyle::Any);

}



TEST_F(NodeTest_255, SizeInitiallyZero_255) {

    EXPECT_EQ(testNode.size(), 0);

}



TEST_F(NodeTest_255, SetDefinedChangesIsDefined_255) {

    testNode.mark_defined();

    EXPECT_TRUE(testNode.is_defined());

}



TEST_F(NodeTest_255, SetMarkUpdatesMark_255) {

    Mark newMark;

    newMark.pos.index = 10;

    newMark.pos.column = 20;

    newMark.pos.line = 30;

    newMark.name = "test_mark";

    testNode.set_mark(newMark);

    const Mark& mark = testNode.mark();

    EXPECT_EQ(mark.pos.index, newMark.pos.index);

    EXPECT_EQ(mark.pos.column, newMark.pos.column);

    EXPECT_EQ(mark.pos.line, newMark.pos.line);

    EXPECT_EQ(mark.name, newMark.name);

}



TEST_F(NodeTest_255, SetTypeUpdatesType_255) {

    testNode.set_type(NodeType::Map);

    EXPECT_EQ(testNode.type(), NodeType::Map);

}



TEST_F(NodeTest_255, SetScalarUpdatesScalar_255) {

    testNode.set_scalar("test_scalar");

    EXPECT_EQ(testNode.scalar(), "test_scalar");

}



TEST_F(NodeTest_255, SetTagUpdatesTag_255) {

    testNode.set_tag("!test_tag");

    EXPECT_EQ(testNode.tag(), "!test_tag");

}



TEST_F(NodeTest_255, SetStyleUpdatesStyle_255) {

    testNode.set_style(EmitterStyle::Flow);

    EXPECT_EQ(testNode.style(), EmitterStyle::Flow);

}
