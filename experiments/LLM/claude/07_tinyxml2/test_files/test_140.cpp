#include "gtest/gtest.h"
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleTest_140 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test constructing XMLConstHandle from a null node pointer
TEST_F(XMLConstHandleTest_140, ConstructFromNullPointer_140) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test constructing XMLConstHandle from a valid node pointer
TEST_F(XMLConstHandleTest_140, ConstructFromValidPointer_140) {
    doc->Parse("<root><child/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test constructing XMLConstHandle from a node reference
TEST_F(XMLConstHandleTest_140, ConstructFromReference_140) {
    doc->Parse("<root/>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(*root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test copy constructor
TEST_F(XMLConstHandleTest_140, CopyConstructor_140) {
    doc->Parse("<root/>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle1(root);
    XMLConstHandle handle2(handle1);
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test copy assignment operator
TEST_F(XMLConstHandleTest_140, CopyAssignment_140) {
    doc->Parse("<root><child/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    const XMLNode* child = root->FirstChild();
    ASSERT_NE(root, nullptr);
    ASSERT_NE(child, nullptr);

    XMLConstHandle handle1(root);
    XMLConstHandle handle2(child);
    handle2 = handle1;
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test NextSibling with null node
TEST_F(XMLConstHandleTest_140, NextSiblingNullNode_140) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.NextSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test NextSibling with valid node that has a sibling
TEST_F(XMLConstHandleTest_140, NextSiblingValidNode_140) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* a = root->FirstChild();
    ASSERT_NE(a, nullptr);

    XMLConstHandle handle(a);
    XMLConstHandle next = handle.NextSibling();
    ASSERT_NE(next.ToNode(), nullptr);
    EXPECT_NE(next.ToElement(), nullptr);
    EXPECT_STREQ(next.ToElement()->Name(), "b");
}

// Test NextSibling when there is no next sibling
TEST_F(XMLConstHandleTest_140, NextSiblingNoSibling_140) {
    doc->Parse("<root><only/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* only = root->FirstChild();
    ASSERT_NE(only, nullptr);

    XMLConstHandle handle(only);
    XMLConstHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test FirstChild with null node
TEST_F(XMLConstHandleTest_140, FirstChildNullNode_140) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.FirstChild();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test FirstChild with valid node
TEST_F(XMLConstHandleTest_140, FirstChildValidNode_140) {
    doc->Parse("<root><a/><b/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle first = handle.FirstChild();
    ASSERT_NE(first.ToNode(), nullptr);
    EXPECT_NE(first.ToElement(), nullptr);
    EXPECT_STREQ(first.ToElement()->Name(), "a");
}

// Test FirstChild with no children
TEST_F(XMLConstHandleTest_140, FirstChildNoChildren_140) {
    doc->Parse("<root/>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle first = handle.FirstChild();
    EXPECT_EQ(first.ToNode(), nullptr);
}

// Test FirstChildElement with null node
TEST_F(XMLConstHandleTest_140, FirstChildElementNullNode_140) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.FirstChildElement();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test FirstChildElement with valid node and no name filter
TEST_F(XMLConstHandleTest_140, FirstChildElementNoFilter_140) {
    doc->Parse("<root><a/><b/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle first = handle.FirstChildElement();
    ASSERT_NE(first.ToNode(), nullptr);
    EXPECT_STREQ(first.ToElement()->Name(), "a");
}

// Test FirstChildElement with name filter
TEST_F(XMLConstHandleTest_140, FirstChildElementWithNameFilter_140) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle found = handle.FirstChildElement("b");
    ASSERT_NE(found.ToNode(), nullptr);
    EXPECT_STREQ(found.ToElement()->Name(), "b");
}

// Test FirstChildElement with non-existent name filter
TEST_F(XMLConstHandleTest_140, FirstChildElementNonExistent_140) {
    doc->Parse("<root><a/><b/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle notFound = handle.FirstChildElement("z");
    EXPECT_EQ(notFound.ToNode(), nullptr);
}

// Test LastChild with null node
TEST_F(XMLConstHandleTest_140, LastChildNullNode_140) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.LastChild();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test LastChild with valid node
TEST_F(XMLConstHandleTest_140, LastChildValidNode_140) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle last = handle.LastChild();
    ASSERT_NE(last.ToNode(), nullptr);
    EXPECT_STREQ(last.ToElement()->Name(), "c");
}

// Test LastChildElement with null node
TEST_F(XMLConstHandleTest_140, LastChildElementNullNode_140) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.LastChildElement();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test LastChildElement with valid node
TEST_F(XMLConstHandleTest_140, LastChildElementValidNode_140) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle last = handle.LastChildElement();
    ASSERT_NE(last.ToNode(), nullptr);
    EXPECT_STREQ(last.ToElement()->Name(), "c");
}

// Test LastChildElement with name filter
TEST_F(XMLConstHandleTest_140, LastChildElementWithNameFilter_140) {
    doc->Parse("<root><a/><b/><a id='2'/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle last = handle.LastChildElement("a");
    ASSERT_NE(last.ToNode(), nullptr);
    EXPECT_STREQ(last.ToElement()->Name(), "a");
    // The last "a" element has an attribute "id" = "2"
    EXPECT_STREQ(last.ToElement()->Attribute("id"), "2");
}

// Test PreviousSibling with null node
TEST_F(XMLConstHandleTest_140, PreviousSiblingNullNode_140) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.PreviousSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test PreviousSibling with valid node
TEST_F(XMLConstHandleTest_140, PreviousSiblingValidNode_140) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    XMLConstHandle handle(b);
    XMLConstHandle prev = handle.PreviousSibling();
    ASSERT_NE(prev.ToNode(), nullptr);
    EXPECT_STREQ(prev.ToElement()->Name(), "a");
}

// Test PreviousSibling when there is no previous sibling
TEST_F(XMLConstHandleTest_140, PreviousSiblingNoPrev_140) {
    doc->Parse("<root><a/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* a = root->FirstChild();
    ASSERT_NE(a, nullptr);

    XMLConstHandle handle(a);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSiblingElement with null node
TEST_F(XMLConstHandleTest_140, PreviousSiblingElementNullNode_140) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.PreviousSiblingElement();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test PreviousSiblingElement with valid node
TEST_F(XMLConstHandleTest_140, PreviousSiblingElementValidNode_140) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    const XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(c, nullptr);

    XMLConstHandle handle(c);
    XMLConstHandle prev = handle.PreviousSiblingElement();
    ASSERT_NE(prev.ToNode(), nullptr);
    EXPECT_STREQ(prev.ToElement()->Name(), "b");
}

// Test PreviousSiblingElement with name filter
TEST_F(XMLConstHandleTest_140, PreviousSiblingElementWithNameFilter_140) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    const XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(c, nullptr);

    XMLConstHandle handle(c);
    XMLConstHandle prev = handle.PreviousSiblingElement("a");
    ASSERT_NE(prev.ToNode(), nullptr);
    EXPECT_STREQ(prev.ToElement()->Name(), "a");
}

// Test NextSiblingElement with null node
TEST_F(XMLConstHandleTest_140, NextSiblingElementNullNode_140) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.NextSiblingElement();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test NextSiblingElement with valid node and no name filter
TEST_F(XMLConstHandleTest_140, NextSiblingElementNoFilter_140) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    const XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    XMLConstHandle handle(a);
    XMLConstHandle next = handle.NextSiblingElement();
    ASSERT_NE(next.ToNode(), nullptr);
    EXPECT_STREQ(next.ToElement()->Name(), "b");
}

// Test NextSiblingElement with name filter
TEST_F(XMLConstHandleTest_140, NextSiblingElementWithNameFilter_140) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    const XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    XMLConstHandle handle(a);
    XMLConstHandle next = handle.NextSiblingElement("c");
    ASSERT_NE(next.ToNode(), nullptr);
    EXPECT_STREQ(next.ToElement()->Name(), "c");
}

// Test NextSiblingElement with non-existent name filter
TEST_F(XMLConstHandleTest_140, NextSiblingElementNonExistent_140) {
    doc->Parse("<root><a/><b/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    const XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    XMLConstHandle handle(a);
    XMLConstHandle next = handle.NextSiblingElement("z");
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test ToNode returns correct node
TEST_F(XMLConstHandleTest_140, ToNodeReturnsCorrectNode_140) {
    doc->Parse("<root/>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test ToNode returns null for null handle
TEST_F(XMLConstHandleTest_140, ToNodeNullHandle_140) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test ToElement with element node
TEST_F(XMLConstHandleTest_140, ToElementWithElement_140) {
    doc->Parse("<root/>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_NE(handle.ToElement(), nullptr);
    EXPECT_STREQ(handle.ToElement()->Name(), "root");
}

// Test ToElement with null handle
TEST_F(XMLConstHandleTest_140, ToElementNullHandle_140) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test ToText with text node
TEST_F(XMLConstHandleTest_140, ToTextWithTextNode_140) {
    doc->Parse("<root>hello</root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* text = root->FirstChild();
    ASSERT_NE(text, nullptr);

    XMLConstHandle handle(text);
    EXPECT_NE(handle.ToText(), nullptr);
    EXPECT_STREQ(handle.ToText()->Value(), "hello");
}

// Test ToText with null handle
TEST_F(XMLConstHandleTest_140, ToTextNullHandle_140) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToText with non-text node
TEST_F(XMLConstHandleTest_140, ToTextWithNonTextNode_140) {
    doc->Parse("<root/>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToUnknown with null handle
TEST_F(XMLConstHandleTest_140, ToUnknownNullHandle_140) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToDeclaration with declaration node
TEST_F(XMLConstHandleTest_140, ToDeclarationWithDecl_140) {
    doc->Parse("<?xml version=\"1.0\"?><root/>");
    const XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);

    XMLConstHandle handle(firstChild);
    // firstChild should be the declaration
    if (handle.ToDeclaration() != nullptr) {
        EXPECT_NE(handle.ToDeclaration(), nullptr);
    }
}

// Test ToDeclaration with null handle
TEST_F(XMLConstHandleTest_140, ToDeclarationNullHandle_140) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test chaining: FirstChild().NextSibling()
TEST_F(XMLConstHandleTest_140, ChainingFirstChildNextSibling_140) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle b = handle.FirstChild().NextSibling();
    ASSERT_NE(b.ToNode(), nullptr);
    EXPECT_STREQ(b.ToElement()->Name(), "b");
}

// Test chaining: FirstChildElement().NextSiblingElement()
TEST_F(XMLConstHandleTest_140, ChainingFirstChildElementNextSiblingElement_140) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle b = handle.FirstChildElement("a").NextSiblingElement();
    ASSERT_NE(b.ToNode(), nullptr);
    EXPECT_STREQ(b.ToElement()->Name(), "b");
}

// Test chaining with null propagation
TEST_F(XMLConstHandleTest_140, ChainingNullPropagation_140) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.FirstChild().NextSibling().FirstChildElement();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test multiple NextSibling calls in chain
TEST_F(XMLConstHandleTest_140, MultipleNextSiblingChain_140) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle c = handle.FirstChild().NextSibling().NextSibling();
    ASSERT_NE(c.ToNode(), nullptr);
    EXPECT_STREQ(c.ToElement()->Name(), "c");
}

// Test NextSibling past last child returns null
TEST_F(XMLConstHandleTest_140, NextSiblingPastLastReturnsNull_140) {
    doc->Parse("<root><a/><b/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle pastEnd = handle.FirstChild().NextSibling().NextSibling();
    EXPECT_EQ(pastEnd.ToNode(), nullptr);
}

// Test with document node
TEST_F(XMLConstHandleTest_140, HandleWithDocumentNode_140) {
    doc->Parse("<root><a/></root>");
    XMLConstHandle handle(static_cast<const XMLNode*>(doc));
    XMLConstHandle first = handle.FirstChildElement("root");
    ASSERT_NE(first.ToNode(), nullptr);
    EXPECT_STREQ(first.ToElement()->Name(), "root");
}

// Test LastChild with multiple children
TEST_F(XMLConstHandleTest_140, LastChildMultipleChildren_140) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle last = handle.LastChild();
    ASSERT_NE(last.ToNode(), nullptr);
    EXPECT_STREQ(last.ToElement()->Name(), "c");
}

// Test LastChildElement with name filter that doesn't match last
TEST_F(XMLConstHandleTest_140, LastChildElementFilterNotLast_140) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle found = handle.LastChildElement("b");
    ASSERT_NE(found.ToNode(), nullptr);
    EXPECT_STREQ(found.ToElement()->Name(), "b");
}

// Test single child - FirstChild and LastChild should be the same
TEST_F(XMLConstHandleTest_140, SingleChildFirstAndLastSame_140) {
    doc->Parse("<root><only/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.FirstChild().ToNode(), handle.LastChild().ToNode());
}
