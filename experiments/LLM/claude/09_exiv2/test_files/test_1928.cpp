#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary headers
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// We need to define kXMP_ArrayItemName if not available
#ifndef kXMP_ArrayItemName
#define kXMP_ArrayItemName "[]"
#endif

// Forward declare or include the function under test
// Since AppendLangItem is a static function in XMPMeta-GetSet.cpp, we need to
// either include it or recreate the declaration for testing purposes.
// For testing, we'll recreate the function signature based on the provided code.

static void AppendLangItem(XMP_Node* arrayNode, XMP_StringPtr itemLang, XMP_StringPtr itemValue)
{
    XMP_Node* newItem = new XMP_Node(arrayNode, kXMP_ArrayItemName, itemValue,
                                     (kXMP_PropHasQualifiers | kXMP_PropHasLang));
    XMP_Node* langQual = new XMP_Node(newItem, "xml:lang", itemLang, kXMP_PropIsQualifier);
    newItem->qualifiers.push_back(langQual);

    if ((arrayNode->children.empty()) || (langQual->value != "x-default")) {
        arrayNode->children.push_back(newItem);
    } else {
        arrayNode->children.insert(arrayNode->children.begin(), newItem);
    }
}

class AppendLangItemTest_1928 : public ::testing::Test {
protected:
    XMP_Node* arrayNode;

    void SetUp() override {
        arrayNode = new XMP_Node(nullptr, "testArray", kXMP_PropArrayIsAlternate);
    }

    void TearDown() override {
        // Clean up children and their qualifiers
        for (size_t i = 0; i < arrayNode->children.size(); ++i) {
            XMP_Node* child = arrayNode->children[i];
            for (size_t j = 0; j < child->qualifiers.size(); ++j) {
                delete child->qualifiers[j];
            }
            child->qualifiers.clear();
            delete child;
        }
        arrayNode->children.clear();
        delete arrayNode;
    }
};

// Test: Adding a single non-default language item to an empty array
TEST_F(AppendLangItemTest_1928, AddSingleNonDefaultItem_1928)
{
    AppendLangItem(arrayNode, "en-US", "Hello");

    ASSERT_EQ(arrayNode->children.size(), 1u);
    EXPECT_EQ(arrayNode->children[0]->value, "Hello");
    EXPECT_EQ(arrayNode->children[0]->name, kXMP_ArrayItemName);

    // Check qualifiers
    ASSERT_EQ(arrayNode->children[0]->qualifiers.size(), 1u);
    EXPECT_EQ(arrayNode->children[0]->qualifiers[0]->name, "xml:lang");
    EXPECT_EQ(arrayNode->children[0]->qualifiers[0]->value, "en-US");
}

// Test: Adding x-default to an empty array appends it (since array is empty)
TEST_F(AppendLangItemTest_1928, AddXDefaultToEmptyArray_1928)
{
    AppendLangItem(arrayNode, "x-default", "Default Value");

    ASSERT_EQ(arrayNode->children.size(), 1u);
    EXPECT_EQ(arrayNode->children[0]->value, "Default Value");

    ASSERT_EQ(arrayNode->children[0]->qualifiers.size(), 1u);
    EXPECT_EQ(arrayNode->children[0]->qualifiers[0]->value, "x-default");
}

// Test: Adding x-default to a non-empty array inserts it at the beginning
TEST_F(AppendLangItemTest_1928, AddXDefaultToNonEmptyArrayInsertsAtBeginning_1928)
{
    // First add a non-default item
    AppendLangItem(arrayNode, "en-US", "Hello");
    ASSERT_EQ(arrayNode->children.size(), 1u);

    // Now add x-default - should be inserted at the beginning
    AppendLangItem(arrayNode, "x-default", "Default Value");

    ASSERT_EQ(arrayNode->children.size(), 2u);
    EXPECT_EQ(arrayNode->children[0]->value, "Default Value");
    EXPECT_EQ(arrayNode->children[0]->qualifiers[0]->value, "x-default");
    EXPECT_EQ(arrayNode->children[1]->value, "Hello");
    EXPECT_EQ(arrayNode->children[1]->qualifiers[0]->value, "en-US");
}

