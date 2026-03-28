#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/exiv2/xmpsdk/src/XMPMeta-GetSet.cpp"
#include "./TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "XMP_Const.h"

// Mock classes if needed
class MockXMP_Node : public XMP_Node {
public:
    MOCK_METHOD(void, RemoveChildren, (), (override));
    MOCK_METHOD(void, RemoveQualifiers, (), (override));
    MOCK_METHOD(void, ClearNode, (), (override));
};

class XMPMetaTest_1926 : public ::testing::Test {
protected:
    // You can set up common test fixtures here.
    void SetUp() override {
        // Setup any necessary mock behavior here.
    }

    void TearDown() override {
        // Clean up any resources after the test if needed.
    }
};

// Normal operation - Insert item at the end of the array
TEST_F(XMPMetaTest_1926, DoSetArrayItem_InsertItemAtEnd_1926) {
    XMP_Node parentNode(nullptr, "ParentNode", 0);
    XMP_Node arrayNode(&parentNode, "ArrayNode", 0);
    XMP_Index itemIndex = kXMP_ArrayLastItem;
    XMP_StringPtr itemValue = "NewItem";
    XMP_OptionBits options = kXMP_PropArrayLocationMask;

    // Mock setup for a node to be inserted
    EXPECT_CALL(*this, InsertItemAtEnd).Times(1);

    // Call the function
    DoSetArrayItem(&arrayNode, itemIndex, itemValue, options);

    // Verify the expected behavior (observable effect) here
    ASSERT_EQ(arrayNode.children.size(), 1);
    ASSERT_EQ(arrayNode.children[0]->name, "NewItem");
}

// Boundary conditions - Invalid index (out of bounds)
TEST_F(XMPMetaTest_1926, DoSetArrayItem_InvalidIndex_1926) {
    XMP_Node parentNode(nullptr, "ParentNode", 0);
    XMP_Node arrayNode(&parentNode, "ArrayNode", 0);
    XMP_Index itemIndex = 999; // Invalid index
    XMP_StringPtr itemValue = "InvalidItem";
    XMP_OptionBits options = 0;

    // Expect the function to throw an exception
    EXPECT_THROW(DoSetArrayItem(&arrayNode, itemIndex, itemValue, options), XMP_Error);
}

// Exceptional cases - Insert before item, exceeding size
TEST_F(XMPMetaTest_1926, DoSetArrayItem_InsertBeforeExceeding_1926) {
    XMP_Node parentNode(nullptr, "ParentNode", 0);
    XMP_Node arrayNode(&parentNode, "ArrayNode", 0);
    XMP_Index itemIndex = arrayNode.children.size() + 1;  // Exceeding the current size
    XMP_StringPtr itemValue = "ExceedingItem";
    XMP_OptionBits options = kXMP_InsertBeforeItem;

    // Expect exception when trying to insert before exceeding size
    EXPECT_THROW(DoSetArrayItem(&arrayNode, itemIndex, itemValue, options), XMP_Error);
}

// Boundary condition - Insert first item when empty
TEST_F(XMPMetaTest_1926, DoSetArrayItem_InsertFirstItem_1926) {
    XMP_Node parentNode(nullptr, "ParentNode", 0);
    XMP_Node arrayNode(&parentNode, "ArrayNode", 0);
    XMP_Index itemIndex = 1;  // First item index
    XMP_StringPtr itemValue = "FirstItem";
    XMP_OptionBits options = 0;

    // Call the function
    DoSetArrayItem(&arrayNode, itemIndex, itemValue, options);

    // Verify the new item is added as the first element
    ASSERT_EQ(arrayNode.children.size(), 1);
    ASSERT_EQ(arrayNode.children[0]->name, "FirstItem");
}

// Exceptional cases - Invalid item location (Can't insert before implicit item)
TEST_F(XMPMetaTest_1926, DoSetArrayItem_InvalidLocation_1926) {
    XMP_Node parentNode(nullptr, "ParentNode", 0);
    XMP_Node arrayNode(&parentNode, "ArrayNode", 0);
    XMP_Index itemIndex = arrayNode.children.size() + 1;
    XMP_StringPtr itemValue = "InvalidLocationItem";
    XMP_OptionBits options = kXMP_InsertBeforeItem;  // Invalid location

    // Expect exception due to invalid location
    EXPECT_THROW(DoSetArrayItem(&arrayNode, itemIndex, itemValue, options), XMP_Error);
}

// Normal operation - Insert after a specific item
TEST_F(XMPMetaTest_1926, DoSetArrayItem_InsertAfterItem_1926) {
    XMP_Node parentNode(nullptr, "ParentNode", 0);
    XMP_Node arrayNode(&parentNode, "ArrayNode", 0);
    XMP_Index itemIndex = 1;  // Insert after the first item
    XMP_StringPtr itemValue = "AfterItem";
    XMP_OptionBits options = kXMP_InsertAfterItem;

    // Insert first item
    DoSetArrayItem(&arrayNode, 1, "FirstItem", options);

    // Now insert after the first item
    DoSetArrayItem(&arrayNode, itemIndex, itemValue, options);

    // Verify that the new item was added after the first one
    ASSERT_EQ(arrayNode.children.size(), 2);
    ASSERT_EQ(arrayNode.children[1]->name, "AfterItem");
}