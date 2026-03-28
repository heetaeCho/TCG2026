#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"

#include "yaml-cpp/node/detail/node_ref.h"



using namespace YAML::detail;



class NodeTest_240 : public ::testing::Test {

protected:

    NodeTest_240() : node_(), nodeRef_(new node_ref()) {}



    node node_;

    std::shared_ptr<node_ref> nodeRef_;

};



TEST_F(NodeTest_240, TypeReturnsCorrectType_240) {

    nodeRef_->set_type(NodeType::Map);

    node_.set_ref(*nodeRef_);

    EXPECT_EQ(node_.type(), NodeType::Map);



    nodeRef_->set_type(NodeType::Scalar);

    node_.set_ref(*nodeRef_);

    EXPECT_EQ(node_.type(), NodeType::Scalar);

}



TEST_F(NodeTest_240, IsDefinedReturnsCorrectValue_240) {

    EXPECT_FALSE(node_.is_defined());

    nodeRef_->mark_defined();

    node_.set_ref(*nodeRef_);

    EXPECT_TRUE(node_.is_defined());

}



TEST_F(NodeTest_240, ScalarReturnsEmptyStringInitially_240) {

    EXPECT_EQ(node_.scalar(), "");

}



TEST_F(NodeTest_240, TagReturnsEmptyStringInitially_240) {

    EXPECT_EQ(node_.tag(), "");

}



TEST_F(NodeTest_240, SetScalarUpdatesScalarValue_240) {

    node_.set_scalar("test_value");

    EXPECT_EQ(nodeRef_->scalar(), "test_value");

}



TEST_F(NodeTest_240, SetTagUpdatesTagValue_240) {

    node_.set_tag("test_tag");

    EXPECT_EQ(nodeRef_->tag(), "test_tag");

}



TEST_F(NodeTest_240, SizeReturnsZeroInitially_240) {

    EXPECT_EQ(node_.size(), 0);

}



TEST_F(NodeTest_240, SetTypeUpdatesTypeValue_240) {

    node_.set_type(NodeType::Sequence);

    EXPECT_EQ(nodeRef_->type(), NodeType::Sequence);



    node_.set_type(NodeType::Null);

    EXPECT_EQ(nodeRef_->type(), NodeType::Null);

}



TEST_F(NodeTest_240, SetMarkUpdatesMarkValue_240) {

    Mark mark(1, 2, "test_file.yaml");

    node_.set_mark(mark);

    EXPECT_EQ(nodeRef_->mark().line, mark.line);

    EXPECT_EQ(nodeRef_->mark().column, mark.column);

    EXPECT_EQ(nodeRef_->mark().buffer_mark, mark.buffer_mark);

}



TEST_F(NodeTest_240, SetNullSetsTypeToNull_240) {

    node_.set_null();

    EXPECT_EQ(node_.type(), NodeType::Null);

}
