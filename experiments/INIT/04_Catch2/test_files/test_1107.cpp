// File: tests/TakeGenerator_tests_1107.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// We include the amalgamated header so we can use the public generator interfaces.
#include "Catch2/extras/catch_amalgamated.hpp"

using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::AtLeast;
using ::testing::AtMost;
using ::testing::_;
using Catch::Generators::IGenerator;
using Catch::Generators::GeneratorWrapper;
using Catch::Generators::TakeGenerator;

//
// A simple external collaborator: a finite vector-backed generator.
// This is NOT testing TakeGenerator internals; it is just a concrete
// IGenerator<T> we can wrap to observe public behavior.
//
class VectorIntGenerator : public IGenerator<int> {
public:
    explicit VectorIntGenerator(std::vector<int> values)
        : data_(std::move(values)), idx_(0) {
        // Precondition for IGenerator: user should not call get() if empty.
        // Tests below avoid calling get() on an empty generator.
        if (data_.empty()) idx_ = 0; // keep 0; next() will immediately fail
    }

    int const& get() const override {
        return data_[idx_];
    }

    bool next() override {
        if (data_.empty()) return false;
        if (idx_ + 1 < data_.size()) {
            ++idx_;
            return true;
        }
        return false;
    }

private:
    std::vector<int> data_;
    std::size_t idx_;
};

//
// A mock external collaborator to verify interactions (call counts) with
// the underlying generator. We only mock the collaborator, not the SUT.
//
class MockIntGenerator : public IGenerator<int> {
public:
    MOCK_METHOD(int const&, get, (), (const, override));
    MOCK_METHOD(bool, next, (), (override));
};

// --- Tests ---

// Normal operation: take limits the number of values exposed.
TEST(TakeGeneratorTest_1107, TakeLimitsElements_1107) {
    // Underlying generator has 4 values.
    auto base = std::unique_ptr<IGenerator<int>>(new VectorIntGenerator({10, 20, 30, 40}));
    GeneratorWrapper<int> wrapper(std::move(base));

    // Take only 2 values.
    TakeGenerator<int> take2(2, std::move(wrapper));

    // First value is available immediately via get().
    EXPECT_EQ(take2.get(), 10);

    // Move to the second value.
    EXPECT_TRUE(take2.next());
    EXPECT_EQ(take2.get(), 20);

    // After exposing 2 values total, next() should report no more values.
    EXPECT_FALSE(take2.next());

    // Further next() calls should continue to report exhaustion (black-box safe check).
    EXPECT_FALSE(take2.next());
}

// Boundary: underlying shorter than target — should stop when collaborator is exhausted.
TEST(TakeGeneratorTest_1107, StopsWhenUnderlyingExhausted_1107) {
    // Underlying has only 2 values.
    auto base = std::unique_ptr<IGenerator<int>>(new VectorIntGenerator({1, 2}));
    GeneratorWrapper<int> wrapper(std::move(base));

    // Ask to take more than available.
    TakeGenerator<int> take5(5, std::move(wrapper));

    // First value present.
    EXPECT_EQ(take5.get(), 1);

    // Advance to second.
    EXPECT_TRUE(take5.next());
    EXPECT_EQ(take5.get(), 2);

    // Underlying now exhausted — even though target not yet reached, next() should be false.
    EXPECT_FALSE(take5.next());
    EXPECT_FALSE(take5.next());
}

// External interaction verification: ensure TakeGenerator does NOT forward next()
// to the underlying generator after the take limit is reached.
TEST(TakeGeneratorTest_1107, DoesNotForwardNextAfterLimit_1107) {
    // Allocate a mock on the heap so GeneratorWrapper can take ownership.
    auto* raw = new NiceMock<MockIntGenerator>();
    // Provide a stable backing storage for get()'s reference return.
    static int backing = 42;
    ON_CALL(*raw, get()).WillByDefault(ReturnRef(backing));
    // By default, pretend the underlying has "infinite" values.
    ON_CALL(*raw, next()).WillByDefault(Return(true));

    // Expect exactly (target-1) forwards: for N taken values, user needs (N-1) successful next() calls.
    // Here we target N=3, so only 2 calls should reach the underlying.
    EXPECT_CALL(*raw, next()).Times(2);

    std::unique_ptr<IGenerator<int>> base(raw);
    GeneratorWrapper<int> wrapper(std::move(base));
    TakeGenerator<int> take3(3, std::move(wrapper));

    // Expose first (via get), then advance twice to get the 2nd and 3rd values.
    (void)take3.get();          // First value visible immediately.
    EXPECT_TRUE(take3.next());  // 1st forward to underlying
    EXPECT_TRUE(take3.next());  // 2nd forward to underlying

    // Now the take limit has been reached — next() should NOT forward anymore and should be false.
    EXPECT_FALSE(take3.next());

    // And subsequent next() calls should also not forward.
    EXPECT_FALSE(take3.next());
}

#ifndef NDEBUG
// Exceptional case (debug builds): constructing with target == 0 should trip the assert.
// We match the public assertion string from the code snippet.
TEST(TakeGeneratorTest_1107, ConstructionWithZeroTargetDies_1107) {
    auto base = std::unique_ptr<IGenerator<int>>(new VectorIntGenerator({123}));
    // Wrap in a lambda to isolate the death region.
    EXPECT_DEATH(
        {
            GeneratorWrapper<int> wrapper(std::move(base));
            TakeGenerator<int> invalid(0, std::move(wrapper));
            (void)invalid;
        },
        "Empty generators are not allowed"
    );
}
#endif
