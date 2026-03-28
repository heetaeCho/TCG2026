#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// Mock dependencies
class MockXMP_Node : public XMP_Node {
public:
    MockXMP_Node(XMP_Node* parent, XMP_VarString name, XMP_OptionBits options)
        : XMP_Node(parent, name, options) {}
    
    MOCK_METHOD(void, RemoveChildren, (), (override));
    MOCK_METHOD(void, RemoveQualifiers, (), (override));
    MOCK_METHOD(void, ClearNode, (), (override));
    MOCK_METHOD(~XMP_Node, Destructor, (), (override));
};

// Test fixture for LookupLangItem function
class LookupLangItemTest : public ::testing::Test {
protected:
    // Helper function to create a sample XMP_Node with lang qualifiers
    XMP_Node* CreateNodeWithLang(const std::string& lang) {
        // Create mock node
        XMP_VarString langString(lang.c_str());
        XMP_Node* parentNode = new XMP_Node(nullptr, "root", 0);
        XMP_Node* langNode = new XMP_Node(parentNode, "item", 0);
        XMP_Node* qualifierNode = new XMP_Node(langNode, "xml:lang", langString, 0);
        
        langNode->qualifiers.push_back(qualifierNode);
        parentNode->children.push_back(langNode);

        return parentNode;
    }
};

// Normal operation: lang exists
TEST_F(LookupLangItemTest, LookupLangItem_Found_1898) {
    XMP_Node* arrayNode = CreateNodeWithLang("en");
    XMP_VarString lang("en");

    // Test the behavior of LookupLangItem
    XMP_Index result = LookupLangItem(arrayNode, lang);
    
    EXPECT_EQ(result, 0);  // First item should match

    // Clean up
    delete arrayNode;
}

// Normal operation: lang does not exist
TEST_F(LookupLangItemTest, LookupLangItem_NotFound_1899) {
    XMP_Node* arrayNode = CreateNodeWithLang("fr");
    XMP_VarString lang("en");

    // Test the behavior when the lang is not found
    XMP_Index result = LookupLangItem(arrayNode, lang);
    
    EXPECT_EQ(result, -1);  // Lang not found should return -1

    // Clean up
    delete arrayNode;
}

// Boundary condition: empty arrayNode
TEST_F(LookupLangItemTest, LookupLangItem_EmptyArray_1900) {
    XMP_Node* arrayNode = new XMP_Node(nullptr, "root", 0);  // No children
    XMP_VarString lang("en");

    // Test the behavior when the node is empty
    XMP_Index result = LookupLangItem(arrayNode, lang);
    
    EXPECT_EQ(result, -1);  // Should return -1 since there are no items

    // Clean up
    delete arrayNode;
}

// Exceptional case: Invalid arrayNode (not an array)
TEST_F(LookupLangItemTest, LookupLangItem_NotArray_1901) {
    XMP_Node* arrayNode = new XMP_Node(nullptr, "item", 0);  // Not marked as an array
    XMP_VarString lang("en");

    // Test the behavior when the node is not an array
    EXPECT_THROW(LookupLangItem(arrayNode, lang), std::runtime_error);  // Expecting exception

    // Clean up
    delete arrayNode;
}