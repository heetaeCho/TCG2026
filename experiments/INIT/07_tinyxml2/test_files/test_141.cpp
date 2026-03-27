// File: ./TestProjects/tinyxml2/tests/XMLConstHandle_NextSiblingElement_141_test.cpp

#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleNextSiblingElementTest_141 : public ::testing::Test {
protected:
    XMLDocument doc;

    const XMLElement* ParseAndGetRoot(const char* xml) {
        const XMLError err = doc.Parse(xml);
        EXPECT_EQ(err, XML_SUCCESS);
        const XMLElement* root = doc.RootElement();
        EXPECT_NE(root, nullptr);
        return root;
    }
};

TEST_F(XMLConstHandleNextSiblingElementTest_141, WithoutName_ReturnsImmediateNextElementSibling_141) {
    const XMLElement* root = ParseAndGetRoot("<root><a/><b/><c/></root>");
    const XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    const XMLConstHandle h(a);
    const XMLConstHandle next = h.NextSiblingElement();  // default name = 0

    const XMLElement* nextElem = next.ToElement();
    ASSERT_NE(nextElem, nullptr);
    EXPECT_STREQ(nextElem->Name(), "b");
}

TEST_F(XMLConstHandleNextSiblingElementTest_141, WithName_SkipsNonMatchingSiblingsAndReturnsNextMatching_141) {
    const XMLElement* root = ParseAndGetRoot("<root><a/><b/><c/><b id='2'/></root>");
    const XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    const XMLConstHandle h(a);
    const XMLConstHandle nextB = h.NextSiblingElement("b");

    const XMLElement* nextElem = nextB.ToElement();
    ASSERT_NE(nextElem, nullptr);
    EXPECT_STREQ(nextElem->Name(), "b");
    // First <b/> has no id attribute, so "id" should be absent.
    EXPECT_EQ(nextElem->Attribute("id"), nullptr);
}

TEST_F(XMLConstHandleNextSiblingElementTest_141, WithName_FindsLaterMatchingSiblingAfterOtherElements_141) {
    const XMLElement* root = ParseAndGetRoot("<root><a/><b/><c/><b id='2'/></root>");
    const XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(c, nullptr);

    const XMLConstHandle h(c);
    const XMLConstHandle nextB = h.NextSiblingElement("b");

    const XMLElement* nextElem = nextB.ToElement();
    ASSERT_NE(nextElem, nullptr);
    EXPECT_STREQ(nextElem->Name(), "b");
    EXPECT_STREQ(nextElem->Attribute("id"), "2");
}

TEST_F(XMLConstHandleNextSiblingElementTest_141, WithName_NoMatchingSibling_ReturnsNullHandle_141) {
    const XMLElement* root = ParseAndGetRoot("<root><a/><b/><c/></root>");
    const XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    const XMLConstHandle h(a);
    const XMLConstHandle nextMissing = h.NextSiblingElement("does_not_exist");

    EXPECT_EQ(nextMissing.ToNode(), nullptr);
    EXPECT_EQ(nextMissing.ToElement(), nullptr);
}

TEST_F(XMLConstHandleNextSiblingElementTest_141, NoNextSiblingElement_ReturnsNullHandle_141) {
    const XMLElement* root = ParseAndGetRoot("<root><a/><b/><c/></root>");
    const XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(c, nullptr);

    const XMLConstHandle h(c);
    const XMLConstHandle next = h.NextSiblingElement();

    EXPECT_EQ(next.ToNode(), nullptr);
    EXPECT_EQ(next.ToElement(), nullptr);
}

TEST_F(XMLConstHandleNextSiblingElementTest_141, NullHandle_ReturnsNullHandleAndDoesNotCrash_141) {
    const XMLConstHandle nullHandle(static_cast<const XMLNode*>(nullptr));

    const XMLConstHandle next = nullHandle.NextSiblingElement();
    EXPECT_EQ(next.ToNode(), nullptr);
    EXPECT_EQ(next.ToElement(), nullptr);

    const XMLConstHandle nextNamed = nullHandle.NextSiblingElement("b");
    EXPECT_EQ(nextNamed.ToNode(), nullptr);
    EXPECT_EQ(nextNamed.ToElement(), nullptr);
}

TEST_F(XMLConstHandleNextSiblingElementTest_141, ChainedCalls_CanTraverseAcrossMultipleSiblings_141) {
    const XMLElement* root = ParseAndGetRoot("<root><a/><b/><c/></root>");
    const XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    const XMLConstHandle h(a);
    const XMLConstHandle b = h.NextSiblingElement();
    ASSERT_NE(b.ToElement(), nullptr);
    EXPECT_STREQ(b.ToElement()->Name(), "b");

    const XMLConstHandle c = b.NextSiblingElement();
    ASSERT_NE(c.ToElement(), nullptr);
    EXPECT_STREQ(c.ToElement()->Name(), "c");

    const XMLConstHandle end = c.NextSiblingElement();
    EXPECT_EQ(end.ToNode(), nullptr);
}
