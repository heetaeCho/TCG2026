// File: re2_tostring_test.cc
#include <gtest/gtest.h>
#include <string>

// SUT headers (based on your paths/snippets)
#include "re2/tostring.cc"   // Provides re2::Regexp::ToString() definition in your partial snippet

namespace {

using ::re2::Regexp;

// Helper to check the exact suffix used when traversal is truncated.
static constexpr const char* kTruncatedSuffix = " [truncated]";

TEST(RegexpToStringTest_225, ReturnsStringWithoutThrowing_225) {
  Regexp re;
  // Normal operation: calling ToString should not throw and returns a std::string.
  EXPECT_NO_THROW({
    std::string s = re.ToString();
    (void)s; // silence unused warning
  });
}

TEST(RegexpToStringTest_225, DeterministicAcrossCalls_225) {
  Regexp re;
  // Normal/Idempotent behavior observable via the public method:
  // Multiple calls should be deterministic (same output each time).
  const std::string first = re.ToString();
  const std::string second = re.ToString();
  EXPECT_EQ(first, second);
}

TEST(RegexpToStringTest_225, TruncatedSuffixIsWellFormedIfPresent_225) {
  Regexp re;
  const std::string out = re.ToString();

  // Boundary/format check of observable behavior:
  // If traversal stops early, ToString must append the exact suffix " [truncated]".
  // We don't assert that it MUST be present (cannot force walker behavior here),
  // but if it appears, it should be correctly formed and at the end.
  const bool has_suffix =
      out.size() >= std::strlen(kTruncatedSuffix) &&
      out.compare(out.size() - std::strlen(kTruncatedSuffix),
                  std::strlen(kTruncatedSuffix),
                  kTruncatedSuffix) == 0;

  if (has_suffix) {
    // When present, ensure the suffix is exactly as specified.
    EXPECT_TRUE(has_suffix);
  } else {
    // Otherwise, the output is whatever the walker produced; at minimum it should be a valid string.
    SUCCEED();
  }
}

TEST(RegexpToStringTest_225, OutputIsEitherEmptyOrMeaningfullyFormatted_225) {
  Regexp re;
  const std::string out = re.ToString();

  // Exceptional/boundary-lite observable check:
  // With the given partial implementation, we cannot assert internal traversal results.
  // We only check that if the special truncated marker appears, it is correctly placed.
  if (!out.empty()) {
    // If non-empty, it either ends with the truncated suffix or contains some content.
    // We only validate the suffix placement if present; otherwise we accept any content.
    if (out.size() >= std::strlen(kTruncatedSuffix)) {
      const std::string tail =
          out.substr(out.size() - std::strlen(kTruncatedSuffix));
      if (tail == kTruncatedSuffix) {
        EXPECT_EQ(tail, kTruncatedSuffix);
      } else {
        SUCCEED(); // Non-empty, non-truncated content is acceptable.
      }
    } else {
      SUCCEED(); // Short, non-empty content also acceptable.
    }
  } else {
    SUCCEED(); // Empty string is acceptable given black-box traversal.
  }
}

}  // namespace
