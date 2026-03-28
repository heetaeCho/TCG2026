#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleTest_135 : public ::testing::Test {
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
TEST_F(XMLConstHandleTest_135, ConstructWithNullNode_135) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test constructing XMLConstHandle with a valid node
TEST_F(XMLConstHandleTest_135, ConstructWithValidNode_135) {
    doc->Parse("<root><child/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test constructing XMLConstHandle with a node reference
TEST_F(XMLConstHandleTest_135, ConstructWithNodeReference_135) {
    doc->Parse("<root><child/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(*root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test copy constructor
TEST_F(XMLConstHandleTest_135, CopyConstructor_135) {
    doc->Parse("<root><child/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle1(root);
    XMLConstHandle handle2(handle1);
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test assignment operator
TEST_F(XMLConstHandleTest_135, AssignmentOperator_135) {
    doc->Parse("<root><child/></root>");
    const XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle1(root);
    XMLConstHandle handle2(static_cast<const XMLNode*>(nullptr));
    handle2 = handle1;
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test FirstChild on a valid node with children
TEST_F(XMLConstHandleTest_135, FirstChildValid_135) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_NE(firstChild.ToNode(), nullptr);
}

// Test FirstChild on a null handle
TEST_F(XMLConstHandleTest_135, FirstChildNullHandle_135) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChild on a node with no children
TEST_F(XMLConstHandleTest_135, FirstChildNoChildren_135) {
    doc->Parse("<root/>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChildElement with no name filter
TEST_F(XMLConstHandleTest_135, FirstChildElementNoFilter_135) {
    doc->Parse("<root><alpha/><beta/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle firstChildElem = handle.FirstChildElement();
    ASSERT_NE(firstChildElem.ToElement(), nullptr);
    EXPECT_STREQ(firstChildElem.ToElement()->Name(), "alpha");
}

// Test FirstChildElement with a name filter
TEST_F(XMLConstHandleTest_135, FirstChildElementWithName_135) {
    doc->Parse("<root><alpha/><beta/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle childElem = handle.FirstChildElement("beta");
    ASSERT_NE(childElem.ToElement(), nullptr);
    EXPECT_STREQ(childElem.ToElement()->Name(), "beta");
}

// Test FirstChildElement with a name that doesn't exist
TEST_F(XMLConstHandleTest_135, FirstChildElementNameNotFound_135) {
    doc->Parse("<root><alpha/><beta/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle childElem = handle.FirstChildElement("gamma");
    EXPECT_EQ(childElem.ToElement(), nullptr);
    EXPECT_EQ(childElem.ToNode(), nullptr);
}

// Test FirstChildElement on null handle
TEST_F(XMLConstHandleTest_135, FirstChildElementNullHandle_135) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle childElem = handle.FirstChildElement("anything");
    EXPECT_EQ(childElem.ToNode(), nullptr);
    EXPECT_EQ(childElem.ToElement(), nullptr);
}

// Test LastChild
TEST_F(XMLConstHandleTest_135, LastChildValid_135) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_NE(lastChild.ToNode(), nullptr);
}

// Test LastChild on null handle
TEST_F(XMLConstHandleTest_135, LastChildNullHandle_135) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle lastChild = handle.LastChild();
    EXPECT_EQ(lastChild.ToNode(), nullptr);
}

// Test LastChildElement with no name filter
TEST_F(XMLConstHandleTest_135, LastChildElementNoFilter_135) {
    doc->Parse("<root><alpha/><beta/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle lastChildElem = handle.LastChildElement();
    ASSERT_NE(lastChildElem.ToElement(), nullptr);
    EXPECT_STREQ(lastChildElem.ToElement()->Name(), "beta");
}

// Test LastChildElement with a name filter
TEST_F(XMLConstHandleTest_135, LastChildElementWithName_135) {
    doc->Parse("<root><alpha/><beta/><alpha/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle lastAlpha = handle.LastChildElement("alpha");
    ASSERT_NE(lastAlpha.ToElement(), nullptr);
    EXPECT_STREQ(lastAlpha.ToElement()->Name(), "alpha");
}

// Test LastChildElement on null handle
TEST_F(XMLConstHandleTest_135, LastChildElementNullHandle_135) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.LastChildElement();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test PreviousSibling
TEST_F(XMLConstHandleTest_135, PreviousSiblingValid_135) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* child2 = root->FirstChildElement("child2");
    ASSERT_NE(child2, nullptr);

    XMLConstHandle handle(child2);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_NE(prev.ToNode(), nullptr);
}

// Test PreviousSibling on null handle
TEST_F(XMLConstHandleTest_135, PreviousSiblingNullHandle_135) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSibling on the first child (no previous sibling)
TEST_F(XMLConstHandleTest_135, PreviousSiblingNone_135) {
    doc->Parse("<root><child1/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);

    XMLConstHandle handle(child1);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSiblingElement
TEST_F(XMLConstHandleTest_135, PreviousSiblingElementValid_135) {
    doc->Parse("<root><alpha/><beta/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* beta = root->FirstChildElement("beta");
    ASSERT_NE(beta, nullptr);

    XMLConstHandle handle(beta);
    XMLConstHandle prevElem = handle.PreviousSiblingElement();
    ASSERT_NE(prevElem.ToElement(), nullptr);
    EXPECT_STREQ(prevElem.ToElement()->Name(), "alpha");
}

// Test PreviousSiblingElement with name filter
TEST_F(XMLConstHandleTest_135, PreviousSiblingElementWithName_135) {
    doc->Parse("<root><alpha/><beta/><gamma/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* gamma = root->FirstChildElement("gamma");
    ASSERT_NE(gamma, nullptr);

    XMLConstHandle handle(gamma);
    XMLConstHandle prevAlpha = handle.PreviousSiblingElement("alpha");
    ASSERT_NE(prevAlpha.ToElement(), nullptr);
    EXPECT_STREQ(prevAlpha.ToElement()->Name(), "alpha");
}

// Test PreviousSiblingElement on null handle
TEST_F(XMLConstHandleTest_135, PreviousSiblingElementNullHandle_135) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.PreviousSiblingElement();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test NextSibling
TEST_F(XMLConstHandleTest_135, NextSiblingValid_135) {
    doc->Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);

    XMLConstHandle handle(child1);
    XMLConstHandle next = handle.NextSibling();
    EXPECT_NE(next.ToNode(), nullptr);
}

// Test NextSibling on null handle
TEST_F(XMLConstHandleTest_135, NextSiblingNullHandle_135) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test NextSibling on the last child (no next sibling)
TEST_F(XMLConstHandleTest_135, NextSiblingNone_135) {
    doc->Parse("<root><child1/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);

    XMLConstHandle handle(child1);
    XMLConstHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test NextSiblingElement
TEST_F(XMLConstHandleTest_135, NextSiblingElementValid_135) {
    doc->Parse("<root><alpha/><beta/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* alpha = root->FirstChildElement("alpha");
    ASSERT_NE(alpha, nullptr);

    XMLConstHandle handle(alpha);
    XMLConstHandle nextElem = handle.NextSiblingElement();
    ASSERT_NE(nextElem.ToElement(), nullptr);
    EXPECT_STREQ(nextElem.ToElement()->Name(), "beta");
}

// Test NextSiblingElement with name filter
TEST_F(XMLConstHandleTest_135, NextSiblingElementWithName_135) {
    doc->Parse("<root><alpha/><beta/><gamma/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* alpha = root->FirstChildElement("alpha");
    ASSERT_NE(alpha, nullptr);

    XMLConstHandle handle(alpha);
    XMLConstHandle nextGamma = handle.NextSiblingElement("gamma");
    ASSERT_NE(nextGamma.ToElement(), nullptr);
    EXPECT_STREQ(nextGamma.ToElement()->Name(), "gamma");
}

// Test NextSiblingElement on null handle
TEST_F(XMLConstHandleTest_135, NextSiblingElementNullHandle_135) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.NextSiblingElement();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test ToNode on a valid handle
TEST_F(XMLConstHandleTest_135, ToNodeValid_135) {
    doc->Parse("<root/>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test ToNode on a null handle
TEST_F(XMLConstHandleTest_135, ToNodeNull_135) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test ToElement on a valid element handle
TEST_F(XMLConstHandleTest_135, ToElementValid_135) {
    doc->Parse("<root/>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_NE(handle.ToElement(), nullptr);
    EXPECT_STREQ(handle.ToElement()->Name(), "root");
}

// Test ToElement on a null handle
TEST_F(XMLConstHandleTest_135, ToElementNull_135) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test ToText on a text node
TEST_F(XMLConstHandleTest_135, ToTextValid_135) {
    doc->Parse("<root>Hello</root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* textNode = root->FirstChild();
    ASSERT_NE(textNode, nullptr);

    XMLConstHandle handle(textNode);
    EXPECT_NE(handle.ToText(), nullptr);
}

// Test ToText on a non-text node
TEST_F(XMLConstHandleTest_135, ToTextOnElement_135) {
    doc->Parse("<root/>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToText on a null handle
TEST_F(XMLConstHandleTest_135, ToTextNull_135) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToUnknown on a null handle
TEST_F(XMLConstHandleTest_135, ToUnknownNull_135) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToDeclaration on a declaration node
TEST_F(XMLConstHandleTest_135, ToDeclarationValid_135) {
    doc->Parse("<?xml version=\"1.0\"?><root/>");
    const XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);

    XMLConstHandle handle(firstChild);
    // The first child could be the declaration
    // If it is, ToDeclaration should be non-null
    if (firstChild->ToDeclaration()) {
        EXPECT_NE(handle.ToDeclaration(), nullptr);
    }
}

// Test ToDeclaration on a null handle
TEST_F(XMLConstHandleTest_135, ToDeclarationNull_135) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test chaining: FirstChildElement then NextSiblingElement
TEST_F(XMLConstHandleTest_135, ChainingFirstChildThenNextSibling_135) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.FirstChildElement("a").NextSiblingElement("b");
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "b");
}

// Test chaining: multiple levels of FirstChildElement
TEST_F(XMLConstHandleTest_135, ChainingDeepFirstChildElement_135) {
    doc->Parse("<root><level1><level2><level3/></level2></level1></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle deepChild = handle.FirstChildElement("level1")
                                     .FirstChildElement("level2")
                                     .FirstChildElement("level3");
    ASSERT_NE(deepChild.ToElement(), nullptr);
    EXPECT_STREQ(deepChild.ToElement()->Name(), "level3");
}

// Test chaining through null (should remain null)
TEST_F(XMLConstHandleTest_135, ChainingThroughNull_135) {
    doc->Parse("<root><a/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.FirstChildElement("nonexistent")
                                  .FirstChildElement("anything");
    EXPECT_EQ(result.ToNode(), nullptr);
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test FirstChildElement with default parameter (nullptr)
TEST_F(XMLConstHandleTest_135, FirstChildElementDefaultParam_135) {
    doc->Parse("<root><alpha/><beta/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle firstElem = handle.FirstChildElement();
    ASSERT_NE(firstElem.ToElement(), nullptr);
    EXPECT_STREQ(firstElem.ToElement()->Name(), "alpha");
}

// Test handle constructed from XMLDocument directly
TEST_F(XMLConstHandleTest_135, HandleFromDocument_135) {
    doc->Parse("<root><child/></root>");

    XMLConstHandle handle(static_cast<const XMLNode*>(doc));
    XMLConstHandle rootHandle = handle.FirstChildElement("root");
    ASSERT_NE(rootHandle.ToElement(), nullptr);
    EXPECT_STREQ(rootHandle.ToElement()->Name(), "root");
}

// Test handle on empty document
TEST_F(XMLConstHandleTest_135, HandleEmptyDocument_135) {
    XMLConstHandle handle(static_cast<const XMLNode*>(doc));
    XMLConstHandle child = handle.FirstChildElement();
    EXPECT_EQ(child.ToElement(), nullptr);
}

// Test LastChildElement with no name on multiple children
TEST_F(XMLConstHandleTest_135, LastChildElementReturnsLast_135) {
    doc->Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle lastElem = handle.LastChildElement();
    ASSERT_NE(lastElem.ToElement(), nullptr);
    EXPECT_STREQ(lastElem.ToElement()->Name(), "c");
}

// Test NextSiblingElement returns nullptr when name not found
TEST_F(XMLConstHandleTest_135, NextSiblingElementNameNotFound_135) {
    doc->Parse("<root><a/><b/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    XMLConstHandle handle(a);
    XMLConstHandle result = handle.NextSiblingElement("nonexistent");
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test PreviousSiblingElement returns nullptr when name not found
TEST_F(XMLConstHandleTest_135, PreviousSiblingElementNameNotFound_135) {
    doc->Parse("<root><a/><b/></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    XMLConstHandle handle(b);
    XMLConstHandle result = handle.PreviousSiblingElement("nonexistent");
    EXPECT_EQ(result.ToElement(), nullptr);
}
