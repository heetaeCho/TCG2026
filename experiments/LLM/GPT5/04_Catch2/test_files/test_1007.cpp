// File: test_testspec_hasfilters_1007.cpp
#include <gtest/gtest.h>

#if __has_include("catch2/catch_test_spec.hpp")
  #include "catch2/catch_test_spec.hpp"
#elif __has_include("catch_amalgamated.hpp")
  // Some setups bundle everything into the amalgamated header
  #include "catch_amalgamated.hpp"
#else
  // Fallback: rely on the compilation environment to provide the header.
  // If neither header is available, this test will fail to compile by design,
  // because we must not re-implement or stub the class under test.
  #error "Catch2 TestSpec header not found. Include path missing?"
#endif

#include <type_traits>

using Catch::TestSpec;

// NOTE ABOUT SCOPE OF TESTS (per constraints):
// - We must treat TestSpec as a black box and only use public API.
// - The provided public API does not include any method to add filters;
//   constructing a TestSpec with filters appears to require TestSpecParser (a friend).
// - Therefore, we verify observable behavior for a default-constructed instance
//   and through copy/move/const object semantics. We do NOT access private state,
//   and we do NOT attempt to infer/replicate internal logic.

// -----------------------------
// Normal operation (empty/default)
// -----------------------------

TEST(TestSpec_HasFilters_EmptyDefault_1007, ReturnsFalseForNewObject_1007) {
    TestSpec spec; // default-constructed => observable state only via public API
    EXPECT_FALSE(spec.hasFilters()) << "Default-constructed TestSpec should report no filters";
}

// -----------------------------
// Object semantics (copy/move) — still observable via public API
// -----------------------------

TEST(TestSpec_HasFilters_CopySemantics_1007, CopyOfEmptyRemainsEmpty_1007) {
    TestSpec original;
    ASSERT_FALSE(original.hasFilters()) << "Precondition: original has no filters";

    TestSpec copy = original; // copy-construct
    EXPECT_FALSE(copy.hasFilters()) << "Copy should also report no filters (observable behavior)";
    // We do not assert anything about internals, only the public result.
}

TEST(TestSpec_HasFilters_MoveSemantics_1007, MoveOfEmptyRemainsEmpty_1007) {
    TestSpec original;
    ASSERT_FALSE(original.hasFilters()) << "Precondition: original has no filters";

    TestSpec moved = std::move(original);
    // Calling methods on a moved-from object is generally unspecified;
    // we only assert on the moved-to object (observable behavior).
    EXPECT_FALSE(moved.hasFilters()) << "Moved-to object should still report no filters";
}

// -----------------------------
// Const-correctness (boundary on cv-qualification)
// -----------------------------

TEST(TestSpec_HasFilters_ConstQualification_1007, CallableOnConstObject_1007) {
    const TestSpec specConst;
    // The function is declared const in the interface; verify it is callable and returns a bool result.
    EXPECT_FALSE(specConst.hasFilters()) << "Const TestSpec should report no filters by default";
}

// -----------------------------
// Type traits sanity checks (non-invasive; do not touch internals)
// -----------------------------

TEST(TestSpec_Traits_CompileTime_1007, IsCopyAndMoveConstructible_1007) {
    // These are compile-time properties and do not peek at private state.
    // They help document/verify expectations for typical value semantics.
    static_assert(std::is_copy_constructible<TestSpec>::value, "TestSpec should be copy-constructible");
    static_assert(std::is_move_constructible<TestSpec>::value, "TestSpec should be move-constructible");
    SUCCEED();
}
