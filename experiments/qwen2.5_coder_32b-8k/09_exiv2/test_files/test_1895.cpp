#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"

#include "XMP_Const.h"



class XMPCoreTest_1895 : public ::testing::Test {

protected:

    XMP_Node* parent;

    XMP_StringPtr childName = "childNode";

    XMP_OptionBits options = kXMP_PropValueIsStruct;



    void SetUp() override {

        parent = new XMP_Node(nullptr, "parentNode", options);

    }



    void TearDown() override {

        delete parent;

    }

};



TEST_F(XMPCoreTest_1895, FindChildNode_NormalOperation_CreateNodesTrue_1895) {

    XMP_Node* childNode = FindChildNode(parent, childName, true);

    EXPECT_NE(childNode, nullptr);

    EXPECT_EQ(childNode->name, "childNode");

}



TEST_F(XMPCoreTest_1895, FindChildNode_NormalOperation_CreateNodesFalse_1895) {

    XMP_Node* createdChild = FindChildNode(parent, childName, true);

    XMP_Node* foundChild = FindChildNode(parent, childName, false);

    EXPECT_EQ(createdChild, foundChild);

}



TEST_F(XMPCoreTest_1895, FindChildNode_Boundary_NoChildren_1895) {

    XMP_Node* childNode = FindChildNode(parent, "nonExistentChild", false);

    EXPECT_EQ(childNode, nullptr);

}



TEST_F(XMPCoreTest_1895, FindChildNode_Error_NamedChildrenNotSchemaOrStruct_1895) {

    parent->options &= ~kXMP_PropValueIsStruct;

    EXPECT_THROW(FindChildNode(parent, childName, true), XMP_Error);

}



TEST_F(XMPCoreTest_1895, FindChildNode_Error_NamedChildrenInArray_1895) {

    parent->options = kXMP_PropValueIsArray | kXMP_NewImplicitNode;

    EXPECT_THROW(FindChildNode(parent, childName, true), XMP_Error);

}



TEST_F(XMPCoreTest_1895, FindChildNode_Error_CreateNodesFalseForNewImplicitNode_1895) {

    parent->options = kXMP_NewImplicitNode;

    EXPECT_THROW(FindChildNode(parent, childName, false), XMP_Error);

}



TEST_F(XMPCoreTest_1895, FindChildNode_VerifyPtrPos_SetWhenFound_1895) {

    XMP_Node* createdChild = FindChildNode(parent, childName, true);

    XMP_NodePtrPos ptrPos;

    XMP_Node* foundChild = FindChildNode(parent, childName, false, &ptrPos);

    EXPECT_EQ(createdChild, *ptrPos);

}



TEST_F(XMPCoreTest_1895, FindChildNode_VerifyPtrPos_SetWhenCreated_1895) {

    XMP_NodePtrPos ptrPos;

    XMP_Node* childNode = FindChildNode(parent, childName, true, &ptrPos);

    EXPECT_EQ(childNode, *ptrPos);

}
