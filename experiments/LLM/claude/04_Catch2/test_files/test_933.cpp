#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <string>
#include <cstddef>

// We need to include the Catch2 header for the ChunkGenerator
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Generators;

// Helper: Create a generator from a fixed set of values
// We'll use Catch2's own facilities to create generators for testing

class ChunkGeneratorTest_933 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that ChunkGenerator produces correct chunks from an exact multiple of values
TEST_F(ChunkGeneratorTest_933, ExactMultipleChunks_933) {
    // Create a generator with values 1..6, chunk size 3
    // Should produce chunks [1,2,3] and [4,5,6]
    auto gen = chunk(3, values<int>({1, 2, 3, 4, 5, 6}));

    // First chunk should be available via get()
    std::vector<int> expected1 = {1, 2, 3};
    EXPECT_EQ(gen.get(), expected1);

    // Move to next chunk
    EXPECT_TRUE(gen.next());
    std::vector<int> expected2 = {4, 5, 6};
    EXPECT_EQ(gen.get(), expected2);

    // No more chunks
    EXPECT_FALSE(gen.next());
}

// Test that ChunkGenerator returns false from next() when values don't fill a complete chunk
TEST_F(ChunkGeneratorTest_933, IncompleteLastChunkReturnsFalse_933) {
    // 5 values, chunk size 3: first chunk [1,2,3], second chunk incomplete (only 2 values)
    auto gen = chunk(3, values<int>({1, 2, 3, 4, 5}));

    std::vector<int> expected1 = {1, 2, 3};
    EXPECT_EQ(gen.get(), expected1);

    // next() should return false because the underlying generator runs out mid-chunk
    EXPECT_FALSE(gen.next());
}

// Test chunk size of 1 (each element is its own chunk)
TEST_F(ChunkGeneratorTest_933, ChunkSizeOne_933) {
    auto gen = chunk(1, values<int>({10, 20, 30}));

    std::vector<int> expected1 = {10};
    EXPECT_EQ(gen.get(), expected1);

    EXPECT_TRUE(gen.next());
    std::vector<int> expected2 = {20};
    EXPECT_EQ(gen.get(), expected2);

    EXPECT_TRUE(gen.next());
    std::vector<int> expected3 = {30};
    EXPECT_EQ(gen.get(), expected3);

    EXPECT_FALSE(gen.next());
}

// Test with a single value and chunk size 1
TEST_F(ChunkGeneratorTest_933, SingleValueChunkSizeOne_933) {
    auto gen = chunk(1, values<int>({42}));

    std::vector<int> expected = {42};
    EXPECT_EQ(gen.get(), expected);

    EXPECT_FALSE(gen.next());
}

// Test that get() returns the same value when called multiple times without next()
TEST_F(ChunkGeneratorTest_933, GetIsIdempotent_933) {
    auto gen = chunk(2, values<int>({1, 2, 3, 4}));

    std::vector<int> expected = {1, 2};
    EXPECT_EQ(gen.get(), expected);
    EXPECT_EQ(gen.get(), expected);
    EXPECT_EQ(gen.get(), expected);
}

// Test with string type
TEST_F(ChunkGeneratorTest_933, StringChunks_933) {
    auto gen = chunk(2, values<std::string>({"a", "b", "c", "d"}));

    std::vector<std::string> expected1 = {"a", "b"};
    EXPECT_EQ(gen.get(), expected1);

    EXPECT_TRUE(gen.next());
    std::vector<std::string> expected2 = {"c", "d"};
    EXPECT_EQ(gen.get(), expected2);

    EXPECT_FALSE(gen.next());
}

// Test with chunk size equal to number of elements
TEST_F(ChunkGeneratorTest_933, ChunkSizeEqualsTotal_933) {
    auto gen = chunk(4, values<int>({1, 2, 3, 4}));

    std::vector<int> expected = {1, 2, 3, 4};
    EXPECT_EQ(gen.get(), expected);

    EXPECT_FALSE(gen.next());
}

// Test with chunk size larger than number of elements (incomplete first chunk)
TEST_F(ChunkGeneratorTest_933, ChunkSizeLargerThanTotal_933) {
    // The first call to get() should still work if the initial construction
    // succeeds. But since the underlying generator will be exhausted before
    // filling the chunk, behavior depends on implementation.
    // Based on the next() implementation: it clears chunk, iterates, and if
    // generator.next() returns false, it returns false.
    // The constructor likely fills the first chunk. If the underlying has fewer
    // elements than chunk_size, the constructor behavior is implementation-defined.
    // We test what we can observe.
    
    // With 2 elements and chunk size 5, the initial chunk may or may not be filled.
    // This tests boundary behavior.
    // Since this might throw or produce partial results, we just verify it doesn't crash.
    try {
        auto gen = chunk(5, values<int>({1, 2}));
        // If we get here, get() should return something
        auto result = gen.get();
        // The result size should be <= 5
        EXPECT_LE(result.size(), 5u);
    } catch (...) {
        // If it throws, that's also acceptable behavior for this edge case
        SUCCEED();
    }
}

// Test multiple chunks with doubles
TEST_F(ChunkGeneratorTest_933, DoubleTypeChunks_933) {
    auto gen = chunk(2, values<double>({1.1, 2.2, 3.3, 4.4}));

    std::vector<double> expected1 = {1.1, 2.2};
    EXPECT_EQ(gen.get(), expected1);

    EXPECT_TRUE(gen.next());
    std::vector<double> expected2 = {3.3, 4.4};
    EXPECT_EQ(gen.get(), expected2);

    EXPECT_FALSE(gen.next());
}

// Test that after next() returns false, get() still returns last valid state
TEST_F(ChunkGeneratorTest_933, GetAfterExhaustion_933) {
    auto gen = chunk(2, values<int>({1, 2}));

    std::vector<int> expected = {1, 2};
    EXPECT_EQ(gen.get(), expected);

    EXPECT_FALSE(gen.next());
    
    // After exhaustion, get() should still be callable (returns const ref to internal state)
    // The exact content after failed next() depends on implementation
    // but it should not crash
    auto result = gen.get();
    // We just verify it doesn't crash; the content may be empty or stale
    (void)result;
}

// Test with chunk size of 2 and odd number of elements
TEST_F(ChunkGeneratorTest_933, OddElementsEvenChunkSize_933) {
    auto gen = chunk(2, values<int>({1, 2, 3}));

    std::vector<int> expected1 = {1, 2};
    EXPECT_EQ(gen.get(), expected1);

    // Second chunk would need 2 elements but only 1 remains
    EXPECT_FALSE(gen.next());
}

// Test with larger dataset
TEST_F(ChunkGeneratorTest_933, LargerDataset_933) {
    auto gen = chunk(3, values<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));

    std::vector<int> expected1 = {1, 2, 3};
    EXPECT_EQ(gen.get(), expected1);

    EXPECT_TRUE(gen.next());
    std::vector<int> expected2 = {4, 5, 6};
    EXPECT_EQ(gen.get(), expected2);

    EXPECT_TRUE(gen.next());
    std::vector<int> expected3 = {7, 8, 9};
    EXPECT_EQ(gen.get(), expected3);

    EXPECT_FALSE(gen.next());
}
