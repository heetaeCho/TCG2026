#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary headers
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// Since CanBeRDFAttrProp is a static function in a .cpp file, we need to
// either include the .cpp or redeclare/redefine it for testing purposes.
// We'll include the relevant portion or use a test-accessible declaration.

// Forward declare or include the function. Since it's static in the .cpp file,
// we need to make it accessible for testing. One approach is to include the .cpp file.
// This is a common pattern for testing static functions.

// We need to expose the static function for testing
namespace {
    // Include the source file to get access to the static function
    // This brings the static function into this translation unit
}

// If direct inclusion doesn't work, we replicate the function signature for linkage.
// For the purpose of this test, we include the cpp to access the static function.
#include "XMPMeta-Serialize.cpp"

class CanBeRDFAttrPropTest_2108 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any allocated nodes
    }
};

// Test: A simple property node with a normal name, no qualifiers, no special options
// should return true
TEST_F(CanBeRDFAttrPropTest_2108, SimplePropertyReturnsTrue_2108) {
    XMP_Node node(nullptr, "simpleProp", 0);
    EXPECT_TRUE(CanBeRDFAttrProp(&node));
}

// Test: A node whose name starts with '[' should return false
TEST_F(CanBeRDFAttrPropTest_2108, NameStartsWithBracketReturnsFalse_2108) {
    XMP_Node node(nullptr, "[1]", 0);
    EXPECT_FALSE(CanBeRDFAttrProp(&node));
}

// Test: A node with non-empty qualifiers should return false
TEST_F(CanBeRDFAttrPropTest_2108, HasQualifiersReturnsFalse_2108) {
    XMP_Node node(nullptr, "prop", 0);
    XMP_Node* qualifier = new XMP_Node(&node, "qualifier", 0);
    node.qualifiers.push_back(qualifier);
    EXPECT_FALSE(CanBeRDFAttrProp(&node));
    // Cleanup
    node.RemoveQualifiers();
}

// Test: A node with kXMP_PropValueIsURI option should return false
TEST_F(CanBeRDFAttrPropTest_2108, PropValueIsURIReturnsFalse_2108) {
    XMP_Node node(nullptr, "prop", kXMP_PropValueIsURI);
    EXPECT_FALSE(CanBeRDFAttrProp(&node));
}

// Test: A node with kXMP_PropValueIsStruct (part of CompositeMask) should return false
TEST_F(CanBeRDFAttrPropTest_2108, PropValueIsStructReturnsFalse_2108) {
    XMP_Node node(nullptr, "prop", kXMP_PropValueIsStruct);
    EXPECT_FALSE(CanBeRDFAttrProp(&node));
}

// Test: A node with kXMP_PropValueIsArray (part of CompositeMask) should return false
TEST_F(CanBeRDFAttrPropTest_2108, PropValueIsArrayReturnsFalse_2108) {
    XMP_Node node(nullptr, "prop", kXMP_PropValueIsArray);
    EXPECT_FALSE(CanBeRDFAttrProp(&node));
}

// Test: A node with kXMP_PropArrayIsOrdered (part of CompositeMask) should return false
TEST_F(CanBeRDFAttrPropTest_2108, PropArrayIsOrderedReturnsFalse_2108) {
    XMP_Node node(nullptr, "prop", kXMP_PropArrayIsOrdered);
    EXPECT_FALSE(CanBeRDFAttrProp(&node));
}

// Test: A node with kXMP_PropArrayIsAlternate (part of CompositeMask) should return false
TEST_F(CanBeRDFAttrPropTest_2108, PropArrayIsAlternateReturnsFalse_2108) {
    XMP_Node node(nullptr, "prop", kXMP_PropArrayIsAlternate);
    EXPECT_FALSE(CanBeRDFAttrProp(&node));
}

// Test: A node with kXMP_PropArrayIsAltText (part of CompositeMask) should return false
TEST_F(CanBeRDFAttrPropTest_2108, PropArrayIsAltTextReturnsFalse_2108) {
    XMP_Node node(nullptr, "prop", kXMP_PropArrayIsAltText);
    EXPECT_FALSE(CanBeRDFAttrProp(&node));
}

