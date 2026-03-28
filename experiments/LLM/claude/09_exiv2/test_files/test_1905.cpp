#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include necessary headers
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// Forward declaration of the function under test
void DetectAltText(XMP_Node* xmpParent);
void NormalizeLangArray(XMP_Node* xmpParent);

// We need to understand the macros used
#ifndef XMP_ArrayIsAlternate
#define XMP_ArrayIsAlternate(options) (((options) & kXMP_PropArrayIsAlternate) != 0)
#endif

class DetectAltTextTest_1905 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any nodes we created
        for (auto* node : nodesToCleanup) {
            // Don't call RemoveChildren as it may try to delete children we manage
            delete node;
        }
        nodesToCleanup.clear();
    }

    // Helper to create a child node with given options
    XMP_Node* CreateChildNode(XMP_Node* parent, const char* name, XMP_OptionBits options) {
        XMP_Node* child = new XMP_Node(parent, name, options);
        nodesToCleanup.push_back(child);
        return child;
    }

    // Helper to create a parent node that is an alternate array
    XMP_Node* CreateAltArrayParent() {
        XMP_Node* parent = new XMP_Node(nullptr, "parent",
            kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered | kXMP_PropArrayIsAlternate);
        nodesToCleanup.push_back(parent);
        return parent;
    }

    std::vector<XMP_Node*> nodesToCleanup;
};

// Test: Empty children list - should NOT set kXMP_PropArrayIsAltText
// because itemLim == 0
TEST_F(DetectAltTextTest_1905, EmptyChildren_DoesNotSetAltText_1905) {
    XMP_Node* parent = CreateAltArrayParent();
    
    XMP_OptionBits optionsBefore = parent->options;
    DetectAltText(parent);
    
    // With no children, itemLim == 0, so the condition (itemLim != 0 && itemNum == itemLim) is false
    EXPECT_FALSE(parent->options & kXMP_PropArrayIsAltText);
}

// Test: Single child with kXMP_PropHasLang and no composite mask
// Should set kXMP_PropArrayIsAltText
TEST_F(DetectAltTextTest_1905, SingleChildWithLang_SetsAltText_1905) {
    XMP_Node* parent = CreateAltArrayParent();
    
    XMP_Node* child = CreateChildNode(parent, "item", kXMP_PropHasLang);
    parent->children.push_back(child);
    
    // Add a qualifier for the lang (NormalizeLangArray may expect this)
    XMP_Node* langQual = new XMP_Node(child, "xml:lang", "x-default", kXMP_PropIsQualifier);
    nodesToCleanup.push_back(langQual);
    child->qualifiers.push_back(langQual);
    
    DetectAltText(parent);
    
    EXPECT_TRUE((parent->options & kXMP_PropArrayIsAltText) != 0);
}

// Test: Multiple children all with kXMP_PropHasLang and no composite flags
// Should set kXMP_PropArrayIsAltText
TEST_F(DetectAltTextTest_1905, MultipleChildrenAllWithLang_SetsAltText_1905) {
    XMP_Node* parent = CreateAltArrayParent();
    
    for (int i = 0; i < 3; ++i) {
        std::string name = "item" + std::to_string(i);
        XMP_Node* child = CreateChildNode(parent, name.c_str(), kXMP_PropHasLang);
        
        std::string langVal = (i == 0) ? "x-default" : ("en-" + std::to_string(i));
        XMP_Node* langQual = new XMP_Node(child, "xml:lang", langVal.c_str(), kXMP_PropIsQualifier);
        nodesToCleanup.push_back(langQual);
        child->qualifiers.push_back(langQual);
        
        parent->children.push_back(child);
    }
    
    DetectAltText(parent);
    
    EXPECT_TRUE((parent->options & kXMP_PropArrayIsAltText) != 0);
}

// Test: Child with composite mask bit set - should NOT set kXMP_PropArrayIsAltText
// kXMP_PropValueIsStruct is part of kXMP_PropCompositeMask
TEST_F(DetectAltTextTest_1905, ChildWithCompositeMask_DoesNotSetAltText_1905) {
    XMP_Node* parent = CreateAltArrayParent();
    
    XMP_Node* child = CreateChildNode(parent, "item",
        kXMP_PropHasLang | kXMP_PropValueIsStruct);
    parent->children.push_back(child);
    
    DetectAltText(parent);
    
    EXPECT_FALSE(parent->options & kXMP_PropArrayIsAltText);
}

// Test: Child without kXMP_PropHasLang - should NOT set kXMP_PropArrayIsAltText
TEST_F(DetectAltTextTest_1905, ChildWithoutLang_DoesNotSetAltText_1905) {
    XMP_Node* parent = CreateAltArrayParent();
    
    XMP_Node* child = CreateChildNode(parent, "item", 0);  // No lang flag
    parent->children.push_back(child);
    
    DetectAltText(parent);
    
    EXPECT_FALSE(parent->options & kXMP_PropArrayIsAltText);
}

// Test: First child has lang, second child does not - should NOT set AltText
TEST_F(DetectAltTextTest_1905, MixedChildren_SecondWithoutLang_DoesNotSetAltText_1905) {
    XMP_Node* parent = CreateAltArrayParent();
    
    XMP_Node* child1 = CreateChildNode(parent, "item1", kXMP_PropHasLang);
    XMP_Node* langQual1 = new XMP_Node(child1, "xml:lang", "x-default", kXMP_PropIsQualifier);
    nodesToCleanup.push_back(langQual1);
    child1->qualifiers.push_back(langQual1);
    parent->children.push_back(child1);
    
    XMP_Node* child2 = CreateChildNode(parent, "item2", 0);  // No lang
    parent->children.push_back(child2);
    
    DetectAltText(parent);
    
    EXPECT_FALSE(parent->options & kXMP_PropArrayIsAltText);
}

