// File: tostring_appendccrange_test.cc

#include <gtest/gtest.h>
#include <string>

// --- Minimal collaborator declarations to compile the target code ---
namespace re2 {
// RE2 commonly uses Rune as an integer type; we only need it to compile & pass values.
using Rune = int;

// Forward declare the external collaborator that AppendCCRange calls.
// We'll provide a test double below.
void AppendCCChar(std::string* t, Rune r);
}  // namespace re2

// --- Include the target implementation so the internal-linkage function is visible here ---
#include "TestProjects/re2/re2/tostring.cc"

// --- Test double for the external collaborator + simple observability hooks ---
namespace re2 {
namespace {
static int g_append_cc_char_calls = 0;
}  // namespace

void AppendCCChar(std::string* t, Rune r) {
  ++g_append_cc_char_calls;
  // Deterministic, easily-assertable encoding for the rune value.
  t->append("[" + std::to_string(r) + "]");
}

// Helper to reset the call counter between tests.
static void ResetCounters() { g_append_cc_char_calls = 0; }
static int Calls() { return g_append_cc_char_calls; }
}  // namespace re2

// -------------------- Tests --------------------

TEST(AppendCCRangeTest_229, LoGreaterThanHi_NoChange_NoCalls_229) {
  using namespace re2;
  std::string s = "X";
  ResetCounters();

  AppendCCRange(&s, /*lo=*/5, /*hi=*/3);

  EXPECT_EQ(s, "X");                  // No modification
  EXPECT_EQ(Calls(), 0);              // Collaborator not invoked
}

TEST(AppendCCRangeTest_229, LoEqualsHi_AppendsSingleChar_NoDash_229) {
  using namespace re2;
  std::string s;
  ResetCounters();

  AppendCCRange(&s, /*lo=*/7, /*hi=*/7);

  EXPECT_EQ(s, "[7]");                // Single AppendCCChar, no '-'
  EXPECT_EQ(Calls(), 1);
}

TEST(AppendCCRangeTest_229, LoLessThanHi_AppendsBoth_WithDashBetween_229) {
  using namespace re2;
  std::string s;
  ResetCounters();

  AppendCCRange(&s, /*lo=*/10, /*hi=*/20);

  EXPECT_EQ(s, "[10]-[20]");          // Format: low, '-', high (as produced by mock)
  EXPECT_EQ(Calls(), 2);
}

TEST(AppendCCRangeTest_229, AppendsToExistingContent_DoesNotOverwrite_229) {
  using namespace re2;
  std::string s = "PRE:";
  ResetCounters();

  AppendCCRange(&s, /*lo=*/1, /*hi=*/1);

  EXPECT_EQ(s, "PRE:[1]");            // Appends after existing content
  EXPECT_EQ(Calls(), 1);
}

TEST(AppendCCRangeTest_229, HandlesNegativeAndZeroBounds_AsValuesPassedThrough_229) {
  using namespace re2;
  std::string s;
  ResetCounters();

  AppendCCRange(&s, /*lo=*/-1, /*hi=*/0);

  // The hyphen between range endpoints is distinct from the '-' in "-1".
  EXPECT_EQ(s, "[-1]-[0]");
  EXPECT_EQ(Calls(), 2);
}