// Test: Adding multiple non-default items appends in order
TEST_F(AppendLangItemTest_1928, AddMultipleNonDefaultItemsAppendsInOrder_1928)
{
    AppendLangItem(arrayNode, "en-US", "Hello");
    AppendLangItem(arrayNode, "fr-FR", "Bonjour");
    AppendLangItem(arrayNode, "de-DE", "Hallo");

    ASSERT_EQ(arrayNode->children.size(), 3u);
    EXPECT_EQ(arrayNode->children[0]->qualifiers[0]->value, "en-US");
    EXPECT_EQ(arrayNode->children[1]->qualifiers[0]->value, "fr-FR");
    EXPECT_EQ(arrayNode->children[2]->qualifiers[0]->value, "de-DE");
}

// Test: Verify that new item has correct options set
TEST_F(AppendLangItemTest_1928, NewItemHasCorrectOptions_1928)
{
    AppendLangItem(arrayNode, "en-US", "Hello");

    ASSERT_EQ(arrayNode->children.size(), 1u);
    XMP_Node* newItem = arrayNode->children[0];
    EXPECT_EQ(newItem->options, static_cast<XMP_OptionBits>(kXMP_PropHasQualifiers | kXMP_PropHasLang));
}

// Test: Verify that qualifier has correct options set
TEST_F(AppendLangItemTest_1928, QualifierHasCorrectOptions_1928)
{
    AppendLangItem(arrayNode, "en-US", "Hello");

    ASSERT_EQ(arrayNode->children.size(), 1u);
    ASSERT_EQ(arrayNode->children[0]->qualifiers.size(), 1u);
    XMP_Node* langQual = arrayNode->children[0]->qualifiers[0];
    EXPECT_EQ(langQual->options, static_cast<XMP_OptionBits>(kXMP_PropIsQualifier));
}

// Test: Verify parent of new item is arrayNode
TEST_F(AppendLangItemTest_1928, NewItemParentIsArrayNode_1928)
{
    AppendLangItem(arrayNode, "en-US", "Hello");

    ASSERT_EQ(arrayNode->children.size(), 1u);
    EXPECT_EQ(arrayNode->children[0]->parent, arrayNode);
}

// Test: Verify parent of qualifier is the new item
TEST_F(AppendLangItemTest_1928, QualifierParentIsNewItem_1928)
{
    AppendLangItem(arrayNode, "en-US", "Hello");

    ASSERT_EQ(arrayNode->children.size(), 1u);
    XMP_Node* newItem = arrayNode->children[0];
    ASSERT_EQ(newItem->qualifiers.size(), 1u);
    EXPECT_EQ(newItem->qualifiers[0]->parent, newItem);
}

// Test: Adding x-default after multiple items inserts at beginning
TEST_F(AppendLangItemTest_1928, AddXDefaultAfterMultipleItemsInsertsAtFront_1928)
{
    AppendLangItem(arrayNode, "en-US", "Hello");
    AppendLangItem(arrayNode, "fr-FR", "Bonjour");
    AppendLangItem(arrayNode, "de-DE", "Hallo");

    // Add x-default
    AppendLangItem(arrayNode, "x-default", "Default");

    ASSERT_EQ(arrayNode->children.size(), 4u);
    EXPECT_EQ(arrayNode->children[0]->qualifiers[0]->value, "x-default");
    EXPECT_EQ(arrayNode->children[0]->value, "Default");
    EXPECT_EQ(arrayNode->children[1]->qualifiers[0]->value, "en-US");
    EXPECT_EQ(arrayNode->children[2]->qualifiers[0]->value, "fr-FR");
    EXPECT_EQ(arrayNode->children[3]->qualifiers[0]->value, "de-DE");
}

// Test: Empty string language and value
TEST_F(AppendLangItemTest_1928, EmptyLangAndValue_1928)
{
    AppendLangItem(arrayNode, "", "");

    ASSERT_EQ(arrayNode->children.size(), 1u);
    EXPECT_EQ(arrayNode->children[0]->value, "");
    ASSERT_EQ(arrayNode->children[0]->qualifiers.size(), 1u);
    EXPECT_EQ(arrayNode->children[0]->qualifiers[0]->value, "");
}

