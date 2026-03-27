// File: catch_result_type_or_operator_test_62.cpp

#include <type_traits>
#include <gtest/gtest.h>

// Include the header under test (path based on the partial code)
#include "catch2/internal/catch_result_type.hpp"

using Catch::ResultDisposition;

namespace {

// A tiny helper to make values readable in assertions without
// depending on specific numeric constants.
constexpr int ToInt(ResultDisposition::Flags f) {
    return static_cast<int>(f);
}

} // namespace

// Verifies the operator returns the correct type and can be used in constexpr context
TEST(CatchResultDispositionOr_62, TypeAndConstexpr_62) {
    // Pick two distinct flags from the interface
    constexpr ResultDisposition::Flags A = ResultDisposition::ContinueOnFailure;
    constexpr ResultDisposition::Flags B = ResultDisposition::FalseTest;

    // The expression must be constexpr and of the same enum type
    constexpr auto combined = (A | B);
    static_assert(std::is_same<decltype(combined), ResultDisposition::Flags>::value,
                  "operator| must return ResultDisposition::Flags");

    // Ensure it actually produces some value at compile time
    constexpr int combined_int = ToInt(combined);
    (void)combined_int; // silence unused warning in some build modes
}

// Commutativity: A | B == B | A
TEST(CatchResultDispositionOr_62, Commutative_62) {
    const auto A = ResultDisposition::ContinueOnFailure;
    const auto B = ResultDisposition::FalseTest;

    EXPECT_EQ(ToInt(A | B), ToInt(B | A));
}

// Idempotence: A | A == A
TEST(CatchResultDispositionOr_62, Idempotent_62) {
    const auto A = ResultDisposition::SuppressFail;

    EXPECT_EQ(ToInt(A | A), ToInt(A));
}

// Identity element (Normal): A | Normal == A and Normal | A == A
TEST(CatchResultDispositionOr_62, IdentityWithNormal_62) {
    const auto A = ResultDisposition::ContinueOnFailure;
    const auto Normal = ResultDisposition::Normal;

    EXPECT_EQ(ToInt(A | Normal), ToInt(A));
    EXPECT_EQ(ToInt(Normal | A), ToInt(A));
}

// Associativity: (A | B) | C == A | (B | C)
TEST(CatchResultDispositionOr_62, Associative_62) {
    const auto A = ResultDisposition::ContinueOnFailure;
    const auto B = ResultDisposition::FalseTest;
    const auto C = ResultDisposition::SuppressFail;

    const auto left  = ToInt((A | B) | C);
    const auto right = ToInt(A | (B | C));

    EXPECT_EQ(left, right);
}

// Observable bit-combination behavior without assuming specific numeric values
TEST(CatchResultDispositionOr_62, CombinesDistinctFlags_62) {
    const auto A = ResultDisposition::ContinueOnFailure;
    const auto B = ResultDisposition::FalseTest;

    const int ai = ToInt(A);
    const int bi = ToInt(B);
    const int ci = ToInt(A | B);

    // The integer representation of the result must match bitwise-or of the integer representations
    EXPECT_EQ(ci, (ai | bi));

    // And it should differ from each input when A and B are distinct
    EXPECT_NE(ci, ai);
    EXPECT_NE(ci, bi);
}

// Chaining multiple flags yields the same as int-level OR (observable via casting)
TEST(CatchResultDispositionOr_62, ChainsMatchIntegerOr_62) {
    const auto A = ResultDisposition::ContinueOnFailure;
    const auto B = ResultDisposition::FalseTest;
    const auto C = ResultDisposition::SuppressFail;

    const int combined_flags = ToInt(A | B | C);
    const int combined_ints  = (ToInt(A) | ToInt(B) | ToInt(C));

    EXPECT_EQ(combined_flags, combined_ints);
}
