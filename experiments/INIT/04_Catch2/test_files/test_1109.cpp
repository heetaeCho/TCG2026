// File: tests/repeat_generator_tests_1109.cpp

#include <gtest/gtest.h>
#include "Catch2/extras/catch_amalgamated.hpp"

// Minimal external collaborator used only to provide a concrete IGenerator<T>
// for the RepeatGenerator's constructor. This does NOT simulate internal logic
// of RepeatGenerator; it merely yields a fixed sequence once.
template <typename T>
class VectorOnceGenerator : public Catch::Generators::IGenerator<T> {
public:
    explicit VectorOnceGenerator(std::vector<T> values)
        : vals_(std::move(values)), idx_(0) {
        // Precondition for IGenerator: at least one value to expose via get()
        // (If your environment allows empty generators, you can add a separate
        // test guarded appropriately. This one keeps assumptions minimal.)
        assert(!vals_.empty());
    }

    T const& get() const override {
        return vals_[idx_];
    }

    bool next() override {
        if (idx_ + 1 < vals_.size()) {
            ++idx_;
            return true;
        }
        return false;
    }

private:
    std::vector<T> vals_;
    std::size_t idx_;
};

using Catch::Generators::GeneratorWrapper;
using Catch::Generators::RepeatGenerator;

// Helper: exhaust an IGenerator<T> into a vector<T> by observing get()/next()
template <typename T>
static std::vector<T> DrainGenerator(Catch::Generators::IGenerator<T>& gen) {
    std::vector<T> out;
    // Always observe current value first (IGenerator contract),
    // then advance while next() returns true.
    out.push_back(gen.get());
    while (gen.next()) {
        out.push_back(gen.get());
    }
    return out;
}

// ----------------------------------------------------------------------------
// Normal operation: repeats a short sequence multiple times
// ----------------------------------------------------------------------------
TEST(RepeatGenerator_1109, RepeatsSequenceThreeTimes_1109) {
    // Base sequence [1, 2] produced once by the collaborator
    auto base = std::make_unique<VectorOnceGenerator<int>>(std::vector<int>{1, 2});
    GeneratorWrapper<int> wrapped{std::move(base)};

    // Repeat the base sequence 3 times
    RepeatGenerator<int> rep{3, std::move(wrapped)};

    // Observable behavior: values yielded in order, then generator ends
    const auto values = DrainGenerator(rep);
    // Expect: [1,2, 1,2, 1,2]
    ASSERT_EQ(values.size(), 6u);
    EXPECT_EQ(values[0], 1);
    EXPECT_EQ(values[1], 2);
    EXPECT_EQ(values[2], 1);
    EXPECT_EQ(values[3], 2);
    EXPECT_EQ(values[4], 1);
    EXPECT_EQ(values[5], 2);
}

// ----------------------------------------------------------------------------
// Boundary: repeats == 1 should behave like pass-through of the base sequence
// ----------------------------------------------------------------------------
TEST(RepeatGenerator_1109, RepeatsOnceActsLikePassthrough_1109) {
    auto base = std::make_unique<VectorOnceGenerator<int>>(std::vector<int>{42, 7, 9});
    GeneratorWrapper<int> wrapped{std::move(base)};

    RepeatGenerator<int> rep{1, std::move(wrapped)};

    const auto values = DrainGenerator(rep);
    ASSERT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], 42);
    EXPECT_EQ(values[1], 7);
    EXPECT_EQ(values[2], 9);
}

// ----------------------------------------------------------------------------
// Boundary: single-element base sequence repeated many times
// ----------------------------------------------------------------------------
TEST(RepeatGenerator_1109, SingleElementRepeatedFourTimes_1109) {
    auto base = std::make_unique<VectorOnceGenerator<int>>(std::vector<int>{5});
    GeneratorWrapper<int> wrapped{std::move(base)};

    RepeatGenerator<int> rep{4, std::move(wrapped)};

    const auto values = DrainGenerator(rep);
    ASSERT_EQ(values.size(), 4u);
    for (int v : values) {
        EXPECT_EQ(v, 5);
    }
}

// ----------------------------------------------------------------------------
// Observability of get(): repeated calls to get() without next() should not
// change the observed value (no assumptions about reference identity).
// ----------------------------------------------------------------------------
TEST(RepeatGenerator_1109, GetIsStableUntilNext_1109) {
    auto base = std::make_unique<VectorOnceGenerator<int>>(std::vector<int>{3, 4});
    GeneratorWrapper<int> wrapped{std::move(base)};

    RepeatGenerator<int> rep{2, std::move(wrapped)};

    // Initial value observable via get()
    int first = rep.get();
    // Multiple gets without next() return the same observed value
    EXPECT_EQ(rep.get(), first);
    EXPECT_EQ(rep.get(), first);

    // After advancing, observable value can change
    ASSERT_TRUE(rep.next());
    int second = rep.get();
    EXPECT_NE(second, first);
    EXPECT_EQ(rep.get(), second);
}

// ----------------------------------------------------------------------------
// Exceptional / error case: constructing with repeats == 0 should fire the
// assertion in the constructor (death test). This requires asserts enabled
// (i.e., do NOT compile this test with NDEBUG).
// ----------------------------------------------------------------------------
TEST(RepeatGenerator_1109, ConstructionWithZeroRepeatsAsserts_1109) {
    auto base = std::make_unique<VectorOnceGenerator<int>>(std::vector<int>{1});
    // We have to prepare the wrapper first; but we cannot move it into the
    // lambda twice, so build inside the death lambda.
    ASSERT_DEATH(
        [] {
            auto innerBase = std::make_unique<VectorOnceGenerator<int>>(std::vector<int>{1});
            GeneratorWrapper<int> innerWrapped{std::move(innerBase)};
            // Expect assertion: "Repeat generator must repeat at least once"
            RepeatGenerator<int> rep{0, std::move(innerWrapped)};
            (void)rep; // silence unused warning
        }(),
        "Repeat generator must repeat at least once"
    );
}
