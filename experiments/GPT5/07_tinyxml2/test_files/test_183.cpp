// File: test_xmlnode_childelementcount_183.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeChildElementCountTest_183 : public ::testing::Test {
protected:
    XMLDocument doc;
};

TEST_F(XMLNodeChildElementCountTest_183, ReturnsZeroWhenNoChildElements_183) {
    // Document with no elements.
    const XMLNode* node = &doc;
    EXPECT_EQ(node->ChildElementCount(), 0);

    // Explicit empty root element with no children.
    XMLElement* root = doc.NewElement("root");
    ASSERT_NE(root, nullptr);
    doc.InsertEndChild(root);

    const XMLNode* rootNode = root;
    EXPECT_EQ(rootNode->ChildElementCount(), 0);
}

TEST_F(XMLNodeChildElementCountTest_183, CountsDirectChildElementsOnly_183) {
    // <root><a/><b/><c/></root>
    XMLElement* root = doc.NewElement("root");
    ASSERT_NE(root, nullptr);
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("c"));

    const XMLNode* rootNode = root;
    EXPECT_EQ(rootNode->ChildElementCount(), 3);
}

TEST_F(XMLNodeChildElementCountTest_183, IgnoresNonElementChildren_183) {
    // Mix text and comments between elements; only elements should be counted.
    // <root>text<!--c--><a/>more<b/><!--d--></root>
    XMLElement* root = doc.NewElement("root");
    ASSERT_NE(root, nullptr);
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewText("text"));
    root->InsertEndChild(doc.NewComment("c"));
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewText("more"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewComment("d"));

    const XMLNode* rootNode = root;
    EXPECT_EQ(rootNode->ChildElementCount(), 2);
}

TEST_F(XMLNodeChildElementCountTest_183, DoesNotCountGrandchildren_183) {
    // <root><parent><child1/><child2/></parent><sibling/></root>
    XMLElement* root = doc.NewElement("root");
    ASSERT_NE(root, nullptr);
    doc.InsertEndChild(root);

    XMLElement* parent = doc.NewElement("parent");
    ASSERT_NE(parent, nullptr);
    root->InsertEndChild(parent);

    parent->InsertEndChild(doc.NewElement("child1"));
    parent->InsertEndChild(doc.NewElement("child2"));

    root->InsertEndChild(doc.NewElement("sibling"));

    const XMLNode* rootNode = root;
    const XMLNode* parentNode = parent;

    EXPECT_EQ(rootNode->ChildElementCount(), 2);   // parent, sibling
    EXPECT_EQ(parentNode->ChildElementCount(), 2); // child1, child2
}

TEST_F(XMLNodeChildElementCountTest_183, WorksViaParsingAndConstNode_183) {
    // Parse XML and call via const pointers.
    const char* xml =
        "<root>"
        "  <a/>"
        "  <b/>"
        "  <c><x/></c>"
        "</root>";

    XMLDocument parsed;
    ASSERT_EQ(parsed.Parse(xml), XML_SUCCESS);

    const XMLElement* root = parsed.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLNode* rootNode = root;
    EXPECT_EQ(rootNode->ChildElementCount(), 3);

    const XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(c, nullptr);
    const XMLNode* cNode = c;
    EXPECT_EQ(cNode->ChildElementCount(), 1);
}

TEST_F(XMLNodeChildElementCountTest_183, UpdatesAfterDeleteChildren_183) {
    XMLElement* root = doc.NewElement("root");
    ASSERT_NE(root, nullptr);
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    EXPECT_EQ(root->ChildElementCount(), 2);

    root->DeleteChildren();
    EXPECT_EQ(root->ChildElementCount(), 0);

    // Add again after deletion.
    root->InsertEndChild(doc.NewElement("c"));
    EXPECT_EQ(root->ChildElementCount(), 1);
}
