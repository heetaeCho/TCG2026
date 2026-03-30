// TEST_ID: 53
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLNodeFirstChildElementTest_53 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* ParseAndGetRoot(const char* xml) {
        const XMLError err = doc.Parse(xml);
        EXPECT_EQ(err, XML_SUCCESS);
        XMLElement* root = doc.FirstChildElement("root");
        EXPECT_NE(root, nullptr);
        return root;
    }
};

TEST_F(XMLNodeFirstChildElementTest_53, NoName_ReturnsFirstChildElement_53) {
    XMLElement* root = ParseAndGetRoot("<root><a/><b/></root>");

    XMLNode* node = root;
    XMLElement* first = node->FirstChildElement();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Name(), "a");
}

TEST_F(XMLNodeFirstChildElementTest_53, NameMatches_ReturnsFirstMatchingChildElement_53) {
    XMLElement* root = ParseAndGetRoot("<root><a/><b/><b id='2'/></root>");

    XMLNode* node = root;
    XMLElement* b = node->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Name(), "b");
    // Should be the first <b/> (no id attribute).
    EXPECT_EQ(b->Attribute("id"), nullptr);
}

TEST_F(XMLNodeFirstChildElementTest_53, NameNotFound_ReturnsNullptr_53) {
    XMLElement* root = ParseAndGetRoot("<root><a/><b/></root>");

    XMLNode* node = root;
    EXPECT_EQ(node->FirstChildElement("c"), nullptr);
}

TEST_F(XMLNodeFirstChildElementTest_53, NoChildren_ReturnsNullptr_53) {
    XMLElement* root = ParseAndGetRoot("<root/>");

    XMLNode* node = root;
    EXPECT_EQ(node->FirstChildElement(), nullptr);
    EXPECT_EQ(node->FirstChildElement("anything"), nullptr);
}

TEST_F(XMLNodeFirstChildElementTest_53, NonConstOverloadMatchesConstOverloadPointer_53) {
    XMLElement* root = ParseAndGetRoot("<root><a/><b/></root>");

    XMLNode* node = root;
    const XMLNode* cnode = root;

    const XMLElement* constResultNoName = cnode->FirstChildElement(nullptr);
    XMLElement* nonConstResultNoName = node->FirstChildElement(nullptr);
    EXPECT_EQ(nonConstResultNoName, const_cast<XMLElement*>(constResultNoName));

    const XMLElement* constResultByName = cnode->FirstChildElement("b");
    XMLElement* nonConstResultByName = node->FirstChildElement("b");
    EXPECT_EQ(nonConstResultByName, const_cast<XMLElement*>(constResultByName));
}

TEST_F(XMLNodeFirstChildElementTest_53, RepeatedCalls_AreStable_53) {
    XMLElement* root = ParseAndGetRoot("<root><a/><b/></root>");

    XMLNode* node = root;

    XMLElement* first1 = node->FirstChildElement();
    XMLElement* first2 = node->FirstChildElement();
    EXPECT_EQ(first1, first2);

    XMLElement* b1 = node->FirstChildElement("b");
    XMLElement* b2 = node->FirstChildElement("b");
    EXPECT_EQ(b1, b2);
}

}  // namespace
