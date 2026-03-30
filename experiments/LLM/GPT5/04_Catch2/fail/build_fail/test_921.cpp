// File: tests/take_generator_next_921.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Catch2/extras/catch_amalgamated.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::StrictMock;
using ::testing::InSequence;

namespace {

template <typename T>
class MockGenerator : public Catch::Generators::IGenerator<T> {
public:
    MOCK_METHOD(T const&, get, (), (const, override));
    MOCK_METHOD(bool, next, (), (override));
};

using Catch::Generators::GeneratorWrapper;
using Catch::Generators::TakeGenerator;

// Helper to build a GeneratorWrapper<T> owning the given mock pointer.
template <typename T>
GeneratorWrapper<T> wrapOwned(MockGenerator<T>* raw) {
    return GeneratorWrapper<T>(std::unique_ptr<Catch::Generators::IGenerator<T>>(raw));
}

} // namespace

// -------------------------------------------------------------
// TESTS (TEST_ID = 921)
// -------------------------------------------------------------

// For target == 0, next() should immediately return false and not
// call the underlying generator.
TEST(TakeGeneratorTest_921, ZeroTarget_ImmediatelyFalse_NoInnerCalls_921) {
    auto* inner = new StrictMock<MockGenerator<int>>();
    auto wrapper = wrapOwned(inner);

    TakeGenerator<int> take{0, std::move(wrapper)};

    EXPECT_FALSE(take.next()); // should short-circuit
    // No expectations set on inner -> ensures no calls were made.
}

// For target == 1, according to the provided next() implementation,
// ++m_returned happens before the target check, so it returns false
// immediately and does not call the inner generator.
TEST(TakeGeneratorTest_921, TargetOne_ImmediatelyFalse_NoInnerCalls_921) {
    auto* inner = new StrictMock<MockGenerator<int>>();
    auto wrapper = wrapOwned(inner);

    TakeGenerator<int> take{1, std::move(wrapper)};

    EXPECT_FALSE(take.next()); // short-circuit at the limit
    // No interactions with inner
}

// When target == 2 and the inner generator's first next() succeeds,
// TakeGenerator::next() should:
//  - first call: call inner.next() and return its value (true)
//  - second call: hit the limit and return false without calling inner
TEST(TakeGeneratorTest_921, CallsInnerUntilLimit_ThenStops_921) {
    auto* inner = new StrictMock<MockGenerator<int>>();
    auto wrapper = wrapOwned(inner);

    {
        InSequence seq;
        EXPECT_CALL(*inner, next()).WillOnce(Return(true));
        // On the second take.next(), no inner.next() should be called.
    }

    TakeGenerator<int> take{2, std::move(wrapper)};

    EXPECT_TRUE(take.next());   // calls inner.next() -> true
    EXPECT_FALSE(take.next());  // reaches limit, no inner call
}

// If the inner generator reports false early on its first next(),
// TakeGenerator::next() should return false and "latch" to the target,
// so subsequent next() calls remain false without additional inner calls.
TEST(TakeGeneratorTest_921, InnerStopsEarly_PropagatesFalse_AndShortCircuitsNext_921) {
    auto* inner = new StrictMock<MockGenerator<int>>();
    auto wrapper = wrapOwned(inner);

    EXPECT_CALL(*inner, next()).WillOnce(Return(false));

    TakeGenerator<int> take{5, std::move(wrapper)};

    EXPECT_FALSE(take.next());  // inner returns false
    // Subsequent calls should not touch inner anymore
    EXPECT_FALSE(take.next());
    EXPECT_FALSE(take.next());
}

// After a successful next(), get() should delegate to the inner generator's get()
// and return the same reference/value.
TEST(TakeGeneratorTest_921, GetDelegatesToInner_AfterSuccessfulNext_921) {
    auto* inner = new StrictMock<MockGenerator<int>>();
    auto wrapper = wrapOwned(inner);

    int stored = 42;

    {
        InSequence seq;
        EXPECT_CALL(*inner, next()).WillOnce(Return(true));
        EXPECT_CALL(*inner, get()).WillOnce(ReturnRef(stored));
    }

    TakeGenerator<int> take{2, std::move(wrapper)};

    ASSERT_TRUE(take.next());              // make value available
    const int& got = take.get();          // should delegate to inner.get()
    EXPECT_EQ(&got, &stored);             // verify it's the same reference
    EXPECT_EQ(got, 42);
}
