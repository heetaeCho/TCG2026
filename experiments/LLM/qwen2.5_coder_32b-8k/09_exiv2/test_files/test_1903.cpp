#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"

#include <memory>



class DeleteEmptySchemaTest_1903 : public ::testing::Test {

protected:

    void SetUp() override {

        root = std::make_unique<XMP_Node>(nullptr, "root", 0);

        schemaNode = std::make_unique<XMP_Node>(root.get(), "schema", kXMPCore_DebugFlag);

        nonEmptySchemaNode = std::make_unique<XMP_Node>(root.get(), "nonEmptySchema", kXMPCore_DebugFlag);

        childNode = std::make_unique<XMP_Node>(schemaNode.get(), "child", "value", 0);

        

        schemaNode->children.push_back(childNode.get());

        root->children.push_back(schemaNode.get());

        root->children.push_back(nonEmptySchemaNode.get());



        // Remove the unique_ptr ownership temporarily for testing

        childNode.release();

        schemaNode.release();

        nonEmptySchemaNode.release();

    }



    void TearDown() override {

        // Clean up nodes manually since we released them from unique_ptr

        delete childNode;

        delete schemaNode;

        delete nonEmptySchemaNode;

        delete root.get();

    }



    XMP_Node* root = nullptr;

    XMP_Node* schemaNode = nullptr;

    XMP_Node* nonEmptySchemaNode = nullptr;

    XMP_Node* childNode = nullptr;

};



TEST_F(DeleteEmptySchemaTest_1903, DeleteEmptySchema_SuccessfulDeletion_1903) {

    schemaNode->children.clear();

    DeleteEmptySchema(schemaNode);

    EXPECT_EQ(root->children.size(), 2); // root should have nonEmptySchemaNode and schemaNode is deleted

    for (const auto& child : root->children) {

        EXPECT_NE(child, schemaNode);

    }

}



TEST_F(DeleteEmptySchemaTest_1903, DeleteNonEmptySchema_NoDeletion_1903) {

    DeleteEmptySchema(nonEmptySchemaNode);

    EXPECT_EQ(root->children.size(), 2); // root should still have both schemaNode and nonEmptySchemaNode

}



TEST_F(DeleteEmptySchemaTest_1903, DeleteEmptySchema_RootHasNoChildrenAfterDeletion_1903) {

    schemaNode->children.clear();

    nonEmptySchemaNode->children.clear();

    DeleteEmptySchema(schemaNode);

    DeleteEmptySchema(nonEmptySchemaNode);

    EXPECT_EQ(root->children.size(), 0); // root should have no children after deleting both

}



TEST_F(DeleteEmptySchemaTest_1903, DeleteNullSchema_NoDeletion_1903) {

    XMP_Node* nullNode = nullptr;

    DeleteEmptySchema(nullNode);

    EXPECT_EQ(root->children.size(), 2); // root should still have both schemaNode and nonEmptySchemaNode

}



TEST_F(DeleteEmptySchemaTest_1903, DeleteNonSchemaNode_NoDeletion_1903) {

    XMP_Node* nonSchemaNode = new XMP_Node(root.get(), "nonSchema", 0);

    root->children.push_back(nonSchemaNode);



    DeleteEmptySchema(nonSchemaNode);

    EXPECT_EQ(root->children.size(), 3); // root should still have schemaNode, nonEmptySchemaNode and nonSchemaNode



    // Clean up

    delete nonSchemaNode;

}
