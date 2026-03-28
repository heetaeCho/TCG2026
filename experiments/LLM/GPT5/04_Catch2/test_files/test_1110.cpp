// File: tests/ChunkGeneratorTest_1110.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Catch2/extras/catch_amalgamated.hpp"

using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::StrictMock;

namespace Catch { namespace Generators {
// Minimal mock for the underlying generator collaborator.
template <typename T>
class MockIGenerator : public IGenerator<T> {
public:
    MOCK_METHOD(const T&, get, (), (const, override));
    MOCK_METHOD(bool, next, (), (override));
};
}} // namespace Catch::Generators

// Test fixture (kept simple for clarity)
class ChunkGeneratorTest_1110 : public ::testing::Test {};

//
// Normal operation: size > 0, enough values available to initialize the first chunk
//
TEST_F(ChunkGeneratorTest_1110, InitializesChunkWithProvidedValues_1110) {
    using namespace Catch::Generators;

    StrictMock<MockIGenerator<int>>* raw = nullptr;
    {
        // Use StrictMock to also validate call order and counts.
        auto mock = std::make_unique<StrictMock<MockIGenerator<int>>>();
        raw = mock.get();

        // Values to be returned by get() (must outlive calls)
        static int v1 = 10, v2 = 20, v3 = 30;

        InSequence seq;
        // According to observable ctor behavior: get() for first element,
        // then for each remaining element: next() then get()
        EXPECT_CALL(*raw, get()).WillOnce(ReturnRef(v1));
        EXPECT_CALL(*raw, next()).WillOnce(Return(true));
        EXPECT_CALL(*raw, get()).WillOnce(ReturnRef(v2));
        EXPECT_CALL(*raw, next()).WillOnce(Return(true));
        EXPECT_CALL(*raw, get()).WillOnce(ReturnRef(v3));

        GeneratorWrapper<int> wrapper(std::move(mock));
        ChunkGenerator<int> chunkGen(/*size*/3, std::move(wrapper));

        const auto& chunk = chunkGen.get(); // observable read
        ASSERT_EQ(chunk.size(), 3u);
        EXPECT_EQ(chunk[0], 10);
        EXPECT_EQ(chunk[1], 20);
        EXPECT_EQ(chunk[2], 30);
    }
}

//
// Boundary: size == 0 should not query the underlying generator at construction,
// and get() should return an empty vector.
//
TEST_F(ChunkGeneratorTest_1110, ZeroSizeYieldsEmptyChunkAndNoGeneratorCalls_1110) {
    using namespace Catch::Generators;

    auto mock = std::make_unique<StrictMock<MockIGenerator<int>>>();
    auto* raw = mock.get();

    // No interactions expected during construction for size == 0
    EXPECT_CALL(*raw, get()).Times(0);
    EXPECT_CALL(*raw, next()).Times(0);

    GeneratorWrapper<int> wrapper(std::move(mock));
    ChunkGenerator<int> chunkGen(/*size*/0, std::move(wrapper));

    const auto& chunk = chunkGen.get();
    EXPECT_TRUE(chunk.empty());
}

//
// Boundary: size == 1 should read exactly one value (get once) and never call next().
//
TEST_F(ChunkGeneratorTest_1110, SizeOneReadsSingleValueWithoutNext_1110) {
    using namespace Catch::Generators;

    auto mock = std::make_unique<StrictMock<MockIGenerator<int>>>();
    auto* raw = mock.get();

    static int v = 42;

    InSequence seq;
    EXPECT_CALL(*raw, get()).WillOnce(ReturnRef(v));
    EXPECT_CALL(*raw, next()).Times(0);

    GeneratorWrapper<int> wrapper(std::move(mock));
    ChunkGenerator<int> chunkGen(/*size*/1, std::move(wrapper));

    const auto& chunk = chunkGen.get();
    ASSERT_EQ(chunk.size(), 1u);
    EXPECT_EQ(chunk[0], 42);
}

//
// Exceptional case: not enough values to initialize the first chunk.
// The constructor is expected to throw when next() returns false during initialization.
//
TEST_F(ChunkGeneratorTest_1110, ThrowsWhenInsufficientValuesForInitialChunk_1110) {
    using namespace Catch::Generators;

    // We build expectations so that: first get() ok, then next() -> false, causing a throw
    auto makeWrapper = []() {
        auto mock = std::make_unique<StrictMock<MockIGenerator<int>>>();
        auto* raw = mock.get();

        static int v1 = 7;

        InSequence seq;
        EXPECT_CALL(*raw, get()).WillOnce(ReturnRef(v1));
        EXPECT_CALL(*raw, next()).WillOnce(Return(false)); // triggers throw during ctor

        return GeneratorWrapper<int>(std::move(mock));
    };

    // Constructing ChunkGenerator should throw an exception (type is implementation detail;
    // we assert std::exception to stick to observable behavior).
    EXPECT_THROW(
        (ChunkGenerator<int>(/*size*/2, makeWrapper())),
        std::exception
    );
}
