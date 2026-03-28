#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary headers
#include "XMPCore_Impl.hpp"

// The function under test is static in the .cpp file, so we need to access it.
// We declare it as extern or include the cpp to make it accessible for testing.
// Since it's static, we include the source file to get access.
// In practice, this would be refactored, but for testing we include it.

// Forward declare or re-declare for linkage. Since it's static, we include the cpp.
// We need to be careful about multiple definitions.

#include "XMPMeta.cpp"

class CompareNodeLangsTest_2144 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Helper to create a node with a qualifier
    XMP_Node* CreateNodeWithLangQualifier(XMP_Node* parent, const std::string& langValue) {
        XMP_Node* node = new XMP_Node(parent, "item", 0);
        XMP_Node* qualifier = new XMP_Node(node, "xml:lang", langValue.c_str(), 0);
        node->qualifiers.push_back(qualifier);
        return node;
    }

    XMP_Node* CreateNodeWithNonLangQualifier(XMP_Node* parent, const std::string& name, const std::string& value) {
        XMP_Node* node = new XMP_Node(parent, "item", 0);
        XMP_Node* qualifier = new XMP_Node(node, name.c_str(), value.c_str(), 0);
        node->qualifiers.push_back(qualifier);
        return node;
    }

    XMP_Node* CreateNodeWithoutQualifiers(XMP_Node* parent) {
        XMP_Node* node = new XMP_Node(parent, "item", 0);
        return node;
    }
};

// Test: Left node has no qualifiers -> returns false
TEST_F(CompareNodeLangsTest_2144, LeftNoQualifiers_ReturnsFalse_2144) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* left = CreateNodeWithoutQualifiers(&parent);
    XMP_Node* right = CreateNodeWithLangQualifier(&parent, "en");

    EXPECT_FALSE(CompareNodeLangs(left, right));

    delete left;
    delete right;
}

// Test: Right node has no qualifiers -> returns false
TEST_F(CompareNodeLangsTest_2144, RightNoQualifiers_ReturnsFalse_2144) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* left = CreateNodeWithLangQualifier(&parent, "en");
    XMP_Node* right = CreateNodeWithoutQualifiers(&parent);

    EXPECT_FALSE(CompareNodeLangs(left, right));

    delete left;
    delete right;
}

// Test: Both nodes have no qualifiers -> returns false
TEST_F(CompareNodeLangsTest_2144, BothNoQualifiers_ReturnsFalse_2144) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* left = CreateNodeWithoutQualifiers(&parent);
    XMP_Node* right = CreateNodeWithoutQualifiers(&parent);

    EXPECT_FALSE(CompareNodeLangs(left, right));

    delete left;
    delete right;
}

// Test: Left qualifier name is not "xml:lang" -> returns false
TEST_F(CompareNodeLangsTest_2144, LeftNonLangQualifier_ReturnsFalse_2144) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* left = CreateNodeWithNonLangQualifier(&parent, "rdf:type", "en");
    XMP_Node* right = CreateNodeWithLangQualifier(&parent, "en");

    EXPECT_FALSE(CompareNodeLangs(left, right));

    delete left;
    delete right;
}

// Test: Right qualifier name is not "xml:lang" -> returns false
TEST_F(CompareNodeLangsTest_2144, RightNonLangQualifier_ReturnsFalse_2144) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* left = CreateNodeWithLangQualifier(&parent, "en");
    XMP_Node* right = CreateNodeWithNonLangQualifier(&parent, "rdf:type", "en");

    EXPECT_FALSE(CompareNodeLangs(left, right));

    delete left;
    delete right;
}

// Test: Left lang is "x-default" -> returns true
TEST_F(CompareNodeLangsTest_2144, LeftIsXDefault_ReturnsTrue_2144) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* left = CreateNodeWithLangQualifier(&parent, "x-default");
    XMP_Node* right = CreateNodeWithLangQualifier(&parent, "en");

    EXPECT_TRUE(CompareNodeLangs(left, right));

    delete left;
    delete right;
}

