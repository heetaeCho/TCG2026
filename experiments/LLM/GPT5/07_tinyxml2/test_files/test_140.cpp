// File: ./TestProjects/tinyxml2/tests/xmlconsthandle_nextsibling_test_140.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleNextSiblingTest_140 : public ::testing::Test {
protected:
    static XMLDocument ParseDocOrFail(const char* xml) {
        XMLDocument doc;
        const XMLError err = doc.Parse(xml);
        EXPECT_EQ(err, XML_SUCCESS);
        return doc;
    }
};

TEST_F(XMLConstHandleNextSiblingTest_140, NullHandleNextSiblingReturnsNullNode_140) {
    const XMLConstHandle h(static_cast<const XMLNode*>(nullptr));

    const XMLConstHandle next = h.NextSibling();

    EXPECT_EQ(next.ToNode(), nullptr);
}

TEST_F(XMLConstHandleNextSiblingTest_140, NextSiblingFromFirstChildReturnsSecondChild_140) {
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root><a/><b/><c/></root>"), XML_SUCCESS);

    const XMLElement* rootEl = doc.RootElement();
    ASSERT_NE(rootEl, nullptr);

    const XMLNode* aNode = rootEl->FirstChild();  // <a/>
    ASSERT_NE(aNode, nullptr);

    const XMLNode* bNode = aNode->NextSibling();  // <b/>
    ASSERT_NE(bNode, nullptr);

    const XMLConstHandle aHandle(aNode);
    const XMLConstHandle nextHandle = aHandle.NextSibling();

    EXPECT_EQ(nextHandle.ToNode(), bNode);
}

TEST_F(XMLConstHandleNextSiblingTest_140, NextSiblingFromMiddleChildReturnsThirdChild_140) {
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root><a/><b/><c/></root>"), XML_SUCCESS);

    const XMLElement* rootEl = doc.RootElement();
    ASSERT_NE(rootEl, nullptr);

    const XMLNode* aNode = rootEl->FirstChild();          // <a/>
    ASSERT_NE(aNode, nullptr);
    const XMLNode* bNode = aNode->NextSibling();          // <b/>
    ASSERT_NE(bNode, nullptr);
    const XMLNode* cNode = bNode->NextSibling();          // <c/>
    ASSERT_NE(cNode, nullptr);

    const XMLConstHandle bHandle(bNode);
    const XMLConstHandle nextHandle = bHandle.NextSibling();

    EXPECT_EQ(nextHandle.ToNode(), cNode);
}

TEST_F(XMLConstHandleNextSiblingTest_140, NextSiblingFromLastChildReturnsNullNode_140) {
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root><a/><b/></root>"), XML_SUCCESS);

    const XMLElement* rootEl = doc.RootElement();
    ASSERT_NE(rootEl, nullptr);

    const XMLNode* aNode = rootEl->FirstChild();          // <a/>
    ASSERT_NE(aNode, nullptr);
    const XMLNode* bNode = aNode->NextSibling();          // <b/>
    ASSERT_NE(bNode, nullptr);
    ASSERT_EQ(bNode->NextSibling(), nullptr);             // last child

    const XMLConstHandle bHandle(bNode);
    const XMLConstHandle nextHandle = bHandle.NextSibling();

    EXPECT_EQ(nextHandle.ToNode(), nullptr);
}

TEST_F(XMLConstHandleNextSiblingTest_140, NextSiblingCanBeChainedAcrossMultipleSiblings_140) {
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root><a/><b/><c/></root>"), XML_SUCCESS);

    const XMLElement* rootEl = doc.RootElement();
    ASSERT_NE(rootEl, nullptr);

    const XMLNode* aNode = rootEl->FirstChild();          // <a/>
    ASSERT_NE(aNode, nullptr);
    const XMLNode* cNode = aNode->NextSibling();          // <b/>
    ASSERT_NE(cNode, nullptr);
    cNode = cNode->NextSibling();                         // <c/>
    ASSERT_NE(cNode, nullptr);

    const XMLConstHandle aHandle(aNode);
    const XMLConstHandle cHandle = aHandle.NextSibling().NextSibling();

    EXPECT_EQ(cHandle.ToNode(), cNode);
}
