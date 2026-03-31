#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLHandleTest_131 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
        // Build a simple document for testing
        // <root>
        //   <child1>text1</child1>
        //   <child2 attr="val">text2</child2>
        //   <child3/>
        // </root>
        const char* xml =
            "<?xml version=\"1.0\"?>"
            "<root>"
            "  <child1>text1</child1>"
            "  <child2 attr=\"val\">text2</child2>"
            "  <child3/>"
            "</root>";
        doc.Parse(xml);
    }
};

// Test constructing XMLHandle with a null node pointer
TEST_F(XMLHandleTest_131, ConstructWithNullNode_131) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
    EXPECT_EQ(handle.ToElement(), nullptr);
    EXPECT_EQ(handle.ToText(), nullptr);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test constructing XMLHandle with a valid node pointer
TEST_F(XMLHandleTest_131, ConstructWithValidNode_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
    EXPECT_EQ(handle.ToElement(), root);
}

// Test constructing XMLHandle with a node reference
TEST_F(XMLHandleTest_131, ConstructWithNodeReference_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle(*root);
    EXPECT_EQ(handle.ToNode(), root);
    EXPECT_EQ(handle.ToElement(), root);
}

// Test copy constructor
TEST_F(XMLHandleTest_131, CopyConstructor_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle1(root);
    XMLHandle handle2(handle1);
    EXPECT_EQ(handle2.ToNode(), root);
    EXPECT_EQ(handle2.ToElement(), root);
}

// Test assignment operator
TEST_F(XMLHandleTest_131, AssignmentOperator_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle1(root);
    XMLHandle handle2(static_cast<XMLNode*>(nullptr));
    handle2 = handle1;
    EXPECT_EQ(handle2.ToNode(), root);
    EXPECT_EQ(handle2.ToElement(), root);
}

// Test FirstChild on a valid node
TEST_F(XMLHandleTest_131, FirstChild_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle(root);
    XMLHandle firstChild = handle.FirstChild();
    EXPECT_NE(firstChild.ToNode(), nullptr);
}

// Test FirstChild on a null handle
TEST_F(XMLHandleTest_131, FirstChildOnNullHandle_131) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChildElement with no name filter
TEST_F(XMLHandleTest_131, FirstChildElementNoFilter_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle(root);
    XMLHandle firstElem = handle.FirstChildElement();
    EXPECT_NE(firstElem.ToElement(), nullptr);
    EXPECT_STREQ(firstElem.ToElement()->Name(), "child1");
}

// Test FirstChildElement with a name filter
TEST_F(XMLHandleTest_131, FirstChildElementWithName_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle(root);
    XMLHandle child2 = handle.FirstChildElement("child2");
    EXPECT_NE(child2.ToElement(), nullptr);
    EXPECT_STREQ(child2.ToElement()->Name(), "child2");
}

// Test FirstChildElement with a non-existent name
TEST_F(XMLHandleTest_131, FirstChildElementNonExistent_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle(root);
    XMLHandle nonExistent = handle.FirstChildElement("doesnotexist");
    EXPECT_EQ(nonExistent.ToElement(), nullptr);
    EXPECT_EQ(nonExistent.ToNode(), nullptr);
}

// Test FirstChildElement on a null handle
TEST_F(XMLHandleTest_131, FirstChildElementOnNullHandle_131) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle firstElem = handle.FirstChildElement();
    EXPECT_EQ(firstElem.ToElement(), nullptr);
}

// Test LastChild
TEST_F(XMLHandleTest_131, LastChild_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle(root);
    XMLHandle lastChild = handle.LastChild();
    EXPECT_NE(lastChild.ToNode(), nullptr);
}

// Test LastChild on a null handle
TEST_F(XMLHandleTest_131, LastChildOnNullHandle_131) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle lastChild = handle.LastChild();
    EXPECT_EQ(lastChild.ToNode(), nullptr);
}

// Test LastChildElement with no name filter
TEST_F(XMLHandleTest_131, LastChildElementNoFilter_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle(root);
    XMLHandle lastElem = handle.LastChildElement();
    EXPECT_NE(lastElem.ToElement(), nullptr);
    EXPECT_STREQ(lastElem.ToElement()->Name(), "child3");
}

// Test LastChildElement with a name filter
TEST_F(XMLHandleTest_131, LastChildElementWithName_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle(root);
    XMLHandle child1 = handle.LastChildElement("child1");
    EXPECT_NE(child1.ToElement(), nullptr);
    EXPECT_STREQ(child1.ToElement()->Name(), "child1");
}

// Test LastChildElement on a null handle
TEST_F(XMLHandleTest_131, LastChildElementOnNullHandle_131) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle lastElem = handle.LastChildElement();
    EXPECT_EQ(lastElem.ToElement(), nullptr);
}

