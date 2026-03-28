// File: tests/colour_guard_move_assign_630.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <sstream>

// Include the public header that declares ColourImpl::ColourGuard
#include "catch2/internal/catch_console_colour.hpp"

using Catch::ColourImpl;
using Catch::Colour; // for Colour::Code

// Helper: pick arbitrary integral values for Colour::Code without relying on specific enumerators.
static constexpr Colour::Code kCodeA = static_cast<Colour::Code>(0);
static constexpr Colour::Code kCodeB = static_cast<Colour::Code>(1);
static constexpr Colour::Code kCodeC = static_cast<Colour::Code>(2);

// ----------------------
// Type trait expectations
// ----------------------

TEST(ColourGuardTest_630, MoveAssignableTraits_630) {
    // Move-assignable and nothrow as declared in the interface (noexcept)
    static_assert(std::is_move_assignable<ColourImpl::ColourGuard>::value,
                  "ColourGuard should be move-assignable");
    static_assert(std::is_nothrow_move_assignable<ColourImpl::ColourGuard>::value,
                  "ColourGuard move-assign must be noexcept");

    // Move-constructible is also present in interface
    static_assert(std::is_move_constructible<ColourImpl::ColourGuard>::value,
                  "ColourGuard should be move-constructible");

    // Copy operations are deleted in the interface
    static_assert(!std::is_copy_assignable<ColourImpl::ColourGuard>::value,
                  "ColourGuard should NOT be copy-assignable");
    static_assert(!std::is_copy_constructible<ColourImpl::ColourGuard>::value,
                  "ColourGuard should NOT be copy-constructible");
}

// --------------------------------------
// Return value and noexcept at expression
// --------------------------------------

TEST(ColourGuardTest_630, MoveAssignReturnsSelf_630) {
    ColourImpl::ColourGuard lhs(kCodeA, /*colourImpl*/ nullptr);
    ColourImpl::ColourGuard rhs(kCodeB, /*colourImpl*/ nullptr);

    // Verify the operator returns *this (lvalue ref to lhs)
    auto* ret = &(lhs = std::move(rhs));
    EXPECT_EQ(ret, &lhs);
}

TEST(ColourGuardTest_630, MoveAssignIsNoexceptAtExprLevel_630) {
    ColourImpl::ColourGuard a(kCodeA, nullptr);
    ColourImpl::ColourGuard b(kCodeB, nullptr);

    // Expression-level noexcept check (in addition to type trait above)
    EXPECT_TRUE(noexcept(a = std::move(b)));
}

// ------------------------------
// Self move-assign (edge case)
// ------------------------------

TEST(ColourGuardTest_630, SelfMoveAssignDoesNotThrowAndReturnsSelf_630) {
    ColourImpl::ColourGuard g(kCodeA, nullptr);

    // Self move-assignment should be well-defined (no-throw) and return self
    auto* ret = &(g = std::move(g));
    EXPECT_EQ(ret, &g);
    // No further checks on internal state (black-box constraint).
}

// -----------------------------------------
// Chained move-assignment returns lvalue ref
// -----------------------------------------

TEST(ColourGuardTest_630, ChainedMoveAssignmentReturnsLHS_630) {
    ColourImpl::ColourGuard a(kCodeA, nullptr);
    ColourImpl::ColourGuard b(kCodeB, nullptr);
    ColourImpl::ColourGuard c(kCodeC, nullptr);

    // Ensure the operator returns lvalue ref enabling chaining
    auto* ret = &((a = std::move(b)) = std::move(c));
    EXPECT_EQ(ret, &a);
}
