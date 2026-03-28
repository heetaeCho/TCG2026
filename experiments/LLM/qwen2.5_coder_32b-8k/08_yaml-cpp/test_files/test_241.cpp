#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/node.h>



using namespace YAML::detail;



class NodeTest_241 : public ::testing::Test {

protected:

    NodeTest_241() : node_() {}



    Node node_;

};



TEST_F(NodeTest_241, ScalarReturnsEmptyStringByDefault_241) {

    EXPECT_EQ(node_.scalar(), "");

}



TEST_F(NodeTest_241, SetScalarAndGetScalarConsistent_241) {

    const std::string test_scalar = "test_value";

    node_.set_scalar(test_scalar);

    EXPECT_EQ(node_.scalar(), test_scalar);

}



TEST_F(NodeTest_241, IsDefinedReturnsFalseByDefault_241) {

    EXPECT_FALSE(node_.is_defined());

}



TEST_F(NodeTest_241, MarkDefinedChangesIsDefinedStatus_241) {

    node_.mark_defined();

    EXPECT_TRUE(node_.is_defined());

}



TEST_F(NodeTest_241, TypeReturnsUndefinedByDefault_241) {

    EXPECT_EQ(node_.type(), NodeType::Undefined);

}



TEST_F(NodeTest_241, SetTypeAndGetTypeConsistent_241) {

    node_.set_type(NodeType::Scalar);

    EXPECT_EQ(node_.type(), NodeType::Scalar);

}



TEST_F(NodeTest_241, TagReturnsEmptyStringByDefault_241) {

    EXPECT_EQ(node_.tag(), "");

}



TEST_F(NodeTest_241, SetTagAndGetTagConsistent_241) {

    const std::string test_tag = "test_tag";

    node_.set_tag(test_tag);

    EXPECT_EQ(node_.tag(), test_tag);

}



TEST_F(NodeTest_241, StyleReturnsAutoByDefault_241) {

    EXPECT_EQ(node_.style(), EmitterStyle::Auto);

}



TEST_F(NodeTest_241, SetStyleAndGetStyleConsistent_241) {

    node_.set_style(EmitterStyle::Block);

    EXPECT_EQ(node_.style(), EmitterStyle::Block);

}



TEST_F(NodeTest_241, SizeReturnsZeroByDefault_241) {

    EXPECT_EQ(node_.size(), 0);

}
