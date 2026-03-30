// File: re2_program_fanout_shim_test_56.cc

#include <gtest/gtest.h>
#include <vector>
#include <string>

#include "re2/re2.h"

// Forward declaration of the shim under test.
// (Alternatively, include the header/cc where it's defined.)
namespace re2_python {
std::vector<int> RE2ProgramFanoutShim(const re2::RE2& self);
}

// Test fixture kept minimal: no reliance on internal state or behavior.
class RE2ProgramFanoutShimTest_56 : public ::testing::Test {};

// [Normal operation] Simple alternation should produce the same histogram via shim vs direct call.
TEST_F(RE2ProgramFanoutShimTest_56, ReturnsSameHistogram_SimpleAlternation_56) {
  re2::RE2 re("(a|b)c");

  // Direct call to the public interface
  std::vector<int> direct_hist;
  (void)re.ProgramFanout(&direct_hist);  // We don't assert on the return value; we compare observable hist data.

  // Shim call
  std::vector<int> shim_hist = re2_python::RE2ProgramFanoutShim(re);

  // Observable behavior: identical contents
  ASSERT_EQ(shim_hist.size(), direct_hist.size());
  EXPECT_EQ(shim_hist, direct_hist);
}

// [Normal operation] A literal pattern should also match histograms exactly.
TEST_F(RE2ProgramFanoutShimTest_56, ReturnsSameHistogram_LiteralPattern_56) {
  re2::RE2 re("hello world");

  std::vector<int> direct_hist;
  (void)re.ProgramFanout(&direct_hist);

  std::vector<int> shim_hist = re2_python::RE2ProgramFanoutShim(re);

  ASSERT_EQ(shim_hist.size(), direct_hist.size());
  EXPECT_EQ(shim_hist, direct_hist);
}

// [Boundary / Exceptional observable case] Invalid pattern: ensure shim mirrors direct behavior.
TEST_F(RE2ProgramFanoutShimTest_56, ReturnsSameHistogram_InvalidPattern_56) {
  re2::RE2 re("(");  // Typically invalid; treat as black box and rely only on public surface.

  // It's fine to observe public status if useful, but we don't assert behavior beyond histogram equality.
  // EXPECT_FALSE(re.ok());  // Optional: If asserting status is acceptable in your suite.

  std::vector<int> direct_hist;
  (void)re.ProgramFanout(&direct_hist);

  std::vector<int> shim_hist = re2_python::RE2ProgramFanoutShim(re);

  ASSERT_EQ(shim_hist.size(), direct_hist.size());
  EXPECT_EQ(shim_hist, direct_hist);
}

// [Additional coverage] Pattern with quantifiers for a slightly larger program graph.
TEST_F(RE2ProgramFanoutShimTest_56, ReturnsSameHistogram_Quantifiers_56) {
  re2::RE2 re("(ab|cd)+e?");

  std::vector<int> direct_hist;
  (void)re.ProgramFanout(&direct_hist);

  std::vector<int> shim_hist = re2_python::RE2ProgramFanoutShim(re);

  ASSERT_EQ(shim_hist.size(), direct_hist.size());
  EXPECT_EQ(shim_hist, direct_hist);
}
