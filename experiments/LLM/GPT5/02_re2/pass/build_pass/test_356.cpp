// File: regexp_numcaptures_test_356.cc

#include "gtest/gtest.h"
#include "re2/regexp.h"

#include <string>

using re2::Regexp;

namespace {

// Helper: parse with default/zero flags; treat nullptr status as acceptable per interface.
static Regexp* ParseOrNull(const std::string& pattern) {
  return Regexp::Parse(pattern, static_cast<Regexp::ParseFlags>(0), nullptr);
}

// Ensures we always Decref on scope exit.
struct RegexpHolder {
  Regexp* re{nullptr};
  explicit RegexpHolder(Regexp* r) : re(r) {}
  ~RegexpHolder() { if (re) re->Decref(); }
  Regexp* get() const { return re; }
};

}  // namespace

// Normal operation: no capturing groups -> 0
TEST(RegexpNumCapturesTest_356, NoCaptures_ReturnsZero_356) {
  RegexpHolder h(ParseOrNull("abc"));
  ASSERT_NE(nullptr, h.get()) << "Parse should succeed for a simple literal.";
  EXPECT_EQ(0, h.get()->NumCaptures());
}

// Normal operation: exactly one capture -> 1
TEST(RegexpNumCapturesTest_356, SingleCapture_ReturnsOne_356) {
  RegexpHolder h(ParseOrNull("(abc)"));
  ASSERT_NE(nullptr, h.get()) << "Parse should succeed for a single capture.";
  EXPECT_EQ(1, h.get()->NumCaptures());
}

// Nested and multiple captures -> total count across the whole pattern
TEST(RegexpNumCapturesTest_356, MultipleAndNestedCaptures_ReturnsThree_356) {
  RegexpHolder h(ParseOrNull("(a)(b(c))"));
  ASSERT_NE(nullptr, h.get()) << "Parse should succeed for multiple/nested captures.";
  EXPECT_EQ(3, h.get()->NumCaptures());
}

// Boundary/scale: many captures -> count matches the number created
TEST(RegexpNumCapturesTest_356, ManyCaptures_StressCount_356) {
  const int N = 50;  // choose a moderate stress size; adjust if the environment prefers smaller
  std::string pattern;
  pattern.reserve(static_cast<size_t>(N) * 2 + 2);
  for (int i = 0; i < N; ++i) pattern.push_back('(');
  pattern.push_back('a');
  for (int i = 0; i < N; ++i) pattern.push_back(')');

  RegexpHolder h(ParseOrNull(pattern));
  ASSERT_NE(nullptr, h.get()) << "Parse should succeed for many sequential capturing groups.";
  EXPECT_EQ(N, h.get()->NumCaptures());
}

// Edge case: empty pattern -> 0 captures
TEST(RegexpNumCapturesTest_356, EmptyPattern_ReturnsZero_356) {
  RegexpHolder h(ParseOrNull(""));
  ASSERT_NE(nullptr, h.get()) << "Empty pattern should parse (implementation-defined), but if it does, it has 0 captures.";
  EXPECT_EQ(0, h.get()->NumCaptures());
}

// Error case (observable at the Parse boundary): malformed pattern fails to parse
// Verifies we don't attempt to call NumCaptures on a null Regexp*.
TEST(RegexpNumCapturesTest_356, InvalidPattern_ParseFails_356) {
  Regexp* raw = ParseOrNull("(");  // unbalanced '('
  // Intentionally do not wrap in RegexpHolder; there's nothing to Decref when null.
  EXPECT_EQ(nullptr, raw) << "Malformed pattern should fail to parse and return nullptr.";
  // No call to NumCaptures() here because there is no valid Regexp instance.
}

