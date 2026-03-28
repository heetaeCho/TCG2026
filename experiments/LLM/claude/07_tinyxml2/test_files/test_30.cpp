#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Mock visitor to test the XMLVisitor interface
class MockXMLVisitor : public XMLVisitor {
public:
    MOCK_METHOD(bool, Visit, (const XMLDeclaration&), (override));
};

// Test fixture
class XMLVisitorTest_30 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that the default Visit(XMLDeclaration) returns true
TEST_F(XMLVisitorTest_30, DefaultVisitDeclarationReturnsTrue_30) {
    XMLVisitor visitor;
    
    // We need an XMLDeclaration to pass. We'll create one through the document.
    XMLDocument doc;
    // Parse a document that contains a declaration
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    bool result = visitor.Visit(*decl);
    EXPECT_TRUE(result);
}

// Test that a derived class can override Visit for XMLDeclaration
TEST_F(XMLVisitorTest_30, MockVisitDeclarationCanReturnFalse_30) {
    MockXMLVisitor mockVisitor;
    
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    EXPECT_CALL(mockVisitor, Visit(::testing::Ref(*decl)))
        .WillOnce(::testing::Return(false));
    
    bool result = mockVisitor.Visit(*decl);
    EXPECT_FALSE(result);
}

// Test that a derived class can override Visit and return true
TEST_F(XMLVisitorTest_30, MockVisitDeclarationCanReturnTrue_30) {
    MockXMLVisitor mockVisitor;
    
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>");
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    EXPECT_CALL(mockVisitor, Visit(::testing::Ref(*decl)))
        .WillOnce(::testing::Return(true));
    
    bool result = mockVisitor.Visit(*decl);
    EXPECT_TRUE(result);
}

// Test multiple calls to Visit on default visitor all return true
TEST_F(XMLVisitorTest_30, DefaultVisitDeclarationMultipleCalls_30) {
    XMLVisitor visitor;
    
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    // Call multiple times to ensure consistent behavior
    EXPECT_TRUE(visitor.Visit(*decl));
    EXPECT_TRUE(visitor.Visit(*decl));
    EXPECT_TRUE(visitor.Visit(*decl));
}

// Test that XMLVisitor can be used with Accept on a document containing a declaration
TEST_F(XMLVisitorTest_30, AcceptCallsVisitOnDeclaration_30) {
    MockXMLVisitor mockVisitor;
    
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    
    // When Accept is called on the declaration node, it should call Visit
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    EXPECT_CALL(mockVisitor, Visit(::testing::Ref(*decl)))
        .WillOnce(::testing::Return(true));
    
    // Accept on the declaration node should invoke Visit
    const_cast<XMLDeclaration*>(decl)->Accept(&mockVisitor);
}

// Test that XMLVisitor is polymorphically destroyable
TEST_F(XMLVisitorTest_30, PolymorphicDeletion_30) {
    // Ensure no issues with polymorphic deletion via base pointer
    XMLVisitor* visitor = new MockXMLVisitor();
    delete visitor;
    // If we reach here without crash, the test passes
    SUCCEED();
}

// Boundary: declaration with minimal content
TEST_F(XMLVisitorTest_30, VisitMinimalDeclaration_30) {
    XMLVisitor visitor;
    
    XMLDocument doc;
    doc.Parse("<?xml?><root/>");
    
    // Check if a minimal declaration is parseable and visitable
    const XMLNode* firstChild = doc.FirstChild();
    if (firstChild != nullptr) {
        const XMLDeclaration* decl = firstChild->ToDeclaration();
        if (decl != nullptr) {
            EXPECT_TRUE(visitor.Visit(*decl));
        }
    }
    // If parsing doesn't produce a declaration, that's also valid behavior
    SUCCEED();
}
