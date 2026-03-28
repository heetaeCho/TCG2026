#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary headers
#include "XMPCore_Impl.hpp"

// We need the declaration of LookupFieldSelector
extern XMP_Index LookupFieldSelector(const XMP_Node* arrayNode, XMP_StringPtr fieldName, XMP_StringPtr fieldValue);

class LookupFieldSelectorTest_1897 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up nodes - we need to manually manage since XMP_Node has children vectors
        for (auto* node : allocated_nodes_) {
            node->children.clear();
            node->qualifiers.clear();
        }
        for (auto* node : allocated_nodes_) {
            delete node;
        }
        allocated_nodes_.clear();
    }

    XMP_Node* CreateNode(XMP_Node* parent, const char* name, const char* value, XMP_OptionBits options) {
        XMP_Node* node = new XMP_Node(parent, name, value, options);
        allocated_nodes_.push_back(node);
        return node;
    }

    XMP_Node* CreateNode(XMP_Node* parent, const char* name, XMP_OptionBits options) {
        XMP_Node* node = new XMP_Node(parent, name, options);
        allocated_nodes_.push_back(node);
        return node;
    }

    std::vector<XMP_Node*> allocated_nodes_;
};

// Test: Empty array returns -1
TEST_F(LookupFieldSelectorTest_1897, EmptyArrayReturnsMinusOne_1897) {
    XMP_Node* arrayNode = CreateNode(nullptr, "array", 0);
    XMP_Index result = LookupFieldSelector(arrayNode, "fieldName", "fieldValue");
    EXPECT_EQ(result, -1);
}

// Test: Single struct child with matching field returns index 0
TEST_F(LookupFieldSelectorTest_1897, SingleMatchingChildReturnsZero_1897) {
    XMP_Node* arrayNode = CreateNode(nullptr, "array", 0);

    XMP_Node* structChild = CreateNode(arrayNode, "item", kXMP_PropValueIsStruct);
    arrayNode->children.push_back(structChild);

    XMP_Node* field = CreateNode(structChild, "fieldName", "fieldValue", 0);
    structChild->children.push_back(field);

    XMP_Index result = LookupFieldSelector(arrayNode, "fieldName", "fieldValue");
    EXPECT_EQ(result, 0);
}

// Test: Single struct child with non-matching field name returns -1
TEST_F(LookupFieldSelectorTest_1897, NonMatchingFieldNameReturnsMinusOne_1897) {
    XMP_Node* arrayNode = CreateNode(nullptr, "array", 0);

    XMP_Node* structChild = CreateNode(arrayNode, "item", kXMP_PropValueIsStruct);
    arrayNode->children.push_back(structChild);

    XMP_Node* field = CreateNode(structChild, "otherField", "fieldValue", 0);
    structChild->children.push_back(field);

    XMP_Index result = LookupFieldSelector(arrayNode, "fieldName", "fieldValue");
    EXPECT_EQ(result, -1);
}

// Test: Single struct child with matching field name but non-matching value returns -1
TEST_F(LookupFieldSelectorTest_1897, MatchingNameButDifferentValueReturnsMinusOne_1897) {
    XMP_Node* arrayNode = CreateNode(nullptr, "array", 0);

    XMP_Node* structChild = CreateNode(arrayNode, "item", kXMP_PropValueIsStruct);
    arrayNode->children.push_back(structChild);

    XMP_Node* field = CreateNode(structChild, "fieldName", "wrongValue", 0);
    structChild->children.push_back(field);

    XMP_Index result = LookupFieldSelector(arrayNode, "fieldName", "wrongValue2");
    EXPECT_EQ(result, -1);
}

// Test: Non-struct child throws exception
TEST_F(LookupFieldSelectorTest_1897, NonStructChildThrowsException_1897) {
    XMP_Node* arrayNode = CreateNode(nullptr, "array", 0);

    // Child without kXMP_PropValueIsStruct
    XMP_Node* nonStructChild = CreateNode(arrayNode, "item", 0);
    arrayNode->children.push_back(nonStructChild);

    EXPECT_THROW(LookupFieldSelector(arrayNode, "fieldName", "fieldValue"), XMP_Error);
}

