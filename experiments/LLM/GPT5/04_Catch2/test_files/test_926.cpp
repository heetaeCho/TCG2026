// File: tests/RepeatGeneratorTest_926.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Catch2/extras/catch_amalgamated.hpp"

using ::testing::_;
using ::testing::StrictMock;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Invoke;

namespace {

template <typename T>
struct MockIGenerator : Catch::Generators::IGenerator<T> {
    MOCK_METHOD(T const&, get, (), (const, override));
    MOCK_METHOD(bool, next, (), (override));
    ~MockIGenerator() override = default;
};

// A tiny external collaborator: yields a fixed sequence once.
// This is NOT simulating RepeatGenerator internals; it is a simple
// source generator used as input (allowed by the constraints).
class SimpleSeqGen final : public Catch::Generators::IGenerator<int> {
public:
    explicit SimpleSeqGen(std::vector<int> seq) : seq_(std::move(seq)) {
        if (seq_.empty()) { curr_ = 0; done_ = true; }
        else              { curr_ = 0; done_ = false; }
    }

    int const& get() const override {
        return seq_[curr_];
    }

    bool next() override {
        if (done_) return false;
        if (curr_ + 1 < seq_.size()) {
            ++curr_;
            return true;
        }
        // Exhaust after last element
        done_ = true;
        return false;
    }

private:
    std::vector<int> seq_;
    size_t curr_{0};
    bool done_{false};
};

struct RepeatGeneratorTest_926 : ::testing::Test {
    template <typename T>
    static Catch::Generators::GeneratorWrapper<T>
    wrap(std::unique_ptr<Catch::Generators::IGenerator<T>> p) {
        return Catch::Generators::GeneratorWrapper<T>(std::move(p));
    }
};

} // namespace

// Normal operation: repeating a two-element sequence twice yields it twice.
TEST_F(RepeatGeneratorTest_926, RepeatTwice_YieldsSequenceTwice_926) {
    using namespace Catch::Generators;
    auto inner = std::make_unique<SimpleSeqGen>(std::vector<int>{1, 2});
    RepeatGenerator<int> rg(/*repeats=*/2, RepeatGeneratorTest_926::wrap<int>(std::move(inner)));

    std::vector<int> observed;
    observed.push_back(rg.get());
    while (rg.next()) {
        observed.push_back(rg.get());
    }

    std::vector<int> expected{1, 2, 1, 2};
    EXPECT_EQ(observed, expected);
}

// Boundary: single repeat behaves like the inner generator (no extra copies).
TEST_F(RepeatGeneratorTest_926, SingleRepeat_ActsLikeInnerSequence_926) {
    using namespace Catch::Generators;
    auto inner = std::make_unique<SimpleSeqGen>(std::vector<int>{10, 20});
    RepeatGenerator<int> rg(/*repeats=*/1, RepeatGeneratorTest_926::wrap<int>(std::move(inner)));

    std::vector<int> observed;
    observed.push_back(rg.get());
    while (rg.next()) {
        observed.push_back(rg.get());
    }

    std::vector<int> expected{10, 20};
    EXPECT_EQ(observed, expected);
}

// Boundary: repeating a single-element sequence multiple times yields
// that element the specified number of times.
TEST_F(RepeatGeneratorTest_926, SingleElement_RepeatsNtimes_926) {
    using namespace Catch::Generators;
    auto inner = std::make_unique<SimpleSeqGen>(std::vector<int>{42});
    RepeatGenerator<int> rg(/*repeats=*/3, RepeatGeneratorTest_926::wrap<int>(std::move(inner)));

    std::vector<int> observed;
    observed.push_back(rg.get());
    while (rg.next()) {
        observed.push_back(rg.get());
    }

    std::vector<int> expected{42, 42, 42};
    EXPECT_EQ(observed, expected);
}

// Verification of external interactions:
// Ensure the inner generator's get() is only used to produce the first
// pass's values; repeated passes should not call inner.get() again.
// (We do not assert exact next() calls to avoid over-constraining.)
TEST_F(RepeatGeneratorTest_926, DoesNotCallInnerGetOnRepeatedPasses_926) {
    using namespace Catch::Generators;

    // Prepare a strict mock so unexpected calls fail the test.
    auto mockPtr = std::make_unique<StrictMock<MockIGenerator<int>>>();
    auto* raw = mockPtr.get();

    // A tiny stateful backing sequence for the mock.
    static int v1 = 7, v2 = 9;
    int idx = 0; // 0 -> v1, 1 -> v2, then exhausted

    // get() should be called only while discovering the first pass.
    // There are two distinct values in the inner sequence, so exactly 2 gets.
    EXPECT_CALL(*raw, get())
        .Times(2)
        .WillRepeatedly(Invoke([&]() -> int const& {
            return (idx == 0) ? v1 : v2;
        }));

    // next() advances through the inner sequence once, then reports exhaustion.
    // Do not over-constrain call counts; just provide correct behavior.
    ON_CALL(*raw, next())
        .WillByDefault(Invoke([&]() -> bool {
            if (idx == 0) { idx = 1; return true; }
            if (idx == 1) { idx = 2; return false; }
            // Already exhausted
            return false;
        }));

    RepeatGenerator<int> rg(/*repeats=*/3, RepeatGeneratorTest_926::wrap<int>(std::move(mockPtr)));

    // Consume the repeated generator fully.
    std::vector<int> observed;
    observed.push_back(rg.get());
    while (rg.next()) {
        observed.push_back(rg.get());
    }

    // Observable values: inner [7,9] repeated 3 times.
    std::vector<int> expected{7,9, 7,9, 7,9};
    EXPECT_EQ(observed, expected);
}

// Reference stability (observable via addresses):
// The same logical position across repeats should refer to the same cached object.
TEST_F(RepeatGeneratorTest_926, ReferenceIdentityIsStableAcrossRepeats_926) {
    using namespace Catch::Generators;
    auto inner = std::make_unique<SimpleSeqGen>(std::vector<int>{3, 5});
    RepeatGenerator<int> rg(/*repeats=*/2, RepeatGeneratorTest_926::wrap<int>(std::move(inner)));

    // First pass, capture addresses
    auto const* first_0 = &rg.get(); // value 3
    ASSERT_TRUE(rg.next());
    auto const* first_1 = &rg.get(); // value 5

    // Move to second pass (finish first pass)
    ASSERT_FALSE(rg.next()); // inner exhausted, should roll into repeat
    // Now at start of second pass
    auto const* second_0 = &rg.get(); // value 3 again
    ASSERT_TRUE(rg.next());
    auto const* second_1 = &rg.get(); // value 5 again

    // Addresses should be stable across repeats for the same positions
    EXPECT_EQ(first_0, second_0);
    EXPECT_EQ(first_1, second_1);
}
