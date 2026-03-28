#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"

#include "XMP_Const.h"



class FindQualifierNodeTest_1896 : public ::testing::Test {

protected:

    XMP_Node* parent;

    XMP_StringPtr qualName = "exampleQual";

    XMP_OptionBits options = 0;



    void SetUp() override {

        parent = new XMP_Node(nullptr, "parentNode", options);

    }



    void TearDown() override {

        delete parent;

    }

};



TEST_F(FindQualifierNodeTest_1896, FindExistingQualifier_1896) {

    XMP_Node* qualNode = new XMP_Node(parent, qualName, kXMP_PropIsQualifier);

    parent->qualifiers.push_back(qualNode);



    XMP_NodePtrPos ptrPos;

    XMP_Node* result = FindQualifierNode(parent, qualName, false, &ptrPos);



    EXPECT_EQ(result, qualNode);

    EXPECT_EQ(*ptrPos, qualNode);

}



TEST_F(FindQualifierNodeTest_1896, CreateNewQualifier_1896) {

    XMP_NodePtrPos ptrPos;

    XMP_Node* result = FindQualifierNode(parent, qualName, true, &ptrPos);



    EXPECT_NE(result, nullptr);

    EXPECT_EQ(*ptrPos, result);

    EXPECT_EQ(result->name, qualName);

    EXPECT_EQ(result->parent, parent);

    EXPECT_EQ(parent->qualifiers.size(), 1);

}



TEST_F(FindQualifierNodeTest_1896, NoCreateNonExistentQualifier_1896) {

    XMP_NodePtrPos ptrPos;

    XMP_Node* result = FindQualifierNode(parent, qualName, false, &ptrPos);



    EXPECT_EQ(result, nullptr);

    EXPECT_EQ(ptrPos, nullptr);

}



TEST_F(FindQualifierNodeTest_1896, CreateLangQualifier_1896) {

    const char* langQualName = "xml:lang";

    XMP_NodePtrPos ptrPos;

    XMP_Node* result = FindQualifierNode(parent, langQualName, true, &ptrPos);



    EXPECT_NE(result, nullptr);

    EXPECT_EQ(*ptrPos, result);

    EXPECT_EQ(result->name, langQualName);

    EXPECT_EQ(result->parent, parent);

    EXPECT_EQ(parent->qualifiers.size(), 1);

    EXPECT_TRUE((parent->options & kXMP_PropHasLang) != 0);

}



TEST_F(FindQualifierNodeTest_1896, CreateTypeQualifier_1896) {

    const char* typeQualName = "rdf:type";

    XMP_NodePtrPos ptrPos;

    XMP_Node* result = FindQualifierNode(parent, typeQualName, true, &ptrPos);



    EXPECT_NE(result, nullptr);

    EXPECT_EQ(*ptrPos, result);

    EXPECT_EQ(result->name, typeQualName);

    EXPECT_EQ(result->parent, parent);

    EXPECT_EQ(parent->qualifiers.size(), 1);

    EXPECT_TRUE((parent->options & kXMP_PropHasType) != 0);

}



TEST_F(FindQualifierNodeTest_1896, CreateLangAndTypeQualifiersOrder_1896) {

    const char* langQualName = "xml:lang";

    const char* typeQualName = "rdf:type";



    XMP_NodePtrPos ptrPos;

    FindQualifierNode(parent, langQualName, true, &ptrPos);

    FindQualifierNode(parent, typeQualName, true, &ptrPos);



    EXPECT_EQ(parent->qualifiers.size(), 2);

    EXPECT_EQ(parent->qualifiers[0]->name, langQualName);

    EXPECT_EQ(parent->qualifiers[1]->name, typeQualName);

}
