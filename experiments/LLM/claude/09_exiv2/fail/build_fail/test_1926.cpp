#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include necessary XMP headers
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// We need access to DoSetArrayItem - since it's a static function in the .cpp file,
// we include the source directly for testing purposes
// Forward declarations and includes needed by the source
#include "XMPMeta-GetSet.cpp"

// Constants we need
#ifndef kXMP_ArrayItemName
#define kXMP_ArrayItemName "[]"
#endif

#ifndef kXMP_ArrayLastItem
#define kXMP_ArrayLastItem ((XMP_Index)(-1))
#endif

class DoSetArrayItemTest_1926 : public ::testing::Test {
protected:
    XMP_Node* arrayNode;

    void SetUp() override {
        arrayNode = new XMP_Node(nullptr, "testArray", 0);
    }

    void TearDown() override {
        delete arrayNode;
    }

    void AddChildrenToArray(int count) {
        for (int i = 0; i < count; i++) {
            std::string val = "item" + std::to_string(i + 1);
            XMP_Node* child = new XMP_Node(arrayNode, kXMP_ArrayItemName, val.c_str(), 0);
            arrayNode->children.push_back(child);
        }
    }

    size_t ChildCount() {
        return arrayNode->children.size();
    }
};

// Test appending to an empty array (itemIndex = arraySize+1 = 1, no location flag)
TEST_F(DoSetArrayItemTest_1926, AppendToEmptyArray_1926) {
    DoSetArrayItem(arrayNode, 1, "newItem", 0);
    EXPECT_EQ(ChildCount(), 1u);
    EXPECT_EQ(arrayNode->children[0]->value, "newItem");
}

// Test using kXMP_ArrayLastItem on empty array
TEST_F(DoSetArrayItemTest_1926, ArrayLastItemOnEmptyArray_1926) {
    // kXMP_ArrayLastItem maps to arraySize which is 0, then itemIndex becomes 0
    // With no location mask, itemIndex=0 < 1, should throw BadIndex
    // Actually: arraySize=0, itemIndex becomes 0, then since 0 != arraySize+1=1,
    // falls to else branch where itemIndex < 1, throws
    EXPECT_ANY_THROW(DoSetArrayItem(arrayNode, kXMP_ArrayLastItem, "value", 0));
}

// Test replacing an existing item
TEST_F(DoSetArrayItemTest_1926, ReplaceExistingItem_1926) {
    AddChildrenToArray(3);
    DoSetArrayItem(arrayNode, 2, "replaced", 0);
    EXPECT_EQ(ChildCount(), 3u);
    EXPECT_EQ(arrayNode->children[1]->value, "replaced");
}

// Test replacing first item
TEST_F(DoSetArrayItemTest_1926, ReplaceFirstItem_1926) {
    AddChildrenToArray(3);
    DoSetArrayItem(arrayNode, 1, "newFirst", 0);
    EXPECT_EQ(ChildCount(), 3u);
    EXPECT_EQ(arrayNode->children[0]->value, "newFirst");
}

// Test replacing last item using kXMP_ArrayLastItem
TEST_F(DoSetArrayItemTest_1926, ReplaceLastItem_1926) {
    AddChildrenToArray(3);
    DoSetArrayItem(arrayNode, kXMP_ArrayLastItem, "newLast", 0);
    EXPECT_EQ(ChildCount(), 3u);
    EXPECT_EQ(arrayNode->children[2]->value, "newLast");
}

// Test insert before item
TEST_F(DoSetArrayItemTest_1926, InsertBeforeItem_1926) {
    AddChildrenToArray(3);
    DoSetArrayItem(arrayNode, 2, "inserted", kXMP_InsertBeforeItem);
    EXPECT_EQ(ChildCount(), 4u);
    EXPECT_EQ(arrayNode->children[1]->value, "inserted");
    EXPECT_EQ(arrayNode->children[2]->value, "item2");
}

// Test insert after item
TEST_F(DoSetArrayItemTest_1926, InsertAfterItem_1926) {
    AddChildrenToArray(3);
    DoSetArrayItem(arrayNode, 2, "inserted", kXMP_InsertAfterItem);
    EXPECT_EQ(ChildCount(), 4u);
    EXPECT_EQ(arrayNode->children[2]->value, "inserted");
    EXPECT_EQ(arrayNode->children[1]->value, "item2");
}

// Test insert before first item
TEST_F(DoSetArrayItemTest_1926, InsertBeforeFirstItem_1926) {
    AddChildrenToArray(3);
    DoSetArrayItem(arrayNode, 1, "inserted", kXMP_InsertBeforeItem);
    EXPECT_EQ(ChildCount(), 4u);
    EXPECT_EQ(arrayNode->children[0]->value, "inserted");
    EXPECT_EQ(arrayNode->children[1]->value, "item1");
}

// Test insert after last item (becomes append)
TEST_F(DoSetArrayItemTest_1926, InsertAfterLastItem_1926) {
    AddChildrenToArray(3);
    // itemIndex=3=arraySize, itemLoc=kXMP_InsertAfterItem -> itemIndex becomes 4, itemLoc=0
    // itemIndex=4=arraySize+1 -> appends
    DoSetArrayItem(arrayNode, 3, "appended", kXMP_InsertAfterItem);
    EXPECT_EQ(ChildCount(), 4u);
    EXPECT_EQ(arrayNode->children[3]->value, "appended");
}

// Test index 0 with InsertAfterItem converts to index 1 InsertBeforeItem
TEST_F(DoSetArrayItemTest_1926, IndexZeroInsertAfterBecomesInsertBefore_1926) {
    AddChildrenToArray(3);
    DoSetArrayItem(arrayNode, 0, "inserted", kXMP_InsertAfterItem);
    EXPECT_EQ(ChildCount(), 4u);
    EXPECT_EQ(arrayNode->children[0]->value, "inserted");
}

