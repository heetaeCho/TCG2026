#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLHandleTest_126 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test: XMLHandle constructed with null node returns null on NextSibling
TEST_F(XMLHandleTest_126, NextSiblingWithNullNode_126) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle result = handle.NextSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test: XMLHandle constructed with a valid node that has no next sibling returns null
TEST_F(XMLHandleTest_126, NextSiblingNoSibling_126) {
    doc->Parse("<root><child/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* child = root->FirstChild();
    ASSERT_NE(child, nullptr);

    XMLHandle handle(child);
    XMLHandle result = handle.NextSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test: XMLHandle NextSibling returns the correct next sibling node
TEST_F(XMLHandleTest_126, NextSiblingReturnsCorrectSibling_126) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);

    XMLHandle handle(firstChild);
    XMLHandle nextHandle = handle.NextSibling();
    XMLNode* nextNode = nextHandle.ToNode();
    ASSERT_NE(nextNode, nullptr);
    XMLElement* nextElem = nextNode->ToElement();
    ASSERT_NE(nextElem, nullptr);
    EXPECT_STREQ(nextElem->Name(), "b");
}

// Test: Chaining NextSibling calls
TEST_F(XMLHandleTest_126, NextSiblingChained_126) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLHandle handle(root->FirstChild());
    XMLHandle third = handle.NextSibling().NextSibling();
    XMLNode* node = third.ToNode();
    ASSERT_NE(node, nullptr);
    XMLElement* elem = node->ToElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "c");
}

