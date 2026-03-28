// TEST_ID: 182
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLNodeChildElementCountTest_182 : public ::testing::Test {
protected:
    XMLDocument doc;
};

TEST_F(XMLNodeChildElementCountTest_182, ReturnsZeroWhenNoChildren_182) {
    ASSERT_EQ(XML_SUCCESS, doc.Parse("<root/>"));

    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->ChildElementCount(nullptr), 0);
    EXPECT_EQ(root->ChildElementCount("child"), 0);
    EXPECT_EQ(root->ChildElementCount(""), 0);
}

TEST_F(XMLNodeChildElementCountTest_182, CountsAllDirectChildrenWhenNameIsNullptr_182) {
    ASSERT_EQ(XML_SUCCESS,
              doc.Parse("<root><a/><b/><c/></root>"));

    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->ChildElementCount(nullptr), 3);
}

TEST_F(XMLNodeChildElementCountTest_182, CountsOnlyMatchingElementNames_182) {
    ASSERT_EQ(XML_SUCCESS,
              doc.Parse("<root><a/><b/><a/><c/><a/></root>"));

    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->ChildElementCount("a"), 3);
    EXPECT_EQ(root->ChildElementCount("b"), 1);
    EXPECT_EQ(root->ChildElementCount("c"), 1);
    EXPECT_EQ(root->ChildElementCount("missing"), 0);
}

TEST_F(XMLNodeChildElementCountTest_182, DoesNotCountNestedDescendants_182) {
    ASSERT_EQ(XML_SUCCESS,
              doc.Parse("<root><a><a/><a/></a><a/></root>"));

    const XMLElement* rootEl = doc.FirstChildElement("root");
    ASSERT_NE(rootEl, nullptr);

    // Direct children named "a" under <root>: two (<a>...</a> and <a/>)
    EXPECT_EQ(rootEl->ChildElementCount("a"), 2);

    const XMLElement* firstA = rootEl->FirstChildElement("a");
    ASSERT_NE(firstA, nullptr);

    // Direct children named "a" under the first <a>: two (<a/><a/>)
    EXPECT_EQ(firstA->ChildElementCount("a"), 2);
}

TEST_F(XMLNodeChildElementCountTest_182, EmptyStringNameYieldsZeroWhenNoSuchElementsExist_182) {
    ASSERT_EQ(XML_SUCCESS,
              doc.Parse("<root><a/><b/></root>"));

    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    // An empty element name is not present in normal XML; observable behavior should be 0 here.
    EXPECT_EQ(root->ChildElementCount(""), 0);
}

TEST_F(XMLNodeChildElementCountTest_182, WorksForArbitraryElementNodesNotOnlyDocumentRoot_182) {
    ASSERT_EQ(XML_SUCCESS,
              doc.Parse("<root><parent><x/><y/><x/></parent></root>"));

    const XMLElement* parent = doc.FirstChildElement("root")->FirstChildElement("parent");
    ASSERT_NE(parent, nullptr);

    EXPECT_EQ(parent->ChildElementCount(nullptr), 3);
    EXPECT_EQ(parent->ChildElementCount("x"), 2);
    EXPECT_EQ(parent->ChildElementCount("y"), 1);
    EXPECT_EQ(parent->ChildElementCount("z"), 0);
}

}  // namespace
