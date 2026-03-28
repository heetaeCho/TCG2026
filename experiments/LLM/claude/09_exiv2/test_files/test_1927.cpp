#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>

// Include necessary headers
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// We need access to the ChooseLocalizedText function and related types
// Based on the provided code, these are the return value constants
enum {
    kXMP_CLT_NoValues = 0,
    kXMP_CLT_SpecificMatch = 1,
    kXMP_CLT_SingleGeneric = 2,
    kXMP_CLT_MultipleGeneric = 3,
    kXMP_CLT_XDefault = 4,
    kXMP_CLT_FirstItem = 5
};

typedef unsigned char XMP_CLTMatch;

// Forward declaration - this function is static in the source file, 
// so we may need to include the source or make it accessible for testing.
// For testing purposes, we include the implementation.
// In practice, you'd need to make this function testable (e.g., via a test friend or linkage).
extern XMP_CLTMatch ChooseLocalizedText(
    const XMP_Node* arrayNode,
    XMP_StringPtr genericLang,
    XMP_StringPtr specificLang,
    const XMP_Node** itemNode);

// Helper to create a qualifier node with xml:lang
static XMP_Node* MakeLangQualifier(XMP_Node* parent, const char* lang) {
    XMP_Node* qual = new XMP_Node(parent, "xml:lang", lang, 0);
    return qual;
}

// Helper to create an alt-text item with a language qualifier
static XMP_Node* MakeAltTextItem(XMP_Node* parent, const char* lang, const char* value) {
    XMP_Node* item = new XMP_Node(parent, "item", value, 0);
    item->parent = parent;
    XMP_Node* qual = MakeLangQualifier(item, lang);
    item->qualifiers.push_back(qual);
    parent->children.push_back(item);
    return item;
}

class ChooseLocalizedTextTest_1927 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up nodes
        for (auto* node : nodesToClean) {
            node->RemoveChildren();
            node->RemoveQualifiers();
            delete node;
        }
        nodesToClean.clear();
    }

    XMP_Node* CreateAltTextArray() {
        XMP_Node* arrayNode = new XMP_Node(nullptr, "array", kXMP_PropArrayIsAltText | kXMP_PropArrayIsAlternate | kXMP_PropValueIsArray);
        nodesToClean.push_back(arrayNode);
        return arrayNode;
    }

    XMP_Node* CreateAlternateArray() {
        // Alternate but not alt-text - for empty array case
        XMP_Node* arrayNode = new XMP_Node(nullptr, "array", kXMP_PropArrayIsAlternate | kXMP_PropValueIsArray);
        nodesToClean.push_back(arrayNode);
        return arrayNode;
    }

    std::vector<XMP_Node*> nodesToClean;
};

// Test: Empty alt-text array returns kXMP_CLT_NoValues
TEST_F(ChooseLocalizedTextTest_1927, EmptyArrayReturnsNoValues_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    const XMP_Node* itemNode = nullptr;

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "en-US", &itemNode);

    EXPECT_EQ(result, kXMP_CLT_NoValues);
    EXPECT_EQ(itemNode, nullptr);
}

// Test: Empty alternate (not alt-text) array returns kXMP_CLT_NoValues
TEST_F(ChooseLocalizedTextTest_1927, EmptyAlternateArrayReturnsNoValues_1927) {
    XMP_Node* arrayNode = CreateAlternateArray();
    const XMP_Node* itemNode = nullptr;

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "en-US", &itemNode);

    EXPECT_EQ(result, kXMP_CLT_NoValues);
    EXPECT_EQ(itemNode, nullptr);
}

// Test: Non-alt-text, non-empty array throws
TEST_F(ChooseLocalizedTextTest_1927, NonAltTextArrayThrows_1927) {
    XMP_Node* arrayNode = new XMP_Node(nullptr, "array", kXMP_PropValueIsArray);
    nodesToClean.push_back(arrayNode);
    // Add an item so it's not empty
    XMP_Node* item = new XMP_Node(arrayNode, "item", "value", 0);
    XMP_Node* qual = MakeLangQualifier(item, "en");
    item->qualifiers.push_back(qual);
    arrayNode->children.push_back(item);

    const XMP_Node* itemNode = nullptr;

    EXPECT_THROW(ChooseLocalizedText(arrayNode, "en", "en", &itemNode), XMP_Error);
}

// Test: Specific language match returns kXMP_CLT_SpecificMatch
TEST_F(ChooseLocalizedTextTest_1927, SpecificMatchReturnsCorrectly_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    XMP_Node* item1 = MakeAltTextItem(arrayNode, "en-US", "Hello");
    XMP_Node* item2 = MakeAltTextItem(arrayNode, "fr-FR", "Bonjour");

    const XMP_Node* itemNode = nullptr;

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "en-US", &itemNode);

    EXPECT_EQ(result, kXMP_CLT_SpecificMatch);
    EXPECT_EQ(itemNode, item1);
}