// Test: Non-default language item appended after x-default
TEST_F(AppendLangItemTest_1928, NonDefaultAppendedAfterXDefault_1928)
{
    AppendLangItem(arrayNode, "x-default", "Default");
    AppendLangItem(arrayNode, "en-US", "Hello");

    ASSERT_EQ(arrayNode->children.size(), 2u);
    EXPECT_EQ(arrayNode->children[0]->qualifiers[0]->value, "x-default");
    EXPECT_EQ(arrayNode->children[1]->qualifiers[0]->value, "en-US");
}

// Test: Value with special characters
TEST_F(AppendLangItemTest_1928, SpecialCharactersInValue_1928)
{
    AppendLangItem(arrayNode, "en-US", "Hello <World> & \"Friends\" 'Everyone'");

    ASSERT_EQ(arrayNode->children.size(), 1u);
    EXPECT_EQ(arrayNode->children[0]->value, "Hello <World> & \"Friends\" 'Everyone'");
}

// Test: Language tag with special casing
TEST_F(AppendLangItemTest_1928, LanguageTagCaseSensitivity_1928)
{
    // "X-Default" is not equal to "x-default" (case sensitive comparison)
    AppendLangItem(arrayNode, "en-US", "Hello");
    AppendLangItem(arrayNode, "X-Default", "Not really default");

    // Since "X-Default" != "x-default", it should be appended at end
    ASSERT_EQ(arrayNode->children.size(), 2u);
    EXPECT_EQ(arrayNode->children[0]->qualifiers[0]->value, "en-US");
    EXPECT_EQ(arrayNode->children[1]->qualifiers[0]->value, "X-Default");
}

// Test: Adding x-default twice (both to non-empty array)
TEST_F(AppendLangItemTest_1928, AddXDefaultTwice_1928)
{
    AppendLangItem(arrayNode, "en-US", "Hello");
    AppendLangItem(arrayNode, "x-default", "Default1");
    AppendLangItem(arrayNode, "x-default", "Default2");

    // Both x-default items should be inserted at the beginning
    ASSERT_EQ(arrayNode->children.size(), 3u);
    // The second x-default should be inserted at position 0
    EXPECT_EQ(arrayNode->children[0]->value, "Default2");
    EXPECT_EQ(arrayNode->children[0]->qualifiers[0]->value, "x-default");
    EXPECT_EQ(arrayNode->children[1]->value, "Default1");
    EXPECT_EQ(arrayNode->children[1]->qualifiers[0]->value, "x-default");
    EXPECT_EQ(arrayNode->children[2]->value, "Hello");
}

// Test: Qualifier name is always "xml:lang"
TEST_F(AppendLangItemTest_1928, QualifierNameIsXmlLang_1928)
{
    AppendLangItem(arrayNode, "ja-JP", "こんにちは");

    ASSERT_EQ(arrayNode->children.size(), 1u);
    ASSERT_EQ(arrayNode->children[0]->qualifiers.size(), 1u);
    EXPECT_EQ(arrayNode->children[0]->qualifiers[0]->name, "xml:lang");
}

// Test: Item name is kXMP_ArrayItemName
TEST_F(AppendLangItemTest_1928, ItemNameIsArrayItemName_1928)
{
    AppendLangItem(arrayNode, "en-US", "Test");

    ASSERT_EQ(arrayNode->children.size(), 1u);
    EXPECT_EQ(arrayNode->children[0]->name, kXMP_ArrayItemName);
}

// Test: Long value string
TEST_F(AppendLangItemTest_1928, LongValueString_1928)
{
    std::string longValue(10000, 'A');
    AppendLangItem(arrayNode, "en-US", longValue.c_str());

    ASSERT_EQ(arrayNode->children.size(), 1u);
    EXPECT_EQ(arrayNode->children[0]->value, longValue);
}
