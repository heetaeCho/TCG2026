#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLDocument::NewComment tests
class XMLDocumentNewCommentTest_273 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test that NewComment returns a non-null pointer
TEST_F(XMLDocumentNewCommentTest_273, ReturnsNonNull_273) {
    XMLComment* comment = doc.NewComment("This is a comment");
    ASSERT_NE(comment, nullptr);
}

// Test that the comment value matches the string passed to NewComment
TEST_F(XMLDocumentNewCommentTest_273, ValueMatchesInput_273) {
    const char* text = "Hello World Comment";
    XMLComment* comment = doc.NewComment(text);
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), text);
}

// Test NewComment with an empty string
TEST_F(XMLDocumentNewCommentTest_273, EmptyString_273) {
    XMLComment* comment = doc.NewComment("");
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "");
}

// Test that the returned node is indeed a comment (ToComment returns non-null)
TEST_F(XMLDocumentNewCommentTest_273, IsCommentType_273) {
    XMLComment* comment = doc.NewComment("test");
    ASSERT_NE(comment, nullptr);
    EXPECT_NE(comment->ToComment(), nullptr);
}

// Test that the comment is not an element
TEST_F(XMLDocumentNewCommentTest_273, IsNotElement_273) {
    XMLComment* comment = doc.NewComment("test");
    ASSERT_NE(comment, nullptr);
    EXPECT_EQ(comment->ToElement(), nullptr);
}

// Test that the comment is not a text node
TEST_F(XMLDocumentNewCommentTest_273, IsNotText_273) {
    XMLComment* comment = doc.NewComment("test");
    ASSERT_NE(comment, nullptr);
    EXPECT_EQ(comment->ToText(), nullptr);
}

// Test that the comment is not a declaration
TEST_F(XMLDocumentNewCommentTest_273, IsNotDeclaration_273) {
    XMLComment* comment = doc.NewComment("test");
    ASSERT_NE(comment, nullptr);
    EXPECT_EQ(comment->ToDeclaration(), nullptr);
}

// Test that the comment is not a document
TEST_F(XMLDocumentNewCommentTest_273, IsNotDocument_273) {
    XMLComment* comment = doc.NewComment("test");
    ASSERT_NE(comment, nullptr);
    EXPECT_EQ(comment->ToDocument(), nullptr);
}

// Test that the comment has no parent initially (unlinked)
TEST_F(XMLDocumentNewCommentTest_273, HasNoParentInitially_273) {
    XMLComment* comment = doc.NewComment("orphan comment");
    ASSERT_NE(comment, nullptr);
    EXPECT_EQ(comment->Parent(), nullptr);
}

// Test that the comment has no children
TEST_F(XMLDocumentNewCommentTest_273, HasNoChildren_273) {
    XMLComment* comment = doc.NewComment("a comment");
    ASSERT_NE(comment, nullptr);
    EXPECT_TRUE(comment->NoChildren());
}

// Test that the comment's GetDocument returns the creating document
TEST_F(XMLDocumentNewCommentTest_273, DocumentMatchesCreator_273) {
    XMLComment* comment = doc.NewComment("doc check");
    ASSERT_NE(comment, nullptr);
    EXPECT_EQ(comment->GetDocument(), &doc);
}

// Test creating multiple comments
TEST_F(XMLDocumentNewCommentTest_273, MultipleComments_273) {
    XMLComment* c1 = doc.NewComment("first");
    XMLComment* c2 = doc.NewComment("second");
    XMLComment* c3 = doc.NewComment("third");
    ASSERT_NE(c1, nullptr);
    ASSERT_NE(c2, nullptr);
    ASSERT_NE(c3, nullptr);
    EXPECT_STREQ(c1->Value(), "first");
    EXPECT_STREQ(c2->Value(), "second");
    EXPECT_STREQ(c3->Value(), "third");
}

// Test NewComment with special characters
TEST_F(XMLDocumentNewCommentTest_273, SpecialCharacters_273) {
    const char* text = "Comment with <special> & \"characters\" 'here'";
    XMLComment* comment = doc.NewComment(text);
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), text);
}

// Test NewComment with a long string
TEST_F(XMLDocumentNewCommentTest_273, LongString_273) {
    std::string longStr(10000, 'A');
    XMLComment* comment = doc.NewComment(longStr.c_str());
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), longStr.c_str());
}

// Test that a comment can be inserted into the document
TEST_F(XMLDocumentNewCommentTest_273, CanInsertAsChild_273) {
    XMLComment* comment = doc.NewComment("inserted comment");
    ASSERT_NE(comment, nullptr);
    XMLNode* result = doc.InsertEndChild(comment);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(comment->Parent(), &doc);
}

// Test that a comment can be inserted and then found as first child
TEST_F(XMLDocumentNewCommentTest_273, InsertedCommentIsFirstChild_273) {
    XMLComment* comment = doc.NewComment("first child");
    doc.InsertFirstChild(comment);
    const XMLNode* first = doc.FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_NE(first->ToComment(), nullptr);
    EXPECT_STREQ(first->Value(), "first child");
}

