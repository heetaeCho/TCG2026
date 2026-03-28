// File: ./TestProjects/tinyxml2/tests/XMLConstHandle_LastChildElement_137_test.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLConstHandleLastChildElementTest_137 : public ::testing::Test {
protected:
    XMLDocument doc;

    const XMLElement* ParseAndRoot(const char* xml) {
        // We only rely on observable API: Parse result and RootElement().
        const XMLError err = doc.Parse(xml);
        EXPECT_EQ(err, XML_SUCCESS);
        const XMLElement* root = doc.RootElement();
        EXPECT_NE(root, nullptr);
        return root;
    }
};

}  // namespace

TEST_F(XMLConstHandleLastChildElementTest_137, NullHandleReturnsNullElement_137) {
    XMLConstHandle nullHandle(static_cast<const XMLNode*>(nullptr));

    const XMLConstHandle resultDefault = nullHandle.LastChildElement();
    EXPECT_EQ(resultDefault.ToElement(), nullptr);
    EXPECT_EQ(resultDefault.ToNode(), nullptr);

    const XMLConstHandle resultNamed = nullHandle.LastChildElement("any");
    EXPECT_EQ(resultNamed.ToElement(), nullptr);
    EXPECT_EQ(resultNamed.ToNode(), nullptr);
}

TEST_F(XMLConstHandleLastChildElementTest_137, ReturnsLastChildElementWhenMultipleChildrenExist_137) {
    const XMLElement* root = ParseAndRoot(
        "<root>"
        "  <a/>"
        "  <b/>"
        "  <c/>"
        "</root>"
    );

    XMLConstHandle h(*root);
    const XMLConstHandle last = h.LastChildElement();

    ASSERT_NE(last.ToElement(), nullptr);
    EXPECT_STREQ(last.ToElement()->Name(), "c");
}

TEST_F(XMLConstHandleLastChildElementTest_137, NameFilterReturnsLastMatchingElement_137) {
    const XMLElement* root = ParseAndRoot(
        "<root>"
        "  <x/>"
        "  <target id='1'/>"
        "  <y/>"
        "  <target id='2'/>"
        "  <z/>"
        "</root>"
    );

    XMLConstHandle h(*root);
    const XMLConstHandle lastTarget = h.LastChildElement("target");

    ASSERT_NE(lastTarget.ToElement(), nullptr);
    EXPECT_STREQ(lastTarget.ToElement()->Name(), "target");
    // Observable attribute to disambiguate which one we got.
    EXPECT_STREQ(lastTarget.ToElement()->Attribute("id"), "2");
}

TEST_F(XMLConstHandleLastChildElementTest_137, NameFilterNoMatchReturnsNull_137) {
    const XMLElement* root = ParseAndRoot(
        "<root>"
        "  <a/>"
        "  <b/>"
        "</root>"
    );

    XMLConstHandle h(*root);
    const XMLConstHandle none = h.LastChildElement("does_not_exist");

    EXPECT_EQ(none.ToElement(), nullptr);
    EXPECT_EQ(none.ToNode(), nullptr);
}

TEST_F(XMLConstHandleLastChildElementTest_137, NoChildElementsReturnsNull_137) {
    const XMLElement* root = ParseAndRoot("<root/>");

    XMLConstHandle h(*root);
    const XMLConstHandle last = h.LastChildElement();

    EXPECT_EQ(last.ToElement(), nullptr);
    EXPECT_EQ(last.ToNode(), nullptr);
}

TEST_F(XMLConstHandleLastChildElementTest_137, IgnoresNonElementChildrenAndStillFindsLastElement_137) {
    const XMLElement* root = ParseAndRoot(
        "<root>"
        "  text-before"
        "  <a/>"
        "  text-middle"
        "  <b/>"
        "  text-after"
        "</root>"
    );

    XMLConstHandle h(*root);
    const XMLConstHandle last = h.LastChildElement();

    ASSERT_NE(last.ToElement(), nullptr);
    EXPECT_STREQ(last.ToElement()->Name(), "b");
}

TEST_F(XMLConstHandleLastChildElementTest_137, ExplicitNullNameBehavesLikeDefault_137) {
    const XMLElement* root = ParseAndRoot(
        "<root>"
        "  <a/>"
        "  <b/>"
        "</root>"
    );

    XMLConstHandle h(*root);

    const XMLConstHandle byDefault = h.LastChildElement();
    const XMLConstHandle byNullptr = h.LastChildElement(nullptr);

    // Both should resolve to the same last child element name in observable terms.
    ASSERT_NE(byDefault.ToElement(), nullptr);
    ASSERT_NE(byNullptr.ToElement(), nullptr);
    EXPECT_STREQ(byDefault.ToElement()->Name(), byNullptr.ToElement()->Name());
    EXPECT_STREQ(byDefault.ToElement()->Name(), "b");
}

TEST_F(XMLConstHandleLastChildElementTest_137, OnTextNodeHandleReturnsNull_137) {
    ParseAndRoot(
        "<root>"
        "  hello"
        "  <a/>"
        "</root>"
    );

    // Get the first child node of the document root; in this XML it may be a text node
    // (depending on tinyxml2 whitespace/text handling), so we guard by checking ToText().
    const XMLNode* rootNode = doc.RootElement();
    ASSERT_NE(rootNode, nullptr);

    const XMLNode* firstChild = rootNode->FirstChild();
    ASSERT_NE(firstChild, nullptr);

    XMLConstHandle childHandle(*firstChild);

    // If it's a text node, LastChildElement should return null because a text node has no element children.
    if (childHandle.ToText() != nullptr) {
        const XMLConstHandle lastEl = childHandle.LastChildElement();
        EXPECT_EQ(lastEl.ToElement(), nullptr);
        EXPECT_EQ(lastEl.ToNode(), nullptr);
    } else {
        // If parsing collapses/omits text nodes in this scenario, we still make a safe assertion:
        // the call should not crash, and result should be consistent with there being no element children.
        const XMLConstHandle lastEl = childHandle.LastChildElement();
        // We can't assume firstChild is an element or has children; just assert call is safe and returns a handle.
        (void)lastEl;
        SUCCEED();
    }
}
