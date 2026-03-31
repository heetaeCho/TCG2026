#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>

// Include necessary headers from the project
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// We need access to FindSchemaNode and FindChildNode, and RepairAltText is static
// so we include the implementation file to get access
#include "XMPMeta-Parse.cpp"

// Helper macros matching those used in XMP SDK
#ifndef XMP_PropIsSimple
#define XMP_PropIsSimple(opt) (((opt) & kXMP_PropCompositeMask) == 0)
#endif
#ifndef XMP_PropIsArray
#define XMP_PropIsArray(opt) (((opt) & kXMP_PropValueIsArray) != 0)
#endif
#ifndef XMP_ArrayIsAltText
#define XMP_ArrayIsAltText(opt) (((opt) & kXMP_PropArrayIsAltText) != 0)
#endif
#ifndef XMP_PropHasLang
#define XMP_PropHasLang(opt) (((opt) & kXMP_PropHasLang) != 0)
#endif

class RepairAltTextTest_1968 : public ::testing::Test {
protected:
    void SetUp() override {
        tree_ = new XMP_Node(nullptr, "tree", 0);
    }

    void TearDown() override {
        delete tree_;
    }

    XMP_Node* AddSchemaNode(const char* ns) {
        XMP_Node* schema = new XMP_Node(tree_, ns, kXMP_SchemaNode);
        tree_->children.push_back(schema);
        return schema;
    }

    XMP_Node* AddArrayNode(XMP_Node* schema, const char* name, XMP_OptionBits options) {
        XMP_Node* arrayNode = new XMP_Node(schema, name, options);
        schema->children.push_back(arrayNode);
        return arrayNode;
    }

    XMP_Node* AddSimpleChild(XMP_Node* parent, const char* name, const char* value, XMP_OptionBits options = 0) {
        XMP_Node* child = new XMP_Node(parent, name, value, options);
        parent->children.push_back(child);
        return child;
    }

    void AddLangQualifier(XMP_Node* node, const char* lang) {
        XMP_Node* qual = new XMP_Node(node, "xml:lang", lang, kXMP_PropIsQualifier);
        node->qualifiers.push_back(qual);
        node->options |= (kXMP_PropHasQualifiers | kXMP_PropHasLang);
    }

    XMP_Node* tree_;
};

// Test: Schema node does not exist - function should return without changes
TEST_F(RepairAltTextTest_1968, NoSchemaNode_ReturnsEarly_1968) {
    // Tree has no schema nodes
    RepairAltText(*tree_, "http://nonexistent.ns/", "arrayName");
    EXPECT_TRUE(tree_->children.empty());
}

// Test: Schema exists but array node does not exist
TEST_F(RepairAltTextTest_1968, NoArrayNode_ReturnsEarly_1968) {
    XMP_Node* schema = AddSchemaNode("http://test.ns/");
    RepairAltText(*tree_, "http://test.ns/", "nonExistentArray");
    // Schema should still be there, no crash
    EXPECT_EQ(tree_->children.size(), 1u);
}

// Test: Array node already has AltText flag - should return without modification
TEST_F(RepairAltTextTest_1968, AlreadyAltText_NoChange_1968) {
    XMP_Node* schema = AddSchemaNode("http://test.ns/");
    XMP_OptionBits opts = kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered |
                          kXMP_PropArrayIsAlternate | kXMP_PropArrayIsAltText;
    XMP_Node* arr = AddArrayNode(schema, "testArray", opts);
    XMP_Node* child = AddSimpleChild(arr, "item", "value");

    RepairAltText(*tree_, "http://test.ns/", "testArray");

    // Options should remain unchanged
    EXPECT_EQ(arr->options, opts);
    EXPECT_EQ(arr->children.size(), 1u);
}

