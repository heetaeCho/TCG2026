// TEST_ID: 142
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleTest_142 : public ::testing::Test {
protected:
    XMLDocument doc_;

    const XMLNode* ParseAndGetFirstNode(const char* xml) {
        // Keep assertions minimal and local: tests depend on having a node to point at.
        XMLError err = doc_.Parse(xml);
        EXPECT_EQ(err, XML_SUCCESS);
        return doc_.FirstChild();
    }
};

TEST_F(XMLConstHandleTest_142, ToNodeReturnsSamePointerWhenConstructedWithPointer_142) {
    const XMLNode* node = ParseAndGetFirstNode("<root/>");
    ASSERT_NE(node, nullptr);

    XMLConstHandle handle(node);
    EXPECT_EQ(handle.ToNode(), node);
}

TEST_F(XMLConstHandleTest_142, ToNodeReturnsSamePointerWhenConstructedWithReference_142) {
    const XMLNode* node = ParseAndGetFirstNode("<root/>");
    ASSERT_NE(node, nullptr);

    XMLConstHandle handle(*node);
    EXPECT_EQ(handle.ToNode(), node);
}

TEST_F(XMLConstHandleTest_142, ToNodeReturnsNullptrWhenConstructedWithNullptr_142) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
}

TEST_F(XMLConstHandleTest_142, ToNodePreservedAfterCopyConstruction_142) {
    const XMLNode* node = ParseAndGetFirstNode("<root><child/></root>");
    ASSERT_NE(node, nullptr);

    XMLConstHandle original(node);
    XMLConstHandle copied(original);

    EXPECT_EQ(original.ToNode(), node);
    EXPECT_EQ(copied.ToNode(), node);
}

TEST_F(XMLConstHandleTest_142, ToNodePreservedAfterCopyAssignment_142) {
    const XMLNode* node1 = ParseAndGetFirstNode("<a/>");
    ASSERT_NE(node1, nullptr);

    XMLDocument otherDoc;
    ASSERT_EQ(otherDoc.Parse("<b/>"), XML_SUCCESS);
    const XMLNode* node2 = otherDoc.FirstChild();
    ASSERT_NE(node2, nullptr);

    XMLConstHandle h1(node1);
    XMLConstHandle h2(node2);

    // Baseline sanity
    EXPECT_EQ(h1.ToNode(), node1);
    EXPECT_EQ(h2.ToNode(), node2);

    // Observable behavior: after assignment, the handle should refer to the same node as the source.
    h2 = h1;
    EXPECT_EQ(h2.ToNode(), node1);
    EXPECT_EQ(h1.ToNode(), node1);
}
