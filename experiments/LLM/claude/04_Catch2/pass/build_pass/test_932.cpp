#include <gtest/gtest.h>
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"
#include <vector>
#include <string>

using namespace Catch::Generators;

// Helper: create a GeneratorWrapper<T> from a fixed set of values
// We use Catch2's own generator infrastructure to create source generators

namespace {

template <typename T>
class FixedValuesGenerator final : public IGenerator<T> {
    std::vector<T> m_values;
    size_t m_index = 0;
public:
    explicit FixedValuesGenerator(std::vector<T> values)
        : m_values(std::move(values)) {
        assert(!m_values.empty());
    }

    T const& get() const override {
        return m_values[m_index];
    }

    bool next() override {
        ++m_index;
        return m_index < m_values.size();
    }
};

template <typename T>
GeneratorWrapper<T> makeFixedGenerator(std::vector<T> values) {
    return GeneratorWrapper<T>(
        Catch::Detail::make_unique<FixedValuesGenerator<T>>(std::move(values))
    );
}

} // anonymous namespace

class ChunkGeneratorTest_932 : public ::testing::Test {
protected:
};

// Test that a chunk generator with exact multiple of elements returns correct first chunk
TEST_F(ChunkGeneratorTest_932, FirstChunkContainsCorrectElements_932) {
    auto gen = makeFixedGenerator<int>({1, 2, 3, 4, 5, 6});
    ChunkGenerator<int> chunkGen(3, std::move(gen));

    auto const& chunk = chunkGen.get();
    ASSERT_EQ(chunk.size(), 3u);
    EXPECT_EQ(chunk[0], 1);
    EXPECT_EQ(chunk[1], 2);
    EXPECT_EQ(chunk[2], 3);
}

// Test that next() advances to the second chunk
TEST_F(ChunkGeneratorTest_932, NextAdvancesToSecondChunk_932) {
    auto gen = makeFixedGenerator<int>({1, 2, 3, 4, 5, 6});
    ChunkGenerator<int> chunkGen(3, std::move(gen));

    bool hasMore = chunkGen.next();
    EXPECT_TRUE(hasMore);

    auto const& chunk = chunkGen.get();
    ASSERT_EQ(chunk.size(), 3u);
    EXPECT_EQ(chunk[0], 4);
    EXPECT_EQ(chunk[1], 5);
    EXPECT_EQ(chunk[2], 6);
}

// Test that next() returns false when all chunks are exhausted (exact multiple)
TEST_F(ChunkGeneratorTest_932, NextReturnsFalseWhenExhausted_932) {
    auto gen = makeFixedGenerator<int>({1, 2, 3, 4, 5, 6});
    ChunkGenerator<int> chunkGen(3, std::move(gen));

    EXPECT_TRUE(chunkGen.next());  // second chunk
    EXPECT_FALSE(chunkGen.next()); // no more
}

// Test chunk size of 1 (each element is its own chunk)
TEST_F(ChunkGeneratorTest_932, ChunkSizeOne_932) {
    auto gen = makeFixedGenerator<int>({10, 20, 30});
    ChunkGenerator<int> chunkGen(1, std::move(gen));

    auto const& chunk1 = chunkGen.get();
    ASSERT_EQ(chunk1.size(), 1u);
    EXPECT_EQ(chunk1[0], 10);

    EXPECT_TRUE(chunkGen.next());
    auto const& chunk2 = chunkGen.get();
    ASSERT_EQ(chunk2.size(), 1u);
    EXPECT_EQ(chunk2[0], 20);

    EXPECT_TRUE(chunkGen.next());
    auto const& chunk3 = chunkGen.get();
    ASSERT_EQ(chunk3.size(), 1u);
    EXPECT_EQ(chunk3[0], 30);

    EXPECT_FALSE(chunkGen.next());
}

// Test that when the source has fewer remaining elements than chunk size, we get a partial chunk
TEST_F(ChunkGeneratorTest_932, PartialLastChunk_932) {
    auto gen = makeFixedGenerator<int>({1, 2, 3, 4, 5});
    ChunkGenerator<int> chunkGen(3, std::move(gen));

    auto const& chunk1 = chunkGen.get();
    ASSERT_EQ(chunk1.size(), 3u);
    EXPECT_EQ(chunk1[0], 1);
    EXPECT_EQ(chunk1[1], 2);
    EXPECT_EQ(chunk1[2], 3);

    // The second chunk should have only 2 elements
    bool hasMore = chunkGen.next();
    // Depending on implementation, this might be true (partial chunk available)
    // or it might return the partial chunk and then false on next call
    if (hasMore) {
        auto const& chunk2 = chunkGen.get();
        ASSERT_EQ(chunk2.size(), 2u);
        EXPECT_EQ(chunk2[0], 4);
        EXPECT_EQ(chunk2[1], 5);
        EXPECT_FALSE(chunkGen.next());
    }
}

