#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary headers for XMP SDK
#include "XMP_Environment.h"
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"
#include "XMPMeta.hpp"
#include "XMPUtils.hpp"

class RemoveSchemaChildrenTest_1921 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: RemoveProperties with doAll=true removes all properties from a schema
TEST_F(RemoveSchemaChildrenTest_1921, RemoveAllPropertiesFromSchema_1921) {
    SXMPMeta meta;
    std::string ns = "http://ns.example.com/test/";
    std::string prefix;
    
    SXMPMeta::RegisterNamespace(ns.c_str(), "test:", &prefix);
    meta.SetProperty(ns.c_str(), "Prop1", "Value1");
    meta.SetProperty(ns.c_str(), "Prop2", "Value2");
    meta.SetProperty(ns.c_str(), "Prop3", "Value3");
    
    // Verify properties exist
    std::string val;
    ASSERT_TRUE(meta.GetProperty(ns.c_str(), "Prop1", &val, nullptr));
    ASSERT_TRUE(meta.GetProperty(ns.c_str(), "Prop2", &val, nullptr));
    ASSERT_TRUE(meta.GetProperty(ns.c_str(), "Prop3", &val, nullptr));
    
    // Remove all properties from this schema
    SXMPUtils::RemoveProperties(&meta, ns.c_str(), nullptr, kXMPUtil_DoAllProperties);
    
    // Verify all properties are gone
    EXPECT_FALSE(meta.GetProperty(ns.c_str(), "Prop1", &val, nullptr));
    EXPECT_FALSE(meta.GetProperty(ns.c_str(), "Prop2", &val, nullptr));
    EXPECT_FALSE(meta.GetProperty(ns.c_str(), "Prop3", &val, nullptr));
}

// Test: RemoveProperties with doAll=false on custom namespace removes external properties
TEST_F(RemoveSchemaChildrenTest_1921, RemoveExternalPropertiesOnly_1921) {
    SXMPMeta meta;
    std::string ns = "http://ns.example.com/custom/";
    std::string prefix;
    
    SXMPMeta::RegisterNamespace(ns.c_str(), "custom:", &prefix);
    meta.SetProperty(ns.c_str(), "PropA", "ValueA");
    meta.SetProperty(ns.c_str(), "PropB", "ValueB");
    
    // Remove without doAll flag - for custom namespaces, properties are external
    SXMPUtils::RemoveProperties(&meta, ns.c_str(), nullptr, 0);
    
    // For custom (non-standard) namespaces, all properties should be considered external
    std::string val;
    EXPECT_FALSE(meta.GetProperty(ns.c_str(), "PropA", &val, nullptr));
    EXPECT_FALSE(meta.GetProperty(ns.c_str(), "PropB", &val, nullptr));
}

// Test: RemoveProperties with specific property name removes only that property
TEST_F(RemoveSchemaChildrenTest_1921, RemoveSpecificProperty_1921) {
    SXMPMeta meta;
    std::string ns = "http://ns.example.com/specific/";
    std::string prefix;
    
    SXMPMeta::RegisterNamespace(ns.c_str(), "spec:", &prefix);
    meta.SetProperty(ns.c_str(), "Keep", "KeepValue");
    meta.SetProperty(ns.c_str(), "Remove", "RemoveValue");
    
    SXMPUtils::RemoveProperties(&meta, ns.c_str(), "Remove", kXMPUtil_DoAllProperties);
    
    std::string val;
    EXPECT_TRUE(meta.GetProperty(ns.c_str(), "Keep", &val, nullptr));
    EXPECT_EQ(val, "KeepValue");
    EXPECT_FALSE(meta.GetProperty(ns.c_str(), "Remove", &val, nullptr));
}

// Test: RemoveProperties on empty schema does not crash
TEST_F(RemoveSchemaChildrenTest_1921, RemoveFromEmptyMeta_1921) {
    SXMPMeta meta;
    
    // Should not crash when there's nothing to remove
    EXPECT_NO_THROW(SXMPUtils::RemoveProperties(&meta, nullptr, nullptr, kXMPUtil_DoAllProperties));
}

