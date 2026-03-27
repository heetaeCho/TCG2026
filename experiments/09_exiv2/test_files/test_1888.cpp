#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPCore_Impl.hpp"

#include "XMP_Const.h"



class FollowXPathStepTest_1888 : public ::testing::Test {

protected:

    XMP_Node* parentNode;

    XMP_ExpandedXPath fullPath;

    XMP_NodePtrPos ptrPos;



    void SetUp() override {

        parentNode = new XMP_Node(nullptr, "parent", 0);

        ptrPos = nullptr;

    }



    void TearDown() override {

        delete parentNode;

    }

};



TEST_F(FollowXPathStepTest_1888, StructFieldStep_SuccessfulRetrieval_1888) {

    fullPath.push_back(XPathStepInfo("child", kXMP_StructFieldStep));

    XMP_Node* childNode = new XMP_Node(parentNode, "child", 0);

    parentNode->children.push_back(childNode);



    XMP_Node* result = FollowXPathStep(parentNode, fullPath, 0, false, &ptrPos);

    EXPECT_EQ(result, childNode);

}



TEST_F(FollowXPathStepTest_1888, StructFieldStep_CreateNodes_1888) {

    fullPath.push_back(XPathStepInfo("child", kXMP_StructFieldStep));



    XMP_Node* result = FollowXPathStep(parentNode, fullPath, 0, true, &ptrPos);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->name.c_str(), "child");

    EXPECT_EQ(parentNode->children.size(), 1);

}



TEST_F(FollowXPathStepTest_1888, QualifierStep_SuccessfulRetrieval_1888) {

    fullPath.push_back(XPathStepInfo("?qual", kXMP_QualifierStep));

    XMP_Node* qualifierNode = new XMP_Node(parentNode, "qual", 0);

    parentNode->qualifiers.push_back(qualifierNode);



    XMP_Node* result = FollowXPathStep(parentNode, fullPath, 0, false, &ptrPos);

    EXPECT_EQ(result, qualifierNode);

}



TEST_F(FollowXPathStepTest_1888, QualifierStep_CreateNodes_1888) {

    fullPath.push_back(XPathStepInfo("?qual", kXMP_QualifierStep));



    XMP_Node* result = FollowXPathStep(parentNode, fullPath, 0, true, &ptrPos);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->name.c_str(), "qual");

    EXPECT_EQ(parentNode->qualifiers.size(), 1);

}



TEST_F(FollowXPathStepTest_1888, ArrayIndexStep_SuccessfulRetrieval_1888) {

    fullPath.push_back(XPathStepInfo("[1]", kXMP_ArrayIndexStep));

    XMP_Node* arrayItem = new XMP_Node(parentNode, "item", 0);

    parentNode->children.push_back(arrayItem);

    parentNode->options |= kXMP_PropValueIsArray;



    XMP_Node* result = FollowXPathStep(parentNode, fullPath, 0, false, &ptrPos);

    EXPECT_EQ(result, arrayItem);

}



TEST_F(FollowXPathStepTest_1888, ArrayIndexStep_CreateNodes_1888) {

    fullPath.push_back(XPathStepInfo("[1]", kXMP_ArrayIndexStep));

    parentNode->options |= kXMP_PropValueIsArray;



    XMP_Node* result = FollowXPathStep(parentNode, fullPath, 0, true, &ptrPos);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(parentNode->children.size(), 1);

}



TEST_F(FollowXPathStepTest_1888, ArrayLastStep_SuccessfulRetrieval_1888) {

    fullPath.push_back(XPathStepInfo("last()", kXMP_ArrayLastStep));

    XMP_Node* arrayItem = new XMP_Node(parentNode, "item", 0);

    parentNode->children.push_back(arrayItem);

    parentNode->options |= kXMP_PropValueIsArray;



    XMP_Node* result = FollowXPathStep(parentNode, fullPath, 0, false, &ptrPos);

    EXPECT_EQ(result, arrayItem);

}