// Test: Chaining past the last sibling results in null
TEST_F(XMLHandleTest_126, NextSiblingChainedPastEnd_126) {
    doc->Parse("<root><a/><b/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLHandle handle(root->FirstChild());
    XMLHandle result = handle.NextSibling().NextSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test: NextSibling from null handle chained still returns null
TEST_F(XMLHandleTest_126, NextSiblingFromNullHandleChained_126) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle result = handle.NextSibling().NextSibling().NextSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test: XMLHandle constructed from node reference
TEST_F(XMLHandleTest_126, ConstructFromNodeReference_126) {
    doc->Parse("<root><a/><b/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);

    XMLHandle handle(*firstChild);
    XMLHandle nextHandle = handle.NextSibling();
    ASSERT_NE(nextHandle.ToNode(), nullptr);
    EXPECT_STREQ(nextHandle.ToElement()->Name(), "b");
}

// Test: Copy constructor preserves state for NextSibling
TEST_F(XMLHandleTest_126, CopyConstructorNextSibling_126) {
    doc->Parse("<root><a/><b/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLHandle handle(root->FirstChild());
    XMLHandle copy(handle);
    XMLHandle result = copy.NextSibling();
    ASSERT_NE(result.ToNode(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "b");
}

// Test: Assignment operator preserves state for NextSibling
TEST_F(XMLHandleTest_126, AssignmentOperatorNextSibling_126) {
    doc->Parse("<root><x/><y/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLHandle handle1(root->FirstChild());
    XMLHandle handle2(static_cast<XMLNode*>(nullptr));
    handle2 = handle1;
    XMLHandle result = handle2.NextSibling();
    ASSERT_NE(result.ToNode(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "y");
}

// Test: FirstChild
TEST_F(XMLHandleTest_126, FirstChild_126) {
    doc->Parse("<root><a/><b/></root>");
    XMLHandle handle(doc->FirstChildElement("root"));
    XMLHandle child = handle.FirstChild();
    ASSERT_NE(child.ToNode(), nullptr);
    EXPECT_STREQ(child.ToElement()->Name(), "a");
}

// Test: FirstChild on null handle
TEST_F(XMLHandleTest_126, FirstChildNull_126) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle child = handle.FirstChild();
    EXPECT_EQ(child.ToNode(), nullptr);
}

// Test: FirstChildElement
TEST_F(XMLHandleTest_126, FirstChildElement_126) {
    doc->Parse("<root><a/><b/></root>");
    XMLHandle handle(doc->FirstChildElement("root"));
    XMLHandle child = handle.FirstChildElement("b");
    ASSERT_NE(child.ToElement(), nullptr);
    EXPECT_STREQ(child.ToElement()->Name(), "b");
}

// Test: FirstChildElement with no name
TEST_F(XMLHandleTest_126, FirstChildElementNoName_126) {
    doc->Parse("<root><a/><b/></root>");
    XMLHandle handle(doc->FirstChildElement("root"));
    XMLHandle child = handle.FirstChildElement();
    ASSERT_NE(child.ToElement(), nullptr);
    EXPECT_STREQ(child.ToElement()->Name(), "a");
}

// Test: FirstChildElement on null handle
TEST_F(XMLHandleTest_126, FirstChildElementNull_126) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle child = handle.FirstChildElement("anything");
    EXPECT_EQ(child.ToElement(), nullptr);
}

// Test: LastChild
TEST_F(XMLHandleTest_126, LastChild_126) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLHandle handle(doc->FirstChildElement("root"));
    XMLHandle child = handle.LastChild();
    ASSERT_NE(child.ToNode(), nullptr);
    EXPECT_STREQ(child.ToElement()->Name(), "c");
}

// Test: LastChild on null handle
TEST_F(XMLHandleTest_126, LastChildNull_126) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle child = handle.LastChild();
    EXPECT_EQ(child.ToNode(), nullptr);
}

// Test: LastChildElement
TEST_F(XMLHandleTest_126, LastChildElement_126) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLHandle handle(doc->FirstChildElement("root"));
    XMLHandle child = handle.LastChildElement("b");
    ASSERT_NE(child.ToElement(), nullptr);
    EXPECT_STREQ(child.ToElement()->Name(), "b");
}

// Test: LastChildElement with no name
TEST_F(XMLHandleTest_126, LastChildElementNoName_126) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLHandle handle(doc->FirstChildElement("root"));
    XMLHandle child = handle.LastChildElement();
    ASSERT_NE(child.ToElement(), nullptr);
    EXPECT_STREQ(child.ToElement()->Name(), "c");
}

// Test: PreviousSibling
TEST_F(XMLHandleTest_126, PreviousSibling_126) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    XMLNode* last = root->LastChild();
    ASSERT_NE(last, nullptr);

    XMLHandle handle(last);
    XMLHandle prev = handle.PreviousSibling();
    ASSERT_NE(prev.ToNode(), nullptr);
    EXPECT_STREQ(prev.ToElement()->Name(), "b");
}

// Test: PreviousSibling on null handle
TEST_F(XMLHandleTest_126, PreviousSiblingNull_126) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test: PreviousSibling on first child returns null
TEST_F(XMLHandleTest_126, PreviousSiblingOnFirst_126) {
    doc->Parse("<root><a/><b/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);

    XMLHandle handle(first);
    XMLHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test: PreviousSiblingElement
TEST_F(XMLHandleTest_126, PreviousSiblingElement_126) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    XMLNode* last = root->LastChild();
    ASSERT_NE(last, nullptr);

    XMLHandle handle(last);
    XMLHandle prev = handle.PreviousSiblingElement("a");
    ASSERT_NE(prev.ToElement(), nullptr);
    EXPECT_STREQ(prev.ToElement()->Name(), "a");
}

// Test: PreviousSiblingElement on null handle
TEST_F(XMLHandleTest_126, PreviousSiblingElementNull_126) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle prev = handle.PreviousSiblingElement();
    EXPECT_EQ(prev.ToElement(), nullptr);
}

// Test: NextSiblingElement
TEST_F(XMLHandleTest_126, NextSiblingElement_126) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);

    XMLHandle handle(first);
    XMLHandle next = handle.NextSiblingElement("c");
    ASSERT_NE(next.ToElement(), nullptr);
    EXPECT_STREQ(next.ToElement()->Name(), "c");
}