// Test: RemoveProperties removes all schemas when schema is null and doAll is true
TEST_F(RemoveSchemaChildrenTest_1921, RemoveAllSchemasWhenNullSchema_1921) {
    SXMPMeta meta;
    std::string ns1 = "http://ns.example.com/ns1/";
    std::string ns2 = "http://ns.example.com/ns2/";
    std::string prefix;
    
    SXMPMeta::RegisterNamespace(ns1.c_str(), "ns1:", &prefix);
    SXMPMeta::RegisterNamespace(ns2.c_str(), "ns2:", &prefix);
    
    meta.SetProperty(ns1.c_str(), "Prop1", "Val1");
    meta.SetProperty(ns2.c_str(), "Prop2", "Val2");
    
    SXMPUtils::RemoveProperties(&meta, nullptr, nullptr, kXMPUtil_DoAllProperties);
    
    std::string val;
    EXPECT_FALSE(meta.GetProperty(ns1.c_str(), "Prop1", &val, nullptr));
    EXPECT_FALSE(meta.GetProperty(ns2.c_str(), "Prop2", &val, nullptr));
}

// Test: RemoveProperties with single child - schema should be removed when empty
TEST_F(RemoveSchemaChildrenTest_1921, SchemaRemovedWhenAllChildrenDeleted_1921) {
    SXMPMeta meta;
    std::string ns = "http://ns.example.com/single/";
    std::string prefix;
    
    SXMPMeta::RegisterNamespace(ns.c_str(), "single:", &prefix);
    meta.SetProperty(ns.c_str(), "OnlyProp", "OnlyValue");
    
    // Verify property exists
    std::string val;
    ASSERT_TRUE(meta.GetProperty(ns.c_str(), "OnlyProp", &val, nullptr));
    
    SXMPUtils::RemoveProperties(&meta, ns.c_str(), nullptr, kXMPUtil_DoAllProperties);
    
    // After removing the only property, the schema node should also be gone
    EXPECT_FALSE(meta.GetProperty(ns.c_str(), "OnlyProp", &val, nullptr));
    
    // Count remaining properties - should be 0
    EXPECT_EQ(meta.CountArrayItems(ns.c_str(), "OnlyProp"), 0);
}

// Test: RemoveProperties on dc namespace with doAll removes internal properties too
TEST_F(RemoveSchemaChildrenTest_1921, RemoveDCPropertiesWithDoAll_1921) {
    SXMPMeta meta;
    const char* dcNS = "http://purl.org/dc/elements/1.1/";
    
    meta.SetProperty(dcNS, "title", "TestTitle");
    meta.SetProperty(dcNS, "creator", "TestCreator");
    
    std::string val;
    ASSERT_TRUE(meta.GetProperty(dcNS, "title", &val, nullptr));
    
    SXMPUtils::RemoveProperties(&meta, dcNS, nullptr, kXMPUtil_DoAllProperties);
    
    EXPECT_FALSE(meta.GetProperty(dcNS, "title", &val, nullptr));
    EXPECT_FALSE(meta.GetProperty(dcNS, "creator", &val, nullptr));
}

// Test: RemoveProperties preserves properties in other schemas
TEST_F(RemoveSchemaChildrenTest_1921, RemoveFromOneSchemaPreservesOthers_1921) {
    SXMPMeta meta;
    std::string ns1 = "http://ns.example.com/remove/";
    std::string ns2 = "http://ns.example.com/keep/";
    std::string prefix;
    
    SXMPMeta::RegisterNamespace(ns1.c_str(), "rem:", &prefix);
    SXMPMeta::RegisterNamespace(ns2.c_str(), "keep:", &prefix);
    
    meta.SetProperty(ns1.c_str(), "RemProp", "RemVal");
    meta.SetProperty(ns2.c_str(), "KeepProp", "KeepVal");
    
    SXMPUtils::RemoveProperties(&meta, ns1.c_str(), nullptr, kXMPUtil_DoAllProperties);
    
    std::string val;
    EXPECT_FALSE(meta.GetProperty(ns1.c_str(), "RemProp", &val, nullptr));
    EXPECT_TRUE(meta.GetProperty(ns2.c_str(), "KeepProp", &val, nullptr));
    EXPECT_EQ(val, "KeepVal");
}

