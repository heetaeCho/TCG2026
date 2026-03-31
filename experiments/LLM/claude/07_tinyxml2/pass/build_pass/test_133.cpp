#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleTest_133 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
        const char* xml =
            "<?xml version=\"1.0\"?>"
            "<root>"
            "  <first>text1</first>"
            "  <second attr=\"value\">text2</second>"
            "  <third/>"
            "  <!-- comment -->"
            "  <last>text3</last>"
            "</root>";
        doc.Parse(xml);
    }
};

// Test construction from a valid XMLNode pointer
TEST_F(XMLConstHandleTest_133, ConstructFromValidNodePointer_133) {
    const XMLNode* root = doc.RootElement();
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test construction from a null XMLNode pointer
TEST_F(XMLConstHandleTest_133, ConstructFromNullPointer_133) {
    const XMLNode* nullNode = nullptr;
    XMLConstHandle handle(nullNode);
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test construction from XMLNode reference
TEST_F(XMLConstHandleTest_133, ConstructFromNodeReference_133) {
    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLConstHandle handle(*root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test copy constructor
TEST_F(XMLConstHandleTest_133, CopyConstructor_133) {
    const XMLNode* root = doc.RootElement();
    XMLConstHandle handle1(root);
    XMLConstHandle handle2(handle1);
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test assignment operator
TEST_F(XMLConstHandleTest_133, AssignmentOperator_133) {
    const XMLNode* root = doc.RootElement();
    XMLConstHandle handle1(root);
    XMLConstHandle handle2(static_cast<const XMLNode*>(nullptr));
    handle2 = handle1;
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test assignment operator with null handle
TEST_F(XMLConstHandleTest_133, AssignmentOperatorNull_133) {
    const XMLNode* root = doc.RootElement();
    XMLConstHandle handle1(root);
    XMLConstHandle nullHandle(static_cast<const XMLNode*>(nullptr));
    handle1 = nullHandle;
    EXPECT_EQ(handle1.ToNode(), nullptr);
}

// Test ToElement on an element node
TEST_F(XMLConstHandleTest_133, ToElementOnElement_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToElement(), root);
}

// Test ToElement on null
TEST_F(XMLConstHandleTest_133, ToElementOnNull_133) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test ToText on a text node
TEST_F(XMLConstHandleTest_133, ToTextOnTextNode_133) {
    const XMLElement* first = doc.RootElement()->FirstChildElement("first");
    ASSERT_NE(first, nullptr);
    const XMLNode* textNode = first->FirstChild();
    ASSERT_NE(textNode, nullptr);
    XMLConstHandle handle(textNode);
    EXPECT_NE(handle.ToText(), nullptr);
}

// Test ToText on a non-text node
TEST_F(XMLConstHandleTest_133, ToTextOnNonTextNode_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToNode returns the underlying node
TEST_F(XMLConstHandleTest_133, ToNodeReturnsCorrectNode_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), static_cast<const XMLNode*>(root));
}

// Test ToNode on null handle
TEST_F(XMLConstHandleTest_133, ToNodeOnNullHandle_133) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test FirstChild
TEST_F(XMLConstHandleTest_133, FirstChild_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_NE(firstChild.ToNode(), nullptr);
}

// Test FirstChild on null handle
TEST_F(XMLConstHandleTest_133, FirstChildOnNull_133) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChildElement with no name filter
TEST_F(XMLConstHandleTest_133, FirstChildElementNoFilter_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle firstElem = handle.FirstChildElement();
    ASSERT_NE(firstElem.ToElement(), nullptr);
    EXPECT_STREQ(firstElem.ToElement()->Name(), "first");
}

// Test FirstChildElement with name filter
TEST_F(XMLConstHandleTest_133, FirstChildElementWithName_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle secondElem = handle.FirstChildElement("second");
    ASSERT_NE(secondElem.ToElement(), nullptr);
    EXPECT_STREQ(secondElem.ToElement()->Name(), "second");
}

// Test FirstChildElement with non-existent name
TEST_F(XMLConstHandleTest_133, FirstChildElementNonExistent_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle result = handle.FirstChildElement("nonexistent");
    EXPECT_EQ(result.ToElement(), nullptr);
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test FirstChildElement on null handle
TEST_F(XMLConstHandleTest_133, FirstChildElementOnNull_133) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.FirstChildElement();
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test LastChild
TEST_F(XMLConstHandleTest_133, LastChild_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_NE(lastChild.ToNode(), nullptr);
}

// Test LastChild on null handle
TEST_F(XMLConstHandleTest_133, LastChildOnNull_133) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_EQ(lastChild.ToNode(), nullptr);
}

// Test LastChildElement with no name filter
TEST_F(XMLConstHandleTest_133, LastChildElementNoFilter_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle lastElem = handle.LastChildElement();
    ASSERT_NE(lastElem.ToElement(), nullptr);
    EXPECT_STREQ(lastElem.ToElement()->Name(), "last");
}

// Test LastChildElement with name filter
TEST_F(XMLConstHandleTest_133, LastChildElementWithName_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle result = handle.LastChildElement("first");
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "first");
}

// Test LastChildElement with non-existent name
TEST_F(XMLConstHandleTest_133, LastChildElementNonExistent_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle result = handle.LastChildElement("nonexistent");
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test LastChildElement on null handle
TEST_F(XMLConstHandleTest_133, LastChildElementOnNull_133) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.LastChildElement();
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test NextSibling
TEST_F(XMLConstHandleTest_133, NextSibling_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle firstElem = handle.FirstChildElement("first");
    ASSERT_NE(firstElem.ToNode(), nullptr);
    XMLConstHandle nextSibling = firstElem.NextSibling();
    EXPECT_NE(nextSibling.ToNode(), nullptr);
}

// Test NextSibling on null handle
TEST_F(XMLConstHandleTest_133, NextSiblingOnNull_133) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.NextSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test NextSiblingElement with no name filter
TEST_F(XMLConstHandleTest_133, NextSiblingElementNoFilter_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle firstElem = handle.FirstChildElement("first");
    ASSERT_NE(firstElem.ToElement(), nullptr);
    XMLConstHandle nextSiblingElem = firstElem.NextSiblingElement();
    ASSERT_NE(nextSiblingElem.ToElement(), nullptr);
    EXPECT_STREQ(nextSiblingElem.ToElement()->Name(), "second");
}

// Test NextSiblingElement with name filter
TEST_F(XMLConstHandleTest_133, NextSiblingElementWithName_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle firstElem = handle.FirstChildElement("first");
    ASSERT_NE(firstElem.ToElement(), nullptr);
    XMLConstHandle result = firstElem.NextSiblingElement("third");
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "third");
}

// Test NextSiblingElement with non-existent name
TEST_F(XMLConstHandleTest_133, NextSiblingElementNonExistent_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle firstElem = handle.FirstChildElement("first");
    ASSERT_NE(firstElem.ToElement(), nullptr);
    XMLConstHandle result = firstElem.NextSiblingElement("nonexistent");
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test NextSiblingElement on null handle
TEST_F(XMLConstHandleTest_133, NextSiblingElementOnNull_133) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.NextSiblingElement();
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test PreviousSibling
TEST_F(XMLConstHandleTest_133, PreviousSibling_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle lastElem = handle.LastChildElement("last");
    ASSERT_NE(lastElem.ToNode(), nullptr);
    XMLConstHandle prevSibling = lastElem.PreviousSibling();
    EXPECT_NE(prevSibling.ToNode(), nullptr);
}

// Test PreviousSibling on null handle
TEST_F(XMLConstHandleTest_133, PreviousSiblingOnNull_133) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.PreviousSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test PreviousSiblingElement with no name filter
TEST_F(XMLConstHandleTest_133, PreviousSiblingElementNoFilter_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle lastElem = handle.LastChildElement("last");
    ASSERT_NE(lastElem.ToElement(), nullptr);
    XMLConstHandle prevSiblingElem = lastElem.PreviousSiblingElement();
    ASSERT_NE(prevSiblingElem.ToElement(), nullptr);
    EXPECT_STREQ(prevSiblingElem.ToElement()->Name(), "third");
}

// Test PreviousSiblingElement with name filter
TEST_F(XMLConstHandleTest_133, PreviousSiblingElementWithName_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle lastElem = handle.LastChildElement("last");
    ASSERT_NE(lastElem.ToElement(), nullptr);
    XMLConstHandle result = lastElem.PreviousSiblingElement("first");
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "first");
}

// Test PreviousSiblingElement with non-existent name
TEST_F(XMLConstHandleTest_133, PreviousSiblingElementNonExistent_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle lastElem = handle.LastChildElement("last");
    ASSERT_NE(lastElem.ToElement(), nullptr);
    XMLConstHandle result = lastElem.PreviousSiblingElement("nonexistent");
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test PreviousSiblingElement on null handle
TEST_F(XMLConstHandleTest_133, PreviousSiblingElementOnNull_133) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.PreviousSiblingElement();
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test ToUnknown on a non-unknown node
TEST_F(XMLConstHandleTest_133, ToUnknownOnElement_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToUnknown on null handle
TEST_F(XMLConstHandleTest_133, ToUnknownOnNull_133) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToDeclaration on declaration node
TEST_F(XMLConstHandleTest_133, ToDeclarationOnDeclaration_133) {
    const XMLNode* firstChild = doc.FirstChild();
    ASSERT_NE(firstChild, nullptr);
    XMLConstHandle handle(firstChild);
    // The first child of the document should be the XML declaration
    EXPECT_NE(handle.ToDeclaration(), nullptr);
}

// Test ToDeclaration on element node returns null
TEST_F(XMLConstHandleTest_133, ToDeclarationOnElement_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test ToDeclaration on null handle
TEST_F(XMLConstHandleTest_133, ToDeclarationOnNull_133) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test chaining operations
TEST_F(XMLConstHandleTest_133, ChainingOperations_133) {
    XMLConstHandle handle(&doc);
    const XMLElement* elem = handle.FirstChildElement("root")
                                    .FirstChildElement("second")
                                    .ToElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "second");
}

// Test chaining with null intermediate
TEST_F(XMLConstHandleTest_133, ChainingWithNullIntermediate_133) {
    XMLConstHandle handle(&doc);
    const XMLElement* elem = handle.FirstChildElement("nonexistent")
                                    .FirstChildElement("second")
                                    .ToElement();
    EXPECT_EQ(elem, nullptr);
}

// Test self-assignment
TEST_F(XMLConstHandleTest_133, SelfAssignment_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    handle = handle;
    EXPECT_EQ(handle.ToNode(), root);
}

// Test empty document
TEST_F(XMLConstHandleTest_133, EmptyDocumentFirstChild_133) {
    XMLDocument emptyDoc;
    XMLConstHandle handle(&emptyDoc);
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test node with no children
TEST_F(XMLConstHandleTest_133, LeafNodeFirstChild_133) {
    const XMLElement* third = doc.RootElement()->FirstChildElement("third");
    ASSERT_NE(third, nullptr);
    XMLConstHandle handle(third);
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test node with no children - LastChild
TEST_F(XMLConstHandleTest_133, LeafNodeLastChild_133) {
    const XMLElement* third = doc.RootElement()->FirstChildElement("third");
    ASSERT_NE(third, nullptr);
    XMLConstHandle handle(third);
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_EQ(lastChild.ToNode(), nullptr);
}

// Test NextSibling on last sibling returns null
TEST_F(XMLConstHandleTest_133, NextSiblingOnLastSibling_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle lastElem = handle.LastChildElement("last");
    ASSERT_NE(lastElem.ToNode(), nullptr);
    XMLConstHandle nextSibling = lastElem.NextSibling();
    EXPECT_EQ(nextSibling.ToNode(), nullptr);
}

// Test PreviousSibling on first child
TEST_F(XMLConstHandleTest_133, PreviousSiblingOnFirstChild_133) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle firstChild = handle.FirstChild();
    ASSERT_NE(firstChild.ToNode(), nullptr);
    // Keep going to the actual first child
    // The root's first child might be text or element
    // Let's just test on first child element
    XMLConstHandle firstElem = handle.FirstChildElement("first");
    ASSERT_NE(firstElem.ToElement(), nullptr);
    XMLConstHandle prevElem = firstElem.PreviousSiblingElement();
    EXPECT_EQ(prevElem.ToElement(), nullptr);
}

// Test ToText on null handle
TEST_F(XMLConstHandleTest_133, ToTextOnNull_133) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToText(), nullptr);
}
