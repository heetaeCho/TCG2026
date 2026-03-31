#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleTest_142 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
        const char* xml =
            "<?xml version=\"1.0\"?>"
            "<root>"
            "  <first>text1</first>"
            "  <second attr=\"val\">text2</second>"
            "  <third/>"
            "  <!-- comment -->"
            "  <last>text3</last>"
            "</root>";
        doc.Parse(xml);
    }
};

// Test construction from a valid XMLNode pointer
TEST_F(XMLConstHandleTest_142, ConstructFromValidNodePointer_142) {
    const XMLNode* root = doc.RootElement();
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test construction from a null XMLNode pointer
TEST_F(XMLConstHandleTest_142, ConstructFromNullPointer_142) {
    const XMLNode* nullNode = nullptr;
    XMLConstHandle handle(nullNode);
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test construction from XMLNode reference
TEST_F(XMLConstHandleTest_142, ConstructFromNodeReference_142) {
    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLConstHandle handle(*root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test copy constructor
TEST_F(XMLConstHandleTest_142, CopyConstructor_142) {
    const XMLNode* root = doc.RootElement();
    XMLConstHandle handle1(root);
    XMLConstHandle handle2(handle1);
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test assignment operator
TEST_F(XMLConstHandleTest_142, AssignmentOperator_142) {
    const XMLNode* root = doc.RootElement();
    XMLConstHandle handle1(root);
    XMLConstHandle handle2(nullptr);
    handle2 = handle1;
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test ToNode returns the correct node
TEST_F(XMLConstHandleTest_142, ToNodeReturnsCorrectNode_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test ToElement on an element node
TEST_F(XMLConstHandleTest_142, ToElementOnElementNode_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToElement(), root);
}

// Test ToElement on a null handle
TEST_F(XMLConstHandleTest_142, ToElementOnNullHandle_142) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test ToText on a text node
TEST_F(XMLConstHandleTest_142, ToTextOnTextNode_142) {
    const XMLElement* first = doc.RootElement()->FirstChildElement("first");
    ASSERT_NE(first, nullptr);
    const XMLNode* textNode = first->FirstChild();
    ASSERT_NE(textNode, nullptr);
    XMLConstHandle handle(textNode);
    EXPECT_NE(handle.ToText(), nullptr);
}

// Test ToText on a non-text node
TEST_F(XMLConstHandleTest_142, ToTextOnNonTextNode_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToUnknown on a null handle
TEST_F(XMLConstHandleTest_142, ToUnknownOnNullHandle_142) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToDeclaration on the declaration node
TEST_F(XMLConstHandleTest_142, ToDeclarationOnDeclarationNode_142) {
    const XMLNode* firstChild = doc.FirstChild();
    ASSERT_NE(firstChild, nullptr);
    XMLConstHandle handle(firstChild);
    EXPECT_NE(handle.ToDeclaration(), nullptr);
}

// Test ToDeclaration on a non-declaration node
TEST_F(XMLConstHandleTest_142, ToDeclarationOnNonDeclarationNode_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test FirstChild on a valid node
TEST_F(XMLConstHandleTest_142, FirstChildOnValidNode_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_NE(firstChild.ToNode(), nullptr);
}

// Test FirstChild on a null handle
TEST_F(XMLConstHandleTest_142, FirstChildOnNullHandle_142) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChildElement with no name filter
TEST_F(XMLConstHandleTest_142, FirstChildElementNoFilter_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle firstElem = handle.FirstChildElement();
    ASSERT_NE(firstElem.ToElement(), nullptr);
    EXPECT_STREQ(firstElem.ToElement()->Name(), "first");
}

// Test FirstChildElement with name filter
TEST_F(XMLConstHandleTest_142, FirstChildElementWithNameFilter_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle secondElem = handle.FirstChildElement("second");
    ASSERT_NE(secondElem.ToElement(), nullptr);
    EXPECT_STREQ(secondElem.ToElement()->Name(), "second");
}

// Test FirstChildElement with non-existent name
TEST_F(XMLConstHandleTest_142, FirstChildElementNonExistentName_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle noElem = handle.FirstChildElement("nonexistent");
    EXPECT_EQ(noElem.ToNode(), nullptr);
}

// Test FirstChildElement on a null handle
TEST_F(XMLConstHandleTest_142, FirstChildElementOnNullHandle_142) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.FirstChildElement();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test LastChild on a valid node
TEST_F(XMLConstHandleTest_142, LastChildOnValidNode_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_NE(lastChild.ToNode(), nullptr);
}

// Test LastChild on a null handle
TEST_F(XMLConstHandleTest_142, LastChildOnNullHandle_142) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_EQ(lastChild.ToNode(), nullptr);
}

// Test LastChildElement with no name filter
TEST_F(XMLConstHandleTest_142, LastChildElementNoFilter_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle lastElem = handle.LastChildElement();
    ASSERT_NE(lastElem.ToElement(), nullptr);
    EXPECT_STREQ(lastElem.ToElement()->Name(), "last");
}

// Test LastChildElement with name filter
TEST_F(XMLConstHandleTest_142, LastChildElementWithNameFilter_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle thirdElem = handle.LastChildElement("third");
    ASSERT_NE(thirdElem.ToElement(), nullptr);
    EXPECT_STREQ(thirdElem.ToElement()->Name(), "third");
}

// Test LastChildElement on a null handle
TEST_F(XMLConstHandleTest_142, LastChildElementOnNullHandle_142) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.LastChildElement();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test NextSibling
TEST_F(XMLConstHandleTest_142, NextSibling_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle firstChild = handle.FirstChildElement("first");
    ASSERT_NE(firstChild.ToNode(), nullptr);
    XMLConstHandle nextSib = firstChild.NextSibling();
    EXPECT_NE(nextSib.ToNode(), nullptr);
}

// Test NextSibling on null handle
TEST_F(XMLConstHandleTest_142, NextSiblingOnNullHandle_142) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.NextSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test NextSiblingElement with no filter
TEST_F(XMLConstHandleTest_142, NextSiblingElementNoFilter_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle firstElem = handle.FirstChildElement("first");
    ASSERT_NE(firstElem.ToNode(), nullptr);
    XMLConstHandle nextElem = firstElem.NextSiblingElement();
    ASSERT_NE(nextElem.ToElement(), nullptr);
    EXPECT_STREQ(nextElem.ToElement()->Name(), "second");
}

// Test NextSiblingElement with name filter
TEST_F(XMLConstHandleTest_142, NextSiblingElementWithNameFilter_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle firstElem = handle.FirstChildElement("first");
    ASSERT_NE(firstElem.ToNode(), nullptr);
    XMLConstHandle thirdElem = firstElem.NextSiblingElement("third");
    ASSERT_NE(thirdElem.ToElement(), nullptr);
    EXPECT_STREQ(thirdElem.ToElement()->Name(), "third");
}

// Test NextSiblingElement on null handle
TEST_F(XMLConstHandleTest_142, NextSiblingElementOnNullHandle_142) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.NextSiblingElement();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test PreviousSibling
TEST_F(XMLConstHandleTest_142, PreviousSibling_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle lastElem = handle.LastChildElement("last");
    ASSERT_NE(lastElem.ToNode(), nullptr);
    XMLConstHandle prevSib = lastElem.PreviousSibling();
    EXPECT_NE(prevSib.ToNode(), nullptr);
}

// Test PreviousSibling on null handle
TEST_F(XMLConstHandleTest_142, PreviousSiblingOnNullHandle_142) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.PreviousSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test PreviousSiblingElement with no filter
TEST_F(XMLConstHandleTest_142, PreviousSiblingElementNoFilter_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle lastElem = handle.LastChildElement("last");
    ASSERT_NE(lastElem.ToNode(), nullptr);
    XMLConstHandle prevElem = lastElem.PreviousSiblingElement();
    ASSERT_NE(prevElem.ToElement(), nullptr);
    EXPECT_STREQ(prevElem.ToElement()->Name(), "third");
}

// Test PreviousSiblingElement with name filter
TEST_F(XMLConstHandleTest_142, PreviousSiblingElementWithNameFilter_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle lastElem = handle.LastChildElement("last");
    ASSERT_NE(lastElem.ToNode(), nullptr);
    XMLConstHandle firstElem = lastElem.PreviousSiblingElement("first");
    ASSERT_NE(firstElem.ToElement(), nullptr);
    EXPECT_STREQ(firstElem.ToElement()->Name(), "first");
}

// Test PreviousSiblingElement on null handle
TEST_F(XMLConstHandleTest_142, PreviousSiblingElementOnNullHandle_142) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.PreviousSiblingElement();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test chaining: navigate to a grandchild
TEST_F(XMLConstHandleTest_142, ChainingNavigation_142) {
    XMLConstHandle handle(&doc);
    const XMLConstHandle textHandle = handle.FirstChildElement("root")
                                            .FirstChildElement("first")
                                            .FirstChild();
    ASSERT_NE(textHandle.ToNode(), nullptr);
    ASSERT_NE(textHandle.ToText(), nullptr);
    EXPECT_STREQ(textHandle.ToText()->Value(), "text1");
}

// Test chaining with null intermediate step
TEST_F(XMLConstHandleTest_142, ChainingWithNullIntermediate_142) {
    XMLConstHandle handle(&doc);
    const XMLConstHandle result = handle.FirstChildElement("root")
                                        .FirstChildElement("nonexistent")
                                        .FirstChild();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test node with no children
TEST_F(XMLConstHandleTest_142, NodeWithNoChildren_142) {
    const XMLElement* third = doc.RootElement()->FirstChildElement("third");
    ASSERT_NE(third, nullptr);
    XMLConstHandle handle(third);
    EXPECT_EQ(handle.FirstChild().ToNode(), nullptr);
    EXPECT_EQ(handle.FirstChildElement().ToNode(), nullptr);
    EXPECT_EQ(handle.LastChild().ToNode(), nullptr);
    EXPECT_EQ(handle.LastChildElement().ToNode(), nullptr);
}

// Test NextSiblingElement when there is no next sibling element
TEST_F(XMLConstHandleTest_142, NextSiblingElementAtEnd_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle lastElem = handle.LastChildElement("last");
    ASSERT_NE(lastElem.ToNode(), nullptr);
    XMLConstHandle noNext = lastElem.NextSiblingElement();
    EXPECT_EQ(noNext.ToNode(), nullptr);
}

// Test PreviousSiblingElement when there is no previous sibling element
TEST_F(XMLConstHandleTest_142, PreviousSiblingElementAtBeginning_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    XMLConstHandle firstElem = handle.FirstChildElement("first");
    ASSERT_NE(firstElem.ToNode(), nullptr);
    XMLConstHandle noPrev = firstElem.PreviousSiblingElement();
    EXPECT_EQ(noPrev.ToNode(), nullptr);
}

// Test document handle
TEST_F(XMLConstHandleTest_142, DocumentHandle_142) {
    const XMLDocument* constDoc = &doc;
    XMLConstHandle handle(constDoc);
    EXPECT_EQ(handle.ToNode(), constDoc);
}

// Test self-assignment
TEST_F(XMLConstHandleTest_142, SelfAssignment_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    handle = handle;
    EXPECT_EQ(handle.ToNode(), root);
}

// Test ToUnknown on element returns null
TEST_F(XMLConstHandleTest_142, ToUnknownOnElementReturnsNull_142) {
    const XMLElement* root = doc.RootElement();
    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToText on null returns null
TEST_F(XMLConstHandleTest_142, ToTextOnNullReturnsNull_142) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToDeclaration on null returns null
TEST_F(XMLConstHandleTest_142, ToDeclarationOnNullReturnsNull_142) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}
