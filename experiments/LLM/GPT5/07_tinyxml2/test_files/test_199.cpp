// File: test_xmlcomment_shallowequal_199.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLCommentShallowEqualTest_199 : public ::testing::Test {
protected:
    // Parses XML into `doc` and returns the first comment node found as an XMLNode*.
    // (We intentionally interact only via the public interface.)
    static const XMLNode* FirstCommentNodeOrNull(XMLDocument& doc, const char* xml) {
        ASSERT_NE(xml, nullptr);
        const XMLError err = doc.Parse(xml);
        ASSERT_EQ(err, XML_SUCCESS);

        const XMLNode* n = doc.FirstChild();
        while (n && !n->ToComment()) {
            n = n->NextSibling();
        }
        return n;
    }
};

}  // namespace

TEST_F(XMLCommentShallowEqualTest_199, SameValueReturnsTrue_199) {
    XMLDocument docA;
    XMLDocument docB;

    const XMLNode* a = FirstCommentNodeOrNull(docA, "<!--hello-->");
    const XMLNode* b = FirstCommentNodeOrNull(docB, "<!--hello-->");

    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);

    const XMLComment* commentA = a->ToComment();
    ASSERT_NE(commentA, nullptr);

    EXPECT_TRUE(commentA->ShallowEqual(b));
}

TEST_F(XMLCommentShallowEqualTest_199, DifferentValueReturnsFalse_199) {
    XMLDocument docA;
    XMLDocument docB;

    const XMLNode* a = FirstCommentNodeOrNull(docA, "<!--hello-->");
    const XMLNode* b = FirstCommentNodeOrNull(docB, "<!--world-->");

    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);

    const XMLComment* commentA = a->ToComment();
    ASSERT_NE(commentA, nullptr);

    EXPECT_FALSE(commentA->ShallowEqual(b));
}

TEST_F(XMLCommentShallowEqualTest_199, CompareWithNonCommentNodeReturnsFalse_199) {
    XMLDocument docA;
    XMLDocument docB;

    const XMLNode* a = FirstCommentNodeOrNull(docA, "<!--hello-->");
    ASSERT_NE(a, nullptr);

    // Non-comment root element node.
    ASSERT_EQ(docB.Parse("<root/>"), XML_SUCCESS);
    const XMLNode* root = docB.FirstChild();
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(root->ToComment(), nullptr);

    const XMLComment* commentA = a->ToComment();
    ASSERT_NE(commentA, nullptr);

    EXPECT_FALSE(commentA->ShallowEqual(root));
}

TEST_F(XMLCommentShallowEqualTest_199, EmptyCommentValueEquality_199) {
    XMLDocument docA;
    XMLDocument docB;

    const XMLNode* a = FirstCommentNodeOrNull(docA, "<!---->");
    const XMLNode* b = FirstCommentNodeOrNull(docB, "<!---->");

    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);

    const XMLComment* commentA = a->ToComment();
    ASSERT_NE(commentA, nullptr);

    EXPECT_TRUE(commentA->ShallowEqual(b));
}

TEST_F(XMLCommentShallowEqualTest_199, PreservesWhitespaceDifferences_199) {
    XMLDocument docA;
    XMLDocument docB;

    const XMLNode* a = FirstCommentNodeOrNull(docA, "<!-- hello -->");
    const XMLNode* b = FirstCommentNodeOrNull(docB, "<!--hello-->");

    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);

    const XMLComment* commentA = a->ToComment();
    ASSERT_NE(commentA, nullptr);

    // Observable behavior: if comment values differ (including whitespace), ShallowEqual should be false.
    EXPECT_FALSE(commentA->ShallowEqual(b));
}

TEST_F(XMLCommentShallowEqualTest_199, VeryLongCommentValueEquality_199) {
    std::string payload(10'000, 'x');
    std::string xml = "<!--" + payload + "-->";

    XMLDocument docA;
    XMLDocument docB;

    const XMLNode* a = FirstCommentNodeOrNull(docA, xml.c_str());
    const XMLNode* b = FirstCommentNodeOrNull(docB, xml.c_str());

    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);

    const XMLComment* commentA = a->ToComment();
    ASSERT_NE(commentA, nullptr);

    EXPECT_TRUE(commentA->ShallowEqual(b));
}

TEST_F(XMLCommentShallowEqualTest_199, NullCompareTriggersAssertInDebug_199) {
#if !defined(NDEBUG)
    XMLDocument doc;
    const XMLNode* a = FirstCommentNodeOrNull(doc, "<!--hello-->");
    ASSERT_NE(a, nullptr);

    const XMLComment* commentA = a->ToComment();
    ASSERT_NE(commentA, nullptr);

    // XMLComment::ShallowEqual has a TIXMLASSERT(compare) precondition.
    ASSERT_DEATH({ (void)commentA->ShallowEqual(nullptr); }, "");
#else
    GTEST_SKIP() << "Death test requires assertions enabled (non-NDEBUG build).";
#endif
}
