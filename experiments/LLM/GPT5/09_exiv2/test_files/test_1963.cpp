#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPMeta-Parse.h"
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

using namespace ::testing;

// Mock the XMP_Node for dependency injection (if needed)
class MockXMPNode : public XMP_Node {
public:
    MockXMPNode(XMP_Node* parent, const XMP_VarString& name, XMP_OptionBits options)
        : XMP_Node(parent, name, options) {}
    MOCK_METHOD(void, SetOptions, (XMP_OptionBits options), ());
    MOCK_METHOD(void, AddQualifier, (XMP_Node* qualifier), ());
};

// Test case for normal operation (no errors)
TEST_F(XMPMetaTest_1963, TransplantArrayItemAlias_NormalOperation) {
    // Arrange
    XMP_Node* oldParent = new XMP_Node(nullptr, "oldParent", 0);
    XMP_Node* newParent = new XMP_Node(nullptr, "newParent", 0);
    XMP_Node* childNode = new XMP_Node(oldParent, "childNode", 0);
    
    oldParent->children.push_back(childNode);

    // Act
    TransplantArrayItemAlias(oldParent, 0, newParent);

    // Assert
    ASSERT_EQ(newParent->children.size(), 1);
    EXPECT_EQ(newParent->children.front()->parent, newParent);
    EXPECT_EQ(oldParent->children.size(), 0);
}

// Test case for handling language qualifiers (edge case for x-default language)
TEST_F(XMPMetaTest_1963, TransplantArrayItemAlias_WithLanguageQualifier) {
    // Arrange
    XMP_Node* oldParent = new XMP_Node(nullptr, "oldParent", kXMP_PropArrayIsAltText);
    XMP_Node* newParent = new XMP_Node(nullptr, "newParent", kXMP_PropArrayIsAltText);
    XMP_Node* childNode = new XMP_Node(oldParent, "childNode", kXMP_PropHasLang);
    
    oldParent->children.push_back(childNode);

    // Act
    TransplantArrayItemAlias(oldParent, 0, newParent);

    // Assert
    ASSERT_EQ(newParent->children.size(), 1);
    EXPECT_TRUE(childNode->options & kXMP_PropHasLang);
    EXPECT_EQ(newParent->children.front()->qualifiers.size(), 1);
    EXPECT_EQ(newParent->children.front()->qualifiers.front()->name, "xml:lang");
}

// Test case for aliasing behavior (error case for already existing language qualifier)
TEST_F(XMPMetaTest_1963, TransplantArrayItemAlias_AliasWithExistingLang_Throws) {
    // Arrange
    XMP_Node* oldParent = new XMP_Node(nullptr, "oldParent", kXMP_PropArrayIsAltText);
    XMP_Node* newParent = new XMP_Node(nullptr, "newParent", kXMP_PropArrayIsAltText);
    XMP_Node* childNode = new XMP_Node(oldParent, "childNode", kXMP_PropHasLang | kXMP_PropIsQualifier);
    
    XMP_Node* langQual = new XMP_Node(childNode, "xml:lang", "x-default", kXMP_PropIsQualifier);
    childNode->qualifiers.push_back(langQual);
    oldParent->children.push_back(childNode);

    // Act and Assert
    EXPECT_THROW(TransplantArrayItemAlias(oldParent, 0, newParent), std::runtime_error);
}

// Test case for boundary conditions (empty parent-child relationships)
TEST_F(XMPMetaTest_1963, TransplantArrayItemAlias_EmptyParentChild) {
    // Arrange
    XMP_Node* oldParent = new XMP_Node(nullptr, "oldParent", 0);
    XMP_Node* newParent = new XMP_Node(nullptr, "newParent", 0);
    
    // Act
    TransplantArrayItemAlias(oldParent, 0, newParent);

    // Assert
    ASSERT_EQ(oldParent->children.size(), 0);
    ASSERT_EQ(newParent->children.size(), 0);
}

// Test case for exceptional error handling (invalid child node index)
TEST_F(XMPMetaTest_1963, TransplantArrayItemAlias_InvalidChildIndex_Throws) {
    // Arrange
    XMP_Node* oldParent = new XMP_Node(nullptr, "oldParent", 0);
    XMP_Node* newParent = new XMP_Node(nullptr, "newParent", 0);

    // Act and Assert
    EXPECT_THROW(TransplantArrayItemAlias(oldParent, 999, newParent), std::out_of_range);
}