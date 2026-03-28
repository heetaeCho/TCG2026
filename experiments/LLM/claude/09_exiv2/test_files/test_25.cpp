#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <cstdint>

// Include the header under test
#include "exiv2/slice.hpp"

// =============================================================================
// Tests for makeSliceUntil and Slice functionality
// =============================================================================

// ---------------------------------------------------------------------------
// Basic construction and access tests
// ---------------------------------------------------------------------------

TEST(MakeSliceUntilTest_25, CreateSliceFromIntArray_25) {
    int arr[] = {10, 20, 30, 40, 50};
    auto slice = Exiv2::makeSliceUntil(arr, 5);
    EXPECT_EQ(slice.size(), 5u);
}

TEST(MakeSliceUntilTest_25, CreateSliceFromConstIntArray_25) {
    const int arr[] = {1, 2, 3, 4, 5};
    auto slice = Exiv2::makeSliceUntil(arr, 5);
    EXPECT_EQ(slice.size(), 5u);
}

TEST(MakeSliceUntilTest_25, AccessElementsViaAt_25) {
    int arr[] = {100, 200, 300};
    auto slice = Exiv2::makeSliceUntil(arr, 3);
    EXPECT_EQ(slice.at(0), 100);
    EXPECT_EQ(slice.at(1), 200);
    EXPECT_EQ(slice.at(2), 300);
}

TEST(MakeSliceUntilTest_25, EmptySlice_25) {
    int arr[] = {1, 2, 3};
    auto slice = Exiv2::makeSliceUntil(arr, 0);
    EXPECT_EQ(slice.size(), 0u);
}

TEST(MakeSliceUntilTest_25, SingleElementSlice_25) {
    int arr[] = {42};
    auto slice = Exiv2::makeSliceUntil(arr, 1);
    EXPECT_EQ(slice.size(), 1u);
    EXPECT_EQ(slice.at(0), 42);
}

// ---------------------------------------------------------------------------
// Type variations
// ---------------------------------------------------------------------------

TEST(MakeSliceUntilTest_25, WorksWithUint8Array_25) {
    uint8_t data[] = {0x00, 0xFF, 0xAB, 0xCD};
    auto slice = Exiv2::makeSliceUntil(data, 4);
    EXPECT_EQ(slice.size(), 4u);
    EXPECT_EQ(slice.at(0), 0x00);
    EXPECT_EQ(slice.at(3), 0xCD);
}

TEST(MakeSliceUntilTest_25, WorksWithCharArray_25) {
    char data[] = "Hello";
    auto slice = Exiv2::makeSliceUntil(data, 5);
    EXPECT_EQ(slice.size(), 5u);
    EXPECT_EQ(slice.at(0), 'H');
    EXPECT_EQ(slice.at(4), 'o');
}

TEST(MakeSliceUntilTest_25, WorksWithDoubleArray_25) {
    double arr[] = {1.1, 2.2, 3.3};
    auto slice = Exiv2::makeSliceUntil(arr, 3);
    EXPECT_EQ(slice.size(), 3u);
    EXPECT_DOUBLE_EQ(slice.at(0), 1.1);
    EXPECT_DOUBLE_EQ(slice.at(2), 3.3);
}

// ---------------------------------------------------------------------------
// Modification through slice
// ---------------------------------------------------------------------------

TEST(MakeSliceUntilTest_25, ModifyElementThroughSlice_25) {
    int arr[] = {1, 2, 3, 4, 5};
    auto slice = Exiv2::makeSliceUntil(arr, 5);
    slice.at(2) = 99;
    EXPECT_EQ(arr[2], 99);
}

// ---------------------------------------------------------------------------
// Subslice tests
// ---------------------------------------------------------------------------

TEST(MakeSliceUntilTest_25, SubsliceCreation_25) {
    int arr[] = {10, 20, 30, 40, 50};
    auto slice = Exiv2::makeSliceUntil(arr, 5);
    auto sub = slice.subSlice(1, 4);
    EXPECT_EQ(sub.size(), 3u);
    EXPECT_EQ(sub.at(0), 20);
    EXPECT_EQ(sub.at(1), 30);
    EXPECT_EQ(sub.at(2), 40);
}

TEST(MakeSliceUntilTest_25, SubsliceEmptyRange_25) {
    int arr[] = {10, 20, 30};
    auto slice = Exiv2::makeSliceUntil(arr, 3);
    auto sub = slice.subSlice(1, 1);
    EXPECT_EQ(sub.size(), 0u);
}

// ---------------------------------------------------------------------------
// Boundary / error cases
// ---------------------------------------------------------------------------

TEST(MakeSliceUntilTest_25, AtOutOfBoundsThrows_25) {
    int arr[] = {1, 2, 3};
    auto slice = Exiv2::makeSliceUntil(arr, 3);
    EXPECT_THROW(slice.at(3), std::out_of_range);
}

