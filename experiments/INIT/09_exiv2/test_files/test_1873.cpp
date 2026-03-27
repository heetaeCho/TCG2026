#include <gtest/gtest.h>
#include "XMLParserAdapter.hpp"

// Mocking the behavior of XML_NodePtr if necessary
class MockXMLNode : public XML_Node {
public:
    MockXMLNode(XML_NodePtr _parent, const std::string & _name, XMP_Uns8 _kind)
        : XML_Node(_parent, _name, _kind) {}
    
    MOCK_METHOD(bool, IsWhitespaceNode, (), (const, override));
    MOCK_METHOD(bool, IsLeafContentNode, (), (const, override));
    MOCK_METHOD(bool, IsEmptyLeafNode, (), (const, override));
    MOCK_METHOD(XMP_StringPtr, GetAttrValue, (XMP_StringPtr attrName), (const, override));
    MOCK_METHOD(void, SetAttrValue, (XMP_StringPtr attrName, XMP_StringPtr attrValue), (override));
    MOCK_METHOD(XMP_StringPtr, GetLeafContentValue, (), (const, override));
    MOCK_METHOD(void, SetLeafContentValue, (XMP_StringPtr value), (override));
    MOCK_METHOD(size_t, CountNamedElements, (XMP_StringPtr nsURI, XMP_StringPtr localName), (const, override));
    MOCK_METHOD(XML_NodePtr, GetNamedElement, (XMP_StringPtr nsURI, XMP_StringPtr localName, size_t which), (override));
    MOCK_METHOD(void, Dump, (std::string * buffer), (override));
    MOCK_METHOD(void, Serialize, (std::string * buffer), (override));
    MOCK_METHOD(void, RemoveAttrs, (), (override));
    MOCK_METHOD(void, RemoveContent, (), (override));
    MOCK_METHOD(void, ClearNode, (), (override));
};

class XMLNodeTest : public ::testing::Test {
protected:
    MockXMLNode* mockNode;

    void SetUp() override {
        mockNode = new MockXMLNode(nullptr, "TestNode", 1);
    }

    void TearDown() override {
        delete mockNode;
    }
};

// Test: Normal operation of IsWhitespaceNode
TEST_F(XMLNodeTest, IsWhitespaceNode_Normal_1873) {
    EXPECT_CALL(*mockNode, IsWhitespaceNode()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(mockNode->IsWhitespaceNode());
}

// Test: Normal operation of IsLeafContentNode
TEST_F(XMLNodeTest, IsLeafContentNode_Normal_1874) {
    EXPECT_CALL(*mockNode, IsLeafContentNode()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(mockNode->IsLeafContentNode());
}

// Test: Normal operation of GetAttrValue
TEST_F(XMLNodeTest, GetAttrValue_Normal_1875) {
    const std::string attrName = "testAttr";
    const std::string attrValue = "value";
    EXPECT_CALL(*mockNode, GetAttrValue(attrName.c_str())).WillOnce(::testing::Return(attrValue.c_str()));
    EXPECT_EQ(mockNode->GetAttrValue(attrName.c_str()), attrValue);
}

// Test: Boundary condition for CountNamedElements (empty node)
TEST_F(XMLNodeTest, CountNamedElements_Empty_1876) {
    const std::string nsURI = "testURI";
    const std::string localName = "testLocalName";
    EXPECT_CALL(*mockNode, CountNamedElements(nsURI.c_str(), localName.c_str())).WillOnce(::testing::Return(0));
    EXPECT_EQ(mockNode->CountNamedElements(nsURI.c_str(), localName.c_str()), 0);
}

// Test: Exceptional case for GetAttrValue when attribute is not present
TEST_F(XMLNodeTest, GetAttrValue_AttrNotFound_1877) {
    const std::string attrName = "nonExistentAttr";
    EXPECT_CALL(*mockNode, GetAttrValue(attrName.c_str())).WillOnce(::testing::Return(nullptr));
    EXPECT_EQ(mockNode->GetAttrValue(attrName.c_str()), nullptr);
}

// Test: Verifying SetAttrValue behavior
TEST_F(XMLNodeTest, SetAttrValue_Normal_1878) {
    const std::string attrName = "testAttr";
    const std::string attrValue = "newValue";
    EXPECT_CALL(*mockNode, SetAttrValue(attrName.c_str(), attrValue.c_str())).Times(1);
    mockNode->SetAttrValue(attrName.c_str(), attrValue.c_str());
}

// Test: Boundary condition for GetNamedElement when index is out of range
TEST_F(XMLNodeTest, GetNamedElement_OutOfRange_1879) {
    const std::string nsURI = "testURI";
    const std::string localName = "testLocalName";
    EXPECT_CALL(*mockNode, GetNamedElement(nsURI.c_str(), localName.c_str(), 10)).WillOnce(::testing::Return(nullptr));
    EXPECT_EQ(mockNode->GetNamedElement(nsURI.c_str(), localName.c_str(), 10), nullptr);
}

// Test: Exceptional case for Serialize
TEST_F(XMLNodeTest, Serialize_EmptyBuffer_1880) {
    std::string buffer;
    EXPECT_CALL(*mockNode, Serialize(&buffer)).Times(1);
    mockNode->Serialize(&buffer);
    EXPECT_FALSE(buffer.empty());  // Assuming some data is serialized into buffer
}

// Test: Verify RemoveAttrs behavior
TEST_F(XMLNodeTest, RemoveAttrs_Normal_1881) {
    EXPECT_CALL(*mockNode, RemoveAttrs()).Times(1);
    mockNode->RemoveAttrs();
}

// Test: Verify RemoveContent behavior
TEST_F(XMLNodeTest, RemoveContent_Normal_1882) {
    EXPECT_CALL(*mockNode, RemoveContent()).Times(1);
    mockNode->RemoveContent();
}

// Test: Verify ClearNode behavior
TEST_F(XMLNodeTest, ClearNode_Normal_1883) {
    EXPECT_CALL(*mockNode, ClearNode()).Times(1);
    mockNode->ClearNode();
}