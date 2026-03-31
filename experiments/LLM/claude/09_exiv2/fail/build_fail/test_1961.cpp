#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>

// Include necessary XMP headers
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// We need access to the static function. Since it's file-static,
// we include the cpp to get access for testing purposes.
// Forward declarations of dependencies
extern XMP_Node * FindSchemaNode(XMP_Node * xmpTree, XMP_StringPtr schemaURI, bool createNodes);
extern XMP_OptionBits VerifySetOptions(XMP_OptionBits options, XMP_StringPtr propValue);

// If we can't include the .cpp directly, we replicate the test through the parse interface.
// For unit testing of the static function, we include the source:
#include "XMPMeta-Parse.cpp"

// Helper: kXMP_NS_DC is typically "http://purl.org/dc/elements/1.1/"
#ifndef kXMP_NS_DC
#define kXMP_NS_DC "http://purl.org/dc/elements/1.1/"
#endif

#ifndef kXMP_ArrayItemName
#define kXMP_ArrayItemName "[]"
#endif

#ifndef kXMP_ExistingOnly
#define kXMP_ExistingOnly false
#endif

// Macro helpers from XMP
#ifndef XMP_PropIsSimple
#define XMP_PropIsSimple(opt) (((opt) & kXMP_PropCompositeMask) == 0)
#endif

#ifndef XMP_ArrayIsAltText
#define XMP_ArrayIsAltText(opt) (((opt) & kXMP_PropArrayIsAltText) != 0)
#endif

class NormalizeDCArraysTest_1961 : public ::testing::Test {
protected:
    void SetUp() override {
        xmpTree = new XMP_Node(nullptr, "xmpTree", 0);
    }

    void TearDown() override {
        delete xmpTree;
    }

    // Helper to create a DC schema node under xmpTree
    XMP_Node* CreateDCSchema() {
        XMP_Node* dcSchema = new XMP_Node(xmpTree, kXMP_NS_DC, kXMP_PropValueIsStruct);
        xmpTree->children.push_back(dcSchema);
        return dcSchema;
    }

    // Helper to add a simple property to dc schema
    XMP_Node* AddSimpleDCProp(XMP_Node* dcSchema, const char* name, const char* value = "testValue") {
        XMP_Node* prop = new XMP_Node(dcSchema, name, value, 0); // options=0 means simple
        dcSchema->children.push_back(prop);
        return prop;
    }

    XMP_Node* xmpTree;
};

// Test: No DC schema present - function should return without changes
TEST_F(NormalizeDCArraysTest_1961, NoDCSchema_NoChanges_1961) {
    // xmpTree has no children (no DC schema)
    EXPECT_TRUE(xmpTree->children.empty());
    NormalizeDCArrays(xmpTree);
    EXPECT_TRUE(xmpTree->children.empty());
}

// Test: DC schema exists but has no children
TEST_F(NormalizeDCArraysTest_1961, EmptyDCSchema_NoChanges_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    EXPECT_TRUE(dcSchema->children.empty());
    NormalizeDCArrays(xmpTree);
    EXPECT_TRUE(dcSchema->children.empty());
}

// Test: dc:creator (simple) should be converted to ordered array
TEST_F(NormalizeDCArraysTest_1961, CreatorConvertedToOrderedArray_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    XMP_Node* creator = AddSimpleDCProp(dcSchema, "dc:creator", "John Doe");

    NormalizeDCArrays(xmpTree);

    // The node at position 0 should now be an array node
    XMP_Node* arrayNode = dcSchema->children[0];
    EXPECT_NE(arrayNode, creator); // Should be a new node
    EXPECT_EQ(arrayNode->name, "dc:creator");
    EXPECT_TRUE((arrayNode->options & kXMP_PropArrayIsOrdered) != 0);

    // The original node should be a child of the array
    ASSERT_EQ(arrayNode->children.size(), 1u);
    EXPECT_EQ(arrayNode->children[0], creator);
    EXPECT_EQ(creator->name, kXMP_ArrayItemName);
    EXPECT_EQ(creator->parent, arrayNode);
}

// Test: dc:date (simple) should be converted to ordered array
TEST_F(NormalizeDCArraysTest_1961, DateConvertedToOrderedArray_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    XMP_Node* date = AddSimpleDCProp(dcSchema, "dc:date", "2023-01-01");

    NormalizeDCArrays(xmpTree);

    XMP_Node* arrayNode = dcSchema->children[0];
    EXPECT_EQ(arrayNode->name, "dc:date");
    EXPECT_TRUE((arrayNode->options & kXMP_PropArrayIsOrdered) != 0);
    ASSERT_EQ(arrayNode->children.size(), 1u);
    EXPECT_EQ(arrayNode->children[0], date);
    EXPECT_EQ(date->name, kXMP_ArrayItemName);
}

