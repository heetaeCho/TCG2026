// File: tests/within_ulps_matcher_tests_1050.cpp

#include <gtest/gtest.h>
#include <limits>

// Include the matcher’s public interface
#include "Catch2/src/catch2/matchers/catch_matchers_floating_point.hpp"

namespace {

using Catch::Matchers::WithinUlpsMatcher;
using FPKind = Catch::Matchers::Detail::FloatingPointKind;

// -------------------------
// Constructor behavior only
// -------------------------

// Normal operation: constructing with Double should allow arbitrarily large ULPs.
TEST(WithinUlpsMatcherTest_1050, Double_AllowsVeryLargeUlps_1050) {
    const uint64_t huge = (std::numeric_limits<uint64_t>::max)();
    EXPECT_NO_THROW({
        WithinUlpsMatcher m(1.0, huge, FPKind::Double);
        (void)m;
    });
}

// Boundary: for Float, ULP must be strictly less than max(uint32_t).
TEST(WithinUlpsMatcherTest_1050, Float_UlpsJustBelowUint32Max_IsAllowed_1050) {
    const uint64_t allowed = (std::numeric_limits<uint32_t>::max)() - 1ull;
    EXPECT_NO_THROW({
        WithinUlpsMatcher m(0.0, allowed, FPKind::Float);
        (void)m;
    });
}

// Boundary: equal to max(uint32_t) should be rejected for Float.
TEST(WithinUlpsMatcherTest_1050, Float_UlpsAtUint32Max_IsRejected_1050) {
    const uint64_t disallowed = (std::numeric_limits<uint32_t>::max)();
    EXPECT_ANY_THROW({
        WithinUlpsMatcher m(0.0, disallowed, FPKind::Float);
        (void)m;
    });
}

// Error case: wildly large ULP for Float should be rejected.
TEST(WithinUlpsMatcherTest_1050, Float_VeryLargeUlps_IsRejected_1050) {
    const uint64_t huge = (std::numeric_limits<uint64_t>::max)();
    EXPECT_ANY_THROW({
        WithinUlpsMatcher m(123.456, huge, FPKind::Float);
        (void)m;
    });
}

// Platform constraint (IEEE-754): The constructor enforces that double is IEC559.
// We do NOT simulate any platform; instead we assert observable behavior conditionally.
TEST(WithinUlpsMatcherTest_1050, Ieee754_Requirement_IsEnforced_1050) {
    const bool isIeee754 = std::numeric_limits<double>::is_iec559;
    if (isIeee754) {
        // On IEEE-754 platforms, construction with valid params should succeed.
        EXPECT_NO_THROW({
            WithinUlpsMatcher m(1.0, 0ull, FPKind::Double);
            (void)m;
        });
    } else {
        // On non-IEEE-754 platforms, constructor enforces and should throw.
        EXPECT_ANY_THROW({
            WithinUlpsMatcher m(1.0, 0ull, FPKind::Double);
            (void)m;
        });
    }
}

} // namespace
