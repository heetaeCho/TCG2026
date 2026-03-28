#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementInsertNewCommentTest_260 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* root;

    void SetUp() override {
        doc.Parse("<root></root>");
        root = doc.RootElement();
        ASSERT_NE(root, nullptr);
    }
};

TEST_F(XMLElementInsertNewCommentTest_260, InsertNewCommentReturnsNonNull_260) {
    XMLComment* comment = root->InsertNewComment("This is a comment");
    ASSERT_NE(comment, nullptr);
}

TEST_F(XMLElementInsertNewCommentTest_260, InsertNewCommentValueIsCorrect_260) {
    XMLComment* comment = root->InsertNewComment("Hello World");
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "Hello World");
}

TEST_F(XMLElementInsertNewCommentTest_260, InsertNewCommentIsChildOfElement_260) {
    XMLComment* comment = root->InsertNewComment("child comment");
    ASSERT_NE(comment, nullptr);
    
    const XMLNode* lastChild = root->LastChild();
    ASSERT_NE(lastChild, nullptr);
    EXPECT_EQ(lastChild->ToComment(), comment);
}

TEST_F(XMLElementInsertNewCommentTest_260, InsertNewCommentAppendsAtEnd_260) {
    root->InsertNewChildElement("child1");
    XMLComment* comment = root->InsertNewComment("after child1");
    ASSERT_NE(comment, nullptr);
    
    const XMLNode* lastChild = root->LastChild();
    ASSERT_NE(lastChild, nullptr);
    EXPECT_EQ(lastChild->ToComment(), comment);
}

TEST_F(XMLElementInsertNewCommentTest_260, InsertMultipleComments_260) {
    XMLComment* c1 = root->InsertNewComment("first");
    XMLComment* c2 = root->InsertNewComment("second");
    XMLComment* c3 = root->InsertNewComment("third");

    ASSERT_NE(c1, nullptr);
    ASSERT_NE(c2, nullptr);
    ASSERT_NE(c3, nullptr);

    EXPECT_STREQ(c1->Value(), "first");
    EXPECT_STREQ(c2->Value(), "second");
    EXPECT_STREQ(c3->Value(), "third");

    // They should be in order: first, second, third
    const XMLNode* node = root->FirstChild();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->ToComment(), c1);

    node = node->NextSibling();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->ToComment(), c2);

    node = node->NextSibling();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->ToComment(), c3);
}

TEST_F(XMLElementInsertNewCommentTest_260, InsertNewCommentEmptyString_260) {
    XMLComment* comment = root->InsertNewComment("");
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "");
}

TEST_F(XMLElementInsertNewCommentTest_260, InsertNewCommentWithSpecialCharacters_260) {
    XMLComment* comment = root->InsertNewComment("Special chars: <>&\"'");
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "Special chars: <>&\"'");
}

TEST_F(XMLElementInsertNewCommentTest_260, InsertNewCommentParentIsCorrect_260) {
    XMLComment* comment = root->InsertNewComment("check parent");
    ASSERT_NE(comment, nullptr);
    EXPECT_EQ(comment->Parent(), root);
}

TEST_F(XMLElementInsertNewCommentTest_260, InsertNewCommentBelongsToSameDocument_260) {
    XMLComment* comment = root->InsertNewComment("doc check");
    ASSERT_NE(comment, nullptr);
    EXPECT_EQ(comment->GetDocument(), &doc);
}

TEST_F(XMLElementInsertNewCommentTest_260, InsertNewCommentIncrementsChildCount_260) {
    EXPECT_EQ(root->ChildElementCount(), 0);
    EXPECT_TRUE(root->NoChildren());

    root->InsertNewComment("a comment");
    // ChildElementCount counts elements, not comments; but NoChildren should be false
    EXPECT_FALSE(root->NoChildren());
}

TEST_F(XMLElementInsertNewCommentTest_260, InsertNewCommentToCommentReturnsValidPointer_260) {
    XMLComment* comment = root->InsertNewComment("to comment test");
    ASSERT_NE(comment, nullptr);
    
    XMLComment* asComment = comment->ToComment();
    ASSERT_NE(asComment, nullptr);
    EXPECT_EQ(asComment, comment);
}

TEST_F(XMLElementInsertNewCommentTest_260, InsertNewCommentIsNotElement_260) {
    XMLComment* comment = root->InsertNewComment("not element");
    ASSERT_NE(comment, nullptr);
    EXPECT_EQ(comment->ToElement(), nullptr);
}

TEST_F(XMLElementInsertNewCommentTest_260, InsertNewCommentWithLongString_260) {
    std::string longComment(10000, 'x');
    XMLComment* comment = root->InsertNewComment(longComment.c_str());
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), longComment.c_str());
}

TEST_F(XMLElementInsertNewCommentTest_260, InsertNewCommentMixedWithElements_260) {
    root->InsertNewChildElement("elem1");
    XMLComment* c1 = root->InsertNewComment("comment1");
    root->InsertNewChildElement("elem2");
    XMLComment* c2 = root->InsertNewComment("comment2");

    ASSERT_NE(c1, nullptr);
    ASSERT_NE(c2, nullptr);

    // Verify order: elem1, comment1, elem2, comment2
    const XMLNode* node = root->FirstChild();
    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToElement(), nullptr);

    node = node->NextSibling();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->ToComment(), c1);

    node = node->NextSibling();
    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToElement(), nullptr);

    node = node->NextSibling();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->ToComment(), c2);
}

TEST_F(XMLElementInsertNewCommentTest_260, InsertNewCommentPreservedAfterPrint_260) {
    root->InsertNewComment("printed comment");

    XMLPrinter printer;
    doc.Print(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("printed comment"), std::string::npos);
}

TEST_F(XMLElementInsertNewCommentTest_260, InsertNewCommentOnNestedElement_260) {
    XMLElement* child = root->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);

    XMLComment* comment = child->InsertNewComment("nested comment");
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "nested comment");
    EXPECT_EQ(comment->Parent(), child);
}

TEST_F(XMLElementInsertNewCommentTest_260, DeleteChildAfterInsertNewComment_260) {
    XMLComment* comment = root->InsertNewComment("to be deleted");
    ASSERT_NE(comment, nullptr);
    EXPECT_FALSE(root->NoChildren());

    root->DeleteChild(comment);
    EXPECT_TRUE(root->NoChildren());
}

TEST_F(XMLElementInsertNewCommentTest_260, InsertNewCommentWithNewlines_260) {
    XMLComment* comment = root->InsertNewComment("line1\nline2\nline3");
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "line1\nline2\nline3");
}
