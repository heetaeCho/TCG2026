// File: re2_consumeN_test_254.cc

#include <gtest/gtest.h>
#include <string>
#include "absl/strings/string_view.h"

// Headers from the prompt
#include "re2.h"  // assumes it declares re2::RE2 and Anchor enum as shown

namespace re2 {

// ----- Minimal stubs to allow constructing RE2 and linking -----
// These do NOT implement internal logic; they only satisfy the linker
// so we can call the already-implemented RE2::ConsumeN under test.
RE2::RE2(const char* /*pattern*/) {}
RE2::RE2(const std::string& /*pattern*/) {}
RE2::RE2(absl::string_view /*pattern*/) {}
RE2::RE2(absl::string_view /*pattern*/, const RE2::Options& /*options*/) {}
RE2::~RE2() {}

// ----- Test seam for DoMatch -----
// We do not reimplement internal logic; we provide a controllable seam so we
// can verify the observable effects of ConsumeN (return value, input mutation,
// and parameters passed through to DoMatch).
static bool        g_DoMatchReturn         = false;
static size_t      g_DoMatchConsumed       = 0;
static const RE2::Arg* const* g_LastArgs   = nullptr;
static int         g_LastN                 = 0;
static absl::string_view g_LastText;
static RE2::Anchor g_LastAnchor;

// Define the (otherwise-unimplemented here) private member so tests can run.
bool RE2::DoMatch(absl::string_view text,
                  Anchor re_anchor,
                  size_t* consumed,
                  const Arg* const* args,
                  int n) const {
  g_LastText   = text;
  g_LastAnchor = re_anchor;
  g_LastArgs   = args;
  g_LastN      = n;
  if (consumed) *consumed = g_DoMatchConsumed;
  return g_DoMatchReturn;
}

}  // namespace re2

using re2::RE2;

class RE2_ConsumeNTest_254 : public ::testing::Test {
protected:
  void SetUp() override {
    // Reset seam state before each test
    re2::g_DoMatchReturn   = false;
    re2::g_DoMatchConsumed = 0;
    re2::g_LastArgs        = nullptr;
    re2::g_LastN           = 0;
    re2::g_LastText        = absl::string_view();
    re2::g_LastAnchor      = static_cast<re2::RE2::Anchor>(-1);
  }
};

// --- Tests ---

TEST_F(RE2_ConsumeNTest_254, ReturnsTrueAndRemovesConsumedPrefix_254) {
  RE2 caller("");              // arbitrary; not used by ConsumeN
  RE2 pattern_re("");          // passed to ConsumeN; only used by DoMatch seam

  absl::string_view input = "abcdef";
  const RE2::Arg* args[] = {nullptr};
  const int n = 1;

  re2::g_DoMatchReturn   = true;
  re2::g_DoMatchConsumed = 3;  // simulate 3 chars consumed: "abc"

  bool ok = caller.ConsumeN(&input, pattern_re, args, n);

  EXPECT_TRUE(ok);
  EXPECT_EQ(input, "def");  // prefix removed
  // Ensure DoMatch saw the original text and correct anchor.
  EXPECT_EQ(re2::g_LastText, "abcdef");
  EXPECT_EQ(re2::g_LastAnchor, re2::RE2::ANCHOR_START);
}

TEST_F(RE2_ConsumeNTest_254, ReturnsFalseAndLeavesInputUnchanged_254) {
  RE2 caller("");
  RE2 pattern_re("");

  absl::string_view input = "xyz";
  const RE2::Arg* args[] = {nullptr};
  const int n = 1;

  re2::g_DoMatchReturn   = false;
  re2::g_DoMatchConsumed = 2;  // should be ignored when DoMatch returns false

  bool ok = caller.ConsumeN(&input, pattern_re, args, n);

  EXPECT_FALSE(ok);
  EXPECT_EQ(input, "xyz");  // unchanged
  EXPECT_EQ(re2::g_LastText, "xyz");  // DoMatch still received the full input
  EXPECT_EQ(re2::g_LastAnchor, re2::RE2::ANCHOR_START);
}

TEST_F(RE2_ConsumeNTest_254, ZeroConsumedStillTrueAndNoChangeToInput_254) {
  RE2 caller("");
  RE2 pattern_re("");

  absl::string_view input = "hello";
  const RE2::Arg* args[] = {nullptr};
  const int n = 1;

  re2::g_DoMatchReturn   = true;
  re2::g_DoMatchConsumed = 0;

  bool ok = caller.ConsumeN(&input, pattern_re, args, n);

  EXPECT_TRUE(ok);
  EXPECT_EQ(input, "hello");  // no prefix removed
  EXPECT_EQ(re2::g_LastText, "hello");
}

TEST_F(RE2_ConsumeNTest_254, ConsumedEqualsInputLengthResultsInEmptyInput_254) {
  RE2 caller("");
  RE2 pattern_re("");

  absl::string_view input = "12345";
  const RE2::Arg* args[] = {nullptr};
  const int n = 1;

  re2::g_DoMatchReturn   = true;
  re2::g_DoMatchConsumed = 5;  // entire string

  bool ok = caller.ConsumeN(&input, pattern_re, args, n);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(input.empty());
  EXPECT_EQ(re2::g_LastText, "12345");
}

TEST_F(RE2_ConsumeNTest_254, ForwardsArgsPointerAndCountToDoMatch_254) {
  RE2 caller("");
  RE2 pattern_re("");

  RE2::Arg a0(nullptr);  // concrete objects not functionally used
  RE2::Arg a1(nullptr);
  const RE2::Arg* args[] = {&a0, &a1};
  const int n = 2;

  absl::string_view input = "params";
  re2::g_DoMatchReturn   = true;
  re2::g_DoMatchConsumed = 1;

  bool ok = caller.ConsumeN(&input, pattern_re, args, n);

  EXPECT_TRUE(ok);
  EXPECT_EQ(re2::g_LastArgs, args);  // same pointer forwarded
  EXPECT_EQ(re2::g_LastN, n);        // same count forwarded
  EXPECT_EQ(re2::g_LastAnchor, re2::RE2::ANCHOR_START);
}

