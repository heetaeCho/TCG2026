#include <gtest/gtest.h>

#include <yaml-cpp/node/convert.h>

#include <yaml-cpp/node/node.h>



class YAMLNodeTest_593 : public ::testing::Test {

protected:

    YAML::Node node;

};



TEST_F(YAMLNodeTest_593, EncodeReturnsSameNode_593) {

    YAML::Node encodedNode = YAML::encode(node);

    EXPECT_EQ(&encodedNode, &node);

}



TEST_F(YAMLNodeTest_593, DefaultConstructorIsValid_593) {

    YAML::Node defaultNode;

    EXPECT_TRUE(defaultNode.IsValid());

}



TEST_F(YAMLNodeTest_593, ScalarTypeIsDefined_593) {

    YAML::Node scalarNode("test");

    EXPECT_TRUE(scalarNode.IsDefined());

}



TEST_F(YAMLNodeTest_593, NullNodeIsNotValid_593) {

    YAML::Node nullNode(YAML::NodeType::Null);

    EXPECT_FALSE(nullNode.IsValid());

}



TEST_F(YAMLNodeTest_593, ScalarTypeReturnsCorrectValue_593) {

    std::string expected = "test";

    YAML::Node scalarNode(expected);

    EXPECT_EQ(scalarNode.Scalar(), expected);

}



TEST_F(YAMLNodeTest_593, InvalidNodeThrowsOnScalarAccess_593) {

    YAML::Node invalidNode(YAML::NodeType::Null);

    EXPECT_THROW(invalidNode.Scalar(), YAML::InvalidNode);

}



TEST_F(YAMLNodeTest_593, NodeEqualityCheckWorks_593) {

    YAML::Node node1("test");

    YAML::Node node2("test");

    YAML::Node node3("different");



    EXPECT_TRUE(node1 == node2);

    EXPECT_FALSE(node1 == node3);

}



TEST_F(YAMLNodeTest_593, NodeAssignmentOperatorWorks_593) {

    YAML::Node original("original");

    YAML::Node assigned;

    assigned = original;



    EXPECT_EQ(assigned.Scalar(), "original");

}



TEST_F(YAMLNodeTest_593, NodeResetMethodWorks_593) {

    YAML::Node node1("test");

    YAML::Node node2("reset");



    node1.reset(node2);

    EXPECT_EQ(node1.Scalar(), "reset");

}



TEST_F(YAMLNodeTest_593, SequenceTypeSizeCorrect_593) {

    YAML::Node sequenceNode;

    sequenceNode.push_back(1);

    sequenceNode.push_back(2);



    EXPECT_EQ(sequenceNode.size(), 2u);

}



TEST_F(YAMLNodeTest_593, MapTypeAccessAndInsertion_593) {

    YAML::Node mapNode;

    mapNode["key"] = "value";



    EXPECT_EQ(mapNode["key"].Scalar(), "value");

}



TEST_F(YAMLNodeTest_593, MapTypeRemovalWorks_593) {

    YAML::Node mapNode;

    mapNode["key"] = "value";

    bool removed = mapNode.remove("key");



    EXPECT_TRUE(removed);

    EXPECT_FALSE(mapNode.IsDefined());

}