// Test: Right lang is "x-default", left is not -> returns false
TEST_F(CompareNodeLangsTest_2144, RightIsXDefault_ReturnsFalse_2144) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* left = CreateNodeWithLangQualifier(&parent, "en");
    XMP_Node* right = CreateNodeWithLangQualifier(&parent, "x-default");

    EXPECT_FALSE(CompareNodeLangs(left, right));

    delete left;
    delete right;
}

// Test: Both are "x-default" -> left is x-default so returns true
TEST_F(CompareNodeLangsTest_2144, BothXDefault_ReturnsTrue_2144) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* left = CreateNodeWithLangQualifier(&parent, "x-default");
    XMP_Node* right = CreateNodeWithLangQualifier(&parent, "x-default");

    EXPECT_TRUE(CompareNodeLangs(left, right));

    delete left;
    delete right;
}

// Test: Normal lexicographic comparison, left < right -> returns true
TEST_F(CompareNodeLangsTest_2144, LeftLessThanRight_ReturnsTrue_2144) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* left = CreateNodeWithLangQualifier(&parent, "de");
    XMP_Node* right = CreateNodeWithLangQualifier(&parent, "en");

    EXPECT_TRUE(CompareNodeLangs(left, right));

    delete left;
    delete right;
}

// Test: Normal lexicographic comparison, left > right -> returns false
TEST_F(CompareNodeLangsTest_2144, LeftGreaterThanRight_ReturnsFalse_2144) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* left = CreateNodeWithLangQualifier(&parent, "fr");
    XMP_Node* right = CreateNodeWithLangQualifier(&parent, "en");

    EXPECT_FALSE(CompareNodeLangs(left, right));

    delete left;
    delete right;
}

// Test: Same language values -> returns false (not strictly less)
TEST_F(CompareNodeLangsTest_2144, SameLangValues_ReturnsFalse_2144) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* left = CreateNodeWithLangQualifier(&parent, "en");
    XMP_Node* right = CreateNodeWithLangQualifier(&parent, "en");

    EXPECT_FALSE(CompareNodeLangs(left, right));

    delete left;
    delete right;
}

// Test: Empty language values (both empty strings, neither is x-default)
TEST_F(CompareNodeLangsTest_2144, EmptyLangValues_ReturnsFalse_2144) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* left = CreateNodeWithLangQualifier(&parent, "");
    XMP_Node* right = CreateNodeWithLangQualifier(&parent, "");

    EXPECT_FALSE(CompareNodeLangs(left, right));

    delete left;
    delete right;
}

// Test: Left empty string, right non-empty -> empty < non-empty
TEST_F(CompareNodeLangsTest_2144, LeftEmptyRightNonEmpty_ReturnsTrue_2144) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* left = CreateNodeWithLangQualifier(&parent, "");
    XMP_Node* right = CreateNodeWithLangQualifier(&parent, "en");

    EXPECT_TRUE(CompareNodeLangs(left, right));

    delete left;
    delete right;
}

// Test: Left non-empty, right empty -> returns false
TEST_F(CompareNodeLangsTest_2144, LeftNonEmptyRightEmpty_ReturnsFalse_2144) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* left = CreateNodeWithLangQualifier(&parent, "en");
    XMP_Node* right = CreateNodeWithLangQualifier(&parent, "");

    EXPECT_FALSE(CompareNodeLangs(left, right));

    delete left;
    delete right;
}

// Test: Left has multiple qualifiers but first is xml:lang
TEST_F(CompareNodeLangsTest_2144, MultipleQualifiersFirstIsLang_2144) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* left = new XMP_Node(&parent, "item", 0);
    XMP_Node* langQual = new XMP_Node(left, "xml:lang", "de", 0);
    XMP_Node* otherQual = new XMP_Node(left, "rdf:type", "something", 0);
    left->qualifiers.push_back(langQual);
    left->qualifiers.push_back(otherQual);

    XMP_Node* right = CreateNodeWithLangQualifier(&parent, "en");

    EXPECT_TRUE(CompareNodeLangs(left, right));

    delete left;
    delete right;
}

