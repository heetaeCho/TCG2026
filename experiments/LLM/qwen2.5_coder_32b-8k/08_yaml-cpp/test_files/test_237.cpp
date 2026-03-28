#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"



using namespace YAML::detail;



class NodeTest_237 : public ::testing::Test {

protected:

    Node nodeUnderTest;

};



TEST_F(NodeTest_237, RefReturnsNonNullPointer_237) {

    EXPECT_NE(nodeUnderTest.ref(), nullptr);

}



TEST_F(NodeTest_237, IsDefinedInitiallyFalse_237) {

    EXPECT_FALSE(nodeUnderTest.is_defined());

}



TEST_F(NodeTest_237, MarkInitiallyDefaultConstructed_237) {

    Mark defaultMark;

    EXPECT_EQ(nodeUnderTest.mark(), defaultMark);

}



TEST_F(NodeTest_237, TypeInitiallyUndefined_237) {

    EXPECT_EQ(nodeUnderTest.type(), NodeType::Undefined);

}



TEST_F(NodeTest_237, ScalarInitiallyEmptyString_237) {

    EXPECT_TRUE(nodeUnderTest.scalar().empty());

}



TEST_F(NodeTest_237, TagInitiallyEmptyString_237) {

    EXPECT_TRUE(nodeUnderTest.tag().empty());

}



TEST_F(NodeTest_237, StyleInitiallyDefault_237) {

    EXPECT_EQ(nodeUnderTest.style(), EmitterStyle::Default);

}



TEST_F(NodeTest_237, SizeInitiallyZero_237) {

    EXPECT_EQ(nodeUnderTest.size(), 0);

}



TEST_F(NodeTest_237, BeginEqualsEndInitially_237) {

    EXPECT_EQ(nodeUnderTest.begin(), nodeUnderTest.end());

}



TEST_F(NodeTest_237, SetMarkUpdatesMark_237) {

    Mark newMark(1, 2, "filename.yaml");

    nodeUnderTest.set_mark(newMark);

    EXPECT_EQ(nodeUnderTest.mark(), newMark);

}



TEST_F(NodeTest_237, SetTypeUpdatesType_237) {

    nodeUnderTest.set_type(NodeType::Map);

    EXPECT_EQ(nodeUnderTest.type(), NodeType::Map);

}



TEST_F(NodeTest_237, SetScalarUpdatesScalar_237) {

    std::string newScalar = "value";

    nodeUnderTest.set_scalar(newScalar);

    EXPECT_EQ(nodeUnderTest.scalar(), newScalar);

}



TEST_F(NodeTest_237, SetTagUpdatesTag_237) {

    std::string newTag = "!tag";

    nodeUnderTest.set_tag(newTag);

    EXPECT_EQ(nodeUnderTest.tag(), newTag);

}



TEST_F(NodeTest_237, SetStyleUpdatesStyle_237) {

    nodeUnderTest.set_style(EmitterStyle::Block);

    EXPECT_EQ(nodeUnderTest.style(), EmitterStyle::Block);

}



TEST_F(NodeTest_237, MarkDefinedSetsIsDefinedTrue_237) {

    nodeUnderTest.mark_defined();

    EXPECT_TRUE(nodeUnderTest.is_defined());

}
