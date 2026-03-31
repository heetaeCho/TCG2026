#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary headers
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// Forward declaration of the function under test
XMP_Index LookupLangItem(const XMP_Node* arrayNode, XMP_VarString& lang);

class LookupLangItemTest_1898 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any allocated nodes
        for (auto* node : allocated_nodes_) {
            delete node;
        }
        allocated_nodes_.clear();
    }

    // Helper to create a child node with xml:lang qualifier
    XMP_Node* CreateLangItem(XMP_Node* parent, const std::string& value, const std::string& lang) {
        XMP_Node* item = new XMP_Node(parent, "rdf:li", value.c_str(), 0);
        item->parent = parent;
        allocated_nodes_.push_back(item);

        XMP_Node* qualifier = new XMP_Node(item, "xml:lang", lang.c_str(), kXMP_PropIsQualifier);
        qualifier->parent = item;
        item->qualifiers.push_back(qualifier);
        allocated_nodes_.push_back(qualifier);

        return item;
    }

    // Helper to create a child node without qualifiers
    XMP_Node* CreateItemWithoutQualifiers(XMP_Node* parent, const std::string& value) {
        XMP_Node* item = new XMP_Node(parent, "rdf:li", value.c_str(), 0);
        item->parent = parent;
        allocated_nodes_.push_back(item);
        return item;
    }

    // Helper to create a child node with a non-lang qualifier
    XMP_Node* CreateItemWithNonLangQualifier(XMP_Node* parent, const std::string& value,
                                              const std::string& qualName, const std::string& qualValue) {
        XMP_Node* item = new XMP_Node(parent, "rdf:li", value.c_str(), 0);
        item->parent = parent;
        allocated_nodes_.push_back(item);

        XMP_Node* qualifier = new XMP_Node(item, qualName.c_str(), qualValue.c_str(), kXMP_PropIsQualifier);
        qualifier->parent = item;
        item->qualifiers.push_back(qualifier);
        allocated_nodes_.push_back(qualifier);

        return item;
    }

    std::vector<XMP_Node*> allocated_nodes_;
};

// Test that a non-array node throws an exception
TEST_F(LookupLangItemTest_1898, ThrowsWhenNodeIsNotArray_1898) {
    XMP_Node node(nullptr, "test", 0);  // options = 0, not an array
    XMP_VarString lang = "en";

    EXPECT_THROW(LookupLangItem(&node, lang), XMP_Error);
}

// Test that a struct node (not array) throws an exception
TEST_F(LookupLangItemTest_1898, ThrowsWhenNodeIsStruct_1898) {
    XMP_Node node(nullptr, "test", kXMP_PropValueIsStruct);
    XMP_VarString lang = "en";

    EXPECT_THROW(LookupLangItem(&node, lang), XMP_Error);
}

// Test with an empty array returns -1
TEST_F(LookupLangItemTest_1898, EmptyArrayReturnsNegativeOne_1898) {
    XMP_Node arrayNode(nullptr, "testArray", kXMP_PropValueIsArray);
    XMP_VarString lang = "en";

    XMP_Index result = LookupLangItem(&arrayNode, lang);
    EXPECT_EQ(result, -1);
}

// Test finding a language item that exists at the first position
TEST_F(LookupLangItemTest_1898, FindsLangAtFirstPosition_1898) {
    XMP_Node arrayNode(nullptr, "testArray", kXMP_PropValueIsArray);

    XMP_Node* item = CreateLangItem(&arrayNode, "Hello", "en");
    arrayNode.children.push_back(item);

    XMP_VarString lang = "en";
    XMP_Index result = LookupLangItem(&arrayNode, lang);
    EXPECT_EQ(result, 0);
}

// Test finding a language item at a middle position
TEST_F(LookupLangItemTest_1898, FindsLangAtMiddlePosition_1898) {
    XMP_Node arrayNode(nullptr, "testArray", kXMP_PropValueIsArray);

    XMP_Node* item1 = CreateLangItem(&arrayNode, "Bonjour", "fr");
    XMP_Node* item2 = CreateLangItem(&arrayNode, "Hello", "en");
    XMP_Node* item3 = CreateLangItem(&arrayNode, "Hola", "es");

    arrayNode.children.push_back(item1);
    arrayNode.children.push_back(item2);
    arrayNode.children.push_back(item3);

    XMP_VarString lang = "en";
    XMP_Index result = LookupLangItem(&arrayNode, lang);
    EXPECT_EQ(result, 1);
}

