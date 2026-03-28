#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <stdexcept>
#include <string>

// We need to provide minimal infrastructure to test ChunkGenerator.
// Since we're testing against the Catch2 amalgamated header, we include it.
// However, we need to work within the Catch2 Generators framework.

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Generators;

// Helper: Create a generator from a fixed set of values
template <typename T>
GeneratorWrapper<T> makeFixedGenerator(std::initializer_list<T> values) {
    return from_range(std::vector<T>(values));
}

// Test fixture
class ChunkGeneratorTest_1110 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: ChunkGenerator with a normal chunk size that divides evenly
TEST_F(ChunkGeneratorTest_1110, NormalChunkEvenlyDivisible_1110) {
    auto gen = chunk(2, values<int>({1, 2, 3, 4}));
    
    // First chunk should be {1, 2}
    auto first = gen.get();
    ASSERT_EQ(first.size(), 2u);
    EXPECT_EQ(first[0], 1);
    EXPECT_EQ(first[1], 2);
    
    // Move to next chunk
    ASSERT_TRUE(gen.next());
    auto second = gen.get();
    ASSERT_EQ(second.size(), 2u);
    EXPECT_EQ(second[0], 3);
    EXPECT_EQ(second[1], 4);
    
    // No more chunks
    EXPECT_FALSE(gen.next());
}

// Test: ChunkGenerator with chunk size of 1
TEST_F(ChunkGeneratorTest_1110, ChunkSizeOne_1110) {
    auto gen = chunk(1, values<int>({10, 20, 30}));
    
    auto first = gen.get();
    ASSERT_EQ(first.size(), 1u);
    EXPECT_EQ(first[0], 10);
    
    ASSERT_TRUE(gen.next());
    auto second = gen.get();
    ASSERT_EQ(second.size(), 1u);
    EXPECT_EQ(second[0], 20);
    
    ASSERT_TRUE(gen.next());
    auto third = gen.get();
    ASSERT_EQ(third.size(), 1u);
    EXPECT_EQ(third[0], 30);
    
    EXPECT_FALSE(gen.next());
}

// Test: ChunkGenerator where values don't divide evenly - last chunk is smaller
TEST_F(ChunkGeneratorTest_1110, LastChunkSmallerThanSize_1110) {
    auto gen = chunk(3, values<int>({1, 2, 3, 4, 5}));
    
    auto first = gen.get();
    ASSERT_EQ(first.size(), 3u);
    EXPECT_EQ(first[0], 1);
    EXPECT_EQ(first[1], 2);
    EXPECT_EQ(first[2], 3);
    
    ASSERT_TRUE(gen.next());
    auto second = gen.get();
    // Second chunk should have remaining 2 elements
    ASSERT_EQ(second.size(), 2u);
    EXPECT_EQ(second[0], 4);
    EXPECT_EQ(second[1], 5);
    
    EXPECT_FALSE(gen.next());
}

// Test: ChunkGenerator with chunk size 0
TEST_F(ChunkGeneratorTest_1110, ChunkSizeZero_1110) {
    auto gen = chunk(0, values<int>({1, 2, 3}));
    
    // With chunk_size 0, the initial chunk should be empty
    auto first = gen.get();
    EXPECT_EQ(first.size(), 0u);
}

// Test: ChunkGenerator with exact number of values for one chunk
TEST_F(ChunkGeneratorTest_1110, ExactlyOneChunk_1110) {
    auto gen = chunk(3, values<int>({1, 2, 3}));
    
    auto first = gen.get();
    ASSERT_EQ(first.size(), 3u);
    EXPECT_EQ(first[0], 1);
    EXPECT_EQ(first[1], 2);
    EXPECT_EQ(first[2], 3);
    
    EXPECT_FALSE(gen.next());
}

// Test: ChunkGenerator with string type
TEST_F(ChunkGeneratorTest_1110, StringType_1110) {
    auto gen = chunk(2, values<std::string>({"hello", "world", "foo", "bar"}));
    
    auto first = gen.get();
    ASSERT_EQ(first.size(), 2u);
    EXPECT_EQ(first[0], "hello");
    EXPECT_EQ(first[1], "world");
    
    ASSERT_TRUE(gen.next());
    auto second = gen.get();
    ASSERT_EQ(second.size(), 2u);
    EXPECT_EQ(second[0], "foo");
    EXPECT_EQ(second[1], "bar");
    
    EXPECT_FALSE(gen.next());
}

