// File: ./TestProjects/tinyxml2/xmlconsthandle_totext_test_144.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleToTextTest_144 : public ::testing::Test {
protected:
    XMLDocument doc_;

    const XMLElement* ParseAndGetRoot(const char* xml, const char* rootName = "root") {
        doc_.Clear();
        ASSERT_EQ(XML_SUCCESS, doc_.Parse(xml));
        const XMLElement* root = doc_.FirstChildElement(rootName);
        ASSERT_NE(nullptr, root);
        return root;
    }
};

TEST_F(XMLConstHandleToTextTest_144, ToTextReturnsNullptrWhenConstructedWithNullNode_144) {
    XMLConstHandle handle(nullptr);
    EXPECT_EQ(nullptr, handle.ToText());
}

TEST_F(XMLConstHandleToTextTest_144, ToTextReturnsNullptrWhenHandlePointsToElementNode_144) {
    const XMLElement* root = ParseAndGetRoot("<root>hi</root>");
    ASSERT_NE(nullptr, root);

    XMLConstHandle handle(root);
    EXPECT_EQ(nullptr, handle.ToText());
}

TEST_F(XMLConstHandleToTextTest_144, ToTextReturnsSamePointerAsNodeToTextWhenHandlePointsToTextNode_144) {
    const XMLElement* root = ParseAndGetRoot("<root>hi</root>");
    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(nullptr, firstChild);

    const XMLText* expected = firstChild->ToText();
    // If parsing produced a non-text first child for some reason, this test should not proceed.
    ASSERT_NE(nullptr, expected);

    XMLConstHandle handle(firstChild);
    EXPECT_EQ(expected, handle.ToText());
}

TEST_F(XMLConstHandleToTextTest_144, ToTextReturnsNullptrWhenNodeIsNonTextChildSuchAsElement_144) {
    const XMLElement* root = ParseAndGetRoot("<root><child/></root>");
    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(nullptr, firstChild);

    // First child should be an element node here; ToText() should therefore be nullptr.
    ASSERT_EQ(nullptr, firstChild->ToText());

    XMLConstHandle handle(firstChild);
    EXPECT_EQ(nullptr, handle.ToText());
}

TEST_F(XMLConstHandleToTextTest_144, ToTextIsConsistentAcrossCopiesAndAssignments_144) {
    const XMLElement* root = ParseAndGetRoot("<root>hi</root>");
    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(nullptr, firstChild);

    const XMLText* expected = firstChild->ToText();
    ASSERT_NE(nullptr, expected);

    XMLConstHandle original(firstChild);

    // Copy construction
    XMLConstHandle copy(original);
    EXPECT_EQ(expected, copy.ToText());

    // Assignment
    XMLConstHandle assigned(nullptr);
    assigned = original;
    EXPECT_EQ(expected, assigned.ToText());
}
