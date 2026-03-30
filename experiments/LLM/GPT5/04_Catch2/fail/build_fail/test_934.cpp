// File: tests/chunk_generator_tests_934.cpp

#include <gtest/gtest.h>
#include "Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Generators;

class ChunkGeneratorTest_934 : public ::testing::Test {
protected:
    template <typename T>
    static std::vector<std::vector<T>> CollectAll(GeneratorWrapper<std::vector<T>>& gen) {
        std::vector<std::vector<T>> out;
        // According to Catch2 generator semantics, after construction `get()` returns
        // the first element; `next()` advances and returns false when exhausted.
        out.push_back(gen.get());
        while (gen.next()) {
            out.push_back(gen.get());
        }
        return out;
    }
};

// Normal operation: elements are grouped in-order into chunks of given size.
// 5 items, chunk size 2 => {{1,2}, {3,4}, {5}}
TEST_F(ChunkGeneratorTest_934, GroupsInOrder_WithRemainder_934) {
    auto gen = chunk(2, values({1, 2, 3, 4, 5}));
    auto chunks = CollectAll(gen);

    ASSERT_EQ(chunks.size(), 3u);
    EXPECT_EQ(chunks[0], (std::vector<int>{1, 2}));
    EXPECT_EQ(chunks[1], (std::vector<int>{3, 4}));
    EXPECT_EQ(chunks[2], (std::vector<int>{5}));
}

// Boundary: exact multiple of chunk size.
// 6 items, chunk size 3 => {{1,2,3}, {4,5,6}}
TEST_F(ChunkGeneratorTest_934, ExactMultiple_SizeThree_934) {
    auto gen = chunk(3, values({1, 2, 3, 4, 5, 6}));
    auto chunks = CollectAll(gen);

    ASSERT_EQ(chunks.size(), 2u);
    EXPECT_EQ(chunks[0], (std::vector<int>{1, 2, 3}));
    EXPECT_EQ(chunks[1], (std::vector<int>{4, 5, 6}));
}

// Boundary: chunk size of 1 yields single-element vectors.
// 3 items, chunk size 1 => {{1}, {2}, {3}}
TEST_F(ChunkGeneratorTest_934, ChunkSizeOne_Singles_934) {
    auto gen = chunk(1, values({1, 2, 3}));
    auto chunks = CollectAll(gen);

    ASSERT_EQ(chunks.size(), 3u);
    EXPECT_EQ(chunks[0], (std::vector<int>{1}));
    EXPECT_EQ(chunks[1], (std::vector<int>{2}));
    EXPECT_EQ(chunks[2], (std::vector<int>{3}));
}

// Boundary: fewer underlying elements than the chunk size still yields a single, smaller chunk.
// take(1) over 3 values, chunk size 5 => {{1}}
TEST_F(ChunkGeneratorTest_934, UnderlyingShorterThanChunk_YieldsPartial_934) {
    auto gen = chunk(5, take(1, values({1, 2, 3})));
    auto chunks = CollectAll(gen);

    ASSERT_EQ(chunks.size(), 1u);
    EXPECT_EQ(chunks[0], (std::vector<int>{1}));
}

// Exceptional/error case: chunk size 0 is invalid and should throw when creating/using the generator.
TEST_F(ChunkGeneratorTest_934, ZeroChunkSize_Throws_934) {
    // Construction of the chunk generator with size 0 should fail observably.
    EXPECT_THROW(
        {
            // Wrap in its own scope to ensure temporary handling is clear.
            auto bad = chunk(0, values({1, 2, 3}));
            // Some Catch2 versions may throw on first access; this line ensures we
            // trigger any deferred validation without asserting internal details.
            (void)bad.get();
        },
        Catch::Generators::GeneratorException
    );
}