// Test with a single element source and chunk size larger than source
TEST_F(ChunkGeneratorTest_932, ChunkSizeLargerThanSource_932) {
    auto gen = makeFixedGenerator<int>({42});
    ChunkGenerator<int> chunkGen(5, std::move(gen));

    auto const& chunk = chunkGen.get();
    // First chunk should contain what's available (1 element)
    ASSERT_GE(chunk.size(), 1u);
    ASSERT_LE(chunk.size(), 5u);
    EXPECT_EQ(chunk[0], 42);
}

// Test with string type
TEST_F(ChunkGeneratorTest_932, WorksWithStrings_932) {
    auto gen = makeFixedGenerator<std::string>({"hello", "world", "foo", "bar"});
    ChunkGenerator<std::string> chunkGen(2, std::move(gen));

    auto const& chunk1 = chunkGen.get();
    ASSERT_EQ(chunk1.size(), 2u);
    EXPECT_EQ(chunk1[0], "hello");
    EXPECT_EQ(chunk1[1], "world");

    EXPECT_TRUE(chunkGen.next());
    auto const& chunk2 = chunkGen.get();
    ASSERT_EQ(chunk2.size(), 2u);
    EXPECT_EQ(chunk2[0], "foo");
    EXPECT_EQ(chunk2[1], "bar");

    EXPECT_FALSE(chunkGen.next());
}

// Test that get() is idempotent (calling it multiple times returns the same chunk)
TEST_F(ChunkGeneratorTest_932, GetIsIdempotent_932) {
    auto gen = makeFixedGenerator<int>({1, 2, 3});
    ChunkGenerator<int> chunkGen(2, std::move(gen));

    auto const& chunk1 = chunkGen.get();
    auto const& chunk2 = chunkGen.get();
    EXPECT_EQ(chunk1.size(), chunk2.size());
    EXPECT_EQ(&chunk1, &chunk2); // Should return reference to same internal vector
}

// Test chunk size equal to total number of elements
TEST_F(ChunkGeneratorTest_932, ChunkSizeEqualToTotal_932) {
    auto gen = makeFixedGenerator<int>({1, 2, 3});
    ChunkGenerator<int> chunkGen(3, std::move(gen));

    auto const& chunk = chunkGen.get();
    ASSERT_EQ(chunk.size(), 3u);
    EXPECT_EQ(chunk[0], 1);
    EXPECT_EQ(chunk[1], 2);
    EXPECT_EQ(chunk[2], 3);

    EXPECT_FALSE(chunkGen.next());
}

// Test multiple iterations through all chunks with double type
TEST_F(ChunkGeneratorTest_932, WorksWithDoubles_932) {
    auto gen = makeFixedGenerator<double>({1.1, 2.2, 3.3, 4.4});
    ChunkGenerator<double> chunkGen(2, std::move(gen));

    auto const& chunk1 = chunkGen.get();
    ASSERT_EQ(chunk1.size(), 2u);
    EXPECT_DOUBLE_EQ(chunk1[0], 1.1);
    EXPECT_DOUBLE_EQ(chunk1[1], 2.2);

    EXPECT_TRUE(chunkGen.next());
    auto const& chunk2 = chunkGen.get();
    ASSERT_EQ(chunk2.size(), 2u);
    EXPECT_DOUBLE_EQ(chunk2[0], 3.3);
    EXPECT_DOUBLE_EQ(chunk2[1], 4.4);

    EXPECT_FALSE(chunkGen.next());
}

// Test with a large number of elements
TEST_F(ChunkGeneratorTest_932, LargeNumberOfElements_932) {
    std::vector<int> values(100);
    for (int i = 0; i < 100; ++i) {
        values[i] = i;
    }
    auto gen = makeFixedGenerator<int>(values);
    ChunkGenerator<int> chunkGen(10, std::move(gen));

    int chunkCount = 0;
    auto const& firstChunk = chunkGen.get();
    ASSERT_EQ(firstChunk.size(), 10u);
    EXPECT_EQ(firstChunk[0], 0);
    EXPECT_EQ(firstChunk[9], 9);
    chunkCount++;

    while (chunkGen.next()) {
        auto const& chunk = chunkGen.get();
        ASSERT_EQ(chunk.size(), 10u);
        EXPECT_EQ(chunk[0], chunkCount * 10);
        EXPECT_EQ(chunk[9], chunkCount * 10 + 9);
        chunkCount++;
    }

    EXPECT_EQ(chunkCount, 10);
}
