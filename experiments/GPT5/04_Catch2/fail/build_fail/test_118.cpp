// File: test_binaryexpr_and_chaining_118.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

// The tests assume the header below is available on your include path,
// and we treat it as a black box per the constraints.
#include "catch2/internal/catch_decomposer.hpp"

// ----- Detection utilities (compile-time only, no logic reimplementation) -----

// Primary template: fallback = false (not detectable)
template <typename T, typename = void>
struct has_chain_and_118 : std::false_type {};

// Specialization tries to take the address of the operator&&<U> template.
// If it's well-formed, we detect "true"; otherwise substitution fails -> false.
// We don't evaluate any body logic; we only check if the specialization is
// detectable from the public signature.
template <typename T>
struct has_chain_and_118<
    T,
    std::void_t<decltype(&T::template operator&&<int>)>> : std::true_type {};

// Helper variable template
template <typename T>
inline constexpr bool has_chain_and_118_v = has_chain_and_118<T>::value;


// ------------------------------ TESTS ---------------------------------

// Note: TEST names include the TEST_ID (118) as required.

TEST(BinaryExpr_118, TypeIsUsableAsADeclaration_118) {
    // We should be able to refer to the type without instantiating operator bodies.
    // This merely verifies that the class name is visible and can be used in declarations.
    Catch::BinaryExpr* ptr = nullptr;
    (void)ptr;
    SUCCEED(); // If it compiles and runs, the declaration use is valid.
}

TEST(BinaryExpr_118, ChainingOperatorAndIsNotDetectable_118) {
    // We expect that trying to detect an address of operator&&<int> is *not* well-formed,
    // because the interface forbids chained comparisons inside assertions.
    // Thus the detection should be false.
    constexpr bool detectable = has_chain_and_118_v<Catch::BinaryExpr>;
    EXPECT_FALSE(detectable);
}

/*
  Notes:
  - We are not re-implementing any logic from Catch2. We only attempt to detect
    whether the public operator template can be addressed (i.e., whether chaining
    "&&" would be considered a valid callable target).
  - When Catch2 enforces "no chained comparisons" via a static_assert inside the
    operator&& template, forming its address should be ill-formed and fail SFINAE,
    making our trait evaluate to false (the expected behavior).
  - We avoid any assumptions about private state or internal buffers; tests focus
    solely on observable/compilability properties of the interface.
*/
