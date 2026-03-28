#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLComment tests
class XMLCommentTest_66 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test that creating a comment via XMLDocument and ToComment returns non-null
TEST_F(XMLCommentTest_66, ToCommentReturnsNonNull_66) {
    XMLComment* comment = doc.NewComment("test comment");
    ASSERT_NE(comment, nullptr);
    EXPECT_EQ(comment->ToComment(), comment);
}

// Test that ToComment returns this pointer
TEST_F(XMLCommentTest_66, ToCommentReturnsSelf_66) {
    XMLComment* comment = doc.NewComment("hello");
    EXPECT_EQ(comment->ToComment(), comment);
}

// Test creating a comment with empty text
TEST_F(XMLCommentTest_66, EmptyComment_66) {
    XMLComment* comment = doc.NewComment("");
    ASSERT_NE(comment, nullptr);
    EXPECT_EQ(comment->ToComment(), comment);
}

// Test creating a comment with null text
TEST_F(XMLCommentTest_66, NullComment_66) {
    XMLComment* comment = doc.NewComment(nullptr);
    ASSERT_NE(comment, nullptr);
    EXPECT_EQ(comment->ToComment(), comment);
}

// Test ShallowClone creates a valid copy in the same document
TEST_F(XMLCommentTest_66, ShallowCloneSameDocument_66) {
    XMLComment* comment = doc.NewComment("clone test");
    ASSERT_NE(comment, nullptr);
    
    XMLNode* cloned = comment->ShallowClone(&doc);
    ASSERT_NE(cloned, nullptr);
    EXPECT_NE(cloned->ToComment(), nullptr);
}

// Test ShallowClone creates a valid copy in a different document
TEST_F(XMLCommentTest_66, ShallowCloneDifferentDocument_66) {
    XMLComment* comment = doc.NewComment("clone test");
    ASSERT_NE(comment, nullptr);
    
    XMLDocument doc2;
    XMLNode* cloned = comment->ShallowClone(&doc2);
    ASSERT_NE(cloned, nullptr);
    EXPECT_NE(cloned->ToComment(), nullptr);
}

// Test ShallowEqual with identical comments
TEST_F(XMLCommentTest_66, ShallowEqualIdenticalComments_66) {
    XMLComment* comment1 = doc.NewComment("same text");
    XMLComment* comment2 = doc.NewComment("same text");
    ASSERT_NE(comment1, nullptr);
    ASSERT_NE(comment2, nullptr);
    
    EXPECT_TRUE(comment1->ShallowEqual(comment2));
}

// Test ShallowEqual with different comments
TEST_F(XMLCommentTest_66, ShallowEqualDifferentComments_66) {
    XMLComment* comment1 = doc.NewComment("text A");
    XMLComment* comment2 = doc.NewComment("text B");
    ASSERT_NE(comment1, nullptr);
    ASSERT_NE(comment2, nullptr);
    
    EXPECT_FALSE(comment1->ShallowEqual(comment2));
}

// Test ShallowEqual with a non-comment node
TEST_F(XMLCommentTest_66, ShallowEqualWithNonComment_66) {
    XMLComment* comment = doc.NewComment("a comment");
    XMLElement* element = doc.NewElement("elem");
    ASSERT_NE(comment, nullptr);
    ASSERT_NE(element, nullptr);
    
    EXPECT_FALSE(comment->ShallowEqual(element));
}

// Test ShallowEqual with cloned comment
TEST_F(XMLCommentTest_66, ShallowEqualWithClone_66) {
    XMLComment* comment = doc.NewComment("clone equal test");
    ASSERT_NE(comment, nullptr);
    
    XMLNode* cloned = comment->ShallowClone(&doc);
    ASSERT_NE(cloned, nullptr);
    
    EXPECT_TRUE(comment->ShallowEqual(cloned));
}

// Mock XMLVisitor for Accept testing
class MockXMLVisitor : public XMLVisitor {
public:
    MOCK_METHOD(bool, Visit, (const XMLComment&), (override));
    // Need default implementations for other Visit methods
    MOCK_METHOD(bool, VisitEnter, (const XMLDocument&), (override));
    MOCK_METHOD(bool, VisitExit, (const XMLDocument&), (override));
    MOCK_METHOD(bool, VisitEnter, (const XMLElement&, const XMLAttribute*), (override));
    MOCK_METHOD(bool, VisitExit, (const XMLElement&), (override));
    MOCK_METHOD(bool, Visit, (const XMLDeclaration&), (override));
    MOCK_METHOD(bool, Visit, (const XMLText&), (override));
    MOCK_METHOD(bool, Visit, (const XMLUnknown&), (override));
};

