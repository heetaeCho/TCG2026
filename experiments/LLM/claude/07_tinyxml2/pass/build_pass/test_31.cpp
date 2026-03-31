#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Mock visitor to test XMLVisitor behavior
class MockXMLVisitor : public XMLVisitor {
public:
    MOCK_METHOD(bool, Visit, (const XMLText& text), (override));
};

// Test fixture
class XMLVisitorTest_31 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that the default XMLVisitor::Visit returns true
TEST_F(XMLVisitorTest_31, DefaultVisitReturnsTrue_31) {
    XMLVisitor visitor;
    
    // We need an XMLText to pass to Visit. Create a document and add text.
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    root->SetText("Hello World");
    
    const XMLText* textNode = root->FirstChild()->ToText();
    ASSERT_NE(textNode, nullptr);
    
    bool result = visitor.Visit(*textNode);
    EXPECT_TRUE(result);
}

// Test that a derived (mocked) visitor can override Visit
TEST_F(XMLVisitorTest_31, MockVisitCanReturnFalse_31) {
    MockXMLVisitor mockVisitor;
    
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    root->SetText("Test text");
    
    const XMLText* textNode = root->FirstChild()->ToText();
    ASSERT_NE(textNode, nullptr);
    
    EXPECT_CALL(mockVisitor, Visit(::testing::_))
        .WillOnce(::testing::Return(false));
    
    bool result = mockVisitor.Visit(*textNode);
    EXPECT_FALSE(result);
}

// Test that a derived (mocked) visitor can return true
TEST_F(XMLVisitorTest_31, MockVisitCanReturnTrue_31) {
    MockXMLVisitor mockVisitor;
    
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    root->SetText("Another text");
    
    const XMLText* textNode = root->FirstChild()->ToText();
    ASSERT_NE(textNode, nullptr);
    
    EXPECT_CALL(mockVisitor, Visit(::testing::_))
        .WillOnce(::testing::Return(true));
    
    bool result = mockVisitor.Visit(*textNode);
    EXPECT_TRUE(result);
}

// Test default Visit with empty text node
TEST_F(XMLVisitorTest_31, DefaultVisitWithEmptyText_31) {
    XMLVisitor visitor;
    
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    root->SetText("");
    
    const XMLText* textNode = root->FirstChild()->ToText();
    ASSERT_NE(textNode, nullptr);
    
    bool result = visitor.Visit(*textNode);
    EXPECT_TRUE(result);
}

// Test that Visit is called when Accept is invoked on a document with text
TEST_F(XMLVisitorTest_31, VisitCalledViaAccept_31) {
    MockXMLVisitor mockVisitor;
    
    XMLDocument doc;
    doc.Parse("<root>Some text</root>");
    ASSERT_FALSE(doc.Error());
    
    // We expect Visit to be called at least once for the text node
    // We also need to handle other visitor methods - use default behavior
    ON_CALL(mockVisitor, Visit(::testing::_))
        .WillByDefault(::testing::Return(true));
    
    EXPECT_CALL(mockVisitor, Visit(::testing::_))
        .Times(::testing::AtLeast(1))
        .WillRepeatedly(::testing::Return(true));
    
    doc.Accept(&mockVisitor);
}

// Test multiple Visit calls with different text nodes
TEST_F(XMLVisitorTest_31, MultipleVisitCalls_31) {
    MockXMLVisitor mockVisitor;
    
    XMLDocument doc;
    doc.Parse("<root><a>Text1</a><b>Text2</b></root>");
    ASSERT_FALSE(doc.Error());
    
    ON_CALL(mockVisitor, Visit(::testing::_))
        .WillByDefault(::testing::Return(true));
    
    EXPECT_CALL(mockVisitor, Visit(::testing::_))
        .Times(::testing::AtLeast(2))
        .WillRepeatedly(::testing::Return(true));
    
    doc.Accept(&mockVisitor);
}

// Test that returning false from Visit can stop traversal
TEST_F(XMLVisitorTest_31, VisitReturnFalseStopsTraversal_31) {
    MockXMLVisitor mockVisitor;
    
    XMLDocument doc;
    doc.Parse("<root><a>Text1</a><b>Text2</b><c>Text3</c></root>");
    ASSERT_FALSE(doc.Error());
    
    ON_CALL(mockVisitor, Visit(::testing::_))
        .WillByDefault(::testing::Return(false));
    
    // When Visit returns false, traversal may stop, so we might get fewer calls
    EXPECT_CALL(mockVisitor, Visit(::testing::_))
        .Times(::testing::AtLeast(1))
        .WillRepeatedly(::testing::Return(false));
    
    doc.Accept(&mockVisitor);
}

// Test default visitor with special characters in text
TEST_F(XMLVisitorTest_31, DefaultVisitWithSpecialCharacters_31) {
    XMLVisitor visitor;
    
    XMLDocument doc;
    doc.Parse("<root>Hello &amp; World &lt; &gt;</root>");
    ASSERT_FALSE(doc.Error());
    
    const XMLText* textNode = doc.FirstChildElement("root")->FirstChild()->ToText();
    ASSERT_NE(textNode, nullptr);
    
    bool result = visitor.Visit(*textNode);
    EXPECT_TRUE(result);
}
