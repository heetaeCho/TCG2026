#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Mock visitor to test XMLComment::Accept
class MockXMLVisitor : public XMLVisitor {
public:
    MOCK_METHOD(bool, VisitEnter, (const XMLDocument&), (override));
    MOCK_METHOD(bool, VisitExit, (const XMLDocument&), (override));
    MOCK_METHOD(bool, VisitEnter, (const XMLElement&, const XMLAttribute*), (override));
    MOCK_METHOD(bool, VisitExit, (const XMLElement&), (override));
    MOCK_METHOD(bool, Visit, (const XMLDeclaration&), (override));
    MOCK_METHOD(bool, Visit, (const XMLText&), (override));
    MOCK_METHOD(bool, Visit, (const XMLComment&), (override));
    MOCK_METHOD(bool, Visit, (const XMLUnknown&), (override));
};

class XMLCommentTest_200 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test that Accept calls Visit on the visitor with the comment and returns true when visitor returns true
TEST_F(XMLCommentTest_200, AcceptCallsVisitorVisitReturnsTrue_200) {
    // Create an XML document with a comment
    doc->Parse("<!-- This is a comment -->");
    XMLNode* node = doc->FirstChild();
    ASSERT_NE(node, nullptr);
    XMLComment* comment = node->ToComment();
    ASSERT_NE(comment, nullptr);

    MockXMLVisitor mockVisitor;
    EXPECT_CALL(mockVisitor, Visit(testing::Matcher<const XMLComment&>(testing::Ref(*comment))))
        .Times(1)
        .WillOnce(testing::Return(true));

    bool result = comment->Accept(&mockVisitor);
    EXPECT_TRUE(result);
}

// Test that Accept returns false when the visitor's Visit returns false
TEST_F(XMLCommentTest_200, AcceptCallsVisitorVisitReturnsFalse_200) {
    doc->Parse("<!-- Another comment -->");
    XMLNode* node = doc->FirstChild();
    ASSERT_NE(node, nullptr);
    XMLComment* comment = node->ToComment();
    ASSERT_NE(comment, nullptr);

    MockXMLVisitor mockVisitor;
    EXPECT_CALL(mockVisitor, Visit(testing::Matcher<const XMLComment&>(testing::Ref(*comment))))
        .Times(1)
        .WillOnce(testing::Return(false));

    bool result = comment->Accept(&mockVisitor);
    EXPECT_FALSE(result);
}

// Test that ToComment returns non-null for an XMLComment node
TEST_F(XMLCommentTest_200, ToCommentReturnsNonNull_200) {
    doc->Parse("<!-- test -->");
    XMLNode* node = doc->FirstChild();
    ASSERT_NE(node, nullptr);
    XMLComment* comment = node->ToComment();
    EXPECT_NE(comment, nullptr);
}

// Test ShallowClone creates a copy in the target document
TEST_F(XMLCommentTest_200, ShallowCloneCreatesComment_200) {
    doc->Parse("<!-- clone me -->");
    XMLNode* node = doc->FirstChild();
    ASSERT_NE(node, nullptr);
    XMLComment* comment = node->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLDocument targetDoc;
    XMLNode* cloned = comment->ShallowClone(&targetDoc);
    ASSERT_NE(cloned, nullptr);
    XMLComment* clonedComment = cloned->ToComment();
    ASSERT_NE(clonedComment, nullptr);

    // The cloned comment should have the same value
    EXPECT_STREQ(comment->Value(), clonedComment->Value());

    // Clean up - the cloned node is not inserted, need to delete via document
    targetDoc.DeleteNode(cloned);
}

// Test ShallowEqual returns true for comments with the same value
TEST_F(XMLCommentTest_200, ShallowEqualSameValue_200) {
    doc->Parse("<!-- same comment -->");
    XMLNode* node = doc->FirstChild();
    ASSERT_NE(node, nullptr);
    XMLComment* comment = node->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLDocument doc2;
    doc2.Parse("<!-- same comment -->");
    XMLNode* node2 = doc2.FirstChild();
    ASSERT_NE(node2, nullptr);
    XMLComment* comment2 = node2->ToComment();
    ASSERT_NE(comment2, nullptr);

    EXPECT_TRUE(comment->ShallowEqual(comment2));
}

