// File: regexp_runes_test_160.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"

namespace {

using re2::Regexp;
using re2::Rune;
using re2::kRegexpLiteralString;

using PF = Regexp::ParseFlags;  // zero is acceptable for default flags

// Helper to create a LiteralString Regexp while respecting possible ownership
// semantics of the 'runes' buffer (pass heap memory and let Regexp manage it).
static Regexp* MakeLiteralString(const std::vector<Rune>& vals) {
  Rune* buf = nullptr;
  int n = static_cast<int>(vals.size());
  if (n > 0) {
    buf = new Rune[n];
    for (int i = 0; i < n; ++i) buf[i] = vals[i];
  }
  return Regexp::LiteralString(buf, n, static_cast<PF>(0));
}

// --- Normal behavior ---

TEST(RegexpRunesTest_160, LiteralString_ReturnsRunesAndCount_160) {
  std::vector<Rune> input = { 'a', 'b', 'c' };
  Regexp* re = MakeLiteralString(input);
  ASSERT_NE(re, nullptr);

  // Observable behavior via public interface.
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), static_cast<int>(input.size()));

  Rune* p = re->runes();
  ASSERT_NE(p, nullptr);
  for (int i = 0; i < re->nrunes(); ++i) {
    EXPECT_EQ(p[i], input[i]) << "Mismatch at index " << i;
  }

  re->Decref();
}

TEST(RegexpRunesTest_160, PointerStableAcrossCalls_160) {
  std::vector<Rune> input = { 'x', 'y' };
  Regexp* re = MakeLiteralString(input);
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(re->op(), kRegexpLiteralString);

  Rune* p1 = re->runes();
  Rune* p2 = re->runes();
  EXPECT_EQ(p1, p2);  // Calling runes() repeatedly should be idempotent.

  re->Decref();
}

// --- Boundary conditions ---

TEST(RegexpRunesTest_160, UnicodeRunesPreserved_160) {
  // Use a non-BMP code point (e.g., U+1F600 GRINNING FACE) to ensure wide-rune handling.
  std::vector<Rune> input = { static_cast<Rune>(0x1F600) };
  Regexp* re = MakeLiteralString(input);
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(re->op(), kRegexpLiteralString);
  ASSERT_EQ(re->nrunes(), 1);
  ASSERT_NE(re->runes(), nullptr);
  EXPECT_EQ(re->runes()[0], static_cast<Rune>(0x1F600));

  re->Decref();
}

TEST(RegexpRunesTest_160, ZeroLengthHasZeroNrunes_160) {
  // Empty literal string: passing nullptr with length 0 must be handled via interface.
  Regexp* re = Regexp::LiteralString(nullptr, 0, static_cast<PF>(0));
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 0);

  // We do not assert on runes() nullability for the empty case—only that the call is valid.
  (void)re->runes();

  re->Decref();
}

// --- Exceptional / error case (observable via debug assertions) ---

#ifndef NDEBUG
TEST(RegexpRunesTest_160, RunesOnNonLiteralStringTriggersDCHECK_160) {
  // Create a non-literal-string regexp (a single literal rune, not a string).
  Regexp* non_string = Regexp::NewLiteral(static_cast<Rune>('q'), static_cast<PF>(0));
  ASSERT_NE(non_string, nullptr);
  ASSERT_NE(non_string->op(), kRegexpLiteralString);

  // Accessing runes() violates the documented precondition and should trigger ABSL_DCHECK in debug.
  EXPECT_DEATH(
      {
        // The call below should hit the debug check.
        (void)non_string->runes();
      },
      "");  // Match any death message.

  non_string->Decref();
}
#endif  // NDEBUG

}  // namespace
