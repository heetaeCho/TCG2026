// File: ./TestProjects/tinyxml2/tests/xmlunknown_shallowclone_test_206.cpp

#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLUnknownShallowCloneTest_206 : public ::testing::Test {
protected:
    XMLDocument docA;
    XMLDocument docB;

    XMLUnknownShallowCloneTest_206() : docA(true, COLLAPSE_WHITESPACE), docB(true, COLLAPSE_WHITESPACE) {}
};

TEST_F(XMLUnknownShallowCloneTest_206, CloneWithNullDocumentUsesOriginalDocument_206) {
    XMLUnknown* original = docA.NewUnknown("<?target data?>");
    ASSERT_NE(original, nullptr);

    XMLNode* clonedNode = original->ShallowClone(nullptr);
    ASSERT_NE(clonedNode, nullptr);
    EXPECT_NE(clonedNode, original);

    // Should be an unknown node.
    XMLUnknown* clonedUnknown = clonedNode->ToUnknown();
    ASSERT_NE(clonedUnknown, nullptr);

    // Should belong to the same document when nullptr is passed.
    EXPECT_EQ(clonedNode->GetDocument(), original->GetDocument());

    // Should preserve the value.
    ASSERT_NE(original->Value(), nullptr);
    ASSERT_NE(clonedNode->Value(), nullptr);
    EXPECT_STREQ(clonedNode->Value(), original->Value());
}

TEST_F(XMLUnknownShallowCloneTest_206, CloneWithExplicitDocumentUsesThatDocument_206) {
    XMLUnknown* original = docA.NewUnknown("<!SOME_UNKNOWN_DECL>");
    ASSERT_NE(original, nullptr);

    XMLNode* clonedNode = original->ShallowClone(&docB);
    ASSERT_NE(clonedNode, nullptr);
    EXPECT_NE(clonedNode, original);

    // Should be an unknown node.
    XMLUnknown* clonedUnknown = clonedNode->ToUnknown();
    ASSERT_NE(clonedUnknown, nullptr);

    // Should belong to the provided document.
    EXPECT_EQ(clonedNode->GetDocument(), &docB);
    EXPECT_NE(clonedNode->GetDocument(), original->GetDocument());

    // Should preserve the value.
    ASSERT_NE(original->Value(), nullptr);
    ASSERT_NE(clonedNode->Value(), nullptr);
    EXPECT_STREQ(clonedNode->Value(), original->Value());
}

TEST_F(XMLUnknownShallowCloneTest_206, ClonePreservesEmptyValue_206) {
    XMLUnknown* original = docA.NewUnknown("");
    ASSERT_NE(original, nullptr);

    XMLNode* clonedNodeA = original->ShallowClone(nullptr);
    ASSERT_NE(clonedNodeA, nullptr);
    ASSERT_NE(clonedNodeA->ToUnknown(), nullptr);
    ASSERT_NE(clonedNodeA->Value(), nullptr);
    EXPECT_STREQ(clonedNodeA->Value(), "");

    XMLNode* clonedNodeB = original->ShallowClone(&docB);
    ASSERT_NE(clonedNodeB, nullptr);
    ASSERT_NE(clonedNodeB->ToUnknown(), nullptr);
    ASSERT_NE(clonedNodeB->Value(), nullptr);
    EXPECT_STREQ(clonedNodeB->Value(), "");
    EXPECT_EQ(clonedNodeB->GetDocument(), &docB);
}

TEST_F(XMLUnknownShallowCloneTest_206, CloneDoesNotModifyOriginalValue_206) {
    XMLUnknown* original = docA.NewUnknown("original-value");
    ASSERT_NE(original, nullptr);

    const char* before = original->Value();
    ASSERT_NE(before, nullptr);
    EXPECT_STREQ(before, "original-value");

    XMLNode* clonedNode = original->ShallowClone(&docB);
    ASSERT_NE(clonedNode, nullptr);
    ASSERT_NE(clonedNode->ToUnknown(), nullptr);

    // Verify original unchanged (observable via public API).
    const char* after = original->Value();
    ASSERT_NE(after, nullptr);
    EXPECT_STREQ(after, "original-value");

    // And clone still matches.
    ASSERT_NE(clonedNode->Value(), nullptr);
    EXPECT_STREQ(clonedNode->Value(), "original-value");
}
