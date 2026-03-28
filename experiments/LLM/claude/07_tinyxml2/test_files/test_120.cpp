#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLHandleTest_120 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test XMLHandle constructed with null node
TEST_F(XMLHandleTest_120, ConstructWithNullNode_120) {
    XMLHandle handle((XMLNode*)nullptr);
    EXPECT_EQ(handle.ToNode(), nullptr);
    EXPECT_EQ(handle.ToElement(), nullptr);
    EXPECT_EQ(handle.ToText(), nullptr);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test XMLHandle constructed with a valid node
TEST_F(XMLHandleTest_120, ConstructWithValidNode_120) {
    doc->Parse("<root><child/></root>");
    XMLHandle handle(doc->RootElement());
    EXPECT_NE(handle.ToNode(), nullptr);
    EXPECT_NE(handle.ToElement(), nullptr);
}

// Test XMLHandle constructed with node reference
TEST_F(XMLHandleTest_120, ConstructWithNodeReference_120) {
    doc->Parse("<root/>");
    XMLNode* root = doc->RootElement();
    XMLHandle handle(*root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test copy constructor
TEST_F(XMLHandleTest_120, CopyConstructor_120) {
    doc->Parse("<root/>");
    XMLHandle handle1(doc->RootElement());
    XMLHandle handle2(handle1);
    EXPECT_EQ(handle1.ToNode(), handle2.ToNode());
}

// Test assignment operator
TEST_F(XMLHandleTest_120, AssignmentOperator_120) {
    doc->Parse("<root><child/></root>");
    XMLHandle handle1(doc->RootElement());
    XMLHandle handle2((XMLNode*)nullptr);
    handle2 = handle1;
    EXPECT_EQ(handle1.ToNode(), handle2.ToNode());
}

// Test FirstChild on a node with children
TEST_F(XMLHandleTest_120, FirstChildWithChildren_120) {
    doc->Parse("<root><child1/><child2/></root>");
    XMLHandle handle(doc->RootElement());
    XMLHandle firstChild = handle.FirstChild();
    EXPECT_NE(firstChild.ToNode(), nullptr);
    EXPECT_NE(firstChild.ToElement(), nullptr);
    EXPECT_STREQ(firstChild.ToElement()->Name(), "child1");
}

// Test FirstChild on a node with no children
TEST_F(XMLHandleTest_120, FirstChildNoChildren_120) {
    doc->Parse("<root/>");
    XMLHandle handle(doc->RootElement());
    XMLHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChild on null handle
TEST_F(XMLHandleTest_120, FirstChildOnNullHandle_120) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChildElement on a node with element children
TEST_F(XMLHandleTest_120, FirstChildElement_120) {
    doc->Parse("<root><alpha/><beta/></root>");
    XMLHandle handle(doc->RootElement());
    XMLHandle elem = handle.FirstChildElement();
    EXPECT_NE(elem.ToElement(), nullptr);
    EXPECT_STREQ(elem.ToElement()->Name(), "alpha");
}

// Test FirstChildElement with name filter
TEST_F(XMLHandleTest_120, FirstChildElementWithName_120) {
    doc->Parse("<root><alpha/><beta/><gamma/></root>");
    XMLHandle handle(doc->RootElement());
    XMLHandle elem = handle.FirstChildElement("beta");
    EXPECT_NE(elem.ToElement(), nullptr);
    EXPECT_STREQ(elem.ToElement()->Name(), "beta");
}

// Test FirstChildElement with name that doesn't exist
TEST_F(XMLHandleTest_120, FirstChildElementNameNotFound_120) {
    doc->Parse("<root><alpha/><beta/></root>");
    XMLHandle handle(doc->RootElement());
    XMLHandle elem = handle.FirstChildElement("nonexistent");
    EXPECT_EQ(elem.ToElement(), nullptr);
    EXPECT_EQ(elem.ToNode(), nullptr);
}

// Test FirstChildElement on null handle
TEST_F(XMLHandleTest_120, FirstChildElementOnNullHandle_120) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle elem = handle.FirstChildElement();
    EXPECT_EQ(elem.ToElement(), nullptr);
}

// Test LastChild on a node with children
TEST_F(XMLHandleTest_120, LastChildWithChildren_120) {
    doc->Parse("<root><child1/><child2/><child3/></root>");
    XMLHandle handle(doc->RootElement());
    XMLHandle lastChild = handle.LastChild();
    EXPECT_NE(lastChild.ToNode(), nullptr);
    EXPECT_NE(lastChild.ToElement(), nullptr);
    EXPECT_STREQ(lastChild.ToElement()->Name(), "child3");
}

// Test LastChild on a node with no children
TEST_F(XMLHandleTest_120, LastChildNoChildren_120) {
    doc->Parse("<root/>");
    XMLHandle handle(doc->RootElement());
    XMLHandle lastChild = handle.LastChild();
    EXPECT_EQ(lastChild.ToNode(), nullptr);
}

// Test LastChild on null handle
TEST_F(XMLHandleTest_120, LastChildOnNullHandle_120) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle lastChild = handle.LastChild();
    EXPECT_EQ(lastChild.ToNode(), nullptr);
}

// Test LastChildElement
TEST_F(XMLHandleTest_120, LastChildElement_120) {
    doc->Parse("<root><alpha/><beta/><gamma/></root>");
    XMLHandle handle(doc->RootElement());
    XMLHandle elem = handle.LastChildElement();
    EXPECT_NE(elem.ToElement(), nullptr);
    EXPECT_STREQ(elem.ToElement()->Name(), "gamma");
}

// Test LastChildElement with name filter
TEST_F(XMLHandleTest_120, LastChildElementWithName_120) {
    doc->Parse("<root><alpha/><beta/><alpha id='2'/></root>");
    XMLHandle handle(doc->RootElement());
    XMLHandle elem = handle.LastChildElement("alpha");
    EXPECT_NE(elem.ToElement(), nullptr);
    EXPECT_STREQ(elem.ToElement()->Name(), "alpha");
    EXPECT_STREQ(elem.ToElement()->Attribute("id"), "2");
}

// Test LastChildElement on null handle
TEST_F(XMLHandleTest_120, LastChildElementOnNullHandle_120) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle elem = handle.LastChildElement();
    EXPECT_EQ(elem.ToElement(), nullptr);
}

// Test PreviousSibling
TEST_F(XMLHandleTest_120, PreviousSibling_120) {
    doc->Parse("<root><child1/><child2/><child3/></root>");
    XMLHandle handle(doc->RootElement()->LastChildElement());
    XMLHandle prev = handle.PreviousSibling();
    EXPECT_NE(prev.ToNode(), nullptr);
    EXPECT_STREQ(prev.ToElement()->Name(), "child2");
}

// Test PreviousSibling on first child (no previous)
TEST_F(XMLHandleTest_120, PreviousSiblingOnFirstChild_120) {
    doc->Parse("<root><child1/><child2/></root>");
    XMLHandle handle(doc->RootElement()->FirstChildElement());
    XMLHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSibling on null handle
TEST_F(XMLHandleTest_120, PreviousSiblingOnNullHandle_120) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSiblingElement
TEST_F(XMLHandleTest_120, PreviousSiblingElement_120) {
    doc->Parse("<root><alpha/><beta/><gamma/></root>");
    XMLHandle handle(doc->RootElement()->LastChildElement());
    XMLHandle prev = handle.PreviousSiblingElement();
    EXPECT_NE(prev.ToElement(), nullptr);
    EXPECT_STREQ(prev.ToElement()->Name(), "beta");
}

// Test PreviousSiblingElement with name filter
TEST_F(XMLHandleTest_120, PreviousSiblingElementWithName_120) {
    doc->Parse("<root><alpha/><beta/><gamma/></root>");
    XMLHandle handle(doc->RootElement()->LastChildElement());
    XMLHandle prev = handle.PreviousSiblingElement("alpha");
    EXPECT_NE(prev.ToElement(), nullptr);
    EXPECT_STREQ(prev.ToElement()->Name(), "alpha");
}

// Test PreviousSiblingElement on null handle
TEST_F(XMLHandleTest_120, PreviousSiblingElementOnNullHandle_120) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle prev = handle.PreviousSiblingElement();
    EXPECT_EQ(prev.ToElement(), nullptr);
}

// Test NextSibling
TEST_F(XMLHandleTest_120, NextSibling_120) {
    doc->Parse("<root><child1/><child2/><child3/></root>");
    XMLHandle handle(doc->RootElement()->FirstChildElement());
    XMLHandle next = handle.NextSibling();
    EXPECT_NE(next.ToNode(), nullptr);
    EXPECT_STREQ(next.ToElement()->Name(), "child2");
}

// Test NextSibling on last child (no next)
TEST_F(XMLHandleTest_120, NextSiblingOnLastChild_120) {
    doc->Parse("<root><child1/><child2/></root>");
    XMLHandle handle(doc->RootElement()->LastChildElement());
    XMLHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test NextSibling on null handle
TEST_F(XMLHandleTest_120, NextSiblingOnNullHandle_120) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test NextSiblingElement
TEST_F(XMLHandleTest_120, NextSiblingElement_120) {
    doc->Parse("<root><alpha/><beta/><gamma/></root>");
    XMLHandle handle(doc->RootElement()->FirstChildElement());
    XMLHandle next = handle.NextSiblingElement();
    EXPECT_NE(next.ToElement(), nullptr);
    EXPECT_STREQ(next.ToElement()->Name(), "beta");
}

// Test NextSiblingElement with name filter
TEST_F(XMLHandleTest_120, NextSiblingElementWithName_120) {
    doc->Parse("<root><alpha/><beta/><gamma/></root>");
    XMLHandle handle(doc->RootElement()->FirstChildElement());
    XMLHandle next = handle.NextSiblingElement("gamma");
    EXPECT_NE(next.ToElement(), nullptr);
    EXPECT_STREQ(next.ToElement()->Name(), "gamma");
}

// Test NextSiblingElement on null handle
TEST_F(XMLHandleTest_120, NextSiblingElementOnNullHandle_120) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle next = handle.NextSiblingElement();
    EXPECT_EQ(next.ToElement(), nullptr);
}

// Test ToNode returns the underlying node
TEST_F(XMLHandleTest_120, ToNodeReturnsNode_120) {
    doc->Parse("<root/>");
    XMLNode* root = doc->RootElement();
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test ToNode on null handle
TEST_F(XMLHandleTest_120, ToNodeOnNullHandle_120) {
    XMLHandle handle((XMLNode*)nullptr);
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test ToElement returns element
TEST_F(XMLHandleTest_120, ToElementReturnsElement_120) {
    doc->Parse("<root/>");
    XMLElement* root = doc->RootElement();
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToElement(), root);
}

// Test ToElement on null handle
TEST_F(XMLHandleTest_120, ToElementOnNullHandle_120) {
    XMLHandle handle((XMLNode*)nullptr);
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test ToText on a text node
TEST_F(XMLHandleTest_120, ToTextOnTextNode_120) {
    doc->Parse("<root>Hello</root>");
    XMLHandle handle(doc->RootElement());
    XMLHandle textHandle = handle.FirstChild();
    EXPECT_NE(textHandle.ToText(), nullptr);
}

// Test ToText on non-text node
TEST_F(XMLHandleTest_120, ToTextOnNonTextNode_120) {
    doc->Parse("<root><child/></root>");
    XMLHandle handle(doc->RootElement());
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToText on null handle
TEST_F(XMLHandleTest_120, ToTextOnNullHandle_120) {
    XMLHandle handle((XMLNode*)nullptr);
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToUnknown on null handle
TEST_F(XMLHandleTest_120, ToUnknownOnNullHandle_120) {
    XMLHandle handle((XMLNode*)nullptr);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToDeclaration on null handle
TEST_F(XMLHandleTest_120, ToDeclarationOnNullHandle_120) {
    XMLHandle handle((XMLNode*)nullptr);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test ToDeclaration on a declaration node
TEST_F(XMLHandleTest_120, ToDeclarationOnDeclarationNode_120) {
    doc->Parse("<?xml version='1.0'?><root/>");
    XMLHandle handle(doc);
    XMLHandle firstChild = handle.FirstChild();
    EXPECT_NE(firstChild.ToDeclaration(), nullptr);
}

// Test chaining: FirstChildElement then NextSiblingElement
TEST_F(XMLHandleTest_120, ChainingFirstChildAndNextSibling_120) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLHandle handle(doc->RootElement());
    XMLHandle result = handle.FirstChildElement("a").NextSiblingElement("b");
    EXPECT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "b");
}

// Test chaining through null gracefully
TEST_F(XMLHandleTest_120, ChainingThroughNullGracefully_120) {
    doc->Parse("<root><a/></root>");
    XMLHandle handle(doc->RootElement());
    XMLHandle result = handle.FirstChildElement("nonexistent").FirstChild();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test chaining: deep navigation
TEST_F(XMLHandleTest_120, ChainingDeepNavigation_120) {
    doc->Parse("<root><a><b><c/></b></a></root>");
    XMLHandle handle(doc);
    XMLHandle result = handle.FirstChildElement("root")
                             .FirstChildElement("a")
                             .FirstChildElement("b")
                             .FirstChildElement("c");
    EXPECT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "c");
}

// Test handle with document node
TEST_F(XMLHandleTest_120, HandleWithDocumentNode_120) {
    doc->Parse("<root/>");
    XMLHandle handle(doc);
    EXPECT_NE(handle.ToNode(), nullptr);
    XMLHandle rootHandle = handle.FirstChildElement("root");
    EXPECT_NE(rootHandle.ToElement(), nullptr);
    EXPECT_STREQ(rootHandle.ToElement()->Name(), "root");
}

// Test FirstChild with mixed content (text and elements)
TEST_F(XMLHandleTest_120, FirstChildMixedContent_120) {
    doc->Parse("<root>text<child/></root>");
    XMLHandle handle(doc->RootElement());
    XMLHandle first = handle.FirstChild();
    EXPECT_NE(first.ToNode(), nullptr);
    EXPECT_NE(first.ToText(), nullptr);
}

// Test FirstChildElement skips text nodes
TEST_F(XMLHandleTest_120, FirstChildElementSkipsText_120) {
    doc->Parse("<root>text<child/></root>");
    XMLHandle handle(doc->RootElement());
    XMLHandle firstElem = handle.FirstChildElement();
    EXPECT_NE(firstElem.ToElement(), nullptr);
    EXPECT_STREQ(firstElem.ToElement()->Name(), "child");
}

// Test single child: FirstChild and LastChild return same
TEST_F(XMLHandleTest_120, SingleChildFirstAndLastSame_120) {
    doc->Parse("<root><only/></root>");
    XMLHandle handle(doc->RootElement());
    XMLHandle first = handle.FirstChild();
    XMLHandle last = handle.LastChild();
    EXPECT_EQ(first.ToNode(), last.ToNode());
}

// Test NextSiblingElement with name not found
TEST_F(XMLHandleTest_120, NextSiblingElementNameNotFound_120) {
    doc->Parse("<root><a/><b/></root>");
    XMLHandle handle(doc->RootElement()->FirstChildElement());
    XMLHandle next = handle.NextSiblingElement("z");
    EXPECT_EQ(next.ToElement(), nullptr);
}

// Test PreviousSiblingElement with name not found
TEST_F(XMLHandleTest_120, PreviousSiblingElementNameNotFound_120) {
    doc->Parse("<root><a/><b/></root>");
    XMLHandle handle(doc->RootElement()->LastChildElement());
    XMLHandle prev = handle.PreviousSiblingElement("z");
    EXPECT_EQ(prev.ToElement(), nullptr);
}

// Test self-assignment of XMLHandle
TEST_F(XMLHandleTest_120, SelfAssignment_120) {
    doc->Parse("<root/>");
    XMLHandle handle(doc->RootElement());
    XMLNode* originalNode = handle.ToNode();
    handle = handle;
    EXPECT_EQ(handle.ToNode(), originalNode);
}