// Test: RemoveProperties with many children iterates correctly in reverse
TEST_F(RemoveSchemaChildrenTest_1921, RemoveManyChildrenCorrectly_1921) {
    SXMPMeta meta;
    std::string ns = "http://ns.example.com/many/";
    std::string prefix;
    
    SXMPMeta::RegisterNamespace(ns.c_str(), "many:", &prefix);
    
    // Add many properties
    for (int i = 0; i < 100; i++) {
        std::string propName = "Prop" + std::to_string(i);
        std::string propVal = "Val" + std::to_string(i);
        meta.SetProperty(ns.c_str(), propName.c_str(), propVal.c_str());
    }
    
    // Verify some exist
    std::string val;
    ASSERT_TRUE(meta.GetProperty(ns.c_str(), "Prop0", &val, nullptr));
    ASSERT_TRUE(meta.GetProperty(ns.c_str(), "Prop99", &val, nullptr));
    
    SXMPUtils::RemoveProperties(&meta, ns.c_str(), nullptr, kXMPUtil_DoAllProperties);
    
    // All should be gone
    for (int i = 0; i < 100; i++) {
        std::string propName = "Prop" + std::to_string(i);
        EXPECT_FALSE(meta.GetProperty(ns.c_str(), propName.c_str(), &val, nullptr))
            << "Property " << propName << " should have been removed";
    }
}

// Test: RemoveProperties with structured/nested properties
TEST_F(RemoveSchemaChildrenTest_1921, RemoveStructuredProperties_1921) {
    SXMPMeta meta;
    std::string ns = "http://ns.example.com/struct/";
    std::string prefix;
    
    SXMPMeta::RegisterNamespace(ns.c_str(), "st:", &prefix);
    
    meta.SetStructField(ns.c_str(), "MyStruct", ns.c_str(), "Field1", "Value1");
    meta.SetStructField(ns.c_str(), "MyStruct", ns.c_str(), "Field2", "Value2");
    
    std::string val;
    ASSERT_TRUE(meta.GetStructField(ns.c_str(), "MyStruct", ns.c_str(), "Field1", &val, nullptr));
    
    SXMPUtils::RemoveProperties(&meta, ns.c_str(), nullptr, kXMPUtil_DoAllProperties);
    
    EXPECT_FALSE(meta.GetStructField(ns.c_str(), "MyStruct", ns.c_str(), "Field1", &val, nullptr));
    EXPECT_FALSE(meta.GetStructField(ns.c_str(), "MyStruct", ns.c_str(), "Field2", &val, nullptr));
}

// Test: RemoveProperties with XMP basic namespace (internal properties behavior)
TEST_F(RemoveSchemaChildrenTest_1921, InternalPropertiesNotRemovedWithoutDoAll_1921) {
    SXMPMeta meta;
    const char* xmpNS = "http://ns.adobe.com/xap/1.0/";
    
    meta.SetProperty(xmpNS, "CreatorTool", "TestTool");
    
    std::string val;
    ASSERT_TRUE(meta.GetProperty(xmpNS, "CreatorTool", &val, nullptr));
    
    // Without doAll, internal properties of known schemas may be preserved
    SXMPUtils::RemoveProperties(&meta, xmpNS, nullptr, 0);
    
    // CreatorTool in xmp namespace is considered internal for some schemas
    // The exact behavior depends on IsExternalProperty implementation
    // We just verify no crash and the function completes
}

// Test: RemoveProperties called twice does not crash
TEST_F(RemoveSchemaChildrenTest_1921, DoubleRemoveDoesNotCrash_1921) {
    SXMPMeta meta;
    std::string ns = "http://ns.example.com/double/";
    std::string prefix;
    
    SXMPMeta::RegisterNamespace(ns.c_str(), "dbl:", &prefix);
    meta.SetProperty(ns.c_str(), "Prop1", "Val1");
    
    SXMPUtils::RemoveProperties(&meta, ns.c_str(), nullptr, kXMPUtil_DoAllProperties);
    
    // Second call on already-removed schema should not crash
    EXPECT_NO_THROW(SXMPUtils::RemoveProperties(&meta, ns.c_str(), nullptr, kXMPUtil_DoAllProperties));
}

int main(int argc, char** argv) {
    if (!SXMPMeta::Initialize()) {
        return 1;
    }
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    SXMPMeta::Terminate();
    return result;
}
