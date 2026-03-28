// File: ./TestProjects/tinyxml2/xml_declaration_shallow_equal_test_203.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLDeclarationShallowEqualTest_203 : public ::testing::Test {
protected:
    static XMLDeclaration* ParseFirstDeclaration(XMLDocument& doc, const char* xml) {
        ASSERT_NE(xml, nullptr);

        const XMLError err = doc.Parse(xml);
        ASSERT_EQ(err, XML_SUCCESS) << "XMLDocument::Parse failed with error=" << err;

        // In tinyxml2, a declaration (if present) is typically the first child.
        XMLNode* first = doc.FirstChild();
        ASSERT_NE(first, nullptr) << "Expected at least one top-level node after Parse.";
        XMLDeclaration* decl = first->ToDeclaration();
        ASSERT_NE(decl, nullptr) << "Expected first child to be an XMLDeclaration.";
        return decl;
    }

    static XMLElement* ParseRootElement(XMLDocument& doc, const char* xml) {
        ASSERT_NE(xml, nullptr);

        const XMLError err = doc.Parse(xml);
        ASSERT_EQ(err, XML_SUCCESS) << "XMLDocument::Parse failed with error=" << err;

        XMLElement* root = doc.RootElement();
        ASSERT_NE(root, nullptr) << "Expected a root element.";
        return root;
    }
};

}  // namespace

TEST_F(XMLDeclarationShallowEqualTest_203, ReturnsTrueWhenComparingSameDeclarationValue_203) {
    XMLDocument d1;
    XMLDocument d2;

    XMLDeclaration* decl1 = ParseFirstDeclaration(d1, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<r/>");
    XMLDeclaration* decl2 = ParseFirstDeclaration(d2, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<r/>");

    // Observable behavior: shallow-equal should succeed when declaration values match.
    EXPECT_TRUE(decl1->ShallowEqual(decl2));
    EXPECT_TRUE(decl2->ShallowEqual(decl1));
}

TEST_F(XMLDeclarationShallowEqualTest_203, ReturnsFalseWhenDeclarationValuesDiffer_203) {
    XMLDocument d1;
    XMLDocument d2;

    XMLDeclaration* decl1 = ParseFirstDeclaration(d1, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<r/>");
    XMLDeclaration* decl2 = ParseFirstDeclaration(d2, "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n<r/>");

    // Observable behavior: different declaration value => not shallow-equal.
    EXPECT_FALSE(decl1->ShallowEqual(decl2));
    EXPECT_FALSE(decl2->ShallowEqual(decl1));
}

TEST_F(XMLDeclarationShallowEqualTest_203, ReturnsFalseWhenCompareIsNotADeclaration_203) {
    XMLDocument docWithDecl;
    XMLDocument docWithElemOnly;

    XMLDeclaration* decl = ParseFirstDeclaration(docWithDecl, "<?xml version=\"1.0\"?>\n<r/>");
    XMLElement* root = ParseRootElement(docWithElemOnly, "<r/>");

    // compare->ToDeclaration() should be null for elements, so ShallowEqual should return false.
    EXPECT_FALSE(decl->ShallowEqual(root));
}

TEST_F(XMLDeclarationShallowEqualTest_203, ReturnsFalseWhenCompareIsNullDeclarationPointerButNonNullNode_203) {
    XMLDocument docWithDecl;
    XMLDocument docWithText;

    XMLDeclaration* decl = ParseFirstDeclaration(docWithDecl, "<?xml version=\"1.0\"?>\n<r/>");

    // Build a doc with a text node as the first child of the root, then compare against that text node.
    ASSERT_EQ(docWithText.Parse("<r>hello</r>"), XML_SUCCESS);
    XMLElement* root = docWithText.RootElement();
    ASSERT_NE(root, nullptr);
    XMLNode* textNode = root->FirstChild();
    ASSERT_NE(textNode, nullptr);
    ASSERT_EQ(textNode->ToDeclaration(), nullptr) << "Sanity: text node must not be a declaration.";

    EXPECT_FALSE(decl->ShallowEqual(textNode));
}

#if defined(GTEST_HAS_DEATH_TEST) && GTEST_HAS_DEATH_TEST
// ShallowEqual contains TIXMLASSERT(compare). In common builds this aborts on nullptr.
// This test is only reliable when assertions are enabled (typically debug / !NDEBUG).
#ifndef NDEBUG
TEST_F(XMLDeclarationShallowEqualTest_203, DeathWhenCompareIsNull_203) {
    XMLDocument doc;
    XMLDeclaration* decl = ParseFirstDeclaration(doc, "<?xml version=\"1.0\"?>\n<r/>");

    // We don't depend on the exact assert message; just that the process dies.
    EXPECT_DEATH(
        {
            (void)decl->ShallowEqual(nullptr);
        },
        "");
}
#endif  // !NDEBUG
#endif  // death tests
