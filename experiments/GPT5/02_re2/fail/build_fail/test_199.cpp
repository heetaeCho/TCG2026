// File: pcre_do_match_test_199.cc
#include <gtest/gtest.h>
#include <cstddef>
#include <string>

#include "absl/strings/string_view.h"

// Include the production header
#include "TestProjects/re2/util/pcre.h"

// We don't rely on real Anchor definition; use a neutral value.
namespace {
template <typename T>
constexpr T ZeroEnum() { return static_cast<T>(0); }
}

namespace re2 {

// ---- Test seam: provide minimal definitions needed to link ----
// These are NO-OP bodies to allow constructing PCRE for the tests.
// They do not (and must not) simulate internal behavior.

PCRE::PCRE(const char* /*pattern*/) {}
PCRE::~PCRE() {}

// ---- Capture state for observing DoMatch -> DoMatchImpl forwarding ----
static absl::string_view g_last_text;
static Anchor            g_last_anchor;
static size_t*           g_last_consumed = nullptr;
static const PCRE::Arg* const* g_last_args = nullptr;
static int               g_last_n = 0;
static int*              g_last_vec = nullptr;
static int               g_last_vecsize = 0;
static int               g_call_count = 0;
static bool              g_stub_result = false;

// Test stub for the private method DoMatchImpl that DoMatch calls.
// We capture all parameters to validate what DoMatch forwards.
// IMPORTANT: We are not reproducing internal behavior—just recording inputs.
bool PCRE::DoMatchImpl(absl::string_view text,
                       Anchor anchor,
                       size_t* consumed,
                       const Arg* const* args,
                       int n,
                       int* vec,
                       int vecsize) const {
  g_call_count++;
  g_last_text     = text;
  g_last_anchor   = anchor;
  g_last_consumed = consumed;
  g_last_args     = args;
  g_last_n        = n;
  g_last_vec      = vec;
  g_last_vecsize  = vecsize;
  return g_stub_result;
}

}  // namespace re2

// ---------------------- Test Fixture ----------------------
class PCRE_DoMatchTest_199 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Reset capture state
    re2::g_last_text = absl::string_view();
    re2::g_last_anchor = ZeroEnum<Anchor>();
    re2::g_last_consumed = nullptr;
    re2::g_last_args = nullptr;
    re2::g_last_n = 0;
    re2::g_last_vec = nullptr;
    re2::g_last_vecsize = 0;
    re2::g_call_count = 0;
    re2::g_stub_result = false;
  }
};

// ---------------------- Tests ----------------------

// Verifies: DoMatch asserts on n < 0 before calling DoMatchImpl.
TEST_F(PCRE_DoMatchTest_199, DeathOnNegativeN_199) {
#ifndef NDEBUG
  re2::PCRE re("^.*$");  // Constructor is a test seam no-op.
  size_t consumed = 0;
  // args can be null when n == 0; here we pass nullptr anyway.
  EXPECT_DEATH(
      (void)re.DoMatch(absl::string_view("abc"),
                       ZeroEnum<Anchor>(),
                       &consumed,
                       /*args=*/nullptr,
                       /*n=*/-1),
      "");  // Any assert message; empty regex suffices.
#else
  GTEST_SKIP() << "Assertions disabled (NDEBUG defined); skipping death test.";
#endif
}

// Verifies: DoMatch forwards parameters and returns the value from DoMatchImpl.
TEST_F(PCRE_DoMatchTest_199, ForwardsParamsAndReturn_199) {
  re2::PCRE re("x");
  size_t consumed = 1234;
  const re2::PCRE::Arg* args[] = {nullptr, nullptr};
  const int n = 2;

  // Make stub return true and check DoMatch returns true.
  re2::g_stub_result = true;
  bool result_true = re.DoMatch(absl::string_view("hello"),
                                ZeroEnum<Anchor>(),
                                &consumed,
                                args,
                                n);
  EXPECT_TRUE(result_true);
  EXPECT_EQ(re2::g_call_count, 1);
  EXPECT_EQ(re2::g_last_text, absl::string_view("hello"));
  EXPECT_EQ(re2::g_last_anchor, ZeroEnum<Anchor>());
  EXPECT_EQ(re2::g_last_consumed, &consumed);
  EXPECT_EQ(re2::g_last_args, args);
  EXPECT_EQ(re2::g_last_n, n);
  // vec must be allocated by DoMatch; we only verify it's non-null here.
  EXPECT_NE(re2::g_last_vec, nullptr);
  // vecsize must be (1 + n) * 3 per implementation.
  EXPECT_EQ(re2::g_last_vecsize, (1 + n) * 3);

  // Make stub return false and check DoMatch returns false.
  re2::g_stub_result = false;
  bool result_false = re.DoMatch(absl::string_view("bye"),
                                 ZeroEnum<Anchor>(),
                                 &consumed,
                                 args,
                                 n);
  EXPECT_FALSE(result_false);
  EXPECT_EQ(re2::g_call_count, 2);
  EXPECT_EQ(re2::g_last_text, absl::string_view("bye"));
}

// Verifies: vecsize calculation when n == 0.
TEST_F(PCRE_DoMatchTest_199, VecSizeWhenNoArgs_199) {
  re2::PCRE re("x");
  size_t consumed = 0;

  const int n = 0;
  re2::g_stub_result = true;  // Return value irrelevant; we inspect parameters.
  (void)re.DoMatch(absl::string_view("t"), ZeroEnum<Anchor>(), &consumed,
                   /*args=*/nullptr, n);

  EXPECT_EQ(re2::g_call_count, 1);
  EXPECT_NE(re2::g_last_vec, nullptr);
  EXPECT_EQ(re2::g_last_vecsize, (1 + n) * 3);  // (1+0)*3 == 3
}

// Verifies: vecsize calculation when n > 0 for a second sample.
TEST_F(PCRE_DoMatchTest_199, VecSizeWithCaptures_199) {
  re2::PCRE re("x");
  size_t consumed = 0;
  const re2::PCRE::Arg* args[] = {nullptr, nullptr, nullptr, nullptr, nullptr};
  const int n = static_cast<int>(std::size(args));

  re2::g_stub_result = true;
  (void)re.DoMatch(absl::string_view("text"),
                   ZeroEnum<Anchor>(),
                   &consumed,
                   args,
                   n);

  EXPECT_EQ(re2::g_call_count, 1);
  EXPECT_NE(re2::g_last_vec, nullptr);
  EXPECT_EQ(re2::g_last_vecsize, (1 + n) * 3);  // validates formula
}

// Verifies: DoMatch calls DoMatchImpl exactly once per invocation.
TEST_F(PCRE_DoMatchTest_199, CallsImplExactlyOncePerCall_199) {
  re2::PCRE re("x");
  size_t consumed = 0;

  re2::g_stub_result = true;
  (void)re.DoMatch(absl::string_view("A"), ZeroEnum<Anchor>(), &consumed, nullptr, 0);
  (void)re.DoMatch(absl::string_view("B"), ZeroEnum<Anchor>(), &consumed, nullptr, 0);
  EXPECT_EQ(re2::g_call_count, 2);
}
