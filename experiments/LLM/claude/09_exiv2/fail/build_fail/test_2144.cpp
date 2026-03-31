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
