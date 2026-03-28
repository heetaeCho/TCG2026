#include <gtest/gtest.h>
#include <string>
#include <vector>

// XMP SDK headers
#define TXMP_STRING_TYPE std::string
#include "XMP.hpp"
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"

// We need to test AppendSubtree indirectly through XMPUtils::ApplyTemplate
// since AppendSubtree is a static (file-local) function.

class AppendSubtreeTest_1923 : public ::testing::Test {
protected:
    void SetUp() override {
        SXMPMeta::Initialize();
    }
    
    void TearDown() override {
        SXMPMeta::Terminate();
    }
    
    static const char* kTestNS;
};

const char* AppendSubtreeTest_1923::kTestNS = "http://ns.test.com/test/";

// Test: ApplyTemplate with kXMPTemplate_AddNewProperties merges new simple property
TEST_F(AppendSubtreeTest_1923, AddNewSimpleProperty_1923) {
    SXMPMeta source;
    SXMPMeta dest;
    
    SXMPMeta::RegisterNamespace(kTestNS, "test", nullptr);
    
    source.SetProperty(kTestNS, "prop1", "value1");
    
    SXMPUtils::ApplyTemplate(&dest, source, kXMPTemplate_AddNewProperties);
    
    std::string value;
    EXPECT_TRUE(dest.GetProperty(kTestNS, "prop1", &value, nullptr));
    EXPECT_EQ("value1", value);
}

// Test: ApplyTemplate with kXMPTemplate_AddNewProperties does not replace existing property
TEST_F(AppendSubtreeTest_1923, DoNotReplaceExistingSimpleProperty_1923) {
    SXMPMeta source;
    SXMPMeta dest;
    
    SXMPMeta::RegisterNamespace(kTestNS, "test", nullptr);
    
    source.SetProperty(kTestNS, "prop1", "newValue");
    dest.SetProperty(kTestNS, "prop1", "oldValue");
    
    SXMPUtils::ApplyTemplate(&dest, source, kXMPTemplate_AddNewProperties);
    
    std::string value;
    EXPECT_TRUE(dest.GetProperty(kTestNS, "prop1", &value, nullptr));
    EXPECT_EQ("oldValue", value);
}

// Test: ApplyTemplate with kXMPTemplate_ReplaceExistingProperties replaces existing property
TEST_F(AppendSubtreeTest_1923, ReplaceExistingSimpleProperty_1923) {
    SXMPMeta source;
    SXMPMeta dest;
    
    SXMPMeta::RegisterNamespace(kTestNS, "test", nullptr);
    
    source.SetProperty(kTestNS, "prop1", "newValue");
    dest.SetProperty(kTestNS, "prop1", "oldValue");
    
    SXMPUtils::ApplyTemplate(&dest, source, 
        kXMPTemplate_AddNewProperties | kXMPTemplate_ReplaceExistingProperties);
    
    std::string value;
    EXPECT_TRUE(dest.GetProperty(kTestNS, "prop1", &value, nullptr));
    EXPECT_EQ("newValue", value);
}

// Test: ApplyTemplate with kXMPTemplate_ClearUnnamedProperties and empty source removes dest property
TEST_F(AppendSubtreeTest_1923, DeleteEmptySimpleProperty_1923) {
    SXMPMeta source;
    SXMPMeta dest;
    
    SXMPMeta::RegisterNamespace(kTestNS, "test", nullptr);
    
    source.SetProperty(kTestNS, "prop1", "");
    dest.SetProperty(kTestNS, "prop1", "existingValue");
    
    SXMPUtils::ApplyTemplate(&dest, source, 
        kXMPTemplate_AddNewProperties | kXMPTemplate_ReplaceExistingProperties | kXMPTemplate_ReplaceWithDeleteEmpty);
    
    std::string value;
    EXPECT_FALSE(dest.GetProperty(kTestNS, "prop1", &value, nullptr));
}

// Test: Merging struct properties - new fields added to existing struct
TEST_F(AppendSubtreeTest_1923, MergeStructAddNewField_1923) {
    SXMPMeta source;
    SXMPMeta dest;
    
    SXMPMeta::RegisterNamespace(kTestNS, "test", nullptr);
    
    source.SetStructField(kTestNS, "myStruct", kTestNS, "field1", "val1");
    source.SetStructField(kTestNS, "myStruct", kTestNS, "field2", "val2");
    
    dest.SetStructField(kTestNS, "myStruct", kTestNS, "field1", "existVal1");
    
    SXMPUtils::ApplyTemplate(&dest, source, kXMPTemplate_AddNewProperties);
    
    std::string value;
    // Existing field should be preserved (no replace)
    EXPECT_TRUE(dest.GetStructField(kTestNS, "myStruct", kTestNS, "field1", &value, nullptr));
    EXPECT_EQ("existVal1", value);
    
    // New field should be added
    EXPECT_TRUE(dest.GetStructField(kTestNS, "myStruct", kTestNS, "field2", &value, nullptr));
    EXPECT_EQ("val2", value);
}

