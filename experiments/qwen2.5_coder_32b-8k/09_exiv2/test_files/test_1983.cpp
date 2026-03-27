#include <gtest/gtest.h>

#include "XMPUtils.cpp"

#include "XMPCore_Impl.hpp"



using namespace XMP_NAMESPACE;



class EstimateSizeForJPEGTest : public ::testing::Test {

protected:

    void SetUp() override {

        parent = new XMP_Node(nullptr, "parentName", 0);

        node = new XMP_Node(parent, "nodeName", 0);

    }



    void TearDown() override {

        delete node;

        delete parent;

    }



    XMP_Node* parent;

    XMP_Node* node;

};



TEST_F(EstimateSizeForJPEGTest_1983, SimplePropertyWithoutName_1983) {

    node->options = 0; // Simple property

    node->name.clear(); // No name

    node->value = "nodeValue";

    EXPECT_EQ(EstimateSizeForJPEG(node), node->value.size());

}



TEST_F(EstimateSizeForJPEGTest_1983, SimplePropertyWithName_1983) {

    node->options = 0; // Simple property

    node->name = "nodeName";

    node->value = "nodeValue";

    EXPECT_EQ(EstimateSizeForJPEG(node), node->name.size() + 3 + node->value.size());

}



TEST_F(EstimateSizeForJPEGTest_1983, ArrayPropertyWithoutName_1983) {

    node->options = kXMP_PropValueIsArray;

    node->name.clear(); // No name

    XMP_Node* childNode = new XMP_Node(node, "childNode", "childValue", 0);

    node->children.push_back(childNode);

    size_t expectedSize = 9 + 10 + (8 + 9) * 1 + childNode->name.size() + 3 + childNode->value.size();

    EXPECT_EQ(EstimateSizeForJPEG(node), expectedSize);

    delete childNode;

}



TEST_F(EstimateSizeForJPEGTest_1983, ArrayPropertyWithName_1983) {

    node->options = kXMP_PropValueIsArray;

    node->name = "nodeName";

    XMP_Node* childNode = new XMP_Node(node, "childNode", "childValue", 0);

    node->children.push_back(childNode);

    size_t expectedSize = 2 * node->name.size() + 5 + 9 + 10 + (8 + 9) * 1 + childNode->name.size() + 3 + childNode->value.size();

    EXPECT_EQ(EstimateSizeForJPEG(node), expectedSize);

    delete childNode;

}



TEST_F(EstimateSizeForJPEGTest_1983, StructPropertyWithoutName_1983) {

    node->options = kXMP_PropValueIsStruct;

    node->name.clear(); // No name

    XMP_Node* childNode = new XMP_Node(node, "childNode", "childValue", 0);

    node->children.push_back(childNode);

    size_t expectedSize = 25 + childNode->name.size() + 3 + childNode->value.size();

    EXPECT_EQ(EstimateSizeForJPEG(node), expectedSize);

    delete childNode;

}



TEST_F(EstimateSizeForJPEGTest_1983, StructPropertyWithName_1983) {

    node->options = kXMP_PropValueIsStruct;

    node->name = "nodeName";

    XMP_Node* childNode = new XMP_Node(node, "childNode", "childValue", 0);

    node->children.push_back(childNode);

    size_t expectedSize = 2 * node->name.size() + 5 + 25 + childNode->name.size() + 3 + childNode->value.size();

    EXPECT_EQ(EstimateSizeForJPEG(node), expectedSize);

    delete childNode;

}



TEST_F(EstimateSizeForJPEGTest_1983, NoChildrenSimpleProperty_1983) {

    node->options = 0; // Simple property

    node->name = "nodeName";

    node->value = "nodeValue";

    EXPECT_EQ(EstimateSizeForJPEG(node), node->name.size() + 3 + node->value.size());

}



TEST_F(EstimateSizeForJPEGTest_1983, NoChildrenArrayProperty_1983) {

    node->options = kXMP_PropValueIsArray;

    node->name = "nodeName";

    EXPECT_EQ(EstimateSizeForJPEG(node), 2 * node->name.size() + 5 + 9 + 10);

}



TEST_F(EstimateSizeForJPEGTest_1983, NoChildrenStructProperty_1983) {

    node->options = kXMP_PropValueIsStruct;

    node->name = "nodeName";

    EXPECT_EQ(EstimateSizeForJPEG(node), 2 * node->name.size() + 5 + 25);

}



TEST_F(EstimateSizeForJPEGTest_1983, MultipleChildrenArrayProperty_1983) {

    node->options = kXMP_PropValueIsArray;

    node->name = "nodeName";

    XMP_Node* childNode1 = new XMP_Node(node, "childNode1", "childValue1", 0);

    XMP_Node* childNode2 = new XMP_Node(node, "childNode2", "childValue2", 0);

    node->children.push_back(childNode1);

    node->children.push_back(childNode2);



    size_t expectedSize = 2 * node->name.size() + 5 + 9 + 10 + (8 + 9) * 2 +

                          childNode1->name.size() + 3 + childNode1->value.size() +

                          childNode2->name.size() + 3 + childNode2->value.size();

    EXPECT_EQ(EstimateSizeForJPEG(node), expectedSize);



    delete childNode1;

    delete childNode2;

}



TEST_F(EstimateSizeForJPEGTest_1983, MultipleChildrenStructProperty_1983) {

    node->options = kXMP_PropValueIsStruct;

    node->name = "nodeName";

    XMP_Node* childNode1 = new XMP_Node(node, "childNode1", "childValue1", 0);

    XMP_Node* childNode2 = new XMP_Node(node, "childNode2", "childValue2", 0);

    node->children.push_back(childNode1);

    node->children.push_back(childNode2);



    size_t expectedSize = 2 * node->name.size() + 5 + 25 +

                          childNode1->name.size() + 3 + childNode1->value.size() +

                          childNode2->name.size() + 3 + childNode2->value.size();

    EXPECT_EQ(EstimateSizeForJPEG(node), expectedSize);



    delete childNode1;

    delete childNode2;

}
