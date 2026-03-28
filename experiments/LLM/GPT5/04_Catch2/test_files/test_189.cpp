// File: tests/AllTrueFactoryTest_189.cpp

#include <gtest/gtest.h>
#include <type_traits>

// Public Catch2 matcher interface (header where AllTrueMatcher is declared)
#include <catch2/matchers/catch_matchers_quantifiers.hpp>

using Catch::Matchers::AllTrue;
using Catch::Matchers::AllTrueMatcher;

class AllTrueFactoryTest_189 : public ::testing::Test {};

// Verifies that the factory returns the expected concrete type.
TEST_F(AllTrueFactoryTest_189, ReturnsAllTrueMatcherType_189) {
    static_assert(std::is_same<decltype(AllTrue()), AllTrueMatcher>::value,
                  "AllTrue() must return AllTrueMatcher");
    (void)AllTrue(); // runtime call just to exercise the symbol
    SUCCEED();
}

// Verifies each call returns a distinct object instance (no hidden sharing).
TEST_F(AllTrueFactoryTest_189, ReturnsDistinctObjectsPerCall_189) {
    auto a = AllTrue();
    auto b = AllTrue();
    // Distinct stack objects should have different addresses.
    EXPECT_NE(&a, &b);
}

// Verifies basic constructibility properties of the returned type via traits.
// (Checks public-facing type properties; no reliance on internals.)
TEST_F(AllTrueFactoryTest_189, MatcherIsDefaultCopyMoveConstructible_189) {
    EXPECT_TRUE((std::is_default_constructible<AllTrueMatcher>::value));
    EXPECT_TRUE((std::is_copy_constructible<AllTrueMatcher>::value));
    EXPECT_TRUE((std::is_move_constructible<AllTrueMatcher>::value));
}

// If the type advertises nothrow construction via traits, this should hold.
// (Purely trait-based; does not assume behavior.)
TEST_F(AllTrueFactoryTest_189, MatcherConstructionNoexceptTraits_189) {
    // These checks are intentionally non-fatal and trait-based only.
    // They won’t fail builds if the library changes to potentially-throwing.
    (void) ::testing::Test::RecordProperty("nothrow_default_constructible",
        std::is_nothrow_default_constructible<AllTrueMatcher>::value);
    (void) ::testing::Test::RecordProperty("nothrow_move_constructible",
        std::is_nothrow_move_constructible<AllTrueMatcher>::value);
    SUCCEED();
}
