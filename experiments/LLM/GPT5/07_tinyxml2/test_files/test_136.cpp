// TEST_ID: 136
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace tinyxml2 {

class XMLConstHandleLastChildTest_136 : public ::testing::Test {
protected:
    XMLDocument doc_;

    static const XMLNode* FindLastChildByTraversal(const XMLNode* node) {
        if (!node) return nullptr;
        const XMLNode* cur = node->FirstChild();
        if (!cur) return nullptr;
        while (cur->NextSibling()) {
            cur = cur->NextSibling();
        }
        return cur;
    }
};

TEST_F(XMLConstHandleLastChildTest_136, NullHandleReturnsNull_136) {
    const XMLConstHandle h(nullptr);

    const XMLConstHandle last = h.LastChild();

    EXPECT_EQ(last.ToNode(), nullptr);
}

TEST_F(XMLConstHandleLastChildTest_136, NodeWithNoChildrenReturnsNull_136) {
    ASSERT_EQ(doc_.Parse("<root/>"), XML_SUCCESS);
    const XMLElement* root = doc_.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLConstHandle h(*root);
    const XMLConstHandle last = h.LastChild();

    EXPECT_EQ(last.ToNode(), nullptr);
}

TEST_F(XMLConstHandleLastChildTest_136, ReturnsLastChildElementWhenMultipleElementChildren_136) {
    ASSERT_EQ(doc_.Parse("<root><a/><b/><c/></root>"), XML_SUCCESS);
    const XMLElement* root = doc_.RootElement();
    ASSERT_NE(root, nullptr);

    // Expected last child via public traversal (not relying on LastChild()).
    const XMLNode* expectedLast = FindLastChildByTraversal(root);
    ASSERT_NE(expectedLast, nullptr);

    const XMLConstHandle h(*root);
    const XMLConstHandle last = h.LastChild();

    EXPECT_EQ(last.ToNode(), expectedLast);
    EXPECT_NE(last.ToElement(), nullptr);
}

TEST_F(XMLConstHandleLastChildTest_136, LastChildCanBeTextNode_136) {
    ASSERT_EQ(doc_.Parse("<root>hello</root>"), XML_SUCCESS);
    const XMLElement* root = doc_.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLNode* expectedLast = FindLastChildByTraversal(root);
    ASSERT_NE(expectedLast, nullptr);

    const XMLConstHandle h(*root);
    const XMLConstHandle last = h.LastChild();

    EXPECT_EQ(last.ToNode(), expectedLast);
    EXPECT_NE(last.ToText(), nullptr);
}

TEST_F(XMLConstHandleLastChildTest_136, LastChildAfterTextAndElementIsElement_136) {
    ASSERT_EQ(doc_.Parse("<root>hello<child/></root>"), XML_SUCCESS);
    const XMLElement* root = doc_.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLNode* expectedLast = FindLastChildByTraversal(root);
    ASSERT_NE(expectedLast, nullptr);

    const XMLConstHandle h(*root);
    const XMLConstHandle last = h.LastChild();

    EXPECT_EQ(last.ToNode(), expectedLast);
    EXPECT_NE(last.ToElement(), nullptr);
}

TEST_F(XMLConstHandleLastChildTest_136, RepeatedCallsAreConsistent_136) {
    ASSERT_EQ(doc_.Parse("<root><a/><b/></root>"), XML_SUCCESS);
    const XMLElement* root = doc_.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLConstHandle h(*root);

    const XMLConstHandle last1 = h.LastChild();
    const XMLConstHandle last2 = h.LastChild();

    EXPECT_EQ(last1.ToNode(), last2.ToNode());
}

}  // namespace tinyxml2