// Test: First child without lang, second with lang - should NOT set AltText
// because the loop breaks on the first child
TEST_F(DetectAltTextTest_1905, FirstChildWithoutLang_DoesNotSetAltText_1905) {
    XMP_Node* parent = CreateAltArrayParent();
    
    XMP_Node* child1 = CreateChildNode(parent, "item1", 0);  // No lang
    parent->children.push_back(child1);
    
    XMP_Node* child2 = CreateChildNode(parent, "item2", kXMP_PropHasLang);
    XMP_Node* langQual2 = new XMP_Node(child2, "xml:lang", "en", kXMP_PropIsQualifier);
    nodesToCleanup.push_back(langQual2);
    child2->qualifiers.push_back(langQual2);
    parent->children.push_back(child2);
    
    DetectAltText(parent);
    
    EXPECT_FALSE(parent->options & kXMP_PropArrayIsAltText);
}

// Test: Child with kXMP_PropValueIsArray (part of composite mask) breaks the loop
TEST_F(DetectAltTextTest_1905, ChildWithArrayOption_DoesNotSetAltText_1905) {
    XMP_Node* parent = CreateAltArrayParent();
    
    XMP_Node* child = CreateChildNode(parent, "item",
        kXMP_PropHasLang | kXMP_PropValueIsArray);
    parent->children.push_back(child);
    
    DetectAltText(parent);
    
    EXPECT_FALSE(parent->options & kXMP_PropArrayIsAltText);
}

// Test: Verify that kXMP_PropArrayIsAltText was not already set and gets added
TEST_F(DetectAltTextTest_1905, AltTextFlagAddedToExistingOptions_1905) {
    XMP_Node* parent = CreateAltArrayParent();
    XMP_OptionBits originalOptions = parent->options;
    
    XMP_Node* child = CreateChildNode(parent, "item", kXMP_PropHasLang);
    XMP_Node* langQual = new XMP_Node(child, "xml:lang", "x-default", kXMP_PropIsQualifier);
    nodesToCleanup.push_back(langQual);
    child->qualifiers.push_back(langQual);
    parent->children.push_back(child);
    
    DetectAltText(parent);
    
    // Original options should still be present
    EXPECT_TRUE((parent->options & originalOptions) == originalOptions);
    // And kXMP_PropArrayIsAltText should now also be set
    EXPECT_TRUE((parent->options & kXMP_PropArrayIsAltText) != 0);
}

// Test: Child with only kXMP_PropHasLang and kXMP_PropHasQualifiers (not composite)
// kXMP_PropHasQualifiers (16) is NOT in kXMP_PropCompositeMask (7936), so should pass
TEST_F(DetectAltTextTest_1905, ChildWithQualifiersAndLang_SetsAltText_1905) {
    XMP_Node* parent = CreateAltArrayParent();
    
    XMP_Node* child = CreateChildNode(parent, "item",
        kXMP_PropHasLang | kXMP_PropHasQualifiers);
    XMP_Node* langQual = new XMP_Node(child, "xml:lang", "x-default", kXMP_PropIsQualifier);
    nodesToCleanup.push_back(langQual);
    child->qualifiers.push_back(langQual);
    parent->children.push_back(child);
    
    DetectAltText(parent);
    
    EXPECT_TRUE((parent->options & kXMP_PropArrayIsAltText) != 0);
}

// Test: Large number of children all with lang - should still set AltText
TEST_F(DetectAltTextTest_1905, ManyChildrenAllWithLang_SetsAltText_1905) {
    XMP_Node* parent = CreateAltArrayParent();
    
    for (int i = 0; i < 100; ++i) {
        std::string name = "item" + std::to_string(i);
        XMP_Node* child = CreateChildNode(parent, name.c_str(), kXMP_PropHasLang);
        
        std::string langVal = (i == 0) ? "x-default" : ("lang-" + std::to_string(i));
        XMP_Node* langQual = new XMP_Node(child, "xml:lang", langVal.c_str(), kXMP_PropIsQualifier);
        nodesToCleanup.push_back(langQual);
        child->qualifiers.push_back(langQual);
        
        parent->children.push_back(child);
    }
    
    DetectAltText(parent);
    
    EXPECT_TRUE((parent->options & kXMP_PropArrayIsAltText) != 0);
}

// Test: Last child in a list breaks the loop - should NOT set AltText
TEST_F(DetectAltTextTest_1905, LastChildBreaksLoop_DoesNotSetAltText_1905) {
    XMP_Node* parent = CreateAltArrayParent();
    
    // First two children are fine
    for (int i = 0; i < 2; ++i) {
        std::string name = "item" + std::to_string(i);
        XMP_Node* child = CreateChildNode(parent, name.c_str(), kXMP_PropHasLang);
        
        std::string langVal = (i == 0) ? "x-default" : "en";
        XMP_Node* langQual = new XMP_Node(child, "xml:lang", langVal.c_str(), kXMP_PropIsQualifier);
        nodesToCleanup.push_back(langQual);
        child->qualifiers.push_back(langQual);
        
        parent->children.push_back(child);
    }
    
    // Third child has no lang
    XMP_Node* badChild = CreateChildNode(parent, "item2", 0);
    parent->children.push_back(badChild);
    
    DetectAltText(parent);
    
    EXPECT_FALSE(parent->options & kXMP_PropArrayIsAltText);
}