// Test finding a language item at the last position
TEST_F(LookupLangItemTest_1898, FindsLangAtLastPosition_1898) {
    XMP_Node arrayNode(nullptr, "testArray", kXMP_PropValueIsArray);

    XMP_Node* item1 = CreateLangItem(&arrayNode, "Bonjour", "fr");
    XMP_Node* item2 = CreateLangItem(&arrayNode, "Hello", "en");
    XMP_Node* item3 = CreateLangItem(&arrayNode, "Hola", "es");

    arrayNode.children.push_back(item1);
    arrayNode.children.push_back(item2);
    arrayNode.children.push_back(item3);

    XMP_VarString lang = "es";
    XMP_Index result = LookupLangItem(&arrayNode, lang);
    EXPECT_EQ(result, 2);
}

// Test that a non-existent language returns -1
TEST_F(LookupLangItemTest_1898, NonExistentLangReturnsNegativeOne_1898) {
    XMP_Node arrayNode(nullptr, "testArray", kXMP_PropValueIsArray);

    XMP_Node* item1 = CreateLangItem(&arrayNode, "Bonjour", "fr");
    XMP_Node* item2 = CreateLangItem(&arrayNode, "Hello", "en");

    arrayNode.children.push_back(item1);
    arrayNode.children.push_back(item2);

    XMP_VarString lang = "de";
    XMP_Index result = LookupLangItem(&arrayNode, lang);
    EXPECT_EQ(result, -1);
}

// Test that items without qualifiers are skipped
TEST_F(LookupLangItemTest_1898, SkipsItemsWithoutQualifiers_1898) {
    XMP_Node arrayNode(nullptr, "testArray", kXMP_PropValueIsArray);

    XMP_Node* item1 = CreateItemWithoutQualifiers(&arrayNode, "NoLang");
    XMP_Node* item2 = CreateLangItem(&arrayNode, "Hello", "en");

    arrayNode.children.push_back(item1);
    arrayNode.children.push_back(item2);

    XMP_VarString lang = "en";
    XMP_Index result = LookupLangItem(&arrayNode, lang);
    EXPECT_EQ(result, 1);
}

// Test that items with non-lang qualifiers are skipped
TEST_F(LookupLangItemTest_1898, SkipsItemsWithNonLangQualifier_1898) {
    XMP_Node arrayNode(nullptr, "testArray", kXMP_PropValueIsArray);

    XMP_Node* item1 = CreateItemWithNonLangQualifier(&arrayNode, "SomeValue", "rdf:type", "someType");
    XMP_Node* item2 = CreateLangItem(&arrayNode, "Hello", "en");

    arrayNode.children.push_back(item1);
    arrayNode.children.push_back(item2);

    XMP_VarString lang = "en";
    XMP_Index result = LookupLangItem(&arrayNode, lang);
    EXPECT_EQ(result, 1);
}

// Test with ordered array option
TEST_F(LookupLangItemTest_1898, WorksWithOrderedArray_1898) {
    XMP_Node arrayNode(nullptr, "testArray", kXMP_PropArrayIsOrdered);

    XMP_Node* item = CreateLangItem(&arrayNode, "Hello", "en");
    arrayNode.children.push_back(item);

    XMP_VarString lang = "en";
    XMP_Index result = LookupLangItem(&arrayNode, lang);
    EXPECT_EQ(result, 0);
}

// Test with alternate array option
TEST_F(LookupLangItemTest_1898, WorksWithAlternateArray_1898) {
    XMP_Node arrayNode(nullptr, "testArray", kXMP_PropArrayIsAlternate);

    XMP_Node* item = CreateLangItem(&arrayNode, "Hello", "en");
    arrayNode.children.push_back(item);

    XMP_VarString lang = "en";
    XMP_Index result = LookupLangItem(&arrayNode, lang);
    EXPECT_EQ(result, 0);
}

// Test with alt-text array option
TEST_F(LookupLangItemTest_1898, WorksWithAltTextArray_1898) {
    XMP_Node arrayNode(nullptr, "testArray", kXMP_PropArrayIsAltText);

    XMP_Node* item = CreateLangItem(&arrayNode, "Hello", "en");
    arrayNode.children.push_back(item);

    XMP_VarString lang = "en";
    XMP_Index result = LookupLangItem(&arrayNode, lang);
    EXPECT_EQ(result, 0);
}

// Test case sensitivity of language matching
TEST_F(LookupLangItemTest_1898, LangMatchIsCaseSensitive_1898) {
    XMP_Node arrayNode(nullptr, "testArray", kXMP_PropValueIsArray);

    XMP_Node* item = CreateLangItem(&arrayNode, "Hello", "en");
    arrayNode.children.push_back(item);

    XMP_VarString lang = "EN";
    XMP_Index result = LookupLangItem(&arrayNode, lang);
    // Exact string comparison, so "EN" != "en"
    EXPECT_EQ(result, -1);
}

