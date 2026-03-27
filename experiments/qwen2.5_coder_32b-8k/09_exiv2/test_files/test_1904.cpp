#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"

#include "XMP_Const.h"



class NormalizeLangArrayTest_1904 : public ::testing::Test {

protected:

    XMP_Node* CreateNode(XMP_StringPtr name, XMP_StringPtr value = nullptr) {

        return new XMP_Node(nullptr, name, value, 0);

    }



    void AddQualifier(XMP_Node* node, XMP_StringPtr qualifierName, XMP_StringPtr qualifierValue) {

        XMP_Node* qualifier = CreateNode(qualifierName, qualifierValue);

        node->qualifiers.push_back(qualifier);

    }



    void SetUp() override {

        arrayNode = CreateNode("array", nullptr);

        arrayNode->options |= kXMP_ArrayIsAltText;

    }



    void TearDown() override {

        delete arrayNode;

    }



    XMP_Node* arrayNode;

};



TEST_F(NormalizeLangArrayTest_1904, PutIncreasesCount_1904) {

    // Arrange

    XMP_Node* item1 = CreateNode("item1");

    AddQualifier(item1, "xml:lang", "en");

    XMP_Node* item2 = CreateNode("item2");

    AddQualifier(item2, "xml:lang", "x-default");



    arrayNode->children.push_back(item1);

    arrayNode->children.push_back(item2);



    // Act

    NormalizeLangArray(arrayNode);



    // Assert

    EXPECT_EQ(arrayNode->children[0]->qualifiers[0]->value, "x-default");

}



TEST_F(NormalizeLangArrayTest_1904, NoDefaultItem_1904) {

    // Arrange

    XMP_Node* item1 = CreateNode("item1");

    AddQualifier(item1, "xml:lang", "en");



    arrayNode->children.push_back(item1);



    // Act & Assert

    EXPECT_NO_THROW(NormalizeLangArray(arrayNode));

    EXPECT_EQ(arrayNode->children[0]->qualifiers[0]->value, "en");

}



TEST_F(NormalizeLangArrayTest_1904, MultipleDefaultItems_1904) {

    // Arrange

    XMP_Node* item1 = CreateNode("item1");

    AddQualifier(item1, "xml:lang", "x-default");

    XMP_Node* item2 = CreateNode("item2");

    AddQualifier(item2, "xml:lang", "x-default");



    arrayNode->children.push_back(item1);

    arrayNode->children.push_back(item2);



    // Act

    NormalizeLangArray(arrayNode);



    // Assert

    EXPECT_EQ(arrayNode->children[0]->qualifiers[0]->value, "x-default");

}



TEST_F(NormalizeLangArrayTest_1904, MissingXmlLangQualifier_1904) {

    // Arrange

    XMP_Node* item1 = CreateNode("item1");



    arrayNode->children.push_back(item1);



    // Act & Assert

    EXPECT_THROW(NormalizeLangArray(arrayNode), XMP_Error);

}



TEST_F(NormalizeLangArrayTest_1904, InvalidXmlLangQualifierValue_1904) {

    // Arrange

    XMP_Node* item1 = CreateNode("item1");

    AddQualifier(item1, "xml:lang", "invalid");



    arrayNode->children.push_back(item1);



    // Act & Assert

    EXPECT_NO_THROW(NormalizeLangArray(arrayNode));

}



TEST_F(NormalizeLangArrayTest_1904, EmptyChildren_1904) {

    // Arrange & Act & Assert

    EXPECT_NO_THROW(NormalizeLangArray(arrayNode));

}
