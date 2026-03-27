#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/node.h>



using namespace YAML::detail;



class NodeTest_242 : public ::testing::Test {

protected:

    node* testNode;



    void SetUp() override {

        testNode = new node();

    }



    void TearDown() override {

        delete testNode;

    }

};



TEST_F(NodeTest_242, Tag_ReturnsEmptyStringByDefault_242) {

    EXPECT_EQ(testNode->tag(), "");

}



TEST_F(NodeTest_242, IsDefined_ReturnsFalseInitially_242) {

    EXPECT_FALSE(testNode->is_defined());

}



TEST_F(NodeTest_242, MarkDefined_SetsDefinedFlag_242) {

    testNode->mark_defined();

    EXPECT_TRUE(testNode->is_defined());

}



TEST_F(NodeTest_242, SetTag_ChangesTagValue_242) {

    const std::string newTag = "!newtag";

    testNode->set_tag(newTag);

    EXPECT_EQ(testNode->tag(), newTag);

}



TEST_F(NodeTest_242, SetScalar_SetsScalarValue_242) {

    const std::string newScalar = "value";

    testNode->set_scalar(newScalar);

    EXPECT_EQ(testNode->scalar(), newScalar);

}



TEST_F(NodeTest_242, SetType_ChangesTypeValue_242) {

    NodeType::value newType = NodeType::Map;

    testNode->set_type(newType);

    EXPECT_EQ(testNode->type(), newType);

}



TEST_F(NodeTest_242, Size_ReturnsZeroInitially_242) {

    EXPECT_EQ(testNode->size(), 0);

}



TEST_F(NodeTest_242, SetStyle_ChangesStyleValue_242) {

    EmitterStyle::value newStyle = EmitterStyle::Flow;

    testNode->set_style(newStyle);

    EXPECT_EQ(testNode->style(), newStyle);

}
