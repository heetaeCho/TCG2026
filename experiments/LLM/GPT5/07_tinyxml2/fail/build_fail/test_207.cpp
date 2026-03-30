// File: ./TestProjects/tinyxml2/tests/xmlunknown_shallowequal_test_207.cpp

#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLUnknownShallowEqualTest_207 : public ::testing::Test {
protected:
    // Parse a document that should produce an XMLUnknown as the first child:
    // e.g. a DOCTYPE becomes XMLUnknown in tinyxml2.
    static XMLUnknown* ParseFirstUnknownOrFail(XMLDocument& doc, const char* xml) {
        ASSERT_NE(xml, nullptr);

        const XMLError err = doc.Parse(xml);
        ASSERT_EQ(err, XML_SUCCESS) << "Parse failed with error: " << err;

        XMLNode* first = doc.FirstChild();
        ASSERT_NE(first, nullptr) << "Expected a first child node.";

        XMLUnknown* unk = first->ToUnknown();
        ASSERT_NE(unk, nullptr) << "Expected first child to be XMLUnknown.";
        return unk;
    }

    static XMLComment* ParseFirstCommentOrFail(XMLDocument& doc, const char* xml) {
        ASSERT_NE(xml, nullptr);

        const XMLError err = doc.Parse(xml);
        ASSERT_EQ(err, XML_SUCCESS) << "Parse failed with error: " << err;

        XMLNode* first = doc.FirstChild();
        ASSERT_NE(first, nullptr) << "Expected a first child node.";

        XMLComment* c = first->ToComment();
        ASSERT_NE(c, nullptr) << "Expected first child to be XMLComment.";
        return c;
    }
};

TEST_F(XMLUnknownShallowEqualTest_207, SameUnknownValue_ReturnsTrue_207) {
    XMLDocument d1;
    XMLDocument d2;

    XMLUnknown* u1 = ParseFirstUnknownOrFail(d1, "<!DOCTYPE foo>");
    XMLUnknown* u2 = ParseFirstUnknownOrFail(d2, "<!DOCTYPE foo>");

    EXPECT_TRUE(u1->ShallowEqual(u2));
    EXPECT_TRUE(u2->ShallowEqual(u1));
}

TEST_F(XMLUnknownShallowEqualTest_207, DifferentUnknownValue_ReturnsFalse_207) {
    XMLDocument d1;
    XMLDocument d2;

    XMLUnknown* u1 = ParseFirstUnknownOrFail(d1, "<!DOCTYPE foo>");
    XMLUnknown* u2 = ParseFirstUnknownOrFail(d2, "<!DOCTYPE bar>");

    EXPECT_FALSE(u1->ShallowEqual(u2));
    EXPECT_FALSE(u2->ShallowEqual(u1));
}

TEST_F(XMLUnknownShallowEqualTest_207, CompareIsNotUnknown_ReturnsFalse_207) {
    XMLDocument dUnknown;
    XMLDocument dComment;

    XMLUnknown* unk = ParseFirstUnknownOrFail(dUnknown, "<!DOCTYPE foo>");
    XMLComment* com = ParseFirstCommentOrFail(dComment, "<!-- hello -->");

    // Observable behavior: ShallowEqual should be false when compare isn't an XMLUnknown.
    EXPECT_FALSE(unk->ShallowEqual(com));
}

TEST_F(XMLUnknownShallowEqualTest_207, SameNodeComparedWithItself_ReturnsTrue_207) {
    XMLDocument doc;
    XMLUnknown* unk = ParseFirstUnknownOrFail(doc, "<!DOCTYPE foo>");

    EXPECT_TRUE(unk->ShallowEqual(unk));
}

TEST_F(XMLUnknownShallowEqualTest_207, AfterChangingValue_EqualityReflectsNewValue_207) {
    XMLDocument d1;
    XMLDocument d2;

    XMLUnknown* u1 = ParseFirstUnknownOrFail(d1, "<!DOCTYPE foo>");
    XMLUnknown* u2 = ParseFirstUnknownOrFail(d2, "<!DOCTYPE foo>");

    ASSERT_TRUE(u1->ShallowEqual(u2));

    // Change one node's value through the public interface on XMLNode.
    u2->SetValue("something else", /*staticMem=*/true);

    EXPECT_FALSE(u1->ShallowEqual(u2));
    EXPECT_FALSE(u2->ShallowEqual(u1));

    // Make them match again.
    u1->SetValue("something else", /*staticMem=*/true);
    EXPECT_TRUE(u1->ShallowEqual(u2));
}

#if !defined(NDEBUG)
// TIXMLASSERT(compare) is expected to fire in debug builds when compare == nullptr.
// In release builds it may be compiled out, so we only check this behavior in debug.
TEST_F(XMLUnknownShallowEqualTest_207, NullCompare_TriggersAssertDeath_207) {
    XMLDocument doc;
    XMLUnknown* unk = ParseFirstUnknownOrFail(doc, "<!DOCTYPE foo>");

    ASSERT_DEATH(
        {
            (void)unk->ShallowEqual(nullptr);
        },
        ".*");
}
#endif

}  // namespace