// Test: Specific match on second item
TEST_F(ChooseLocalizedTextTest_1927, SpecificMatchOnSecondItem_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    MakeAltTextItem(arrayNode, "en-US", "Hello");
    XMP_Node* item2 = MakeAltTextItem(arrayNode, "fr-FR", "Bonjour");

    const XMP_Node* itemNode = nullptr;

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "fr", "fr-FR", &itemNode);

    EXPECT_EQ(result, kXMP_CLT_SpecificMatch);
    EXPECT_EQ(itemNode, item2);
}

// Test: Single generic match returns kXMP_CLT_SingleGeneric
TEST_F(ChooseLocalizedTextTest_1927, SingleGenericMatchReturnsCorrectly_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    XMP_Node* item1 = MakeAltTextItem(arrayNode, "en-US", "Hello");
    MakeAltTextItem(arrayNode, "fr-FR", "Bonjour");

    const XMP_Node* itemNode = nullptr;

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "en-GB", &itemNode);

    EXPECT_EQ(result, kXMP_CLT_SingleGeneric);
    EXPECT_EQ(itemNode, item1);
}

// Test: Multiple generic matches returns kXMP_CLT_MultipleGeneric
TEST_F(ChooseLocalizedTextTest_1927, MultipleGenericMatchReturnsCorrectly_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    XMP_Node* item1 = MakeAltTextItem(arrayNode, "en-US", "Hello US");
    XMP_Node* item2 = MakeAltTextItem(arrayNode, "en-GB", "Hello GB");

    const XMP_Node* itemNode = nullptr;

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "en-AU", &itemNode);

    EXPECT_EQ(result, kXMP_CLT_MultipleGeneric);
    EXPECT_EQ(itemNode, item1); // First generic match
}

// Test: x-default match when no specific or generic match
TEST_F(ChooseLocalizedTextTest_1927, XDefaultMatchReturnsCorrectly_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    MakeAltTextItem(arrayNode, "fr-FR", "Bonjour");
    XMP_Node* item2 = MakeAltTextItem(arrayNode, "x-default", "Default");

    const XMP_Node* itemNode = nullptr;

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "en-US", &itemNode);

    EXPECT_EQ(result, kXMP_CLT_XDefault);
    EXPECT_EQ(itemNode, item2);
}

// Test: First item returned when no match at all
TEST_F(ChooseLocalizedTextTest_1927, FirstItemReturnedWhenNoMatch_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    XMP_Node* item1 = MakeAltTextItem(arrayNode, "fr-FR", "Bonjour");
    MakeAltTextItem(arrayNode, "de-DE", "Hallo");

    const XMP_Node* itemNode = nullptr;

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "en-US", &itemNode);

    EXPECT_EQ(result, kXMP_CLT_FirstItem);
    EXPECT_EQ(itemNode, item1);
}

// Test: Composite item in array throws
TEST_F(ChooseLocalizedTextTest_1927, CompositeItemThrows_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    // Create a composite (struct) item
    XMP_Node* item = new XMP_Node(arrayNode, "item", "value", kXMP_PropValueIsStruct);
    XMP_Node* qual = MakeLangQualifier(item, "en");
    item->qualifiers.push_back(qual);
    arrayNode->children.push_back(item);

    const XMP_Node* itemNode = nullptr;

    EXPECT_THROW(ChooseLocalizedText(arrayNode, "en", "en", &itemNode), XMP_Error);
}

// Test: Item without language qualifier throws
TEST_F(ChooseLocalizedTextTest_1927, ItemWithoutLangQualifierThrows_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    XMP_Node* item = new XMP_Node(arrayNode, "item", "value", 0);
    // No qualifiers added
    arrayNode->children.push_back(item);

    const XMP_Node* itemNode = nullptr;

    EXPECT_THROW(ChooseLocalizedText(arrayNode, "en", "en", &itemNode), XMP_Error);
}

// Test: Item with non-lang qualifier as first qualifier throws
TEST_F(ChooseLocalizedTextTest_1927, ItemWithWrongQualifierThrows_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    XMP_Node* item = new XMP_Node(arrayNode, "item", "value", 0);
    XMP_Node* qual = new XMP_Node(item, "rdf:type", "something", 0);
    item->qualifiers.push_back(qual);
    arrayNode->children.push_back(item);

    const XMP_Node* itemNode = nullptr;

    EXPECT_THROW(ChooseLocalizedText(arrayNode, "en", "en", &itemNode), XMP_Error);
}

// Test: Generic language empty string means no generic search
TEST_F(ChooseLocalizedTextTest_1927, EmptyGenericLangSkipsGenericSearch_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    MakeAltTextItem(arrayNode, "en-US", "Hello");
    XMP_Node* item2 = MakeAltTextItem(arrayNode, "x-default", "Default");

    const XMP_Node* itemNode = nullptr;

    // Empty generic lang ("") with non-matching specific lang
    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "", "fr-FR", &itemNode);

    EXPECT_EQ(result, kXMP_CLT_XDefault);
    EXPECT_EQ(itemNode, item2);
}

