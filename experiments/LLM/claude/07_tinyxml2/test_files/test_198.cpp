#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLCommentShallowCloneTest_198 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test that ShallowClone creates a new comment with the same value in the same document
TEST_F(XMLCommentShallowCloneTest_198, ShallowCloneWithNullDocUsesOwnDocument_198) {
    const char* xml = "<!-- Hello World -->";
    doc->Parse(xml);

    XMLNode* node = doc->FirstChild();
    ASSERT_NE(node, nullptr);

    XMLComment* comment = node->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLNode* cloned = comment->ShallowClone(nullptr);
    ASSERT_NE(cloned, nullptr);

    XMLComment* clonedComment = cloned->ToComment();
    ASSERT_NE(clonedComment, nullptr);

    // The cloned comment should have the same value
    EXPECT_STREQ(clonedComment->Value(), comment->Value());

    // Clean up - the cloned node is unlinked, need to delete it
    doc->DeleteNode(cloned);
}

// Test that ShallowClone creates a new comment in a different document
TEST_F(XMLCommentShallowCloneTest_198, ShallowCloneWithDifferentDocument_198) {
    const char* xml = "<!-- Test Comment -->";
    doc->Parse(xml);

    XMLNode* node = doc->FirstChild();
    ASSERT_NE(node, nullptr);

    XMLComment* comment = node->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLDocument otherDoc;
    XMLNode* cloned = comment->ShallowClone(&otherDoc);
    ASSERT_NE(cloned, nullptr);

    XMLComment* clonedComment = cloned->ToComment();
    ASSERT_NE(clonedComment, nullptr);

    // The cloned comment should have the same value
    EXPECT_STREQ(clonedComment->Value(), comment->Value());

    // The cloned node belongs to otherDoc
    EXPECT_EQ(clonedComment->GetDocument(), &otherDoc);

    otherDoc.DeleteNode(cloned);
}

// Test ShallowClone with an empty comment
TEST_F(XMLCommentShallowCloneTest_198, ShallowCloneEmptyComment_198) {
    const char* xml = "<!---->";
    doc->Parse(xml);

    XMLNode* node = doc->FirstChild();
    ASSERT_NE(node, nullptr);

    XMLComment* comment = node->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLNode* cloned = comment->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    XMLComment* clonedComment = cloned->ToComment();
    ASSERT_NE(clonedComment, nullptr);

    // Both should have the same (empty) value
    EXPECT_STREQ(clonedComment->Value(), comment->Value());

    doc->DeleteNode(cloned);
}

// Test that ShallowClone returns a distinct node (not the same pointer)
TEST_F(XMLCommentShallowCloneTest_198, ShallowCloneReturnsDifferentNode_198) {
    const char* xml = "<!-- Original Comment -->";
    doc->Parse(xml);

    XMLNode* node = doc->FirstChild();
    ASSERT_NE(node, nullptr);

    XMLComment* comment = node->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLNode* cloned = comment->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    // Cloned should be a different node
    EXPECT_NE(cloned, node);

    doc->DeleteNode(cloned);
}

// Test ShallowClone with a comment containing special characters
TEST_F(XMLCommentShallowCloneTest_198, ShallowCloneCommentWithSpecialChars_198) {
    const char* xml = "<!-- <special> &chars; \"quotes\" -->";
    doc->Parse(xml);

    XMLNode* node = doc->FirstChild();
    ASSERT_NE(node, nullptr);

    XMLComment* comment = node->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLNode* cloned = comment->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    XMLComment* clonedComment = cloned->ToComment();
    ASSERT_NE(clonedComment, nullptr);

    EXPECT_STREQ(clonedComment->Value(), comment->Value());

    doc->DeleteNode(cloned);
}

// Test ShallowClone preserves value but does not clone children (comments don't have children normally)
TEST_F(XMLCommentShallowCloneTest_198, ShallowCloneHasNoChildren_198) {
    const char* xml = "<!-- A comment -->";
    doc->Parse(xml);

    XMLNode* node = doc->FirstChild();
    ASSERT_NE(node, nullptr);

    XMLComment* comment = node->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLNode* cloned = comment->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    // A shallow clone of a comment should have no children
    EXPECT_TRUE(cloned->NoChildren());

    doc->DeleteNode(cloned);
}

// Test ShallowClone with a comment created via NewComment
TEST_F(XMLCommentShallowCloneTest_198, ShallowCloneFromNewComment_198) {
    XMLComment* comment = doc->NewComment("Programmatic comment");
    ASSERT_NE(comment, nullptr);
    doc->InsertEndChild(comment);

    XMLNode* cloned = comment->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    XMLComment* clonedComment = cloned->ToComment();
    ASSERT_NE(clonedComment, nullptr);

    EXPECT_STREQ(clonedComment->Value(), "Programmatic comment");

    doc->DeleteNode(cloned);
}

// Test that ShallowClone into a different document keeps the value intact
TEST_F(XMLCommentShallowCloneTest_198, ShallowCloneCrossDocumentPreservesValue_198) {
    XMLComment* comment = doc->NewComment("Cross document test");
    ASSERT_NE(comment, nullptr);
    doc->InsertEndChild(comment);

    XMLDocument targetDoc;
    XMLNode* cloned = comment->ShallowClone(&targetDoc);
    ASSERT_NE(cloned, nullptr);

    XMLComment* clonedComment = cloned->ToComment();
    ASSERT_NE(clonedComment, nullptr);

    EXPECT_STREQ(clonedComment->Value(), "Cross document test");
    EXPECT_EQ(clonedComment->GetDocument(), &targetDoc);

    targetDoc.DeleteNode(cloned);
}

// Test ShallowClone with a long comment string
TEST_F(XMLCommentShallowCloneTest_198, ShallowCloneLongComment_198) {
    std::string longComment(1000, 'A');
    XMLComment* comment = doc->NewComment(longComment.c_str());
    ASSERT_NE(comment, nullptr);
    doc->InsertEndChild(comment);

    XMLNode* cloned = comment->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    XMLComment* clonedComment = cloned->ToComment();
    ASSERT_NE(clonedComment, nullptr);

    EXPECT_STREQ(clonedComment->Value(), longComment.c_str());

    doc->DeleteNode(cloned);
}

// Test ShallowClone with comment inside an element
TEST_F(XMLCommentShallowCloneTest_198, ShallowCloneCommentInsideElement_198) {
    const char* xml = "<root><!-- inside comment --></root>";
    doc->Parse(xml);

    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLNode* child = root->FirstChild();
    ASSERT_NE(child, nullptr);

    XMLComment* comment = child->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLNode* cloned = comment->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    XMLComment* clonedComment = cloned->ToComment();
    ASSERT_NE(clonedComment, nullptr);

    EXPECT_STREQ(clonedComment->Value(), comment->Value());

    // The cloned node should not have a parent (it's unlinked)
    EXPECT_EQ(cloned->Parent(), nullptr);

    doc->DeleteNode(cloned);
}

// Test ShallowEqual between a comment and its shallow clone
TEST_F(XMLCommentShallowCloneTest_198, ShallowCloneIsShallowEqual_198) {
    const char* xml = "<!-- equality test -->";
    doc->Parse(xml);

    XMLNode* node = doc->FirstChild();
    ASSERT_NE(node, nullptr);

    XMLComment* comment = node->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLNode* cloned = comment->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    EXPECT_TRUE(comment->ShallowEqual(cloned));
    EXPECT_TRUE(cloned->ShallowEqual(comment));

    doc->DeleteNode(cloned);
}
