// File: ./TestProjects/tinyxml2/tests/XMLConstHandle_PreviousSiblingElement_139.test.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLConstHandlePreviousSiblingElementTest_139 : public ::testing::Test {
protected:
    static const XMLElement* ElementOrNull(const XMLConstHandle& h) {
        return h.ToElement();
    }
};

} // namespace

TEST_F(XMLConstHandlePreviousSiblingElementTest_139, NullHandleReturnsNull_139) {
    const XMLConstHandle nullHandle(static_cast<const XMLNode*>(nullptr));

    const XMLConstHandle prevAny = nullHandle.PreviousSiblingElement();
    EXPECT_EQ(prevAny.ToNode(), nullptr);
    EXPECT_EQ(prevAny.ToElement(), nullptr);

    const XMLConstHandle prevNamed = nullHandle.PreviousSiblingElement("a");
    EXPECT_EQ(prevNamed.ToNode(), nullptr);
    EXPECT_EQ(prevNamed.ToElement(), nullptr);
}

TEST_F(XMLConstHandlePreviousSiblingElementTest_139, PreviousSiblingElementWithoutNameFindsImmediatePreviousElement_139) {
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root><a/><b/><c/></root>"), XML_SUCCESS);

    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(c, nullptr);

    const XMLConstHandle hc(c);
    const XMLConstHandle prev = hc.PreviousSiblingElement();

    const XMLElement* prevElem = ElementOrNull(prev);
    ASSERT_NE(prevElem, nullptr);
    EXPECT_STREQ(prevElem->Name(), "b");
}

TEST_F(XMLConstHandlePreviousSiblingElementTest_139, PreviousSiblingElementWithNameFiltersByName_139) {
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root><a/><b/><c/></root>"), XML_SUCCESS);

    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(c, nullptr);

    const XMLConstHandle hc(c);

    {
        const XMLElement* e = ElementOrNull(hc.PreviousSiblingElement("b"));
        ASSERT_NE(e, nullptr);
        EXPECT_STREQ(e->Name(), "b");
    }
    {
        const XMLElement* e = ElementOrNull(hc.PreviousSiblingElement("a"));
        ASSERT_NE(e, nullptr);
        EXPECT_STREQ(e->Name(), "a");
    }
    {
        const XMLElement* e = ElementOrNull(hc.PreviousSiblingElement("does_not_exist"));
        EXPECT_EQ(e, nullptr);
    }
}

TEST_F(XMLConstHandlePreviousSiblingElementTest_139, FirstElementHasNoPreviousSiblingElement_139) {
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root><a/><b/></root>"), XML_SUCCESS);

    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    const XMLConstHandle ha(a);

    EXPECT_EQ(ElementOrNull(ha.PreviousSiblingElement()), nullptr);
    EXPECT_EQ(ElementOrNull(ha.PreviousSiblingElement("a")), nullptr);
}

TEST_F(XMLConstHandlePreviousSiblingElementTest_139, SkipsNonElementNodesWhenSearchingPreviousSiblingElement_139) {
    // There is a text node between <a/> and <b/>; PreviousSiblingElement() should still find <a/>.
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root><a/>text<b/></root>"), XML_SUCCESS);

    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    const XMLConstHandle hb(b);
    const XMLElement* prevElem = ElementOrNull(hb.PreviousSiblingElement());

    ASSERT_NE(prevElem, nullptr);
    EXPECT_STREQ(prevElem->Name(), "a");
}

TEST_F(XMLConstHandlePreviousSiblingElementTest_139, EmptyStringNameDoesNotCrashAndReturnsNullWhenNoMatch_139) {
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root><a/><b/></root>"), XML_SUCCESS);

    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    const XMLConstHandle hb(b);

    // Boundary input: empty string (distinct from nullptr default).
    const XMLElement* e = ElementOrNull(hb.PreviousSiblingElement(""));
    EXPECT_EQ(e, nullptr);
}

TEST_F(XMLConstHandlePreviousSiblingElementTest_139, DocumentNodeHasNoPreviousSiblingElement_139) {
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root><a/></root>"), XML_SUCCESS);

    const XMLConstHandle hdoc(doc);
    const XMLConstHandle prev = hdoc.PreviousSiblingElement();

    EXPECT_EQ(prev.ToNode(), nullptr);
    EXPECT_EQ(prev.ToElement(), nullptr);
}

TEST_F(XMLConstHandlePreviousSiblingElementTest_139, RootElementHasNoPreviousSiblingElement_139) {
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root><a/></root>"), XML_SUCCESS);

    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLConstHandle hroot(root);
    EXPECT_EQ(ElementOrNull(hroot.PreviousSiblingElement()), nullptr);
    EXPECT_EQ(ElementOrNull(hroot.PreviousSiblingElement("root")), nullptr);
}
