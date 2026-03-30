// File: tests/repeat_tests_897.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <utility>
#include "Catch2/extras/catch_amalgamated.hpp"

// Helper functor to observe copies/moves via external counters.
struct MoveCopyProbe {
    static int copies;
    static int moves;

    MoveCopyProbe() = default;
    MoveCopyProbe(const MoveCopyProbe&) { ++copies; }
    MoveCopyProbe(MoveCopyProbe&&) noexcept { ++moves; }
    MoveCopyProbe& operator=(const MoveCopyProbe&) = default;
    MoveCopyProbe& operator=(MoveCopyProbe&&) = default;

    void operator()() const noexcept {}
};
int MoveCopyProbe::copies = 0;
int MoveCopyProbe::moves  = 0;

static void ResetProbeCounts() {
    MoveCopyProbe::copies = 0;
    MoveCopyProbe::moves  = 0;
}

// Boundary: move-only functor — should be acceptable with rvalue.
struct MoveOnlyFunctor {
    MoveOnlyFunctor() = default;
    MoveOnlyFunctor(MoveOnlyFunctor&&) = default;
    MoveOnlyFunctor& operator=(MoveOnlyFunctor&&) = default;
    MoveOnlyFunctor(const MoveOnlyFunctor&) = delete;
    MoveOnlyFunctor& operator=(const MoveOnlyFunctor&) = delete;

    void operator()() const noexcept {}
};

namespace C = Catch::Benchmark::Detail;

TEST(RepeatTest_897, ReturnTypeIsRepeater_DecaysFunctorType_897) {
    using Fun = MoveCopyProbe;
    using Decayed = std::decay_t<Fun>;
    // The observable/compile-time contract: repeat returns repeater<decay_t<Fun>>.
    using Returned = decltype(C::repeat(Fun{}));
    using Expected = C::repeater<Decayed>;
    static_assert(std::is_same<Returned, Expected>::value,
                  "repeat(Fun) must return repeater<decay_t<Fun>>");
    SUCCEED(); // Keeps the test as a runtime test case.
}

TEST(RepeatTest_897, ForwardsRvalue_UsesMove_NotCopy_897) {
    ResetProbeCounts();
    auto r = C::repeat(MoveCopyProbe{}); // rvalue
    (void)r;
    EXPECT_EQ(MoveCopyProbe::copies, 0) << "Rvalue should not be copied into repeater";
    EXPECT_GE(MoveCopyProbe::moves, 1)  << "Rvalue should be moved at least once into repeater";
}

TEST(RepeatTest_897, ForwardsLvalue_UsesCopy_NotMove_897) {
    ResetProbeCounts();
    MoveCopyProbe f;
    auto r = C::repeat(f); // lvalue
    (void)r;
    EXPECT_GE(MoveCopyProbe::copies, 1) << "Lvalue should be copied into repeater";
    EXPECT_EQ(MoveCopyProbe::moves, 0)  << "Lvalue forwarding should not cause a move";
}

TEST(RepeatTest_897, ForwardsConstLvalue_UsesCopy_NotMove_897) {
    ResetProbeCounts();
    const MoveCopyProbe f{};
    auto r = C::repeat(f); // const lvalue
    (void)r;
    EXPECT_GE(MoveCopyProbe::copies, 1) << "Const lvalue should be copied into repeater";
    EXPECT_EQ(MoveCopyProbe::moves, 0)  << "Const lvalue forwarding should not cause a move";
}

TEST(RepeatTest_897, AcceptsMoveOnlyFunctor_WithRvalue_897) {
    // Compile-time check that move-only functors are accepted and type decays correctly.
    using Returned = decltype(C::repeat(MoveOnlyFunctor{}));
    using Expected = C::repeater<std::decay_t<MoveOnlyFunctor>>;
    static_assert(std::is_same<Returned, Expected>::value,
                  "repeat(move-only) must return repeater<decay_t<MoveOnlyFunctor>>");
    // Also construct at runtime (no copy available -> must succeed via move).
    auto r = C::repeat(MoveOnlyFunctor{});
    (void)r;
    SUCCEED();
}
