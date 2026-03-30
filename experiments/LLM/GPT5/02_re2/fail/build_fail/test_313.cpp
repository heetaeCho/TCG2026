// File: re2_compiler_addrunerange_test_313.cc

#include <gtest/gtest.h>
#include "re2/regexp.h"
#include "re2/re2.h"

// The partial impl & known deps place Compiler in namespace re2 and expose the
// following public members used here:
//   - void BeginRange();
//   - void AddRuneRange(Rune lo, Rune hi, bool foldcase);
//   - void AddRuneRangeUTF8(Rune lo, Rune hi, bool foldcase);
//   - void AddRuneRangeLatin1(Rune lo, Rune hi, bool foldcase);
//   - Frag EndRange();
//   - void Setup(Regexp::ParseFlags flags, int64_t max_mem, RE2::Anchor anchor);
//
// We do not assume anything about Frag's internals; we only require that the
// public pipeline calls do not crash and complete as expected.

namespace re2 {

class CompilerAddRuneRangeTest_313 : public ::testing::Test {
 protected:
  // Helper to initialize a fresh compiler with given flags/anchor.
  // We use a small max_mem since we add tiny ranges only.
  static void Init(Compiler* c,
                   Regexp::ParseFlags flags = Regexp::NoParseFlags,
                   RE2::Anchor anchor = RE2::UNANCHORED) {
    // Setup is public per the provided interface snippet.
    c->Setup(flags, /*max_mem=*/1 << 20, anchor);
  }
};

// ========== Normal operation (UTF-8 default) ==========

TEST_F(CompilerAddRuneRangeTest_313, UTF8_SimpleAsciiRange_NoThrow_313) {
  Compiler c;
  ASSERT_NO_FATAL_FAILURE(Init(&c, Regexp::NoParseFlags, RE2::UNANCHORED));

  // Begin → AddRuneRange (dispatch to UTF-8 per default) → End
  ASSERT_NO_FATAL_FAILURE(c.BeginRange());
  ASSERT_NO_THROW(c.AddRuneRange('a', 'z', /*foldcase=*/false));
  // EndRange should be callable safely; we don't peek into Frag internals.
  ASSERT_NO_THROW((void)c.EndRange());
}

TEST_F(CompilerAddRuneRangeTest_313, UTF8_SingleRune_NoThrow_313) {
  Compiler c;
  ASSERT_NO_FATAL_FAILURE(Init(&c));

  ASSERT_NO_FATAL_FAILURE(c.BeginRange());
  ASSERT_NO_THROW(c.AddRuneRange('X', 'X', /*foldcase=*/false));
  ASSERT_NO_THROW((void)c.EndRange());
}

TEST_F(CompilerAddRuneRangeTest_313, UTF8_Foldcase_True_NoThrow_313) {
  Compiler c;
  ASSERT_NO_FATAL_FAILURE(Init(&c));

  ASSERT_NO_FATAL_FAILURE(c.BeginRange());
  ASSERT_NO_THROW(c.AddRuneRange('a', 'f', /*foldcase=*/true));
  ASSERT_NO_THROW((void)c.EndRange());
}

// ========== Boundary conditions on runes (UTF-8) ==========

TEST_F(CompilerAddRuneRangeTest_313, UTF8_MinBoundary_Zero_NoThrow_313) {
  Compiler c;
  ASSERT_NO_FATAL_FAILURE(Init(&c));

  ASSERT_NO_FATAL_FAILURE(c.BeginRange());
  ASSERT_NO_THROW(c.AddRuneRange(0x0000, 0x0000, /*foldcase=*/false));
  ASSERT_NO_THROW((void)c.EndRange());
}

TEST_F(CompilerAddRuneRangeTest_313, UTF8_MaxBoundary_10FFFF_NoThrow_313) {
  Compiler c;
  ASSERT_NO_FATAL_FAILURE(Init(&c));

  ASSERT_NO_FATAL_FAILURE(c.BeginRange());
  ASSERT_NO_THROW(c.AddRuneRange(0x10FFFF, 0x10FFFF, /*foldcase=*/false));
  ASSERT_NO_THROW((void)c.EndRange());
}

TEST_F(CompilerAddRuneRangeTest_313, UTF8_WideRange_ASCIItoBMP_NoThrow_313) {
  Compiler c;
  ASSERT_NO_FATAL_FAILURE(Init(&c));

  ASSERT_NO_FATAL_FAILURE(c.BeginRange());
  ASSERT_NO_THROW(c.AddRuneRange(0x0020, 0x07FF, /*foldcase=*/false));
  ASSERT_NO_THROW((void)c.EndRange());
}

// ========== Latin-1 dispatch path ==========

TEST_F(CompilerAddRuneRangeTest_313, Latin1_SimpleRange_NoThrow_313) {
  Compiler c;
  // Use Latin1 parse flag to drive encoding selection through the public Setup.
  ASSERT_NO_FATAL_FAILURE(Init(&c, Regexp::Latin1, RE2::UNANCHORED));

  ASSERT_NO_FATAL_FAILURE(c.BeginRange());
  // 0x00A0..0x00FF is inside Latin-1 upper block; ensure call path remains safe.
  ASSERT_NO_THROW(c.AddRuneRange(0x00A0, 0x00FF, /*foldcase=*/false));
  ASSERT_NO_THROW((void)c.EndRange());
}

TEST_F(CompilerAddRuneRangeTest_313, Latin1_SingleRune_Foldcase_True_NoThrow_313) {
  Compiler c;
  ASSERT_NO_FATAL_FAILURE(Init(&c, Regexp::Latin1));

  ASSERT_NO_FATAL_FAILURE(c.BeginRange());
  ASSERT_NO_THROW(c.AddRuneRange(0x00C5 /* Å */, 0x00C5, /*foldcase=*/true));
  ASSERT_NO_THROW((void)c.EndRange());
}

// ========== Direct helpers are callable (public API surface) ==========
// These DO NOT infer internal logic; they only validate that the public helper
// entry points themselves accept inputs and complete without crashing.

TEST_F(CompilerAddRuneRangeTest_313, DirectUTF8Helper_Callable_NoThrow_313) {
  Compiler c;
  ASSERT_NO_FATAL_FAILURE(Init(&c));

  ASSERT_NO_FATAL_FAILURE(c.BeginRange());
  ASSERT_NO_THROW(c.AddRuneRangeUTF8('0', '9', /*foldcase=*/false));
  ASSERT_NO_THROW((void)c.EndRange());
}

TEST_F(CompilerAddRuneRangeTest_313, DirectLatin1Helper_Callable_NoThrow_313) {
  Compiler c;
  ASSERT_NO_FATAL_FAILURE(Init(&c));

  ASSERT_NO_FATAL_FAILURE(c.BeginRange());
  ASSERT_NO_THROW(c.AddRuneRangeLatin1(0x00E0 /* à */, 0x00E6 /* æ */, /*foldcase=*/false));
  ASSERT_NO_THROW((void)c.EndRange());
}

// ========== Degenerate / edge input handling (observable: no crash) ==========

TEST_F(CompilerAddRuneRangeTest_313, UTF8_Degenerate_LoGreaterThanHi_NoThrow_313) {
  Compiler c;
  ASSERT_NO_FATAL_FAILURE(Init(&c));

  ASSERT_NO_FATAL_FAILURE(c.BeginRange());
  // We do not assert on internal behavior, only that the call is safe.
  ASSERT_NO_THROW(c.AddRuneRange('z', 'a', /*foldcase=*/false));
  ASSERT_NO_THROW((void)c.EndRange());
}

TEST_F(CompilerAddRuneRangeTest_313, Latin1_Degenerate_LoGreaterThanHi_NoThrow_313) {
  Compiler c;
  ASSERT_NO_FATAL_FAILURE(Init(&c, Regexp::Latin1));

  ASSERT_NO_FATAL_FAILURE(c.BeginRange());
  ASSERT_NO_THROW(c.AddRuneRange(0x00FF, 0x00A0, /*foldcase=*/true));
  ASSERT_NO_THROW((void)c.EndRange());
}

}  // namespace re2
