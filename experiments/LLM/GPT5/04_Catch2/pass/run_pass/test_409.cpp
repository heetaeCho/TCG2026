// tests/optional_deref_409_test.cpp
#include <gtest/gtest.h>
#include <string>
#include "catch2/internal/catch_optional.hpp"

using Catch::Optional;

class OptionalTest_409 : public ::testing::Test {};

// Normal operation: dereference returns a T& and reflects mutations
TEST_F(OptionalTest_409, DereferenceReturnsReferenceAndMutates_409) {
    Optional<int> opt{42};
    int& ref = *opt;            // must be a reference to the contained value
    EXPECT_EQ(ref, 42);
    ref = 77;                   // mutate through the reference
    EXPECT_EQ(*opt, 77);        // subsequent dereference sees the mutation
    EXPECT_TRUE(opt.some());
    EXPECT_TRUE(static_cast<bool>(opt));
}

// Boundary: dereferencing after move construction (moved-from source is unspecified-through-interface;
// we only assert that the moved-to, if engaged, dereferences correctly)
TEST_F(OptionalTest_409, DereferenceAfterMoveConstruction_409) {
    Optional<std::string> src{std::string("hi")};
    Optional<std::string> dst{std::move(src)};
    // We only test the observable state of dst via operator*.
    // If dst is engaged, *dst must equal the original value.
    if (dst) {
        EXPECT_EQ(*dst, "hi");
        // Mutate through operator* and observe via operator* again
        *dst = "changed";
        EXPECT_EQ(*dst, "changed");
    }
    // No assertions about src (black-box rule).
}

// Normal operation with user-defined type: verify we can modify fields via operator*
struct Point409 {
    int x{0};
    int y{0};
};

TEST_F(OptionalTest_409, DereferenceAllowsMemberMutation_409) {
    Optional<Point409> p{Point409{1, 2}};
    Point409& ref = *p;
    EXPECT_EQ(ref.x, 1);
    EXPECT_EQ(ref.y, 2);

    ref.x = 10;
    ref.y = 20;
    // Observe through another dereference (no internal access)
    EXPECT_EQ((*p).x, 10);
    EXPECT_EQ((*p).y, 20);
}

// Exceptional/error-like observable behavior: dereferencing an empty Optional should assert in debug.
// We gate this with NDEBUG so it only runs when assertions are active.
#ifndef NDEBUG
TEST_F(OptionalTest_409, DereferenceEmptyCausesDebugAssert_409) {
    Optional<int> opt;   // default-constructed: empty
    // Expect a death due to assert failure when dereferencing an empty Optional.
    // We don't depend on the specific assert message; regex ".*" is sufficient.
    ASSERT_DEATH( (void)*opt, ".*" );
}

TEST_F(OptionalTest_409, DereferenceAfterResetCausesDebugAssert_409) {
    Optional<int> opt{5};
    opt.reset();
    ASSERT_DEATH( (void)*opt, ".*" );
}
#endif
