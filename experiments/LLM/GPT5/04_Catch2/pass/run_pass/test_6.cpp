// StringRef_operator_index_tests_6.cpp
// Tests only observable behavior of Catch::StringRef::operator[]
// No reliance on private state or internal implementation details.

#include <gtest/gtest.h>
#include <string>

// Adjust include path as appropriate for your project
#include "Catch2/src/catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

// --- Compile-time checks (interface-only) ------------------------------------

// operator[] is declared constexpr & noexcept, so it should be usable in a
// constant-evaluation context and be non-throwing.
namespace {
constexpr StringRef kConstexprRef("abc", 3);
static_assert(kConstexprRef[0] == 'a', "operator[] must return correct char");
static_assert(kConstexprRef[1] == 'b', "operator[] must return correct char");
static_assert(noexcept(kConstexprRef[0]),
              "operator[] must be noexcept per interface");
} // namespace

// --- Runtime tests -----------------------------------------------------------

TEST(StringRefIndexTest_6, ReturnsCorrectCharsWithinBounds_6) {
    StringRef r("hello", 5);
    EXPECT_EQ(r[0], 'h');
    EXPECT_EQ(r[1], 'e');
    EXPECT_EQ(r[2], 'l');
    EXPECT_EQ(r[3], 'l');
    EXPECT_EQ(r[4], 'o');
}

TEST(StringRefIndexTest_6, BoundaryIndices_6) {
    StringRef r("xyz", 3);
    // First element
    EXPECT_EQ(r[0], 'x');
    // Last element
    EXPECT_EQ(r[2], 'z');
}

TEST(StringRefIndexTest_6, WorksWithStdStringSource_6) {
    std::string s = "world";
    StringRef r(s); // interface provides std::string ctor
    EXPECT_EQ(r[0], 'w');
    EXPECT_EQ(r[4], 'd');
}

// Death tests verify the interface's documented/observable debug-time assert
// on out-of-range access. Skip when assertions are disabled (NDEBUG) or when
// death tests are not available on the platform/toolchain.
TEST(StringRefIndexTest_6, OutOfRangeAccessTriggersAssert_6) {
#if defined(NDEBUG)
    GTEST_SKIP() << "Assertions disabled (NDEBUG defined); skipping death test.";
#else
#  if GTEST_HAS_DEATH_TEST
    StringRef r("abc", 3);
    // Index == size is out of range
    EXPECT_DEATH((void)r[3], ".*");
    // Index > size is also out of range
    EXPECT_DEATH((void)r[100], ".*");
#  else
    GTEST_SKIP() << "GTest death tests not supported on this platform.";
#  endif
#endif
}

TEST(StringRefIndexTest_6, EmptyStringAnyAccessTriggersAssert_6) {
#if defined(NDEBUG)
    GTEST_SKIP() << "Assertions disabled (NDEBUG defined); skipping death test.";
#else
#  if GTEST_HAS_DEATH_TEST
    StringRef empty; // default-constructed empty StringRef per interface
    EXPECT_DEATH((void)empty[0], ".*");
#  else
    GTEST_SKIP() << "GTest death tests not supported on this platform.";
#  endif
#endif
}
