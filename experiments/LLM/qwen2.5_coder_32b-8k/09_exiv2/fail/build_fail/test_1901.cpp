#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"



class XmpNodeTest_1901 : public ::testing::Test {

protected:

    void SetUp() override {

        parent = new XMP_Node(nullptr, "parent", kXMP_SchemaNode);

        origRoot = new XMP_Node(parent, "original", "value", 0);

    }



    void TearDown() override {

        delete origRoot;

        delete parent;

    }



    XMP_Node *parent;

    XMP_Node *origRoot;

};



TEST_F(XmpNodeTest_1901, CloneSubtree_NormalOperation_1901) {

    XMP_Node* cloneParent = new XMP_Node(nullptr, "cloneParent", kXMP_SchemaNode);

    XMP_Node* clonedNode = CloneSubtree(origRoot, cloneParent);



    EXPECT_EQ(clonedNode->name, origRoot->name);

    EXPECT_EQ(clonedNode->value, origRoot->value);

    EXPECT_EQ(clonedNode->options, origRoot->options);

    EXPECT_EQ(clonedNode->parent, cloneParent);

    EXPECT_EQ(cloneParent->children.size(), 1);



    delete cloneParent;

}



TEST_F(XmpNodeTest_1901, CloneSubtree_BoundaryCondition_EmptyName_1901) {

    XMP_Node* emptyNameNode = new XMP_Node(parent, "", "value", 0);

    XMP_Node* cloneParent = new XMP_Node(nullptr, "cloneParent", kXMP_SchemaNode);

    XMP_Node* clonedNode = CloneSubtree(emptyNameNode, cloneParent);



    EXPECT_EQ(clonedNode->name, "");

    EXPECT_EQ(clonedNode->value, emptyNameNode->value);

    EXPECT_EQ(clonedNode->options, emptyNameNode->options);

    EXPECT_EQ(clonedNode->parent, cloneParent);

    EXPECT_EQ(cloneParent->children.size(), 1);



    delete emptyNameNode;

    delete cloneParent;

}



TEST_F(XmpNodeTest_1901, CloneSubtree_BoundaryCondition_EmptyValue_1901) {

    XMP_Node* emptyValueNode = new XMP_Node(parent, "original", "", 0);

    XMP_Node* cloneParent = new XMP_Node(nullptr, "cloneParent", kXMP_SchemaNode);

    XMP_Node* clonedNode = CloneSubtree(emptyValueNode, cloneParent);



    EXPECT_EQ(clonedNode->name, emptyValueNode->name);

    EXPECT_EQ(clonedNode->value, "");

    EXPECT_EQ(clonedNode->options, emptyValueNode->options);

    EXPECT_EQ(clonedNode->parent, cloneParent);

    EXPECT_EQ(cloneParent->children.size(), 1);



    delete emptyValueNode;

    delete cloneParent;

}



TEST_F(XmpNodeTest_1901, CloneSubtree_ExceptionalCase_CloneNonSchemaToSchema_1901) {

    XMP_Node* nonSchemaNode = new XMP_Node(parent, "nonSchema", "value", 0);

    XMP_Node* schemaParent = new XMP_Node(nullptr, "schemaParent", kXMP_SchemaNode);



#ifdef XMP_DebugBuild

    EXPECT_DEATH(CloneSubtree(nonSchemaNode, schemaParent), "");

#else

    CloneSubtree(nonSchemaNode, schemaParent);

#endif



    delete nonSchemaNode;

    delete schemaParent;

}



TEST_F(XmpNodeTest_1901, CloneSubtree_ExceptionalCase_CloneSchemaToNonSchema_1901) {

    XMP_Node* schemaNode = new XMP_Node(parent, "schema", "value", kXMP_SchemaNode);

    XMP_Node* nonSchemaParent = new XMP_Node(nullptr, "nonSchemaParent", 0);



#ifdef XMP_DebugBuild

    EXPECT_DEATH(CloneSubtree(schemaNode, nonSchemaParent), "");

#else

    CloneSubtree(schemaNode, nonSchemaParent);

#endif



    delete schemaNode;

    delete nonSchemaParent;

}