// Test: ChunkGenerator - get() returns const reference and is stable before next()
TEST_F(ChunkGeneratorTest_1110, GetReturnsConsistentValue_1110) {
    auto gen = chunk(2, values<int>({1, 2, 3, 4}));
    
    const auto& first_call = gen.get();
    const auto& second_call = gen.get();
    
    // Both calls should return the same data
    EXPECT_EQ(first_call, second_call);
    ASSERT_EQ(first_call.size(), 2u);
    EXPECT_EQ(first_call[0], 1);
    EXPECT_EQ(first_call[1], 2);
}

// Test: ChunkGenerator throws when not enough values for first chunk
TEST_F(ChunkGeneratorTest_1110, NotEnoughValuesForFirstChunk_1110) {
    // Only 2 values but requesting chunk of 5
    EXPECT_THROW(
        chunk(5, values<int>({1, 2})),
        Catch::GeneratorException
    );
}

// Test: ChunkGenerator with single value and chunk size 1
TEST_F(ChunkGeneratorTest_1110, SingleValueSingleChunk_1110) {
    auto gen = chunk(1, values<int>({42}));
    
    auto first = gen.get();
    ASSERT_EQ(first.size(), 1u);
    EXPECT_EQ(first[0], 42);
    
    EXPECT_FALSE(gen.next());
}

// Test: ChunkGenerator with large chunk size equal to total values
TEST_F(ChunkGeneratorTest_1110, ChunkSizeEqualsTotal_1110) {
    auto gen = chunk(5, values<int>({1, 2, 3, 4, 5}));
    
    auto first = gen.get();
    ASSERT_EQ(first.size(), 5u);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(first[i], i + 1);
    }
    
    EXPECT_FALSE(gen.next());
}

// Test: ChunkGenerator with double type
TEST_F(ChunkGeneratorTest_1110, DoubleType_1110) {
    auto gen = chunk(2, values<double>({1.1, 2.2, 3.3, 4.4}));
    
    auto first = gen.get();
    ASSERT_EQ(first.size(), 2u);
    EXPECT_DOUBLE_EQ(first[0], 1.1);
    EXPECT_DOUBLE_EQ(first[1], 2.2);
    
    ASSERT_TRUE(gen.next());
    auto second = gen.get();
    ASSERT_EQ(second.size(), 2u);
    EXPECT_DOUBLE_EQ(second[0], 3.3);
    EXPECT_DOUBLE_EQ(second[1], 4.4);
}

// Test: Multiple next() calls after exhaustion
TEST_F(ChunkGeneratorTest_1110, MultipleNextAfterExhaustion_1110) {
    auto gen = chunk(2, values<int>({1, 2}));
    
    auto first = gen.get();
    ASSERT_EQ(first.size(), 2u);
    
    EXPECT_FALSE(gen.next());
    // Calling next again after exhaustion
    EXPECT_FALSE(gen.next());
}

// Test: ChunkGenerator with chunk size 3 and 7 values (3+3+1)
TEST_F(ChunkGeneratorTest_1110, ThreeChunksWithRemainder_1110) {
    auto gen = chunk(3, values<int>({1, 2, 3, 4, 5, 6, 7}));
    
    auto first = gen.get();
    ASSERT_EQ(first.size(), 3u);
    EXPECT_EQ(first[0], 1);
    EXPECT_EQ(first[1], 2);
    EXPECT_EQ(first[2], 3);
    
    ASSERT_TRUE(gen.next());
    auto second = gen.get();
    ASSERT_EQ(second.size(), 3u);
    EXPECT_EQ(second[0], 4);
    EXPECT_EQ(second[1], 5);
    EXPECT_EQ(second[2], 6);
    
    ASSERT_TRUE(gen.next());
    auto third = gen.get();
    ASSERT_EQ(third.size(), 1u);
    EXPECT_EQ(third[0], 7);
    
    EXPECT_FALSE(gen.next());
}
