#include <gtest/gtest.h>
#include <cstdint>
#include <unordered_set>
#include <unordered_map>

// Based on the interface, TiffGroupKey appears to be a std::pair<uint16_t, uint16_t> or similar
// We need to include the actual header
#include "tiffimage_int.hpp"

using namespace Exiv2::Internal;

class TiffGroupKeyHashTest_107 : public ::testing::Test {
protected:
    TiffGroupKey_hash hasher;
};

// Test that the hash function produces a consistent result for the same input
TEST_F(TiffGroupKeyHashTest_107, ConsistentHashForSameInput_107) {
    TiffGroupKey key = {1, 2};
    std::size_t hash1 = hasher(key);
    std::size_t hash2 = hasher(key);
    EXPECT_EQ(hash1, hash2);
}

// Test that different inputs produce different hashes (not guaranteed but highly likely for simple cases)
TEST_F(TiffGroupKeyHashTest_107, DifferentInputsProduceDifferentHashes_107) {
    TiffGroupKey key1 = {1, 2};
    TiffGroupKey key2 = {2, 1};
    std::size_t hash1 = hasher(key1);
    std::size_t hash2 = hasher(key2);
    EXPECT_NE(hash1, hash2);
}

// Test hash with zero values
TEST_F(TiffGroupKeyHashTest_107, ZeroValues_107) {
    TiffGroupKey key = {0, 0};
    std::size_t hash = hasher(key);
    // Hash of (0,0) should be the hash of uint64_t(0)
    std::size_t expected = std::hash<uint64_t>{}(0);
    EXPECT_EQ(hash, expected);
}

// Test hash with first element zero
TEST_F(TiffGroupKeyHashTest_107, FirstElementZero_107) {
    TiffGroupKey key = {0, 5};
    std::size_t hash = hasher(key);
    std::size_t expected = std::hash<uint64_t>{}(static_cast<uint64_t>(5));
    EXPECT_EQ(hash, expected);
}

// Test hash with second element zero
TEST_F(TiffGroupKeyHashTest_107, SecondElementZero_107) {
    TiffGroupKey key = {5, 0};
    std::size_t hash = hasher(key);
    std::size_t expected = std::hash<uint64_t>{}(static_cast<uint64_t>(5) << 32);
    EXPECT_EQ(hash, expected);
}

// Test that the hash correctly combines first and second elements
TEST_F(TiffGroupKeyHashTest_107, CorrectCombination_107) {
    TiffGroupKey key = {3, 7};
    std::size_t hash = hasher(key);
    uint64_t combined = (static_cast<uint64_t>(key.first) << 32) | static_cast<uint64_t>(key.second);
    std::size_t expected = std::hash<uint64_t>{}(combined);
    EXPECT_EQ(hash, expected);
}

// Test that the hash is noexcept
TEST_F(TiffGroupKeyHashTest_107, IsNoexcept_107) {
    TiffGroupKey key = {1, 2};
    EXPECT_TRUE(noexcept(hasher(key)));
}

// Test that (a,b) and (b,a) are distinguishable (order matters)
TEST_F(TiffGroupKeyHashTest_107, OrderMatters_107) {
    TiffGroupKey key1 = {100, 200};
    TiffGroupKey key2 = {200, 100};
    EXPECT_NE(hasher(key1), hasher(key2));
}

// Test with maximum values for the key components
TEST_F(TiffGroupKeyHashTest_107, MaxValues_107) {
    TiffGroupKey key = {0xFFFF, 0xFFFF};
    std::size_t hash = hasher(key);
    uint64_t combined = (static_cast<uint64_t>(0xFFFF) << 32) | static_cast<uint64_t>(0xFFFF);
    std::size_t expected = std::hash<uint64_t>{}(combined);
    EXPECT_EQ(hash, expected);
}

// Test usability in an unordered container
TEST_F(TiffGroupKeyHashTest_107, UsableInUnorderedMap_107) {
    std::unordered_map<TiffGroupKey, int, TiffGroupKey_hash> map;
    map[{1, 2}] = 42;
    map[{3, 4}] = 84;
    
    EXPECT_EQ(map[{1, 2}], 42);
    EXPECT_EQ(map[{3, 4}], 84);
    EXPECT_EQ(map.count({1, 2}), 1u);
    EXPECT_EQ(map.count({5, 6}), 0u);
}

// Test that identical keys map to same bucket in unordered_set
TEST_F(TiffGroupKeyHashTest_107, IdenticalKeysInUnorderedSet_107) {
    std::unordered_set<TiffGroupKey, TiffGroupKey_hash> set;
    set.insert({10, 20});
    set.insert({10, 20}); // duplicate
    EXPECT_EQ(set.size(), 1u);
}

// Test boundary: one element at max, other at min
TEST_F(TiffGroupKeyHashTest_107, BoundaryMaxMin_107) {
    TiffGroupKey key1 = {0xFFFF, 0};
    TiffGroupKey key2 = {0, 0xFFFF};
    EXPECT_NE(hasher(key1), hasher(key2));
}

// Test a variety of keys produce unique hashes (collision resistance check)
TEST_F(TiffGroupKeyHashTest_107, CollisionResistance_107) {
    std::unordered_set<std::size_t> hashes;
    for (uint32_t i = 0; i < 100; ++i) {
        for (uint32_t j = 0; j < 100; ++j) {
            TiffGroupKey key = {static_cast<uint16_t>(i), static_cast<uint16_t>(j)};
            hashes.insert(hasher(key));
        }
    }
    // We expect all 10000 hashes to be unique for such small inputs
    EXPECT_EQ(hashes.size(), 10000u);
}
