#include <gtest/gtest.h>

#include <yaml-cpp/node/impl.h>



using namespace YAML;



class NodeTest_558 : public ::testing::Test {

protected:

    Node node;

};



TEST_F(NodeTest_558, Tag_ReturnsEmptyScalarWhenNodeIsValidAndNoTagIsSet_558) {

    EXPECT_EQ(node.Tag(), detail::node_data::empty_scalar());

}



TEST_F(NodeTest_558, Tag_ThrowsInvalidNodeExceptionWhenNodeIsInvalid_558) {

    Node invalidNode(Zombie{});

    EXPECT_THROW(invalidNode.Tag(), InvalidNode);

}



TEST_F(NodeTest_558, Tag_ReturnsSetTagWhenNodeIsValidAndTagIsSet_558) {

    const std::string testTag = "test_tag";

    node.SetTag(testTag);

    EXPECT_EQ(node.Tag(), testTag);

}