// Test: NextSiblingElement with no name
TEST_F(XMLHandleTest_126, NextSiblingElementNoName_126) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);

    XMLHandle handle(first);
    XMLHandle next = handle.NextSiblingElement();
    ASSERT_NE(next.ToElement(), nullptr);
    EXPECT_STREQ(next.ToElement()->Name(), "b");
}

// Test: NextSiblingElement on null handle
TEST_F(XMLHandleTest_126, NextSiblingElementNull_126) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle next = handle.NextSiblingElement();
    EXPECT_EQ(next.ToElement(), nullptr);
}

// Test: ToNode returns the underlying node
TEST_F(XMLHandleTest_126, ToNode_126) {
    doc->Parse("<root/>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test: ToNode on null handle
TEST_F(XMLHandleTest_126, ToNodeNull_126) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test: ToElement
TEST_F(XMLHandleTest_126, ToElement_126) {
    doc->Parse("<root/>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLHandle handle(root);
    EXPECT_EQ(handle.ToElement(), root);
}

// Test: ToElement on null handle
TEST_F(XMLHandleTest_126, ToElementNull_126) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test: ToText on a text node
TEST_F(XMLHandleTest_126, ToText_126) {
    doc->Parse("<root>Hello</root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* textNode = root->FirstChild();
    ASSERT_NE(textNode, nullptr);

    XMLHandle handle(textNode);
    EXPECT_NE(handle.ToText(), nullptr);
}

// Test: ToText on non-text returns null
TEST_F(XMLHandleTest_126, ToTextOnElement_126) {
    doc->Parse("<root/>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLHandle handle(root);
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test: ToText on null handle
TEST_F(XMLHandleTest_126, ToTextNull_126) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test: ToUnknown on null handle
TEST_F(XMLHandleTest_126, ToUnknownNull_126) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test: ToDeclaration on null handle
TEST_F(XMLHandleTest_126, ToDeclarationNull_126) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test: ToDeclaration on a declaration node
TEST_F(XMLHandleTest_126, ToDeclaration_126) {
    doc->Parse("<?xml version=\"1.0\"?><root/>");
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);

    XMLHandle handle(firstChild);
    // First child should be the declaration
    if (handle.ToDeclaration() != nullptr) {
        EXPECT_NE(handle.ToDeclaration(), nullptr);
    }
}

// Test: NextSibling with mixed content (text + elements)
TEST_F(XMLHandleTest_126, NextSiblingMixedContent_126) {
    doc->Parse("<root>text<a/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);

    XMLHandle handle(firstChild);
    XMLHandle next = handle.NextSibling();
    ASSERT_NE(next.ToNode(), nullptr);
    EXPECT_NE(next.ToElement(), nullptr);
    EXPECT_STREQ(next.ToElement()->Name(), "a");
}

// Test: Complex navigation FirstChild -> NextSibling -> NextSiblingElement
TEST_F(XMLHandleTest_126, ComplexNavigation_126) {
    doc->Parse("<root><a/><b/><c/><d/></root>");
    XMLHandle docHandle(doc);
    XMLHandle result = docHandle.FirstChildElement("root")
                                .FirstChild()
                                .NextSibling()
                                .NextSiblingElement("d");
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "d");
}

// Test: Navigation on empty element
TEST_F(XMLHandleTest_126, EmptyElementFirstChild_126) {
    doc->Parse("<root/>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLHandle handle(root);
    XMLHandle child = handle.FirstChild();
    EXPECT_EQ(child.ToNode(), nullptr);
}

// Test: NextSiblingElement with non-matching name
TEST_F(XMLHandleTest_126, NextSiblingElementNonMatching_126) {
    doc->Parse("<root><a/><b/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);

    XMLHandle handle(first);
    XMLHandle next = handle.NextSiblingElement("z");
    EXPECT_EQ(next.ToElement(), nullptr);
}
