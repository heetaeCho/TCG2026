#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"

#include "XMP_Const.h"



class DeleteSubtreeTest_1890 : public ::testing::Test {

protected:

    XMP_Node* root;

    XMP_Node* child;

    XMP_Node* qualifier;



    void SetUp() override {

        root = new XMP_Node(nullptr, "root", 0);

        child = new XMP_Node(root, "child", 0);

        qualifier = new XMP_Node(root, "xml:lang", kXMP_PropIsQualifier);



        root->children.push_back(child);

        root->qualifiers.push_back(qualifier);

    }



    void TearDown() override {

        delete root;

    }

};



TEST_F(DeleteSubtreeTest_1890, DeleteChildNode_1890) {

    XMP_NodePtrPos childPos = root->children.begin();

    DeleteSubtree(childPos);



    EXPECT_EQ(root->children.size(), 0);

}



TEST_F(DeleteSubtreeTest_1890, DeleteQualifierNodeWithLang_1890) {

    XMP_NodePtrPos qualifierPos = root->qualifiers.begin();

    DeleteSubtree(qualifierPos);



    EXPECT_EQ(root->qualifiers.size(), 0);

    EXPECT_TRUE(!(root->options & kXMP_PropHasLang));

}



TEST_F(DeleteSubtreeTest_1890, DeleteQualifierNodeWithOtherName_1890) {

    qualifier->name = "other";

    XMP_NodePtrPos qualifierPos = root->qualifiers.begin();

    DeleteSubtree(qualifierPos);



    EXPECT_EQ(root->qualifiers.size(), 0);

    EXPECT_TRUE(!(root->options & kXMP_PropHasType));

}



TEST_F(DeleteSubtreeTest_1890, DeleteLastQualifierNode_1890) {

    XMP_NodePtrPos qualifierPos = root->qualifiers.begin();

    DeleteSubtree(qualifierPos);



    EXPECT_TRUE(!(root->options & kXMP_PropHasQualifiers));

}



TEST_F(DeleteSubtreeTest_1890, BoundaryConditionEmptyChildren_1890) {

    root->children.clear();

    XMP_NodePtrPos childPos = root->children.begin();



    DeleteSubtree(childPos);  // This should handle gracefully with no effect



    EXPECT_EQ(root->children.size(), 0);

}



TEST_F(DeleteSubtreeTest_1890, BoundaryConditionEmptyQualifiers_1890) {

    root->qualifiers.clear();

    XMP_NodePtrPos qualifierPos = root->qualifiers.begin();



    DeleteSubtree(qualifierPos);  // This should handle gracefully with no effect



    EXPECT_EQ(root->qualifiers.size(), 0);

}



TEST_F(DeleteSubtreeTest_1890, ExceptionalCaseNullPointer_1890) {

    XMP_NodePtrPos nullPos = root->children.end();



    DeleteSubtree(nullPos);  // This should handle gracefully with no effect

}