// Test: Node is not an array - should return without modification
TEST_F(RepairAltTextTest_1968, NotAnArray_NoChange_1968) {
    XMP_Node* schema = AddSchemaNode("http://test.ns/");
    // Simple property, not an array
    XMP_Node* prop = new XMP_Node(schema, "testProp", "someValue", 0);
    schema->children.push_back(prop);

    RepairAltText(*tree_, "http://test.ns/", "testProp");

    // Options should remain 0, not modified
    EXPECT_EQ(prop->options, 0u);
}

// Test: Array without AltText flag, simple children with values but no lang
// Should add lang qualifiers and set AltText flags
TEST_F(RepairAltTextTest_1968, SimpleChildrenGetLangRepair_1968) {
    XMP_Node* schema = AddSchemaNode("http://test.ns/");
    XMP_Node* arr = AddArrayNode(schema, "testArray", kXMP_PropValueIsArray);
    XMP_Node* child = AddSimpleChild(arr, "item1", "hello");

    RepairAltText(*tree_, "http://test.ns/", "testArray");

    // Array should now have alt-text flags
    EXPECT_TRUE((arr->options & kXMP_PropArrayIsOrdered) != 0);
    EXPECT_TRUE((arr->options & kXMP_PropArrayIsAlternate) != 0);
    EXPECT_TRUE((arr->options & kXMP_PropArrayIsAltText) != 0);

    // Child should still exist
    ASSERT_EQ(arr->children.size(), 1u);
    XMP_Node* repairedChild = arr->children[0];

    // Child should have lang qualifier
    EXPECT_TRUE((repairedChild->options & kXMP_PropHasQualifiers) != 0);
    EXPECT_TRUE((repairedChild->options & kXMP_PropHasLang) != 0);
    ASSERT_EQ(repairedChild->qualifiers.size(), 1u);
    EXPECT_EQ(repairedChild->qualifiers[0]->name, "xml:lang");
    EXPECT_EQ(repairedChild->qualifiers[0]->value, "x-repair");
}

// Test: Simple child with empty value and no lang should be removed
TEST_F(RepairAltTextTest_1968, EmptySimpleChildRemoved_1968) {
    XMP_Node* schema = AddSchemaNode("http://test.ns/");
    XMP_Node* arr = AddArrayNode(schema, "testArray", kXMP_PropValueIsArray);
    AddSimpleChild(arr, "item1", "");  // empty value, no lang

    RepairAltText(*tree_, "http://test.ns/", "testArray");

    // Empty child should be removed
    EXPECT_EQ(arr->children.size(), 0u);
}

// Test: Non-simple (composite) children should be removed
TEST_F(RepairAltTextTest_1968, NonSimpleChildrenRemoved_1968) {
    XMP_Node* schema = AddSchemaNode("http://test.ns/");
    XMP_Node* arr = AddArrayNode(schema, "testArray", kXMP_PropValueIsArray);

    // Add a struct child (non-simple)
    XMP_Node* structChild = new XMP_Node(arr, "structItem", kXMP_PropValueIsStruct);
    arr->children.push_back(structChild);

    RepairAltText(*tree_, "http://test.ns/", "testArray");

    // Struct child should be removed
    EXPECT_EQ(arr->children.size(), 0u);
}

// Test: Child that already has lang qualifier should not be modified
TEST_F(RepairAltTextTest_1968, ChildWithLangUnchanged_1968) {
    XMP_Node* schema = AddSchemaNode("http://test.ns/");
    XMP_Node* arr = AddArrayNode(schema, "testArray", kXMP_PropValueIsArray);
    XMP_Node* child = AddSimpleChild(arr, "item1", "hello");
    AddLangQualifier(child, "en");

    RepairAltText(*tree_, "http://test.ns/", "testArray");

    // Child should still have exactly one qualifier
    ASSERT_EQ(arr->children.size(), 1u);
    EXPECT_EQ(arr->children[0]->qualifiers.size(), 1u);
    EXPECT_EQ(arr->children[0]->qualifiers[0]->value, "en");
}

