#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <stdexcept>

// Include necessary headers
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"

// We need access to the static function. Since it's static in a .cpp file,
// we include the .cpp to get access for testing purposes.
#include "XMPCore_Impl.cpp"

class FollowXPathStepTest_1888 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create an XPathStepInfo with specific step kind
    XPathStepInfo makeStep(const std::string& stepStr, XMP_OptionBits kind) {
        return XPathStepInfo(stepStr.c_str(), kind);
    }
};

// Test: StructFieldStep finds existing child node
TEST_F(FollowXPathStepTest_1888, StructFieldStep_FindsExistingChild_1888) {
    XMP_Node parent(nullptr, "parent", 0);
    XMP_Node* child = new XMP_Node(&parent, "ns:field", 0);
    parent.children.push_back(child);

    XMP_ExpandedXPath fullPath;
    fullPath.push_back(XPathStepInfo("schema", 0)); // step 0 - schema
    fullPath.push_back(XPathStepInfo("ns:field", kXMP_StructFieldStep)); // step 1

    XMP_NodePtrPos ptrPos;
    XMP_Node* result = FollowXPathStep(&parent, fullPath, 1, false, &ptrPos);

    EXPECT_EQ(result, child);
}

// Test: StructFieldStep returns null for non-existing child when createNodes is false
TEST_F(FollowXPathStepTest_1888, StructFieldStep_ReturnsNullForMissingChild_1888) {
    XMP_Node parent(nullptr, "parent", 0);

    XMP_ExpandedXPath fullPath;
    fullPath.push_back(XPathStepInfo("schema", 0));
    fullPath.push_back(XPathStepInfo("ns:nonexistent", kXMP_StructFieldStep));

    XMP_Node* result = FollowXPathStep(&parent, fullPath, 1, false, nullptr);

    EXPECT_EQ(result, nullptr);
}

// Test: StructFieldStep creates node when createNodes is true
TEST_F(FollowXPathStepTest_1888, StructFieldStep_CreatesNodeWhenRequested_1888) {
    XMP_Node parent(nullptr, "parent", 0);

    XMP_ExpandedXPath fullPath;
    fullPath.push_back(XPathStepInfo("schema", 0));
    fullPath.push_back(XPathStepInfo("ns:newfield", kXMP_StructFieldStep));

    XMP_Node* result = FollowXPathStep(&parent, fullPath, 1, true, nullptr);

    EXPECT_NE(result, nullptr);
    if (result) {
        EXPECT_EQ(result->name, "ns:newfield");
    }
    // Cleanup
    parent.RemoveChildren();
}

// Test: QualifierStep finds existing qualifier
TEST_F(FollowXPathStepTest_1888, QualifierStep_FindsExistingQualifier_1888) {
    XMP_Node parent(nullptr, "parent", kXMP_PropHasQualifiers);
    XMP_Node* qual = new XMP_Node(&parent, "ns:qual", kXMP_PropIsQualifier);
    parent.qualifiers.push_back(qual);

    XMP_ExpandedXPath fullPath;
    fullPath.push_back(XPathStepInfo("schema", 0));
    fullPath.push_back(XPathStepInfo("?ns:qual", kXMP_QualifierStep));

    XMP_Node* result = FollowXPathStep(&parent, fullPath, 1, false, nullptr);

    EXPECT_EQ(result, qual);
}

// Test: ArrayIndexStep throws when parent is not an array
TEST_F(FollowXPathStepTest_1888, ArrayIndexStep_ThrowsOnNonArray_1888) {
    XMP_Node parent(nullptr, "parent", 0); // Not an array

    XMP_ExpandedXPath fullPath;
    fullPath.push_back(XPathStepInfo("schema", 0));
    fullPath.push_back(XPathStepInfo("[1]", kXMP_ArrayIndexStep));

    EXPECT_THROW(
        FollowXPathStep(&parent, fullPath, 1, false, nullptr),
        XMP_Error
    );
}

// Test: ArrayIndexStep finds item in array
TEST_F(FollowXPathStepTest_1888, ArrayIndexStep_FindsItemInArray_1888) {
    XMP_Node parent(nullptr, "parent", kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered);
    XMP_Node* item = new XMP_Node(&parent, kXMP_ArrayItemName, 0);
    parent.children.push_back(item);

    XMP_ExpandedXPath fullPath;
    fullPath.push_back(XPathStepInfo("schema", 0));
    fullPath.push_back(XPathStepInfo("[1]", kXMP_ArrayIndexStep));

    XMP_NodePtrPos ptrPos;
    XMP_Node* result = FollowXPathStep(&parent, fullPath, 1, false, &ptrPos);

    EXPECT_EQ(result, item);
    // Cleanup
    parent.RemoveChildren();
}

