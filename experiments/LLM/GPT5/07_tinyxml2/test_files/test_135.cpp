// File: ./TestProjects/tinyxml2/tests/XMLConstHandle_FirstChildElement_135.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleFirstChildElementTest_135 : public ::testing::Test {
protected:
    // Helper that parses XML and asserts success.
    static XMLDocument ParseDocOrFail(const char* xml) {
        XMLDocument doc;
        ASSERT_EQ(XML_SUCCESS, doc.Parse(xml));
        return doc;
    }
};

TEST_F(XMLConstHandleFirstChildElementTest_135, ReturnsFirstChildElementWhenNameIsNull_135) {
    XMLDocument doc;
    ASSERT_EQ(XML_SUCCESS,
              doc.Parse("<root><a/><b/></root>"));

    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLConstHandle h(*root);

    // Compare to the observable result from the underlying node API.
    const XMLElement* expected = root->FirstChildElement(nullptr);
    const XMLConstHandle child = h.FirstChildElement(nullptr);

    EXPECT_EQ(child.ToElement(), expected);
    EXPECT_EQ(child.ToNode(), expected);  // Same pointer if element exists, else both null.
}

TEST_F(XMLConstHandleFirstChildElementTest_135, ReturnsFirstMatchingChildElementWhenNameProvided_135) {
    XMLDocument doc;
    ASSERT_EQ(XML_SUCCESS,
              doc.Parse("<root><a/><b/><c/></root>"));

    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLConstHandle h(*root);

    const XMLElement* expectedB = root->FirstChildElement("b");
    ASSERT_NE(expectedB, nullptr);

    const XMLConstHandle childB = h.FirstChildElement("b");
    EXPECT_EQ(childB.ToElement(), expectedB);
}

TEST_F(XMLConstHandleFirstChildElementTest_135, ReturnsNullHandleWhenNoMatchingChildElement_135) {
    XMLDocument doc;
    ASSERT_EQ(XML_SUCCESS,
              doc.Parse("<root><a/><b/></root>"));

    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLConstHandle h(*root);

    const XMLElement* expected = root->FirstChildElement("does_not_exist");
    ASSERT_EQ(expected, nullptr);

    const XMLConstHandle child = h.FirstChildElement("does_not_exist");
    EXPECT_EQ(child.ToNode(), nullptr);
    EXPECT_EQ(child.ToElement(), nullptr);
}

TEST_F(XMLConstHandleFirstChildElementTest_135, ReturnsNullHandleWhenUnderlyingNodeIsNull_135) {
    // Boundary: construct a handle with a null node pointer.
    const XMLConstHandle nullHandle(static_cast<const XMLNode*>(nullptr));

    const XMLConstHandle child = nullHandle.FirstChildElement();
    EXPECT_EQ(child.ToNode(), nullptr);
    EXPECT_EQ(child.ToElement(), nullptr);
}

TEST_F(XMLConstHandleFirstChildElementTest_135, ReturnsNullHandleWhenNodeHasNoChildren_135) {
    XMLDocument doc;
    ASSERT_EQ(XML_SUCCESS,
              doc.Parse("<root/>"));

    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLConstHandle h(*root);

    const XMLElement* expected = root->FirstChildElement(nullptr);
    ASSERT_EQ(expected, nullptr);

    const XMLConstHandle child = h.FirstChildElement();
    EXPECT_EQ(child.ToNode(), nullptr);
    EXPECT_EQ(child.ToElement(), nullptr);
}

TEST_F(XMLConstHandleFirstChildElementTest_135, WorksWhenHandleWrapsNonElementNodeWithNoChildren_135) {
    XMLDocument doc;
    ASSERT_EQ(XML_SUCCESS,
              doc.Parse("<root>text</root>"));

    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    // First child is expected to be a (non-element) node (typically text).
    const XMLNode* firstChildNode = root->FirstChild();
    ASSERT_NE(firstChildNode, nullptr);

    const XMLConstHandle h(firstChildNode);

    // Underlying node has no element children; compare to node API.
    const XMLElement* expected = firstChildNode->FirstChildElement(nullptr);
    ASSERT_EQ(expected, nullptr);

    const XMLConstHandle child = h.FirstChildElement();
    EXPECT_EQ(child.ToNode(), nullptr);
    EXPECT_EQ(child.ToElement(), nullptr);
}