// Test: Left has multiple qualifiers but first is NOT xml:lang -> returns false
TEST_F(CompareNodeLangsTest_2144, MultipleQualifiersFirstIsNotLang_ReturnsFalse_2144) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* left = new XMP_Node(&parent, "item", 0);
    XMP_Node* otherQual = new XMP_Node(left, "rdf:type", "something", 0);
    XMP_Node* langQual = new XMP_Node(left, "xml:lang", "de", 0);
    left->qualifiers.push_back(otherQual);
    left->qualifiers.push_back(langQual);

    XMP_Node* right = CreateNodeWithLangQualifier(&parent, "en");

    EXPECT_FALSE(CompareNodeLangs(left, right));

    delete left;
    delete right;
}

// Test: Lexicographic comparison with longer strings
TEST_F(CompareNodeLangsTest_2144, LongerLangStrings_2144) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* left = CreateNodeWithLangQualifier(&parent, "en-US");
    XMP_Node* right = CreateNodeWithLangQualifier(&parent, "en-gb");

    // 'U' (85) < 'g' (103) in ASCII, so "en-US" < "en-gb"
    EXPECT_TRUE(CompareNodeLangs(left, right));

    delete left;
    delete right;
}

// Test: x-default on left takes priority even if right has smaller string
TEST_F(CompareNodeLangsTest_2144, XDefaultAlwaysSortsFirst_2144) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node* left = CreateNodeWithLangQualifier(&parent, "x-default");
    XMP_Node* right = CreateNodeWithLangQualifier(&parent, "aa"); // "aa" < "x-default" lexicographically

    EXPECT_TRUE(CompareNodeLangs(left, right));

    delete left;
    delete right;
}
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>

// Include necessary headers from the project
#define TXMP_STRING_TYPE std::string
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"
#include "XMPMeta.hpp"

// We need access to the static helper. Since SortWithinOffspring is static in the .cpp,
// we test via XMPMeta::Sort() which is the public interface that calls it.

class SortWithinOffspringTest_2145 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Helper to check if XMP_Node options macros work as expected
// XMP_PropIsStruct checks kXMP_PropValueIsStruct (256)
// XMP_PropIsArray checks array bits
// XMP_ArrayIsUnordered checks kXMP_PropArrayIsUnordered (512) without ordered bit
// XMP_ArrayIsAltText checks kXMP_PropArrayIsAltText (4096)
// XMP_NodeIsSchema - typically a node-level flag

// Test sorting through XMPMeta::Sort() public interface
TEST_F(SortWithinOffspringTest_2145, SortEmptyMetadata_2145) {
    SXMPMeta meta;
    // Sorting empty metadata should not crash
    EXPECT_NO_THROW(meta.Sort());
}

TEST_F(SortWithinOffspringTest_2145, SortSingleProperty_2145) {
    SXMPMeta meta;
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "Creator", "John");
    EXPECT_NO_THROW(meta.Sort());
    
    std::string value;
    EXPECT_TRUE(meta.GetProperty("http://ns.adobe.com/xap/1.0/", "Creator", &value, nullptr));
    EXPECT_EQ("John", value);
}

TEST_F(SortWithinOffspringTest_2145, SortMultiplePropertiesSameNamespace_2145) {
    SXMPMeta meta;
    // Add properties in reverse alphabetical order
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "Zebra", "val1");
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "Apple", "val2");
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "Mango", "val3");
    
    meta.Sort();
    
    // After sorting, iterating should give properties in alphabetical order
    SXMPIterator iter(meta, "http://ns.adobe.com/xap/1.0/", nullptr, kXMP_IterJustChildren);
    std::string schemaNS, propPath, propValue;
    std::vector<std::string> propNames;
    
    while (iter.Next(&schemaNS, &propPath, &propValue, nullptr)) {
        propNames.push_back(propPath);
    }
    
    // Verify sorted order
    ASSERT_EQ(3u, propNames.size());
    // Properties should be sorted by name within the schema (struct-like sorting)
    for (size_t i = 1; i < propNames.size(); ++i) {
        EXPECT_LE(propNames[i-1], propNames[i]) 
            << "Expected " << propNames[i-1] << " <= " << propNames[i];
    }
}