// Test: ArrayLastStep finds last item in array
TEST_F(FollowXPathStepTest_1888, ArrayLastStep_FindsLastItem_1888) {
    XMP_Node parent(nullptr, "parent", kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered);
    XMP_Node* item1 = new XMP_Node(&parent, kXMP_ArrayItemName, 0);
    XMP_Node* item2 = new XMP_Node(&parent, kXMP_ArrayItemName, 0);
    XMP_Node* item3 = new XMP_Node(&parent, kXMP_ArrayItemName, 0);
    parent.children.push_back(item1);
    parent.children.push_back(item2);
    parent.children.push_back(item3);

    XMP_ExpandedXPath fullPath;
    fullPath.push_back(XPathStepInfo("schema", 0));
    fullPath.push_back(XPathStepInfo("[last()]", kXMP_ArrayLastStep));

    XMP_NodePtrPos ptrPos;
    XMP_Node* result = FollowXPathStep(&parent, fullPath, 1, false, &ptrPos);

    EXPECT_EQ(result, item3);
    // Cleanup
    parent.RemoveChildren();
}

// Test: ArrayLastStep on single element array
TEST_F(FollowXPathStepTest_1888, ArrayLastStep_SingleElement_1888) {
    XMP_Node parent(nullptr, "parent", kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered);
    XMP_Node* item1 = new XMP_Node(&parent, kXMP_ArrayItemName, 0);
    parent.children.push_back(item1);

    XMP_ExpandedXPath fullPath;
    fullPath.push_back(XPathStepInfo("schema", 0));
    fullPath.push_back(XPathStepInfo("[last()]", kXMP_ArrayLastStep));

    XMP_Node* result = FollowXPathStep(&parent, fullPath, 1, false, nullptr);

    EXPECT_EQ(result, item1);
    parent.RemoveChildren();
}

// Test: Implicit node gets array form mask from step options
TEST_F(FollowXPathStepTest_1888, ImplicitNode_GetsArrayFormMask_1888) {
    XMP_Node parent(nullptr, "parent", 0);

    XMP_ExpandedXPath fullPath;
    fullPath.push_back(XPathStepInfo("schema", 0));
    fullPath.push_back(XPathStepInfo("ns:newfield", kXMP_StructFieldStep | kXMP_PropArrayIsOrdered));

    XMP_Node* result = FollowXPathStep(&parent, fullPath, 1, true, nullptr);

    EXPECT_NE(result, nullptr);
    if (result) {
        // The node should have kXMP_NewImplicitNode set, and the array form mask applied
        EXPECT_TRUE(result->options & kXMP_PropArrayIsOrdered);
    }
    parent.RemoveChildren();
}

// Test: FieldSelectorStep on array with matching field
TEST_F(FollowXPathStepTest_1888, FieldSelectorStep_FindsMatchingItem_1888) {
    XMP_Node parent(nullptr, "parent", kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered);
    
    // Create an array item that is a struct with a field
    XMP_Node* item1 = new XMP_Node(&parent, kXMP_ArrayItemName, kXMP_PropValueIsStruct);
    XMP_Node* field1 = new XMP_Node(item1, "ns:fieldName", "fieldValue", 0);
    item1->children.push_back(field1);
    parent.children.push_back(item1);

    XMP_ExpandedXPath fullPath;
    fullPath.push_back(XPathStepInfo("schema", 0));
    fullPath.push_back(XPathStepInfo("[ns:fieldName=\"fieldValue\"]", kXMP_FieldSelectorStep));

    XMP_Node* result = FollowXPathStep(&parent, fullPath, 1, false, nullptr);

    EXPECT_EQ(result, item1);
    parent.RemoveChildren();
}

// Test: QualSelectorStep on alt-text array with x-default
TEST_F(FollowXPathStepTest_1888, QualSelectorStep_CreatesXDefaultWhenMissing_1888) {
    XMP_Node parent(nullptr, "parent", 
        kXMP_PropValueIsArray | kXMP_PropArrayIsAltText | kXMP_PropArrayIsAlternate | kXMP_PropArrayIsOrdered);

    // We need step at index 2 with specific content for the aliased path
    XMP_ExpandedXPath fullPath;
    fullPath.push_back(XPathStepInfo("schema", 0));
    fullPath.push_back(XPathStepInfo("ns:prop", kXMP_StructFieldStep));
    fullPath.push_back(XPathStepInfo("[?xml:lang=\"x-default\"]", kXMP_QualSelectorStep));

    // The function should create a new x-default node when createNodes=true and aliasedArrayItem=true
    XMP_Node* result = FollowXPathStep(&parent, fullPath, 2, true, nullptr, true);

    EXPECT_NE(result, nullptr);
    if (result) {
        EXPECT_FALSE(parent.children.empty());
        EXPECT_EQ(parent.children[0], result);
        EXPECT_FALSE(result->qualifiers.empty());
        if (!result->qualifiers.empty()) {
            EXPECT_EQ(result->qualifiers[0]->name, "xml:lang");
            EXPECT_EQ(result->qualifiers[0]->value, "x-default");
        }
    }
    parent.RemoveChildren();
}

