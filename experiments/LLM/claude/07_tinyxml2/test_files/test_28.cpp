#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Mock visitor to test the default behavior and override behavior
class MockXMLVisitor : public XMLVisitor {
public:
    MOCK_METHOD(bool, VisitEnter, (const XMLElement& element, const XMLAttribute* firstAttribute), (override));
};

// Test fixture
class XMLVisitorTest_28 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that the default implementation of VisitEnter returns true
TEST_F(XMLVisitorTest_28, DefaultVisitEnterReturnsTrue_28) {
    XMLVisitor visitor;
    
    // We need an XMLElement to pass. Create a document and parse minimal XML.
    XMLDocument doc;
    doc.Parse("<root attr=\"value\"/>");
    const XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);
    
    const XMLAttribute* firstAttr = element->FirstAttribute();
    
    bool result = visitor.VisitEnter(*element, firstAttr);
    EXPECT_TRUE(result);
}

// Test that the default VisitEnter returns true with nullptr attribute
TEST_F(XMLVisitorTest_28, DefaultVisitEnterWithNullAttributeReturnsTrue_28) {
    XMLVisitor visitor;
    
    XMLDocument doc;
    doc.Parse("<root/>");
    const XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);
    
    bool result = visitor.VisitEnter(*element, nullptr);
    EXPECT_TRUE(result);
}

// Test that a mock can override VisitEnter and return false
TEST_F(XMLVisitorTest_28, MockVisitEnterCanReturnFalse_28) {
    MockXMLVisitor mockVisitor;
    
    XMLDocument doc;
    doc.Parse("<root/>");
    const XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);
    
    EXPECT_CALL(mockVisitor, VisitEnter(::testing::_, ::testing::_))
        .WillOnce(::testing::Return(false));
    
    bool result = mockVisitor.VisitEnter(*element, nullptr);
    EXPECT_FALSE(result);
}

// Test that a mock can override VisitEnter and return true
TEST_F(XMLVisitorTest_28, MockVisitEnterCanReturnTrue_28) {
    MockXMLVisitor mockVisitor;
    
    XMLDocument doc;
    doc.Parse("<elem key=\"val\"/>");
    const XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);
    const XMLAttribute* attr = element->FirstAttribute();
    
    EXPECT_CALL(mockVisitor, VisitEnter(::testing::_, attr))
        .WillOnce(::testing::Return(true));
    
    bool result = mockVisitor.VisitEnter(*element, attr);
    EXPECT_TRUE(result);
}

// Test that default VisitEnter works with element having multiple attributes
TEST_F(XMLVisitorTest_28, DefaultVisitEnterWithMultipleAttributes_28) {
    XMLVisitor visitor;
    
    XMLDocument doc;
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    const XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);
    
    const XMLAttribute* firstAttr = element->FirstAttribute();
    ASSERT_NE(firstAttr, nullptr);
    
    bool result = visitor.VisitEnter(*element, firstAttr);
    EXPECT_TRUE(result);
}

// Test that Accept on an element calls VisitEnter on the visitor
TEST_F(XMLVisitorTest_28, AcceptCallsVisitEnter_28) {
    MockXMLVisitor mockVisitor;
    
    XMLDocument doc;
    doc.Parse("<root/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);
    
    // When Accept is called on the element, it should invoke VisitEnter
    EXPECT_CALL(mockVisitor, VisitEnter(::testing::_, ::testing::_))
        .WillOnce(::testing::Return(true));
    
    element->Accept(&mockVisitor);
}

// Test default visitor with deeply nested element
TEST_F(XMLVisitorTest_28, DefaultVisitEnterWithNestedElement_28) {
    XMLVisitor visitor;
    
    XMLDocument doc;
    doc.Parse("<root><child><grandchild/></child></root>");
    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    const XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    const XMLElement* grandchild = child->FirstChildElement("grandchild");
    ASSERT_NE(grandchild, nullptr);
    
    EXPECT_TRUE(visitor.VisitEnter(*root, nullptr));
    EXPECT_TRUE(visitor.VisitEnter(*child, nullptr));
    EXPECT_TRUE(visitor.VisitEnter(*grandchild, nullptr));
}

// Test that the mock receives correct attribute pointer
TEST_F(XMLVisitorTest_28, MockReceivesCorrectAttributePointer_28) {
    MockXMLVisitor mockVisitor;
    
    XMLDocument doc;
    doc.Parse("<item id=\"42\"/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);
    const XMLAttribute* expectedAttr = element->FirstAttribute();
    ASSERT_NE(expectedAttr, nullptr);
    
    EXPECT_CALL(mockVisitor, VisitEnter(::testing::_, expectedAttr))
        .WillOnce(::testing::Return(true));
    
    element->Accept(&mockVisitor);
}
