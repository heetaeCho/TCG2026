// File: ./TestProjects/tinyxml2/xmlconsthandle_previoussibling_test_138.cpp

#include <gtest/gtest.h>
#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandlePreviousSiblingTest_138 : public ::testing::Test {
protected:
    static XMLDocument ParseDocOrFail(const char* xml) {
        XMLDocument doc;
        const XMLError err = doc.Parse(xml);
        EXPECT_EQ(err, XML_SUCCESS);
        return doc;
    }
};

TEST_F(XMLConstHandlePreviousSiblingTest_138, NullHandleReturnsNull_138) {
    XMLConstHandle h(static_cast<const XMLNode*>(nullptr));
    const XMLConstHandle prev = h.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
    EXPECT_EQ(prev.ToElement(), nullptr);
    EXPECT_EQ(prev.ToText(), nullptr);
    EXPECT_EQ(prev.ToUnknown(), nullptr);
    EXPECT_EQ(prev.ToDeclaration(), nullptr);
}

TEST_F(XMLConstHandlePreviousSiblingTest_138, MiddleElementReturnsPreviousSibling_138) {
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root><a/><b/><c/></root>"), XML_SUCCESS);

    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    const XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    XMLConstHandle hb(b);
    const XMLConstHandle prev = hb.PreviousSibling();

    EXPECT_EQ(prev.ToNode(), a);
    EXPECT_EQ(prev.ToElement(), a);
}

TEST_F(XMLConstHandlePreviousSiblingTest_138, FirstChildHasNoPreviousSibling_138) {
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root><a/><b/></root>"), XML_SUCCESS);

    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    XMLConstHandle ha(a);
    const XMLConstHandle prev = ha.PreviousSibling();

    EXPECT_EQ(prev.ToNode(), nullptr);
    EXPECT_EQ(prev.ToElement(), nullptr);
}

TEST_F(XMLConstHandlePreviousSiblingTest_138, ChainingPreviousSiblingEventuallyReturnsNull_138) {
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root><a/><b/><c/></root>"), XML_SUCCESS);

    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    const XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    const XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(c, nullptr);

    XMLConstHandle hc(c);

    const XMLConstHandle prev1 = hc.PreviousSibling();
    ASSERT_NE(prev1.ToNode(), nullptr);
    EXPECT_EQ(prev1.ToElement(), b);

    const XMLConstHandle prev2 = prev1.PreviousSibling();
    ASSERT_NE(prev2.ToNode(), nullptr);
    EXPECT_EQ(prev2.ToElement(), a);

    const XMLConstHandle prev3 = prev2.PreviousSibling();
    EXPECT_EQ(prev3.ToNode(), nullptr);
    EXPECT_EQ(prev3.ToElement(), nullptr);
}
