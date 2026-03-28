// File: tests/chunk_generator_932_tests.cpp
#include <gtest/gtest.h>

#include "Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Generators;

namespace {

// Simple stub generator that yields items from a fixed vector.
// It implements the public IGenerator<T> interface and has no knowledge
// of ChunkGenerator internals.
template <typename T>
class VectorGenerator final : public IGenerator<T> {
public:
    explicit VectorGenerator(std::vector<T> values)
        : values_(std::move(values)) {
        if (!values_.empty()) {
            idx_ = 0;
        }
    }

    T const& get() const override {
        // Precondition for Catch2 generators: caller should not call get()
        // unless construction succeeded and/or next() previously returned true.
        return values_.at(idx_);
    }

    bool next() override {
        if (values_.empty()) return false;
        if (idx_ + 1 < values_.size()) {
            ++idx_;
            return true;
        }
        return false;
    }

private:
    std::vector<T> values_;
    size_t idx_ = 0; // valid only if !values_.empty()
};

// Helper to make a GeneratorWrapper<T> from a unique_ptr<IGenerator<T>>
template <typename T>
GeneratorWrapper<T> makeWrapper(std::unique_ptr<IGenerator<T>> gen) {
    return GeneratorWrapper<T>(std::move(gen));
}

} // namespace

class ChunkGeneratorTest_932 : public ::testing::Test {};

// Normal operation: chunks of fixed size, with a final partial chunk.
TEST_F(ChunkGeneratorTest_932, YieldsFixedSizeChunksAndFinalPartial_932) {
    auto base = std::make_unique<VectorGenerator<int>>(std::vector<int>{1,2,3,4,5});
    ChunkGenerator<int> cg(/*size=*/2, makeWrapper<int>(std::move(base)));

    // 1st chunk
    ASSERT_TRUE(cg.next());               // prepare first chunk
    const auto& c1 = cg.get();
    ASSERT_EQ(c1.size(), 2u);
    EXPECT_EQ(c1[0], 1);
    EXPECT_EQ(c1[1], 2);

    // 2nd chunk
    ASSERT_TRUE(cg.next());
    const auto& c2 = cg.get();
    ASSERT_EQ(c2.size(), 2u);
    EXPECT_EQ(c2[0], 3);
    EXPECT_EQ(c2[1], 4);

    // 3rd (final, partial) chunk
    ASSERT_TRUE(cg.next());
    const auto& c3 = cg.get();
    ASSERT_EQ(c3.size(), 1u);
    EXPECT_EQ(c3[0], 5);

    // No more chunks
    EXPECT_FALSE(cg.next());
}

// Boundary: chunk size == 1 behaves like element-by-element iteration.
TEST_F(ChunkGeneratorTest_932, ChunkSizeOneProducesSingleElementChunks_932) {
    auto base = std::make_unique<VectorGenerator<int>>(std::vector<int>{10,20,30});
    ChunkGenerator<int> cg(/*size=*/1, makeWrapper<int>(std::move(base)));

    ASSERT_TRUE(cg.next());
    const auto& a = cg.get();
    ASSERT_EQ(a.size(), 1u);
    EXPECT_EQ(a[0], 10);

    ASSERT_TRUE(cg.next());
    const auto& b = cg.get();
    ASSERT_EQ(b.size(), 1u);
    EXPECT_EQ(b[0], 20);

    ASSERT_TRUE(cg.next());
    const auto& c = cg.get();
    ASSERT_EQ(c.size(), 1u);
    EXPECT_EQ(c[0], 30);

    EXPECT_FALSE(cg.next());
}

// Boundary: chunk size larger than the number of available elements.
TEST_F(ChunkGeneratorTest_932, ChunkSizeLargerThanInputYieldsSingleFinalChunk_932) {
    auto base = std::make_unique<VectorGenerator<int>>(std::vector<int>{7,8,9});
    ChunkGenerator<int> cg(/*size=*/10, makeWrapper<int>(std::move(base)));

    ASSERT_TRUE(cg.next());
    const auto& only = cg.get();
    ASSERT_EQ(only.size(), 3u);
    EXPECT_EQ(only[0], 7);
    EXPECT_EQ(only[1], 8);
    EXPECT_EQ(only[2], 9);

    EXPECT_FALSE(cg.next());
}

// Boundary: empty upstream generator -> no chunks available.
TEST_F(ChunkGeneratorTest_932, EmptyUpstreamProducesNoChunks_932) {
    auto base = std::make_unique<VectorGenerator<int>>(std::vector<int>{});
    ChunkGenerator<int> cg(/*size=*/3, makeWrapper<int>(std::move(base)));

    // No data to form a chunk
    EXPECT_FALSE(cg.next());
}

// Stability: get() returns a reference; repeated get() without next() returns the same data.
TEST_F(ChunkGeneratorTest_932, GetReturnsStableReferenceUntilNext_932) {
    auto base = std::make_unique<VectorGenerator<int>>(std::vector<int>{1,2,3,4});
    ChunkGenerator<int> cg(/*size=*/2, makeWrapper<int>(std::move(base)));

    ASSERT_TRUE(cg.next());
    auto const* ref1 = &cg.get();
    auto const* ref2 = &cg.get();
    // Same reference before calling next()
    EXPECT_EQ(ref1, ref2);

    ASSERT_TRUE(cg.next());
    auto const* ref3 = &cg.get();
    // After next(), the reference can (and likely will) refer to a different chunk
    // We only assert that the content is different as observable behavior.
    const auto& c = *ref3;
    ASSERT_EQ(c.size(), 2u);
    EXPECT_EQ(c[0], 3);
    EXPECT_EQ(c[1], 4);
}

// Exceptional case: constructing with chunk size 0 should fail in a user-observable way.
// Catch2 throws Catch::GeneratorException for invalid generator parameters.
TEST_F(ChunkGeneratorTest_932, ConstructWithZeroSizeThrows_932) {
    auto base = std::make_unique<VectorGenerator<int>>(std::vector<int>{1,2,3});
    EXPECT_THROW(
        (ChunkGenerator<int>(/*size=*/0, makeWrapper<int>(std::move(base)))),
        Catch::GeneratorException
    );
}
