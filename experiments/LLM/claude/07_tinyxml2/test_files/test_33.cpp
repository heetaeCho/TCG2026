#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLVisitor tests
class XMLVisitorTest_33 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Mock visitor to test virtual method behavior
class MockXMLVisitor : public XMLVisitor {
public:
    MOCK_METHOD(bool, Visit, (const XMLUnknown&), (override));
};

// Test that default XMLVisitor::Visit(XMLUnknown) returns true
TEST_F(XMLVisitorTest_33, DefaultVisitUnknownReturnsTrue_33) {
    XMLVisitor visitor;
    // We need an XMLUnknown instance to pass to Visit.
    // Create an XML document with an unknown node to get one.
    XMLDocument doc;
    // Parse something that creates an XMLUnknown node
    // In XML, processing instructions or unrecognized constructs like <! ... > become XMLUnknown
    doc.Parse("<root><![unknown[test]]></root>");
    
    // Try another approach - use the document API to create unknown
    // XMLUnknown nodes are created from constructs like <!something>
    XMLDocument doc2;
    doc2.Parse("<!DOCTYPE root>");
    
    // Let's use the visitor pattern through the document
    // The default Visit should return true
    // We can test this by checking that Accept works with default visitor
    bool result = doc2.Accept(&visitor);
    // Default visitor methods return true, so traversal should complete successfully
    EXPECT_TRUE(result);
}

// Test that a full XML document can be visited with default XMLVisitor
TEST_F(XMLVisitorTest_33, DefaultVisitorAcceptsFullDocument_33) {
    XMLVisitor visitor;
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    ASSERT_FALSE(doc.Error());
    
    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test that MockXMLVisitor can override Visit behavior
TEST_F(XMLVisitorTest_33, MockVisitorCanOverrideVisitUnknown_33) {
    MockXMLVisitor mockVisitor;
    
    // When Visit is called with an XMLUnknown, we can control the return
    // We need to set default behavior for other visitor methods
    // The mock only overrides Visit(const XMLUnknown&)
    
    // For this test, just verify the mock can be set up
    EXPECT_CALL(mockVisitor, Visit(::testing::_))
        .WillRepeatedly(::testing::Return(false));
    
    XMLDocument doc;
    // Create a document with an unknown node
    // <! directives that aren't DOCTYPE, comments, etc. become XMLUnknown
    doc.Parse("<?xml version=\"1.0\"?><!DOCTYPE root><root/>");
    
    // Accept will call various visitor methods
    doc.Accept(&mockVisitor);
}

// Test default visitor with empty document
TEST_F(XMLVisitorTest_33, DefaultVisitorAcceptsEmptyDocument_33) {
    XMLVisitor visitor;
    XMLDocument doc;
    
    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test default visitor with complex XML
TEST_F(XMLVisitorTest_33, DefaultVisitorAcceptsComplexDocument_33) {
    XMLVisitor visitor;
    XMLDocument doc;
    const char* xml = 
        "<?xml version=\"1.0\"?>"
        "<!-- comment -->"
        "<root attr=\"value\">"
        "  <child1>text1</child1>"
        "  <child2>text2</child2>"
        "  <child3/>"
        "</root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    
    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test that XMLVisitor can be used as a base class pointer
TEST_F(XMLVisitorTest_33, VisitorPolymorphism_33) {
    MockXMLVisitor mockVisitor;
    XMLVisitor* basePtr = &mockVisitor;
    
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());
    
    bool result = doc.Accept(basePtr);
    // Should complete without error
    EXPECT_TRUE(result);
}

// Test visitor with document containing text nodes
TEST_F(XMLVisitorTest_33, DefaultVisitorHandlesTextNodes_33) {
    XMLVisitor visitor;
    XMLDocument doc;
    doc.Parse("<root>Hello World</root>");
    ASSERT_FALSE(doc.Error());
    
    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test visitor with document containing CDATA
TEST_F(XMLVisitorTest_33, DefaultVisitorHandlesCDATA_33) {
    XMLVisitor visitor;
    XMLDocument doc;
    doc.Parse("<root><![CDATA[Some <special> data]]></root>");
    ASSERT_FALSE(doc.Error());
    
    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test visitor with nested elements
TEST_F(XMLVisitorTest_33, DefaultVisitorHandlesDeeplyNestedElements_33) {
    XMLVisitor visitor;
    XMLDocument doc;
    doc.Parse("<a><b><c><d><e>deep</e></d></c></b></a>");
    ASSERT_FALSE(doc.Error());
    
    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test that multiple visits on the same document work
TEST_F(XMLVisitorTest_33, MultipleVisitsOnSameDocument_33) {
    XMLVisitor visitor;
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());
    
    bool result1 = doc.Accept(&visitor);
    bool result2 = doc.Accept(&visitor);
    
    EXPECT_TRUE(result1);
    EXPECT_TRUE(result2);
}
