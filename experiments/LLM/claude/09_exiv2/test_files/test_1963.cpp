// We need to include the implementation to access the static function
// First, include necessary XMP SDK headers

#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include XMP SDK headers
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"

// Since TransplantArrayItemAlias is static, we need to include the cpp file
// or use a workaround. We'll include the source directly.
#include "XMPMeta-Parse.cpp"

class TransplantArrayItemAliasTest_1963 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up is handled by XMP_Node destructors
    }
};

// Test: Basic transplant without AltText - child moves from old to new parent
TEST_F(TransplantArrayItemAliasTest_1963, BasicTransplantToEmptyNewParent_1963) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", 0);
    
    XMP_Node* child = new XMP_Node(&oldParent, "childName", "childValue", 0);
    oldParent.children.push_back(child);
    
    TransplantArrayItemAlias(&oldParent, 0, &newParent);
    
    EXPECT_TRUE(oldParent.children.empty());
    ASSERT_EQ(newParent.children.size(), 1u);
    EXPECT_EQ(newParent.children[0], child);
    EXPECT_EQ(child->name, kXMP_ArrayItemName);
    EXPECT_EQ(child->parent, &newParent);
    EXPECT_EQ(child->value, "childValue");
}

// Test: Transplant to non-empty newParent - child inserted at beginning
TEST_F(TransplantArrayItemAliasTest_1963, TransplantToNonEmptyNewParent_1963) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", 0);
    
    XMP_Node* existingChild = new XMP_Node(&newParent, kXMP_ArrayItemName, "existing", 0);
    newParent.children.push_back(existingChild);
    
    XMP_Node* child = new XMP_Node(&oldParent, "childName", "newChild", 0);
    oldParent.children.push_back(child);
    
    TransplantArrayItemAlias(&oldParent, 0, &newParent);
    
    EXPECT_TRUE(oldParent.children.empty());
    ASSERT_EQ(newParent.children.size(), 2u);
    EXPECT_EQ(newParent.children[0], child);
    EXPECT_EQ(newParent.children[1], existingChild);
    EXPECT_EQ(child->name, kXMP_ArrayItemName);
    EXPECT_EQ(child->parent, &newParent);
}

// Test: Transplant with AltText flag on newParent - adds language qualifier
TEST_F(TransplantArrayItemAliasTest_1963, TransplantWithAltTextAddsLangQualifier_1963) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", kXMP_PropArrayIsAltText);
    
    XMP_Node* child = new XMP_Node(&oldParent, "childName", "childValue", 0);
    oldParent.children.push_back(child);
    
    TransplantArrayItemAlias(&oldParent, 0, &newParent);
    
    EXPECT_TRUE(oldParent.children.empty());
    ASSERT_EQ(newParent.children.size(), 1u);
    EXPECT_EQ(newParent.children[0], child);
    
    // Check that language qualifier was added
    EXPECT_TRUE(child->options & kXMP_PropHasQualifiers);
    EXPECT_TRUE(child->options & kXMP_PropHasLang);
    ASSERT_EQ(child->qualifiers.size(), 1u);
    EXPECT_EQ(child->qualifiers[0]->name, "xml:lang");
    EXPECT_EQ(child->qualifiers[0]->value, "x-default");
    EXPECT_TRUE(child->qualifiers[0]->options & kXMP_PropIsQualifier);
}

// Test: Transplant with AltText and child already has kXMP_PropHasLang - should throw
TEST_F(TransplantArrayItemAliasTest_1963, TransplantWithAltTextAndExistingLangThrows_1963) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", kXMP_PropArrayIsAltText);
    
    XMP_Node* child = new XMP_Node(&oldParent, "childName", "childValue", kXMP_PropHasLang);
    oldParent.children.push_back(child);
    
    EXPECT_THROW(TransplantArrayItemAlias(&oldParent, 0, &newParent), XMP_Error);
}

// Test: Transplant with AltText, child has existing qualifiers but no lang
TEST_F(TransplantArrayItemAliasTest_1963, TransplantWithAltTextExistingQualifiersNoLang_1963) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", kXMP_PropArrayIsAltText);
    
    XMP_Node* child = new XMP_Node(&oldParent, "childName", "childValue", 0);
    XMP_Node* existingQual = new XMP_Node(child, "someQual", "qualValue", kXMP_PropIsQualifier);
    child->qualifiers.push_back(existingQual);
    oldParent.children.push_back(child);
    
    TransplantArrayItemAlias(&oldParent, 0, &newParent);
    
    // Language qualifier should be inserted at the beginning
    ASSERT_EQ(child->qualifiers.size(), 2u);
    EXPECT_EQ(child->qualifiers[0]->name, "xml:lang");
    EXPECT_EQ(child->qualifiers[0]->value, "x-default");
    EXPECT_EQ(child->qualifiers[1], existingQual);
    EXPECT_TRUE(child->options & kXMP_PropHasQualifiers);
    EXPECT_TRUE(child->options & kXMP_PropHasLang);
}

// Test: Transplant from middle of oldParent's children
TEST_F(TransplantArrayItemAliasTest_1963, TransplantFromMiddleIndex_1963) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", 0);
    
    XMP_Node* child0 = new XMP_Node(&oldParent, "child0", "val0", 0);
    XMP_Node* child1 = new XMP_Node(&oldParent, "child1", "val1", 0);
    XMP_Node* child2 = new XMP_Node(&oldParent, "child2", "val2", 0);
    oldParent.children.push_back(child0);
    oldParent.children.push_back(child1);
    oldParent.children.push_back(child2);
    
    TransplantArrayItemAlias(&oldParent, 1, &newParent);
    
    ASSERT_EQ(oldParent.children.size(), 2u);
    EXPECT_EQ(oldParent.children[0], child0);
    EXPECT_EQ(oldParent.children[1], child2);
    
    ASSERT_EQ(newParent.children.size(), 1u);
    EXPECT_EQ(newParent.children[0], child1);
    EXPECT_EQ(child1->name, kXMP_ArrayItemName);
    EXPECT_EQ(child1->parent, &newParent);
}

