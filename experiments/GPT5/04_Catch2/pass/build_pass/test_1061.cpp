// File: tests/random_floating_generator_tests_1061.cpp

#include <gtest/gtest.h>

// Headers under test
#include "catch2/generators/catch_generators_random.hpp"

using Catch::Generators::RandomFloatingGenerator;

namespace {

// Helper: check value in [lo, hi] (inclusive on both ends for boundary sanity).
template <typename T>
static void expect_in_closed_range(const T& v, const T& lo, const T& hi) {
    EXPECT_LE(lo, v);
    EXPECT_LE(v, hi);
}

} // namespace

// --- Normal operation: values remain within [a, b], and next() indicates progress (observable via return value).
TEST(RandomFloatingGeneratorTest_1061, ValuesStayWithinRange_Double_1061) {
    const double a = -1.5;
    const double b =  2.5;
    const std::uint32_t seed = 123u;

    RandomFloatingGenerator<double> gen(a, b, seed);

    // Initial value should be in range
    expect_in_closed_range(gen.get(), a, b);

    // Multiple next() calls should keep values in range
    for (int i = 0; i < 100; ++i) {
        // We only assert on the observable contract: next() returns a bool and get() is within [a,b].
        // (We do not assume finiteness.)
        bool cont = gen.next();
        (void)cont; // Presence/boolean is observable; exact meaning is class-defined.
        expect_in_closed_range(gen.get(), a, b);
    }
}

// --- Boundary condition: a == b must always produce that exact value.
TEST(RandomFloatingGeneratorTest_1061, DegenerateRange_AlwaysReturnsEndpoint_1061) {
    const double a = 3.141592653589793;
    const std::uint32_t seed = 777u;

    RandomFloatingGenerator<double> gen(a, a, seed);

    // Initial value equals the only endpoint
    EXPECT_DOUBLE_EQ(gen.get(), a);

    // Repeated next() must keep returning the same endpoint
    for (int i = 0; i < 10; ++i) {
        bool cont = gen.next();
        (void)cont;
        EXPECT_DOUBLE_EQ(gen.get(), a);
    }
}

// --- Determinism (observable): same (a,b,seed) -> identical sequence of observable get()s.
TEST(RandomFloatingGeneratorTest_1061, SameSeedSameSequence_Double_1061) {
    const double a = 0.0;
    const double b = 1.0;
    const std::uint32_t seed = 42u;

    RandomFloatingGenerator<double> g1(a, b, seed);
    RandomFloatingGenerator<double> g2(a, b, seed);

    // Compare a reasonable prefix of the sequence, including initial get()
    for (int i = 0; i < 50; ++i) {
        EXPECT_DOUBLE_EQ(g1.get(), g2.get());
        bool c1 = g1.next();
        bool c2 = g2.next();
        // The boolean is observable; we only assert equality between the two generators.
        EXPECT_EQ(c1, c2);
    }
}

// --- Plausible divergence (observable): different seeds typically produce different sequences.
//     We only require "at least one difference" in the first K samples, to avoid relying on internals.
TEST(RandomFloatingGeneratorTest_1061, DifferentSeeds_DivergeEarly_Double_1061) {
    const double a = -10.0;
    const double b =  10.0;

    RandomFloatingGenerator<double> g1(a, b, /*seed*/ 111u);
    RandomFloatingGenerator<double> g2(a, b, /*seed*/ 222u);

    // Allow a few steps to detect a difference; if all equal, it’s extremely unlikely and indicates a problem.
    bool saw_difference = false;

    for (int i = 0; i < 50; ++i) {
        if (g1.get() != g2.get()) {
            saw_difference = true;
            break;
        }
        bool c1 = g1.next();
        bool c2 = g2.next();
        (void)c1; (void)c2;
    }
    EXPECT_TRUE(saw_difference);
}

// --- Long double specialization: constructor (per partial code) performs an initial next().
//     We only assert observable guarantees: values are in range and determinism holds with same seed.
TEST(RandomFloatingGeneratorTest_1061, LongDouble_InRange_And_SameSeedDeterminism_1061) {
    const long double a = static_cast<long double>(-0.25L);
    const long double b = static_cast<long double>( 0.75L);
    const std::uint32_t seed = 31415926u;

    RandomFloatingGenerator<long double> g1(a, b, seed);
    RandomFloatingGenerator<long double> g2(a, b, seed);

    // Initial value should be within [a, b]
    expect_in_closed_range<long double>(g1.get(), a, b);
    expect_in_closed_range<long double>(g2.get(), a, b);

    // Same-seed determinism across a prefix (including long double path)
    for (int i = 0; i < 40; ++i) {
        // Use EXPECT_EQ for long double by comparing exact representation here;
        // the generator/distribution in Catch2 is intended to be stable and deterministic.
        EXPECT_EQ(g1.get(), g2.get());
        bool c1 = g1.next();
        bool c2 = g2.next();
        EXPECT_EQ(c1, c2);
        expect_in_closed_range<long double>(g1.get(), a, b);
        expect_in_closed_range<long double>(g2.get(), a, b);
    }
}

// --- Smoke test on next()'s return type/consistency for long double specialization.
//     We only assert that it is callable repeatedly and returns a bool; values remain in range.
TEST(RandomFloatingGeneratorTest_1061, LongDouble_NextIsCallableAndKeepsRange_1061) {
    const long double a = 1.0L;
    const long double b = 2.0L;
    const std::uint32_t seed = 999u;

    RandomFloatingGenerator<long double> gen(a, b, seed);

    expect_in_closed_range<long double>(gen.get(), a, b);

    for (int i = 0; i < 64; ++i) {
        bool cont = gen.next();
        // We don't rely on the meaning of 'cont', just that it's a bool and next() is callable.
        (void)cont;
        expect_in_closed_range<long double>(gen.get(), a, b);
    }
}
