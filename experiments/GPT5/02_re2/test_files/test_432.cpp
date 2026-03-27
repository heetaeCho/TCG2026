// File: ./TestProjects/re2/tests/prog_dfa_bail_flag_test_432.cc

#include "gtest/gtest.h"
#include "re2/prog.h"

// We only observe the effect through the global flag defined in dfa.cc.
// This is not private state; it has external linkage in namespace re2.
namespace re2 {
extern bool dfa_should_bail_when_slow;
}

namespace {

class ProgDfaBailFlagTest_432 : public ::testing::Test {
 protected:
  bool original_ = true;

  void SetUp() override {
    // Snapshot the original value to avoid cross-test contamination.
    original_ = re2::dfa_should_bail_when_slow;
  }

  void TearDown() override {
    // Restore the original value after each test.
    re2::Prog p;
    p.TESTING_ONLY_set_dfa_should_bail_when_slow(original_);
  }
};

// Verifies the module-level default (from dfa.cc) is true.
TEST_F(ProgDfaBailFlagTest_432, DefaultIsTrue_432) {
  EXPECT_TRUE(re2::dfa_should_bail_when_slow);
}

// Setting the flag to false through the public testing method updates the observable flag.
TEST_F(ProgDfaBailFlagTest_432, SetFalseThroughMethod_432) {
  re2::Prog p;
  p.TESTING_ONLY_set_dfa_should_bail_when_slow(false);
  EXPECT_FALSE(re2::dfa_should_bail_when_slow);
}

// Toggling back to true through the public testing method updates the observable flag.
TEST_F(ProgDfaBailFlagTest_432, SetTrueThroughMethod_432) {
  re2::Prog p;
  p.TESTING_ONLY_set_dfa_should_bail_when_slow(false);
  ASSERT_FALSE(re2::dfa_should_bail_when_slow);

  p.TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  EXPECT_TRUE(re2::dfa_should_bail_when_slow);
}

// Demonstrates that the flag is global: changes via one instance are visible to another.
TEST_F(ProgDfaBailFlagTest_432, GlobalAcrossInstances_432) {
  re2::Prog a;
  re2::Prog b;

  a.TESTING_ONLY_set_dfa_should_bail_when_slow(false);
  EXPECT_FALSE(re2::dfa_should_bail_when_slow);

  b.TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  EXPECT_TRUE(re2::dfa_should_bail_when_slow);
}

}  // namespace
