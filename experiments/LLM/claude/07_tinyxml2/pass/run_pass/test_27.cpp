#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// We need a forward declaration or minimal XMLDocument for compilation
// Since XMLDocument is referenced in the interface, we need it to exist.
// The actual header should provide it, but if not, we work with what we have.

// Mock visitor to test virtual dispatch
class MockXMLVisitor : public XMLVisitor {
public:
    MOCK_METHOD(bool, VisitExit, (const XMLDocument&), (override));
};

// Concrete visitor that uses default implementation
class DefaultXMLVisitor : public XMLVisitor {
    // Uses default VisitExit which returns true
};

// Test fixture
class XMLVisitorTest_27 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that the default implementation of VisitExit returns true
TEST_F(XMLVisitorTest_27, DefaultVisitExitReturnsTrue_27) {
    DefaultXMLVisitor visitor;
    XMLDocument doc;
    bool result = visitor.VisitExit(doc);
    EXPECT_TRUE(result);
}

// Test that XMLVisitor can be instantiated directly and default VisitExit returns true
TEST_F(XMLVisitorTest_27, BaseClassVisitExitReturnsTrue_27) {
    XMLVisitor visitor;
    XMLDocument doc;
    EXPECT_TRUE(visitor.VisitExit(doc));
}

// Test that a derived class can override VisitExit to return false
TEST_F(XMLVisitorTest_27, OverriddenVisitExitCanReturnFalse_27) {
    class FalseVisitor : public XMLVisitor {
    public:
        bool VisitExit(const XMLDocument&) override { return false; }
    };
    
    FalseVisitor visitor;
    XMLDocument doc;
    EXPECT_FALSE(visitor.VisitExit(doc));
}

// Test virtual dispatch through base pointer - default behavior
TEST_F(XMLVisitorTest_27, VirtualDispatchDefaultBehavior_27) {
    DefaultXMLVisitor derivedVisitor;
    XMLVisitor* basePtr = &derivedVisitor;
    XMLDocument doc;
    EXPECT_TRUE(basePtr->VisitExit(doc));
}

// Test virtual dispatch through base pointer - overridden behavior
TEST_F(XMLVisitorTest_27, VirtualDispatchOverriddenBehavior_27) {
    class CustomVisitor : public XMLVisitor {
    public:
        bool VisitExit(const XMLDocument&) override { return false; }
    };
    
    CustomVisitor customVisitor;
    XMLVisitor* basePtr = &customVisitor;
    XMLDocument doc;
    EXPECT_FALSE(basePtr->VisitExit(doc));
}

// Test with mock - verify VisitExit is called
TEST_F(XMLVisitorTest_27, MockVisitExitIsCalled_27) {
    MockXMLVisitor mockVisitor;
    XMLDocument doc;
    
    EXPECT_CALL(mockVisitor, VisitExit(::testing::Ref(doc)))
        .Times(1)
        .WillOnce(::testing::Return(true));
    
    bool result = mockVisitor.VisitExit(doc);
    EXPECT_TRUE(result);
}

// Test with mock - VisitExit returning false
TEST_F(XMLVisitorTest_27, MockVisitExitReturnsFalse_27) {
    MockXMLVisitor mockVisitor;
    XMLDocument doc;
    
    EXPECT_CALL(mockVisitor, VisitExit(::testing::_))
        .WillOnce(::testing::Return(false));
    
    EXPECT_FALSE(mockVisitor.VisitExit(doc));
}

// Test multiple calls to VisitExit on default visitor
TEST_F(XMLVisitorTest_27, MultipleCallsToDefaultVisitExit_27) {
    XMLVisitor visitor;
    XMLDocument doc;
    
    EXPECT_TRUE(visitor.VisitExit(doc));
    EXPECT_TRUE(visitor.VisitExit(doc));
    EXPECT_TRUE(visitor.VisitExit(doc));
}

// Test that VisitExit accepts const XMLDocument reference
TEST_F(XMLVisitorTest_27, VisitExitAcceptsConstDocReference_27) {
    XMLVisitor visitor;
    const XMLDocument doc;
    EXPECT_TRUE(visitor.VisitExit(doc));
}

// Test mock called multiple times with different return values
TEST_F(XMLVisitorTest_27, MockMultipleCallsDifferentReturns_27) {
    MockXMLVisitor mockVisitor;
    XMLDocument doc;
    
    EXPECT_CALL(mockVisitor, VisitExit(::testing::_))
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(true));
    
    EXPECT_TRUE(mockVisitor.VisitExit(doc));
    EXPECT_FALSE(mockVisitor.VisitExit(doc));
    EXPECT_TRUE(mockVisitor.VisitExit(doc));
}
