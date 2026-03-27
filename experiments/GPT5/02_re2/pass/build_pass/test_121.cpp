// File: prog_bit_state_text_max_size_test_121.cc
#include <gtest/gtest.h>
#include <type_traits>
#include "re2/prog.h"

namespace re2 {

class ProgBitStateTextMaxSizeTest_121 : public ::testing::Test {
protected:
  Prog prog_;  // Fresh instance per test
};

// [Normal] Default-constructed value should be zero (per observable behavior).
TEST_F(ProgBitStateTextMaxSizeTest_121, DefaultIsZero_121) {
  EXPECT_EQ(static_cast<size_t>(0), prog_.bit_state_text_max_size());
}

// [Boundary] Repeated calls should be consistent and have no side effects.
TEST_F(ProgBitStateTextMaxSizeTest_121, MultipleCallsConsistent_121) {
  size_t first = prog_.bit_state_text_max_size();
  size_t second = prog_.bit_state_text_max_size();
  EXPECT_EQ(first, second);
}

// [Type] Return type should be size_t (compile-time check).
TEST_F(ProgBitStateTextMaxSizeTest_121, ReturnTypeIsSizeT_121) {
  static_assert(std::is_same<decltype(std::declval<Prog&>().bit_state_text_max_size()), size_t>::value,
                "bit_state_text_max_size() must return size_t");
  (void)prog_; // silence unused-member warning for some compilers
}

// [Exceptional/Negative coverage via observable behavior]
// Public setters that affect other fields should not affect bit_state_text_max_size().
// We do not assume internal relationships; we only verify the observable outcome.
TEST_F(ProgBitStateTextMaxSizeTest_121, UnrelatedSettersDoNotChangeValue_121) {
  const size_t before = prog_.bit_state_text_max_size();

  // Exercise a few public setters/getters unrelated to bit_state_text_max_size().
  prog_.set_anchor_start(true);
  prog_.set_anchor_end(true);
  prog_.set_reversed(true);
  prog_.set_start(123);
  prog_.set_start_unanchored(456);
  prog_.set_dfa_mem(789);

  const size_t after = prog_.bit_state_text_max_size();
  EXPECT_EQ(before, after);
}

// [Robustness] Using other benign calls should not alter the value.
// We only call methods whose effects are observable via their own interfaces;
// we do not rely on any side effects on bit_state_text_max_size().
TEST_F(ProgBitStateTextMaxSizeTest_121, OtherBenignCallsPreserveValue_121) {
  const size_t baseline = prog_.bit_state_text_max_size();

  // Call simple observable getters; ensure they don't mutate the target value.
  (void)prog_.anchor_start();
  (void)prog_.anchor_end();
  (void)prog_.reversed();
  (void)prog_.start();
  (void)prog_.start_unanchored();
  (void)prog_.list_count();
  (void)prog_.dfa_mem();

  EXPECT_EQ(baseline, prog_.bit_state_text_max_size());
}

}  // namespace re2
