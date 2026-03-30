// File: prog_set_dfa_mem_test_123.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

#include "re2/prog.h"

namespace {

using re2::Prog;

class ProgSetDfaMemTest_123 : public ::testing::Test {
protected:
  Prog prog_;
};

// Normal: setting a typical positive value updates the observable state.
TEST_F(ProgSetDfaMemTest_123, SetDfaMem_UpdatesValue_123) {
  const int64_t v1 = 12345;
  const int64_t v2 = 67890;

  // Set to v1 and verify
  prog_.set_dfa_mem(v1);
  EXPECT_EQ(prog_.dfa_mem(), v1);

  // Change to v2 and verify it changes accordingly
  prog_.set_dfa_mem(v2);
  EXPECT_EQ(prog_.dfa_mem(), v2);
  EXPECT_NE(prog_.dfa_mem(), v1);
}

// Boundary: zero should be accepted and observable.
TEST_F(ProgSetDfaMemTest_123, SetDfaMem_ZeroValue_123) {
  prog_.set_dfa_mem(0);
  EXPECT_EQ(prog_.dfa_mem(), 0);
}

// Boundary: negative values should be preserved as-is if the interface allows any int64_t.
TEST_F(ProgSetDfaMemTest_123, SetDfaMem_NegativeValue_123) {
  const int64_t neg = -987654321;
  prog_.set_dfa_mem(neg);
  EXPECT_EQ(prog_.dfa_mem(), neg);
}

// Boundary: INT64_MAX should be stored and reported correctly.
TEST_F(ProgSetDfaMemTest_123, SetDfaMem_Int64Max_123) {
  const int64_t maxv = std::numeric_limits<int64_t>::max();
  prog_.set_dfa_mem(maxv);
  EXPECT_EQ(prog_.dfa_mem(), maxv);
}

// Stability: setting the same value repeatedly should keep the observable state unchanged.
TEST_F(ProgSetDfaMemTest_123, SetDfaMem_IdempotentSameValue_123) {
  const int64_t v = 424242;
  prog_.set_dfa_mem(v);
  EXPECT_EQ(prog_.dfa_mem(), v);

  // Set the same value again; observable state should remain the same.
  prog_.set_dfa_mem(v);
  EXPECT_EQ(prog_.dfa_mem(), v);
}

}  // namespace