// Test: QualSelectorStep creates x-default and inserts at front when children exist
TEST_F(FollowXPathStepTest_1888, QualSelectorStep_InsertsXDefaultAtFront_1888) {
    XMP_Node parent(nullptr, "parent",
        kXMP_PropValueIsArray | kXMP_PropArrayIsAltText | kXMP_PropArrayIsAlternate | kXMP_PropArrayIsOrdered);

    // Add an existing child
    XMP_Node* existingChild = new XMP_Node(&parent, kXMP_ArrayItemName, kXMP_PropHasQualifiers | kXMP_PropHasLang);
    XMP_Node* langQual = new XMP_Node(existingChild, "xml:lang", "en-US", kXMP_PropIsQualifier);
    existingChild->qualifiers.push_back(langQual);
    parent.children.push_back(existingChild);

    XMP_ExpandedXPath fullPath;
    fullPath.push_back(XPathStepInfo("schema", 0));
    fullPath.push_back(XPathStepInfo("ns:prop", kXMP_StructFieldStep));
    fullPath.push_back(XPathStepInfo("[?xml:lang=\"x-default\"]", kXMP_QualSelectorStep));

    XMP_Node* result = FollowXPathStep(&parent, fullPath, 2, true, nullptr, true);

    EXPECT_NE(result, nullptr);
    if (result) {
        EXPECT_EQ(parent.children.size(), 2u);
        EXPECT_EQ(parent.children[0], result); // x-default should be first
        EXPECT_EQ(parent.children[1], existingChild);
    }
    parent.RemoveChildren();
}

// Test: ArrayIndexStep with out-of-range index returns null
TEST_F(FollowXPathStepTest_1888, ArrayIndexStep_OutOfRange_ReturnsNull_1888) {
    XMP_Node parent(nullptr, "parent", kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered);
    XMP_Node* item = new XMP_Node(&parent, kXMP_ArrayItemName, 0);
    parent.children.push_back(item);

    XMP_ExpandedXPath fullPath;
    fullPath.push_back(XPathStepInfo("schema", 0));
    fullPath.push_back(XPathStepInfo("[5]", kXMP_ArrayIndexStep));

    XMP_Node* result = FollowXPathStep(&parent, fullPath, 1, false, nullptr);

    // Index 5 is out of range for a 1-element array, should return null
    EXPECT_EQ(result, nullptr);
    parent.RemoveChildren();
}

// Test: Null ptrPos parameter is handled correctly
TEST_F(FollowXPathStepTest_1888, StructFieldStep_NullPtrPos_1888) {
    XMP_Node parent(nullptr, "parent", 0);
    XMP_Node* child = new XMP_Node(&parent, "ns:field", 0);
    parent.children.push_back(child);

    XMP_ExpandedXPath fullPath;
    fullPath.push_back(XPathStepInfo("schema", 0));
    fullPath.push_back(XPathStepInfo("ns:field", kXMP_StructFieldStep));

    // Should not crash with nullptr for ptrPos
    XMP_Node* result = FollowXPathStep(&parent, fullPath, 1, false, nullptr);

    EXPECT_EQ(result, child);
    parent.RemoveChildren();
}

// Test: ArrayLastStep throws on non-array
TEST_F(FollowXPathStepTest_1888, ArrayLastStep_ThrowsOnNonArray_1888) {
    XMP_Node parent(nullptr, "parent", 0); // Not array

    XMP_ExpandedXPath fullPath;
    fullPath.push_back(XPathStepInfo("schema", 0));
    fullPath.push_back(XPathStepInfo("[last()]", kXMP_ArrayLastStep));

    EXPECT_THROW(
        FollowXPathStep(&parent, fullPath, 1, false, nullptr),
        XMP_Error
    );
}

// Test: FieldSelectorStep throws on non-array
TEST_F(FollowXPathStepTest_1888, FieldSelectorStep_ThrowsOnNonArray_1888) {
    XMP_Node parent(nullptr, "parent", 0); // Not array

    XMP_ExpandedXPath fullPath;
    fullPath.push_back(XPathStepInfo("schema", 0));
    fullPath.push_back(XPathStepInfo("[ns:field=\"value\"]", kXMP_FieldSelectorStep));

    EXPECT_THROW(
        FollowXPathStep(&parent, fullPath, 1, false, nullptr),
        XMP_Error
    );
}

// Test: QualSelectorStep throws on non-array
TEST_F(FollowXPathStepTest_1888, QualSelectorStep_ThrowsOnNonArray_1888) {
    XMP_Node parent(nullptr, "parent", 0); // Not array

    XMP_ExpandedXPath fullPath;
    fullPath.push_back(XPathStepInfo("schema", 0));
    fullPath.push_back(XPathStepInfo("[?xml:lang=\"en\"]", kXMP_QualSelectorStep));

    EXPECT_THROW(
        FollowXPathStep(&parent, fullPath, 1, false, nullptr),
        XMP_Error
    );
}