TEST_F(SortWithinOffspringTest_2145, SortUnorderedArrayByValue_2145) {
    SXMPMeta meta;
    // Create a bag (unordered array) and add items in non-sorted value order
    meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "Keywords",
                         kXMP_PropArrayIsUnordered, "Zebra", 0);
    meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "Keywords",
                         kXMP_PropArrayIsUnordered, "Apple", 0);
    meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "Keywords",
                         kXMP_PropArrayIsUnordered, "Mango", 0);
    
    meta.Sort();
    
    // For unordered arrays, items should be stable_sorted by value
    std::string value;
    EXPECT_TRUE(meta.GetArrayItem("http://ns.adobe.com/xap/1.0/", "Keywords", 1, &value, nullptr));
    EXPECT_EQ("Apple", value);
    EXPECT_TRUE(meta.GetArrayItem("http://ns.adobe.com/xap/1.0/", "Keywords", 2, &value, nullptr));
    EXPECT_EQ("Mango", value);
    EXPECT_TRUE(meta.GetArrayItem("http://ns.adobe.com/xap/1.0/", "Keywords", 3, &value, nullptr));
    EXPECT_EQ("Zebra", value);
}

TEST_F(SortWithinOffspringTest_2145, SortOrderedArrayPreservesOrder_2145) {
    SXMPMeta meta;
    // Create an ordered array (seq)
    meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "Creators",
                         kXMP_PropArrayIsOrdered, "Zebra", 0);
    meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "Creators",
                         kXMP_PropArrayIsOrdered, "Apple", 0);
    meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "Creators",
                         kXMP_PropArrayIsOrdered, "Mango", 0);
    
    meta.Sort();
    
    // Ordered arrays should NOT be sorted (neither by name, value, nor lang)
    std::string value;
    EXPECT_TRUE(meta.GetArrayItem("http://ns.adobe.com/xap/1.0/", "Creators", 1, &value, nullptr));
    EXPECT_EQ("Zebra", value);
    EXPECT_TRUE(meta.GetArrayItem("http://ns.adobe.com/xap/1.0/", "Creators", 2, &value, nullptr));
    EXPECT_EQ("Apple", value);
    EXPECT_TRUE(meta.GetArrayItem("http://ns.adobe.com/xap/1.0/", "Creators", 3, &value, nullptr));
    EXPECT_EQ("Mango", value);
}

TEST_F(SortWithinOffspringTest_2145, SortAltTextByLanguage_2145) {
    SXMPMeta meta;
    // Create an alt-text array with different languages
    meta.SetLocalizedText("http://purl.org/dc/elements/1.1/", "title",
                          nullptr, "x-default", "Default Title");
    meta.SetLocalizedText("http://purl.org/dc/elements/1.1/", "title",
                          "fr", "fr", "Titre Français");
    meta.SetLocalizedText("http://purl.org/dc/elements/1.1/", "title",
                          "de", "de", "Deutscher Titel");
    
    meta.Sort();
    
    // After sorting, alt-text items should be sorted by language qualifier
    // We verify the structure is still valid and accessible
    std::string value, actualLang;
    meta.GetLocalizedText("http://purl.org/dc/elements/1.1/", "title",
                          nullptr, "x-default", &actualLang, &value, nullptr);
    EXPECT_EQ("Default Title", value);
    
    meta.GetLocalizedText("http://purl.org/dc/elements/1.1/", "title",
                          "fr", "fr", &actualLang, &value, nullptr);
    EXPECT_EQ("Titre Français", value);
    
    meta.GetLocalizedText("http://purl.org/dc/elements/1.1/", "title",
                          "de", "de", &actualLang, &value, nullptr);
    EXPECT_EQ("Deutscher Titel", value);
}

