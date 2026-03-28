// File: tests/repeat_generator_next_927.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the amalgamated Catch2 header that contains RepeatGenerator & friends
#include "Catch2/extras/catch_amalgamated.hpp"

using ::testing::_;
using ::testing::DoAll;
using ::testing::InvokeWithoutArgs;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::StrictMock;

namespace {

template <typename T>
class MockGen : public Catch::Generators::IGenerator<T> {
public:
    MOCK_METHOD(T const&, get, (), (const, override));
    MOCK_METHOD(bool, next, (), (override));
};

using Catch::Generators::GeneratorWrapper;
using Catch::Generators::RepeatGenerator;

class RepeatGeneratorTest_927 : public ::testing::Test {
protected:
    // Helper that builds a RepeatGenerator<T> around a mock and returns both
    template <typename T>
    std::pair<std::unique_ptr<StrictMock<MockGen<T>>>, std::unique_ptr<RepeatGenerator<T>>>
    makeRepeatWithMock(std::size_t repeats,
                       std::function<void(StrictMock<MockGen<T>>&,
                                          T& current)> setupExpectations) {
        auto mockPtr = std::make_unique<StrictMock<MockGen<T>>>();
        auto& mock = *mockPtr;
        T* currentPtr = new T{}; // we'll manage via unique_ptr for safety below
        std::unique_ptr<T> currentHolder(currentPtr);

        // By default, get() returns the current value by reference.
        ON_CALL(mock, get()).WillByDefault(ReturnRef(*currentPtr));

        // Let the caller define the exact next() behavior & any updates to current.
        setupExpectations(mock, *currentPtr);

        // Wrap mock into a GeneratorWrapper<T>
        GeneratorWrapper<T> wrapper(std::unique_ptr<Catch::Generators::IGenerator<T>>(mockPtr.release()));

        // Construct RepeatGenerator<T>
        auto rg = std::make_unique<RepeatGenerator<T>>(repeats, std::move(wrapper));

        // Attach a custom deleter to keep currentHolder alive for the duration of the test
        // (so references returned by get() remain valid while rg lives).
        struct Holder {
            std::unique_ptr<T> hold;
            explicit Holder(std::unique_ptr<T> h) : hold(std::move(h)) {}
        };
        // store holder in a dummy lambda capture to extend lifetime alongside rg
        (void) Holder(std::move(currentHolder));

        // Re-acquire the mock pointer (wrapper now owns it; RepeatGenerator stores the wrapper),
        // but we also need to assert calls on it, so we keep a raw pointer via const_cast trick:
        // Instead of retrieving from wrapper, we rely on the expectations already set on the
        // strict mock before moving it into wrapper.

        // Return original mock (now owned by wrapper) through a dangling unique_ptr is not possible,
        // so we just return a nullptr for the mock unique_ptr to avoid ownership confusion.
        // To keep the API simple, we return a pair where the first is nullptr and note that
        // expectations are already installed (StrictMock will verify at test end).
        return { std::unique_ptr<StrictMock<MockGen<T>>>(nullptr), std::move(rg) };
    }
};

} // namespace

// Normal operation: underlying generator produces 3 values, then ends; we repeat twice.
TEST_F(RepeatGeneratorTest_927, Next_RepeatsUnderlyingSequenceTwice_927) {
    // Build expectations: underling sequence 10,20,30 then false
    StrictMock<MockGen<int>>* mockRaw = nullptr;
    std::unique_ptr<RepeatGenerator<int>> rg;

    {
        auto mockPtr = std::make_unique<StrictMock<MockGen<int>>>();
        mockRaw = mockPtr.get();
        int current = 0;
        ON_CALL(*mockRaw, get()).WillByDefault(ReturnRef(current));

        // next(): true with current=10, true with current=20, true with current=30, then false
        EXPECT_CALL(*mockRaw, next())
            .WillOnce(InvokeWithoutArgs([&](){ current = 10; return true; }))
            .WillOnce(InvokeWithoutArgs([&](){ current = 20; return true; }))
            .WillOnce(InvokeWithoutArgs([&](){ current = 30; return true; }))
            .WillOnce(Return(false));

        GeneratorWrapper<int> wrapper(std::unique_ptr<Catch::Generators::IGenerator<int>>(mockPtr.release()));
        rg = std::make_unique<RepeatGenerator<int>>(/*repeats=*/2, std::move(wrapper));
    }

    std::vector<int> seen;
    while (rg->next()) {
        seen.push_back(rg->get());
    }

    // We expect 3 * 2 = 6 values repeated in order.
    ASSERT_EQ(seen.size(), 6u);
    EXPECT_THAT(seen, ::testing::ElementsAre(10, 20, 30, 10, 20, 30));
    // Underlying next() was called exactly 4 times (3 trues + 1 false) — verified by StrictMock.
}