// Test: Merging array properties - new items appended if not duplicate
TEST_F(AppendSubtreeTest_1923, MergeArrayAppendNonDuplicate_1923) {
    SXMPMeta source;
    SXMPMeta dest;
    
    SXMPMeta::RegisterNamespace(kTestNS, "test", nullptr);
    
    source.AppendArrayItem(kTestNS, "myArray", kXMP_PropArrayIsUnordered, "item1");
    source.AppendArrayItem(kTestNS, "myArray", kXMP_PropArrayIsUnordered, "item2");
    
    dest.AppendArrayItem(kTestNS, "myArray", kXMP_PropArrayIsUnordered, "item1");
    
    SXMPUtils::ApplyTemplate(&dest, source, kXMPTemplate_AddNewProperties);
    
    // Should have 2 items: item1 (original) and item2 (appended)
    EXPECT_EQ(2, dest.CountArrayItems(kTestNS, "myArray"));
    
    std::string value;
    dest.GetArrayItem(kTestNS, "myArray", 1, &value, nullptr);
    EXPECT_EQ("item1", value);
    
    dest.GetArrayItem(kTestNS, "myArray", 2, &value, nullptr);
    EXPECT_EQ("item2", value);
}

// Test: Merging array properties - duplicate items are not appended
TEST_F(AppendSubtreeTest_1923, MergeArraySkipDuplicate_1923) {
    SXMPMeta source;
    SXMPMeta dest;
    
    SXMPMeta::RegisterNamespace(kTestNS, "test", nullptr);
    
    source.AppendArrayItem(kTestNS, "myArray", kXMP_PropArrayIsUnordered, "item1");
    dest.AppendArrayItem(kTestNS, "myArray", kXMP_PropArrayIsUnordered, "item1");
    
    SXMPUtils::ApplyTemplate(&dest, source, kXMPTemplate_AddNewProperties);
    
    EXPECT_EQ(1, dest.CountArrayItems(kTestNS, "myArray"));
}

// Test: Alt-text merge - new language item added
TEST_F(AppendSubtreeTest_1923, MergeAltTextAddNewLang_1923) {
    SXMPMeta source;
    SXMPMeta dest;
    
    SXMPMeta::RegisterNamespace(kTestNS, "test", nullptr);
    
    source.SetLocalizedText(kTestNS, "altProp", "x-default", "x-default", "Default Source");
    source.SetLocalizedText(kTestNS, "altProp", "en", "en-US", "English Source");
    
    dest.SetLocalizedText(kTestNS, "altProp", "x-default", "x-default", "Default Dest");
    
    SXMPUtils::ApplyTemplate(&dest, source, kXMPTemplate_AddNewProperties);
    
    std::string value;
    // x-default should remain unchanged (no replace)
    dest.GetLocalizedText(kTestNS, "altProp", "x-default", "x-default", nullptr, &value, nullptr);
    EXPECT_EQ("Default Dest", value);
    
    // en-US should be added
    dest.GetLocalizedText(kTestNS, "altProp", "en", "en-US", nullptr, &value, nullptr);
    EXPECT_EQ("English Source", value);
}

// Test: Source has no dest node - entire subtree cloned
TEST_F(AppendSubtreeTest_1923, CloneEntireSubtreeWhenDestMissing_1923) {
    SXMPMeta source;
    SXMPMeta dest;
    
    SXMPMeta::RegisterNamespace(kTestNS, "test", nullptr);
    
    source.SetStructField(kTestNS, "myStruct", kTestNS, "field1", "val1");
    source.SetStructField(kTestNS, "myStruct", kTestNS, "field2", "val2");
    
    SXMPUtils::ApplyTemplate(&dest, source, kXMPTemplate_AddNewProperties);
    
    std::string value;
    EXPECT_TRUE(dest.GetStructField(kTestNS, "myStruct", kTestNS, "field1", &value, nullptr));
    EXPECT_EQ("val1", value);
    EXPECT_TRUE(dest.GetStructField(kTestNS, "myStruct", kTestNS, "field2", &value, nullptr));
    EXPECT_EQ("val2", value);
}

