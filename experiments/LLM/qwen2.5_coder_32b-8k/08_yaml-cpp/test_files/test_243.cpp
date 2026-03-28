#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"

#include "yaml-cpp/node/detail/node_ref.h"



using namespace YAML::detail;



class NodeTest_243 : public ::testing::Test {

protected:

    NodeTest_243() {}



    node testNode;

};



TEST_F(NodeTest_243, DefaultConstructorInitializesStyle_243) {

    EXPECT_EQ(testNode.style(), EmitterStyle::Default);

}



TEST_F(NodeTest_243, SetStyleUpdatesStyle_243) {

    testNode.set_style(EmitterStyle::Block);

    EXPECT_EQ(testNode.style(), EmitterStyle::Block);

}



TEST_F(NodeTest_243, IsDefinedInitiallyFalse_243) {

    EXPECT_FALSE(testNode.is_defined());

}



TEST_F(NodeTest_243, MarkDefinedSetsIsDefinedTrue_243) {

    testNode.mark_defined();

    EXPECT_TRUE(testNode.is_defined());

}



TEST_F(NodeTest_243, SetMarkDoesNotThrow_243) {

    Mark mark;

    EXPECT_NO_THROW(testNode.set_mark(mark));

}



TEST_F(NodeTest_243, DefaultConstructorInitializesTypeUndefined_243) {

    EXPECT_EQ(testNode.type(), NodeType::Undefined);

}



TEST_F(NodeTest_243, SetTypeUpdatesType_243) {

    testNode.set_type(NodeType::Map);

    EXPECT_EQ(testNode.type(), NodeType::Map);

}



TEST_F(NodeTest_243, DefaultConstructorInitializesEmptyScalar_243) {

    EXPECT_TRUE(testNode.scalar().empty());

}



TEST_F(NodeTest_243, SetScalarUpdatesScalar_243) {

    testNode.set_scalar("test");

    EXPECT_EQ(testNode.scalar(), "test");

}



TEST_F(NodeTest_243, DefaultConstructorInitializesEmptyTag_243) {

    EXPECT_TRUE(testNode.tag().empty());

}



TEST_F(NodeTest_243, SetTagUpdatesTag_243) {

    testNode.set_tag("tag:yaml.org,2002:str");

    EXPECT_EQ(testNode.tag(), "tag:yaml.org,2002:str");

}



TEST_F(NodeTest_243, DefaultConstructorInitializesSizeZero_243) {

    EXPECT_EQ(testNode.size(), 0);

}



TEST_F(NodeTest_243, SetNullSetsTypeToNull_243) {

    testNode.set_null();

    EXPECT_EQ(testNode.type(), NodeType::Null);

}
