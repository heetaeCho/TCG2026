// File: tests/get_seed_tests_352.cpp
#include <gtest/gtest.h>
#include <cstdint>
#include <type_traits>
#include <set>
#include <limits>

// Include the header that declares getSeed().
// If there is no dedicated header, include the TU that provides it,
// or the smallest header that exposes Catch::Generators::Detail::getSeed().
namespace Catch { namespace Generators { namespace Detail {
    std::uint32_t getSeed();
}}}

using Catch::Generators::Detail::getSeed;

class GetSeedTest_352 : public ::testing::Test {};

// Verifies the return type and basic callability (observable type behavior).
TEST_F(GetSeedTest_352, ReturnsUint32Type_352) {
    auto value = getSeed();
    // Compile-time type check expressed at runtime for GTest reporting
    EXPECT_TRUE((std::is_same<decltype(value), std::uint32_t>::value))
        << "getSeed() must return std::uint32_t";
}

// Verifies successive calls are usable and (probabilistically) not all identical.
// We do not assume any specific RNG algorithm; we only check that across
// a small sample there is some variation (observable behavior).
TEST_F(GetSeedTest_352, MultipleCallsShowVariation_352) {
    constexpr int kSamples = 32;
    std::set<std::uint32_t> seen;
    for (int i = 0; i < kSamples; ++i) {
        seen.insert(getSeed());
    }
    // It's possible (but extremely unlikely) that all 32 are equal in a proper RNG.
    // If the implementation returned a constant, this would reliably fail.
    EXPECT_GT(static_cast<int>(seen.size()), 1)
        << "Expected some variation across multiple getSeed() calls";
}

// Verifies values are within the representable range of uint32_t.
// (This is tautological given the return type, but it documents the contract.)
TEST_F(GetSeedTest_352, ValuesWithinUint32Limits_352) {
    constexpr int kSamples = 16;
    for (int i = 0; i < kSamples; ++i) {
        std::uint32_t v = getSeed();
        EXPECT_LE(v, std::numeric_limits<std::uint32_t>::max());
        // No lower-bound check needed; uint32_t cannot be negative.
    }
}

// Smoke test: repeated calls should not throw or crash (observable stability).
TEST_F(GetSeedTest_352, StressCallDoesNotThrow_352) {
    constexpr int kSamples = 10000; // modest to keep tests quick
    for (int i = 0; i < kSamples; ++i) {
        (void)getSeed();
    }
    SUCCEED() << "Repeated getSeed() calls completed without error";
}
