// File: regexp_op_test_149.cc

#include <gtest/gtest.h>
#include "re2/regexp.h"
#include "re2/regexp_status.h"

using re2::Regexp;
using re2::RegexpStatus;
using re2::RegexpOp;

namespace {

// Helper: parse a pattern into a Regexp*, returning nullptr on failure.
// Uses minimal flags (0) to avoid assuming specific flag names.
Regexp* ParsePattern(absl::string_view pattern, RegexpStatus* status) {
  // Avoid assuming any particular ParseFlags enumerator names:
  auto flags = static_cast<Regexp::ParseFlags>(0);
  return Regexp::Parse(pattern, flags, status);
}

// Convenience RAII to ensure Decref is called when needed.
struct RegexpHolder {
  Regexp* re;
  explicit RegexpHolder(Regexp* r) : re(r) {}
  ~RegexpHolder() {
    if (re) re->Decref();
  }
  // Non-copyable
  RegexpHolder(const RegexpHolder&) = delete;
  RegexpHolder& operator=(const RegexpHolder&) = delete;
  // Movable
  RegexpHolder(RegexpHolder&& other) noexcept : re(other.re) { other.re = nullptr; }
  RegexpHolder& operator=(RegexpHolder&& other) noexcept {
    if (this != &other) {
      if (re) re->Decref();
      re = other.re;
      other.re = nullptr;
    }
    return *this;
  }
};

}  // namespace

// --- Normal operation: literal ---
TEST(RegexpOpTest_149, OpReturnsLiteralForSingleChar_149) {
  RegexpStatus status;
  RegexpHolder h(ParsePattern("a", &status));
  ASSERT_NE(h.re, nullptr) << status.Text();
  // Expect the top-level op to represent a literal.
  EXPECT_EQ(h.re->op(), RegexpOp::kRegexpLiteral);
}

// --- Normal operation: unary ops (*, +, ?) ---
TEST(RegexpOpTest_149, OpReturnsStarForKleeneStar_149) {
  RegexpStatus status;
  RegexpHolder h(ParsePattern("a*", &status));
  ASSERT_NE(h.re, nullptr) << status.Text();
  EXPECT_EQ(h.re->op(), RegexpOp::kRegexpStar);
}

TEST(RegexpOpTest_149, OpReturnsPlusForOneOrMore_149) {
  RegexpStatus status;
  RegexpHolder h(ParsePattern("a+", &status));
  ASSERT_NE(h.re, nullptr) << status.Text();
  EXPECT_EQ(h.re->op(), RegexpOp::kRegexpPlus);
}

TEST(RegexpOpTest_149, OpReturnsQuestForZeroOrOne_149) {
  RegexpStatus status;
  RegexpHolder h(ParsePattern("a?", &status));
  ASSERT_NE(h.re, nullptr) << status.Text();
  EXPECT_EQ(h.re->op(), RegexpOp::kRegexpQuest);
}

// --- Normal operation: concat & alternation ---
TEST(RegexpOpTest_149, OpReturnsConcatForAdjacentLiterals_149) {
  RegexpStatus status;
  RegexpHolder h(ParsePattern("ab", &status));
  ASSERT_NE(h.re, nullptr) << status.Text();
  EXPECT_EQ(h.re->op(), RegexpOp::kRegexpConcat);
}

TEST(RegexpOpTest_149, OpReturnsAlternateForPipe_149) {
  RegexpStatus status;
  RegexpHolder h(ParsePattern("a|b", &status));
  ASSERT_NE(h.re, nullptr) << status.Text();
  EXPECT_EQ(h.re->op(), RegexpOp::kRegexpAlternate);
}

// --- Normal operation: capture group ---
TEST(RegexpOpTest_149, OpReturnsCaptureForParenthesized_149) {
  RegexpStatus status;
  RegexpHolder h(ParsePattern("(a)", &status));
  ASSERT_NE(h.re, nullptr) << status.Text();
  EXPECT_EQ(h.re->op(), RegexpOp::kRegexpCapture);
}

// --- Normal operation: bounded repeat {m,n} ---
TEST(RegexpOpTest_149, OpReturnsRepeatForBoundedQuantifier_149) {
  RegexpStatus status;
  RegexpHolder h(ParsePattern("a{2,3}", &status));
  ASSERT_NE(h.re, nullptr) << status.Text();
  EXPECT_EQ(h.re->op(), RegexpOp::kRegexpRepeat);
}

// --- Boundary/Exceptional: invalid pattern should not produce a Regexp ---
TEST(RegexpOpTest_149, ParseInvalidPatternReturnsNull_149) {
  RegexpStatus status;
  Regexp* re = ParsePattern("(", &status);
  EXPECT_EQ(re, nullptr);
  // Status text should be available for diagnostics (observable via interface).
  EXPECT_NE(std::string(status.Text()).size(), 0u);
}

// --- Stability: refcount ops should not affect op() ---
TEST(RegexpOpTest_149, OpIsStableAcrossIncrefDecref_149) {
  RegexpStatus status;
  RegexpHolder h(ParsePattern("ab|c", &status));
  ASSERT_NE(h.re, nullptr) << status.Text();

  const RegexpOp before = h.re->op();

  // Incref returns the same pointer (per signature), and we balance with Decref.
  Regexp* same = h.re->Incref();
  ASSERT_EQ(same, h.re);
  // After incref, op must remain the same (observable behavior).
  EXPECT_EQ(h.re->op(), before);

  // Balance the extra ref.
  h.re->Decref();
  // Still alive because holder has one ref; op remains the same.
  EXPECT_EQ(h.re->op(), before);
}