// Test: Mix of children - some simple with value, some empty, some non-simple
TEST_F(RepairAltTextTest_1968, MixedChildren_1968) {
    XMP_Node* schema = AddSchemaNode("http://test.ns/");
    XMP_Node* arr = AddArrayNode(schema, "testArray", kXMP_PropValueIsArray);

    // Child 1: simple with value, no lang -> should get repair lang
    AddSimpleChild(arr, "item1", "value1");
    // Child 2: simple, empty, no lang -> should be removed
    AddSimpleChild(arr, "item2", "");
    // Child 3: struct (non-simple) -> should be removed
    XMP_Node* structChild = new XMP_Node(arr, "item3", kXMP_PropValueIsStruct);
    arr->children.push_back(structChild);
    // Child 4: simple with value and lang -> should be kept as is
    XMP_Node* child4 = AddSimpleChild(arr, "item4", "value4");
    AddLangQualifier(child4, "fr");

    RepairAltText(*tree_, "http://test.ns/", "testArray");

    // Should have 2 remaining children: item1 (repaired) and item4 (unchanged)
    ASSERT_EQ(arr->children.size(), 2u);

    // First remaining child should be item1 with repair lang
    EXPECT_EQ(arr->children[0]->name, "item1");
    EXPECT_EQ(arr->children[0]->value, "value1");
    ASSERT_GE(arr->children[0]->qualifiers.size(), 1u);
    EXPECT_EQ(arr->children[0]->qualifiers[0]->name, "xml:lang");
    EXPECT_EQ(arr->children[0]->qualifiers[0]->value, "x-repair");

    // Second remaining child should be item4 with original lang
    EXPECT_EQ(arr->children[1]->name, "item4");
    EXPECT_EQ(arr->children[1]->value, "value4");
    ASSERT_EQ(arr->children[1]->qualifiers.size(), 1u);
    EXPECT_EQ(arr->children[1]->qualifiers[0]->value, "fr");
}

// Test: Simple child with value and existing non-lang qualifiers should get lang inserted at front
TEST_F(RepairAltTextTest_1968, ExistingQualifiersLangInsertedAtFront_1968) {
    XMP_Node* schema = AddSchemaNode("http://test.ns/");
    XMP_Node* arr = AddArrayNode(schema, "testArray", kXMP_PropValueIsArray);
    XMP_Node* child = AddSimpleChild(arr, "item1", "value");

    // Add a non-lang qualifier
    XMP_Node* qual = new XMP_Node(child, "someQual", "qualValue", kXMP_PropIsQualifier);
    child->qualifiers.push_back(qual);
    child->options |= kXMP_PropHasQualifiers;

    RepairAltText(*tree_, "http://test.ns/", "testArray");

    ASSERT_EQ(arr->children.size(), 1u);
    XMP_Node* repairedChild = arr->children[0];

    // Should have 2 qualifiers, lang first
    ASSERT_EQ(repairedChild->qualifiers.size(), 2u);
    EXPECT_EQ(repairedChild->qualifiers[0]->name, "xml:lang");
    EXPECT_EQ(repairedChild->qualifiers[0]->value, "x-repair");
    EXPECT_EQ(repairedChild->qualifiers[1]->name, "someQual");
}

// Test: Array with ordered flag but no alt-text flag
TEST_F(RepairAltTextTest_1968, OrderedArrayGetsAltTextFlags_1968) {
    XMP_Node* schema = AddSchemaNode("http://test.ns/");
    XMP_OptionBits opts = kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered;
    XMP_Node* arr = AddArrayNode(schema, "testArray", opts);
    XMP_Node* child = AddSimpleChild(arr, "item1", "val");

    RepairAltText(*tree_, "http://test.ns/", "testArray");

    EXPECT_TRUE((arr->options & kXMP_PropArrayIsOrdered) != 0);
    EXPECT_TRUE((arr->options & kXMP_PropArrayIsAlternate) != 0);
    EXPECT_TRUE((arr->options & kXMP_PropArrayIsAltText) != 0);
}

