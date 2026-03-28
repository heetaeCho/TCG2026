#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"



class LookupQualSelectorTest_1887 : public ::testing::Test {

protected:

    XMP_Node* arrayNode;



    void SetUp() override {

        arrayNode = new XMP_Node(nullptr, "arrayNode", 0);

    }



    void TearDown() override {

        delete arrayNode;

    }

};



TEST_F(LookupQualSelectorTest_1887, NormalOperation_1887) {

    XMP_VarString qualName("qual");

    XMP_VarString qualValue("value");



    XMP_Node* child = new XMP_Node(arrayNode, "child", 0);

    XMP_Node* qualifier = new XMP_Node(child, qualName, qualValue, 0);

    arrayNode->children.push_back(child);

    child->qualifiers.push_back(qualifier);



    XMP_Index index = LookupQualSelector(arrayNode, qualName, qualValue);

    EXPECT_EQ(index, 0);

}



TEST_F(LookupQualSelectorTest_1887, QualLangNormalOperation_1887) {

    XMP_VarString qualName("xml:lang");

    XMP_VarString qualValue("en-US");



    XMP_Node* child = new XMP_Node(arrayNode, "child", 0);

    XMP_Node* qualifier = new XMP_Node(child, qualName, qualValue, 0);

    arrayNode->children.push_back(child);

    child->qualifiers.push_back(qualifier);



    XMP_Index index = LookupQualSelector(arrayNode, qualName, qualValue);

    EXPECT_EQ(index, 0);

}



TEST_F(LookupQualSelectorTest_1887, QualLangWithNormalization_1887) {

    XMP_VarString qualName("xml:lang");

    XMP_VarString qualValue("EN-us");



    XMP_Node* child = new XMP_Node(arrayNode, "child", 0);

    XMP_Node* qualifier = new XMP_Node(child, qualName, "en-US", 0);

    arrayNode->children.push_back(child);

    child->qualifiers.push_back(qualifier);



    XMP_Index index = LookupQualSelector(arrayNode, qualName, qualValue);

    EXPECT_EQ(index, 0);

}



TEST_F(LookupQualSelectorTest_1887, BoundaryCondition_NoChildren_1887) {

    XMP_VarString qualName("qual");

    XMP_VarString qualValue("value");



    XMP_Index index = LookupQualSelector(arrayNode, qualName, qualValue);

    EXPECT_EQ(index, -1);

}



TEST_F(LookupQualSelectorTest_1887, BoundaryCondition_NoMatchingQualifier_1887) {

    XMP_VarString qualName("qual");

    XMP_VarString qualValue("value");



    XMP_Node* child = new XMP_Node(arrayNode, "child", 0);

    arrayNode->children.push_back(child);



    XMP_Index index = LookupQualSelector(arrayNode, qualName, qualValue);

    EXPECT_EQ(index, -1);

}



TEST_F(LookupQualSelectorTest_1887, BoundaryCondition_MultipleChildrenNoMatch_1887) {

    XMP_VarString qualName("qual");

    XMP_VarString qualValue("value");



    for (int i = 0; i < 5; ++i) {

        XMP_Node* child = new XMP_Node(arrayNode, "child", 0);

        arrayNode->children.push_back(child);

    }



    XMP_Index index = LookupQualSelector(arrayNode, qualName, qualValue);

    EXPECT_EQ(index, -1);

}



TEST_F(LookupQualSelectorTest_1887, BoundaryCondition_MultipleChildrenWithMatch_1887) {

    XMP_VarString qualName("qual");

    XMP_VarString qualValue("value");



    for (int i = 0; i < 5; ++i) {

        XMP_Node* child = new XMP_Node(arrayNode, "child", 0);

        if (i == 2) {

            XMP_Node* qualifier = new XMP_Node(child, qualName, qualValue, 0);

            child->qualifiers.push_back(qualifier);

        }

        arrayNode->children.push_back(child);

    }



    XMP_Index index = LookupQualSelector(arrayNode, qualName, qualValue);

    EXPECT_EQ(index, 2);

}



TEST_F(LookupQualSelectorTest_1887, ExceptionalCase_EmptyQualName_1887) {

    XMP_VarString qualName("");

    XMP_VarString qualValue("value");



    XMP_Index index = LookupQualSelector(arrayNode, qualName, qualValue);

    EXPECT_EQ(index, -1);

}



TEST_F(LookupQualSelectorTest_1887, ExceptionalCase_EmptyQualValue_1887) {

    XMP_VarString qualName("qual");

    XMP_VarString qualValue("");



    XMP_Node* child = new XMP_Node(arrayNode, "child", 0);

    XMP_Node* qualifier = new XMP_Node(child, qualName, "", 0);

    arrayNode->children.push_back(child);

    child->qualifiers.push_back(qualifier);



    XMP_Index index = LookupQualSelector(arrayNode, qualName, qualValue);

    EXPECT_EQ(index, 0);

}