// Test: A node with kXMP_PropCompositeMask should return false
TEST_F(CanBeRDFAttrPropTest_2108, PropCompositeMaskReturnsFalse_2108) {
    XMP_Node node(nullptr, "prop", kXMP_PropCompositeMask);
    EXPECT_FALSE(CanBeRDFAttrProp(&node));
}

// Test: A node with options that are not URI and not composite should return true
TEST_F(CanBeRDFAttrPropTest_2108, NonConflictingOptionsReturnsTrue_2108) {
    XMP_Node node(nullptr, "prop", kXMP_PropHasAliases);
    EXPECT_TRUE(CanBeRDFAttrProp(&node));
}

// Test: A node with kXMP_PropIsInternal option (not URI, not composite) returns true
TEST_F(CanBeRDFAttrPropTest_2108, PropIsInternalReturnsTrue_2108) {
    XMP_Node node(nullptr, "prop", kXMP_PropIsInternal);
    EXPECT_TRUE(CanBeRDFAttrProp(&node));
}

// Test: A node with both kXMP_PropValueIsURI and composite options should return false
TEST_F(CanBeRDFAttrPropTest_2108, CombinedURIAndCompositeReturnsFalse_2108) {
    XMP_Node node(nullptr, "prop", kXMP_PropValueIsURI | kXMP_PropValueIsStruct);
    EXPECT_FALSE(CanBeRDFAttrProp(&node));
}

// Test: Name starts with '[' combined with qualifiers - first check (bracket) fails
TEST_F(CanBeRDFAttrPropTest_2108, BracketNameWithQualifiersReturnsFalse_2108) {
    XMP_Node node(nullptr, "[item]", 0);
    XMP_Node* qualifier = new XMP_Node(&node, "qual", 0);
    node.qualifiers.push_back(qualifier);
    EXPECT_FALSE(CanBeRDFAttrProp(&node));
    node.RemoveQualifiers();
}

// Test: Empty name (doesn't start with '[') with no qualifiers and no special options
TEST_F(CanBeRDFAttrPropTest_2108, EmptyNameReturnsTrue_2108) {
    // Empty string - name[0] would be '\0', not '[', so first check passes
    // However accessing [0] on empty string is undefined. Let's use a non-empty name.
    XMP_Node node(nullptr, "a", 0);
    EXPECT_TRUE(CanBeRDFAttrProp(&node));
}

// Test: A node with kXMP_PropHasQualifiers option but empty qualifiers list
// kXMP_PropHasQualifiers is not checked directly; only the qualifiers vector matters
TEST_F(CanBeRDFAttrPropTest_2108, HasQualifiersFlagButEmptyQualifiersReturnsTrue_2108) {
    XMP_Node node(nullptr, "prop", kXMP_PropHasQualifiers);
    EXPECT_TRUE(CanBeRDFAttrProp(&node));
}

// Test: A node with kXMP_PropIsQualifier option returns true (not in the checked masks)
TEST_F(CanBeRDFAttrPropTest_2108, PropIsQualifierReturnsTrue_2108) {
    XMP_Node node(nullptr, "prop", kXMP_PropIsQualifier);
    EXPECT_TRUE(CanBeRDFAttrProp(&node));
}

// Test: A node with kXMP_PropHasLang option returns true
TEST_F(CanBeRDFAttrPropTest_2108, PropHasLangReturnsTrue_2108) {
    XMP_Node node(nullptr, "prop", kXMP_PropHasLang);
    EXPECT_TRUE(CanBeRDFAttrProp(&node));
}

// Test: Name that starts with a character other than '[' and has value set
TEST_F(CanBeRDFAttrPropTest_2108, NodeWithValueReturnsTrue_2108) {
    XMP_Node node(nullptr, "prop", "someValue", 0);
    EXPECT_TRUE(CanBeRDFAttrProp(&node));
}

// Test: kXMP_PropArrayFormMask is a subset of kXMP_PropCompositeMask
// Any option in PropArrayFormMask should cause false
TEST_F(CanBeRDFAttrPropTest_2108, PropArrayFormMaskReturnsFalse_2108) {
    XMP_Node node(nullptr, "prop", kXMP_PropArrayFormMask);
    EXPECT_FALSE(CanBeRDFAttrProp(&node));
}
