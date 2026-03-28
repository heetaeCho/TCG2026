#include <gtest/gtest.h>
#include <string>

// Include the necessary XMP SDK headers
#define XMP_INCLUDE_XMPFILES 0
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "XMPCore_Impl.hpp"

// Common test namespace URIs
static const char* kTestNS = "http://ns.test.com/test/";
static const char* kTestPrefix = "test:";
static const char* kDcNS = "http://purl.org/dc/elements/1.1/";

class XMPMetaPropertyTest_1984 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize the XMP toolkit
        XMPMeta::Initialize();
        // Register test namespace
        XMPMeta::RegisterNamespace(kTestNS, kTestPrefix);
    }

    void TearDown() override {
        XMPMeta::Terminate();
    }
};

// Test setting and getting a simple property
TEST_F(XMPMetaPropertyTest_1984, SetAndGetProperty_1984) {
    XMPMeta meta;
    meta.SetProperty(kTestNS, "TestProp", "TestValue", 0);

    XMP_StringPtr value = nullptr;
    XMP_StringLen valueLen = 0;
    XMP_OptionBits options = 0;
    bool found = meta.GetProperty(kTestNS, "TestProp", &value, &valueLen, &options);

    EXPECT_TRUE(found);
    EXPECT_STREQ(value, "TestValue");
}

// Test DoesPropertyExist for an existing property
TEST_F(XMPMetaPropertyTest_1984, DoesPropertyExistTrue_1984) {
    XMPMeta meta;
    meta.SetProperty(kTestNS, "ExistProp", "SomeValue", 0);

    EXPECT_TRUE(meta.DoesPropertyExist(kTestNS, "ExistProp"));
}

// Test DoesPropertyExist for a non-existing property
TEST_F(XMPMetaPropertyTest_1984, DoesPropertyExistFalse_1984) {
    XMPMeta meta;
    EXPECT_FALSE(meta.DoesPropertyExist(kTestNS, "NonExistProp"));
}

// Test deleting a property
TEST_F(XMPMetaPropertyTest_1984, DeleteProperty_1984) {
    XMPMeta meta;
    meta.SetProperty(kTestNS, "DelProp", "Value", 0);
    EXPECT_TRUE(meta.DoesPropertyExist(kTestNS, "DelProp"));

    meta.DeleteProperty(kTestNS, "DelProp");
    EXPECT_FALSE(meta.DoesPropertyExist(kTestNS, "DelProp"));
}

// Test that deleting a non-existing property does not crash
TEST_F(XMPMetaPropertyTest_1984, DeleteNonExistingProperty_1984) {
    XMPMeta meta;
    EXPECT_NO_THROW(meta.DeleteProperty(kTestNS, "NoProp"));
}

// Test setting property overwrites existing value
TEST_F(XMPMetaPropertyTest_1984, SetPropertyOverwrite_1984) {
    XMPMeta meta;
    meta.SetProperty(kTestNS, "OverProp", "First", 0);
    meta.SetProperty(kTestNS, "OverProp", "Second", 0);

    XMP_StringPtr value = nullptr;
    XMP_StringLen valueLen = 0;
    bool found = meta.GetProperty(kTestNS, "OverProp", &value, &valueLen, nullptr);
    EXPECT_TRUE(found);
    EXPECT_STREQ(value, "Second");
}

// Test getting property from wrong namespace returns false
TEST_F(XMPMetaPropertyTest_1984, GetPropertyWrongNamespace_1984) {
    XMPMeta meta;
    meta.SetProperty(kTestNS, "NSProp", "Value", 0);

    XMP_StringPtr value = nullptr;
    XMP_StringLen valueLen = 0;
    bool found = meta.GetProperty(kDcNS, "NSProp", &value, &valueLen, nullptr);
    EXPECT_FALSE(found);
}

// Test Erase clears all properties
TEST_F(XMPMetaPropertyTest_1984, EraseRemovesProperties_1984) {
    XMPMeta meta;
    meta.SetProperty(kTestNS, "Prop1", "Val1", 0);
    meta.SetProperty(kTestNS, "Prop2", "Val2", 0);

    meta.Erase();

    EXPECT_FALSE(meta.DoesPropertyExist(kTestNS, "Prop1"));
    EXPECT_FALSE(meta.DoesPropertyExist(kTestNS, "Prop2"));
}