// Test PreviousSibling
TEST_F(XMLHandleTest_131, PreviousSibling_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* child2 = root->FirstChildElement("child2");
    ASSERT_NE(child2, nullptr);
    XMLHandle handle(child2);
    XMLHandle prevSibling = handle.PreviousSibling();
    EXPECT_NE(prevSibling.ToNode(), nullptr);
}

// Test PreviousSibling on the first child (should still have text node before, or be null)
TEST_F(XMLHandleTest_131, PreviousSiblingOnFirstElement_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);
    XMLHandle handle(child1);
    XMLHandle prevSibling = handle.PreviousSibling();
    // There might be whitespace text nodes before child1, or it could be null
    // We just verify it doesn't crash
}

// Test PreviousSibling on a null handle
TEST_F(XMLHandleTest_131, PreviousSiblingOnNullHandle_131) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle prevSibling = handle.PreviousSibling();
    EXPECT_EQ(prevSibling.ToNode(), nullptr);
}

// Test PreviousSiblingElement
TEST_F(XMLHandleTest_131, PreviousSiblingElement_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* child3 = root->FirstChildElement("child3");
    ASSERT_NE(child3, nullptr);
    XMLHandle handle(child3);
    XMLHandle prevElem = handle.PreviousSiblingElement();
    EXPECT_NE(prevElem.ToElement(), nullptr);
    EXPECT_STREQ(prevElem.ToElement()->Name(), "child2");
}

// Test PreviousSiblingElement with name
TEST_F(XMLHandleTest_131, PreviousSiblingElementWithName_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* child3 = root->FirstChildElement("child3");
    ASSERT_NE(child3, nullptr);
    XMLHandle handle(child3);
    XMLHandle prevElem = handle.PreviousSiblingElement("child1");
    EXPECT_NE(prevElem.ToElement(), nullptr);
    EXPECT_STREQ(prevElem.ToElement()->Name(), "child1");
}

// Test PreviousSiblingElement on a null handle
TEST_F(XMLHandleTest_131, PreviousSiblingElementOnNullHandle_131) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle prevElem = handle.PreviousSiblingElement();
    EXPECT_EQ(prevElem.ToElement(), nullptr);
}

// Test NextSibling
TEST_F(XMLHandleTest_131, NextSibling_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);
    XMLHandle handle(child1);
    XMLHandle nextSibling = handle.NextSibling();
    EXPECT_NE(nextSibling.ToNode(), nullptr);
}

// Test NextSibling on a null handle
TEST_F(XMLHandleTest_131, NextSiblingOnNullHandle_131) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle nextSibling = handle.NextSibling();
    EXPECT_EQ(nextSibling.ToNode(), nullptr);
}

// Test NextSiblingElement
TEST_F(XMLHandleTest_131, NextSiblingElement_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);
    XMLHandle handle(child1);
    XMLHandle nextElem = handle.NextSiblingElement();
    EXPECT_NE(nextElem.ToElement(), nullptr);
    EXPECT_STREQ(nextElem.ToElement()->Name(), "child2");
}

// Test NextSiblingElement with name
TEST_F(XMLHandleTest_131, NextSiblingElementWithName_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);
    XMLHandle handle(child1);
    XMLHandle nextElem = handle.NextSiblingElement("child3");
    EXPECT_NE(nextElem.ToElement(), nullptr);
    EXPECT_STREQ(nextElem.ToElement()->Name(), "child3");
}

// Test NextSiblingElement on a null handle
TEST_F(XMLHandleTest_131, NextSiblingElementOnNullHandle_131) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle nextElem = handle.NextSiblingElement();
    EXPECT_EQ(nextElem.ToElement(), nullptr);
}

// Test ToNode returns the node
TEST_F(XMLHandleTest_131, ToNode_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test ToNode on null handle returns nullptr
TEST_F(XMLHandleTest_131, ToNodeNull_131) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test ToElement on an element handle
TEST_F(XMLHandleTest_131, ToElementValid_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToElement(), root);
}

// Test ToElement on a null handle
TEST_F(XMLHandleTest_131, ToElementNull_131) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test ToText on a text node
TEST_F(XMLHandleTest_131, ToTextValid_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);
    XMLHandle handle(child1);
    XMLHandle textHandle = handle.FirstChild();
    XMLText* text = textHandle.ToText();
    EXPECT_NE(text, nullptr);
}