// Test: Empty array - no children to process
TEST_F(RepairAltTextTest_1968, EmptyArray_FlagsSetNoChildren_1968) {
    XMP_Node* schema = AddSchemaNode("http://test.ns/");
    XMP_Node* arr = AddArrayNode(schema, "testArray", kXMP_PropValueIsArray);

    RepairAltText(*tree_, "http://test.ns/", "testArray");

    // Flags should be set
    EXPECT_TRUE((arr->options & kXMP_PropArrayIsAltText) != 0);
    // No children
    EXPECT_EQ(arr->children.size(), 0u);
}

// Test: All children are non-simple -> all removed
TEST_F(RepairAltTextTest_1968, AllNonSimpleChildrenRemoved_1968) {
    XMP_Node* schema = AddSchemaNode("http://test.ns/");
    XMP_Node* arr = AddArrayNode(schema, "testArray", kXMP_PropValueIsArray);

    for (int i = 0; i < 5; ++i) {
        std::string name = "struct" + std::to_string(i);
        XMP_Node* structChild = new XMP_Node(arr, name.c_str(), kXMP_PropValueIsStruct);
        arr->children.push_back(structChild);
    }

    RepairAltText(*tree_, "http://test.ns/", "testArray");

    EXPECT_EQ(arr->children.size(), 0u);
}

// Test: Multiple simple children with values, all need repair
TEST_F(RepairAltTextTest_1968, MultipleSimpleChildrenAllRepaired_1968) {
    XMP_Node* schema = AddSchemaNode("http://test.ns/");
    XMP_Node* arr = AddArrayNode(schema, "testArray", kXMP_PropValueIsArray);

    for (int i = 0; i < 3; ++i) {
        std::string name = "item" + std::to_string(i);
        std::string val = "value" + std::to_string(i);
        AddSimpleChild(arr, name.c_str(), val.c_str());
    }

    RepairAltText(*tree_, "http://test.ns/", "testArray");

    ASSERT_EQ(arr->children.size(), 3u);
    for (int i = 0; i < 3; ++i) {
        EXPECT_TRUE((arr->children[i]->options & kXMP_PropHasLang) != 0);
        ASSERT_GE(arr->children[i]->qualifiers.size(), 1u);
        EXPECT_EQ(arr->children[i]->qualifiers[0]->value, "x-repair");
    }
}

// Test: Array child is itself an array (non-simple) -> removed
TEST_F(RepairAltTextTest_1968, NestedArrayChildRemoved_1968) {
    XMP_Node* schema = AddSchemaNode("http://test.ns/");
    XMP_Node* arr = AddArrayNode(schema, "testArray", kXMP_PropValueIsArray);

    XMP_Node* nestedArr = new XMP_Node(arr, "nestedArray", kXMP_PropValueIsArray);
    arr->children.push_back(nestedArr);

    RepairAltText(*tree_, "http://test.ns/", "testArray");

    EXPECT_EQ(arr->children.size(), 0u);
}

// Test: Alternate array without AltText flag should get repaired
TEST_F(RepairAltTextTest_1968, AlternateWithoutAltText_1968) {
    XMP_Node* schema = AddSchemaNode("http://test.ns/");
    XMP_OptionBits opts = kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered | kXMP_PropArrayIsAlternate;
    XMP_Node* arr = AddArrayNode(schema, "testArray", opts);
    XMP_Node* child = AddSimpleChild(arr, "item", "val");

    RepairAltText(*tree_, "http://test.ns/", "testArray");

    EXPECT_TRUE((arr->options & kXMP_PropArrayIsAltText) != 0);
    ASSERT_EQ(arr->children.size(), 1u);
    EXPECT_TRUE((arr->children[0]->options & kXMP_PropHasLang) != 0);
}
