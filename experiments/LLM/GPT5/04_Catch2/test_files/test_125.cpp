// File: test_binaryexpr_le_chaining_125.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

// Include the header under test
#include "catch2/internal/catch_decomposer.hpp"

// ---- Detection utilities (C++20 'requires' for clean, non-instantiating checks) ----
template <typename E, typename T>
concept HasLeChain =
    requires(E e, T t) {
        // Forming the expression must be invalid for the interface to meet its contract.
        // This 'requires' only checks expression formation; it won't execute anything.
        { (e <= t) };
    };

// Overload-address detection (non-idiomatic in real code, but useful for interface validation)
template <typename E>
concept HasLeOperatorAddressable = requires {
    // Taking the address of a templated operator if it were viable.
    // This should be ill-formed for the interface as given.
    &E::template operator<=;
};

// ---- Test suite ----

class BinaryExprTest_125 : public ::testing::Test {};

// 1) The chained <= expression should NOT be formable
//    This asserts that attempting to form `e <= t` is rejected at the interface level.
TEST_F(BinaryExprTest_125, ChainedLessEqualIsNotFormable_125) {
    // We only rely on the public signature existence. We do not re-implement any logic.
    // If the interface blocks chained comparisons (as intended), HasLeChain will be false.
    static_assert(!HasLeChain<Catch::BinaryExpr, int>,
                  "Chained <= on Catch::BinaryExpr must not be a valid expression.");
    SUCCEED(); // If we compiled to here, the compile-time assertion passed.
}

// 2) The operator template should not be directly “addressable” by user code
//    This helps ensure there is no viable overload for external use.
TEST_F(BinaryExprTest_125, OperatorTemplateNotAddressable_125) {
    static_assert(!HasLeOperatorAddressable<Catch::BinaryExpr>,
                  "operator<= should not be directly addressable/viable.");
    SUCCEED();
}

// 3) Header presence / basic ODR-use sanity: we can name the type without constructing it.
//    (We do not access any private state or assume constructibility.)
TEST_F(BinaryExprTest_125, CanReferenceTypeWithoutInstantiation_125) {
    // Just ensure the type name is usable in a harmless context (e.g., pointer declaration).
    Catch::BinaryExpr* maybe_ptr = nullptr;
    (void)maybe_ptr;
    SUCCEED();
}