// Test Clone copies properties
TEST_F(XMPMetaPropertyTest_1984, CloneCopiesProperties_1984) {
    XMPMeta meta;
    meta.SetProperty(kTestNS, "CloneProp", "CloneVal", 0);

    XMPMeta cloned;
    meta.Clone(&cloned, 0);

    XMP_StringPtr value = nullptr;
    XMP_StringLen valueLen = 0;
    bool found = cloned.GetProperty(kTestNS, "CloneProp", &value, &valueLen, nullptr);
    EXPECT_TRUE(found);
    EXPECT_STREQ(value, "CloneVal");
}

// Test modifying clone does not affect original
TEST_F(XMPMetaPropertyTest_1984, CloneIndependence_1984) {
    XMPMeta meta;
    meta.SetProperty(kTestNS, "IndProp", "Original", 0);

    XMPMeta cloned;
    meta.Clone(&cloned, 0);

    cloned.SetProperty(kTestNS, "IndProp", "Modified", 0);

    XMP_StringPtr value = nullptr;
    XMP_StringLen valueLen = 0;
    meta.GetProperty(kTestNS, "IndProp", &value, &valueLen, nullptr);
    EXPECT_STREQ(value, "Original");
}

// Test setting a boolean property
TEST_F(XMPMetaPropertyTest_1984, SetAndGetBoolProperty_1984) {
    XMPMeta meta;
    meta.SetProperty_Bool(kTestNS, "BoolProp", true, 0);

    bool boolVal = false;
    XMP_OptionBits opts = 0;
    bool found = meta.GetProperty_Bool(kTestNS, "BoolProp", &boolVal, &opts);
    EXPECT_TRUE(found);
    EXPECT_TRUE(boolVal);
}

// Test setting an integer property
TEST_F(XMPMetaPropertyTest_1984, SetAndGetIntProperty_1984) {
    XMPMeta meta;
    meta.SetProperty_Int(kTestNS, "IntProp", 42, 0);

    XMP_Int32 intVal = 0;
    XMP_OptionBits opts = 0;
    bool found = meta.GetProperty_Int(kTestNS, "IntProp", &intVal, &opts);
    EXPECT_TRUE(found);
    EXPECT_EQ(intVal, 42);
}

// Test setting a float property
TEST_F(XMPMetaPropertyTest_1984, SetAndGetFloatProperty_1984) {
    XMPMeta meta;
    meta.SetProperty_Float(kTestNS, "FloatProp", 3.14, 0);

    double floatVal = 0.0;
    XMP_OptionBits opts = 0;
    bool found = meta.GetProperty_Float(kTestNS, "FloatProp", &floatVal, &opts);
    EXPECT_TRUE(found);
    EXPECT_NEAR(floatVal, 3.14, 0.001);
}

// Test setting an Int64 property
TEST_F(XMPMetaPropertyTest_1984, SetAndGetInt64Property_1984) {
    XMPMeta meta;
    XMP_Int64 bigVal = 9876543210LL;
    meta.SetProperty_Int64(kTestNS, "Int64Prop", bigVal, 0);

    XMP_Int64 result = 0;
    XMP_OptionBits opts = 0;
    bool found = meta.GetProperty_Int64(kTestNS, "Int64Prop", &result, &opts);
    EXPECT_TRUE(found);
    EXPECT_EQ(result, bigVal);
}

// Test empty property value
TEST_F(XMPMetaPropertyTest_1984, EmptyPropertyValue_1984) {
    XMPMeta meta;
    meta.SetProperty(kTestNS, "EmptyProp", "", 0);

    XMP_StringPtr value = nullptr;
    XMP_StringLen valueLen = 0;
    bool found = meta.GetProperty(kTestNS, "EmptyProp", &value, &valueLen, nullptr);
    EXPECT_TRUE(found);
    EXPECT_STREQ(value, "");
    EXPECT_EQ(valueLen, 0u);
}

// Test multiple properties in same namespace
TEST_F(XMPMetaPropertyTest_1984, MultiplePropertiesSameNS_1984) {
    XMPMeta meta;
    meta.SetProperty(kTestNS, "Prop1", "Val1", 0);
    meta.SetProperty(kTestNS, "Prop2", "Val2", 0);
    meta.SetProperty(kTestNS, "Prop3", "Val3", 0);

    EXPECT_TRUE(meta.DoesPropertyExist(kTestNS, "Prop1"));
    EXPECT_TRUE(meta.DoesPropertyExist(kTestNS, "Prop2"));
    EXPECT_TRUE(meta.DoesPropertyExist(kTestNS, "Prop3"));
}