// Test: dc:description should be converted to alt-text array with x-default lang
TEST_F(NormalizeDCArraysTest_1961, DescriptionConvertedToAltText_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    XMP_Node* desc = AddSimpleDCProp(dcSchema, "dc:description", "A description");

    NormalizeDCArrays(xmpTree);

    XMP_Node* arrayNode = dcSchema->children[0];
    EXPECT_EQ(arrayNode->name, "dc:description");
    EXPECT_TRUE((arrayNode->options & kXMP_PropArrayIsAltText) != 0);

    ASSERT_EQ(arrayNode->children.size(), 1u);
    XMP_Node* item = arrayNode->children[0];
    EXPECT_EQ(item->name, kXMP_ArrayItemName);
    EXPECT_EQ(item->value, "A description");

    // Should have lang qualifier added
    EXPECT_TRUE((item->options & kXMP_PropHasQualifiers) != 0);
    EXPECT_TRUE((item->options & kXMP_PropHasLang) != 0);
    ASSERT_FALSE(item->qualifiers.empty());
    EXPECT_EQ(item->qualifiers[0]->name, "xml:lang");
    EXPECT_EQ(item->qualifiers[0]->value, "x-default");
}

// Test: dc:rights should be converted to alt-text array
TEST_F(NormalizeDCArraysTest_1961, RightsConvertedToAltText_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    XMP_Node* rights = AddSimpleDCProp(dcSchema, "dc:rights", "Copyright 2023");

    NormalizeDCArrays(xmpTree);

    XMP_Node* arrayNode = dcSchema->children[0];
    EXPECT_EQ(arrayNode->name, "dc:rights");
    EXPECT_TRUE((arrayNode->options & kXMP_PropArrayIsAltText) != 0);

    ASSERT_EQ(arrayNode->children.size(), 1u);
    XMP_Node* item = arrayNode->children[0];
    EXPECT_TRUE((item->options & kXMP_PropHasLang) != 0);
    ASSERT_FALSE(item->qualifiers.empty());
    EXPECT_EQ(item->qualifiers[0]->value, "x-default");
}

// Test: dc:title should be converted to alt-text array
TEST_F(NormalizeDCArraysTest_1961, TitleConvertedToAltText_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    XMP_Node* title = AddSimpleDCProp(dcSchema, "dc:title", "My Title");

    NormalizeDCArrays(xmpTree);

    XMP_Node* arrayNode = dcSchema->children[0];
    EXPECT_EQ(arrayNode->name, "dc:title");
    EXPECT_TRUE((arrayNode->options & kXMP_PropArrayIsAltText) != 0);
}

// Test: dc:subject should be converted to unordered array
TEST_F(NormalizeDCArraysTest_1961, SubjectConvertedToUnorderedArray_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    XMP_Node* subject = AddSimpleDCProp(dcSchema, "dc:subject", "keyword");

    NormalizeDCArrays(xmpTree);

    XMP_Node* arrayNode = dcSchema->children[0];
    EXPECT_EQ(arrayNode->name, "dc:subject");
    EXPECT_TRUE((arrayNode->options & kXMP_PropValueIsArray) != 0);
    // Should NOT have alt-text flag
    EXPECT_FALSE((arrayNode->options & kXMP_PropArrayIsAltText) != 0);

    ASSERT_EQ(arrayNode->children.size(), 1u);
    EXPECT_EQ(arrayNode->children[0]->name, kXMP_ArrayItemName);
}

// Test: dc:contributor should be converted to unordered array
TEST_F(NormalizeDCArraysTest_1961, ContributorConvertedToArray_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    AddSimpleDCProp(dcSchema, "dc:contributor", "Someone");

    NormalizeDCArrays(xmpTree);

    XMP_Node* arrayNode = dcSchema->children[0];
    EXPECT_EQ(arrayNode->name, "dc:contributor");
    EXPECT_TRUE((arrayNode->options & kXMP_PropValueIsArray) != 0);
}

// Test: dc:language should be converted to unordered array
TEST_F(NormalizeDCArraysTest_1961, LanguageConvertedToArray_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    AddSimpleDCProp(dcSchema, "dc:language", "en");

    NormalizeDCArrays(xmpTree);

    XMP_Node* arrayNode = dcSchema->children[0];
    EXPECT_EQ(arrayNode->name, "dc:language");
    EXPECT_TRUE((arrayNode->options & kXMP_PropValueIsArray) != 0);
}

// Test: dc:publisher should be converted to unordered array
TEST_F(NormalizeDCArraysTest_1961, PublisherConvertedToArray_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    AddSimpleDCProp(dcSchema, "dc:publisher", "Publisher Inc.");

    NormalizeDCArrays(xmpTree);

    XMP_Node* arrayNode = dcSchema->children[0];
    EXPECT_EQ(arrayNode->name, "dc:publisher");
    EXPECT_TRUE((arrayNode->options & kXMP_PropValueIsArray) != 0);
}

