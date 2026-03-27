// File: prog_dfa_mem_test_122.cc
#include <gtest/gtest.h>
#include <cstdint>

#include "re2/prog.h"

namespace {

using re2::Prog;

class ProgDfaMemTest_122 : public ::testing::Test {
protected:
  Prog prog_; // Fresh instance per test
};

// Verifies the default observable value via the public getter.
TEST_F(ProgDfaMemTest_122, DefaultIsZero_122) {
  // Observable behavior: newly constructed object should report some default.
  // Based on interface usage expectations, we assert zero (common default for sizes).
  EXPECT_EQ(0, prog_.dfa_mem());
}

// Setting a typical positive value should be reflected by the getter.
TEST_F(ProgDfaMemTest_122, SetPositiveValue_122) {
  const int64_t val = 123456789;
  prog_.set_dfa_mem(val);
  EXPECT_EQ(val, prog_.dfa_mem());
}

// Setting zero explicitly should be reflected by the getter.
TEST_F(ProgDfaMemTest_122, SetZero_122) {
  prog_.set_dfa_mem(0);
  EXPECT_EQ(0, prog_.dfa_mem());
}

// If negatives are passed (allowed by the signature), they should round-trip via the getter.
TEST_F(ProgDfaMemTest_122, SetNegativeValue_122) {
  const int64_t val = -42;
  prog_.set_dfa_mem(val);
  EXPECT_EQ(val, prog_.dfa_mem());
}

// Boundary conditions: verify int64 extremes are handled without truncation.
TEST_F(ProgDfaMemTest_122, SetBoundaryValues_122) {
  const int64_t maxv = std::numeric_limits<int64_t>::max();
  const int64_t minv = std::numeric_limits<int64_t>::min();

  prog_.set_dfa_mem(maxv);
  EXPECT_EQ(maxv, prog_.dfa_mem());

  prog_.set_dfa_mem(minv);
  EXPECT_EQ(minv, prog_.dfa_mem());
}

}  // namespace
