// File: test_simple_pcg32_639.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_random_number_generator.hpp"

using Catch::SimplePcg32;

class SimplePcg32Test_639 : public ::testing::Test {
protected:
    // Helper: collect N outputs from an RNG via its public operator()
    template <typename Rng>
    static std::vector<decltype(std::declval<Rng&>()())>
    Collect(Rng& rng, size_t n) {
        std::vector<decltype(rng())> out;
        out.reserve(n);
        for (size_t i = 0; i < n; ++i) out.push_back(rng());
        return out;
    }
};

// 1) Determinism with identical seeds
TEST_F(SimplePcg32Test_639, SameSeed_YieldsIdenticalSequence_639) {
    SimplePcg32 a;
    SimplePcg32 b;
    using result_t = decltype(a());

    const result_t seed = static_cast<result_t>(123456789u);
    a.seed(seed);
    b.seed(seed);

    auto seqA = Collect(a, 10);
    auto seqB = Collect(b, 10);
    EXPECT_EQ(seqA, seqB);
}

// 2) Different seeds should (very likely) produce different sequences
TEST_F(SimplePcg32Test_639, DifferentSeeds_ProduceDifferentSequenceEarly_639) {
    SimplePcg32 a;
    SimplePcg32 b;
    using result_t = decltype(a());

    a.seed(static_cast<result_t>(1u));
    b.seed(static_cast<result_t>(2u));

    // Compare first 10 values; at least one should differ
    bool anyDiff = false;
    for (int i = 0; i < 10; ++i) {
        auto va = a();
        auto vb = b();
        if (va != vb) { anyDiff = true; break; }
    }
    EXPECT_TRUE(anyDiff);
}

// 3) Reseeding restores sequence to start for a given seed
TEST_F(SimplePcg32Test_639, Reseed_RestartsSequenceForThatSeed_639) {
    SimplePcg32 a;
    using result_t = decltype(a());

    const result_t seed = static_cast<result_t>(987654321u);

    // Reference sequence from a freshly-seeded generator
    SimplePcg32 ref;
    ref.seed(seed);
    auto baseline = Collect(ref, 8);

    // Advance 'a' with a different seed first
    a.seed(static_cast<result_t>(111u));
    (void)a(); (void)a(); // draw a couple values

    // Now reseed 'a' with the same 'seed' and expect identical baseline
    a.seed(seed);
    auto afterReseed = Collect(a, 8);
    EXPECT_EQ(afterReseed, baseline);
}

// 4) discard(k) should match k calls to operator()
TEST_F(SimplePcg32Test_639, Discard_EquivalentToAdvancingByKDraws_639) {
    SimplePcg32 x1, x2;
    using result_t = decltype(x1());
    const result_t seed = static_cast<result_t>(2024u);
    x1.seed(seed);
    x2.seed(seed);

    constexpr uint64_t k = 5;
    // Advance x1 by calling operator() k times
    for (uint64_t i = 0; i < k; ++i) (void)x1();

    // Advance x2 using discard
    x2.discard(k);

    // Next values should match
    auto next1 = x1();
    auto next2 = x2();
    EXPECT_EQ(next1, next2);
}

// 5) discard(0) is a no-op
TEST_F(SimplePcg32Test_639, DiscardZero_IsNoOp_639) {
    SimplePcg32 a, b;
    using result_t = decltype(a());
    a.seed(static_cast<result_t>(7u));
    b.seed(static_cast<result_t>(7u));

    b.discard(0); // no-op expected

    // First several draws should be identical
    for (int i = 0; i < 6; ++i) {
        EXPECT_EQ(a(), b());
    }
}

// 6) min/max define closed bounds for outputs
TEST_F(SimplePcg32Test_639, Values_AreWithinMinMax_639) {
    SimplePcg32 rng;
    using result_t = decltype(rng());
    rng.seed(static_cast<result_t>(42u));

    const auto lo = SimplePcg32::min();
    const auto hi = SimplePcg32::max();
    ASSERT_LT(lo, hi); // sanity

    for (int i = 0; i < 100; ++i) {
        auto v = rng();
        EXPECT_LE(lo, v);
        EXPECT_LE(v, hi);
    }
}

// 7) Default construction produces a deterministic default seed
TEST_F(SimplePcg32Test_639, DefaultConstructors_ProduceSameSequence_639) {
    SimplePcg32 a; // default seed
    SimplePcg32 b; // default seed
    auto seqA = Collect(a, 12);
    auto seqB = Collect(b, 12);
    EXPECT_EQ(seqA, seqB);
}

// 8) Equality/inequality reflect generator state
TEST_F(SimplePcg32Test_639, EqualityOperators_ReflectStateProgress_639) {
    SimplePcg32 a, b;
    using result_t = decltype(a());
    const result_t seed = static_cast<result_t>(31415u);

    a.seed(seed);
    b.seed(seed);
    EXPECT_TRUE(a == b);

    (void)a();            // advance only 'a'
    EXPECT_TRUE(a != b);  // states differ

    (void)b();            // advance 'b' to catch up
    EXPECT_TRUE(a == b);  // states equal again
}
