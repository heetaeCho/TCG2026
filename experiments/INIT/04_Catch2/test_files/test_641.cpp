// File: tests/simplepcg32_test_641.cpp
#include <gtest/gtest.h>
#include <vector>
#include <cstdint>

// Adjust include path as needed to where your header lives
#include "catch2/internal/catch_random_number_generator.hpp"

using Catch::SimplePcg32;

namespace {

class SimplePcg32Test_641 : public ::testing::Test {
protected:
    // Helper: produce first n outputs from a given generator (by value)
    static std::vector<SimplePcg32::result_type> generateN(SimplePcg32 gen, size_t n) {
        std::vector<SimplePcg32::result_type> out;
        out.reserve(n);
        for (size_t i = 0; i < n; ++i) {
            out.push_back(gen());
        }
        return out;
    }
};

} // namespace

// Normal operation: default-constructed generators produce identical deterministic sequences
TEST_F(SimplePcg32Test_641, DefaultConstructorsYieldSameSequence_641) {
    SimplePcg32 a;        // default seed (as defined by the interface)
    SimplePcg32 b;        // another default instance

    const auto va = generateN(a, 8);
    const auto vb = generateN(b, 8);

    EXPECT_EQ(va, vb);
}

// Normal operation: seeding to the same value yields identical sequences
TEST_F(SimplePcg32Test_641, SameSeedYieldsSameSequence_641) {
    const SimplePcg32::result_type seed = 123456789u;

    SimplePcg32 a(seed);
    SimplePcg32 b(seed);

    const auto va = generateN(a, 8);
    const auto vb = generateN(b, 8);

    EXPECT_EQ(va, vb);
}

// Boundary-ish/variety: different seeds should (with overwhelming likelihood) diverge quickly
TEST_F(SimplePcg32Test_641, DifferentSeedsUsuallyYieldDifferentSequence_641) {
    SimplePcg32 a(1u);
    SimplePcg32 b(2u);

    const auto va = generateN(a, 8);
    const auto vb = generateN(b, 8);

    // We don't assert any specific numbers; only that sequences are not identical.
    // Collisions across 8 outputs are astronomically unlikely.
    EXPECT_NE(va, vb);
}

// Boundary condition: discard(0) should not change the sequence
TEST_F(SimplePcg32Test_641, DiscardZeroDoesNotAdvance_641) {
    const SimplePcg32::result_type seed = 0x42u;

    SimplePcg32 a(seed);
    SimplePcg32 b(seed);

    a.discard(0);

    // After discard(0), next result must match the other instance's first result
    EXPECT_EQ(a(), b());
}

// Normal operation: discard(k) skips exactly k draws
TEST_F(SimplePcg32Test_641, DiscardSkipsExactlyKDraws_641) {
    const SimplePcg32::result_type seed = 777u;
    const uint64_t k = 5;

    SimplePcg32 a(seed);
    SimplePcg32 b(seed);

    // Advance b by k draws (to simulate discarding)
    for (uint64_t i = 0; i < k; ++i) {
        (void)b();
    }

    a.discard(k);

    // Now both should be at the same position; next draws equal
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(a(), b());
    }
}

// Normal operation: seeding after some draws resets the sequence to match a freshly seeded generator
TEST_F(SimplePcg32Test_641, ReseedResetsSequence_641) {
    const SimplePcg32::result_type seed = 0xDEADBEEFu;

    SimplePcg32 a(seed);
    // advance a a bit
    (void)a(); (void)a(); (void)a();

    // reseed
    a.seed(seed);

    SimplePcg32 fresh(seed);

    // After reseed, sequences must match again
    for (int i = 0; i < 6; ++i) {
        EXPECT_EQ(a(), fresh());
    }
}

// Range contract: values produced fall within [min(), max()]
TEST_F(SimplePcg32Test_641, OutputsWithinMinMaxRange_641) {
    SimplePcg32 gen;

    const auto lo = SimplePcg32::min();
    const auto hi = SimplePcg32::max();

    ASSERT_LE(lo, hi) << "min() must be <= max()";

    for (int i = 0; i < 16; ++i) {
        const auto v = gen();
        EXPECT_LE(lo, v);
        EXPECT_LE(v, hi);
    }
}

// Equality/inequality observable behavior: identical states compare equal; diverged states compare not equal
// (Interface exposes equality; we only check its externally-visible contract.)
TEST_F(SimplePcg32Test_641, EqualityAndInequalityReflectState_641) {
    const SimplePcg32::result_type seed = 2024u;

    SimplePcg32 a(seed);
    SimplePcg32 b(seed);

    // Initially equal
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);

    // Advance one generator; they should diverge
    (void)a();
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);

    // Bring b to the same state using discard(1)
    b.discard(1);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