// Test: Multiple children, match is at second index
TEST_F(LookupFieldSelectorTest_1897, MatchAtSecondIndexReturnsOne_1897) {
    XMP_Node* arrayNode = CreateNode(nullptr, "array", 0);

    // First struct child - no matching field
    XMP_Node* structChild1 = CreateNode(arrayNode, "item1", kXMP_PropValueIsStruct);
    arrayNode->children.push_back(structChild1);
    XMP_Node* field1 = CreateNode(structChild1, "fieldName", "otherValue", 0);
    structChild1->children.push_back(field1);

    // Second struct child - matching field
    XMP_Node* structChild2 = CreateNode(arrayNode, "item2", kXMP_PropValueIsStruct);
    arrayNode->children.push_back(structChild2);
    XMP_Node* field2 = CreateNode(structChild2, "fieldName", "fieldValue", 0);
    structChild2->children.push_back(field2);

    XMP_Index result = LookupFieldSelector(arrayNode, "fieldName", "fieldValue");
    EXPECT_EQ(result, 1);
}

// Test: Multiple children, match is at first index (returns first match)
TEST_F(LookupFieldSelectorTest_1897, MultipleMatchesReturnsFirst_1897) {
    XMP_Node* arrayNode = CreateNode(nullptr, "array", 0);

    // First struct child - matching field
    XMP_Node* structChild1 = CreateNode(arrayNode, "item1", kXMP_PropValueIsStruct);
    arrayNode->children.push_back(structChild1);
    XMP_Node* field1 = CreateNode(structChild1, "fieldName", "fieldValue", 0);
    structChild1->children.push_back(field1);

    // Second struct child - also matching
    XMP_Node* structChild2 = CreateNode(arrayNode, "item2", kXMP_PropValueIsStruct);
    arrayNode->children.push_back(structChild2);
    XMP_Node* field2 = CreateNode(structChild2, "fieldName", "fieldValue", 0);
    structChild2->children.push_back(field2);

    XMP_Index result = LookupFieldSelector(arrayNode, "fieldName", "fieldValue");
    EXPECT_EQ(result, 0);
}

// Test: Struct child with multiple fields, matching field is not the first
TEST_F(LookupFieldSelectorTest_1897, MatchingFieldNotFirstInStruct_1897) {
    XMP_Node* arrayNode = CreateNode(nullptr, "array", 0);

    XMP_Node* structChild = CreateNode(arrayNode, "item", kXMP_PropValueIsStruct);
    arrayNode->children.push_back(structChild);

    XMP_Node* field1 = CreateNode(structChild, "otherField1", "someValue", 0);
    structChild->children.push_back(field1);
    XMP_Node* field2 = CreateNode(structChild, "otherField2", "someValue2", 0);
    structChild->children.push_back(field2);
    XMP_Node* field3 = CreateNode(structChild, "fieldName", "fieldValue", 0);
    structChild->children.push_back(field3);

    XMP_Index result = LookupFieldSelector(arrayNode, "fieldName", "fieldValue");
    EXPECT_EQ(result, 0);
}

// Test: Struct child with no children at all returns -1
TEST_F(LookupFieldSelectorTest_1897, StructChildWithNoFieldsReturnsMinusOne_1897) {
    XMP_Node* arrayNode = CreateNode(nullptr, "array", 0);

    XMP_Node* structChild = CreateNode(arrayNode, "item", kXMP_PropValueIsStruct);
    arrayNode->children.push_back(structChild);

    XMP_Index result = LookupFieldSelector(arrayNode, "fieldName", "fieldValue");
    EXPECT_EQ(result, -1);
}

// Test: Match at last index of a large array
TEST_F(LookupFieldSelectorTest_1897, MatchAtLastIndex_1897) {
    XMP_Node* arrayNode = CreateNode(nullptr, "array", 0);

    // Create 10 non-matching struct children
    for (int i = 0; i < 10; ++i) {
        std::string itemName = "item" + std::to_string(i);
        XMP_Node* structChild = CreateNode(arrayNode, itemName.c_str(), kXMP_PropValueIsStruct);
        arrayNode->children.push_back(structChild);

        XMP_Node* field = CreateNode(structChild, "fieldName", "nonMatchingValue", 0);
        structChild->children.push_back(field);
    }

    // Last one matches
    XMP_Node* structChildLast = CreateNode(arrayNode, "itemLast", kXMP_PropValueIsStruct);
    arrayNode->children.push_back(structChildLast);
    XMP_Node* fieldLast = CreateNode(structChildLast, "fieldName", "fieldValue", 0);
    structChildLast->children.push_back(fieldLast);

    XMP_Index result = LookupFieldSelector(arrayNode, "fieldName", "fieldValue");
    EXPECT_EQ(result, 10);
}

