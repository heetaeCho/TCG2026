// poppler-get-version-test_2598.cc
//
// Unit tests for poppler_get_version() in ./TestProjects/poppler/glib/poppler.cc
//
// Constraints honored:
// - Treat implementation as black box (only observable behavior via public interface).
// - No private/internal state access.
// - No re-implementation of internal logic.
// - Google Mock not needed (no collaborators/callbacks).
//
// NOTE: We only assert properties that are observable and stable given the interface:
// - returns a non-null C string
// - content matches expected version string (from provided dependency info)
// - repeated calls are consistent
// - returned pointer is stable across calls (observable; does not require knowing storage)
//
// If your build system already provides a public header for poppler_get_version(),
// include it instead of forward-declaring below.

#include <gtest/gtest.h>

#include <cstring>

// Forward declaration (prefer including the real public header if available).
extern "C" {
const char* poppler_get_version(void);
}

namespace {

class PopplerGetVersionTest_2598 : public ::testing::Test {};

TEST_F(PopplerGetVersionTest_2598, ReturnsNonNullCStr_2598) {
  const char* v = poppler_get_version();
  ASSERT_NE(v, nullptr);
  // A basic sanity check that it's a valid C string (has a terminator).
  // strlen will crash if not terminated; this is an observable safety check.
  EXPECT_GE(std::strlen(v), 1u);
}

TEST_F(PopplerGetVersionTest_2598, ReturnsExpectedVersionString_2598) {
  const char* v = poppler_get_version();
  ASSERT_NE(v, nullptr);
  EXPECT_STREQ(v, "26.01.90");
}

TEST_F(PopplerGetVersionTest_2598, RepeatedCallsReturnSameContent_2598) {
  const char* v1 = poppler_get_version();
  const char* v2 = poppler_get_version();
  ASSERT_NE(v1, nullptr);
  ASSERT_NE(v2, nullptr);

  EXPECT_STREQ(v1, v2);
}

TEST_F(PopplerGetVersionTest_2598, PointerIsStableAcrossCalls_2598) {
  // Boundary/behavioral check: the returned pointer identity stays the same across calls.
  // This is an observable behavior expectation for a version getter that returns a static string.
  const char* v1 = poppler_get_version();
  const char* v2 = poppler_get_version();
  ASSERT_NE(v1, nullptr);
  ASSERT_NE(v2, nullptr);

  EXPECT_EQ(v1, v2);
}

TEST_F(PopplerGetVersionTest_2598, ReturnedStringLooksLikeDottedNumericVersion_2598) {
  // A light-format check (still black-box): digits and dots only, and contains at least one dot.
  const char* v = poppler_get_version();
  ASSERT_NE(v, nullptr);

  bool has_dot = false;
  for (const char* p = v; *p; ++p) {
    if (*p == '.') {
      has_dot = true;
      continue;
    }
    EXPECT_TRUE(*p >= '0' && *p <= '9') << "Unexpected character in version: '" << *p << "'";
  }
  EXPECT_TRUE(has_dot);
}

}  // namespace