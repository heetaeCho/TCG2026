#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"

#include "XMP_Const.h"



class LookupLangItemTest_1898 : public ::testing::Test {

protected:

    XMP_Node* arrayNode;

    XMP_VarString lang;



    void SetUp() override {

        arrayNode = new XMP_Node(nullptr, "testArray", kXMP_PropValueIsArray);

    }



    void TearDown() override {

        delete arrayNode;

    }

};



TEST_F(LookupLangItemTest_1898, NormalOperationFound_1898) {

    lang = "en";

    XMP_Node* child = new XMP_Node(arrayNode, "child", kXMP_PropHasQualifiers);

    XMP_Node* qualifier = new XMP_Node(child, "xml:lang", "en");

    child->qualifiers.push_back(qualifier);



    arrayNode->children.push_back(child);



    EXPECT_EQ(LookupLangItem(arrayNode, lang), 0);

}



TEST_F(LookupLangItemTest_1898, NormalOperationNotFound_1898) {

    lang = "fr";

    XMP_Node* child = new XMP_Node(arrayNode, "child", kXMP_PropHasQualifiers);

    XMP_Node* qualifier = new XMP_Node(child, "xml:lang", "en");

    child->qualifiers.push_back(qualifier);



    arrayNode->children.push_back(child);



    EXPECT_EQ(LookupLangItem(arrayNode, lang), -1);

}



TEST_F(LookupLangItemTest_1898, BoundaryConditionNoChildren_1898) {

    lang = "en";

    EXPECT_EQ(LookupLangItem(arrayNode, lang), -1);

}



TEST_F(LookupLangItemTest_1898, BoundaryConditionSingleChildNoQualifier_1898) {

    lang = "en";

    XMP_Node* child = new XMP_Node(arrayNode, "child", 0);



    arrayNode->children.push_back(child);



    EXPECT_EQ(LookupLangItem(arrayNode, lang), -1);

}



TEST_F(LookupLangItemTest_1898, BoundaryConditionMultipleChildrenNoneMatch_1898) {

    lang = "en";

    XMP_Node* child1 = new XMP_Node(arrayNode, "child1", kXMP_PropHasQualifiers);

    XMP_Node* qualifier1 = new XMP_Node(child1, "xml:lang", "fr");

    child1->qualifiers.push_back(qualifier1);



    XMP_Node* child2 = new XMP_Node(arrayNode, "child2", kXMP_PropHasQualifiers);

    XMP_Node* qualifier2 = new XMP_Node(child2, "xml:lang", "de");

    child2->qualifiers.push_back(qualifier2);



    arrayNode->children.push_back(child1);

    arrayNode->children.push_back(child2);



    EXPECT_EQ(LookupLangItem(arrayNode, lang), -1);

}



TEST_F(LookupLangItemTest_1898, BoundaryConditionMultipleChildrenOneMatches_1898) {

    lang = "en";

    XMP_Node* child1 = new XMP_Node(arrayNode, "child1", kXMP_PropHasQualifiers);

    XMP_Node* qualifier1 = new XMP_Node(child1, "xml:lang", "fr");

    child1->qualifiers.push_back(qualifier1);



    XMP_Node* child2 = new XMP_Node(arrayNode, "child2", kXMP_PropHasQualifiers);

    XMP_Node* qualifier2 = new XMP_Node(child2, "xml:lang", "en");

    child2->qualifiers.push_back(qualifier2);



    arrayNode->children.push_back(child1);

    arrayNode->children.push_back(child2);



    EXPECT_EQ(LookupLangItem(arrayNode, lang), 1);

}



TEST_F(LookupLangItemTest_1898, ExceptionCaseNonArrayNode_1898) {

    lang = "en";

    XMP_Node* nonArrayNode = new XMP_Node(nullptr, "nonArray", 0);



    EXPECT_THROW({

        LookupLangItem(nonArrayNode, lang);

    }, std::exception);



    delete nonArrayNode;

}