// Test with x-default language
TEST_F(LookupLangItemTest_1898, FindsXDefault_1898) {
    XMP_Node arrayNode(nullptr, "testArray", kXMP_PropValueIsArray);

    XMP_Node* item1 = CreateLangItem(&arrayNode, "Default", "x-default");
    XMP_Node* item2 = CreateLangItem(&arrayNode, "Hello", "en");

    arrayNode.children.push_back(item1);
    arrayNode.children.push_back(item2);

    XMP_VarString lang = "x-default";
    XMP_Index result = LookupLangItem(&arrayNode, lang);
    EXPECT_EQ(result, 0);
}

// Test with multiple items, all without qualifiers - should return -1
TEST_F(LookupLangItemTest_1898, AllItemsWithoutQualifiersReturnsNegativeOne_1898) {
    XMP_Node arrayNode(nullptr, "testArray", kXMP_PropValueIsArray);

    XMP_Node* item1 = CreateItemWithoutQualifiers(&arrayNode, "Value1");
    XMP_Node* item2 = CreateItemWithoutQualifiers(&arrayNode, "Value2");

    arrayNode.children.push_back(item1);
    arrayNode.children.push_back(item2);

    XMP_VarString lang = "en";
    XMP_Index result = LookupLangItem(&arrayNode, lang);
    EXPECT_EQ(result, -1);
}

// Test with empty language string
TEST_F(LookupLangItemTest_1898, EmptyLangStringNotFound_1898) {
    XMP_Node arrayNode(nullptr, "testArray", kXMP_PropValueIsArray);

    XMP_Node* item = CreateLangItem(&arrayNode, "Hello", "en");
    arrayNode.children.push_back(item);

    XMP_VarString lang = "";
    XMP_Index result = LookupLangItem(&arrayNode, lang);
    EXPECT_EQ(result, -1);
}

// Test with empty language string that matches an item with empty lang qualifier
TEST_F(LookupLangItemTest_1898, EmptyLangStringMatchesEmptyQualifier_1898) {
    XMP_Node arrayNode(nullptr, "testArray", kXMP_PropValueIsArray);

    XMP_Node* item = CreateLangItem(&arrayNode, "Hello", "");
    arrayNode.children.push_back(item);

    XMP_VarString lang = "";
    XMP_Index result = LookupLangItem(&arrayNode, lang);
    EXPECT_EQ(result, 0);
}

// Test that the first matching language is returned when duplicates exist
TEST_F(LookupLangItemTest_1898, ReturnsFirstMatchWhenDuplicatesExist_1898) {
    XMP_Node arrayNode(nullptr, "testArray", kXMP_PropValueIsArray);

    XMP_Node* item1 = CreateLangItem(&arrayNode, "Hello1", "en");
    XMP_Node* item2 = CreateLangItem(&arrayNode, "Hello2", "en");

    arrayNode.children.push_back(item1);
    arrayNode.children.push_back(item2);

    XMP_VarString lang = "en";
    XMP_Index result = LookupLangItem(&arrayNode, lang);
    EXPECT_EQ(result, 0);
}

// Test with a single item that has a non-lang qualifier first
TEST_F(LookupLangItemTest_1898, SingleItemNonLangQualifierReturnsNegativeOne_1898) {
    XMP_Node arrayNode(nullptr, "testArray", kXMP_PropValueIsArray);

    XMP_Node* item = CreateItemWithNonLangQualifier(&arrayNode, "Value", "rdf:type", "someType");
    arrayNode.children.push_back(item);

    XMP_VarString lang = "en";
    XMP_Index result = LookupLangItem(&arrayNode, lang);
    EXPECT_EQ(result, -1);
}

// Test with a large number of children
TEST_F(LookupLangItemTest_1898, LargeArrayFindsLastItem_1898) {
    XMP_Node arrayNode(nullptr, "testArray", kXMP_PropValueIsArray);

    // Add 100 items with different languages
    for (int i = 0; i < 100; ++i) {
        std::string lang = "lang-" + std::to_string(i);
        std::string value = "value-" + std::to_string(i);
        XMP_Node* item = CreateLangItem(&arrayNode, value, lang);
        arrayNode.children.push_back(item);
    }

    XMP_VarString lang = "lang-99";
    XMP_Index result = LookupLangItem(&arrayNode, lang);
    EXPECT_EQ(result, 99);
}

// Test that the error code in the exception is kXMPErr_BadXPath
TEST_F(LookupLangItemTest_1898, ThrowsWithBadXPathError_1898) {
    XMP_Node node(nullptr, "test", 0);
    XMP_VarString lang = "en";

    try {
        LookupLangItem(&node, lang);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadXPath);
    }
}
