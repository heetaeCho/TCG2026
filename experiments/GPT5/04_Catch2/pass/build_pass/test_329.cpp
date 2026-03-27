// File: simple_pcg32_tests_329.cpp
#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <utility>
#include <vector>

#include "Catch2/src/catch2/internal/catch_random_number_generator.hpp"

namespace {

using Rng = Catch::SimplePcg32;
using result_t =
    std::remove_cv_t<std::remove_reference_t<decltype(std::declval<Rng&>()())>>;

// Helper: collect n outputs from a copy of rng (does not mutate original)
static std::vector<result_t> Collect(Rng rng, std::size_t n) {
    std::vector<result_t> out;
    out.reserve(n);
    for (std::size_t i = 0; i < n; ++i) out.push_back(rng());
    return out;
}

} // namespace

// --- Normal operation: max() contract ---
TEST(SimplePcg32Test_329, MaxIsNumericLimitsMax_329) {
    // Verify max() matches the full-range max of the result type
    EXPECT_EQ(Rng::max(), std::numeric_limits<result_t>::max());
}

// --- Normal operation: determinism with same seed ---
TEST(SimplePcg32Test_329, SameSeedYieldsIdenticalSequence_329) {
    const result_t seed = static_cast<result_t>(123456u);

    Rng a; a.seed(seed);
    Rng b; b.seed(seed);

    constexpr std::size_t kCount = 16;
    auto seqA = Collect(a, kCount);
    auto seqB = Collect(b, kCount);

    EXPECT_EQ(seqA, seqB);
}

// --- Normal operation: default constructor equivalence to documented default seed ---
TEST(SimplePcg32Test_329, DefaultCtorMatchesDefaultSeedConstant_329) {
    // Based on the provided interface snippet, default-ctor uses 0xed743cc4U
    const result_t defaultSeed = static_cast<result_t>(0xed743cc4U);

    Rng def;            // default constructed
    Rng seeded; seeded.seed(defaultSeed);

    constexpr std::size_t kCount = 8;
    auto seqDef   = Collect(def, kCount);
    auto seqSeeded= Collect(seeded, kCount);

    EXPECT_EQ(seqDef, seqSeeded);
}

// --- Boundary-ish behavior: different seeds should (very likely) differ ---
TEST(SimplePcg32Test_329, DifferentSeedsLikelyDifferentFirstValue_329) {
    Rng a; a.seed(static_cast<result_t>(1u));
    Rng b; b.seed(static_cast<result_t>(2u));

    auto firstA = a();
    auto firstB = b();
    // Not a proof, but a strong observable indicator of seeding effect
    EXPECT_NE(firstA, firstB);
}

// --- Observable skipping: discard(n) equals consuming n values ---
TEST(SimplePcg32Test_329, DiscardSkipsExactlyNOutputs_329) {
    const result_t seed = static_cast<result_t>(42u);
    constexpr uint64_t kSkip = 5;

    Rng base; base.seed(seed);
    Rng skip; skip.seed(seed);

    // Advance 'base' by kSkip calls
    for (uint64_t i = 0; i < kSkip; ++i) (void)base();

    // Discard kSkip in the other instance
    skip.discard(kSkip);

    // Next value must match
    EXPECT_EQ(base(), skip());
}

// --- Equality / inequality reflect observable state progress ---
TEST(SimplePcg32Test_329, EqualityTracksStateProgress_329) {
    const result_t seed = static_cast<result_t>(777u);

    Rng a; a.seed(seed);
    Rng b; b.seed(seed);

    // Initially equal
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);

    // Advance one generator
    (void)a();

    // Now states should differ
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a == b);

    // Bring b to the same point
    (void)b();

    // Equal again
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}
