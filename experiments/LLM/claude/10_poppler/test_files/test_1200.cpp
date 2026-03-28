#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TextOutputDev.h"
#include "GfxState.h"
#include "Link.h"

#include <memory>
#include <cmath>

class TextPoolTest_1200 : public ::testing::Test {
protected:
    void SetUp() override {
        pool = std::make_unique<TextPool>();
    }

    void TearDown() override {
        pool.reset();
    }

    std::unique_ptr<TextPool> pool;
};

// Test that a newly constructed TextPool can be created without errors
TEST_F(TextPoolTest_1200, ConstructorCreatesValidPool_1200) {
    ASSERT_NE(pool, nullptr);
}

// Test getBaseIdx returns a value for various base values
TEST_F(TextPoolTest_1200, GetBaseIdxReturnsValueForZero_1200) {
    int idx = pool->getBaseIdx(0.0);
    // getBaseIdx should return some integer index; we just verify it doesn't crash
    // and returns a deterministic value
    int idx2 = pool->getBaseIdx(0.0);
    EXPECT_EQ(idx, idx2);
}

TEST_F(TextPoolTest_1200, GetBaseIdxReturnsValueForPositive_1200) {
    int idx = pool->getBaseIdx(100.0);
    int idx2 = pool->getBaseIdx(100.0);
    EXPECT_EQ(idx, idx2);
}

TEST_F(TextPoolTest_1200, GetBaseIdxReturnsValueForNegative_1200) {
    int idx = pool->getBaseIdx(-50.0);
    int idx2 = pool->getBaseIdx(-50.0);
    EXPECT_EQ(idx, idx2);
}

TEST_F(TextPoolTest_1200, GetBaseIdxDifferentBasesReturnDifferentIndices_1200) {
    // Bases that are far apart should likely map to different indices
    int idx1 = pool->getBaseIdx(0.0);
    int idx2 = pool->getBaseIdx(1000.0);
    // They could be different for sufficiently different base values
    // This is an observational test
    EXPECT_NE(idx1, idx2);
}

TEST_F(TextPoolTest_1200, GetBaseIdxCloseBasesMaySameIndex_1200) {
    // Very close bases might map to the same index
    int idx1 = pool->getBaseIdx(100.0);
    int idx2 = pool->getBaseIdx(100.001);
    // They are very close, so might be the same bucket
    // Just verify no crash; the actual equality depends on implementation
    (void)idx1;
    (void)idx2;
}

// Test that getPool returns nullptr for a fresh pool at a given index
TEST_F(TextPoolTest_1200, GetPoolReturnsNullForEmptyPool_1200) {
    // First we need to establish a valid base index range by calling getBaseIdx
    int baseIdx = pool->getBaseIdx(50.0);
    TextWord *word = pool->getPool(baseIdx);
    EXPECT_EQ(word, nullptr);
}

// Test setPool and getPool round-trip
TEST_F(TextPoolTest_1200, SetPoolAndGetPoolRoundTrip_1200) {
    // We need a valid base index first
    int baseIdx = pool->getBaseIdx(50.0);
    
    // Create a TextWord - requires GfxState
    // Since we can't easily create a real TextWord, we test with nullptr
    pool->setPool(baseIdx, nullptr);
    TextWord *result = pool->getPool(baseIdx);
    EXPECT_EQ(result, nullptr);
}

// Test sort on empty pool doesn't crash
TEST_F(TextPoolTest_1200, SortOnEmptyPoolDoesNotCrash_1200) {
    EXPECT_NO_FATAL_FAILURE(pool->sort());
}

// Test sort after establishing indices
TEST_F(TextPoolTest_1200, SortAfterGetBaseIdxDoesNotCrash_1200) {
    pool->getBaseIdx(10.0);
    pool->getBaseIdx(20.0);
    pool->getBaseIdx(30.0);
    EXPECT_NO_FATAL_FAILURE(pool->sort());
}

// Test multiple getBaseIdx calls with same value return same index
TEST_F(TextPoolTest_1200, GetBaseIdxIsDeterministic_1200) {
    int idx1 = pool->getBaseIdx(42.5);
    int idx2 = pool->getBaseIdx(42.5);
    int idx3 = pool->getBaseIdx(42.5);
    EXPECT_EQ(idx1, idx2);
    EXPECT_EQ(idx2, idx3);
}

// Test large base value
TEST_F(TextPoolTest_1200, GetBaseIdxLargeValue_1200) {
    int idx = pool->getBaseIdx(100000.0);
    // Should not crash and should return a valid index
    (void)idx;
}

// Test that multiple base indices can be established
TEST_F(TextPoolTest_1200, MultipleBaseIndicesCanBeEstablished_1200) {
    int idx1 = pool->getBaseIdx(0.0);
    int idx2 = pool->getBaseIdx(100.0);
    int idx3 = pool->getBaseIdx(200.0);
    
    // All should be retrievable
    TextWord *w1 = pool->getPool(idx1);
    TextWord *w2 = pool->getPool(idx2);
    TextWord *w3 = pool->getPool(idx3);
    
    EXPECT_EQ(w1, nullptr);
    EXPECT_EQ(w2, nullptr);
    EXPECT_EQ(w3, nullptr);
}

// Test getBaseIdx ordering - larger bases should generally give larger or equal indices
TEST_F(TextPoolTest_1200, GetBaseIdxOrderingIsMonotonic_1200) {
    int idx1 = pool->getBaseIdx(10.0);
    int idx2 = pool->getBaseIdx(20.0);
    int idx3 = pool->getBaseIdx(30.0);
    
    EXPECT_LE(idx1, idx2);
    EXPECT_LE(idx2, idx3);
}

// Test setPool with nullptr then set again
TEST_F(TextPoolTest_1200, SetPoolOverwritesPreviousValue_1200) {
    int baseIdx = pool->getBaseIdx(50.0);
    
    pool->setPool(baseIdx, nullptr);
    EXPECT_EQ(pool->getPool(baseIdx), nullptr);
    
    // Set to nullptr again (since we can't easily create TextWord)
    pool->setPool(baseIdx, nullptr);
    EXPECT_EQ(pool->getPool(baseIdx), nullptr);
}

// Test destruction of pool with established indices doesn't crash
TEST_F(TextPoolTest_1200, DestructionAfterUseDoesNotCrash_1200) {
    auto localPool = std::make_unique<TextPool>();
    localPool->getBaseIdx(10.0);
    localPool->getBaseIdx(50.0);
    localPool->getBaseIdx(100.0);
    EXPECT_NO_FATAL_FAILURE(localPool.reset());
}

// Test boundary: very small positive base
TEST_F(TextPoolTest_1200, GetBaseIdxVerySmallPositive_1200) {
    int idx = pool->getBaseIdx(0.001);
    int idx_zero = pool->getBaseIdx(0.0);
    // Very small value might map to same index as 0
    (void)idx;
    (void)idx_zero;
}

// Test boundary: fractional bases
TEST_F(TextPoolTest_1200, GetBaseIdxFractionalValues_1200) {
    int idx1 = pool->getBaseIdx(10.3);
    int idx2 = pool->getBaseIdx(10.7);
    // These might map to the same index depending on rounding
    // Just verify they don't crash
    (void)idx1;
    (void)idx2;
}
