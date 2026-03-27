// File: optional_operator_arrow_tests_410.cpp
#include <gtest/gtest.h>
#include <string>

// Include the header under test (adjust include path as needed)
#include "Catch2/src/catch2/internal/catch_optional.hpp"

namespace {

using Catch::Optional;

// A small helper type to verify member access & mutation via operator->.
struct Widget {
    int v{0};
    void inc() { ++v; }
};

} // namespace

// -----------------------------------------------------------------------------
// Normal operation: operator-> returns a usable pointer to the contained value.
// -----------------------------------------------------------------------------
TEST(OptionalOperatorArrowTest_410, ReturnsPointerToContainedObject_410) {
    Optional<std::string> opt{std::string("abc")};

    // Can access members via -> (observable behavior).
    EXPECT_EQ(opt->size(), 3u);

    // Pointer identity should match the address of the dereferenced value.
    // (Uses only public interface: operator* and operator->.)
    EXPECT_EQ(opt.operator->(), &(*opt));
}

// -----------------------------------------------------------------------------
// Normal operation: mutating through the pointer affects the contained value.
// -----------------------------------------------------------------------------
TEST(OptionalOperatorArrowTest_410, MutationThroughPointerReflectsInValue_410) {
    Optional<Widget> opt{Widget{}};

    // Mutate through -> and verify via operator* (public API only).
    opt->inc();
    opt->inc();
    EXPECT_EQ((*opt).v, 2);
}

// -----------------------------------------------------------------------------
// Error case (debug builds): calling operator-> on an empty Optional should
// trigger the internal assertion. We check this with a death test in non-NDEBUG.
// -----------------------------------------------------------------------------
#ifndef NDEBUG
TEST(OptionalOperatorArrowTest_410, OperatorArrowOnEmptyTriggersAssert_410) {
    Optional<int> opt; // default-constructed: disengaged/empty

    // Directly invoking operator->() should trip the assertion in debug builds.
    // We do not depend on the exact message; checking that it aborts is enough.
    EXPECT_DEATH(
        (void)opt.operator->(),  // just invoke; we don't access a member
        ".*"
    );
}
#endif
