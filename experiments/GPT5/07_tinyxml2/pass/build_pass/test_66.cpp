// File: ./TestProjects/tinyxml2/tests/test_xmlcomment_tocomment_66.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLCommentToCommentTest_66 : public ::testing::Test {
protected:
    XMLDocument doc;
};

TEST_F(XMLCommentToCommentTest_66, ToCommentReturnsSelf_66) {
    XMLComment* comment = doc.NewComment("hello");
    ASSERT_NE(comment, nullptr);

    XMLComment* asComment = comment->ToComment();
    EXPECT_NE(asComment, nullptr);
    EXPECT_EQ(asComment, comment);
}

TEST_F(XMLCommentToCommentTest_66, ToCommentViaXMLNodePointerReturnsSame_66) {
    XMLComment* comment = doc.NewComment("world");
    ASSERT_NE(comment, nullptr);

    XMLNode* node = comment;
    ASSERT_NE(node, nullptr);

    XMLComment* asComment = node->ToComment();
    EXPECT_NE(asComment, nullptr);
    EXPECT_EQ(asComment, comment);
}

TEST_F(XMLCommentToCommentTest_66, ToCommentMultipleCallsAreStable_66) {
    XMLComment* comment = doc.NewComment("repeat");
    ASSERT_NE(comment, nullptr);

    XMLComment* c1 = comment->ToComment();
    XMLComment* c2 = comment->ToComment();
    XMLComment* c3 = comment->ToComment();

    EXPECT_EQ(c1, comment);
    EXPECT_EQ(c2, comment);
    EXPECT_EQ(c3, comment);
}

TEST_F(XMLCommentToCommentTest_66, ToCommentStillReturnsSelfAfterInsertionIntoDocument_66) {
    XMLComment* comment = doc.NewComment("insert");
    ASSERT_NE(comment, nullptr);

    // Insert into the document tree (observable external operation).
    XMLNode* inserted = doc.InsertEndChild(comment);
    ASSERT_EQ(inserted, comment);

    XMLComment* asComment = comment->ToComment();
    EXPECT_NE(asComment, nullptr);
    EXPECT_EQ(asComment, comment);
}

TEST_F(XMLCommentToCommentTest_66, NonCommentNodeToCommentReturnsNull_66) {
    XMLElement* elem = doc.NewElement("root");
    ASSERT_NE(elem, nullptr);

    XMLNode* node = elem;
    ASSERT_NE(node, nullptr);

    // For a non-comment node, ToComment() should not report a comment.
    EXPECT_EQ(node->ToComment(), nullptr);
}