TEST_F(SortWithinOffspringTest_2145, SortStructChildren_2145) {
    SXMPMeta meta;
    // Create a struct with multiple fields
    meta.SetStructField("http://ns.adobe.com/xap/1.0/", "Address",
                        "http://ns.adobe.com/xap/1.0/", "Zip", "12345");
    meta.SetStructField("http://ns.adobe.com/xap/1.0/", "Address",
                        "http://ns.adobe.com/xap/1.0/", "City", "Springfield");
    meta.SetStructField("http://ns.adobe.com/xap/1.0/", "Address",
                        "http://ns.adobe.com/xap/1.0/", "State", "IL");
    
    meta.Sort();
    
    // Struct children should be sorted by name
    SXMPIterator iter(meta, "http://ns.adobe.com/xap/1.0/", "Address", kXMP_IterJustChildren);
    std::string schemaNS, propPath, propValue;
    std::vector<std::string> fieldNames;
    
    while (iter.Next(&schemaNS, &propPath, &propValue, nullptr)) {
        fieldNames.push_back(propPath);
    }
    
    ASSERT_GE(fieldNames.size(), 3u);
    for (size_t i = 1; i < fieldNames.size(); ++i) {
        EXPECT_LE(fieldNames[i-1], fieldNames[i])
            << "Expected " << fieldNames[i-1] << " <= " << fieldNames[i];
    }
}

TEST_F(SortWithinOffspringTest_2145, SortMultipleNamespaces_2145) {
    SXMPMeta meta;
    // Add properties to multiple namespaces
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "ZebraProp", "val1");
    meta.SetProperty("http://purl.org/dc/elements/1.1/", "title", "MyTitle");
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "AppleProp", "val2");
    
    EXPECT_NO_THROW(meta.Sort());
    
    // Verify properties still accessible
    std::string value;
    EXPECT_TRUE(meta.GetProperty("http://ns.adobe.com/xap/1.0/", "ZebraProp", &value, nullptr));
    EXPECT_EQ("val1", value);
    EXPECT_TRUE(meta.GetProperty("http://ns.adobe.com/xap/1.0/", "AppleProp", &value, nullptr));
    EXPECT_EQ("val2", value);
}

TEST_F(SortWithinOffspringTest_2145, SortUnorderedArrayDuplicateValues_2145) {
    SXMPMeta meta;
    // Unordered array with duplicate values - stable_sort should preserve relative order
    meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "Tags",
                         kXMP_PropArrayIsUnordered, "Beta", 0);
    meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "Tags",
                         kXMP_PropArrayIsUnordered, "Alpha", 0);
    meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "Tags",
                         kXMP_PropArrayIsUnordered, "Beta", 0);
    meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "Tags",
                         kXMP_PropArrayIsUnordered, "Alpha", 0);
    
    meta.Sort();
    
    std::string value;
    EXPECT_TRUE(meta.GetArrayItem("http://ns.adobe.com/xap/1.0/", "Tags", 1, &value, nullptr));
    EXPECT_EQ("Alpha", value);
    EXPECT_TRUE(meta.GetArrayItem("http://ns.adobe.com/xap/1.0/", "Tags", 2, &value, nullptr));
    EXPECT_EQ("Alpha", value);
    EXPECT_TRUE(meta.GetArrayItem("http://ns.adobe.com/xap/1.0/", "Tags", 3, &value, nullptr));
    EXPECT_EQ("Beta", value);
    EXPECT_TRUE(meta.GetArrayItem("http://ns.adobe.com/xap/1.0/", "Tags", 4, &value, nullptr));
    EXPECT_EQ("Beta", value);
}

