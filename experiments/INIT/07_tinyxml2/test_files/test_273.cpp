// TEST_ID: 273
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLDocumentNewCommentTest_273 : public ::testing::Test {
protected:
    // Use an explicit ctor because the provided header shows no default args.
    XMLDocumentNewCommentTest_273()
        : doc_(/*processEntities=*/true, /*whitespaceMode=*/PRESERVE_WHITESPACE) {}

    XMLDocument doc_;
};

TEST_F(XMLDocumentNewCommentTest_273, NewCommentCreatesNonNullComment_273) {
    XMLComment* comment = doc_.NewComment("hello");
    ASSERT_NE(comment, nullptr);

    // Basic type identity
    EXPECT_NE(comment->ToComment(), nullptr);
    EXPECT_EQ(comment->ToComment(), comment);

    // Value should reflect the input string.
    ASSERT_NE(comment->Value(), nullptr);
    EXPECT_STREQ(comment->Value(), "hello");

    // The node should belong to the document that created it.
    EXPECT_EQ(comment->GetDocument(), &doc_);
}

TEST_F(XMLDocumentNewCommentTest_273, NewCommentAcceptsEmptyString_273) {
    XMLComment* comment = doc_.NewComment("");
    ASSERT_NE(comment, nullptr);

    ASSERT_NE(comment->Value(), nullptr);
    EXPECT_STREQ(comment->Value(), "");
}

TEST_F(XMLDocumentNewCommentTest_273, NewCommentWithNullptrDoesNotCrashAndCreatesNode_273) {
    // Behavior for nullptr input is not specified; verify only observable safety + creation.
    XMLComment* comment = nullptr;
    ASSERT_NO_FATAL_FAILURE(comment = doc_.NewComment(nullptr));
    ASSERT_NE(comment, nullptr);

    // Value may be nullptr or an empty string depending on library behavior; accept either.
    const char* v = comment->Value();
    EXPECT_TRUE(v == nullptr || v[0] == '\0');
}

TEST_F(XMLDocumentNewCommentTest_273, NewCommentCreatesUnlinkedNodeWithNoChildren_273) {
    XMLComment* comment = doc_.NewComment("x");
    ASSERT_NE(comment, nullptr);

    // Newly created comment should not be linked into the tree unless user links it.
    EXPECT_EQ(comment->Parent(), nullptr);

    // Comments should have no children.
    EXPECT_TRUE(comment->NoChildren());
    EXPECT_EQ(comment->FirstChild(), nullptr);
    EXPECT_EQ(comment->LastChild(), nullptr);
}

TEST_F(XMLDocumentNewCommentTest_273, MultipleNewCommentCallsReturnDistinctNodes_273) {
    XMLComment* c1 = doc_.NewComment("one");
    XMLComment* c2 = doc_.NewComment("two");

    ASSERT_NE(c1, nullptr);
    ASSERT_NE(c2, nullptr);
    EXPECT_NE(c1, c2);

    ASSERT_NE(c1->Value(), nullptr);
    ASSERT_NE(c2->Value(), nullptr);
    EXPECT_STREQ(c1->Value(), "one");
    EXPECT_STREQ(c2->Value(), "two");
}

TEST_F(XMLDocumentNewCommentTest_273, DeleteNodeCanDeleteNewComment_273) {
    XMLComment* comment = doc_.NewComment("to-delete");
    ASSERT_NE(comment, nullptr);

    // Observable behavior: should be safe to delete a node created by the document.
    ASSERT_NO_FATAL_FAILURE(doc_.DeleteNode(comment));
}

}  // namespace