// Test: dc:relation should be converted to unordered array
TEST_F(NormalizeDCArraysTest_1961, RelationConvertedToArray_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    AddSimpleDCProp(dcSchema, "dc:relation", "related");

    NormalizeDCArrays(xmpTree);

    XMP_Node* arrayNode = dcSchema->children[0];
    EXPECT_EQ(arrayNode->name, "dc:relation");
    EXPECT_TRUE((arrayNode->options & kXMP_PropValueIsArray) != 0);
}

// Test: dc:type should be converted to unordered array
TEST_F(NormalizeDCArraysTest_1961, TypeConvertedToArray_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    AddSimpleDCProp(dcSchema, "dc:type", "Image");

    NormalizeDCArrays(xmpTree);

    XMP_Node* arrayNode = dcSchema->children[0];
    EXPECT_EQ(arrayNode->name, "dc:type");
    EXPECT_TRUE((arrayNode->options & kXMP_PropValueIsArray) != 0);
}

// Test: Non-simple property should be skipped
TEST_F(NormalizeDCArraysTest_1961, NonSimplePropertySkipped_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    // Create a property that already has array options (non-simple)
    XMP_Node* prop = new XMP_Node(dcSchema, "dc:creator", kXMP_PropValueIsArray);
    dcSchema->children.push_back(prop);

    NormalizeDCArrays(xmpTree);

    // Should remain unchanged since it's not simple
    EXPECT_EQ(dcSchema->children[0], prop);
    EXPECT_EQ(prop->name, "dc:creator");
}

// Test: Unknown DC property should be skipped
TEST_F(NormalizeDCArraysTest_1961, UnknownDCPropertySkipped_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    XMP_Node* unknown = AddSimpleDCProp(dcSchema, "dc:unknown", "value");

    NormalizeDCArrays(xmpTree);

    // Should remain unchanged
    EXPECT_EQ(dcSchema->children[0], unknown);
    EXPECT_EQ(unknown->name, "dc:unknown");
    EXPECT_EQ(unknown->options, 0u);
}

// Test: Multiple properties mixed - some converted, some not
TEST_F(NormalizeDCArraysTest_1961, MultiplePropertiesMixed_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    XMP_Node* creator = AddSimpleDCProp(dcSchema, "dc:creator", "John");
    XMP_Node* unknown = AddSimpleDCProp(dcSchema, "dc:unknown", "val");
    XMP_Node* title = AddSimpleDCProp(dcSchema, "dc:title", "Title");
    XMP_Node* subject = AddSimpleDCProp(dcSchema, "dc:subject", "keyword");

    NormalizeDCArrays(xmpTree);

    ASSERT_EQ(dcSchema->children.size(), 4u);

    // dc:creator should be converted to ordered array
    EXPECT_EQ(dcSchema->children[0]->name, "dc:creator");
    EXPECT_TRUE((dcSchema->children[0]->options & kXMP_PropArrayIsOrdered) != 0);

    // dc:unknown should remain unchanged
    EXPECT_EQ(dcSchema->children[1], unknown);
    EXPECT_EQ(unknown->name, "dc:unknown");

    // dc:title should be converted to alt-text
    EXPECT_EQ(dcSchema->children[2]->name, "dc:title");
    EXPECT_TRUE((dcSchema->children[2]->options & kXMP_PropArrayIsAltText) != 0);

    // dc:subject should be converted to unordered array
    EXPECT_EQ(dcSchema->children[3]->name, "dc:subject");
    EXPECT_TRUE((dcSchema->children[3]->options & kXMP_PropValueIsArray) != 0);
}

// Test: Alt-text property that already has lang qualifier should not get x-default added
TEST_F(NormalizeDCArraysTest_1961, AltTextWithExistingLang_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    XMP_Node* desc = new XMP_Node(dcSchema, "dc:description", "desc value", kXMP_PropHasLang);
    dcSchema->children.push_back(desc);

    NormalizeDCArrays(xmpTree);

    XMP_Node* arrayNode = dcSchema->children[0];
    EXPECT_EQ(arrayNode->name, "dc:description");
    XMP_Node* item = arrayNode->children[0];
    // Since it already had kXMP_PropHasLang, no new lang qualifier should be added
    // The qualifiers should remain empty (no x-default was added)
    EXPECT_TRUE(item->qualifiers.empty());
}

