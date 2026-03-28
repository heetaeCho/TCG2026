// File: TestProjects/tinyxml2/tests/xml_document_newtext_test_274.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

namespace tinyxml2 {

class XMLDocumentNewTextTest_274 : public ::testing::Test {
protected:
    // Use a commonly-available constructor signature from the provided header.
    XMLDocument doc_{ /*processEntities=*/true, /*whitespaceMode=*/PRESERVE_WHITESPACE };
};

TEST_F(XMLDocumentNewTextTest_274, NewTextReturnsNonNullPointer_274) {
    XMLText* t = doc_.NewText("hello");
    ASSERT_NE(t, nullptr);
}

TEST_F(XMLDocumentNewTextTest_274, NewTextSetsValueToGivenString_274) {
    const char* input = "hello world";
    XMLText* t = doc_.NewText(input);
    ASSERT_NE(t, nullptr);

    // Observable behavior via public API: Value() should reflect the provided text.
    ASSERT_NE(t->Value(), nullptr);
    EXPECT_STREQ(t->Value(), input);
}

TEST_F(XMLDocumentNewTextTest_274, NewTextReturnedNodeIsTextAndHasDocument_274) {
    XMLText* t = doc_.NewText("x");
    ASSERT_NE(t, nullptr);

    // Observable type behavior via public RTTI-style helpers.
    EXPECT_NE(t->ToText(), nullptr);
    EXPECT_EQ(t->ToDocument(), nullptr);

    // Must be associated with the creating document.
    ASSERT_NE(t->GetDocument(), nullptr);
    EXPECT_EQ(t->GetDocument(), &doc_);
}

TEST_F(XMLDocumentNewTextTest_274, NewTextIsInitiallyUnlinkedInTree_274) {
    XMLText* t = doc_.NewText("unlinked");
    ASSERT_NE(t, nullptr);

    // As a newly created node, it should not be attached anywhere yet.
    EXPECT_EQ(t->Parent(), nullptr);
    EXPECT_EQ(t->PreviousSibling(), nullptr);
    EXPECT_EQ(t->NextSibling(), nullptr);
    EXPECT_TRUE(t->NoChildren());
    EXPECT_EQ(t->FirstChild(), nullptr);
    EXPECT_EQ(t->LastChild(), nullptr);
}

TEST_F(XMLDocumentNewTextTest_274, MultipleNewTextCallsReturnDistinctNodes_274) {
    XMLText* a = doc_.NewText("a");
    XMLText* b = doc_.NewText("b");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);

    EXPECT_NE(a, b);
    ASSERT_NE(a->Value(), nullptr);
    ASSERT_NE(b->Value(), nullptr);
    EXPECT_STREQ(a->Value(), "a");
    EXPECT_STREQ(b->Value(), "b");
}

TEST_F(XMLDocumentNewTextTest_274, NewTextAcceptsEmptyString_274) {
    XMLText* t = doc_.NewText("");
    ASSERT_NE(t, nullptr);

    // Should be safe and observable; allow either nullptr or "" would be too loose here,
    // but empty-string input should reasonably round-trip.
    ASSERT_NE(t->Value(), nullptr);
    EXPECT_STREQ(t->Value(), "");
}

TEST_F(XMLDocumentNewTextTest_274, NewTextWithNullptrDoesNotCrashAndYieldsSafeValue_274) {
    // Error/exceptional-ish input: nullptr text.
    // We only assert observable safety without assuming internal policy.
    XMLText* t = doc_.NewText(nullptr);
    ASSERT_NE(t, nullptr);

    const char* v = t->Value();
    // Accept either nullptr or an empty string as "safe" observable outcomes.
    if (v) {
        EXPECT_STREQ(v, "");
    } else {
        SUCCEED();
    }

    // Still should be a well-formed, unlinked node.
    EXPECT_NE(t->ToText(), nullptr);
    EXPECT_EQ(t->Parent(), nullptr);
}

TEST_F(XMLDocumentNewTextTest_274, NewTextHandlesLongString_274) {
    std::string longStr(4096, 'x');
    XMLText* t = doc_.NewText(longStr.c_str());
    ASSERT_NE(t, nullptr);

    ASSERT_NE(t->Value(), nullptr);
    EXPECT_STREQ(t->Value(), longStr.c_str());
}

}  // namespace tinyxml2
