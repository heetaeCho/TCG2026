#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Mock XMLVisitor to test virtual interface
class MockXMLVisitor : public XMLVisitor {
public:
    MOCK_METHOD(bool, VisitEnter, (const XMLDocument&), (override));
};

// Test fixture
class XMLVisitorTest_26 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that the default XMLVisitor::VisitEnter returns true
TEST_F(XMLVisitorTest_26, DefaultVisitEnterReturnsTrue_26) {
    XMLVisitor visitor;
    XMLDocument doc;
    EXPECT_TRUE(visitor.VisitEnter(doc));
}

// Test that MockXMLVisitor can override VisitEnter behavior
TEST_F(XMLVisitorTest_26, MockVisitEnterCanReturnFalse_26) {
    MockXMLVisitor mockVisitor;
    XMLDocument doc;
    EXPECT_CALL(mockVisitor, VisitEnter(testing::_)).WillOnce(testing::Return(false));
    EXPECT_FALSE(mockVisitor.VisitEnter(doc));
}

// Test that MockXMLVisitor can override VisitEnter to return true
TEST_F(XMLVisitorTest_26, MockVisitEnterCanReturnTrue_26) {
    MockXMLVisitor mockVisitor;
    XMLDocument doc;
    EXPECT_CALL(mockVisitor, VisitEnter(testing::_)).WillOnce(testing::Return(true));
    EXPECT_TRUE(mockVisitor.VisitEnter(doc));
}

// Test multiple calls to default VisitEnter consistently return true
TEST_F(XMLVisitorTest_26, DefaultVisitEnterConsistentlyReturnsTrue_26) {
    XMLVisitor visitor;
    XMLDocument doc;
    EXPECT_TRUE(visitor.VisitEnter(doc));
    EXPECT_TRUE(visitor.VisitEnter(doc));
    EXPECT_TRUE(visitor.VisitEnter(doc));
}

// Test VisitEnter with different XMLDocument instances
TEST_F(XMLVisitorTest_26, DefaultVisitEnterWithDifferentDocuments_26) {
    XMLVisitor visitor;
    XMLDocument doc1;
    XMLDocument doc2;
    EXPECT_TRUE(visitor.VisitEnter(doc1));
    EXPECT_TRUE(visitor.VisitEnter(doc2));
}

// Test that XMLVisitor can be used polymorphically
TEST_F(XMLVisitorTest_26, PolymorphicUsageWithBasePointer_26) {
    MockXMLVisitor mockVisitor;
    XMLVisitor* basePtr = &mockVisitor;
    XMLDocument doc;
    
    EXPECT_CALL(mockVisitor, VisitEnter(testing::_)).WillOnce(testing::Return(false));
    EXPECT_FALSE(basePtr->VisitEnter(doc));
}

// Test that mock can be called multiple times with different return values
TEST_F(XMLVisitorTest_26, MockVisitEnterMultipleCalls_26) {
    MockXMLVisitor mockVisitor;
    XMLDocument doc;
    
    EXPECT_CALL(mockVisitor, VisitEnter(testing::_))
        .WillOnce(testing::Return(true))
        .WillOnce(testing::Return(false))
        .WillOnce(testing::Return(true));
    
    EXPECT_TRUE(mockVisitor.VisitEnter(doc));
    EXPECT_FALSE(mockVisitor.VisitEnter(doc));
    EXPECT_TRUE(mockVisitor.VisitEnter(doc));
}

// Test XMLDocument default construction
TEST_F(XMLVisitorTest_26, XMLDocumentDefaultConstruction_26) {
    XMLDocument doc;
    // Just verify it can be constructed and passed to VisitEnter
    XMLVisitor visitor;
    EXPECT_TRUE(visitor.VisitEnter(doc));
}