// Test: Alt-text with existing qualifiers but no lang - lang inserted at beginning
TEST_F(NormalizeDCArraysTest_1961, AltTextWithExistingQualifiersNoLang_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    XMP_Node* desc = new XMP_Node(dcSchema, "dc:description", "desc value", 0);
    // Add an existing qualifier that is not lang
    XMP_Node* existingQual = new XMP_Node(desc, "rdf:type", "someType", kXMP_PropIsQualifier);
    desc->qualifiers.push_back(existingQual);
    dcSchema->children.push_back(desc);

    NormalizeDCArrays(xmpTree);

    XMP_Node* arrayNode = dcSchema->children[0];
    XMP_Node* item = arrayNode->children[0];

    // x-default lang should be inserted at the beginning
    ASSERT_GE(item->qualifiers.size(), 2u);
    EXPECT_EQ(item->qualifiers[0]->name, "xml:lang");
    EXPECT_EQ(item->qualifiers[0]->value, "x-default");
    EXPECT_EQ(item->qualifiers[1], existingQual);
}

// Test: Alt-text with no qualifiers - lang is pushed back
TEST_F(NormalizeDCArraysTest_1961, AltTextNoQualifiers_LangPushedBack_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    XMP_Node* title = AddSimpleDCProp(dcSchema, "dc:title", "My Title");
    EXPECT_TRUE(title->qualifiers.empty());

    NormalizeDCArrays(xmpTree);

    XMP_Node* arrayNode = dcSchema->children[0];
    XMP_Node* item = arrayNode->children[0];

    ASSERT_EQ(item->qualifiers.size(), 1u);
    EXPECT_EQ(item->qualifiers[0]->name, "xml:lang");
    EXPECT_EQ(item->qualifiers[0]->value, "x-default");
    EXPECT_TRUE((item->qualifiers[0]->options & kXMP_PropIsQualifier) != 0);
}

// Test: Ordered array property (dc:creator) should NOT get lang qualifier
TEST_F(NormalizeDCArraysTest_1961, OrderedArrayNoLangQualifier_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    AddSimpleDCProp(dcSchema, "dc:creator", "Author");

    NormalizeDCArrays(xmpTree);

    XMP_Node* arrayNode = dcSchema->children[0];
    XMP_Node* item = arrayNode->children[0];

    // Ordered arrays (non alt-text) should not have lang qualifier added
    EXPECT_TRUE(item->qualifiers.empty());
    EXPECT_FALSE((item->options & kXMP_PropHasLang) != 0);
}

// Test: Unordered array property (dc:subject) should NOT get lang qualifier
TEST_F(NormalizeDCArraysTest_1961, UnorderedArrayNoLangQualifier_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    AddSimpleDCProp(dcSchema, "dc:subject", "keyword");

    NormalizeDCArrays(xmpTree);

    XMP_Node* arrayNode = dcSchema->children[0];
    XMP_Node* item = arrayNode->children[0];

    EXPECT_TRUE(item->qualifiers.empty());
    EXPECT_FALSE((item->options & kXMP_PropHasLang) != 0);
}

// Test: Value is preserved after conversion
TEST_F(NormalizeDCArraysTest_1961, ValuePreservedAfterConversion_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    AddSimpleDCProp(dcSchema, "dc:creator", "SpecificAuthorName");

    NormalizeDCArrays(xmpTree);

    XMP_Node* arrayNode = dcSchema->children[0];
    ASSERT_EQ(arrayNode->children.size(), 1u);
    EXPECT_EQ(arrayNode->children[0]->value, "SpecificAuthorName");
}

// Test: Parent pointer of new array node is set correctly
TEST_F(NormalizeDCArraysTest_1961, ParentPointerCorrect_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    AddSimpleDCProp(dcSchema, "dc:creator", "Author");

    NormalizeDCArrays(xmpTree);

    XMP_Node* arrayNode = dcSchema->children[0];
    EXPECT_EQ(arrayNode->parent, dcSchema);
    EXPECT_EQ(arrayNode->children[0]->parent, arrayNode);
}

// Test: Property with struct options is skipped (non-simple)
TEST_F(NormalizeDCArraysTest_1961, StructPropertySkipped_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    XMP_Node* prop = new XMP_Node(dcSchema, "dc:creator", kXMP_PropValueIsStruct);
    dcSchema->children.push_back(prop);

    NormalizeDCArrays(xmpTree);

    // Should remain unchanged
    EXPECT_EQ(dcSchema->children[0], prop);
    EXPECT_EQ(prop->options, static_cast<XMP_OptionBits>(kXMP_PropValueIsStruct));
}

// Test: Single property dc:format (not in any list) should be left alone
TEST_F(NormalizeDCArraysTest_1961, FormatPropertyLeftAlone_1961) {
    XMP_Node* dcSchema = CreateDCSchema();
    XMP_Node* format = AddSimpleDCProp(dcSchema, "dc:format", "image/jpeg");

    NormalizeDCArrays(xmpTree);

    EXPECT_EQ(dcSchema->children[0], format);
    EXPECT_EQ(format->name, "dc:format");
    EXPECT_EQ(format->options, 0u);
}
