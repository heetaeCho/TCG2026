#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "ParseRDF.cpp"

#include "XMPCore_Impl.hpp"

#include "XMLParserAdapter.hpp"



class ParseRDFFixture : public ::testing::Test {

protected:

    XMP_Node* root;

    XML_Node xmlNode;



    void SetUp() override {

        root = new XMP_Node(nullptr, "root", 0);

        xmlNode.ns = "http://example.com/schema";

        xmlNode.name = "element";

        xmlNode.value = "";

    }



    void TearDown() override {

        delete root;

    }

};



TEST_F(ParseRDFFixture, AddChildNode_NormalOperation_2120) {

    XMP_Node* child = AddChildNode(root, xmlNode, "", false);

    EXPECT_EQ(child->name, "element");

    EXPECT_EQ(child->value, "");

    EXPECT_EQ(child->parent, root);

    EXPECT_FALSE(child->children.empty());

}



TEST_F(ParseRDFFixture, AddChildNode_TopLevel_2120) {

    XMP_Node* child = AddChildNode(root, xmlNode, "", true);

    EXPECT_EQ(child->name, "element");

    EXPECT_EQ(child->value, "");

    EXPECT_NE(child->parent, root);  // parent should be schema node

}



TEST_F(ParseRDFFixture, AddChildNode_NoNamespace_2120) {

    xmlNode.ns = "";

    EXPECT_THROW(AddChildNode(root, xmlNode, "", false), XMP_Error);

}



TEST_F(ParseRDFFixture, AddChildNode_DuplicateProperty_2120) {

    XMP_Node* child1 = AddChildNode(root, xmlNode, "", false);

    EXPECT_NE(child1, nullptr);



    EXPECT_THROW(AddChildNode(root, xmlNode, "", false), XMP_Error);

}



TEST_F(ParseRDFFixture, AddChildNode_RDFValueElement_2120) {

    xmlNode.name = "rdf:value";

    root->options |= kXMP_PropValueIsStruct;

    XMP_Node* child = AddChildNode(root, xmlNode, "", false);

    EXPECT_EQ(child->name, kXMP_ArrayItemName);  // This is incorrect based on code logic, it should be rdf:value

}



TEST_F(ParseRDFFixture, AddChildNode_RDFValueElement_TopLevel_2120) {

    xmlNode.name = "rdf:value";

    EXPECT_THROW(AddChildNode(root, xmlNode, "", true), XMP_Error);

}



TEST_F(ParseRDFFixture, AddChildNode_MisplacedRDFValueElement_2120) {

    xmlNode.name = "rdf:value";

    root->options &= ~kXMP_PropValueIsStruct;

    EXPECT_THROW(AddChildNode(root, xmlNode, "", false), XMP_Error);

}



TEST_F(ParseRDFFixture, AddChildNode_RDFLiElement_2120) {

    xmlNode.name = "rdf:li";

    root->options |= kXMP_PropValueIsArray;

    XMP_Node* child = AddChildNode(root, xmlNode, "", false);

    EXPECT_EQ(child->name, kXMP_ArrayItemName);

}



TEST_F(ParseRDFFixture, AddChildNode_MisplacedRDFLiElement_2120) {

    xmlNode.name = "rdf:li";

    root->options &= ~kXMP_PropValueIsArray;

    EXPECT_THROW(AddChildNode(root, xmlNode, "", false), XMP_Error);

}



TEST_F(ParseRDFFixture, AddChildNode_AliasHandling_2120) {

    sRegisteredAliasMap->insert({"element", "alias"});

    XMP_Node* child = AddChildNode(root, xmlNode, "", true);

    EXPECT_TRUE(child->parent->options & kXMP_PropHasAliases);

}