// Test deleting one property doesn't affect others
TEST_F(XMPMetaPropertyTest_1984, DeleteOnePropertyLeavesOthers_1984) {
    XMPMeta meta;
    meta.SetProperty(kTestNS, "Keep1", "A", 0);
    meta.SetProperty(kTestNS, "Remove", "B", 0);
    meta.SetProperty(kTestNS, "Keep2", "C", 0);

    meta.DeleteProperty(kTestNS, "Remove");

    EXPECT_TRUE(meta.DoesPropertyExist(kTestNS, "Keep1"));
    EXPECT_FALSE(meta.DoesPropertyExist(kTestNS, "Remove"));
    EXPECT_TRUE(meta.DoesPropertyExist(kTestNS, "Keep2"));
}

// Test object name
TEST_F(XMPMetaPropertyTest_1984, SetAndGetObjectName_1984) {
    XMPMeta meta;
    meta.SetObjectName("TestObject");

    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    meta.GetObjectName(&namePtr, &nameLen);

    EXPECT_STREQ(namePtr, "TestObject");
}

// Test struct field set and get
TEST_F(XMPMetaPropertyTest_1984, SetAndGetStructField_1984) {
    XMPMeta meta;
    meta.SetStructField(kTestNS, "MyStruct", kTestNS, "Field1", "FieldValue", 0);

    XMP_StringPtr value = nullptr;
    XMP_StringLen valueLen = 0;
    XMP_OptionBits opts = 0;
    bool found = meta.GetStructField(kTestNS, "MyStruct", kTestNS, "Field1", &value, &valueLen, &opts);
    EXPECT_TRUE(found);
    EXPECT_STREQ(value, "FieldValue");
}

// Test getting a non-existing bool property returns false
TEST_F(XMPMetaPropertyTest_1984, GetNonExistingBoolProperty_1984) {
    XMPMeta meta;
    bool boolVal = true;
    XMP_OptionBits opts = 0;
    bool found = meta.GetProperty_Bool(kTestNS, "NoBool", &boolVal, &opts);
    EXPECT_FALSE(found);
}

// Test getting a non-existing int property returns false
TEST_F(XMPMetaPropertyTest_1984, GetNonExistingIntProperty_1984) {
    XMPMeta meta;
    XMP_Int32 intVal = 999;
    XMP_OptionBits opts = 0;
    bool found = meta.GetProperty_Int(kTestNS, "NoInt", &intVal, &opts);
    EXPECT_FALSE(found);
}

// Test default constructed XMPMeta has no properties
TEST_F(XMPMetaPropertyTest_1984, DefaultConstructedEmpty_1984) {
    XMPMeta meta;
    EXPECT_FALSE(meta.DoesPropertyExist(kTestNS, "AnyProp"));
}

// Test XMP_Node construction
TEST(XMPNodeTest_1984, NodeConstruction_1984) {
    XMP_Node root(nullptr, "root", 0);
    EXPECT_EQ(root.name, "root");
    EXPECT_EQ(root.parent, nullptr);
    EXPECT_TRUE(root.children.empty());
    EXPECT_TRUE(root.qualifiers.empty());
}

// Test XMP_Node with value construction
TEST(XMPNodeTest_1984, NodeWithValueConstruction_1984) {
    XMP_Node root(nullptr, "root", "rootValue", 0);
    EXPECT_EQ(root.name, "root");
    EXPECT_EQ(root.value, "rootValue");
    EXPECT_EQ(root.parent, nullptr);
}

// Test XMP_Node RemoveChildren
TEST(XMPNodeTest_1984, RemoveChildren_1984) {
    XMP_Node parent(nullptr, "parent", 0);
    XMP_Node* child = new XMP_Node(&parent, "child", 0);
    parent.children.push_back(child);

    EXPECT_EQ(parent.children.size(), 1u);
    parent.RemoveChildren();
    EXPECT_TRUE(parent.children.empty());
}

// Test XMP_Node ClearNode
TEST(XMPNodeTest_1984, ClearNode_1984) {
    XMP_Node node(nullptr, "node", "value", 0);
    XMP_Node* child = new XMP_Node(&node, "child", 0);
    node.children.push_back(child);

    node.ClearNode();
    EXPECT_TRUE(node.children.empty());
    EXPECT_TRUE(node.qualifiers.empty());
}