// Test: Transplant last element from oldParent
TEST_F(TransplantArrayItemAliasTest_1963, TransplantLastElement_1963) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", 0);
    
    XMP_Node* child0 = new XMP_Node(&oldParent, "child0", "val0", 0);
    XMP_Node* child1 = new XMP_Node(&oldParent, "child1", "val1", 0);
    oldParent.children.push_back(child0);
    oldParent.children.push_back(child1);
    
    TransplantArrayItemAlias(&oldParent, 1, &newParent);
    
    ASSERT_EQ(oldParent.children.size(), 1u);
    EXPECT_EQ(oldParent.children[0], child0);
    
    ASSERT_EQ(newParent.children.size(), 1u);
    EXPECT_EQ(newParent.children[0], child1);
    EXPECT_EQ(child1->parent, &newParent);
}

// Test: Transplant with AltText and empty qualifiers on child
TEST_F(TransplantArrayItemAliasTest_1963, TransplantWithAltTextEmptyQualifiers_1963) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", kXMP_PropArrayIsAltText);
    
    XMP_Node* child = new XMP_Node(&oldParent, "childName", "childValue", 0);
    ASSERT_TRUE(child->qualifiers.empty());
    oldParent.children.push_back(child);
    
    TransplantArrayItemAlias(&oldParent, 0, &newParent);
    
    // Language qualifier should be pushed back (not inserted)
    ASSERT_EQ(child->qualifiers.size(), 1u);
    EXPECT_EQ(child->qualifiers[0]->name, "xml:lang");
    EXPECT_EQ(child->qualifiers[0]->value, "x-default");
}

// Test: Transplant without AltText flag - no language qualifier added
TEST_F(TransplantArrayItemAliasTest_1963, TransplantWithoutAltTextNoQualifierAdded_1963) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", kXMP_PropArrayIsOrdered); // Not AltText
    
    XMP_Node* child = new XMP_Node(&oldParent, "childName", "childValue", 0);
    oldParent.children.push_back(child);
    
    TransplantArrayItemAlias(&oldParent, 0, &newParent);
    
    EXPECT_TRUE(child->qualifiers.empty());
    EXPECT_FALSE(child->options & kXMP_PropHasLang);
}

// Test: Child options are preserved after transplant (non-AltText case)
TEST_F(TransplantArrayItemAliasTest_1963, ChildOptionsPreservedNonAltText_1963) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", 0);
    
    XMP_OptionBits originalOptions = kXMP_PropValueIsURI;
    XMP_Node* child = new XMP_Node(&oldParent, "childName", "childValue", originalOptions);
    oldParent.children.push_back(child);
    
    TransplantArrayItemAlias(&oldParent, 0, &newParent);
    
    EXPECT_EQ(child->options, originalOptions);
}

// Test: Child options get OR'd with lang flags in AltText case
TEST_F(TransplantArrayItemAliasTest_1963, ChildOptionsUpdatedForAltText_1963) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", kXMP_PropArrayIsAltText);
    
    XMP_OptionBits originalOptions = kXMP_PropValueIsURI;
    XMP_Node* child = new XMP_Node(&oldParent, "childName", "childValue", originalOptions);
    oldParent.children.push_back(child);
    
    TransplantArrayItemAlias(&oldParent, 0, &newParent);
    
    EXPECT_TRUE(child->options & kXMP_PropValueIsURI);
    EXPECT_TRUE(child->options & kXMP_PropHasQualifiers);
    EXPECT_TRUE(child->options & kXMP_PropHasLang);
}

// Test: Child value is preserved after transplant
TEST_F(TransplantArrayItemAliasTest_1963, ChildValuePreserved_1963) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", 0);
    
    XMP_Node* child = new XMP_Node(&oldParent, "childName", "important_value", 0);
    oldParent.children.push_back(child);
    
    TransplantArrayItemAlias(&oldParent, 0, &newParent);
    
    EXPECT_EQ(child->value, "important_value");
}

// Test: Transplant first element when oldParent has multiple children
TEST_F(TransplantArrayItemAliasTest_1963, TransplantFirstOfMultiple_1963) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", 0);
    
    XMP_Node* child0 = new XMP_Node(&oldParent, "child0", "val0", 0);
    XMP_Node* child1 = new XMP_Node(&oldParent, "child1", "val1", 0);
    XMP_Node* child2 = new XMP_Node(&oldParent, "child2", "val2", 0);
    oldParent.children.push_back(child0);
    oldParent.children.push_back(child1);
    oldParent.children.push_back(child2);
    
    TransplantArrayItemAlias(&oldParent, 0, &newParent);
    
    ASSERT_EQ(oldParent.children.size(), 2u);
    EXPECT_EQ(oldParent.children[0], child1);
    EXPECT_EQ(oldParent.children[1], child2);
    
    ASSERT_EQ(newParent.children.size(), 1u);
    EXPECT_EQ(newParent.children[0], child0);
}

// Test: Language qualifier parent is set to child
TEST_F(TransplantArrayItemAliasTest_1963, LangQualifierParentIsChild_1963) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", kXMP_PropArrayIsAltText);
    
    XMP_Node* child = new XMP_Node(&oldParent, "childName", "childValue", 0);
    oldParent.children.push_back(child);
    
    TransplantArrayItemAlias(&oldParent, 0, &newParent);
    
    ASSERT_EQ(child->qualifiers.size(), 1u);
    EXPECT_EQ(child->qualifiers[0]->parent, child);
}