// Boundary: zero repeats => RepeatGenerator::next() should return false immediately
// even if the underlying has data; still calls inner next() once on first entry.
TEST_F(RepeatGeneratorTest_927, Next_ZeroRepeatsImmediateFalse_927) {
    auto mockPtr = std::make_unique<StrictMock<MockGen<int>>>();
    auto* mock = mockPtr.get();

    int current = 123;
    ON_CALL(*mock, get()).WillByDefault(ReturnRef(current));

    // Even though underlying could yield, RepeatGenerator should end immediately (target=0),
    // but it still probes once per implementation (observable via interaction).
    EXPECT_CALL(*mock, next()).WillOnce(Return(true));

    GeneratorWrapper<int> wrapper(std::unique_ptr<Catch::Generators::IGenerator<int>>(mockPtr.release()));
    RepeatGenerator<int> rg(/*repeats=*/0, std::move(wrapper));

    EXPECT_FALSE(rg.next());
}

// Exceptional/boundary observable behavior: underlying is empty (next() == false immediately).
// With repeats=3, next() will return true twice (counting up repeats) and then false,
// and it must NOT call the inner generator again after the first failure.
TEST_F(RepeatGeneratorTest_927, Next_EmptyUnderlyingRepeatsAsCounter_927) {
    auto mockPtr = std::make_unique<StrictMock<MockGen<int>>>();
    auto* mock = mockPtr.get();

    int current = 0;
    ON_CALL(*mock, get()).WillByDefault(ReturnRef(current));

    // Underlying immediately exhausted
    EXPECT_CALL(*mock, next()).WillOnce(Return(false));

    GeneratorWrapper<int> wrapper(std::unique_ptr<Catch::Generators::IGenerator<int>>(mockPtr.release()));
    RepeatGenerator<int> rg(/*repeats=*/3, std::move(wrapper));

    // No calls to get(), we only probe next() behavior.
    EXPECT_TRUE(rg.next());  // transitions to repeat 1/3
    EXPECT_TRUE(rg.next());  // transitions to repeat 2/3
    EXPECT_FALSE(rg.next()); // transitions to repeat 3/3 -> done
}

// Normal + value stability: single underlying value repeated N times.
TEST_F(RepeatGeneratorTest_927, Next_SingleValueRepeatedThrice_927) {
    auto mockPtr = std::make_unique<StrictMock<MockGen<int>>>();
    auto* mock = mockPtr.get();

    int current = 0;
    ON_CALL(*mock, get()).WillByDefault(ReturnRef(current));

    // One value (42), then end
    EXPECT_CALL(*mock, next())
        .WillOnce(InvokeWithoutArgs([&](){ current = 42; return true; }))
        .WillOnce(Return(false));

    GeneratorWrapper<int> wrapper(std::unique_ptr<Catch::Generators::IGenerator<int>>(mockPtr.release()));
    RepeatGenerator<int> rg(/*repeats=*/3, std::move(wrapper));

    std::vector<int> seen;
    while (rg.next()) {
        seen.push_back(rg.get());
    }
    EXPECT_THAT(seen, ::testing::ElementsAre(42, 42, 42));
}

// Interaction verification: once the underlying generator is exhausted during the first pass,
// subsequent repeats must not invoke the inner generator again.
TEST_F(RepeatGeneratorTest_927, Next_DoesNotCallInnerAfterExhaustion_927) {
    auto mockPtr = std::make_unique<StrictMock<MockGen<int>>>();
    auto* mock = mockPtr.get();

    int current = 0;
    ON_CALL(*mock, get()).WillByDefault(ReturnRef(current));

    // Underlying yields 2 values then ends
    EXPECT_CALL(*mock, next())
        .WillOnce(InvokeWithoutArgs([&](){ current = 1; return true; }))
        .WillOnce(InvokeWithoutArgs([&](){ current = 2; return true; }))
        .WillOnce(Return(false));

    GeneratorWrapper<int> wrapper(std::unique_ptr<Catch::Generators::IGenerator<int>>(mockPtr.release()));
    RepeatGenerator<int> rg(/*repeats=*/5, std::move(wrapper));

    std::size_t countTrue = 0;
    while (rg.next()) {
        (void)rg.get();
        ++countTrue;
    }

    // We saw 2 * 5 values across repeats.
    EXPECT_EQ(countTrue, 10u);
    // StrictMock expectations ensure no extra calls to inner next() occurred after exhaustion.
}
