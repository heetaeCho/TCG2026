#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming XML_Node and related types are included from appropriate headers

using namespace std;



class XMLNodeTest : public ::testing::Test {

protected:

    XML_NodePtr parent;

    XML_NodePtr node;



    void SetUp() override {

        parent = std::make_shared<XML_Node>(nullptr, "root", kRootNode);

        node = std::make_shared<XML_Node>(parent, "test:element", kElemNode);

    }



    void TearDown() override {

        parent.reset();

        node.reset();

    }

};



TEST_F(XMLNodeTest_1976, CollectNamespaceDecls_NormalOperation_1976) {

    NamespaceMap nsMap;

    CollectNamespaceDecls(&nsMap, *node);

    EXPECT_EQ(nsMap.size(), 1);

    EXPECT_EQ(nsMap["test"], node->ns); // Assuming ns is set elsewhere in the codebase

}



TEST_F(XMLNodeTest_1976, CollectNamespaceDecls_NoNamespace_1976) {

    NamespaceMap nsMap;

    XML_NodePtr noNsNode = std::make_shared<XML_Node>(parent, "element", kElemNode);

    CollectNamespaceDecls(&nsMap, *noNsNode);

    EXPECT_EQ(nsMap.size(), 0);

}



TEST_F(XMLNodeTest_1976, CollectNamespaceDecls_AttributesWithNamespaces_1976) {

    NamespaceMap nsMap;

    XML_NodePtr attrNode = std::make_shared<XML_Node>(node, "attr:test", kAttrNode);

    node->attrs.push_back(attrNode);

    CollectNamespaceDecls(&nsMap, *node);

    EXPECT_EQ(nsMap.size(), 2); // One from the element and one from the attribute

}



TEST_F(XMLNodeTest_1976, CollectNamespaceDecls_ContentWithNamespaces_1976) {

    NamespaceMap nsMap;

    XML_NodePtr contentNode = std::make_shared<XML_Node>(node, "content:test", kElemNode);

    node->content.push_back(contentNode);

    CollectNamespaceDecls(&nsMap, *node);

    EXPECT_EQ(nsMap.size(), 2); // One from the element and one from the content

}



TEST_F(XMLNodeTest_1976, CollectNamespaceDecls_DuplicatePrefixes_1976) {

    NamespaceMap nsMap;

    XML_NodePtr attrNode = std::make_shared<XML_Node>(node, "test:attr", kAttrNode);

    node->attrs.push_back(attrNode);



    XML_NodePtr contentNode = std::make_shared<XML_Node>(node, "test:content", kElemNode);

    node->content.push_back(contentNode);



    CollectNamespaceDecls(&nsMap, *node);

    EXPECT_EQ(nsMap.size(), 1); // Only one entry for the prefix 'test'

}



TEST_F(XMLNodeTest_1976, CollectNamespaceDecls_EmptyElementName_1976) {

    NamespaceMap nsMap;

    XML_NodePtr emptyNode = std::make_shared<XML_Node>(parent, "", kElemNode);

    CollectNamespaceDecls(&nsMap, *emptyNode);

    EXPECT_EQ(nsMap.size(), 0); // No prefix to collect

}



TEST_F(XMLNodeTest_1976, CollectNamespaceDecls_BoundaryConditions_1976) {

    NamespaceMap nsMap;

    XML_NodePtr boundaryNode = std::make_shared<XML_Node>(parent, "a:b", kElemNode);

    CollectNamespaceDecls(&nsMap, *boundaryNode);

    EXPECT_EQ(nsMap.size(), 1); // Single prefix 'a'

}



TEST_F(XMLNodeTest_1976, CollectNamespaceDecls_ErrorHandling_NoColonInName_1976) {

    NamespaceMap nsMap;

    XML_NodePtr noColonNode = std::make_shared<XML_Node>(parent, "element", kElemNode);

    CollectNamespaceDecls(&nsMap, *noColonNode);

    EXPECT_EQ(nsMap.size(), 0); // No prefix to collect

}