TEST_F(SortWithinOffspringTest_2145, SortIdempotent_2145) {
    SXMPMeta meta;
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "Zebra", "val1");
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "Apple", "val2");
    meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "Keywords",
                         kXMP_PropArrayIsUnordered, "Zulu", 0);
    meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "Keywords",
                         kXMP_PropArrayIsUnordered, "Alpha", 0);
    
    meta.Sort();
    
    // Serialize after first sort
    std::string serialized1;
    meta.SerializeToBuffer(&serialized1, kXMP_UseCompactFormat);
    
    // Sort again
    meta.Sort();
    
    std::string serialized2;
    meta.SerializeToBuffer(&serialized2, kXMP_UseCompactFormat);
    
    // Should be identical - sorting is idempotent
    EXPECT_EQ(serialized1, serialized2);
}

TEST_F(SortWithinOffspringTest_2145, SortNestedStructs_2145) {
    SXMPMeta meta;
    // Create nested structure
    meta.SetStructField("http://ns.adobe.com/xap/1.0/", "Outer",
                        "http://ns.adobe.com/xap/1.0/", "ZField", "zval");
    meta.SetStructField("http://ns.adobe.com/xap/1.0/", "Outer",
                        "http://ns.adobe.com/xap/1.0/", "AField", "aval");
    
    meta.Sort();
    
    // Verify nested struct children are sorted
    SXMPIterator iter(meta, "http://ns.adobe.com/xap/1.0/", "Outer", kXMP_IterJustChildren);
    std::string schemaNS, propPath, propValue;
    std::vector<std::string> fieldNames;
    
    while (iter.Next(&schemaNS, &propPath, &propValue, nullptr)) {
        fieldNames.push_back(propPath);
    }
    
    ASSERT_EQ(2u, fieldNames.size());
    EXPECT_LE(fieldNames[0], fieldNames[1]);
}

TEST_F(SortWithinOffspringTest_2145, SortSingleElementArray_2145) {
    SXMPMeta meta;
    meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "SingleBag",
                         kXMP_PropArrayIsUnordered, "OnlyItem", 0);
    
    EXPECT_NO_THROW(meta.Sort());
    
    std::string value;
    EXPECT_TRUE(meta.GetArrayItem("http://ns.adobe.com/xap/1.0/", "SingleBag", 1, &value, nullptr));
    EXPECT_EQ("OnlyItem", value);
}

TEST_F(SortWithinOffspringTest_2145, SortWithQualifiers_2145) {
    SXMPMeta meta;
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "TestProp", "TestValue");
    meta.SetQualifier("http://ns.adobe.com/xap/1.0/", "TestProp",
                      "http://ns.adobe.com/xap/1.0/", "ZQual", "qualval1");
    meta.SetQualifier("http://ns.adobe.com/xap/1.0/", "TestProp",
                      "http://ns.adobe.com/xap/1.0/", "AQual", "qualval2");
    
    EXPECT_NO_THROW(meta.Sort());
    
    // Qualifiers should be sorted by name
    std::string value;
    EXPECT_TRUE(meta.GetProperty("http://ns.adobe.com/xap/1.0/", "TestProp", &value, nullptr));
    EXPECT_EQ("TestValue", value);
    
    EXPECT_TRUE(meta.GetQualifier("http://ns.adobe.com/xap/1.0/", "TestProp",
                                   "http://ns.adobe.com/xap/1.0/", "AQual", &value, nullptr));
    EXPECT_EQ("qualval2", value);
    EXPECT_TRUE(meta.GetQualifier("http://ns.adobe.com/xap/1.0/", "TestProp",
                                   "http://ns.adobe.com/xap/1.0/", "ZQual", &value, nullptr));
    EXPECT_EQ("qualval1", value);
}