// Test Accept calls visitor's Visit method
TEST_F(XMLCommentTest_66, AcceptCallsVisitor_66) {
    XMLComment* comment = doc.NewComment("visitor test");
    ASSERT_NE(comment, nullptr);
    
    MockXMLVisitor visitor;
    EXPECT_CALL(visitor, Visit(testing::Ref(*comment)))
        .Times(1)
        .WillOnce(testing::Return(true));
    
    bool result = comment->Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test Accept returns false when visitor returns false
TEST_F(XMLCommentTest_66, AcceptReturnsFalseWhenVisitorReturnsFalse_66) {
    XMLComment* comment = doc.NewComment("visitor false test");
    ASSERT_NE(comment, nullptr);
    
    MockXMLVisitor visitor;
    EXPECT_CALL(visitor, Visit(testing::Ref(*comment)))
        .Times(1)
        .WillOnce(testing::Return(false));
    
    bool result = comment->Accept(&visitor);
    EXPECT_FALSE(result);
}

// Test comment can be inserted into a document and retrieved
TEST_F(XMLCommentTest_66, InsertCommentIntoDocument_66) {
    doc.InsertEndChild(doc.NewComment("doc comment"));
    
    XMLNode* firstChild = doc.FirstChild();
    ASSERT_NE(firstChild, nullptr);
    EXPECT_NE(firstChild->ToComment(), nullptr);
}

// Test parsing a document with a comment
TEST_F(XMLCommentTest_66, ParseDocumentWithComment_66) {
    const char* xml = "<!-- This is a comment --><root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    
    XMLNode* firstChild = doc.FirstChild();
    ASSERT_NE(firstChild, nullptr);
    EXPECT_NE(firstChild->ToComment(), nullptr);
}

// Test parsing a document with multiple comments
TEST_F(XMLCommentTest_66, ParseDocumentWithMultipleComments_66) {
    const char* xml = "<!-- comment1 --><root><!-- comment2 --></root><!-- comment3 -->";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    
    XMLNode* first = doc.FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_NE(first->ToComment(), nullptr);
}

// Test comment Value()
TEST_F(XMLCommentTest_66, CommentValuePreserved_66) {
    const char* xml = "<!-- hello world --><root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    
    XMLNode* firstChild = doc.FirstChild();
    ASSERT_NE(firstChild, nullptr);
    XMLComment* comment = firstChild->ToComment();
    ASSERT_NE(comment, nullptr);
    
    EXPECT_STREQ(comment->Value(), " hello world ");
}

// Test comment with special characters
TEST_F(XMLCommentTest_66, CommentWithSpecialCharacters_66) {
    const char* xml = "<!-- <special> & \"chars\" --><root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    
    XMLNode* firstChild = doc.FirstChild();
    ASSERT_NE(firstChild, nullptr);
    EXPECT_NE(firstChild->ToComment(), nullptr);
}

// Test that non-comment nodes return null for ToComment
TEST_F(XMLCommentTest_66, NonCommentNodeToCommentReturnsNull_66) {
    XMLElement* elem = doc.NewElement("test");
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->ToComment(), nullptr);
}

// Test ShallowEqual with empty comments
TEST_F(XMLCommentTest_66, ShallowEqualEmptyComments_66) {
    XMLComment* comment1 = doc.NewComment("");
    XMLComment* comment2 = doc.NewComment("");
    ASSERT_NE(comment1, nullptr);
    ASSERT_NE(comment2, nullptr);
    
    EXPECT_TRUE(comment1->ShallowEqual(comment2));
}

// Test comment with long text
TEST_F(XMLCommentTest_66, CommentWithLongText_66) {
    std::string longText(10000, 'x');
    XMLComment* comment = doc.NewComment(longText.c_str());
    ASSERT_NE(comment, nullptr);
    EXPECT_EQ(comment->ToComment(), comment);
    EXPECT_STREQ(comment->Value(), longText.c_str());
}

// Test printing a comment via XMLPrinter
TEST_F(XMLCommentTest_66, PrintComment_66) {
    const char* xml = "<!-- test print --><root/>";
    doc.Parse(xml);
    
    XMLPrinter printer;
    doc.Accept(&printer);
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_NE(std::string(result).find("<!-- test print -->"), std::string::npos);
}