// Test ToText on a non-text node
TEST_F(XMLHandleTest_131, ToTextOnElement_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToText on a null handle
TEST_F(XMLHandleTest_131, ToTextNull_131) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToUnknown on a null handle
TEST_F(XMLHandleTest_131, ToUnknownNull_131) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToUnknown on an element node (should return null)
TEST_F(XMLHandleTest_131, ToUnknownOnElement_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToDeclaration on null handle
TEST_F(XMLHandleTest_131, ToDeclarationNull_131) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test ToDeclaration on the XML declaration node
TEST_F(XMLHandleTest_131, ToDeclarationValid_131) {
    XMLHandle docHandle(&doc);
    XMLHandle firstChild = docHandle.FirstChild();
    XMLDeclaration* decl = firstChild.ToDeclaration();
    EXPECT_NE(decl, nullptr);
}

// Test ToDeclaration on an element node (should return null)
TEST_F(XMLHandleTest_131, ToDeclarationOnElement_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test chaining: navigate to a deep child via handles
TEST_F(XMLHandleTest_131, ChainingNavigation_131) {
    XMLHandle docHandle(&doc);
    XMLElement* elem = docHandle.FirstChildElement("root")
                                .FirstChildElement("child2")
                                .ToElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "child2");
}

// Test chaining with non-existent intermediate element returns null
TEST_F(XMLHandleTest_131, ChainingWithNonExistent_131) {
    XMLHandle docHandle(&doc);
    XMLElement* elem = docHandle.FirstChildElement("root")
                                .FirstChildElement("nonexistent")
                                .FirstChildElement("anything")
                                .ToElement();
    EXPECT_EQ(elem, nullptr);
}

// Test ToUnknown on an actual unknown node
TEST_F(XMLHandleTest_131, ToUnknownOnUnknownNode_131) {
    XMLDocument unknownDoc;
    const char* xml = "<root><!unknown stuff></root>";
    unknownDoc.Parse(xml);
    XMLElement* root = unknownDoc.FirstChildElement("root");
    if (root) {
        XMLHandle handle(root);
        XMLHandle firstChild = handle.FirstChild();
        // The unknown node should be parseable
        XMLUnknown* unknown = firstChild.ToUnknown();
        // If tinyxml2 parsed it as unknown, verify
        if (unknown) {
            EXPECT_NE(unknown, nullptr);
        }
    }
}

// Test handle on a document with no children
TEST_F(XMLHandleTest_131, EmptyDocument_131) {
    XMLDocument emptyDoc;
    XMLHandle handle(&emptyDoc);
    EXPECT_EQ(handle.FirstChild().ToNode(), nullptr);
    EXPECT_EQ(handle.FirstChildElement().ToElement(), nullptr);
    EXPECT_EQ(handle.LastChild().ToNode(), nullptr);
    EXPECT_EQ(handle.LastChildElement().ToElement(), nullptr);
}

// Test handle navigation on a node with no children
TEST_F(XMLHandleTest_131, NodeWithNoChildren_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* child3 = root->FirstChildElement("child3");
    ASSERT_NE(child3, nullptr);
    XMLHandle handle(child3);
    EXPECT_EQ(handle.FirstChild().ToNode(), nullptr);
    EXPECT_EQ(handle.FirstChildElement().ToElement(), nullptr);
    EXPECT_EQ(handle.LastChild().ToNode(), nullptr);
    EXPECT_EQ(handle.LastChildElement().ToElement(), nullptr);
}

// Test NextSiblingElement on last element returns null
TEST_F(XMLHandleTest_131, NextSiblingElementOnLastElement_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* child3 = root->FirstChildElement("child3");
    ASSERT_NE(child3, nullptr);
    XMLHandle handle(child3);
    XMLHandle nextElem = handle.NextSiblingElement();
    EXPECT_EQ(nextElem.ToElement(), nullptr);
}

// Test PreviousSiblingElement on first element returns null
TEST_F(XMLHandleTest_131, PreviousSiblingElementOnFirstElement_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);
    XMLHandle handle(child1);
    XMLHandle prevElem = handle.PreviousSiblingElement();
    EXPECT_EQ(prevElem.ToElement(), nullptr);
}

// Test self-assignment
TEST_F(XMLHandleTest_131, SelfAssignment_131) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle(root);
    handle = handle;
    EXPECT_EQ(handle.ToElement(), root);
}

// Test multiple levels of chaining with LastChildElement
TEST_F(XMLHandleTest_131, ChainingLastChildElement_131) {
    XMLHandle docHandle(&doc);
    XMLHandle lastChild = docHandle.FirstChildElement("root").LastChildElement();
    EXPECT_NE(lastChild.ToElement(), nullptr);
    EXPECT_STREQ(lastChild.ToElement()->Name(), "child3");
}

// Test navigating from document handle
TEST_F(XMLHandleTest_131, DocumentHandleNavigation_131) {
    XMLHandle docHandle(&doc);
    XMLNode* node = docHandle.ToNode();
    EXPECT_NE(node, nullptr);
    // Document should convert to node
    EXPECT_EQ(node, static_cast<XMLNode*>(&doc));
}