TEST_F(FollowXPathStepTest_1888, ArrayLastStep_CreateNodes_1888) {

    fullPath.push_back(XPathStepInfo("last()", kXMP_ArrayLastStep));

    parentNode->options |= kXMP_PropValueIsArray;



    XMP_Node* result = FollowXPathStep(parentNode, fullPath, 0, true, &ptrPos);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(parentNode->children.size(), 1);

}



TEST_F(FollowXPathStepTest_1888, FieldSelectorStep_SuccessfulRetrieval_1888) {

    fullPath.push_back(XPathStepInfo("name='value'", kXMP_FieldSelectorStep));

    XMP_Node* arrayItem = new XMP_Node(parentNode, "item", 0);

    parentNode->children.push_back(arrayItem);

    parentNode->options |= kXMP_PropValueIsArray;



    XMP_Node* result = FollowXPathStep(parentNode, fullPath, 0, false, &ptrPos);

    EXPECT_EQ(result, arrayItem);

}



TEST_F(FollowXPathStepTest_1888, FieldSelectorStep_CreateNodes_1888) {

    fullPath.push_back(XPathStepInfo("name='value'", kXMP_FieldSelectorStep));

    parentNode->options |= kXMP_PropValueIsArray;



    XMP_Node* result = FollowXPathStep(parentNode, fullPath, 0, true, &ptrPos);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(parentNode->children.size(), 1);

}



TEST_F(FollowXPathStepTest_1888, QualSelectorStep_SuccessfulRetrieval_1888) {

    fullPath.push_back(XPathStepInfo("?name='value'", kXMP_QualSelectorStep));

    XMP_Node* arrayItem = new XMP_Node(parentNode, "item", 0);

    parentNode->children.push_back(arrayItem);

    parentNode->options |= kXMP_PropValueIsArray;



    XMP_Node* result = FollowXPathStep(parentNode, fullPath, 0, false, &ptrPos);

    EXPECT_EQ(result, arrayItem);

}



TEST_F(FollowXPathStepTest_1888, QualSelectorStep_CreateNodes_1888) {

    fullPath.push_back(XPathStepInfo("?name='value'", kXMP_QualSelectorStep));

    parentNode->options |= kXMP_PropValueIsArray;



    XMP_Node* result = FollowXPathStep(parentNode, fullPath, 0, true, &ptrPos);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(parentNode->children.size(), 1);

}



TEST_F(FollowXPathStepTest_1888, QualSelectorStep_AliasedArrayItemCreation_1888) {

    fullPath.push_back(XPathStepInfo("?xml:lang=\"x-default\"", kXMP_QualSelectorStep));

    parentNode->options |= (kXMP_PropValueIsArray | kXMP_PropArrayIsAltText);



    XMP_Node* result = FollowXPathStep(parentNode, fullPath, 0, true, &ptrPos, true);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(parentNode->children.size(), 1);

    EXPECT_EQ(result->name.c_str(), "x-default");

    EXPECT_TRUE(result->options & kXMP_PropArrayIsAltText);

}



TEST_F(FollowXPathStepTest_1888, InvalidIndexingOnNonArrayNode_1888) {

    fullPath.push_back(XPathStepInfo("[1]", kXMP_ArrayIndexStep));



    EXPECT_THROW({

        FollowXPathStep(parentNode, fullPath, 0, false, &ptrPos);

    }, XMP_Error);



    try {

        FollowXPathStep(parentNode, fullPath, 0, false, &ptrPos);

    } catch (const XMP_Error& e) {

        EXPECT_EQ(e.GetID(), kXMPErr_BadXPath);

    }

}



TEST_F(FollowXPathStepTest_1888, UnknownArrayIndexingStep_1888) {

    fullPath.push_back(XPathStepInfo("unknown", 0));



    EXPECT_THROW({

        FollowXPathStep(parentNode, fullPath, 0, false, &ptrPos);

    }, XMP_Error);



    try {

        FollowXPathStep(parentNode, fullPath, 0, false, &ptrPos);

    } catch (const XMP_Error& e) {

        EXPECT_EQ(e.GetID(), kXMPErr_InternalFailure);

    }

}
