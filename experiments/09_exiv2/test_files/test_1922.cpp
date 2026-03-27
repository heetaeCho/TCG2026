#include <gtest/gtest.h>

#include "XMPUtils-FileInfo.cpp"

#include "XMPCore_Impl.hpp"



using namespace std;



class ItemValuesMatchTest_1922 : public ::testing::Test {

protected:

    XMP_Node* CreateNode(XMP_StringPtr name, XMP_StringPtr value, XMP_OptionBits options) {

        return new XMP_Node(nullptr, name, value, options);

    }



    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Cleanup code if needed

    }

};



TEST_F(ItemValuesMatchTest_1922, SimpleValueMatch_1922) {

    XMP_Node* leftNode = CreateNode("test", "value", 0);

    XMP_Node* rightNode = CreateNode("test", "value", 0);

    EXPECT_TRUE(ItemValuesMatch(leftNode, rightNode));

    delete leftNode;

    delete rightNode;

}



TEST_F(ItemValuesMatchTest_1922, SimpleValueMismatch_1922) {

    XMP_Node* leftNode = CreateNode("test", "value1", 0);

    XMP_Node* rightNode = CreateNode("test", "value2", 0);

    EXPECT_FALSE(ItemValuesMatch(leftNode, rightNode));

    delete leftNode;

    delete rightNode;

}



TEST_F(ItemValuesMatchTest_1922, LanguageQualifierMatch_1922) {

    XMP_Node* leftNode = CreateNode("test", "value", kXMP_PropHasLang);

    XMP_Node* rightNode = CreateNode("test", "value", kXMP_PropHasLang);

    XMP_Node* leftQualifier = CreateNode("lang", "en-US", 0);

    XMP_Node* rightQualifier = CreateNode("lang", "en-US", 0);

    leftNode->qualifiers.push_back(leftQualifier);

    rightNode->qualifiers.push_back(rightQualifier);

    EXPECT_TRUE(ItemValuesMatch(leftNode, rightNode));

    delete leftNode;

    delete rightNode;

}



TEST_F(ItemValuesMatchTest_1922, LanguageQualifierMismatch_1922) {

    XMP_Node* leftNode = CreateNode("test", "value", kXMP_PropHasLang);

    XMP_Node* rightNode = CreateNode("test", "value", kXMP_PropHasLang);

    XMP_Node* leftQualifier = CreateNode("lang", "en-US", 0);

    XMP_Node* rightQualifier = CreateNode("lang", "fr-FR", 0);

    leftNode->qualifiers.push_back(leftQualifier);

    rightNode->qualifiers.push_back(rightQualifier);

    EXPECT_FALSE(ItemValuesMatch(leftNode, rightNode));

    delete leftNode;

    delete rightNode;

}



TEST_F(ItemValuesMatchTest_1922, StructValueMatch_1922) {

    XMP_Node* leftNode = CreateNode("test", "", kXMP_PropValueIsStruct);

    XMP_Node* rightNode = CreateNode("test", "", kXMP_PropValueIsStruct);

    XMP_Node* leftChild = CreateNode("child1", "value1", 0);

    XMP_Node* rightChild = CreateNode("child1", "value1", 0);

    leftNode->children.push_back(leftChild);

    rightNode->children.push_back(rightChild);

    EXPECT_TRUE(ItemValuesMatch(leftNode, rightNode));

    delete leftNode;

    delete rightNode;

}



TEST_F(ItemValuesMatchTest_1922, StructValueMismatch_1922) {

    XMP_Node* leftNode = CreateNode("test", "", kXMP_PropValueIsStruct);

    XMP_Node* rightNode = CreateNode("test", "", kXMP_PropValueIsStruct);

    XMP_Node* leftChild = CreateNode("child1", "value1", 0);

    XMP_Node* rightChild = CreateNode("child2", "value1", 0);

    leftNode->children.push_back(leftChild);

    rightNode->children.push_back(rightChild);

    EXPECT_FALSE(ItemValuesMatch(leftNode, rightNode));

    delete leftNode;

    delete rightNode;

}



TEST_F(ItemValuesMatchTest_1922, ArrayValueMatch_1922) {

    XMP_Node* leftNode = CreateNode("test", "", kXMP_PropValueIsArray);

    XMP_Node* rightNode = CreateNode("test", "", kXMP_PropValueIsArray);

    XMP_Node* leftChild1 = CreateNode("item", "value1", 0);

    XMP_Node* rightChild1 = CreateNode("item", "value1", 0);

    XMP_Node* leftChild2 = CreateNode("item", "value2", 0);

    XMP_Node* rightChild2 = CreateNode("item", "value2", 0);

    leftNode->children.push_back(leftChild1);

    leftNode->children.push_back(leftChild2);

    rightNode->children.push_back(rightChild1);

    rightNode->children.push_back(rightChild2);

    EXPECT_TRUE(ItemValuesMatch(leftNode, rightNode));

    delete leftNode;

    delete rightNode;

}



TEST_F(ItemValuesMatchTest_1922, ArrayValueMismatch_1922) {

    XMP_Node* leftNode = CreateNode("test", "", kXMP_PropValueIsArray);

    XMP_Node* rightNode = CreateNode("test", "", kXMP_PropValueIsArray);

    XMP_Node* leftChild1 = CreateNode("item", "value1", 0);

    XMP_Node* rightChild1 = CreateNode("item", "value2", 0);

    XMP_Node* leftChild2 = CreateNode("item", "value3", 0);

    leftNode->children.push_back(leftChild1);

    leftNode->children.push_back(leftChild2);

    rightNode->children.push_back(rightChild1);

    EXPECT_FALSE(ItemValuesMatch(leftNode, rightNode));

    delete leftNode;

    delete rightNode;

}



TEST_F(ItemValuesMatchTest_1922, DifferentFormMismatch_1922) {

    XMP_Node* leftNode = CreateNode("test", "value", 0);

    XMP_Node* rightNode = CreateNode("test", "", kXMP_PropValueIsStruct);

    EXPECT_FALSE(ItemValuesMatch(leftNode, rightNode));

    delete leftNode;

    delete rightNode;

}



TEST_F(ItemValuesMatchTest_1922, EmptyNodesMatch_1922) {

    XMP_Node* leftNode = CreateNode("test", "", 0);

    XMP_Node* rightNode = CreateNode("test", "", 0);

    EXPECT_TRUE(ItemValuesMatch(leftNode, rightNode));

    delete leftNode;

    delete rightNode;

}
