#include "gtest/gtest.h"
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLHandleTest_128 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test ToNode returns the node pointer when constructed with a valid node
TEST_F(XMLHandleTest_128, ToNodeReturnsValidNode_128) {
    doc->InsertFirstChild(doc->NewElement("root"));
    XMLNode* root = doc->FirstChild();
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test ToNode returns nullptr when constructed with nullptr
TEST_F(XMLHandleTest_128, ToNodeReturnsNullForNullHandle_128) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test construction with XMLNode reference
TEST_F(XMLHandleTest_128, ConstructFromReference_128) {
    doc->InsertFirstChild(doc->NewElement("root"));
    XMLNode* root = doc->FirstChild();
    XMLHandle handle(*root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test copy constructor
TEST_F(XMLHandleTest_128, CopyConstructor_128) {
    doc->InsertFirstChild(doc->NewElement("root"));
    XMLNode* root = doc->FirstChild();
    XMLHandle handle1(root);
    XMLHandle handle2(handle1);
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test assignment operator
TEST_F(XMLHandleTest_128, AssignmentOperator_128) {
    doc->InsertFirstChild(doc->NewElement("root"));
    XMLNode* root = doc->FirstChild();
    XMLHandle handle1(root);
    XMLHandle handle2(static_cast<XMLNode*>(nullptr));
    handle2 = handle1;
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test ToElement returns valid element
TEST_F(XMLHandleTest_128, ToElementReturnsValidElement_128) {
    XMLElement* elem = doc->NewElement("root");
    doc->InsertFirstChild(elem);
    XMLHandle handle(elem);
    EXPECT_EQ(handle.ToElement(), elem);
}

// Test ToElement returns nullptr for null handle
TEST_F(XMLHandleTest_128, ToElementReturnsNullForNullHandle_128) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test ToText returns valid text node
TEST_F(XMLHandleTest_128, ToTextReturnsValidText_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLText* text = doc->NewText("hello");
    root->InsertFirstChild(text);
    XMLHandle handle(text);
    EXPECT_EQ(handle.ToText(), text);
}

// Test ToText returns nullptr for non-text node
TEST_F(XMLHandleTest_128, ToTextReturnsNullForElement_128) {
    XMLElement* elem = doc->NewElement("root");
    doc->InsertFirstChild(elem);
    XMLHandle handle(elem);
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToUnknown returns nullptr for element node
TEST_F(XMLHandleTest_128, ToUnknownReturnsNullForElement_128) {
    XMLElement* elem = doc->NewElement("root");
    doc->InsertFirstChild(elem);
    XMLHandle handle(elem);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToDeclaration returns nullptr for element node
TEST_F(XMLHandleTest_128, ToDeclarationReturnsNullForElement_128) {
    XMLElement* elem = doc->NewElement("root");
    doc->InsertFirstChild(elem);
    XMLHandle handle(elem);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test ToDeclaration returns valid declaration
TEST_F(XMLHandleTest_128, ToDeclarationReturnsValidDeclaration_128) {
    XMLDeclaration* decl = doc->NewDeclaration("xml version=\"1.0\"");
    doc->InsertFirstChild(decl);
    XMLHandle handle(decl);
    EXPECT_EQ(handle.ToDeclaration(), decl);
}

// Test FirstChild returns valid handle for existing child
TEST_F(XMLHandleTest_128, FirstChildReturnsValidChild_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLElement* child = doc->NewElement("child");
    root->InsertFirstChild(child);
    XMLHandle handle(root);
    XMLHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), child);
}

// Test FirstChild returns null handle when no children
TEST_F(XMLHandleTest_128, FirstChildReturnsNullWhenNoChildren_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLHandle handle(root);
    XMLHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChild on null handle returns null handle
TEST_F(XMLHandleTest_128, FirstChildOnNullHandleReturnsNull_128) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChildElement returns correct element
TEST_F(XMLHandleTest_128, FirstChildElementReturnsCorrectElement_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLElement* child1 = doc->NewElement("alpha");
    XMLElement* child2 = doc->NewElement("beta");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    XMLHandle handle(root);
    XMLHandle firstElem = handle.FirstChildElement();
    EXPECT_EQ(firstElem.ToElement(), child1);
}

// Test FirstChildElement with name filter
TEST_F(XMLHandleTest_128, FirstChildElementByName_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLElement* child1 = doc->NewElement("alpha");
    XMLElement* child2 = doc->NewElement("beta");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    XMLHandle handle(root);
    XMLHandle betaElem = handle.FirstChildElement("beta");
    EXPECT_EQ(betaElem.ToElement(), child2);
}

// Test FirstChildElement with name filter that doesn't match
TEST_F(XMLHandleTest_128, FirstChildElementByNameNotFound_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLElement* child1 = doc->NewElement("alpha");
    root->InsertEndChild(child1);
    XMLHandle handle(root);
    XMLHandle result = handle.FirstChildElement("gamma");
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test LastChild returns last child
TEST_F(XMLHandleTest_128, LastChildReturnsLastChild_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLElement* child1 = doc->NewElement("first");
    XMLElement* child2 = doc->NewElement("last");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    XMLHandle handle(root);
    XMLHandle lastChild = handle.LastChild();
    EXPECT_EQ(lastChild.ToNode(), child2);
}

// Test LastChild on null handle
TEST_F(XMLHandleTest_128, LastChildOnNullHandle_128) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle lastChild = handle.LastChild();
    EXPECT_EQ(lastChild.ToNode(), nullptr);
}

// Test LastChildElement returns last element
TEST_F(XMLHandleTest_128, LastChildElementReturnsLastElement_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLElement* child1 = doc->NewElement("first");
    XMLElement* child2 = doc->NewElement("last");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    XMLHandle handle(root);
    XMLHandle lastElem = handle.LastChildElement();
    EXPECT_EQ(lastElem.ToElement(), child2);
}

// Test LastChildElement with name filter
TEST_F(XMLHandleTest_128, LastChildElementByName_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLElement* child1 = doc->NewElement("alpha");
    XMLElement* child2 = doc->NewElement("beta");
    XMLElement* child3 = doc->NewElement("alpha");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->InsertEndChild(child3);
    XMLHandle handle(root);
    XMLHandle lastAlpha = handle.LastChildElement("alpha");
    EXPECT_EQ(lastAlpha.ToElement(), child3);
}

// Test NextSibling
TEST_F(XMLHandleTest_128, NextSiblingReturnsCorrectSibling_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLElement* child1 = doc->NewElement("first");
    XMLElement* child2 = doc->NewElement("second");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    XMLHandle handle(child1);
    XMLHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), child2);
}

// Test NextSibling returns null when no next sibling
TEST_F(XMLHandleTest_128, NextSiblingReturnsNullAtEnd_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLElement* child1 = doc->NewElement("only");
    root->InsertEndChild(child1);
    XMLHandle handle(child1);
    XMLHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test NextSibling on null handle
TEST_F(XMLHandleTest_128, NextSiblingOnNullHandle_128) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test NextSiblingElement
TEST_F(XMLHandleTest_128, NextSiblingElementReturnsCorrectElement_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLElement* child1 = doc->NewElement("first");
    XMLElement* child2 = doc->NewElement("second");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    XMLHandle handle(child1);
    XMLHandle nextElem = handle.NextSiblingElement();
    EXPECT_EQ(nextElem.ToElement(), child2);
}

// Test NextSiblingElement with name filter
TEST_F(XMLHandleTest_128, NextSiblingElementByName_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLElement* child1 = doc->NewElement("alpha");
    XMLElement* child2 = doc->NewElement("beta");
    XMLElement* child3 = doc->NewElement("gamma");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->InsertEndChild(child3);
    XMLHandle handle(child1);
    XMLHandle nextGamma = handle.NextSiblingElement("gamma");
    EXPECT_EQ(nextGamma.ToElement(), child3);
}

// Test PreviousSibling
TEST_F(XMLHandleTest_128, PreviousSiblingReturnsCorrectSibling_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLElement* child1 = doc->NewElement("first");
    XMLElement* child2 = doc->NewElement("second");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    XMLHandle handle(child2);
    XMLHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), child1);
}

// Test PreviousSibling returns null for first child
TEST_F(XMLHandleTest_128, PreviousSiblingReturnsNullAtBegin_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLElement* child1 = doc->NewElement("only");
    root->InsertEndChild(child1);
    XMLHandle handle(child1);
    XMLHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSibling on null handle
TEST_F(XMLHandleTest_128, PreviousSiblingOnNullHandle_128) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSiblingElement
TEST_F(XMLHandleTest_128, PreviousSiblingElementReturnsCorrectElement_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLElement* child1 = doc->NewElement("first");
    XMLElement* child2 = doc->NewElement("second");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    XMLHandle handle(child2);
    XMLHandle prevElem = handle.PreviousSiblingElement();
    EXPECT_EQ(prevElem.ToElement(), child1);
}

// Test PreviousSiblingElement with name filter
TEST_F(XMLHandleTest_128, PreviousSiblingElementByName_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLElement* child1 = doc->NewElement("alpha");
    XMLElement* child2 = doc->NewElement("beta");
    XMLElement* child3 = doc->NewElement("gamma");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->InsertEndChild(child3);
    XMLHandle handle(child3);
    XMLHandle prevAlpha = handle.PreviousSiblingElement("alpha");
    EXPECT_EQ(prevAlpha.ToElement(), child1);
}

// Test chaining handles: FirstChildElement -> FirstChildElement
TEST_F(XMLHandleTest_128, ChainingHandleNavigation_128) {
    doc->Parse("<root><parent><child/></parent></root>");
    XMLHandle docHandle(doc);
    XMLElement* child = docHandle.FirstChildElement("root")
                                 .FirstChildElement("parent")
                                 .FirstChildElement("child")
                                 .ToElement();
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
}

// Test chaining with broken chain returns null
TEST_F(XMLHandleTest_128, ChainingHandleNavigationBrokenChain_128) {
    doc->Parse("<root><parent><child/></parent></root>");
    XMLHandle docHandle(doc);
    XMLElement* result = docHandle.FirstChildElement("root")
                                  .FirstChildElement("nonexistent")
                                  .FirstChildElement("child")
                                  .ToElement();
    EXPECT_EQ(result, nullptr);
}

// Test ToElement returns nullptr for text node
TEST_F(XMLHandleTest_128, ToElementReturnsNullForTextNode_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLText* text = doc->NewText("hello");
    root->InsertEndChild(text);
    XMLHandle handle(text);
    EXPECT_EQ(handle.ToElement(), nullptr);
    EXPECT_NE(handle.ToText(), nullptr);
}

// Test ToUnknown with unknown node
TEST_F(XMLHandleTest_128, ToUnknownReturnsValidUnknown_128) {
    doc->Parse("<root><!unknown stuff></root>");
    // Navigate to unknown node if it exists
    XMLHandle docHandle(doc);
    XMLNode* rootNode = docHandle.FirstChildElement("root").ToNode();
    ASSERT_NE(rootNode, nullptr);
    XMLNode* child = rootNode->FirstChild();
    if (child && child->ToUnknown()) {
        XMLHandle unknownHandle(child);
        EXPECT_NE(unknownHandle.ToUnknown(), nullptr);
    }
}

// Test handle with XMLDocument node
TEST_F(XMLHandleTest_128, HandleWithDocumentNode_128) {
    doc->Parse("<root/>");
    XMLHandle handle(doc);
    EXPECT_EQ(handle.ToNode(), doc);
    XMLHandle firstChild = handle.FirstChildElement("root");
    EXPECT_NE(firstChild.ToElement(), nullptr);
    EXPECT_STREQ(firstChild.ToElement()->Name(), "root");
}

// Test multiple children navigation
TEST_F(XMLHandleTest_128, MultipleChildrenNavigation_128) {
    doc->Parse("<root><a/><b/><c/><d/></root>");
    XMLHandle docHandle(doc);
    XMLHandle root = docHandle.FirstChildElement("root");

    XMLHandle a = root.FirstChildElement("a");
    EXPECT_NE(a.ToElement(), nullptr);

    XMLHandle b = a.NextSiblingElement("b");
    EXPECT_NE(b.ToElement(), nullptr);

    XMLHandle c = b.NextSiblingElement("c");
    EXPECT_NE(c.ToElement(), nullptr);

    XMLHandle d = c.NextSiblingElement("d");
    EXPECT_NE(d.ToElement(), nullptr);

    XMLHandle none = d.NextSiblingElement();
    EXPECT_EQ(none.ToElement(), nullptr);
}

// Test self-assignment
TEST_F(XMLHandleTest_128, SelfAssignment_128) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLHandle handle(root);
    handle = handle;
    EXPECT_EQ(handle.ToNode(), root);
}
