// TEST_ID: 134
// Unit tests for tinyxml2::XMLConstHandle::FirstChild()

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

class XMLConstHandleFirstChildTest_134 : public ::testing::Test {
protected:
    tinyxml2::XMLDocument doc_;
};

TEST_F(XMLConstHandleFirstChildTest_134, FirstChildOnNullHandleReturnsNull_134) {
    const tinyxml2::XMLConstHandle nullHandle(static_cast<const tinyxml2::XMLNode*>(nullptr));

    const tinyxml2::XMLConstHandle child = nullHandle.FirstChild();

    EXPECT_EQ(child.ToNode(), nullptr);
}

TEST_F(XMLConstHandleFirstChildTest_134, FirstChildMatchesUnderlyingXMLNodeFirstChildForElement_134) {
    const char* xml = "<root><a/><b/></root>";
    ASSERT_EQ(doc_.Parse(xml), tinyxml2::XML_SUCCESS);

    const tinyxml2::XMLElement* root = doc_.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const tinyxml2::XMLConstHandle rootHandle(*root);
    const tinyxml2::XMLConstHandle childHandle = rootHandle.FirstChild();

    // Observable behavior: should correspond to the same node as XMLNode::FirstChild()
    const tinyxml2::XMLNode* expected = root->FirstChild();
    EXPECT_EQ(childHandle.ToNode(), expected);

    // Additional observable check via public interface:
    // the first child of <root> should be the <a> element in this input.
    ASSERT_NE(childHandle.ToNode(), nullptr);
    EXPECT_STREQ(childHandle.ToNode()->Value(), "a");
}

TEST_F(XMLConstHandleFirstChildTest_134, FirstChildOnElementWithNoChildrenReturnsNull_134) {
    const char* xml = "<root/>";
    ASSERT_EQ(doc_.Parse(xml), tinyxml2::XML_SUCCESS);

    const tinyxml2::XMLElement* root = doc_.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const tinyxml2::XMLConstHandle rootHandle(*root);
    const tinyxml2::XMLConstHandle childHandle = rootHandle.FirstChild();

    EXPECT_EQ(childHandle.ToNode(), nullptr);
}

TEST_F(XMLConstHandleFirstChildTest_134, FirstChildMatchesUnderlyingXMLNodeFirstChildForDocument_134) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    ASSERT_EQ(doc_.Parse(xml), tinyxml2::XML_SUCCESS);

    const tinyxml2::XMLConstHandle docHandle(doc_);
    const tinyxml2::XMLConstHandle childHandle = docHandle.FirstChild();

    // Observable behavior: should correspond to the same node as XMLDocument/XMLNode::FirstChild()
    const tinyxml2::XMLNode* expected = doc_.FirstChild();
    EXPECT_EQ(childHandle.ToNode(), expected);

    // Sanity: parsing should have produced at least one child node under the document.
    EXPECT_NE(expected, nullptr);
}

TEST_F(XMLConstHandleFirstChildTest_134, ChainedFirstChildNavigatesDownOneLevelAtATime_134) {
    const char* xml = "<root><a>text</a></root>";
    ASSERT_EQ(doc_.Parse(xml), tinyxml2::XML_SUCCESS);

    const tinyxml2::XMLElement* root = doc_.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const tinyxml2::XMLConstHandle rootHandle(*root);

    const tinyxml2::XMLConstHandle aHandle = rootHandle.FirstChild();
    ASSERT_NE(aHandle.ToNode(), nullptr);
    EXPECT_STREQ(aHandle.ToNode()->Value(), "a");

    // Next FirstChild() should match the underlying node's FirstChild() (likely a text node here).
    const tinyxml2::XMLConstHandle textHandle = aHandle.FirstChild();
    EXPECT_EQ(textHandle.ToNode(), aHandle.ToNode()->FirstChild());

    // The child should exist for "<a>text</a>".
    EXPECT_NE(textHandle.ToNode(), nullptr);
}

}  // namespace
