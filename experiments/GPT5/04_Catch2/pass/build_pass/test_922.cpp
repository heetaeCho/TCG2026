// File: tests/generators_take_tests_922.cpp

#include <gtest/gtest.h>
#include <vector>
#include <utility>

#include "Catch2/extras/catch_amalgamated.hpp"

// Helper: Collect all values from a non-empty GeneratorWrapper<T>.
template <typename T>
static std::vector<T> CollectAll(Catch::Generators::GeneratorWrapper<T> gen) {
    std::vector<T> out;
    // Per Catch2 generator contract, the first element is available immediately.
    out.push_back(gen.get());
    while (gen.next()) {
        out.push_back(gen.get());
    }
    return out;
}

// [Normal operation] take(N) should yield at most N items, preserving order.
TEST(GeneratorsTake_922, YieldsUpToTargetCount_922) { // TEST_ID = 922
    using namespace Catch::Generators;

    auto base = values({10, 20, 30});
    auto taken = take(2, std::move(base));

    const auto out = CollectAll(std::move(taken));
    EXPECT_EQ(out, (std::vector<int>{10, 20}));
}

// [Boundary] If target exceeds underlying size, it should yield all underlying items and then stop.
TEST(GeneratorsTake_922, TargetExceedsUnderlying_922) { // TEST_ID = 922
    using namespace Catch::Generators;

    auto taken = take(10, values({1, 2, 3}));
    const auto out = CollectAll(std::move(taken));
    EXPECT_EQ(out, (std::vector<int>{1, 2, 3}));
}

// [Boundary] target == 0 should present an empty sequence (i.e., no accessible current element).
// We do not access get(); we only verify that advancing is immediately impossible.
TEST(GeneratorsTake_922, ZeroTargetProducesEmptySequence_922) { // TEST_ID = 922
    using namespace Catch::Generators;

    auto taken = take(0, values({1, 2, 3}));

    // With zero target, there should be no elements to traverse.
    // Calling next() should be false immediately and remain false.
    EXPECT_FALSE(taken.next());
    EXPECT_FALSE(taken.next()); // idempotent end state
}

// [Observable interaction] The function must accept an rvalue (moved) generator and remain usable.
TEST(GeneratorsTake_922, AcceptsMovedGenerator_922) { // TEST_ID = 922
    using namespace Catch::Generators;

    auto src = values({42, 43});
    auto taken = take(1, std::move(src)); // pass as rvalue as per interface

    const auto out = CollectAll(std::move(taken));
    EXPECT_EQ(out, (std::vector<int>{42}));
}