// Test: Generic match with exact generic language (no hyphen)
TEST_F(ChooseLocalizedTextTest_1927, ExactGenericLanguageMatch_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    XMP_Node* item1 = MakeAltTextItem(arrayNode, "en", "English");
    MakeAltTextItem(arrayNode, "fr", "French");

    const XMP_Node* itemNode = nullptr;

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "en-AU", &itemNode);

    EXPECT_EQ(result, kXMP_CLT_SingleGeneric);
    EXPECT_EQ(itemNode, item1);
}

// Test: Specific match takes priority over generic
TEST_F(ChooseLocalizedTextTest_1927, SpecificMatchPriorityOverGeneric_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    MakeAltTextItem(arrayNode, "en-US", "Hello US");
    XMP_Node* item2 = MakeAltTextItem(arrayNode, "en-GB", "Hello GB");
    MakeAltTextItem(arrayNode, "en-AU", "Hello AU");

    const XMP_Node* itemNode = nullptr;

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "en-GB", &itemNode);

    EXPECT_EQ(result, kXMP_CLT_SpecificMatch);
    EXPECT_EQ(itemNode, item2);
}

// Test: No generic, no x-default, returns first item
TEST_F(ChooseLocalizedTextTest_1927, NoMatchNoDefaultReturnsFirstItem_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    XMP_Node* item1 = MakeAltTextItem(arrayNode, "ja-JP", "Japanese");
    MakeAltTextItem(arrayNode, "zh-CN", "Chinese");

    const XMP_Node* itemNode = nullptr;

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "en-US", &itemNode);

    EXPECT_EQ(result, kXMP_CLT_FirstItem);
    EXPECT_EQ(itemNode, item1);
}

// Test: Single item array with matching specific
TEST_F(ChooseLocalizedTextTest_1927, SingleItemSpecificMatch_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    XMP_Node* item1 = MakeAltTextItem(arrayNode, "en-US", "Hello");

    const XMP_Node* itemNode = nullptr;

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "en-US", &itemNode);

    EXPECT_EQ(result, kXMP_CLT_SpecificMatch);
    EXPECT_EQ(itemNode, item1);
}

// Test: Single item array with no match returns first item
TEST_F(ChooseLocalizedTextTest_1927, SingleItemNoMatchReturnsFirstItem_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    XMP_Node* item1 = MakeAltTextItem(arrayNode, "ja-JP", "Japanese");

    const XMP_Node* itemNode = nullptr;

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "en-US", &itemNode);

    EXPECT_EQ(result, kXMP_CLT_FirstItem);
    EXPECT_EQ(itemNode, item1);
}

// Test: Generic match does not match partial prefix without hyphen separator
TEST_F(ChooseLocalizedTextTest_1927, GenericDoesNotMatchPartialPrefix_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    // "eng" should NOT match generic "en" because 'g' != '-'
    XMP_Node* item1 = MakeAltTextItem(arrayNode, "eng", "English full");
    MakeAltTextItem(arrayNode, "x-default", "Default");

    const XMP_Node* itemNode = nullptr;

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "en-US", &itemNode);

    // "eng" does not match "en" as generic because eng[2] == 'g' != '-'
    // Should fall through to x-default
    EXPECT_EQ(result, kXMP_CLT_XDefault);
}

// Test: Multiple generic with exact and hyphenated
TEST_F(ChooseLocalizedTextTest_1927, MultipleGenericExactAndHyphenated_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    XMP_Node* item1 = MakeAltTextItem(arrayNode, "en", "English");
    MakeAltTextItem(arrayNode, "en-US", "English US");

    const XMP_Node* itemNode = nullptr;

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "en-GB", &itemNode);

    EXPECT_EQ(result, kXMP_CLT_MultipleGeneric);
    EXPECT_EQ(itemNode, item1); // First generic match returned
}

// Test: x-default in first position
TEST_F(ChooseLocalizedTextTest_1927, XDefaultAsFirstItem_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    XMP_Node* item1 = MakeAltTextItem(arrayNode, "x-default", "Default");
    MakeAltTextItem(arrayNode, "fr-FR", "Bonjour");

    const XMP_Node* itemNode = nullptr;

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "en-US", &itemNode);

    EXPECT_EQ(result, kXMP_CLT_XDefault);
    EXPECT_EQ(itemNode, item1);
}

// Test: Empty generic lang with no specific match and no x-default returns first
TEST_F(ChooseLocalizedTextTest_1927, EmptyGenericNoXDefaultReturnsFirst_1927) {
    XMP_Node* arrayNode = CreateAltTextArray();
    XMP_Node* item1 = MakeAltTextItem(arrayNode, "ja-JP", "Japanese");
    MakeAltTextItem(arrayNode, "zh-CN", "Chinese");

    const XMP_Node* itemNode = nullptr;

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "", "en-US", &itemNode);

    EXPECT_EQ(result, kXMP_CLT_FirstItem);
    EXPECT_EQ(itemNode, item1);
}
