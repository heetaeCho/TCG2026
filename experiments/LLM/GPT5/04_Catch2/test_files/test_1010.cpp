// File: tests/testspec_getinvalidspecs_1010.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <vector>

// Prefer the amalgamated header when available in your tree.
// If you use non-amalgamated builds, include <catch2/catch_test_spec.hpp> instead.
#include <catch_amalgamated.hpp>

using Catch::TestSpec;

namespace {

class TestSpec_GetInvalidSpecs_1010 : public ::testing::Test {};

// [Normal operation] Default-constructed TestSpec exposes an empty list of invalid specs.
TEST_F(TestSpec_GetInvalidSpecs_1010, DefaultIsEmpty_1010) {
    TestSpec spec;
    const auto& invalid = spec.getInvalidSpecs();
    EXPECT_TRUE(invalid.empty());
    EXPECT_EQ(invalid.size(), 0u);
}

// [Interface contract] The return type must be a const reference (compile-time checks).
TEST_F(TestSpec_GetInvalidSpecs_1010, ReturnsConstReferenceType_1010) {
    TestSpec spec;
    // Type trait checks only (do not rely on private state).
    using Ret = decltype(spec.getInvalidSpecs());
    static_assert(std::is_reference<Ret>::value, "getInvalidSpecs must return a reference");
    using Bare = std::remove_reference_t<Ret>;
    static_assert(std::is_const<Bare>::value, "getInvalidSpecs must return a const reference");
    // Also ensure it refers to a vector of strings (as per public alias/signature).
    // We avoid exact internal alias names; only check it's a vector-like of std::string.
    static_assert(std::is_same<Bare, const std::vector<std::string>>::value,
                  "getInvalidSpecs should expose const std::vector<std::string>");
    SUCCEED();
}

// [Reference stability] Multiple calls on the same object return the same underlying reference.
TEST_F(TestSpec_GetInvalidSpecs_1010, SameReferenceOnRepeatedCalls_1010) {
    TestSpec spec;
    auto const* first_addr  = &spec.getInvalidSpecs();
    auto const* second_addr = &spec.getInvalidSpecs();
    EXPECT_EQ(first_addr, second_addr);
}

// [Independence] Different objects should not alias each other's invalid-specs container.
TEST_F(TestSpec_GetInvalidSpecs_1010, DifferentInstancesHaveDifferentContainers_1010) {
    TestSpec a;
    TestSpec b;
    auto const* a_addr = &a.getInvalidSpecs();
    auto const* b_addr = &b.getInvalidSpecs();
    EXPECT_NE(a_addr, b_addr);
    EXPECT_TRUE(a.getInvalidSpecs().empty());
    EXPECT_TRUE(b.getInvalidSpecs().empty());
}

// [Boundary / object semantics] getInvalidSpecs remains valid after copy and move operations.
TEST_F(TestSpec_GetInvalidSpecs_1010, ValidAfterCopyAndMove_1010) {
    TestSpec original;

    // Copy construction
    TestSpec copy = original;
    EXPECT_TRUE(copy.getInvalidSpecs().empty());
    // The copy should have its own container address (no aliasing to original expected).
    EXPECT_NE(&original.getInvalidSpecs(), &copy.getInvalidSpecs());

    // Move construction
    TestSpec moved = std::move(copy);
    // Access must remain valid and (observably) empty.
    EXPECT_TRUE(moved.getInvalidSpecs().empty());

    // Copy assignment
    TestSpec other;
    other = original;
    EXPECT_TRUE(other.getInvalidSpecs().empty());

    // Move assignment
    TestSpec another;
    another = std::move(other);
    EXPECT_TRUE(another.getInvalidSpecs().empty());
}

} // namespace
