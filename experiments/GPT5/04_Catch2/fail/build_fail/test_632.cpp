// File: colour_guard_engage_tests_632.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <sstream>
#include <utility>

// Include the real header from your codebase
#include "catch2/internal/catch_console_colour.hpp"

namespace {

using Catch::ColourImpl;
using Guard = Catch::ColourImpl::ColourGuard;

// --- Detection utilities (interface-only checks) ---

// Detect if engage is invocable on an rvalue (should be false due to '&' qualifier)
template <typename T, typename = void>
struct is_engage_invocable_on_rvalue : std::false_type {};

template <typename T>
struct is_engage_invocable_on_rvalue<
    T,
    std::void_t<decltype(std::declval<T&&>().engage(std::declval<std::ostream&>()))>
> : std::true_type {};

// --- Compile-time interface conformance tests ---

// Ensure the return type is exactly Guard& when called on an lvalue.
static_assert(
    std::is_same<
        decltype(std::declval<Guard&>().engage(std::declval<std::ostream&>())),
        Guard&
    >::value,
    "ColourGuard::engage(std::ostream&) must return ColourGuard& when called on an lvalue."
);

// Ensure engage cannot be called on an rvalue (because of the '&' qualifier).
static_assert(
    !is_engage_invocable_on_rvalue<Guard>::value,
    "ColourGuard::engage(std::ostream&) should NOT be invocable on an rvalue (must be lvalue-qualified '&')."
);

// --- Runtime behavior tests (black-box, observable via public API) ---

// Helper to make a guard with minimal assumptions about internals.
// We use a default-initialized Colour::Code and a nullptr ColourImpl*,
// which is acceptable at the type level and doesn't rely on internal state.
inline Guard make_guard() {
    return Guard(typename Colour::Code{}, /*colourImpl*/ static_cast<const ColourImpl*>(nullptr));
}

// 1) ReturnsSelf_632: engage returns a reference to the same object (chainable API behavior).
TEST(ColourGuard_632, ReturnsSelf_632) {
    auto guard = make_guard();
    std::ostringstream os;

    Guard& ret = guard.engage(os);
    EXPECT_EQ(&ret, &guard) << "engage(os) should return *this as an lvalue reference.";
}

// 2) ChainableCallsReturnSameObject_632: Multiple engages chain and keep returning the same object.
TEST(ColourGuard_632, ChainableCallsReturnSameObject_632) {
    auto guard = make_guard();
    std::ostringstream os;

    Guard& after_first = guard.engage(os);
    EXPECT_EQ(&after_first, &guard);

    Guard& after_second = guard.engage(os).engage(os);
    EXPECT_EQ(&after_second, &guard) << "Chained engage calls should continue to return *this.";
}

// 3) MoveConstructedObject_EngageReturnsSelf_632: After move-construction, engage still returns that object's reference.
TEST(ColourGuard_632, MoveConstructedObject_EngageReturnsSelf_632) {
    auto original = make_guard();
    Guard moved(std::move(original));
    std::ostringstream os;

    Guard& ret = moved.engage(os);
    EXPECT_EQ(&ret, &moved) << "After move-construction, engage(os) should return the moved-to object.";
}

// 4) CompileTime_RvalueInvocationIsIllFormed_632: Defensive check mirrored at runtime via constexpr boolean.
//    (The actual enforcement is done by the static_assert above; this is a redundant, readable guard.)
TEST(ColourGuard_632, CompileTime_RvalueInvocationIsIllFormed_632) {
    constexpr bool can_call_on_rvalue = is_engage_invocable_on_rvalue<Guard>::value;
    EXPECT_FALSE(can_call_on_rvalue)
        << "engage(std::ostream&) must not be callable on rvalues (it is '&'-qualified).";
}

} // namespace
