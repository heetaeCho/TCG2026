#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "exiv2/slice.hpp"

// Test with vector<int> - normal operation
TEST(MakeSliceFromTest_23, NormalOperationWithVector_23) {
    std::vector<int> v = {10, 20, 30, 40, 50};
    auto slice = Exiv2::makeSliceFrom(v, 2);
    
    EXPECT_EQ(slice.size(), 3u);
    EXPECT_EQ(slice.at(0), 30);
    EXPECT_EQ(slice.at(1), 40);
    EXPECT_EQ(slice.at(2), 50);
}

// Test slicing from beginning (begin=0)
TEST(MakeSliceFromTest_23, SliceFromBeginning_23) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto slice = Exiv2::makeSliceFrom(v, 0);
    
    EXPECT_EQ(slice.size(), 5u);
    EXPECT_EQ(slice.at(0), 1);
    EXPECT_EQ(slice.at(4), 5);
}

// Test slicing from end (begin=size), yielding empty slice
TEST(MakeSliceFromTest_23, SliceFromEnd_23) {
    std::vector<int> v = {1, 2, 3};
    auto slice = Exiv2::makeSliceFrom(v, v.size());
    
    EXPECT_EQ(slice.size(), 0u);
}

// Test slicing from last element
TEST(MakeSliceFromTest_23, SliceFromLastElement_23) {
    std::vector<int> v = {10, 20, 30};
    auto slice = Exiv2::makeSliceFrom(v, 2);
    
    EXPECT_EQ(slice.size(), 1u);
    EXPECT_EQ(slice.at(0), 30);
}

// Test with empty container and begin=0
TEST(MakeSliceFromTest_23, EmptyContainerBeginZero_23) {
    std::vector<int> v;
    auto slice = Exiv2::makeSliceFrom(v, 0);
    
    EXPECT_EQ(slice.size(), 0u);
}

// Test with single element container
TEST(MakeSliceFromTest_23, SingleElementContainer_23) {
    std::vector<int> v = {42};
    auto slice = Exiv2::makeSliceFrom(v, 0);
    
    EXPECT_EQ(slice.size(), 1u);
    EXPECT_EQ(slice.at(0), 42);
}

// Test that begin > size throws
TEST(MakeSliceFromTest_23, BeginBeyondSizeThrows_23) {
    std::vector<int> v = {1, 2, 3};
    EXPECT_THROW(Exiv2::makeSliceFrom(v, 10), std::out_of_range);
}

// Test with vector<unsigned char> (common in Exiv2)
TEST(MakeSliceFromTest_23, VectorOfUnsignedChar_23) {
    std::vector<unsigned char> v = {0x00, 0x01, 0x02, 0x03, 0xFF};
    auto slice = Exiv2::makeSliceFrom(v, 3);
    
    EXPECT_EQ(slice.size(), 2u);
    EXPECT_EQ(slice.at(0), 0x03);
    EXPECT_EQ(slice.at(1), 0xFF);
}

// Test that modifications through slice are visible in original container
TEST(MakeSliceFromTest_23, ModificationThroughSlice_23) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto slice = Exiv2::makeSliceFrom(v, 2);
    
    slice.at(0) = 99;
    EXPECT_EQ(v[2], 99);
}

// Test with vector<std::string>
TEST(MakeSliceFromTest_23, VectorOfStrings_23) {
    std::vector<std::string> v = {"hello", "world", "foo", "bar"};
    auto slice = Exiv2::makeSliceFrom(v, 1);
    
    EXPECT_EQ(slice.size(), 3u);
    EXPECT_EQ(slice.at(0), "world");
    EXPECT_EQ(slice.at(1), "foo");
    EXPECT_EQ(slice.at(2), "bar");
}

// Test with const container
TEST(MakeSliceFromTest_23, ConstContainer_23) {
    const std::vector<int> v = {10, 20, 30, 40};
    auto slice = Exiv2::makeSliceFrom(v, 1);
    
    EXPECT_EQ(slice.size(), 3u);
    EXPECT_EQ(slice.at(0), 20);
    EXPECT_EQ(slice.at(1), 30);
    EXPECT_EQ(slice.at(2), 40);
}

// Test out of range access on the slice itself
TEST(MakeSliceFromTest_23, SliceOutOfRangeAccess_23) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto slice = Exiv2::makeSliceFrom(v, 3);
    
    EXPECT_EQ(slice.size(), 2u);
    EXPECT_THROW(slice.at(2), std::out_of_range);
}

// Test with large container
TEST(MakeSliceFromTest_23, LargeContainer_23) {
    std::vector<int> v(10000);
    for (size_t i = 0; i < v.size(); ++i) {
        v[i] = static_cast<int>(i);
    }
    auto slice = Exiv2::makeSliceFrom(v, 9990);
    
    EXPECT_EQ(slice.size(), 10u);
    EXPECT_EQ(slice.at(0), 9990);
    EXPECT_EQ(slice.at(9), 9999);
}

// Test begin at size-1 for boundary
TEST(MakeSliceFromTest_23, BeginAtSizeMinusOne_23) {
    std::vector<int> v = {100, 200, 300};
    auto slice = Exiv2::makeSliceFrom(v, v.size() - 1);
    
    EXPECT_EQ(slice.size(), 1u);
    EXPECT_EQ(slice.at(0), 300);
}
