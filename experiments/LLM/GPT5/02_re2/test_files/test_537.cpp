// File: tolower_rune_test_537.cc
#include <gtest/gtest.h>

// --- Minimal shims & stubs so we can compile and observe behavior ---
namespace re2 {

// Match RE2's typical Rune usage for testing purposes.
using Rune = int;

// utf.h constants used by ToLowerRune logic.
enum { UTFmax = 4, Runesync = 128, Runeself = 128, Runeerror = 65533, Runemax = 1114111 };

// A minimal CaseFold with the fields referenced by the implementation.
struct CaseFold {
  int lo;       // lower bound threshold used by the implementation
  int delta;    // fold delta used by ApplyFold (test stub)
};

// Dummy global tables referenced by ToLowerRune (values unused by our stubbed Lookup).
const CaseFold unicode_tolower[] = {};
const int num_unicode_tolower = 0;

// --- Test doubles for external collaborators used by ToLowerRune ---

// Controls and observations for ApplyFold.
static int g_apply_called = 0;
static const CaseFold* g_apply_last_f = nullptr;
static Rune g_apply_last_r = -1;

// Stub: ApplyFold just returns r + f->delta and records the call.
static Rune ApplyFold(const CaseFold* f, Rune r) {
  ++g_apply_called;
  g_apply_last_f = f;
  g_apply_last_r = r;
  return r + (f ? f->delta : 0);
}

// Stub: LookupCaseFold returns different shapes based on r to cover branches.
static const CaseFold* LookupCaseFold(const CaseFold* /*table*/, int /*n*/, Rune r) {
  // Case 1: Return nullptr -> ToLowerRune should return r unchanged.
  if (r == 0x0220) return nullptr;

  // Case 2: Return f with lo greater than r -> ToLowerRune should return r unchanged.
  static const CaseFold kTooHighLo{0x0200, 5};
  if (r == 0x0180) return &kTooHighLo;

  // Case 3: Return f with lo <= r -> ToLowerRune should call ApplyFold.
  static const CaseFold kFoldMe{0x0100, 1};  // delta=1 so result should be r+1
  if (r == 0x0100) return &kFoldMe;

  // Default for other non-ASCII values: behave like nullptr (unchanged).
  return nullptr;
}

}  // namespace re2

// Include the implementation under test so the internal-linkage function is visible.
#include "re2/prefilter.cc"

namespace {

class ToLowerRuneTest_537 : public ::testing::Test {
 protected:
  void SetUp() override {
    re2::g_apply_called = 0;
    re2::g_apply_last_f = nullptr;
    re2::g_apply_last_r = -1;
  }
};

// ----------------------------- Tests ---------------------------------

// Normal operation: ASCII uppercase should map to lowercase.
TEST_F(ToLowerRuneTest_537, AsciiUppercaseToLowercase_537) {
  EXPECT_EQ(re2::ToLowerRune('A'), 'a');
  EXPECT_EQ(re2::ToLowerRune('Z'), 'z');
}

// Normal operation: ASCII lowercase is unchanged.
TEST_F(ToLowerRuneTest_537, AsciiLowercaseUnchanged_537) {
  EXPECT_EQ(re2::ToLowerRune('a'), 'a');
  EXPECT_EQ(re2::ToLowerRune('z'), 'z');
}

// Normal operation: Non-alpha ASCII remains unchanged.
TEST_F(ToLowerRuneTest_537, AsciiNonAlphaUnchanged_537) {
  EXPECT_EQ(re2::ToLowerRune('0'), '0');
  EXPECT_EQ(re2::ToLowerRune('@'), '@');  // before 'A'
}

// Boundary: r == Runeself - 1 stays on ASCII path.
TEST_F(ToLowerRuneTest_537, BoundaryRuneselfMinusOne_537) {
  EXPECT_EQ(re2::ToLowerRune(re2::Runeself - 1), re2::Runeself - 1);  // 127
}

// Boundary: r == Runeself enters Unicode path; with nullptr fold -> unchanged.
TEST_F(ToLowerRuneTest_537, BoundaryRuneselfUnicodePathNoFold_537) {
  // Our LookupCaseFold default returns nullptr for values we didn't special-case.
  const re2::Rune r = re2::Runeself;  // 128
  EXPECT_EQ(re2::ToLowerRune(r), r);
  EXPECT_EQ(re2::g_apply_called, 0) << "ApplyFold should not be called when LookupCaseFold returns nullptr";
}

// Exceptional/early-exit case observable through interface: LookupCaseFold == nullptr.
TEST_F(ToLowerRuneTest_537, Unicode_NoEntryReturnsInput_537) {
  const re2::Rune r = 0x0220;  // Stub returns nullptr
  EXPECT_EQ(re2::ToLowerRune(r), r);
  EXPECT_EQ(re2::g_apply_called, 0);
}

// Boundary condition in unicode path: f exists but r < f->lo -> return r.
TEST_F(ToLowerRuneTest_537, Unicode_FoundButBelowLoReturnsInput_537) {
  const re2::Rune r = 0x0180;  // Stub returns f with lo=0x0200 (> r)
  EXPECT_EQ(re2::ToLowerRune(r), r);
  EXPECT_EQ(re2::g_apply_called, 0);
}

// Verification of external interactions: when lo <= r, ApplyFold is invoked with expected args.
TEST_F(ToLowerRuneTest_537, Unicode_FoundAndAtOrAboveLoCallsApplyFold_537) {
  const re2::Rune r = 0x0100;  // Stub returns f with lo=0x0100 (<= r), delta=1
  const re2::Rune out = re2::ToLowerRune(r);

  EXPECT_EQ(out, r + 1) << "ApplyFold stub returns r + delta (delta=1)";
  ASSERT_EQ(re2::g_apply_called, 1);
  ASSERT_NE(re2::g_apply_last_f, nullptr);
  EXPECT_EQ(re2::g_apply_last_r, r);
}

}  // namespace