TEST_F(SortWithinOffspringTest_2145, SortAlternateArrayNotAltText_2145) {
    SXMPMeta meta;
    // Alternate array (not alt-text) - should not sort children by value or lang
    meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "AltArr",
                         kXMP_PropArrayIsAlternate, "Zvalue", 0);
    meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "AltArr",
                         kXMP_PropArrayIsAlternate, "Avalue", 0);
    
    meta.Sort();
    
    // Alternate (non-alt-text) arrays are still arrays but not unordered,
    // so the order should be preserved
    std::string value;
    EXPECT_TRUE(meta.GetArrayItem("http://ns.adobe.com/xap/1.0/", "AltArr", 1, &value, nullptr));
    EXPECT_EQ("Zvalue", value);
    EXPECT_TRUE(meta.GetArrayItem("http://ns.adobe.com/xap/1.0/", "AltArr", 2, &value, nullptr));
    EXPECT_EQ("Avalue", value);
}

TEST_F(SortWithinOffspringTest_2145, SortLargeUnorderedArray_2145) {
    SXMPMeta meta;
    // Add many items to an unordered array
    std::vector<std::string> items = {"Zulu", "Yankee", "X-ray", "Whiskey", "Victor",
                                       "Uniform", "Tango", "Sierra", "Romeo", "Quebec",
                                       "Papa", "Oscar", "November", "Mike", "Lima",
                                       "Kilo", "Juliet", "India", "Hotel", "Golf",
                                       "Foxtrot", "Echo", "Delta", "Charlie", "Bravo", "Alpha"};
    
    for (const auto& item : items) {
        meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "BigBag",
                             kXMP_PropArrayIsUnordered, item.c_str(), 0);
    }
    
    meta.Sort();
    
    // Values should be sorted
    std::vector<std::string> sorted_items = items;
    std::sort(sorted_items.begin(), sorted_items.end());
    
    for (size_t i = 0; i < sorted_items.size(); ++i) {
        std::string value;
        EXPECT_TRUE(meta.GetArrayItem("http://ns.adobe.com/xap/1.0/", "BigBag",
                                       static_cast<XMP_Index>(i + 1), &value, nullptr));
        EXPECT_EQ(sorted_items[i], value) << "Mismatch at index " << i;
    }
}

TEST_F(SortWithinOffspringTest_2145, SortPreservesPropertyCount_2145) {
    SXMPMeta meta;
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "Prop1", "val1");
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "Prop2", "val2");
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "Prop3", "val3");
    
    int countBefore = meta.CountArrayItems("http://ns.adobe.com/xap/1.0/", "Prop1");
    
    meta.Sort();
    
    // All properties should still be accessible
    std::string value;
    EXPECT_TRUE(meta.GetProperty("http://ns.adobe.com/xap/1.0/", "Prop1", &value, nullptr));
    EXPECT_EQ("val1", value);
    EXPECT_TRUE(meta.GetProperty("http://ns.adobe.com/xap/1.0/", "Prop2", &value, nullptr));
    EXPECT_EQ("val2", value);
    EXPECT_TRUE(meta.GetProperty("http://ns.adobe.com/xap/1.0/", "Prop3", &value, nullptr));
    EXPECT_EQ("val3", value);
}

TEST_F(SortWithinOffspringTest_2145, SortArrayItemCount_2145) {
    SXMPMeta meta;
    meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "Bag",
                         kXMP_PropArrayIsUnordered, "C", 0);
    meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "Bag",
                         kXMP_PropArrayIsUnordered, "A", 0);
    meta.AppendArrayItem("http://ns.adobe.com/xap/1.0/", "Bag",
                         kXMP_PropArrayIsUnordered, "B", 0);
    
    XMP_Index countBefore = meta.CountArrayItems("http://ns.adobe.com/xap/1.0/", "Bag");
    
    meta.Sort();
    
    XMP_Index countAfter = meta.CountArrayItems("http://ns.adobe.com/xap/1.0/", "Bag");
    EXPECT_EQ(countBefore, countAfter);
    EXPECT_EQ(3, countAfter);
}