TEST(MakeSliceUntilTest_25, AtOutOfBoundsOnEmptySliceThrows_25) {
    int arr[] = {1};
    auto slice = Exiv2::makeSliceUntil(arr, 0);
    EXPECT_THROW(slice.at(0), std::out_of_range);
}

TEST(MakeSliceUntilTest_25, SubsliceInvalidRangeThrows_25) {
    int arr[] = {1, 2, 3, 4, 5};
    auto slice = Exiv2::makeSliceUntil(arr, 5);
    // end > size should throw
    EXPECT_THROW(slice.subSlice(0, 6), std::out_of_range);
}

TEST(MakeSliceUntilTest_25, SubsliceBeginGreaterThanEndThrows_25) {
    int arr[] = {1, 2, 3, 4, 5};
    auto slice = Exiv2::makeSliceUntil(arr, 5);
    EXPECT_THROW(slice.subSlice(3, 2), std::out_of_range);
}

// ---------------------------------------------------------------------------
// Partial slice of array
// ---------------------------------------------------------------------------

TEST(MakeSliceUntilTest_25, PartialSliceOfLargerArray_25) {
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto slice = Exiv2::makeSliceUntil(arr, 5);
    EXPECT_EQ(slice.size(), 5u);
    EXPECT_EQ(slice.at(4), 4);
    EXPECT_THROW(slice.at(5), std::out_of_range);
}

// ---------------------------------------------------------------------------
// Pointer from vector data
// ---------------------------------------------------------------------------

TEST(MakeSliceUntilTest_25, WorksWithVectorData_25) {
    std::vector<int> vec = {10, 20, 30, 40, 50};
    auto slice = Exiv2::makeSliceUntil(vec.data(), vec.size());
    EXPECT_EQ(slice.size(), 5u);
    for (size_t i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(slice.at(i), vec[i]);
    }
}

TEST(MakeSliceUntilTest_25, ModifyVectorThroughSlice_25) {
    std::vector<int> vec = {1, 2, 3};
    auto slice = Exiv2::makeSliceUntil(vec.data(), vec.size());
    slice.at(1) = 42;
    EXPECT_EQ(vec[1], 42);
}

// ---------------------------------------------------------------------------
// Const correctness
// ---------------------------------------------------------------------------

TEST(MakeSliceUntilTest_25, ConstSliceReadOnly_25) {
    const int arr[] = {5, 10, 15};
    auto slice = Exiv2::makeSliceUntil(arr, 3);
    // Should be able to read
    EXPECT_EQ(slice.at(0), 5);
    EXPECT_EQ(slice.at(1), 10);
    EXPECT_EQ(slice.at(2), 15);
    // The returned slice should have const element type; writing would be a compile error
}

// ---------------------------------------------------------------------------
// Large slice boundary
// ---------------------------------------------------------------------------

TEST(MakeSliceUntilTest_25, LargeSlice_25) {
    std::vector<int> vec(10000);
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] = static_cast<int>(i);
    }
    auto slice = Exiv2::makeSliceUntil(vec.data(), vec.size());
    EXPECT_EQ(slice.size(), 10000u);
    EXPECT_EQ(slice.at(0), 0);
    EXPECT_EQ(slice.at(9999), 9999);
    EXPECT_THROW(slice.at(10000), std::out_of_range);
}

// ---------------------------------------------------------------------------
// Slice from Slice (nested subslice)
// ---------------------------------------------------------------------------

TEST(MakeSliceUntilTest_25, NestedSubslice_25) {
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto slice = Exiv2::makeSliceUntil(arr, 10);
    auto sub1 = slice.subSlice(2, 8);   // {2,3,4,5,6,7}
    auto sub2 = sub1.subSlice(1, 4);    // {3,4,5}
    EXPECT_EQ(sub2.size(), 3u);
    EXPECT_EQ(sub2.at(0), 3);
    EXPECT_EQ(sub2.at(1), 4);
    EXPECT_EQ(sub2.at(2), 5);
}

// ---------------------------------------------------------------------------
// Slice with end == 0 (empty)
// ---------------------------------------------------------------------------

TEST(MakeSliceUntilTest_25, ZeroEndProducesEmptySlice_25) {
    int arr[] = {1, 2, 3};
    auto slice = Exiv2::makeSliceUntil(arr, 0);
    EXPECT_EQ(slice.size(), 0u);
}

// ---------------------------------------------------------------------------
// Iterator-based tests (if begin/end are available)
// ---------------------------------------------------------------------------

TEST(MakeSliceUntilTest_25, IteratorBasedAccess_25) {
    int arr[] = {5, 10, 15, 20};
    auto slice = Exiv2::makeSliceUntil(arr, 4);
    int sum = 0;
    for (size_t i = 0; i < slice.size(); ++i) {
        sum += slice.at(i);
    }
    EXPECT_EQ(sum, 50);
}
