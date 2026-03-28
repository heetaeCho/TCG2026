#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <array>
#include "exiv2/slice.hpp"

// Test makeSlice with a normal vector of integers
TEST(MakeSliceTest_22, NormalVectorOfInts_22) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto slice = Exiv2::makeSlice(v);
    EXPECT_EQ(slice.size(), v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        EXPECT_EQ(slice.at(i), v[i]);
    }
}

// Test makeSlice with an empty vector
TEST(MakeSliceTest_22, EmptyVector_22) {
    std::vector<int> v;
    auto slice = Exiv2::makeSlice(v);
    EXPECT_EQ(slice.size(), 0u);
}

// Test makeSlice with a single-element vector
TEST(MakeSliceTest_22, SingleElementVector_22) {
    std::vector<int> v = {42};
    auto slice = Exiv2::makeSlice(v);
    EXPECT_EQ(slice.size(), 1u);
    EXPECT_EQ(slice.at(0), 42);
}

// Test makeSlice with a vector of unsigned chars (byte-like)
TEST(MakeSliceTest_22, VectorOfUnsignedChars_22) {
    std::vector<unsigned char> v = {0x00, 0xFF, 0xAB, 0xCD};
    auto slice = Exiv2::makeSlice(v);
    EXPECT_EQ(slice.size(), 4u);
    EXPECT_EQ(slice.at(0), 0x00);
    EXPECT_EQ(slice.at(1), 0xFF);
    EXPECT_EQ(slice.at(2), 0xAB);
    EXPECT_EQ(slice.at(3), 0xCD);
}

// Test that makeSlice reflects modifications to the original container
TEST(MakeSliceTest_22, ModifyThroughSlice_22) {
    std::vector<int> v = {10, 20, 30};
    auto slice = Exiv2::makeSlice(v);
    slice.at(1) = 99;
    EXPECT_EQ(v[1], 99);
}

// Test that modifications to the original container are visible through the slice
TEST(MakeSliceTest_22, ModifyOriginalReflectedInSlice_22) {
    std::vector<int> v = {10, 20, 30};
    auto slice = Exiv2::makeSlice(v);
    v[2] = 77;
    EXPECT_EQ(slice.at(2), 77);
}

// Test makeSlice with a large vector
TEST(MakeSliceTest_22, LargeVector_22) {
    std::vector<int> v(10000);
    for (int i = 0; i < 10000; ++i) {
        v[i] = i;
    }
    auto slice = Exiv2::makeSlice(v);
    EXPECT_EQ(slice.size(), 10000u);
    EXPECT_EQ(slice.at(0), 0);
    EXPECT_EQ(slice.at(9999), 9999);
}

// Test makeSlice creates a slice covering the full range [0, size())
TEST(MakeSliceTest_22, FullRangeCoverage_22) {
    std::vector<int> v = {5, 10, 15, 20, 25};
    auto slice = Exiv2::makeSlice(v);
    EXPECT_EQ(slice.size(), v.size());
    // Verify all elements are accessible
    for (size_t i = 0; i < v.size(); ++i) {
        EXPECT_EQ(slice.at(i), v[i]);
    }
}

// Test out-of-bounds access throws
TEST(MakeSliceTest_22, OutOfBoundsAccessThrows_22) {
    std::vector<int> v = {1, 2, 3};
    auto slice = Exiv2::makeSlice(v);
    EXPECT_THROW(slice.at(3), std::out_of_range);
    EXPECT_THROW(slice.at(100), std::out_of_range);
}

// Test makeSlice with vector of doubles
TEST(MakeSliceTest_22, VectorOfDoubles_22) {
    std::vector<double> v = {1.1, 2.2, 3.3};
    auto slice = Exiv2::makeSlice(v);
    EXPECT_EQ(slice.size(), 3u);
    EXPECT_DOUBLE_EQ(slice.at(0), 1.1);
    EXPECT_DOUBLE_EQ(slice.at(1), 2.2);
    EXPECT_DOUBLE_EQ(slice.at(2), 3.3);
}

// Test subSlice from a makeSlice result
TEST(MakeSliceTest_22, SubSliceFromMakeSlice_22) {
    std::vector<int> v = {10, 20, 30, 40, 50};
    auto slice = Exiv2::makeSlice(v);
    auto sub = slice.subSlice(1, 4);
    EXPECT_EQ(sub.size(), 3u);
    EXPECT_EQ(sub.at(0), 20);
    EXPECT_EQ(sub.at(1), 30);
    EXPECT_EQ(sub.at(2), 40);
}

// Test empty subSlice
TEST(MakeSliceTest_22, EmptySubSlice_22) {
    std::vector<int> v = {10, 20, 30};
    auto slice = Exiv2::makeSlice(v);
    auto sub = slice.subSlice(2, 2);
    EXPECT_EQ(sub.size(), 0u);
}

// Test makeSlice with const container
TEST(MakeSliceTest_22, ConstVector_22) {
    const std::vector<int> v = {1, 2, 3, 4};
    auto slice = Exiv2::makeSlice(v);
    EXPECT_EQ(slice.size(), 4u);
    EXPECT_EQ(slice.at(0), 1);
    EXPECT_EQ(slice.at(3), 4);
}

// Test that accessing at on empty slice throws
TEST(MakeSliceTest_22, EmptySliceAccessThrows_22) {
    std::vector<int> v;
    auto slice = Exiv2::makeSlice(v);
    EXPECT_THROW(slice.at(0), std::out_of_range);
}
