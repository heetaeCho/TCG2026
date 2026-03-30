#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming XMP_Node and related constants are available in the test environment



class TransplantArrayItemAliasTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize nodes for testing

        oldParent = new XMP_Node(nullptr, "oldParent", 0);

        childNode = new XMP_Node(oldParent, "childNode", 0);

        newParent = new XMP_Node(nullptr, "newParent", kXMP_PropArrayIsAltText);



        oldParent->children.push_back(childNode);

    }



    void TearDown() override {

        // Clean up nodes after testing

        delete childNode;

        delete newParent;

        delete oldParent;

    }



    XMP_Node* oldParent;

    XMP_Node* childNode;

    XMP_Node* newParent;

};



TEST_F(TransplantArrayItemAliasTest_1963, NormalOperation_1963) {

    TransplantArrayItemAlias(oldParent, 0, newParent);

    EXPECT_EQ(childNode->parent, newParent);

    EXPECT_EQ(newParent->children.size(), 1);

    EXPECT_TRUE(childNode->options & kXMP_PropHasQualifiers);

    EXPECT_TRUE(childNode->options & kXMP_PropHasLang);

}



TEST_F(TransplantArrayItemAliasTest_1963, BoundaryCondition_EmptyChildren_1963) {

    oldParent->children.clear();

    EXPECT_THROW(TransplantArrayItemAlias(oldParent, 0, newParent), XMP_Error);

}



TEST_F(TransplantArrayItemAliasTest_1963, ExceptionalCase_AlreadyHasLang_1963) {

    childNode->options |= kXMP_PropHasLang;

    EXPECT_THROW(TransplantArrayItemAlias(oldParent, 0, newParent), XMP_Error);

}



TEST_F(TransplantArrayItemAliasTest_1963, BoundaryCondition_OutOfBoundsIndex_1963) {

    EXPECT_THROW(TransplantArrayItemAlias(oldParent, 1, newParent), XMP_Error);

}
