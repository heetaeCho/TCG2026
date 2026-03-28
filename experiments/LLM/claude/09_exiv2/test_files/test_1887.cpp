#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary XMP SDK headers
#define TXMP_STRING_TYPE std::string
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "XMPCore_Impl.hpp"

// We need access to the static function, so include the implementation
// This is a testing technique for static (file-scope) functions
#include "XMPCore_Impl.cpp"

class LookupQualSelectorTest_1887 : public ::testing::Test {
protected:
    void SetUp() override {
        arrayNode = new XMP_Node(nullptr, "arrayNode", 0);
    }

    void TearDown() override {
        // Clean up all children and qualifiers
        for (auto* child : arrayNode->children) {
            for (auto* qual : child->qualifiers) {
                delete qual;
            }
            child->qualifiers.clear();
            delete child;
        }
        arrayNode->children.clear();
        delete arrayNode;
    }

    XMP_Node* AddChildWithQualifier(const std::string& childName, const std::string& childValue,
                                     const std::string& qualName, const std::string& qualValue) {
        XMP_Node* child = new XMP_Node(arrayNode, childName, childValue, 0);
        XMP_Node* qual = new XMP_Node(child, qualName, qualValue, 0);
        child->qualifiers.push_back(qual);
        arrayNode->children.push_back(child);
        return child;
    }

    XMP_Node* AddChildNoQualifiers(const std::string& childName, const std::string& childValue) {
        XMP_Node* child = new XMP_Node(arrayNode, childName, childValue, 0);
        arrayNode->children.push_back(child);
        return child;
    }

    XMP_Node* arrayNode;
};

// Test: When array has no children, should return -1 for non-lang qualifier
TEST_F(LookupQualSelectorTest_1887, EmptyArrayReturnsNegativeOne_1887) {
    XMP_VarString qualName = "myQual";
    XMP_VarString qualValue = "someValue";
    XMP_Index result = LookupQualSelector(arrayNode, qualName, qualValue);
    EXPECT_EQ(result, -1);
}

// Test: Single child with matching qualifier returns index 0
TEST_F(LookupQualSelectorTest_1887, SingleChildMatchingQualReturnsZero_1887) {
    AddChildWithQualifier("item1", "val1", "myQual", "matchValue");
    XMP_VarString qualName = "myQual";
    XMP_VarString qualValue = "matchValue";
    XMP_Index result = LookupQualSelector(arrayNode, qualName, qualValue);
    EXPECT_EQ(result, 0);
}

// Test: Single child with non-matching qualifier value returns -1
TEST_F(LookupQualSelectorTest_1887, SingleChildNonMatchingQualValueReturnsNegOne_1887) {
    AddChildWithQualifier("item1", "val1", "myQual", "matchValue");
    XMP_VarString qualName = "myQual";
    XMP_VarString qualValue = "differentValue";
    XMP_Index result = LookupQualSelector(arrayNode, qualName, qualValue);
    EXPECT_EQ(result, -1);
}

// Test: Single child with non-matching qualifier name returns -1
TEST_F(LookupQualSelectorTest_1887, SingleChildNonMatchingQualNameReturnsNegOne_1887) {
    AddChildWithQualifier("item1", "val1", "otherQual", "matchValue");
    XMP_VarString qualName = "myQual";
    XMP_VarString qualValue = "matchValue";
    XMP_Index result = LookupQualSelector(arrayNode, qualName, qualValue);
    EXPECT_EQ(result, -1);
}

// Test: Multiple children, match is at second child
TEST_F(LookupQualSelectorTest_1887, MultipleChildrenMatchAtSecondIndex_1887) {
    AddChildWithQualifier("item1", "val1", "myQual", "noMatch");
    AddChildWithQualifier("item2", "val2", "myQual", "matchValue");
    AddChildWithQualifier("item3", "val3", "myQual", "alsoNoMatch");
    XMP_VarString qualName = "myQual";
    XMP_VarString qualValue = "matchValue";
    XMP_Index result = LookupQualSelector(arrayNode, qualName, qualValue);
    EXPECT_EQ(result, 1);
}

// Test: Multiple children, match is at last child
TEST_F(LookupQualSelectorTest_1887, MultipleChildrenMatchAtLastIndex_1887) {
    AddChildWithQualifier("item1", "val1", "myQual", "noMatch1");
    AddChildWithQualifier("item2", "val2", "myQual", "noMatch2");
    AddChildWithQualifier("item3", "val3", "myQual", "matchValue");
    XMP_VarString qualName = "myQual";
    XMP_VarString qualValue = "matchValue";
    XMP_Index result = LookupQualSelector(arrayNode, qualName, qualValue);
    EXPECT_EQ(result, 2);
}

// Test: Child with multiple qualifiers, match on second qualifier
TEST_F(LookupQualSelectorTest_1887, ChildWithMultipleQualsMatchOnSecond_1887) {
    XMP_Node* child = new XMP_Node(arrayNode, "item1", "val1", 0);
    XMP_Node* qual1 = new XMP_Node(child, "qualA", "valA", 0);
    XMP_Node* qual2 = new XMP_Node(child, "qualB", "valB", 0);
    child->qualifiers.push_back(qual1);
    child->qualifiers.push_back(qual2);
    arrayNode->children.push_back(child);

    XMP_VarString qualName = "qualB";
    XMP_VarString qualValue = "valB";
    XMP_Index result = LookupQualSelector(arrayNode, qualName, qualValue);
    EXPECT_EQ(result, 0);
}