// Test ShallowEqual returns false for comments with different values
TEST_F(XMLCommentTest_200, ShallowEqualDifferentValue_200) {
    doc->Parse("<!-- comment A -->");
    XMLNode* node = doc->FirstChild();
    ASSERT_NE(node, nullptr);
    XMLComment* comment = node->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLDocument doc2;
    doc2.Parse("<!-- comment B -->");
    XMLNode* node2 = doc2.FirstChild();
    ASSERT_NE(node2, nullptr);
    XMLComment* comment2 = node2->ToComment();
    ASSERT_NE(comment2, nullptr);

    EXPECT_FALSE(comment->ShallowEqual(comment2));
}

// Test ShallowEqual returns false when comparing with a non-comment node
TEST_F(XMLCommentTest_200, ShallowEqualDifferentNodeType_200) {
    doc->Parse("<!-- a comment --><root/>");
    XMLNode* commentNode = doc->FirstChild();
    ASSERT_NE(commentNode, nullptr);
    XMLComment* comment = commentNode->ToComment();
    ASSERT_NE(comment, nullptr);

    // Find the element node
    XMLNode* elementNode = commentNode->NextSibling();
    ASSERT_NE(elementNode, nullptr);
    ASSERT_NE(elementNode->ToElement(), nullptr);

    EXPECT_FALSE(comment->ShallowEqual(elementNode));
}

// Test parsing a comment with empty content
TEST_F(XMLCommentTest_200, EmptyComment_200) {
    doc->Parse("<!---->");
    XMLNode* node = doc->FirstChild();
    ASSERT_NE(node, nullptr);
    XMLComment* comment = node->ToComment();
    ASSERT_NE(comment, nullptr);

    // Value should be empty or whitespace
    EXPECT_NE(comment->Value(), nullptr);
}

// Test ShallowClone into a different document
TEST_F(XMLCommentTest_200, ShallowCloneDifferentDocument_200) {
    doc->Parse("<!-- cloneable -->");
    XMLNode* node = doc->FirstChild();
    ASSERT_NE(node, nullptr);
    XMLComment* comment = node->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLDocument otherDoc;
    XMLNode* cloned = comment->ShallowClone(&otherDoc);
    ASSERT_NE(cloned, nullptr);

    // The cloned node should be a comment
    EXPECT_NE(cloned->ToComment(), nullptr);
    EXPECT_STREQ(cloned->Value(), comment->Value());

    otherDoc.DeleteNode(cloned);
}

// Test Accept is called exactly once per invocation
TEST_F(XMLCommentTest_200, AcceptCalledExactlyOnce_200) {
    doc->Parse("<!-- visitor test -->");
    XMLNode* node = doc->FirstChild();
    ASSERT_NE(node, nullptr);
    XMLComment* comment = node->ToComment();
    ASSERT_NE(comment, nullptr);

    MockXMLVisitor mockVisitor;
    EXPECT_CALL(mockVisitor, Visit(testing::Matcher<const XMLComment&>(testing::_)))
        .Times(1)
        .WillOnce(testing::Return(true));

    comment->Accept(&mockVisitor);
}

// Test comment within a document with other elements
TEST_F(XMLCommentTest_200, CommentAmongElements_200) {
    doc->Parse("<root><!-- inner comment --><child/></root>");
    ASSERT_FALSE(doc->Error());

    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLNode* child = root->FirstChild();
    ASSERT_NE(child, nullptr);
    XMLComment* comment = child->ToComment();
    ASSERT_NE(comment, nullptr);

    EXPECT_STREQ(comment->Value(), " inner comment ");

    MockXMLVisitor mockVisitor;
    EXPECT_CALL(mockVisitor, Visit(testing::Matcher<const XMLComment&>(testing::_)))
        .Times(1)
        .WillOnce(testing::Return(true));

    bool result = comment->Accept(&mockVisitor);
    EXPECT_TRUE(result);
}

// Test multiple comments
TEST_F(XMLCommentTest_200, MultipleComments_200) {
    doc->Parse("<!-- first --><!-- second -->");
    XMLNode* first = doc->FirstChild();
    ASSERT_NE(first, nullptr);
    XMLComment* comment1 = first->ToComment();
    ASSERT_NE(comment1, nullptr);

    XMLNode* second = first->NextSibling();
    ASSERT_NE(second, nullptr);
    XMLComment* comment2 = second->ToComment();
    ASSERT_NE(comment2, nullptr);

    EXPECT_FALSE(comment1->ShallowEqual(comment2));
}
