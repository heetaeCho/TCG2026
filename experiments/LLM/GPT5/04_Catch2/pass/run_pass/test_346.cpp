// File: tests/random_floating_generator_test.cpp

#include <gtest/gtest.h>
#include <cstdint>

// Include the header under test (adjust the include path as needed for your tree)
#include "Catch2/src/catch2/generators/catch_generators_random.hpp"

using Catch::Generators::RandomFloatingGenerator;

namespace {

// Simple helper to assert a value is within [lo, hi], inclusive.
template <typename T>
void ExpectInRangeInclusive(const T& v, T lo, T hi) {
    EXPECT_LE(lo, v);
    EXPECT_LE(v, hi);
}

// ---------- Tests for RandomFloatingGenerator<float> ----------

TEST(RandomFloatingGeneratorTest_346, ReturnsValueWithinRangeOnConstruction_346) {
    const float lo = 0.0f, hi = 1.0f;
    RandomFloatingGenerator<float> gen(lo, hi, /*seed=*/123u);

    const float& v0 = gen.get();
    ExpectInRangeInclusive(v0, lo, hi);
}

TEST(RandomFloatingGeneratorTest_346, ValuesStayWithinRangeOverManyNext_346) {
    const float lo = -10.0f, hi = 10.0f;
    RandomFloatingGenerator<float> gen(lo, hi, /*seed=*/42u);

    // Check initial value
    ExpectInRangeInclusive(gen.get(), lo, hi);

    // Step through a number of values; regardless of next()’s return, get() must be in range.
    for (int i = 0; i < 100; ++i) {
        (void)gen.next();
        const float& v = gen.get();
        ExpectInRangeInclusive(v, lo, hi);
    }
}

TEST(RandomFloatingGeneratorTest_346, DeterministicGivenSeed_346) {
    const float lo = -3.5f, hi = 7.25f;
    constexpr std::uint32_t seed = 987654321u;

    RandomFloatingGenerator<float> genA(lo, hi, seed);
    RandomFloatingGenerator<float> genB(lo, hi, seed);

    // Same seed -> same first value
    EXPECT_FLOAT_EQ(genA.get(), genB.get());

    // After one advance, still identical sequences
    ASSERT_TRUE(genA.next() || true);  // we don't assert the boolean semantics; only that get() stays valid
    ASSERT_TRUE(genB.next() || true);
    EXPECT_FLOAT_EQ(genA.get(), genB.get());

    // After multiple advances, still identical
    for (int i = 0; i < 10; ++i) {
        (void)genA.next();
        (void)genB.next();
        EXPECT_FLOAT_EQ(genA.get(), genB.get());
    }
}

TEST(RandomFloatingGeneratorTest_346, DifferentSeedsProduceDifferentFirstValue_MostOfTheTime_346) {
    // This verifies a practical observable property (seed affects sequence).
    // Exact inequality is overwhelmingly likely for continuous distributions.
    const float lo = 1.0f, hi = 2.0f;

    RandomFloatingGenerator<float> gen1(lo, hi, /*seed=*/1u);
    RandomFloatingGenerator<float> gen2(lo, hi, /*seed=*/2u);

    // If these were ever exactly equal, that would be surprising and likely indicate a bug.
    EXPECT_NE(gen1.get(), gen2.get());
}

TEST(RandomFloatingGeneratorTest_346, GetReturnsStableReferenceWithoutNext_346) {
    const float lo = 0.0f, hi = 10.0f;
    RandomFloatingGenerator<float> gen(lo, hi, /*seed=*/123u);

    // Calling get() repeatedly without next() should refer to the same stored value.
    const float* p1 = &gen.get();
    const float* p2 = &gen.get();
    EXPECT_EQ(p1, p2);  // same object reference
}

TEST(RandomFloatingGeneratorTest_346, ZeroWidthRangeYieldsExactEndpoint_346) {
    const float k = 3.25f;
    RandomFloatingGenerator<float> gen(k, k, /*seed=*/999u);

    // With a == b, every observed value must be exactly that endpoint.
    EXPECT_FLOAT_EQ(gen.get(), k);
    for (int i = 0; i < 10; ++i) {
        (void)gen.next();
        EXPECT_FLOAT_EQ(gen.get(), k);
    }
}

// ---------- Tests for RandomFloatingGenerator<long double> specialization ----------

TEST(RandomFloatingGeneratorLongDoubleTest_346, ReturnsValueWithinRangeAndAdvances_346) {
    const long double lo = static_cast<long double>(-0.5L);
    const long double hi = static_cast<long double>(0.5L);
    RandomFloatingGenerator<long double> gen(lo, hi, /*seed=*/555u);

    const long double& v0 = gen.get();
    ExpectInRangeInclusive<long double>(v0, lo, hi);

    // Advance a few times; values must remain in range.
    for (int i = 0; i < 20; ++i) {
        (void)gen.next();
        const long double& v = gen.get();
        ExpectInRangeInclusive<long double>(v, lo, hi);
    }
}

TEST(RandomFloatingGeneratorLongDoubleTest_346, DeterministicGivenSeed_346) {
    const long double lo = 10.0L, hi = 12.0L;
    constexpr std::uint32_t seed = 20250828u;

    RandomFloatingGenerator<long double> a(lo, hi, seed);
    RandomFloatingGenerator<long double> b(lo, hi, seed);

    EXPECT_EQ(a.get(), b.get());
    for (int i = 0; i < 8; ++i) {
        (void)a.next();
        (void)b.next();
        EXPECT_EQ(a.get(), b.get());
    }
}

} // namespace
