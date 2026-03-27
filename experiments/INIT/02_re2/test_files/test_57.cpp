// File: re2_reverse_program_fanout_shim_test_57.cc

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "re2/re2.h"

// Declare the shim we are testing (as it lives in a .cc in the project).
namespace re2_python {
std::vector<int> RE2ReverseProgramFanoutShim(const re2::RE2& self);
}

using ::re2::RE2;

class RE2ReverseProgramFanoutShimTest_57 : public ::testing::Test {};

// Normal operation: simple literal.
TEST_F(RE2ReverseProgramFanoutShimTest_57, SimpleLiteralMatchesDirectCall_57) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok()) << "Pattern should construct successfully";

  std::vector<int> direct_hist;
  int direct_ret = re.ReverseProgramFanout(&direct_hist);

  std::vector<int> shim_hist = re2_python::RE2ReverseProgramFanoutShim(re);

  // Observable equivalence: the shim must reproduce what the direct call fills.
  EXPECT_EQ(shim_hist, direct_hist);
  // Sanity: size agreement with returned value from direct call is a reasonable invariant to check.
  // (We avoid assuming any deeper internal meaning of the values.)
  EXPECT_GE(direct_ret, 0);
  EXPECT_FALSE(shim_hist.empty());
}

// Normal operation: alternation + repetition.
TEST_F(RE2ReverseProgramFanoutShimTest_57, AlternationAndKleeneMatchesDirectCall_57) {
  RE2 re("(ab|cd)*ef");
  ASSERT_TRUE(re.ok()) << "Pattern should construct successfully";

  std::vector<int> direct_hist;
  (void)re.ReverseProgramFanout(&direct_hist);

  std::vector<int> shim_hist = re2_python::RE2ReverseProgramFanoutShim(re);

  EXPECT_EQ(shim_hist, direct_hist);
  EXPECT_FALSE(shim_hist.empty());
}

// Boundary: empty pattern (matches empty string).
TEST_F(RE2ReverseProgramFanoutShimTest_57, EmptyPatternMatchesDirectCall_57) {
  RE2 re("");
  ASSERT_TRUE(re.ok()) << "Empty pattern is allowed and should be ok()";

  std::vector<int> direct_hist;
  (void)re.ReverseProgramFanout(&direct_hist);

  std::vector<int> shim_hist = re2_python::RE2ReverseProgramFanoutShim(re);

  EXPECT_EQ(shim_hist, direct_hist);
  // We don't assert specific contents; we only assert equivalence to the public API behavior.
}

// Exceptional/error-ish input: syntactically invalid pattern.
// We do not assume internal behavior; we only verify shim == direct call.
TEST_F(RE2ReverseProgramFanoutShimTest_57, InvalidPatternStillConsistentWithDirectCall_57) {
  RE2 re("(");  // Invalid regex
  ASSERT_FALSE(re.ok()) << "Construction should report an error for invalid pattern";

  std::vector<int> direct_hist;
  (void)re.ReverseProgramFanout(&direct_hist);

  std::vector<int> shim_hist = re2_python::RE2ReverseProgramFanoutShim(re);

  EXPECT_EQ(shim_hist, direct_hist);
}

// Stability: multiple calls on the same object should produce identical results and match direct call.
TEST_F(RE2ReverseProgramFanoutShimTest_57, MultipleCallsConsistent_57) {
  RE2 re("^(foo|bar)+$");
  ASSERT_TRUE(re.ok());

  std::vector<int> direct_hist;
  (void)re.ReverseProgramFanout(&direct_hist);

  std::vector<int> shim_hist1 = re2_python::RE2ReverseProgramFanoutShim(re);
  std::vector<int> shim_hist2 = re2_python::RE2ReverseProgramFanoutShim(re);

  EXPECT_EQ(shim_hist1, direct_hist);
  EXPECT_EQ(shim_hist2, direct_hist);
  EXPECT_EQ(shim_hist1, shim_hist2);
}
