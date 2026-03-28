#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleTest_134 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test constructing XMLConstHandle with a null node
TEST_F(XMLConstHandleTest_134, ConstructWithNullNode_134) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test constructing XMLConstHandle with a valid node
TEST_F(XMLConstHandleTest_134, ConstructWithValidNode_134) {
    doc->Parse("<root><child/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test constructing XMLConstHandle with a node reference
TEST_F(XMLConstHandleTest_134, ConstructWithNodeReference_134) {
    doc->Parse("<root><child/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(*root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test copy constructor
TEST_F(XMLConstHandleTest_134, CopyConstructor_134) {
    doc->Parse("<root><child/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle1(root);
    XMLConstHandle handle2(handle1);
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test assignment operator
TEST_F(XMLConstHandleTest_134, AssignmentOperator_134) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle1(root);
    XMLConstHandle handle2(static_cast<const XMLNode*>(nullptr));
    handle2 = handle1;
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test FirstChild on a node with children
TEST_F(XMLConstHandleTest_134, FirstChildWithChildren_134) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_NE(firstChild.ToNode(), nullptr);
    EXPECT_EQ(firstChild.ToNode(), root->FirstChild());
}

// Test FirstChild on a node with no children
TEST_F(XMLConstHandleTest_134, FirstChildNoChildren_134) {
    doc->Parse("<root/>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChild on a null handle
TEST_F(XMLConstHandleTest_134, FirstChildNullHandle_134) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChildElement on a node with matching element
TEST_F(XMLConstHandleTest_134, FirstChildElementWithMatch_134) {
    doc->Parse("<root><alpha/><beta/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle elem = handle.FirstChildElement("beta");
    EXPECT_NE(elem.ToElement(), nullptr);
    EXPECT_STREQ(elem.ToElement()->Name(), "beta");
}

// Test FirstChildElement with no name (gets first element)
TEST_F(XMLConstHandleTest_134, FirstChildElementNoName_134) {
    doc->Parse("<root><alpha/><beta/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle elem = handle.FirstChildElement();
    EXPECT_NE(elem.ToElement(), nullptr);
    EXPECT_STREQ(elem.ToElement()->Name(), "alpha");
}

// Test FirstChildElement with no matching element
TEST_F(XMLConstHandleTest_134, FirstChildElementNoMatch_134) {
    doc->Parse("<root><alpha/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle elem = handle.FirstChildElement("nonexistent");
    EXPECT_EQ(elem.ToElement(), nullptr);
}

// Test FirstChildElement on a null handle
TEST_F(XMLConstHandleTest_134, FirstChildElementNullHandle_134) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle elem = handle.FirstChildElement("anything");
    EXPECT_EQ(elem.ToElement(), nullptr);
}

// Test LastChild on a node with children
TEST_F(XMLConstHandleTest_134, LastChildWithChildren_134) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_NE(lastChild.ToNode(), nullptr);
    EXPECT_EQ(lastChild.ToNode(), root->LastChild());
}

// Test LastChild on a null handle
TEST_F(XMLConstHandleTest_134, LastChildNullHandle_134) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_EQ(lastChild.ToNode(), nullptr);
}

// Test LastChildElement on a node with matching elements
TEST_F(XMLConstHandleTest_134, LastChildElementWithMatch_134) {
    doc->Parse("<root><alpha/><beta/><alpha/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle elem = handle.LastChildElement("alpha");
    EXPECT_NE(elem.ToElement(), nullptr);
    EXPECT_STREQ(elem.ToElement()->Name(), "alpha");
    // Should be the last alpha, not the first
    EXPECT_EQ(elem.ToElement(), root->LastChildElement("alpha"));
}

// Test LastChildElement with no name
TEST_F(XMLConstHandleTest_134, LastChildElementNoName_134) {
    doc->Parse("<root><alpha/><beta/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle elem = handle.LastChildElement();
    EXPECT_NE(elem.ToElement(), nullptr);
    EXPECT_STREQ(elem.ToElement()->Name(), "beta");
}

// Test LastChildElement on a null handle
TEST_F(XMLConstHandleTest_134, LastChildElementNullHandle_134) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle elem = handle.LastChildElement();
    EXPECT_EQ(elem.ToElement(), nullptr);
}

// Test PreviousSibling
TEST_F(XMLConstHandleTest_134, PreviousSibling_134) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* child2 = root->FirstChildElement("child2");
    ASSERT_NE(child2, nullptr);

    XMLConstHandle handle(child2);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_NE(prev.ToNode(), nullptr);
    EXPECT_EQ(prev.ToNode(), child2->PreviousSibling());
}

// Test PreviousSibling on first child (no previous sibling)
TEST_F(XMLConstHandleTest_134, PreviousSiblingNoPrevious_134) {
    doc->Parse("<root><child1/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);

    XMLConstHandle handle(child1);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSibling on a null handle
TEST_F(XMLConstHandleTest_134, PreviousSiblingNullHandle_134) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSiblingElement
TEST_F(XMLConstHandleTest_134, PreviousSiblingElement_134) {
    doc->Parse("<root><alpha/><beta/><gamma/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* gamma = root->FirstChildElement("gamma");
    ASSERT_NE(gamma, nullptr);

    XMLConstHandle handle(gamma);
    XMLConstHandle prevElem = handle.PreviousSiblingElement("alpha");
    EXPECT_NE(prevElem.ToElement(), nullptr);
    EXPECT_STREQ(prevElem.ToElement()->Name(), "alpha");
}

// Test PreviousSiblingElement with no name
TEST_F(XMLConstHandleTest_134, PreviousSiblingElementNoName_134) {
    doc->Parse("<root><alpha/><beta/><gamma/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* gamma = root->FirstChildElement("gamma");
    ASSERT_NE(gamma, nullptr);

    XMLConstHandle handle(gamma);
    XMLConstHandle prevElem = handle.PreviousSiblingElement();
    EXPECT_NE(prevElem.ToElement(), nullptr);
    EXPECT_STREQ(prevElem.ToElement()->Name(), "beta");
}

// Test PreviousSiblingElement on a null handle
TEST_F(XMLConstHandleTest_134, PreviousSiblingElementNullHandle_134) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle prevElem = handle.PreviousSiblingElement();
    EXPECT_EQ(prevElem.ToElement(), nullptr);
}

// Test NextSibling
TEST_F(XMLConstHandleTest_134, NextSibling_134) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);

    XMLConstHandle handle(child1);
    XMLConstHandle next = handle.NextSibling();
    EXPECT_NE(next.ToNode(), nullptr);
    EXPECT_EQ(next.ToNode(), child1->NextSibling());
}

// Test NextSibling on last child (no next sibling)
TEST_F(XMLConstHandleTest_134, NextSiblingNoNext_134) {
    doc->Parse("<root><child1/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);

    XMLConstHandle handle(child1);
    XMLConstHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test NextSibling on a null handle
TEST_F(XMLConstHandleTest_134, NextSiblingNullHandle_134) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test NextSiblingElement
TEST_F(XMLConstHandleTest_134, NextSiblingElement_134) {
    doc->Parse("<root><alpha/><beta/><gamma/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* alpha = root->FirstChildElement("alpha");
    ASSERT_NE(alpha, nullptr);

    XMLConstHandle handle(alpha);
    XMLConstHandle nextElem = handle.NextSiblingElement("gamma");
    EXPECT_NE(nextElem.ToElement(), nullptr);
    EXPECT_STREQ(nextElem.ToElement()->Name(), "gamma");
}

// Test NextSiblingElement with no name
TEST_F(XMLConstHandleTest_134, NextSiblingElementNoName_134) {
    doc->Parse("<root><alpha/><beta/><gamma/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* alpha = root->FirstChildElement("alpha");
    ASSERT_NE(alpha, nullptr);

    XMLConstHandle handle(alpha);
    XMLConstHandle nextElem = handle.NextSiblingElement();
    EXPECT_NE(nextElem.ToElement(), nullptr);
    EXPECT_STREQ(nextElem.ToElement()->Name(), "beta");
}

// Test NextSiblingElement on a null handle
TEST_F(XMLConstHandleTest_134, NextSiblingElementNullHandle_134) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle nextElem = handle.NextSiblingElement();
    EXPECT_EQ(nextElem.ToElement(), nullptr);
}

// Test ToNode returns the underlying node
TEST_F(XMLConstHandleTest_134, ToNodeReturnsNode_134) {
    doc->Parse("<root/>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test ToNode on null handle
TEST_F(XMLConstHandleTest_134, ToNodeNullHandle_134) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test ToElement returns element when node is an element
TEST_F(XMLConstHandleTest_134, ToElementReturnsElement_134) {
    doc->Parse("<root/>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(static_cast<const XMLNode*>(root));
    EXPECT_NE(handle.ToElement(), nullptr);
    EXPECT_EQ(handle.ToElement(), root);
}

// Test ToElement returns null when node is not an element
TEST_F(XMLConstHandleTest_134, ToElementReturnsNullForNonElement_134) {
    doc->Parse("<!-- comment --><root/>");
    const XMLNode* comment = doc->FirstChild();
    ASSERT_NE(comment, nullptr);
    // The first child should be a comment
    ASSERT_NE(comment->ToComment(), nullptr);

    XMLConstHandle handle(comment);
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test ToElement on null handle
TEST_F(XMLConstHandleTest_134, ToElementNullHandle_134) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test ToText returns text node
TEST_F(XMLConstHandleTest_134, ToTextReturnsText_134) {
    doc->Parse("<root>Hello</root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* textNode = root->FirstChild();
    ASSERT_NE(textNode, nullptr);

    XMLConstHandle handle(textNode);
    EXPECT_NE(handle.ToText(), nullptr);
}

// Test ToText returns null for non-text node
TEST_F(XMLConstHandleTest_134, ToTextReturnsNullForNonText_134) {
    doc->Parse("<root/>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToText on null handle
TEST_F(XMLConstHandleTest_134, ToTextNullHandle_134) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToUnknown
TEST_F(XMLConstHandleTest_134, ToUnknownReturnsUnknown_134) {
    doc->Parse("<!DOCTYPE foo><root/>");
    // Find the unknown node - DOCTYPE is parsed as unknown
    const XMLNode* node = doc->FirstChild();
    // If the first child is not unknown, skip
    if (node && node->ToUnknown()) {
        XMLConstHandle handle(node);
        EXPECT_NE(handle.ToUnknown(), nullptr);
    }
}

// Test ToUnknown on null handle
TEST_F(XMLConstHandleTest_134, ToUnknownNullHandle_134) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToDeclaration returns declaration node
TEST_F(XMLConstHandleTest_134, ToDeclarationReturnsDeclaration_134) {
    doc->Parse("<?xml version=\"1.0\"?><root/>");
    const XMLNode* node = doc->FirstChild();
    ASSERT_NE(node, nullptr);

    if (node->ToDeclaration()) {
        XMLConstHandle handle(node);
        EXPECT_NE(handle.ToDeclaration(), nullptr);
    }
}

// Test ToDeclaration on null handle
TEST_F(XMLConstHandleTest_134, ToDeclarationNullHandle_134) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test chaining: FirstChild().FirstChildElement()
TEST_F(XMLConstHandleTest_134, ChainingNavigation_134) {
    doc->Parse("<root><parent><child/></parent></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle child = handle.FirstChildElement("parent").FirstChildElement("child");
    EXPECT_NE(child.ToElement(), nullptr);
    EXPECT_STREQ(child.ToElement()->Name(), "child");
}

// Test chaining with null intermediate result
TEST_F(XMLConstHandleTest_134, ChainingWithNullIntermediate_134) {
    doc->Parse("<root><parent/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    // "nonexistent" doesn't exist, so intermediate is null, and further navigation should be safe
    XMLConstHandle result = handle.FirstChildElement("nonexistent").FirstChildElement("child");
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test deep chaining with multiple levels
TEST_F(XMLConstHandleTest_134, DeepChaining_134) {
    doc->Parse("<a><b><c><d/></c></b></a>");
    XMLConstHandle handle(doc);
    XMLConstHandle d = handle.FirstChildElement("a")
                             .FirstChildElement("b")
                             .FirstChildElement("c")
                             .FirstChildElement("d");
    EXPECT_NE(d.ToElement(), nullptr);
    EXPECT_STREQ(d.ToElement()->Name(), "d");
}

// Test handle constructed from document node
TEST_F(XMLConstHandleTest_134, HandleFromDocument_134) {
    doc->Parse("<root/>");
    XMLConstHandle handle(static_cast<const XMLNode*>(doc));
    XMLConstHandle rootHandle = handle.FirstChildElement("root");
    EXPECT_NE(rootHandle.ToElement(), nullptr);
    EXPECT_STREQ(rootHandle.ToElement()->Name(), "root");
}

// Test NextSiblingElement with no matching name
TEST_F(XMLConstHandleTest_134, NextSiblingElementNoMatch_134) {
    doc->Parse("<root><alpha/><beta/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* alpha = root->FirstChildElement("alpha");
    ASSERT_NE(alpha, nullptr);

    XMLConstHandle handle(alpha);
    XMLConstHandle result = handle.NextSiblingElement("nonexistent");
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test PreviousSiblingElement with no matching name
TEST_F(XMLConstHandleTest_134, PreviousSiblingElementNoMatch_134) {
    doc->Parse("<root><alpha/><beta/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* beta = root->FirstChildElement("beta");
    ASSERT_NE(beta, nullptr);

    XMLConstHandle handle(beta);
    XMLConstHandle result = handle.PreviousSiblingElement("nonexistent");
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test LastChild on a node with a single child
TEST_F(XMLConstHandleTest_134, LastChildSingleChild_134) {
    doc->Parse("<root><only/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle first = handle.FirstChild();
    XMLConstHandle last = handle.LastChild();
    EXPECT_EQ(first.ToNode(), last.ToNode());
}

// Test LastChild on node with no children
TEST_F(XMLConstHandleTest_134, LastChildNoChildren_134) {
    doc->Parse("<root/>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle last = handle.LastChild();
    EXPECT_EQ(last.ToNode(), nullptr);
}

// Test that handle operations on empty document
TEST_F(XMLConstHandleTest_134, EmptyDocument_134) {
    XMLConstHandle handle(static_cast<const XMLNode*>(doc));
    XMLConstHandle child = handle.FirstChild();
    EXPECT_EQ(child.ToNode(), nullptr);
    XMLConstHandle elem = handle.FirstChildElement();
    EXPECT_EQ(elem.ToElement(), nullptr);
}

// Test multiple siblings navigation
TEST_F(XMLConstHandleTest_134, MultipleSiblingsNavigation_134) {
    doc->Parse("<root><a/><b/><c/><d/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle a = handle.FirstChildElement("a");
    EXPECT_NE(a.ToElement(), nullptr);

    XMLConstHandle b = a.NextSiblingElement();
    EXPECT_NE(b.ToElement(), nullptr);
    EXPECT_STREQ(b.ToElement()->Name(), "b");

    XMLConstHandle c = b.NextSiblingElement();
    EXPECT_NE(c.ToElement(), nullptr);
    EXPECT_STREQ(c.ToElement()->Name(), "c");

    XMLConstHandle d = c.NextSiblingElement();
    EXPECT_NE(d.ToElement(), nullptr);
    EXPECT_STREQ(d.ToElement()->Name(), "d");

    XMLConstHandle end = d.NextSiblingElement();
    EXPECT_EQ(end.ToElement(), nullptr);
}

// Test backward navigation through siblings
TEST_F(XMLConstHandleTest_134, BackwardSiblingsNavigation_134) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle c = handle.LastChildElement("c");
    EXPECT_NE(c.ToElement(), nullptr);

    XMLConstHandle b = c.PreviousSiblingElement();
    EXPECT_NE(b.ToElement(), nullptr);
    EXPECT_STREQ(b.ToElement()->Name(), "b");

    XMLConstHandle a = b.PreviousSiblingElement();
    EXPECT_NE(a.ToElement(), nullptr);
    EXPECT_STREQ(a.ToElement()->Name(), "a");

    XMLConstHandle none = a.PreviousSiblingElement();
    EXPECT_EQ(none.ToElement(), nullptr);
}