// Test: Replace existing struct completely
TEST_F(AppendSubtreeTest_1923, ReplaceExistingStructCompletely_1923) {
    SXMPMeta source;
    SXMPMeta dest;
    
    SXMPMeta::RegisterNamespace(kTestNS, "test", nullptr);
    
    source.SetStructField(kTestNS, "myStruct", kTestNS, "fieldA", "srcValA");
    
    dest.SetStructField(kTestNS, "myStruct", kTestNS, "fieldB", "destValB");
    
    SXMPUtils::ApplyTemplate(&dest, source, 
        kXMPTemplate_AddNewProperties | kXMPTemplate_ReplaceExistingProperties);
    
    std::string value;
    EXPECT_TRUE(dest.GetStructField(kTestNS, "myStruct", kTestNS, "fieldA", &value, nullptr));
    EXPECT_EQ("srcValA", value);
    
    // fieldB should be gone since struct was replaced
    EXPECT_FALSE(dest.GetStructField(kTestNS, "myStruct", kTestNS, "fieldB", &value, nullptr));
}

// Test: Different composite types (struct vs array) - no merge
TEST_F(AppendSubtreeTest_1923, DifferentCompositeTypesNoMerge_1923) {
    SXMPMeta source;
    SXMPMeta dest;
    
    SXMPMeta::RegisterNamespace(kTestNS, "test", nullptr);
    
    // Source has array, dest has struct - they shouldn't merge
    source.AppendArrayItem(kTestNS, "mixProp", kXMP_PropArrayIsUnordered, "item1");
    dest.SetStructField(kTestNS, "mixProp", kTestNS, "field1", "val1");
    
    // Without replace, different forms should be left alone
    SXMPUtils::ApplyTemplate(&dest, source, kXMPTemplate_AddNewProperties);
    
    std::string value;
    // Dest should still have its struct
    EXPECT_TRUE(dest.GetStructField(kTestNS, "mixProp", kTestNS, "field1", &value, nullptr));
    EXPECT_EQ("val1", value);
}

// Test: Empty source with no dest node - nothing happens
TEST_F(AppendSubtreeTest_1923, EmptySourceEmptyDest_1923) {
    SXMPMeta source;
    SXMPMeta dest;
    
    SXMPMeta::RegisterNamespace(kTestNS, "test", nullptr);
    
    SXMPUtils::ApplyTemplate(&dest, source, kXMPTemplate_AddNewProperties);
    
    // dest should remain empty
    SXMPMeta::Iterator iter(dest, nullptr, nullptr, 0);
    std::string ns, path, value;
    EXPECT_FALSE(iter.Next(&ns, &path, &value, nullptr));
}

// Test: Delete empty with empty struct source removes dest struct
TEST_F(AppendSubtreeTest_1923, DeleteEmptyStructRemovesDest_1923) {
    SXMPMeta source;
    SXMPMeta dest;
    
    SXMPMeta::RegisterNamespace(kTestNS, "test", nullptr);
    
    // Create an empty struct in source by setting and then deleting children
    source.SetStructField(kTestNS, "myStruct", kTestNS, "temp", "tempVal");
    source.DeleteProperty(kTestNS, "myStruct/test:temp");
    // Now source has empty struct
    
    dest.SetStructField(kTestNS, "myStruct", kTestNS, "field1", "val1");
    
    SXMPUtils::ApplyTemplate(&dest, source, 
        kXMPTemplate_AddNewProperties | kXMPTemplate_ReplaceExistingProperties | kXMPTemplate_ReplaceWithDeleteEmpty);
    
    std::string value;
    EXPECT_FALSE(dest.GetProperty(kTestNS, "myStruct", &value, nullptr));
}

// Test: Multiple properties merged at once
TEST_F(AppendSubtreeTest_1923, MultiplePropertiesMerged_1923) {
    SXMPMeta source;
    SXMPMeta dest;
    
    SXMPMeta::RegisterNamespace(kTestNS, "test", nullptr);
    
    source.SetProperty(kTestNS, "prop1", "val1");
    source.SetProperty(kTestNS, "prop2", "val2");
    source.SetProperty(kTestNS, "prop3", "val3");
    
    dest.SetProperty(kTestNS, "prop2", "existingVal2");
    
    SXMPUtils::ApplyTemplate(&dest, source, kXMPTemplate_AddNewProperties);
    
    std::string value;
    EXPECT_TRUE(dest.GetProperty(kTestNS, "prop1", &value, nullptr));
    EXPECT_EQ("val1", value);
    
    EXPECT_TRUE(dest.GetProperty(kTestNS, "prop2", &value, nullptr));
    EXPECT_EQ("existingVal2", value); // Not replaced
    
    EXPECT_TRUE(dest.GetProperty(kTestNS, "prop3", &value, nullptr));
    EXPECT_EQ("val3", value);
}

