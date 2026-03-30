// File: maybe_parse_perl_cc_escape_test_526.cc

#include <cstddef>
#include <string>

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"
#include "re2/regexp.h"

// Forward declarations to avoid depending on internal headers.
namespace re2 {
struct UGroup;  // opaque to tests
const UGroup* MaybeParsePerlCCEscape(absl::string_view* s,
                                     Regexp::ParseFlags parse_flags);
}  // namespace re2

using re2::Regexp;

class MaybeParsePerlCCEscapeTest_526 : public ::testing::Test {};

// [Normal] Recognized escape with PerlClasses flag: returns non-null and advances by 2.
TEST_F(MaybeParsePerlCCEscapeTest_526, ReturnsGroup_AndAdvancesInput_OnValidEscape_526) {
  absl::string_view sv("\\dABC");
  const re2::UGroup* g = re2::MaybeParsePerlCCEscape(&sv, Regexp::PerlClasses);
  ASSERT_NE(g, nullptr);
  EXPECT_EQ(sv, "ABC");  // advanced exactly two chars
}

// [Boundary] Input is exactly two chars and valid: returns non-null and leaves empty remainder.
TEST_F(MaybeParsePerlCCEscapeTest_526, ValidEscape_ExactLengthTwo_LeavesEmptyInput_526) {
  absl::string_view sv("\\w");
  const re2::UGroup* g = re2::MaybeParsePerlCCEscape(&sv, Regexp::PerlClasses);
  ASSERT_NE(g, nullptr);
  EXPECT_TRUE(sv.empty());
}

// [Error/Flag] PerlClasses flag not set: returns null and does not advance.
TEST_F(MaybeParsePerlCCEscapeTest_526, ReturnsNull_WhenPerlClassesFlagNotSet_526) {
  absl::string_view sv("\\drest");
  absl::string_view original = sv;
  const re2::UGroup* g = re2::MaybeParsePerlCCEscape(&sv, Regexp::NoParseFlags);
  EXPECT_EQ(g, nullptr);
  EXPECT_EQ(sv, original);  // unchanged
}

// [Boundary] Input length < 2 (empty): returns null and does not advance.
TEST_F(MaybeParsePerlCCEscapeTest_526, ReturnsNull_WhenInputEmpty_526) {
  absl::string_view sv("");
  absl::string_view original = sv;
  const re2::UGroup* g = re2::MaybeParsePerlCCEscape(&sv, Regexp::PerlClasses);
  EXPECT_EQ(g, nullptr);
  EXPECT_EQ(sv, original);
}

// [Boundary] Input length == 1 and is backslash: returns null and does not advance.
TEST_F(MaybeParsePerlCCEscapeTest_526, ReturnsNull_WhenOnlyBackslash_526) {
  absl::string_view sv("\\");
  absl::string_view original = sv;
  const re2::UGroup* g = re2::MaybeParsePerlCCEscape(&sv, Regexp::PerlClasses);
  EXPECT_EQ(g, nullptr);
  EXPECT_EQ(sv, original);
}

// [Boundary] First char is not backslash: returns null and does not advance.
TEST_F(MaybeParsePerlCCEscapeTest_526, ReturnsNull_WhenNoLeadingBackslash_526) {
  absl::string_view sv("xY");
  absl::string_view original = sv;
  const re2::UGroup* g = re2::MaybeParsePerlCCEscape(&sv, Regexp::PerlClasses);
  EXPECT_EQ(g, nullptr);
  EXPECT_EQ(sv, original);
}

// [Error] Unknown two-char escape (e.g., "\q"): returns null and does not advance.
TEST_F(MaybeParsePerlCCEscapeTest_526, ReturnsNull_AndDoesNotAdvance_OnUnknownEscape_526) {
  absl::string_view sv("\\qZZ");
  absl::string_view original = sv;
  const re2::UGroup* g = re2::MaybeParsePerlCCEscape(&sv, Regexp::PerlClasses);
  EXPECT_EQ(g, nullptr);
  EXPECT_EQ(sv, original);
}