// Test: Non-struct child throws with correct error code
TEST_F(LookupFieldSelectorTest_1897, NonStructChildThrowsWithCorrectErrorCode_1897) {
    XMP_Node* arrayNode = CreateNode(nullptr, "array", 0);

    XMP_Node* nonStructChild = CreateNode(arrayNode, "item", 0);
    arrayNode->children.push_back(nonStructChild);

    try {
        LookupFieldSelector(arrayNode, "fieldName", "fieldValue");
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadXPath);
    }
}

// Test: Empty field name still searches correctly
TEST_F(LookupFieldSelectorTest_1897, EmptyFieldNameMatch_1897) {
    XMP_Node* arrayNode = CreateNode(nullptr, "array", 0);

    XMP_Node* structChild = CreateNode(arrayNode, "item", kXMP_PropValueIsStruct);
    arrayNode->children.push_back(structChild);

    XMP_Node* field = CreateNode(structChild, "", "fieldValue", 0);
    structChild->children.push_back(field);

    XMP_Index result = LookupFieldSelector(arrayNode, "", "fieldValue");
    EXPECT_EQ(result, 0);
}

// Test: Empty field value still matches
TEST_F(LookupFieldSelectorTest_1897, EmptyFieldValueMatch_1897) {
    XMP_Node* arrayNode = CreateNode(nullptr, "array", 0);

    XMP_Node* structChild = CreateNode(arrayNode, "item", kXMP_PropValueIsStruct);
    arrayNode->children.push_back(structChild);

    XMP_Node* field = CreateNode(structChild, "fieldName", "", 0);
    structChild->children.push_back(field);

    XMP_Index result = LookupFieldSelector(arrayNode, "fieldName", "");
    EXPECT_EQ(result, 0);
}

// Test: Field name matches but value differs across multiple fields in struct
TEST_F(LookupFieldSelectorTest_1897, SameFieldNameDifferentValuesNoMatch_1897) {
    XMP_Node* arrayNode = CreateNode(nullptr, "array", 0);

    XMP_Node* structChild = CreateNode(arrayNode, "item", kXMP_PropValueIsStruct);
    arrayNode->children.push_back(structChild);

    // Multiple fields with same name but wrong values
    XMP_Node* field1 = CreateNode(structChild, "fieldName", "value1", 0);
    structChild->children.push_back(field1);
    XMP_Node* field2 = CreateNode(structChild, "fieldName", "value2", 0);
    structChild->children.push_back(field2);

    XMP_Index result = LookupFieldSelector(arrayNode, "fieldName", "value3");
    EXPECT_EQ(result, -1);
}

// Test: First field with matching name has matching value (early exit in field loop)
TEST_F(LookupFieldSelectorTest_1897, FirstMatchingFieldHasCorrectValue_1897) {
    XMP_Node* arrayNode = CreateNode(nullptr, "array", 0);

    XMP_Node* structChild = CreateNode(arrayNode, "item", kXMP_PropValueIsStruct);
    arrayNode->children.push_back(structChild);

    // First field matches name and value
    XMP_Node* field1 = CreateNode(structChild, "fieldName", "fieldValue", 0);
    structChild->children.push_back(field1);
    // Second field with same name but different value
    XMP_Node* field2 = CreateNode(structChild, "fieldName", "otherValue", 0);
    structChild->children.push_back(field2);

    XMP_Index result = LookupFieldSelector(arrayNode, "fieldName", "fieldValue");
    EXPECT_EQ(result, 0);
}

// Test: Throws exception even when first child is non-struct but second would be struct
TEST_F(LookupFieldSelectorTest_1897, FirstNonStructThrowsBeforeCheckingSecond_1897) {
    XMP_Node* arrayNode = CreateNode(nullptr, "array", 0);

    // First child is NOT a struct
    XMP_Node* nonStructChild = CreateNode(arrayNode, "item1", 0);
    arrayNode->children.push_back(nonStructChild);

    // Second child IS a struct with matching field
    XMP_Node* structChild = CreateNode(arrayNode, "item2", kXMP_PropValueIsStruct);
    arrayNode->children.push_back(structChild);
    XMP_Node* field = CreateNode(structChild, "fieldName", "fieldValue", 0);
    structChild->children.push_back(field);

    EXPECT_THROW(LookupFieldSelector(arrayNode, "fieldName", "fieldValue"), XMP_Error);
}