// Test: Alt-text x-default inserted at beginning when dest has items
TEST_F(AppendSubtreeTest_1923, AltTextXDefaultInsertedFirst_1923) {
    SXMPMeta source;
    SXMPMeta dest;
    
    SXMPMeta::RegisterNamespace(kTestNS, "test", nullptr);
    
    source.SetLocalizedText(kTestNS, "altProp", "x-default", "x-default", "Default Text");
    
    dest.SetLocalizedText(kTestNS, "altProp", "en", "en-US", "English Text");
    
    SXMPUtils::ApplyTemplate(&dest, source, kXMPTemplate_AddNewProperties);
    
    std::string value;
    dest.GetLocalizedText(kTestNS, "altProp", "x-default", "x-default", nullptr, &value, nullptr);
    EXPECT_EQ("Default Text", value);
}

// Direct XMP_Node tests for lower-level behavior
class XMPNodeTest_1923 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: XMP_Node constructor with name and options
TEST_F(XMPNodeTest_1923, ConstructorWithNameAndOptions_1923) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node child(&parent, "child", kXMP_PropValueIsStruct);
    
    EXPECT_EQ("child", child.name);
    EXPECT_EQ(&parent, child.parent);
    EXPECT_EQ(kXMP_PropValueIsStruct, child.options);
    EXPECT_TRUE(child.children.empty());
    EXPECT_TRUE(child.qualifiers.empty());
}

// Test: XMP_Node constructor with name, value, and options
TEST_F(XMPNodeTest_1923, ConstructorWithNameValueOptions_1923) {
    XMP_Node node(nullptr, "prop", "myValue", 0);
    
    EXPECT_EQ("prop", node.name);
    EXPECT_EQ("myValue", node.value);
    EXPECT_EQ(0u, node.options);
}

// Test: XMP_Node RemoveChildren
TEST_F(XMPNodeTest_1923, RemoveChildren_1923) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* child1 = new XMP_Node(&parent, "child1", 0);
    XMP_Node* child2 = new XMP_Node(&parent, "child2", 0);
    parent.children.push_back(child1);
    parent.children.push_back(child2);
    
    EXPECT_EQ(2u, parent.children.size());
    
    parent.RemoveChildren();
    
    EXPECT_TRUE(parent.children.empty());
}

// Test: XMP_Node RemoveQualifiers
TEST_F(XMPNodeTest_1923, RemoveQualifiers_1923) {
    XMP_Node node(nullptr, "prop", "val", 0);
    XMP_Node* qual = new XMP_Node(&node, "xml:lang", "en", kXMP_PropIsQualifier);
    node.qualifiers.push_back(qual);
    
    EXPECT_EQ(1u, node.qualifiers.size());
    
    node.RemoveQualifiers();
    
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test: XMP_Node ClearNode
TEST_F(XMPNodeTest_1923, ClearNode_1923) {
    XMP_Node node(nullptr, "prop", "val", kXMP_PropValueIsStruct);
    XMP_Node* child = new XMP_Node(&node, "child", 0);
    node.children.push_back(child);
    XMP_Node* qual = new XMP_Node(&node, "xml:lang", "en", kXMP_PropIsQualifier);
    node.qualifiers.push_back(qual);
    
    node.ClearNode();
    
    EXPECT_TRUE(node.children.empty());
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test: XMP_Node destructor cleans up children and qualifiers
TEST_F(XMPNodeTest_1923, DestructorCleansUp_1923) {
    // Just verify no crash/leak when destroying node with children
    XMP_Node* node = new XMP_Node(nullptr, "root", 0);
    XMP_Node* child = new XMP_Node(node, "child", 0);
    node->children.push_back(child);
    
    // Should not crash
    delete node;
    SUCCEED();
}

// Test: XMP_Node with VarString name constructor
TEST_F(XMPNodeTest_1923, ConstructorWithVarStringName_1923) {
    XMP_VarString name = "testName";
    XMP_VarString value = "testValue";
    XMP_Node node(nullptr, name, value, kXMP_PropValueIsArray);
    
    EXPECT_EQ("testName", node.name);
    EXPECT_EQ("testValue", node.value);
    EXPECT_EQ(kXMP_PropValueIsArray, node.options);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
