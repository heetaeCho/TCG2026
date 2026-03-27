// File: cycle_fold_rune_test.cc

#include <gtest/gtest.h>

//
// We purposefully DO NOT include the production unicode_casefold header here.
// Instead, we provide minimal declarations that match the observable interface
// used by CycleFoldRune. We include parse.cc itself so it binds to our fakes.
//

namespace re2 {

// Public types / collaborators referenced by CycleFoldRune.
using Rune = int;  // Minimal alias sufficient for tests (observable: takes/returns integral)

// Minimal CaseFold shape with only what CycleFoldRune/ApplyFold touch.
struct CaseFold {
  int lo;        // lower bound used by CycleFoldRune's comparison
  int32_t delta; // present in the known deps; not used by these tests
};

// External collaborators & globals that CycleFoldRune calls/reads.
// We'll provide test doubles below.
extern const CaseFold* LookupCaseFold(const CaseFold* table, int n, Rune r);
extern Rune ApplyFold(const CaseFold* f, Rune r);

// Globals referenced by CycleFoldRune's callsite signature.
// We'll define them as controllable test fixtures.
extern const CaseFold* unicode_casefold;
extern int num_unicode_casefold;

} // namespace re2

// ---- Test doubles & controllable state ----
namespace {

using re2::CaseFold;
using re2::Rune;

static bool g_apply_called = false;
static const CaseFold* g_lookup_return = nullptr;
static CaseFold g_casefold_obj{0, 0};

// Define test-owned "table" and size observed by CycleFoldRune.
static const CaseFold* g_table_stub = &g_casefold_obj;
static int g_table_size_stub = 1;

} // namespace

namespace re2 {

// Provide definitions for the globals referenced by CycleFoldRune.
const CaseFold* unicode_casefold = g_table_stub;
int num_unicode_casefold = g_table_size_stub;

// Fake LookupCaseFold returns a controllable pointer set by tests.
const CaseFold* LookupCaseFold(const CaseFold* /*table*/, int /*n*/, Rune /*r*/) {
  return g_lookup_return;
}

// Fake ApplyFold records it was called and returns a controllable value
// based solely on inputs so tests can assert on the observable result.
Rune ApplyFold(const CaseFold* /*f*/, Rune r) {
  g_apply_called = true;
  // Return a deterministic, visible transformation for test assertions.
  return r + 123; // arbitrary, but observable
}

} // namespace re2

// Include the implementation under test so it binds to the above doubles.
#include "TestProjects/re2/re2/parse.cc"

// -------------------- Tests --------------------

struct CycleFoldRuneTest_486 : public ::testing::Test {
  void SetUp() override {
    g_apply_called = false;
    g_lookup_return = nullptr;
    g_casefold_obj.lo = 0;
    g_casefold_obj.delta = 0;
  }
};

// [Normal] If LookupCaseFold returns nullptr, CycleFoldRune must return input rune.
TEST_F(CycleFoldRuneTest_486, ReturnsInputWhenNoCaseFold_486) {
  g_lookup_return = nullptr; // simulate: no casefold entry for r

  re2::Rune r = 100;
  EXPECT_EQ(re2::CycleFoldRune(r), r);
  EXPECT_FALSE(g_apply_called) << "ApplyFold must not be called when no entry exists";
}

// [Boundary] If a casefold entry exists but r < f->lo, CycleFoldRune must return input rune.
TEST_F(CycleFoldRuneTest_486, ReturnsInputWhenRuneBelowLowerBound_486) {
  // Configure a fold entry with lo greater than r.
  g_casefold_obj.lo = 200;
  g_lookup_return = &g_casefold_obj;

  re2::Rune r = 199; // r < lo
  EXPECT_EQ(re2::CycleFoldRune(r), r);
  EXPECT_FALSE(g_apply_called) << "ApplyFold must not be called when r < f->lo";
}

// [Normal] If entry exists and r >= f->lo, ApplyFold should be used and its result returned.
TEST_F(CycleFoldRuneTest_486, AppliesFoldWhenEntryMatches_486) {
  // Ensure r >= lo
  g_casefold_obj.lo = 50;
  g_lookup_return = &g_casefold_obj;

  re2::Rune r = 123;             // r >= lo
  re2::Rune expected = r + 123;  // from our ApplyFold fake
  EXPECT_EQ(re2::CycleFoldRune(r), expected);
  EXPECT_TRUE(g_apply_called) << "ApplyFold must be called when entry matches";
}

// [Boundary] Works for small (0) rune value when entry requires folding.
TEST_F(CycleFoldRuneTest_486, AppliesFoldAtZeroRuneWhenEligible_486) {
  g_casefold_obj.lo = 0;     // allow folding at lower bound
  g_lookup_return = &g_casefold_obj;

  re2::Rune r = 0;
  EXPECT_EQ(re2::CycleFoldRune(r), r + 123);
  EXPECT_TRUE(g_apply_called);
}

// [Boundary] Works for a large rune value when entry requires folding.
TEST_F(CycleFoldRuneTest_486, AppliesFoldAtLargeRuneWhenEligible_486) {
  g_casefold_obj.lo = 1000;  // require r >= 1000
  g_lookup_return = &g_casefold_obj;

  re2::Rune r = 50000;       // clearly >= lo
  EXPECT_EQ(re2::CycleFoldRune(r), r + 123);
  EXPECT_TRUE(g_apply_called);
}