// Test NewComment with whitespace-only content
TEST_F(XMLDocumentNewCommentTest_273, WhitespaceContent_273) {
    XMLComment* comment = doc.NewComment("   \t\n  ");
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "   \t\n  ");
}

// Test NewComment with Unicode/UTF-8 content
TEST_F(XMLDocumentNewCommentTest_273, Utf8Content_273) {
    const char* text = "コメント テスト 日本語";
    XMLComment* comment = doc.NewComment(text);
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), text);
}

// Test that NewComment comment can be deep cloned
TEST_F(XMLDocumentNewCommentTest_273, DeepClone_273) {
    XMLComment* comment = doc.NewComment("clone me");
    doc.InsertEndChild(comment);

    XMLDocument target;
    doc.DeepCopy(&target);

    const XMLNode* firstChild = target.FirstChild();
    ASSERT_NE(firstChild, nullptr);
    ASSERT_NE(firstChild->ToComment(), nullptr);
    EXPECT_STREQ(firstChild->Value(), "clone me");
}

// Test that comment node can be deleted via DeleteNode
TEST_F(XMLDocumentNewCommentTest_273, DeleteNode_273) {
    XMLComment* comment = doc.NewComment("to delete");
    doc.InsertEndChild(comment);
    EXPECT_FALSE(doc.NoChildren());
    doc.DeleteNode(comment);
    EXPECT_TRUE(doc.NoChildren());
}

// Test ShallowClone of a comment
TEST_F(XMLDocumentNewCommentTest_273, ShallowClone_273) {
    XMLComment* comment = doc.NewComment("shallow clone test");
    doc.InsertEndChild(comment);

    XMLDocument target;
    const XMLNode* cloned = comment->ShallowClone(&target);
    ASSERT_NE(cloned, nullptr);
    ASSERT_NE(cloned->ToComment(), nullptr);
    EXPECT_STREQ(cloned->Value(), "shallow clone test");
}

// Test ShallowEqual of two comments with the same value
TEST_F(XMLDocumentNewCommentTest_273, ShallowEqualSameValue_273) {
    XMLComment* c1 = doc.NewComment("equal");
    XMLComment* c2 = doc.NewComment("equal");
    EXPECT_TRUE(c1->ShallowEqual(c2));
}

// Test ShallowEqual of two comments with different values
TEST_F(XMLDocumentNewCommentTest_273, ShallowEqualDifferentValue_273) {
    XMLComment* c1 = doc.NewComment("one");
    XMLComment* c2 = doc.NewComment("two");
    EXPECT_FALSE(c1->ShallowEqual(c2));
}

// Test that comment integrates properly with Parse (round-trip)
TEST_F(XMLDocumentNewCommentTest_273, ParseRoundTrip_273) {
    const char* xml = "<!-- A parsed comment --><root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);

    const XMLNode* first = doc.FirstChild();
    ASSERT_NE(first, nullptr);
    ASSERT_NE(first->ToComment(), nullptr);
    EXPECT_STREQ(first->Value(), " A parsed comment ");
}

// Test that comment created via NewComment can be printed
TEST_F(XMLDocumentNewCommentTest_273, PrintComment_273) {
    XMLComment* comment = doc.NewComment("print test");
    doc.InsertEndChild(comment);

    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    // The printed output should contain the comment
    EXPECT_NE(std::string(result).find("print test"), std::string::npos);
    EXPECT_NE(std::string(result).find("<!--"), std::string::npos);
    EXPECT_NE(std::string(result).find("-->"), std::string::npos);
}

// Test Accept with XMLPrinter as visitor
TEST_F(XMLDocumentNewCommentTest_273, AcceptVisitor_273) {
    XMLComment* comment = doc.NewComment("visitor test");
    doc.InsertEndChild(comment);

    XMLPrinter printer;
    bool accepted = comment->Accept(&printer);
    EXPECT_TRUE(accepted);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_NE(std::string(result).find("visitor test"), std::string::npos);
}

// Test GetLineNum for a newly created comment (should be 0 since not parsed)
TEST_F(XMLDocumentNewCommentTest_273, LineNumIsZeroForNew_273) {
    XMLComment* comment = doc.NewComment("line num test");
    ASSERT_NE(comment, nullptr);
    EXPECT_EQ(comment->GetLineNum(), 0);
}

// Test that UserData is initially null
TEST_F(XMLDocumentNewCommentTest_273, UserDataInitiallyNull_273) {
    XMLComment* comment = doc.NewComment("userdata test");
    ASSERT_NE(comment, nullptr);
    EXPECT_EQ(comment->GetUserData(), nullptr);
}

// Test setting and getting UserData on a comment
TEST_F(XMLDocumentNewCommentTest_273, SetAndGetUserData_273) {
    XMLComment* comment = doc.NewComment("userdata");
    int data = 42;
    comment->SetUserData(&data);
    EXPECT_EQ(comment->GetUserData(), &data);
}