// Test: Child with no qualifiers returns -1
TEST_F(LookupQualSelectorTest_1887, ChildWithNoQualifiersReturnsNegOne_1887) {
    AddChildNoQualifiers("item1", "val1");
    XMP_VarString qualName = "myQual";
    XMP_VarString qualValue = "matchValue";
    XMP_Index result = LookupQualSelector(arrayNode, qualName, qualValue);
    EXPECT_EQ(result, -1);
}

// Test: xml:lang qualifier triggers NormalizeLangValue and LookupLangItem path
TEST_F(LookupQualSelectorTest_1887, XmlLangQualUsesLangLookup_1887) {
    // Create an alt-text array with xml:lang qualifiers
    XMP_Node* child1 = new XMP_Node(arrayNode, "item1", "English text", 0);
    XMP_Node* langQual1 = new XMP_Node(child1, "xml:lang", "en", 0);
    child1->qualifiers.push_back(langQual1);
    arrayNode->children.push_back(child1);

    XMP_Node* child2 = new XMP_Node(arrayNode, "item2", "French text", 0);
    XMP_Node* langQual2 = new XMP_Node(child2, "xml:lang", "fr", 0);
    child2->qualifiers.push_back(langQual2);
    arrayNode->children.push_back(child2);

    XMP_VarString qualName = "xml:lang";
    XMP_VarString qualValue = "en";
    XMP_Index result = LookupQualSelector(arrayNode, qualName, qualValue);
    // The result depends on LookupLangItem implementation, but should find it
    // If the lang item exists, it should return a valid index (>= 0)
    EXPECT_GE(result, 0);
}

// Test: xml:lang qualifier with non-existing language returns -1
TEST_F(LookupQualSelectorTest_1887, XmlLangQualNonExistingLangReturnsNegOne_1887) {
    XMP_Node* child1 = new XMP_Node(arrayNode, "item1", "English text", 0);
    XMP_Node* langQual1 = new XMP_Node(child1, "xml:lang", "en", 0);
    child1->qualifiers.push_back(langQual1);
    arrayNode->children.push_back(child1);

    XMP_VarString qualName = "xml:lang";
    XMP_VarString qualValue = "de";
    XMP_Index result = LookupQualSelector(arrayNode, qualName, qualValue);
    EXPECT_EQ(result, -1);
}

// Test: First match is returned when multiple children match
TEST_F(LookupQualSelectorTest_1887, FirstMatchReturnedWhenMultipleMatch_1887) {
    AddChildWithQualifier("item1", "val1", "myQual", "matchValue");
    AddChildWithQualifier("item2", "val2", "myQual", "matchValue");
    AddChildWithQualifier("item3", "val3", "myQual", "matchValue");
    XMP_VarString qualName = "myQual";
    XMP_VarString qualValue = "matchValue";
    XMP_Index result = LookupQualSelector(arrayNode, qualName, qualValue);
    EXPECT_EQ(result, 0);
}

// Test: Qualifier name matches but value differs across all children
TEST_F(LookupQualSelectorTest_1887, QualNameMatchesButValuesDiffer_1887) {
    AddChildWithQualifier("item1", "val1", "myQual", "val_a");
    AddChildWithQualifier("item2", "val2", "myQual", "val_b");
    AddChildWithQualifier("item3", "val3", "myQual", "val_c");
    XMP_VarString qualName = "myQual";
    XMP_VarString qualValue = "val_d";
    XMP_Index result = LookupQualSelector(arrayNode, qualName, qualValue);
    EXPECT_EQ(result, -1);
}

// Test: Empty qualifier name and value
TEST_F(LookupQualSelectorTest_1887, EmptyQualNameAndValue_1887) {
    AddChildWithQualifier("item1", "val1", "", "");
    XMP_VarString qualName = "";
    XMP_VarString qualValue = "";
    XMP_Index result = LookupQualSelector(arrayNode, qualName, qualValue);
    EXPECT_EQ(result, 0);
}

// Test: Qualifier value is empty string, matches empty qualifier value
TEST_F(LookupQualSelectorTest_1887, EmptyQualValueMatchesEmptyQual_1887) {
    AddChildWithQualifier("item1", "val1", "myQual", "");
    XMP_VarString qualName = "myQual";
    XMP_VarString qualValue = "";
    XMP_Index result = LookupQualSelector(arrayNode, qualName, qualValue);
    EXPECT_EQ(result, 0);
}

// Test: Large number of children, match at end
TEST_F(LookupQualSelectorTest_1887, LargeArrayMatchAtEnd_1887) {
    for (int i = 0; i < 100; ++i) {
        std::string name = "item" + std::to_string(i);
        std::string val = "val" + std::to_string(i);
        AddChildWithQualifier(name, val, "myQual", val);
    }
    XMP_VarString qualName = "myQual";
    XMP_VarString qualValue = "val99";
    XMP_Index result = LookupQualSelector(arrayNode, qualName, qualValue);
    EXPECT_EQ(result, 99);
}

// Test: xml:lang with uppercase value (NormalizeLangValue should normalize)
TEST_F(LookupQualSelectorTest_1887, XmlLangNormalizesCase_1887) {
    XMP_Node* child1 = new XMP_Node(arrayNode, "item1", "English text", 0);
    XMP_Node* langQual1 = new XMP_Node(child1, "xml:lang", "en", 0);
    child1->qualifiers.push_back(langQual1);
    arrayNode->children.push_back(child1);

    XMP_VarString qualName = "xml:lang";
    XMP_VarString qualValue = "EN";  // uppercase, should be normalized to "en"
    XMP_Index result = LookupQualSelector(arrayNode, qualName, qualValue);
    // After normalization, "EN" should become "en" and match
    EXPECT_GE(result, 0);
}