// Test insert before at arraySize+1 (becomes simple append)
TEST_F(DoSetArrayItemTest_1926, InsertBeforeAtEnd_1926) {
    AddChildrenToArray(3);
    // itemIndex=4=arraySize+1, kXMP_InsertBeforeItem -> itemLoc becomes 0, then append
    DoSetArrayItem(arrayNode, 4, "appended", kXMP_InsertBeforeItem);
    EXPECT_EQ(ChildCount(), 4u);
    EXPECT_EQ(arrayNode->children[3]->value, "appended");
}

// Test out of bounds - index too large
TEST_F(DoSetArrayItemTest_1926, IndexTooLargeThrows_1926) {
    AddChildrenToArray(3);
    EXPECT_ANY_THROW(DoSetArrayItem(arrayNode, 5, "value", 0));
}

// Test out of bounds - index 0 with no location flag
TEST_F(DoSetArrayItemTest_1926, IndexZeroNoFlagThrows_1926) {
    AddChildrenToArray(3);
    // itemIndex=0, itemLoc=0, then 0 != arraySize+1=4, falls to else, 0 < 1 -> throws
    EXPECT_ANY_THROW(DoSetArrayItem(arrayNode, 0, "value", 0));
}

// Test negative index (other than kXMP_ArrayLastItem)
TEST_F(DoSetArrayItemTest_1926, NegativeIndexThrows_1926) {
    AddChildrenToArray(3);
    EXPECT_ANY_THROW(DoSetArrayItem(arrayNode, -2, "value", 0));
}

// Test cannot insert before or after implicit new item at arraySize+1
TEST_F(DoSetArrayItemTest_1926, InsertAfterAtEndPlusOneThrows_1926) {
    AddChildrenToArray(3);
    // itemIndex=4=arraySize+1, itemLoc=kXMP_InsertAfterItem (not cleared by any rule)
    // Should throw "Can't insert before or after implicit new item"
    EXPECT_ANY_THROW(DoSetArrayItem(arrayNode, 4, "value", kXMP_InsertAfterItem));
}

// Test appending to non-empty array
TEST_F(DoSetArrayItemTest_1926, AppendToNonEmptyArray_1926) {
    AddChildrenToArray(2);
    DoSetArrayItem(arrayNode, 3, "third", 0);
    EXPECT_EQ(ChildCount(), 3u);
    EXPECT_EQ(arrayNode->children[2]->value, "third");
}

// Test single element array replace
TEST_F(DoSetArrayItemTest_1926, SingleElementReplace_1926) {
    AddChildrenToArray(1);
    DoSetArrayItem(arrayNode, 1, "replaced", 0);
    EXPECT_EQ(ChildCount(), 1u);
    EXPECT_EQ(arrayNode->children[0]->value, "replaced");
}

// Test insert before on single element
TEST_F(DoSetArrayItemTest_1926, SingleElementInsertBefore_1926) {
    AddChildrenToArray(1);
    DoSetArrayItem(arrayNode, 1, "before", kXMP_InsertBeforeItem);
    EXPECT_EQ(ChildCount(), 2u);
    EXPECT_EQ(arrayNode->children[0]->value, "before");
    EXPECT_EQ(arrayNode->children[1]->value, "item1");
}

// Test insert after on single element (arraySize=1, itemIndex=1=arraySize, InsertAfter -> append)
TEST_F(DoSetArrayItemTest_1926, SingleElementInsertAfter_1926) {
    AddChildrenToArray(1);
    DoSetArrayItem(arrayNode, 1, "after", kXMP_InsertAfterItem);
    EXPECT_EQ(ChildCount(), 2u);
    EXPECT_EQ(arrayNode->children[1]->value, "after");
    EXPECT_EQ(arrayNode->children[0]->value, "item1");
}

// Test that parent of new node is set correctly
TEST_F(DoSetArrayItemTest_1926, NewNodeParentIsArrayNode_1926) {
    DoSetArrayItem(arrayNode, 1, "child", 0);
    EXPECT_EQ(arrayNode->children[0]->parent, arrayNode);
}

// Test insert before in middle of array
TEST_F(DoSetArrayItemTest_1926, InsertBeforeMiddle_1926) {
    AddChildrenToArray(5);
    DoSetArrayItem(arrayNode, 3, "inserted", kXMP_InsertBeforeItem);
    EXPECT_EQ(ChildCount(), 6u);
    EXPECT_EQ(arrayNode->children[2]->value, "inserted");
    EXPECT_EQ(arrayNode->children[3]->value, "item3");
}

// Test insert after in middle of array
TEST_F(DoSetArrayItemTest_1926, InsertAfterMiddle_1926) {
    AddChildrenToArray(5);
    DoSetArrayItem(arrayNode, 3, "inserted", kXMP_InsertAfterItem);
    EXPECT_EQ(ChildCount(), 6u);
    EXPECT_EQ(arrayNode->children[3]->value, "inserted");
    EXPECT_EQ(arrayNode->children[2]->value, "item3");
}

// Test multiple sequential appends
TEST_F(DoSetArrayItemTest_1926, MultipleAppends_1926) {
    for (int i = 1; i <= 5; i++) {
        std::string val = "val" + std::to_string(i);
        DoSetArrayItem(arrayNode, i, val.c_str(), 0);
    }
    EXPECT_EQ(ChildCount(), 5u);
    for (int i = 0; i < 5; i++) {
        std::string expected = "val" + std::to_string(i + 1);
        EXPECT_EQ(arrayNode->children[i]->value, expected);
    }
}
