#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Mock visitor to test XMLVisitor interface
class MockXMLVisitor : public XMLVisitor {
public:
    MOCK_METHOD(bool, Visit, (const XMLComment&), (override));
};

// Test fixture
class XMLVisitorTest_32 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that the default Visit method returns true
TEST_F(XMLVisitorTest_32, DefaultVisitReturnsTrue_32) {
    XMLVisitor visitor;
    
    // We need an XMLComment to pass to Visit. We'll create a document and add a comment.
    XMLDocument doc;
    doc.Parse("<!-- test comment -->");
    const XMLComment* comment = doc.FirstChild()->ToComment();
    ASSERT_NE(comment, nullptr);
    
    bool result = visitor.Visit(*comment);
    EXPECT_TRUE(result);
}

// Test that a derived visitor can override Visit
TEST_F(XMLVisitorTest_32, MockVisitorCanOverrideVisit_32) {
    MockXMLVisitor mockVisitor;
    
    XMLDocument doc;
    doc.Parse("<!-- hello world -->");
    const XMLComment* comment = doc.FirstChild()->ToComment();
    ASSERT_NE(comment, nullptr);
    
    EXPECT_CALL(mockVisitor, Visit(::testing::_))
        .WillOnce(::testing::Return(false));
    
    bool result = mockVisitor.Visit(*comment);
    EXPECT_FALSE(result);
}

// Test that Visit can be called multiple times with default behavior
TEST_F(XMLVisitorTest_32, DefaultVisitReturnsTrueMultipleCalls_32) {
    XMLVisitor visitor;
    
    XMLDocument doc;
    doc.Parse("<!-- comment1 --><!-- comment2 -->");
    
    const XMLNode* node = doc.FirstChild();
    while (node) {
        const XMLComment* comment = node->ToComment();
        if (comment) {
            EXPECT_TRUE(visitor.Visit(*comment));
        }
        node = node->NextSibling();
    }
}

// Test that mock visitor can return true
TEST_F(XMLVisitorTest_32, MockVisitorReturnsTrue_32) {
    MockXMLVisitor mockVisitor;
    
    XMLDocument doc;
    doc.Parse("<!-- some comment -->");
    const XMLComment* comment = doc.FirstChild()->ToComment();
    ASSERT_NE(comment, nullptr);
    
    EXPECT_CALL(mockVisitor, Visit(::testing::_))
        .WillOnce(::testing::Return(true));
    
    bool result = mockVisitor.Visit(*comment);
    EXPECT_TRUE(result);
}

// Test that mock visitor is called correct number of times when Accept is used
TEST_F(XMLVisitorTest_32, VisitorCalledViaAccept_32) {
    MockXMLVisitor mockVisitor;
    
    XMLDocument doc;
    doc.Parse("<!-- my comment -->");
    const XMLComment* comment = doc.FirstChild()->ToComment();
    ASSERT_NE(comment, nullptr);
    
    // When Accept is called on a comment node, it should call Visit on the visitor
    EXPECT_CALL(mockVisitor, Visit(::testing::_))
        .Times(1)
        .WillOnce(::testing::Return(true));
    
    // Accept should trigger the visitor's Visit method
    const_cast<XMLComment*>(comment)->Accept(&mockVisitor);
}

// Test with empty comment
TEST_F(XMLVisitorTest_32, DefaultVisitWithEmptyComment_32) {
    XMLVisitor visitor;
    
    XMLDocument doc;
    doc.Parse("<!---->");
    const XMLComment* comment = doc.FirstChild()->ToComment();
    ASSERT_NE(comment, nullptr);
    
    EXPECT_TRUE(visitor.Visit(*comment));
}

// Test mock visitor returning false stops traversal indication
TEST_F(XMLVisitorTest_32, MockVisitorReturnsFalseToStopTraversal_32) {
    MockXMLVisitor mockVisitor;
    
    XMLDocument doc;
    doc.Parse("<!-- first --><!-- second -->");
    
    // Collect comments
    std::vector<const XMLComment*> comments;
    const XMLNode* node = doc.FirstChild();
    while (node) {
        const XMLComment* c = node->ToComment();
        if (c) comments.push_back(c);
        node = node->NextSibling();
    }
    
    ASSERT_GE(comments.size(), 1u);
    
    EXPECT_CALL(mockVisitor, Visit(::testing::_))
        .WillOnce(::testing::Return(false));
    
    bool result = mockVisitor.Visit(*comments[0]);
    EXPECT_FALSE(result);
}
