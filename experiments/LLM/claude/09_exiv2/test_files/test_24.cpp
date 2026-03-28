#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <array>
#include "exiv2/slice.hpp"

// Test makeSliceUntil with a vector of ints, normal case
TEST(MakeSliceUntilTest_24, NormalVectorSlice_24) {
    std::vector<int> v = {10, 20, 30, 40, 50};
    auto sl = Exiv2::makeSliceUntil(v, 3);
    EXPECT_EQ(sl.size(), 3u);
    EXPECT_EQ(sl.at(0), 10);
    EXPECT_EQ(sl.at(1), 20);
    EXPECT_EQ(sl.at(2), 30);
}

// Test makeSliceUntil with end == 0 (empty slice)
TEST(MakeSliceUntilTest_24, EmptySlice_24) {
    std::vector<int> v = {1, 2, 3};
    auto sl = Exiv2::makeSliceUntil(v, 0);
    EXPECT_EQ(sl.size(), 0u);
}

// Test makeSliceUntil with end == container size (full slice)
TEST(MakeSliceUntilTest_24, FullSlice_24) {
    std::vector<int> v = {5, 10, 15, 20};
    auto sl = Exiv2::makeSliceUntil(v, v.size());
    EXPECT_EQ(sl.size(), v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        EXPECT_EQ(sl.at(i), v[i]);
    }
}

// Test makeSliceUntil with end == 1 (single element slice)
TEST(MakeSliceUntilTest_24, SingleElementSlice_24) {
    std::vector<int> v = {42, 99, 100};
    auto sl = Exiv2::makeSliceUntil(v, 1);
    EXPECT_EQ(sl.size(), 1u);
    EXPECT_EQ(sl.at(0), 42);
}

// Test that modifications through the slice are reflected in the original container
TEST(MakeSliceUntilTest_24, MutabilityThroughSlice_24) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto sl = Exiv2::makeSliceUntil(v, 3);
    sl.at(0) = 100;
    EXPECT_EQ(v[0], 100);
}

// Test makeSliceUntil with end exceeding container size throws
TEST(MakeSliceUntilTest_24, EndExceedsContainerSizeThrows_24) {
    std::vector<int> v = {1, 2, 3};
    EXPECT_THROW(Exiv2::makeSliceUntil(v, 10), std::out_of_range);
}

// Test makeSliceUntil on a const container
TEST(MakeSliceUntilTest_24, ConstContainer_24) {
    const std::vector<int> v = {10, 20, 30, 40};
    auto sl = Exiv2::makeSliceUntil(v, 2);
    EXPECT_EQ(sl.size(), 2u);
    EXPECT_EQ(sl.at(0), 10);
    EXPECT_EQ(sl.at(1), 20);
}

// Test makeSliceUntil with vector of unsigned char (byte-like data)
TEST(MakeSliceUntilTest_24, ByteVector_24) {
    std::vector<uint8_t> v = {0x00, 0x01, 0x02, 0xFF};
    auto sl = Exiv2::makeSliceUntil(v, 4);
    EXPECT_EQ(sl.size(), 4u);
    EXPECT_EQ(sl.at(3), 0xFF);
}

// Test accessing out-of-bounds index on the slice itself throws
TEST(MakeSliceUntilTest_24, AccessOutOfBoundsOnSlice_24) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto sl = Exiv2::makeSliceUntil(v, 3);
    EXPECT_THROW(sl.at(3), std::out_of_range);
}

// Test makeSliceUntil on an empty container with end == 0
TEST(MakeSliceUntilTest_24, EmptyContainerZeroEnd_24) {
    std::vector<int> v;
    auto sl = Exiv2::makeSliceUntil(v, 0);
    EXPECT_EQ(sl.size(), 0u);
}

// Test makeSliceUntil on an empty container with end > 0 throws
TEST(MakeSliceUntilTest_24, EmptyContainerNonZeroEndThrows_24) {
    std::vector<int> v;
    EXPECT_THROW(Exiv2::makeSliceUntil(v, 1), std::out_of_range);
}

// Test that taking a subSlice from a slice created by makeSliceUntil works
TEST(MakeSliceUntilTest_24, SubSliceFromSlice_24) {
    std::vector<int> v = {10, 20, 30, 40, 50};
    auto sl = Exiv2::makeSliceUntil(v, 5);
    auto sub = sl.subSlice(1, 4);
    EXPECT_EQ(sub.size(), 3u);
    EXPECT_EQ(sub.at(0), 20);
    EXPECT_EQ(sub.at(1), 30);
    EXPECT_EQ(sub.at(2), 40);
}

// Test makeSliceUntil with a large container
TEST(MakeSliceUntilTest_24, LargeContainer_24) {
    std::vector<int> v(10000);
    for (size_t i = 0; i < v.size(); ++i) {
        v[i] = static_cast<int>(i);
    }
    auto sl = Exiv2::makeSliceUntil(v, 5000);
    EXPECT_EQ(sl.size(), 5000u);
    EXPECT_EQ(sl.at(0), 0);
    EXPECT_EQ(sl.at(4999), 4999);
}

// Test iterator access on slice created by makeSliceUntil
TEST(MakeSliceUntilTest_24, IteratorAccess_24) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto sl = Exiv2::makeSliceUntil(v, 4);
    auto it = sl.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    auto end = sl.end();
    EXPECT_EQ(std::distance(sl.begin(), end), 4);
}
