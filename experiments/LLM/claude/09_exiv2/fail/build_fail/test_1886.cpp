#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <stdexcept>

// Include necessary XMP headers
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// We need access to the static function. One approach is to include the .cpp file.
// We redefine static to nothing temporarily to expose the function for testing.
#define static
#include "XMPCore_Impl.cpp"
#undef static

class FindIndexedItemTest_1886 : public ::testing::Test {
protected:
    void SetUp() override {
        arrayNode = new XMP_Node(nullptr, "TestArray", 0);
    }

    void TearDown() override {
        // Clean up all children
        for (auto* child : arrayNode->children) {
            delete child;
        }
        arrayNode->children.clear();
        delete arrayNode;
    }

    void AddChildren(int count) {
        for (int i = 0; i < count; ++i) {
            XMP_Node* child = new XMP_Node(arrayNode, "item", 0);
            arrayNode->children.push_back(child);
        }
    }

    XMP_Node* arrayNode;
};

// Test: Index [1] on array with 1 child returns 0 (zero-based)
TEST_F(FindIndexedItemTest_1886, ValidIndex1ReturnsZero_1886) {
    AddChildren(1);
    std::string indexStep = "[1]";
    XMP_Index result = FindIndexedItem(arrayNode, indexStep, false);
    EXPECT_EQ(result, 0);
}

// Test: Index [2] on array with 3 children returns 1
TEST_F(FindIndexedItemTest_1886, ValidIndex2ReturnsOne_1886) {
    AddChildren(3);
    std::string indexStep = "[2]";
    XMP_Index result = FindIndexedItem(arrayNode, indexStep, false);
    EXPECT_EQ(result, 1);
}

// Test: Index [3] on array with 3 children returns 2
TEST_F(FindIndexedItemTest_1886, ValidIndex3ReturnsTwo_1886) {
    AddChildren(3);
    std::string indexStep = "[3]";
    XMP_Index result = FindIndexedItem(arrayNode, indexStep, false);
    EXPECT_EQ(result, 2);
}

// Test: Index [1] on empty array with createNodes=false returns -1
TEST_F(FindIndexedItemTest_1886, IndexBeyondSizeNoCreateReturnsNegOne_1886) {
    // No children added
    std::string indexStep = "[1]";
    XMP_Index result = FindIndexedItem(arrayNode, indexStep, false);
    EXPECT_EQ(result, -1);
}

// Test: Index [1] on empty array with createNodes=true appends node and returns 0
TEST_F(FindIndexedItemTest_1886, IndexLastPlusOneWithCreateAppendsNode_1886) {
    // Empty array, index [1] means index 0 after --index, which equals children.size() (0)
    std::string indexStep = "[1]";
    XMP_Index result = FindIndexedItem(arrayNode, indexStep, true);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(arrayNode->children.size(), 1u);
}

// Test: Index [2] on array with 1 child and createNodes=true appends and returns 1
TEST_F(FindIndexedItemTest_1886, AppendToExistingArrayWithCreate_1886) {
    AddChildren(1);
    std::string indexStep = "[2]";
    XMP_Index result = FindIndexedItem(arrayNode, indexStep, true);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(arrayNode->children.size(), 2u);
}

// Test: Index [3] on array with 1 child and createNodes=true returns -1 (too far beyond)
TEST_F(FindIndexedItemTest_1886, IndexTooFarBeyondWithCreateReturnsNegOne_1886) {
    AddChildren(1);
    std::string indexStep = "[3]";
    XMP_Index result = FindIndexedItem(arrayNode, indexStep, true);
    EXPECT_EQ(result, -1);
}

// Test: Index [5] on array with 5 children returns last element index 4
TEST_F(FindIndexedItemTest_1886, LastElementIndex_1886) {
    AddChildren(5);
    std::string indexStep = "[5]";
    XMP_Index result = FindIndexedItem(arrayNode, indexStep, false);
    EXPECT_EQ(result, 4);
}

// Test: Index [6] on array with 5 children returns -1
TEST_F(FindIndexedItemTest_1886, IndexBeyondArraySizeReturnsNegOne_1886) {
    AddChildren(5);
    std::string indexStep = "[6]";
    XMP_Index result = FindIndexedItem(arrayNode, indexStep, false);
    EXPECT_EQ(result, -1);
}

// Test: Multi-digit index [10] on array with 10 children returns 9
TEST_F(FindIndexedItemTest_1886, MultiDigitIndex_1886) {
    AddChildren(10);
    std::string indexStep = "[10]";
    XMP_Index result = FindIndexedItem(arrayNode, indexStep, false);
    EXPECT_EQ(result, 9);
}

// Test: Large index [100] on array with 100 children returns 99
TEST_F(FindIndexedItemTest_1886, LargeIndex_1886) {
    AddChildren(100);
    std::string indexStep = "[100]";
    XMP_Index result = FindIndexedItem(arrayNode, indexStep, false);
    EXPECT_EQ(result, 99);
}

// Test: createNodes=true does not create when index is within existing range
TEST_F(FindIndexedItemTest_1886, CreateNodesDoesNotCreateWhenWithinRange_1886) {
    AddChildren(3);
    std::string indexStep = "[2]";
    XMP_Index result = FindIndexedItem(arrayNode, indexStep, true);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(arrayNode->children.size(), 3u); // No new node added
}

// Test: Index [1] on array with multiple children returns 0
TEST_F(FindIndexedItemTest_1886, FirstIndexOnMultipleChildren_1886) {
    AddChildren(5);
    std::string indexStep = "[1]";
    XMP_Index result = FindIndexedItem(arrayNode, indexStep, false);
    EXPECT_EQ(result, 0);
}
