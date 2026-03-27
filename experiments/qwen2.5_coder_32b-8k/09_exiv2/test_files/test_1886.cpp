#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPCore_Impl.hpp"

#include "XMP_Const.h"



using namespace std;

using testing::Eq;



class XMP_NodeTest_1886 : public ::testing::Test {

protected:

    void SetUp() override {

        parent = new XMP_Node(nullptr, kXMP_ArrayItemName, kXMP_NewImplicitNode);

    }



    void TearDown() override {

        delete parent;

    }



    XMP_Node* parent;

};



TEST_F(XMP_NodeTest_1886, FindIndexedItem_NormalOperation_1886) {

    const XMP_VarString indexStep = "[2]";

    XMP_Index index = FindIndexedItem(parent, indexStep, false);

    EXPECT_EQ(index, 1);

}



TEST_F(XMP_NodeTest_1886, FindIndexedItem_BoundaryCondition_EmptyArray_1886) {

    const XMP_VarString indexStep = "[1]";

    XMP_Index index = FindIndexedItem(parent, indexStep, false);

    EXPECT_EQ(index, -1);

}



TEST_F(XMP_NodeTest_1886, FindIndexedItem_BoundaryCondition_CreateNodes_1886) {

    const XMP_VarString indexStep = "[2]";

    XMP_Index index = FindIndexedItem(parent, indexStep, true);

    EXPECT_EQ(index, 1);

    EXPECT_EQ(parent->children.size(), 2U);

}



TEST_F(XMP_NodeTest_1886, FindIndexedItem_ExceptionalCase_ZeroIndex_1886) {

    const XMP_VarString indexStep = "[0]";

    EXPECT_THROW(FindIndexedItem(parent, indexStep, false), XMP_Error);

}



TEST_F(XMP_NodeTest_1886, FindIndexedItem_ExceptionalCase_NegativeIndex_1886) {

    const XMP_VarString indexStep = "[-1]";

    EXPECT_THROW(FindIndexedItem(parent, indexStep, false), XMP_Error);

}



TEST_F(XMP_NodeTest_1886, FindIndexedItem_ExceptionalCase_BadFormat_1886) {

    const XMP_VarString indexStep = "[abc]";

    EXPECT_THROW(FindIndexedItem(parent, indexStep, false), XMP_Error);

}



TEST_F(XMP_NodeTest_1886, FindIndexedItem_ExceptionalCase_OutOfBounds_1886) {

    parent->children.push_back(new XMP_Node(parent, kXMP_ArrayItemName, kXMP_NewImplicitNode));

    const XMP_VarString indexStep = "[3]";

    XMP_Index index = FindIndexedItem(parent, indexStep, false);

    EXPECT_EQ(index, -1);

}



TEST_F(XMP_NodeTest_1886, FindIndexedItem_ExceptionalCase_OverflowIndex_1886) {

    const XMP_VarString indexStep = "[9223372036854775807]"; // Very large number to cause overflow

    EXPECT_THROW(FindIndexedItem(parent, indexStep, false), XMP_Error);

}
