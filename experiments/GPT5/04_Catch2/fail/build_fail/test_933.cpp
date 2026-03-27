// File: tests/chunk_generator_tests_933.cpp
#include <gtest/gtest.h>
#include "Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Generators;

// A minimal external collaborator used by the tests.
// Provides a fixed sequence of T and exposes call counters
// so we can verify interactions (how many times next()/get() were called).
template <typename T>
class CountingVectorGen : public IGenerator<T> {
public:
    explicit CountingVectorGen(std::vector<T> data)
        : data_(std::move(data)), idx_(-1) {}

    // Observable collaborator state for interaction verification
    int next_calls = 0;
    int get_calls  = 0;

    const T& get() const override {
        ++const_cast<CountingVectorGen*>(this)->get_calls;
        // Precondition in Catch2: get() is only queried when not used up.
        // We do not test invalid usage; return current element.
        return data_.at(static_cast<size_t>(idx_));
    }

    bool next() override {
        ++next_calls;
        if (static_cast<size_t>(idx_ + 1) < data_.size()) {
            ++idx_;
            return true;
        }
        return false;
    }

private:
    std::vector<T> data_;
    int idx_;
};

class ChunkGeneratorTest_933 : public ::testing::Test {
protected:
    // Helper to build a ChunkGenerator<T> over a CountingVectorGen<T>.
    template <typename T>
    static ChunkGenerator<T> makeChunkGen(
        size_t chunkSize,
        std::unique_ptr<CountingVectorGen<T>> src,
        CountingVectorGen<T>** outRaw = nullptr
    ) {
        if (outRaw) *outRaw = src.get();
        GeneratorWrapper<T> wrapper{ std::unique_ptr<IGenerator<T>>(std::move(src)) };
        return ChunkGenerator<T>(chunkSize, CATCH_MOVE(wrapper));
    }
};

// Normal operation: exact multiple of chunk size => all full chunks emitted, then false.
TEST_F(ChunkGeneratorTest_933, ProducesFullChunksOnExactMultiple_933) {
    auto* raw = static_cast<CountingVectorGen<int>*>(nullptr);
    auto gen = makeChunkGen<int>(
        /*chunkSize*/ 2,
        std::make_unique<CountingVectorGen<int>>(std::vector<int>{1,2,3,4,5,6}),
        &raw
    );

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), (std::vector<int>{1,2}));

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), (std::vector<int>{3,4}));

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), (std::vector<int>{5,6}));

    EXPECT_FALSE(gen.next()); // no more full chunks
    // No assumptions about get() after false.
}

// Boundary: not enough for last chunk => final next() returns false, no partial chunk is exposed.
TEST_F(ChunkGeneratorTest_933, StopsBeforePartialChunk_933) {
    auto gen = makeChunkGen<int>(
        /*chunkSize*/ 2,
        std::make_unique<CountingVectorGen<int>>(std::vector<int>{10,20,30,40,50})
    );

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), (std::vector<int>{10,20}));

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), (std::vector<int>{30,40}));

    // Only one element (50) remains; cannot form a full chunk of size 2.
    EXPECT_FALSE(gen.next());
}

// Boundary: chunk size 1 => each call yields a single-element chunk.
TEST_F(ChunkGeneratorTest_933, ChunkSizeOneYieldsSingles_933) {
    auto gen = makeChunkGen<int>(
        /*chunkSize*/ 1,
        std::make_unique<CountingVectorGen<int>>(std::vector<int>{7,8,9})
    );

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), (std::vector<int>{7}));

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), (std::vector<int>{8}));

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), (std::vector<int>{9}));

    EXPECT_FALSE(gen.next());
}

// Exceptional/edge: empty underlying sequence => first next() is false.
TEST_F(ChunkGeneratorTest_933, EmptyUnderlyingSequenceFailsImmediately_933) {
    auto gen = makeChunkGen<int>(
        /*chunkSize*/ 3,
        std::make_unique<CountingVectorGen<int>>(std::vector<int>{})
    );
    EXPECT_FALSE(gen.next());
}

// Boundary: chunk size larger than available elements => first next() is false.
TEST_F(ChunkGeneratorTest_933, ChunkSizeExceedsAvailableElements_933) {
    auto gen = makeChunkGen<int>(
        /*chunkSize*/ 3,
        std::make_unique<CountingVectorGen<int>>(std::vector<int>{1,2})
    );
    EXPECT_FALSE(gen.next());
}

// Verification of external interactions: underlying generator's next()/get() usage.
TEST_F(ChunkGeneratorTest_933, VerifiesUnderlyingCallsPerSuccessfulChunk_933) {
    CountingVectorGen<int>* raw = nullptr;
    auto gen = makeChunkGen<int>(
        /*chunkSize*/ 2,
        std::make_unique<CountingVectorGen<int>>(std::vector<int>{1,2,3,4}),
        &raw
    );
    ASSERT_NE(raw, nullptr);

    // 1st successful chunk should call next() twice and get() twice
    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), (std::vector<int>{1,2}));
    EXPECT_EQ(raw->next_calls, 2);
    EXPECT_EQ(raw->get_calls,  2);

    // 2nd successful chunk: cumulative next()==4, get()==4
    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), (std::vector<int>{3,4}));
    EXPECT_EQ(raw->next_calls, 4);
    EXPECT_EQ(raw->get_calls,  4);

    // Further attempt should fail; one more next() attempt performed internally
    EXPECT_FALSE(gen.next());
    EXPECT_EQ(raw->next_calls, 5); // one extra attempt that failed
    EXPECT_EQ(raw->get_calls,  4); // no additional get() on failure
}
