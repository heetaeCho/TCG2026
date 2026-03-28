// File: tests/MapGenerator_next_tests_930.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the amalgamated Catch2 header as provided.
#include "Catch2/extras/catch_amalgamated.hpp"

using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::StrictMock;
using ::testing::Sequence;
using ::testing::InSequence;

namespace {

template <typename T>
class MockGenerator : public Catch::Generators::IGenerator<T> {
public:
    MOCK_METHOD(T const&, get, (), (const, override));
    MOCK_METHOD(bool, next, (), (override));
};

// A small helper to build a GeneratorWrapper<T> from a mock.
template <typename T>
Catch::Generators::GeneratorWrapper<T> wrap(std::unique_ptr<Catch::Generators::IGenerator<T>> gen) {
    return Catch::Generators::GeneratorWrapper<T>(std::move(gen));
}

} // namespace

// Test fixture just to hold common aliases
class MapGeneratorTest_930 : public ::testing::Test {
protected:
    using T = int;  // mapped-to type
    using U = int;  // underlying generator's value type
};

// Normal operation: constructor pre-populates cache via function(get())
TEST_F(MapGeneratorTest_930, ConstructorInitialGet_930) {
    auto mock = std::make_unique<StrictMock<MockGenerator<int>>>();

    int current = 3;
    EXPECT_CALL(*mock, get()).Times(1).WillRepeatedly(ReturnRef(current));

    auto func = [](int x) { return x * 2; };

    Catch::Generators::MapGenerator<int, int, decltype(func)> map(
        func, wrap<int>(std::move(mock))
    );

    // get() should reflect mapping of initial underlying value
    EXPECT_EQ(map.get(), 6);
}

// Normal operation: next() returns true and updates mapped cache
TEST_F(MapGeneratorTest_930, NextUpdatesCacheAndReturnsTrue_930) {
    auto mock = std::make_unique<StrictMock<MockGenerator<int>>>();

    int current = 1;
    // get() is called once during construction, and once again on successful next()
    EXPECT_CALL(*mock, get())
        .Times(2)
        .WillRepeatedly(ReturnRef(current));

    {
        InSequence s;
        EXPECT_CALL(*mock, next()).WillOnce(Return(true));
    }

    auto func = [](int x) { return x * 2; };

    Catch::Generators::MapGenerator<int, int, decltype(func)> map(
        func, wrap<int>(std::move(mock))
    );
    // After construction
    EXPECT_EQ(map.get(), 2);

    // Change underlying value that will be observed after next()
    current = 5;

    // Next should succeed and cache should now reflect new mapped value
    EXPECT_TRUE(map.next());
    EXPECT_EQ(map.get(), 10);
}

// Boundary/interaction: next() returns false -> no call to get(), cache unchanged
TEST_F(MapGeneratorTest_930, NextFalseDoesNotCallGetAndKeepsCache_930) {
    auto mock = std::make_unique<StrictMock<MockGenerator<int>>>();

    int current = 7;
    // Only the constructor should call get()
    EXPECT_CALL(*mock, get()).Times(1).WillRepeatedly(ReturnRef(current));

    EXPECT_CALL(*mock, next()).WillOnce(Return(false));

    auto func = [](int x) { return x * 2; };

    Catch::Generators::MapGenerator<int, int, decltype(func)> map(
        func, wrap<int>(std::move(mock))
    );

    // Initial mapped value
    EXPECT_EQ(map.get(), 14);

    // next() returns false; implementation should NOT call get() again
    EXPECT_FALSE(map.next());

    // Cache should remain unchanged and accessible
    EXPECT_EQ(map.get(), 14);
}

// Exceptional case: mapping function throws during construction (observable via thrown exception)
TEST_F(MapGeneratorTest_930, ConstructorThrowsIfMappingFunctionThrows_930) {
    auto mock = std::make_unique<StrictMock<MockGenerator<int>>>();

    int current = 1;
    EXPECT_CALL(*mock, get()).Times(1).WillRepeatedly(ReturnRef(current));

    auto throwing = [](int) -> int {
        throw std::runtime_error("boom at construction");
    };

    // The constructor invokes function(get()); verify exception is observable
    EXPECT_THROW(
        (Catch::Generators::MapGenerator<int, int, decltype(throwing)>(throwing, wrap<int>(std::move(mock)))),
        std::runtime_error
    );
}

// Exceptional case: mapping function throws during next(); exception should propagate
TEST_F(MapGeneratorTest_930, NextThrowsIfMappingFunctionThrows_930) {
    auto mock = std::make_unique<StrictMock<MockGenerator<int>>>();

    int current = 2;

    // get() called at construction and again on successful next()
    EXPECT_CALL(*mock, get()).Times(2).WillRepeatedly(ReturnRef(current));

    // next() of the underlying generator succeeds once
    EXPECT_CALL(*mock, next()).WillOnce(Return(true));

    // Function: first call (construction) ok, second call (next) throws
    auto sometimesThrow = [count = 0](int x) mutable -> int {
        ++count;
        if (count == 2) {
            throw std::runtime_error("boom at next");
        }
        return x * 3;
    };

    Catch::Generators::MapGenerator<int, int, decltype(sometimesThrow)> map(
        sometimesThrow, wrap<int>(std::move(mock))
    );

    // After construction, value mapped successfully
    EXPECT_EQ(map.get(), 6);

    // On next(), mapping function throws; verify propagation
    EXPECT_THROW(map.next(), std::runtime_error);
}
